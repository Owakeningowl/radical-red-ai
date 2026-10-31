#!/usr/bin/env python3
"""Name the non-AI functions the AI calls, by lining up all of CFRU's objects with the ROM. Extends build/map.json."""
import collections, glob, json, os, re, struct, subprocess, sys, pickle
sys.path.insert(0, os.path.dirname(__file__))
import rrv
ROOT = rrv.ROOT
BIN = rrv.BIN
m = json.load(open(f'{ROOT}/build/map.json'))
rows = rrv.rom_rows()
rf = rrv.rom_funcs(rows)
ld = rrv.ld_names()
ldset = set(ld.values())
cache = f'{ROOT}/build/allfuncs.pkl'
if os.path.exists(cache):
    S = pickle.load(open(cache, 'rb'))
else:
    S = []
    for o in sorted(glob.glob(f'{ROOT}/rr41/oall/*.o')):
        fn = os.path.basename(o)[:-2]
        rel = {}
        for line in rrv.sh(BIN + 'objdump', '-r', '-j', '.text', o).splitlines():
            mo = re.match(r'([0-9a-f]{8}) (R_ARM_\S+)\s+(\S+)', line)
            if mo:
                rel[int(mo.group(1), 16)] = mo.group(3)
        subprocess.run([BIN + 'objcopy', '-O', 'binary', '-j', '.text', o, o + '.bin'])
        code = open(o + '.bin', 'rb').read() if os.path.exists(o + '.bin') else b''
        syms = []
        for line in rrv.sh(BIN + 'nm', '-n', '-S', o).splitlines():
            mo = re.match(r'([0-9a-f]{8}) ([0-9a-f]{8}) ([tT]) (\S+)', line)
            if mo:
                syms.append((int(mo.group(1), 16), int(mo.group(2), 16), mo.group(4)))
        allrows = rrv.parse(rrv.sh(BIN + 'objdump', '-d', '-M', 'force-thumb', o))
        for start, size, name in syms:
            fr = [r for r in allrows if start <= r[0] < start + size]
            lits = rrv.literal_addrs(fr)
            fr = [r for r in fr if r[0] not in lits]
            def lit(x, args):
                t = ((x + 4) & ~3) + rrv.pc_off(args)
                if t in rel:
                    return ('s', rel[t])
                if t + 4 <= len(code):
                    return ('k', struct.unpack_from('<I', code, t)[0])
                return ('u', 0)
            def call(x, args, known):
                n = rel.get(x)
                if n is None:
                    mt = re.search(r'<(\w+)', args)
                    n = mt.group(1) if mt else None
                if n and n.startswith('_call_via_r'):
                    v = known.get(int(n[11:]))
                    return v[1] if v and v[0] == 's' else None
                if n and n.startswith('__gnu_thumb1_case'):
                    return None
                return rrv.ALIAS.get(n, n)
            toks, calls = rrv.tokens(fr, lit, call, rrv.branch_targets(fr))
            S.append(dict(name=name, file=fn, size=size, toks=toks, calls=calls))
    pickle.dump(S, open(cache, 'wb'))
print('source functions', len(S))
AI = lambda a: 0x90c3e00 <= a < 0x90e2000 or a >= 0x9350000
R = sorted(a for a in rf if not AI(a) and a >= 0x9000000)
print('rom functions outside AI', len(R))
inv = {f'@{a:x}': n for n, a in m.items()}
known = ldset | set(m)
def bag_s(s):
    c = collections.Counter()
    for t in s['toks']:
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
new = {}
for loop in range(3):
    inv = {f'@{a:x}': n for n, a in list(m.items()) + list(new.items())}
    known = ldset | set(m) | set(new)
    bs = [bag_s(s) for s in S]
    br = {a: bag_r(a) for a in R}
    # exact-ish matches by bag, using size as a guide; order is only a tie break
    cand = {}
    by_tok = collections.defaultdict(list)
    for a, b in br.items():
        for t in b:
            by_tok[t].append(a)
    pairs = []
    for i, s in enumerate(S):
        x = bs[i]
        tot = sum(x.values())
        if tot < 2 or s['name'] in m:
            continue
        score = collections.Counter()
        for t, c in x.items():
            lst = by_tok.get(t, [])
            if len(lst) > 80:
                continue
            for a in lst:
                score[a] += min(c, br[a][t])
        best = []
        for a, inter in score.most_common(6):
            size = (rf[a]['end'] - a) / max(s['size'], 1)
            if not 0.4 < size < 2.5:
                continue
            sim = 2 * inter / (tot + sum(br[a].values()))
            best.append((sim, a))
        best.sort(reverse=True)
        if best and best[0][0] >= 0.6 and (len(best) == 1 or best[0][0] - best[1][0] >= 0.1):
            pairs.append((best[0][0], s['name'], best[0][1]))
    pairs.sort(reverse=True)
    used = set(m.values()) | set(new.values())
    added = 0
    for sim, n, a in pairs:
        if n in m or n in new or a in used:
            continue
        new[n] = a
        used.add(a)
        added += 1
    print('loop', loop, 'added', added)
    if not added:
        break
m2 = dict(m)
m2.update(new)
json.dump(m2, open(f'{ROOT}/build/map.json', 'w'), indent=0)
print('total names', len(m2))
# coverage of what the AI calls
called = collections.Counter()
for a in rf:
    if AI(a):
        for c in rf[a]['calls']:
            if c.startswith('@'):
                called[int(c[1:], 16)] += 1
inv = {a: n for n, a in m2.items()}
un = [(c, a) for a, c in called.items() if a not in inv]
print('AI call sites to unnamed functions', sum(c for c, a in un), 'of', sum(called.values()), 'distinct', len(un))
print([(c, hex(a)) for c, a in sorted(un, reverse=True)[:24]])
