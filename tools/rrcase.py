#!/usr/bin/env python3
"""Case by case compare of a big switch, source vs ROM.

    rrcase.py FILE FUNC ROM_START ROM_END ROM_TABLE COUNT [--all]

Each ROM case is matched to the source case with the most similar calls and constants, so shifted effect ids
do not matter. Prints only cases that differ, with the differing tokens."""
import difflib, json, os, re, struct, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrmatch as R
from rr import *

BIN = R.BIN


def load_names():
    names = dict(R.LD)
    p = os.path.join(R.ROOT, 'build/names.json')
    if os.path.exists(p):
        names.update({int(k): v for k, v in json.load(open(p)).items()})
    return names


def rom_table(tab, n):
    out = []
    for i in range(n):
        o = struct.unpack('<i', struct.pack('<I', u32(tab + 4 * i)))[0]
        out.append(tab + o)
    return out


def src_rows(f, func):
    p = os.path.join(R.ROOT, 'build', 'ni', f + '.o')
    rel = {}
    for line in subprocess.run([BIN + 'objdump', '-r', '-j', '.text', p], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'([0-9a-f]{8}) (R_ARM_\S+)\s+(\S+)', line)
        if m:
            rel[int(m.group(1), 16)] = m.group(3)
    start = size = None
    for line in subprocess.run([BIN + 'nm', '-n', '-S', p], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'([0-9a-f]{8}) ([0-9a-f]{8}) ([tT]) (\S+)', line)
        if m and m.group(4) == func:
            start, size = int(m.group(1), 16), int(m.group(2), 16)
    subprocess.run([BIN + 'objcopy', '-O', 'binary', '-j', '.text', p, p + '.bin'])
    code = open(p + '.bin', 'rb').read()
    t = subprocess.run([BIN + 'objdump', '-d', '-M', 'force-thumb', p], capture_output=True, text=True).stdout
    rows = []
    for line in t.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{4}(?: [0-9a-f]{4})?)\s+(\S+)(?:\s+(.*))?$', line)
        if m:
            x = int(m.group(1), 16)
            if start <= x < start + size:
                rows.append((x, m.group(3).split('.')[0], (m.group(4) or '').split('@')[0].strip()))
    lits = set()
    for x, op, args in rows:
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            tt = ((x + 4) & ~3) + int(m.group(1))
            lits.update((tt, tt + 2))
    toks = []
    table = None
    for x, op, args in rows:
        if x in lits:
            continue
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            tt = ((x + 4) & ~3) + int(m.group(1))
            if tt in rel and not rel[tt].startswith('.'):
                toks.append((x, 'g:' + rel[tt]))
            elif tt + 4 <= len(code):
                v = struct.unpack_from('<I', code, tt)[0]
                toks.append((x, 'k:%d' % v if tt not in rel else 'p'))
        elif op == 'bl':
            n = rel.get(x)
            if not n:
                m3 = re.search(r'<(\w+)>', args)
                n = m3.group(1) if m3 else '?'
            if n == '__gnu_thumb1_case_si' and table is None:
                table = (x + 4 + 3) & ~3
            toks.append((x, 'c:' + n))
        elif op in ('cmp', 'movs') and '#' in args:
            v = args.split('#')[1]
            if v not in ('0', '1'):
                toks.append((x, 'i:' + v))
    return start, size, code, toks, table


def rom_rows(a, b, names):
    allr, addr = R._all_rows()
    import bisect
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
                out.append((x, 'g:' + n))
            elif v < 0x02000000 or v >= 0x0A000000:
                out.append((x, 'k:%d' % v))
        elif op == 'bl':
            m2 = re.match(r'0x([0-9a-f]+)', args)
            v = int(m2.group(1), 16) if m2 else 0
            n = names.get(v)
            if n:
                out.append((x, 'c:' + n))
        elif op in ('cmp', 'movs') and '#' in args:
            v = args.split('#')[1]
            if v not in ('0', '1'):
                out.append((x, 'i:' + v))
    return out


def segs(toks, targets, end):
    ts = sorted(set(targets))
    out = {}
    import bisect
    for i, t in enumerate(ts):
        e = ts[i + 1] if i + 1 < len(ts) else end
        out[t] = [k for x, k in toks if t <= x < e]
    return out


def main():
    f, func, a, b, tab, n = sys.argv[1], sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4], 16), int(sys.argv[5], 16), int(sys.argv[6])
    names = load_names()
    known = set(names.values())
    start, size, code, st, stab = src_rows(f, func)
    # number of source cases: first offset points past the table, so table length is known
    first = min(struct.unpack_from('<i', code, stab + 4 * i)[0] for i in range(4))
    cnt = 0
    while cnt < 400:
        o = struct.unpack_from('<i', code, stab + 4 * cnt)[0]
        if not (0 < o < size):
            break
        cnt += 1
    ct = [stab + struct.unpack_from('<i', code, stab + 4 * i)[0] for i in range(cnt)]
    keep = lambda t: not (t.startswith('c:') and t[2:] not in known) and t != 'p' and not t.startswith('g:__')
    st = [(x, k) for x, k in st if keep(k)]
    ss = segs(st, ct, start + size)
    rt = rom_table(tab, n)
    rr = rom_rows(a, b, names)
    rs = segs(rr, rt, b)
    print('source cases', cnt, 'distinct', len(ss), '; ROM cases', n, 'distinct', len(rs))
    used = {}
    bad = 0
    for t, toks in sorted(rs.items()):
        best, bt = -1, None
        for s, stoks in ss.items():
            if not toks and not stoks:
                v = 1
            else:
                v = difflib.SequenceMatcher(None, toks, stoks, autojunk=False).ratio()
            if v > best:
                best, bt = v, s
        cases = [i for i, x in enumerate(rt) if x == t]
        if best >= (1.1 if '--all' in sys.argv else 0.999):
            continue
        bad += 1
        stoks = ss[bt]
        sm = difflib.SequenceMatcher(None, toks, stoks, autojunk=False)
        d = []
        for op, i1, i2, j1, j2 in sm.get_opcodes():
            if op != 'equal':
                d.append('ROM%s/SRC%s' % (toks[i1:i2], stoks[j1:j2]))
        srccase = [i for i, x in enumerate(ct) if x == bt]
        print('%x rom#%s src#%s sim %.2f len %d/%d' % (t, cases[:4], srccase[:4], best, len(toks), len(stoks)))
        for x in d[:6]:
            print('   ', x.replace("'", '')[:170])
    print('differing', bad, 'of', len(rs))


main()
