#!/usr/bin/env python3
"""Compare the rebuilt AI source with the ROM, function by function.

    rrv.py build            compile rr41/src/Battle_AI/*.c (no inlining) into rr41/o
    rrv.py map              pair ROM functions with source functions by aligning their calls -> build/map.json
    rrv.py report [--list]  count how many functions match, list what differs
    rrv.py show NAME        print the differing tokens of one function

Each function becomes a bag of tokens that survive compiler noise:
    c:Name            a call
    a:Name:rN=V       a known constant passed to that call
    i:V               a compare against a constant
Registers are tracked in a straight line, so "movs r3,#214; adds r3,#255" is 469."""
import collections, difflib, json, os, pickle, re, struct, subprocess, sys

ROOT = os.path.expanduser('~/Downloads/radical-red-ai')
BIN = '/opt/devkitpro/devkitARM/bin/arm-none-eabi-'
ROM = os.path.join(ROOT, 'test/rr.gba')
TREE = os.path.join(ROOT, 'rr41')
FILES = ['ai_master', 'ai_negatives', 'ai_positives', 'ai_advanced', 'ai_switching', 'ai_util', 'ai_partner']
D = open(ROM, 'rb').read()
LO, HI = 0x9000000, 0x9160000
EXTRA = (0x9350000, 0x9352000)
FLAGS = '-mthumb -mno-thumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mno-long-calls -march=armv4t -w -Os -fira-loop-pressure -fipa-pta -fno-tree-loop-distribute-patterns'.split()
ROW = re.compile(r'\s*([0-9a-f]+):\s+([0-9a-f]{4}(?: [0-9a-f]{4})?)\s+(\S+)(?:\s+(.*))?$')
BRANCH = re.compile(r'^(b|beq|bne|bcs|bcc|bmi|bpl|bvs|bvc|bhi|bls|bge|blt|bgt|ble)$')


ALIAS = {'memset': 'Memset', 'memcpy': 'Memcpy', '__aeabi_idiv': '__divsi3', '__aeabi_uidiv': '__udivsi3',
         '__aeabi_uidivmod': '__umodsi3', '__aeabi_idivmod': '__modsi3', '__divsi3': '__divsi3', '__udivsi3': '__udivsi3'}


def u32(a):
    return struct.unpack_from('<I', D, a - 0x8000000)[0]


def sh(*a):
    return subprocess.run(a, capture_output=True, text=True).stdout


def parse(text):
    rows = []
    for line in text.splitlines():
        m = ROW.match(line)
        if m:
            rows.append((int(m.group(1), 16), m.group(3).split('.')[0], (m.group(4) or '').split('@')[0].split(';')[0].strip()))
    return rows


def rom_rows():
    p = os.path.join(ROOT, 'build/romrows.pkl')
    if os.path.exists(p):
        return pickle.load(open(p, 'rb'))
    rows = []
    for a, b in ((LO, HI), EXTRA):
        rows += parse(sh(BIN + 'objdump', '-D', '-b', 'binary', '-m', 'arm', '-M', 'force-thumb', '--adjust-vma=0x8000000',
                         f'--start-address={a:#x}', f'--stop-address={b:#x}', ROM))
    pickle.dump(rows, open(p, 'wb'))
    return rows


def regnum(s):
    m = re.match(r'r(\d+)$', s.strip())
    return int(m.group(1)) if m else None


def tokens(rows, lit, call_name, targets):
    """rows: (addr, op, args). lit(addr, args) gives a literal as ('k', v) or ('s', name).
    call_name(addr, target_text, regs) gives the callee name or None when it isn't a call."""
    known = {}
    out = []
    calls = []
    for x, op, args in rows:
        if x in targets:
            known = {}
        parts = [p.strip() for p in args.split(',')]
        d = regnum(parts[0]) if parts and parts[0] else None
        if op.startswith('ldr') and '[pc' in args:
            v = lit(x, args)
            if d is not None:
                known[d] = v
        elif op == 'bl':
            n = call_name(x, args, known)
            if n is not None:
                out.append(f'c:{n}')
                calls.append(n)
                for r in range(4):
                    v = known.get(r)
                    if v and v[0] == 'k':
                        out.append(f'a:{n}:r{r}={v[1]}')
            for r in (0, 1, 2, 3, 12, 14):
                known.pop(r, None)
        elif op in ('movs', 'mov') and len(parts) == 2:
            if parts[1].startswith('#'):
                known[d] = ('k', int(parts[1][1:]))
            else:
                s = regnum(parts[1])
                if s is not None and s in known:
                    known[d] = known[s]
                else:
                    known.pop(d, None)
        elif op in ('adds', 'subs') and len(parts) == 2 and parts[1].startswith('#') and known.get(d, ('', 0))[0] == 'k':
            n = int(parts[1][1:])
            known[d] = ('k', known[d][1] + (n if op == 'adds' else -n))
        elif op == 'lsls' and len(parts) == 3 and parts[2].startswith('#') and known.get(regnum(parts[1]), ('', 0))[0] == 'k':
            known[d] = ('k', known[regnum(parts[1])][1] << int(parts[2][1:]))
        elif op == 'cmp' and len(parts) == 2:
            if parts[1].startswith('#'):
                v = int(parts[1][1:])
                if v not in (0, 1):
                    out.append(f'i:{v}')
            else:
                s = regnum(parts[1])
                if s in known and known[s][0] == 'k':
                    out.append(f'i:{known[s][1]}')
        elif op in ('str', 'strb', 'strh', 'cmp', 'tst', 'push', 'pop', 'b', 'nop') or BRANCH.match(op):
            pass
        elif d is not None:
            known.pop(d, None)
    return out, calls


