#!/usr/bin/env python3
"""Name the Radical Red AI functions by comparing them with CFRU compiled from source.

Each function becomes an ordered list of what it does that survives a compiler change: calls to known functions,
globals it reads, and small constants it compares. ROM functions and source functions are paired by similarity, then
paired functions name what they call, and the whole thing repeats.
"""
import collections, difflib, json, os, re, struct, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
from rr import *
ROOT = os.path.expanduser('~/Downloads/radical-red-ai')
FILES = ['ai_master', 'ai_negatives', 'ai_positives', 'ai_util', 'ai_advanced', 'ai_switching', 'ai_partner']
LO, HI = 0x09000000, 0x09300000
OBJDIR = 'ni'


def ld_syms():
    out = {}
    for line in open(os.path.join(CFRU, 'BPRE.ld')):
        m = re.match(r'\s*(?://)?\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', line)
        if m:
            v = int(m.group(2), 16)
            out.setdefault(v & ~1 if v >= 0x08000000 else v, m.group(1))
    return out


LD = ld_syms()
NAMES = dict(LD)


def rom_funcs():
    """function starts: every BL target and odd literal pointing into the new code"""
    starts = set()
    for o in range(LO & 0x1FFFFFF, HI & 0x1FFFFFF, 2):
        a, b = struct.unpack_from('<HH', rom, o)
        if (a & 0xF800) == 0xF000 and (b & 0xF800) == 0xF800:
            hi = a & 0x7FF
            if hi & 0x400:
                hi -= 0x800
            t = 0x08000000 + o + 4 + (hi << 12) + ((b & 0x7FF) << 1)
            if LO <= t < HI and (u16(t) & 0xFF00) in (0xB500, 0xB400, 0xB000) or (LO <= t < HI and (u16(t) & 0xFE00) == 0xB400):
                starts.add(t)
    for o in range(LO & 0x1FFFFFF, HI & 0x1FFFFFF, 4):
        v = struct.unpack_from('<I', rom, o)[0]
        if LO <= v < HI and v & 1 and (u16(v & ~1) & 0xFE00) == 0xB400:
            starts.add(v & ~1)
    return sorted(starts)


def dis_rom(a, b):
    t = subprocess.run([BIN + 'objdump', '-D', '-b', 'binary', '-m', 'arm', '-M', 'force-thumb', '--adjust-vma=0x08000000',
                        f'--start-address={a:#x}', f'--stop-address={b:#x}', ROM], capture_output=True, text=True).stdout
    rows = []
    for line in t.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{4}(?: [0-9a-f]{4})?)\s+(\S+)(?:\s+(.*))?$', line)
        if m:
            rows.append((int(m.group(1), 16), m.group(3).split('.')[0], (m.group(4) or '').split('@')[0].strip()))
    return rows


_CACHE = {}


def _all_rows():
    if 'rows' not in _CACHE:
        rows = dis_rom(LO + 0x60000, LO + 0x100000) + dis_rom(0x09350000, 0x09352000)
        _CACHE['rows'] = rows
        _CACHE['addr'] = [r[0] for r in rows]
    return _CACHE['rows'], _CACHE['addr']


def toks_rom(a, b, names):
    import bisect
    allr, addr = _all_rows()
    i, j = bisect.bisect_left(addr, a), bisect.bisect_left(addr, b)
    rows = allr[i:j]
    lits = set()
    for x, op, args in rows:
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            t = ((x + 4) & ~3) + int(m.group(1))
            lits.update((t, t + 2))
    out = []
    for x, op, args in rows:
        if x in lits or not op:
            continue
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            t = ((x + 4) & ~3) + int(m.group(1))
            v = u32(t)
            n = names.get(v) or names.get(v & ~1)
            if n:
                out.append('g:' + n)
            elif v < 0x02000000 or v >= 0x0A000000:
                out.append('k:%d' % v)
            else:
                out.append('p')
        elif op == 'bl':
            m2 = re.match(r'0x([0-9a-f]+)', args)
            v = int(m2.group(1), 16) if m2 else 0
            n = names.get(v)
            out.append('c:' + n if n else 'c?:%x' % v)
        elif op in ('cmp', 'movs') and '#' in args:
            v = args.split('#')[1]
            if v not in ('0', '1'):
                out.append('i:' + v)
    return out


def obj_funcs(f):
    p = os.path.join(ROOT, 'build', OBJDIR, f + '.o')
    rel = {}
    for line in subprocess.run([BIN + 'objdump', '-r', '-j', '.text', p], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'([0-9a-f]{8}) (R_ARM_\S+)\s+(\S+)', line)
        if m:
            rel[int(m.group(1), 16)] = m.group(3)
    nm = []
    for line in subprocess.run([BIN + 'nm', '-n', '-S', p], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'([0-9a-f]{8}) ([0-9a-f]{8}) ([tT]) (\S+)', line)
        if m:
            nm.append((int(m.group(1), 16), int(m.group(2), 16), m.group(4)))
    subprocess.run([BIN + 'objcopy', '-O', 'binary', '-j', '.text', p, p + '.bin'])
    code = open(p + '.bin', 'rb').read()
    t = subprocess.run([BIN + 'objdump', '-d', '-M', 'force-thumb', p], capture_output=True, text=True).stdout
    rows = []
    for line in t.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{4}(?: [0-9a-f]{4})?)\s+(\S+)(?:\s+(.*))?$', line)
        if m:
            rows.append((int(m.group(1), 16), m.group(3).split('.')[0], (m.group(4) or '').split('@')[0].strip()))
    byf = {}
    for start, size, name in nm:
        fr = [r for r in rows if start <= r[0] < start + size]
        lits = set()
        for x, op, args in fr:
            m = re.search(r'\[pc, #(\d+)\]', args)
            if op.startswith('ldr') and m:
                tt = ((x + 4) & ~3) + int(m.group(1))
                lits.update((tt, tt + 2))
        toks = []
        for x, op, args in fr:
            if x in lits or not op:
                continue
            m = re.search(r'\[pc, #(\d+)\]', args)
            if op.startswith('ldr') and m:
                tt = ((x + 4) & ~3) + int(m.group(1))
                if tt in rel and not rel[tt].startswith('.'):
                    toks.append('g:' + rel[tt])
                elif tt + 4 <= len(code):
                    v = struct.unpack_from('<I', code, tt)[0]
                    toks.append('k:%d' % v if tt not in rel else 'p')
            elif op == 'bl':
                n = rel.get(x)
                if not n:
                    m3 = re.search(r'<(\w+)>', args)
                    n = m3.group(1) if m3 else '?'
                toks.append('c:' + n)
            elif op in ('cmp', 'movs') and '#' in args:
                v = args.split('#')[1]
                if v not in ('0', '1'):
                    toks.append('i:' + v)
        byf[name] = (size, toks)
    return byf