def branch_targets(rows):
    t = set()
    for x, op, args in rows:
        if BRANCH.match(op):
            m = re.search(r'(?:0x)?([0-9a-f]+)', args)
            if m:
                t.add(int(m.group(1), 16))
    return t


def pc_off(args):
    m = re.search(r'\[pc(?:, #(\d+))?\]', args)
    return int(m.group(1)) if m and m.group(1) else 0


def literal_addrs(rows):
    s = set()
    for x, op, args in rows:
        if op.startswith('ldr') and '[pc' in args:
            t = ((x + 4) & ~3) + pc_off(args)
            s.update((t, t + 2))
    return s


# ---------- source side
def src_funcs():
    p = os.path.join(ROOT, 'build/srcfuncs.pkl')
    objs = [os.path.join(TREE, 'o', f + '.o') for f in FILES]
    if os.path.exists(p) and all(os.path.getmtime(p) > os.path.getmtime(o) for o in objs):
        return pickle.load(open(p, 'rb'))
    out = {}
    for f, o in zip(FILES, objs):
        rel = {}
        for line in sh(BIN + 'objdump', '-r', '-j', '.text', o).splitlines():
            m = re.match(r'([0-9a-f]{8}) (R_ARM_\S+)\s+(\S+)', line)
            if m:
                rel[int(m.group(1), 16)] = m.group(3)
        subprocess.run([BIN + 'objcopy', '-O', 'binary', '-j', '.text', o, o + '.bin'])
        code = open(o + '.bin', 'rb').read()
        syms = []
        for line in sh(BIN + 'nm', '-n', '-S', o).splitlines():
            m = re.match(r'([0-9a-f]{8}) ([0-9a-f]{8}) ([tT]) (\S+)', line)
            if m:
                syms.append((int(m.group(1), 16), int(m.group(2), 16), m.group(4), m.group(3)))
        rows = parse(sh(BIN + 'objdump', '-d', '-M', 'force-thumb', o))

        def lit(x, args):
            t = ((x + 4) & ~3) + pc_off(args)
            if t in rel:
                n = rel[t]
                return ('s', n)
            if t + 4 <= len(code):
                return ('k', struct.unpack_from('<I', code, t)[0])
            return ('u', 0)

        for start, size, name, bind in syms:
            fr = [r for r in rows if start <= r[0] < start + size]
            lits = literal_addrs(fr)
            fr = [r for r in fr if r[0] not in lits]

            def call(x, args, known, _rel=rel):
                n = _rel.get(x)
                if n is None:
                    m = re.search(r'<(\w+)', args)
                    n = m.group(1) if m else None
                if n and n.startswith('_call_via_r'):
                    v = known.get(int(n[11:]))
                    return v[1] if v and v[0] == 's' else None
                if n and n.startswith('__gnu_thumb1_case'):
                    return None
                return ALIAS.get(n, n)

            toks, calls = tokens(fr, lit, call, branch_targets(fr))
            out[name] = dict(file=f, size=size, toks=toks, calls=calls, local=bind == 't', order=len(out))
    pickle.dump(out, open(p, 'wb'))
    return out


# ---------- ROM side
def rom_funcs(rows):
    p = os.path.join(ROOT, 'build/romfuncs.pkl')
    if os.path.exists(p):
        return pickle.load(open(p, 'rb'))
    idx = {r[0]: i for i, r in enumerate(rows)}
    thunks = {}
    for x, op, args in rows:
        m = re.match(r'bx\s*$', op)
        if op == 'bx' and regnum(args) is not None and regnum(args) < 8:
            pass
    def first(a):
        i = idx.get(a)
        return rows[i] if i is not None else None
    for x, op, args in rows:
        if op == 'bl':
            m = re.search(r'0x([0-9a-f]+)', args)
            if m:
                t = int(m.group(1), 16)
                r = first(t)
                if r and r[1] == 'bx' and regnum(r[2]) is not None:
                    thunks[t] = regnum(r[2])
    def is_start(t):
        i = idx.get(t)
        if i is None or t in thunks:
            return False
        for j in range(i, min(i + 5, len(rows))):
            if rows[j][1] == 'push' and 'lr' in rows[j][2]:
                prev = rows[i - 1]
                return j == i or prev[1] in ('pop', 'bx', 'b', 'nop') or prev[0] != t - 2 or True
        # small leaf: ends in bx lr soon and comes after a terminator
        prev = rows[i - 1]
        if prev[1] in ('pop', 'bx', 'b', 'nop') or not prev[1].startswith(('ldr', 'mov', 'add', 'sub', 'cmp', 'str')):
            for j in range(i, min(i + 24, len(rows))):
                if rows[j][1] == 'bx' and rows[j][2] == 'lr':
                    return True
                if rows[j][1] == 'pop':
                    return False
        return False
    starts = set()
    for x, op, args in rows:
        if op == 'bl':
            m = re.search(r'0x([0-9a-f]+)', args)
            if m and is_start(int(m.group(1), 16)):
                starts.add(int(m.group(1), 16))
    # script tables and hooks point at functions too
    for a in (0x90c904c, 0x90d10d4, 0x90d6998, 0x90cfe04, 0x90cfe5c, 0x90cfeac, 0x90c8f04):
        starts.add(a)
    order = sorted(starts)
    out = {}
    addrs = [r[0] for r in rows]
    import bisect
    ldnames = ld_names()
    for k, a in enumerate(order):
        b = order[k + 1] if k + 1 < len(order) else a + 0x1000
        i, j = bisect.bisect_left(addrs, a), bisect.bisect_left(addrs, b)
        fr = rows[i:j]
        lits = literal_addrs(fr)
        fr = [r for r in fr if r[0] not in lits]

        def lit(x, args):
            t = ((x + 4) & ~3) + pc_off(args)
            try:
                v = u32(t)
            except struct.error:
                return ('u', 0)
            if v in ldnames or (v & ~1) in ldnames:
                return ('s', ldnames.get(v) or ldnames.get(v & ~1))
            if 0x8000000 <= v < 0xA000000:
                return ('s', f'@{v & ~1:x}')
            if 0x2000000 <= v < 0x4000000:
                return ('s', f'@{v:x}')
            return ('k', v)

        def call(x, args, known):
            m = re.search(r'0x([0-9a-f]+)', args)
            if not m:
                return None
            t = int(m.group(1), 16)
            if t in thunks:
                v = known.get(thunks[t])
                return v[1] if v and v[0] == 's' else None
            if a < t < b:
                return None  # long jump inside the function
            return ldnames.get(t) or f'@{t:x}'

        toks, calls = tokens(fr, lit, call, branch_targets(fr))
        out[a] = dict(end=b, toks=toks, calls=calls)
    pickle.dump(out, open(p, 'wb'))
    return out


def ld_names():
    n = {}
    for line in open(os.path.join(ROOT, 'cfru/BPRE.ld')):
        m = re.match(r'(\w+)\s*=\s*0x([0-9A-Fa-f]+)', line)
        if m:
            n[int(m.group(2), 16)] = m.group(1)
    return n


SEEDS = {'AIScript_Negatives': 0x90c904c, 'AIScript_Positives': 0x90d10d4, 'AIScript_SemiSmart': 0x90d6998,
         'ShouldSwitch': 0x90d824c, 'CalcMostSuitableMonToSwitchInto': 0x90d7168, 'AI_TrySwitchOrUseItem': 0x90c802c,
         'GetAIFlags': 0x90c77b0, 'ClearCachedAIData': 0x90c8ba4, 'ClearMonCachedDamageCalcs': 0x90c8ed0,
         'IsValidMovePrediction': 0x90db402, 'IsPredictedToSwitch': 0x90db424, 'RechooseAIMoveAfterSwitchIfNecessary': 0x90c8f04,
         'BattleAI_SetupAIData': 0x90c7868 if False else 0x90c7900 if False else 0x90c7900 if False else None}
SEEDS = {k: v for k, v in SEEDS.items() if v}