LDN = set(LD.values())


def norm_src(toks, objs, paired):
    out = []
    for t in toks:
        if t.startswith('c:'):
            n = t[2:]
            if n in objs and n not in paired:
                continue
            if n not in LDN and n not in objs:
                continue
        elif t.startswith('g:') and t[2:] not in LDN:
            out.append('p')
            continue
        out.append(t)
    return out


def norm_rom(toks):
    return [t for t in toks if not t.startswith('c?:')]


def sim(a, b):
    ca, cb = collections.Counter(a), collections.Counter(b)
    inter = sum((ca & cb).values())
    return 2 * inter / max(len(a) + len(b), 1)


def main():
    extra = [x for x in [0x93507cc, 0x93508b0, 0x9350a5e, 0x9350ac6, 0x9350fbe, 0x93510ce, 0x9351174, 0x93511d8, 0x9351292, 0x93513c0, 0x9351510]]
    starts = sorted(set([x for x in rom_funcs() if LO + 0x60000 <= x < LO + 0x100000] + extra))
    ends = {s: starts[i + 1] if i + 1 < len(starts) else s + 0x400 for i, s in enumerate(starts)}
    print('ROM functions', len(starts), hex(starts[0]), hex(starts[-1]))
    objs = {}
    for f in FILES:
        for name, v in obj_funcs(f).items():
            objs[name] = (f,) + v
    print('source functions', len(objs))
    names = dict(NAMES)
    H = hooks()
    seeds = {'AI_TrySwitchOrUseItem': 0x90c802c, 'GetMostSuitableMonToSwitchInto': 0x90d8230, 'BattleAI_DoAIProcessing': 0x90c6f3c,
             'BattleAI_HandleItemUseBeforeAISetup': 0x90c7988, 'AIScript_Negatives': 0x90c904c, 'AIScript_SemiSmart': 0x90d6998,
             'AIScript_Positives': 0x90d10d4, 'AIScript_Roaming': 0x90cfe04, 'AIScript_Safari': 0x90cfe5c, 'AIScript_FirstBattle': 0x90cfeac}
    paired = {}
    for n, a in seeds.items():
        names[a] = n
        paired[n] = a
    used = set(paired.values())
    for round_ in range(14):
        rt = {s: toks_rom(s, ends[s], names) for s in starts}
        nr = {s: norm_rom(t) for s, t in rt.items()}
        scored = []
        for n, (f, size, toks) in objs.items():
            if n in paired or len(toks) < 4:
                continue
            for s in starts:
                if s in used:
                    continue
                ln = ends[s] - s
                if not (size * 0.45 <= ln <= size * 2.2 + 40):
                    continue
                v = sim(norm_src(toks, objs, paired), nr[s])
                if v > 0.55:
                    scored.append((v, n, s))
        scored.sort(reverse=True)
        added = 0
        for v, n, s in scored:
            if n in paired or s in used:
                continue
            need = max(0.86 - round_ * 0.04, 0.55)
            if v < need:
                break
            paired[n] = s
            used.add(s)
            names[s] = n
            added += 1
        # paired functions name their unnamed callees
        for n, s in list(paired.items()):
            a = [t[2:] for t in objs.get(n, (0, 0, []))[2] if t.startswith('c:')] if n in objs else []
            b = [t for t in rt.get(s, []) if t.startswith('c')]
            if len(a) == len(b):
                for x, y in zip(a, b):
                    if y.startswith('c?:') and x != '?' and x in objs and x not in paired:
                        addr = int(y[3:], 16)
                        if addr in ends and addr not in used:
                            paired[x] = addr
                            used.add(addr)
                            names[addr] = x
                            added += 1
        print('round', round_, 'added', added, 'total', len(paired))
        if not added and round_ > 8:
            break
    json.dump({n: s for n, s in paired.items()}, open(os.path.join(ROOT, 'build/paired.json'), 'w'), indent=0)
    json.dump({str(k): v for k, v in names.items()}, open(os.path.join(ROOT, 'build/names.json'), 'w'))
    bigger = sorted(((objs[n][1], n) for n in objs if n not in paired), reverse=True)[:30]
    print('unpaired biggest', [(s, n) for s, n in bigger])
    un = [s for s in starts if s not in used]
    print('unnamed ROM functions', len(un), 'of', len(starts))


if __name__ == '__main__':
    main()