def build_map():
    """Line up source functions (object order) with ROM functions (address order), then name callees by
    aligning the calls of good pairs. Repeat, since each round's names make the next round sharper."""
    sf = src_funcs()
    rows = rom_rows()
    rf = rom_funcs(rows)
    ld = set(ld_names().values())
    order = ['ai_advanced', 'ai_master', 'ai_negatives', 'ai_partner', 'ai_positives', 'ai_switching', 'ai_util']
    S = sorted(sf, key=lambda n: (order.index(sf[n]['file']), sf[n]['order']))
    R = sorted(a for a in rf if 0x90c3e00 <= a < 0x90e2000 or a >= 0x9350000)
    m = dict(SEEDS)
    prev = -1
    for loop in range(10):
        inv = {f'@{a:x}': n for n, a in m.items()}
        known = ld | set(m)
        def bag_s(n):
            c = collections.Counter()
            for t in sf[n]['toks']:
                if t.startswith(('c:', 'a:')) and t.split(':')[1] not in known:
                    continue
                c[t] += 1
            return c
        def bag_r(a):
            c = collections.Counter()
            for t in rf[a]['toks']:
                if t.startswith(('c:', 'a:')):
                    h = t.split(':')
                    h[1] = inv.get(h[1], h[1])
                    if h[1].startswith('@'):
                        continue
                    t = ':'.join(h)
                c[t] += 1
            return c
        bs = {n: bag_s(n) for n in S}
        br = {a: bag_r(a) for a in R}
        def score(n, a):
            size = (rf[a]['end'] - a) / max(sf[n]['size'], 1)
            if size > 3 or size < 0.3:
                return -1.0
            x, y = bs[n], br[a]
            tot = sum(x.values()) + sum(y.values())
            sim = (2 * sum((x & y).values()) / tot) if tot else 0.4
            sz = 1 - abs(1 - min(size, 1 / size))
            return 3 * sim + 1.5 * sz - 2.0
        N, M = len(S), len(R)
        GAP = -0.15
        best = [[0.0] * (M + 1) for _ in range(N + 1)]
        back = [[0] * (M + 1) for _ in range(N + 1)]
        for i in range(1, N + 1):
            best[i][0] = i * GAP
        for j in range(1, M + 1):
            best[0][j] = j * GAP
        for i in range(1, N + 1):
            ri, rp, bi, n = best[i], best[i - 1], back[i], S[i - 1]
            for j in range(1, M + 1):
                d = rp[j - 1] + score(n, R[j - 1])
                u = rp[j] + GAP
                l = ri[j - 1] + GAP
                if d >= u and d >= l:
                    ri[j], bi[j] = d, 0
                elif u >= l:
                    ri[j], bi[j] = u, 1
                else:
                    ri[j], bi[j] = l, 2
        new = dict(SEEDS)
        used = set(new.values())
        i, j = N, M
        while i and j:
            k = back[i][j]
            if k == 0:
                n, a = S[i - 1], R[j - 1]
                if n not in new and a not in used and score(n, a) > 0:
                    new[n] = a
                    used.add(a)
                i, j = i - 1, j - 1
            elif k == 1:
                i -= 1
            else:
                j -= 1
        # good pairs name what they call, including functions in other files
        for it in range(5):
            inv2 = {f'@{a:x}': n for n, a in new.items()}
            votes = collections.Counter()
            for name, addr in list(new.items()):
                if name not in sf or addr not in rf:
                    continue
                x_ = sf[name]['calls']
                y_ = [inv2.get(c, c) for c in rf[addr]['calls']]
                for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, x_, y_, autojunk=False).get_opcodes():
                    if op == 'replace' and i2 - i1 == j2 - j1:
                        for x, y in zip(x_[i1:i2], y_[j1:j2]):
                            if y.startswith('@') and x not in new and x not in ld:
                                votes[(x, y)] += 1
            taken = 0
            for (x, y), c in votes.most_common():
                a = int(y[1:], 16)
                if x in new or a in new.values():
                    continue
                if c < 2 and (x not in sf or sf[x]['size'] > 60):
                    continue
                new[x] = a
                taken += 1
            if not taken:
                break
        inv3 = {f'@{a:x}': n for n, a in new.items()}
        known3 = ld | set(new)
        for n in list(new):
            if n in SEEDS or n not in sf or new[n] not in rf:
                continue
            x = collections.Counter(t for t in sf[n]['toks'] if not (t.startswith(('c:', 'a:')) and t.split(':')[1] not in known3))
            y = collections.Counter()
            for t in rf[new[n]]['toks']:
                if t.startswith(('c:', 'a:')):
                    h = t.split(':')
                    h[1] = inv3.get(h[1], h[1])
                    if h[1].startswith('@'):
                        continue
                    t = ':'.join(h)
                y[t] += 1
            tot = sum(x.values()) + sum(y.values())
            if tot >= 8 and 2 * sum((x & y).values()) / tot < 0.3:
                del new[n]
        m = new
        print('loop', loop, 'mapped', len(m))
        if len(m) == prev:
            break
        prev = len(m)
    json.dump(m, open(os.path.join(ROOT, 'build/map.json'), 'w'), indent=0)
    return m


def flatten(name, sf, m, depth=0):
    """source tokens, with small local functions the ROM inlined expanded in place"""
    out = []
    for t in sf[name]['toks']:
        if t.startswith(('c:', 'a:')):
            n = t.split(':')[1]
            if n in sf and n not in m and sf[n].get('local'):
                if t.startswith('c:') and depth < 3:
                    out += flatten(n, sf, m, depth + 1)
                continue
        out.append(t)
    return out


LDSET = set()


def compare():
    LDSET.update(ld_names().values())
    sf = src_funcs()
    rows = rom_rows()
    rf = rom_funcs(rows)
    m = json.load(open(os.path.join(ROOT, 'build/map.json')))
    inv = {f'@{a:x}': n for n, a in m.items()}
    res = {}
    for name, addr in m.items():
        if name not in sf or addr not in rf:
            continue
        a = collections.Counter(t for t in flatten(name, sf, m) if not t.startswith('c:_'))
        b = collections.Counter()
        for t in rf[addr]['toks']:
            for k, v in inv.items():
                pass
            if t.startswith('c:') or t.startswith('a:'):
                head = t.split(':')
                head[1] = inv.get(head[1], head[1])
                t = ':'.join(head)
            b[t] += 1
        # ROM calls to functions we couldn't name say nothing about logic; count them apart
        unk = sum(v for k, v in b.items() if '@' in k and k.startswith('c:'))
        b2 = collections.Counter({k: v for k, v in b.items() if '@' not in k})
        a2 = collections.Counter({k: v for k, v in a.items() if not (k.startswith(('c:', 'a:')) and k.split(':')[1] not in m and k.split(':')[1] not in LDSET)})
        res[name] = dict(addr=addr, src=a2, rom=b2, only_src=a2 - b2, only_rom=b2 - a2, unknown=unk, file=sf[name]['file'], size=sf[name]['size'])
    return res


def main():
    cmd = sys.argv[1]
    if cmd == 'build':
        os.makedirs(os.path.join(TREE, 'o'), exist_ok=True)
        ps = []
        for f in FILES:
            ps.append(subprocess.Popen([BIN + 'gcc', '-c', *FLAGS, '-iquote', '.', '-iquote', 'src', f'src/Battle_AI/{f}.c', '-o', f'o/{f}.o'],
                                       cwd=TREE, stderr=subprocess.PIPE, text=True))
        for f, p in zip(FILES, ps):
            e = p.communicate()[1]
            bad = [l for l in e.splitlines() if 'error' in l]
            print(f, 'ok' if not bad else bad[:4])
    elif cmd == 'map':
        m = build_map()
        for n in ('IsValidMovePrediction', 'CanKnockOut', 'Can2HKO', 'IncreaseViability', 'DecreaseViability', 'IncreaseStatusViability', 'MoveKnocksOutXHits', 'GetAIAbility', 'CalcStrongestMove', 'AccuracyCalc'):
            print(n, hex(m[n]) if n in m else '-')
    elif cmd == 'report':
        r = compare()
        same = [k for k, v in r.items() if not v['only_src'] and not v['only_rom']]
        tot = sum(v['size'] for v in r.values())
        ok = sum(r[k]['size'] for k in same)
        sf = src_funcs()
        print(f'source functions {len(sf)}, paired {len(r)}, identical tokens {len(same)} ({100 * ok // max(tot, 1)}% of paired bytes)')
        print('paired bytes', tot, 'of', sum(v['size'] for v in sf.values()))
        if '--list' in sys.argv:
            for k, v in sorted(r.items(), key=lambda kv: -sum(kv[1]['only_src'].values()) - sum(kv[1]['only_rom'].values())):
                n = sum(v['only_src'].values()) + sum(v['only_rom'].values())
                if n:
                    print(f"{k} {v['addr']:#x} diff {n} of {sum(v['src'].values())}")
    elif cmd == 'show':
        r = compare()[sys.argv[2]]
        print('SOURCE ONLY', sorted(r['only_src'].elements()))
        print('ROM ONLY', sorted(r['only_rom'].elements()))


if __name__ == '__main__':
    main()
