#!/usr/bin/env python3
"""Prepare the ROM for Ghidra. Writes test/rr_gh.gba (analysis copy only) and build/gh.json.

GCC's Thumb switch helpers (__gnu_thumb1_case_*) take a table that sits right after the call, which a decompiler
can't follow. In the analysis copy each helper call becomes "mov pc, r0", and build/gh.json lists the real targets."""
import json, os, re, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrv

ROOT = rrv.ROOT
D = bytearray(rrv.D)
rows = rrv.rom_rows()
rf = rrv.rom_funcs(rows)
idx = {r[0]: i for i, r in enumerate(rows)}
ld = rrv.ld_names()
m = json.load(open(os.path.join(ROOT, 'build/map.json')))
OFF = 0x8000000


def h(a):
    return struct.unpack_from('<H', D, a - OFF)[0]


# classify the case helpers by what they read
helpers = {}
for x, op, args in rows:
    if op != 'bl':
        continue
    mt = re.search(r'0x([0-9a-f]+)', args)
    if not mt:
        continue
    t = int(mt.group(1), 16)
    if t >= 0x9001000 or t < 0x9000000 or t in helpers:
        continue
    i = idx.get(t)
    if i is None:
        continue
    code = rows[i:i + 14]
    if not (code[0][1] == 'push' and code[1][1] == 'mov' and code[1][2].replace(' ', '') == 'r1,lr'):
        continue
    ops = []
    for c in code:
        ops.append(c[1])
        if c[1] == 'bx' or (c[1] == 'mov' and c[2].startswith('pc')):
            break
    kind = 'uqi' if 'ldrb' in ops else 'sqi' if 'ldrsb' in ops else 'uhi' if 'ldrh' in ops else 'shi' if 'ldrsh' in ops else 'si' if 'ldr' in ops else None
    if kind:
        helpers[t] = kind
print('case helpers', {hex(k): v for k, v in helpers.items()})

switches = []
tables = []  # (start, end) of table bytes, kept out of code
for x, op, args in rows:
    if op != 'bl':
        continue
    mt = re.search(r'0x([0-9a-f]+)', args)
    if not mt or int(mt.group(1), 16) not in helpers:
        continue
    kind = helpers[int(mt.group(1), 16)]
    base = x + 4
    if kind == 'si':
        base = (base + 3) & ~3
    size = {'uqi': 1, 'sqi': 1, 'uhi': 2, 'shi': 2, 'si': 4}[kind]
    p = base
    targets = []
    lim = None
    while True:
        if lim is not None and p >= lim:
            break
        if kind == 'si':
            v = struct.unpack_from('<i', D, p - OFF)[0]
            t = base + v
        elif kind == 'uqi':
            t = base + 2 * D[p - OFF]
        elif kind == 'sqi':
            t = base + 2 * struct.unpack_from('<b', D, p - OFF)[0]
        elif kind == 'uhi':
            t = base + 2 * struct.unpack_from('<H', D, p - OFF)[0]
        else:
            t = base + 2 * struct.unpack_from('<h', D, p - OFF)[0]
        if not (x - 0x8000 < t < x + 0x8000):
            break
        targets.append(t)
        if t > base and (lim is None or t < lim):
            lim = t
        p += size
        if len(targets) > 400:
            break
    # the compare just before the helper gives the real table length; the rest is alignment padding
    i0 = idx[x]
    bound = None
    for back_ in range(1, 12):
        o2, a2 = rows[i0 - back_][1], rows[i0 - back_][2]
        if o2 == 'cmp' and '#' in a2:
            bound = int(a2.split('#')[1]) + 1
            break
    if bound and bound <= len(targets):
        targets = targets[:bound]
    while targets and targets[-1] == base:
        targets.pop()
    switches.append(dict(addr=x, kind=kind, targets=targets))
    tables.append((x + 4, p))
    # analysis copy: mov pc, r0 ; nop
    struct.pack_into('<HH', D, x - OFF, 0x4687, 0x46C0)
print('switches', len(switches), 'largest', sorted((len(s['targets']) for s in switches), reverse=True)[:6])

# function list: everything in the AI files plus what they call directly elsewhere
names = {a: n for n, a in m.items()}
names.update({a: n for a, n in ld.items() if a >= 0x8000000})
AI = lambda a: 0x90c3e00 <= a < 0x90e2000 or 0x9350000 <= a < 0x9352000
funcs = sorted(a for a in rf if AI(a))
external = set()
for a in funcs:
    for c in rf[a]['calls']:
        if c.startswith('@'):
            t = int(c[1:], 16)
            if not AI(t) and t in rf:
                external.add(t)
print('AI functions', len(funcs), 'called in other files', len(external))
all_f = sorted(set(funcs) | external)

# thunks: bl to a lone "bx rN"
thunks = set()
for x, op, args in rows:
    if op == 'bl':
        mt = re.search(r'0x([0-9a-f]+)', args)
        if mt:
            t = int(mt.group(1), 16)
            i = idx.get(t)
            if i is not None and rows[i][1] == 'bx' and rows[i][2] != 'lr':
                thunks.add(t)
# code ranges and long jumps, per function
code = []
longj = []
tabset = sorted(tables)
for a in all_f:
    b = rf[a]['end']
    import bisect
    addrs = [r[0] for r in rows]
    break
addrs = [r[0] for r in rows]
import bisect
for a in all_f:
    b = rf[a]['end']
    i, j = bisect.bisect_left(addrs, a), bisect.bisect_left(addrs, b)
    fr = rows[i:j]
    lits = rrv.literal_addrs(fr)
    sk = [t for t in tables if a <= t[0] < b]
    ranges = []
    cur = None
    for x, op, args in fr:
        bad = x in lits or any(s <= x < e for s, e in sk)
        if bad:
            if cur:
                ranges.append(cur)
                cur = None
            continue
        size = 4 if op == 'bl' else 2
        if cur and cur[1] == x:
            cur[1] = x + size
        else:
            if cur:
                ranges.append(cur)
            cur = [x, x + size]
        if op == 'bl':
            mt = re.search(r'0x([0-9a-f]+)', args)
            if mt and a < int(mt.group(1), 16) < b:  # a call to the entry itself is recursion
                longj.append(x)
    if cur:
        ranges.append(cur)
    code.append(dict(addr=a, end=b, ranges=ranges, name=names.get(a)))

# every call through a stub: which function it reaches, for a comment at the call
names2 = dict(names)
sites = []
for c in code:
    i, j = bisect.bisect_left(addrs, c['addr']), bisect.bisect_left(addrs, c['end'])
    known = {}
    for x, op, args in rows[i:j]:
        if op.startswith('ldr') and '[pc' in args:
            t = ((x + 4) & ~3) + rrv.pc_off(args)
            try:
                known[rrv.regnum(args.split(',')[0])] = rrv.u32(t)
            except Exception:
                pass
        elif op == 'bl':
            mt = re.search(r'0x([0-9a-f]+)', args)
            if mt and int(mt.group(1), 16) in thunks:
                r = rrv.regnum(rows[idx[int(mt.group(1), 16)]][2])
                v = known.get(r)
                if v is not None:
                    n = names2.get(v & ~1)
                    sites.append([x, n or ('sub_%x' % (v & ~1))])
labels = {hex(a): n for a, n in ld.items()}
for line in open(os.path.join(ROOT, 'cfru/include/new/ram_locs_battle.h')):
    mt = re.match(r'#define (\w+)\s+.*?(0x[0-9A-Fa-f]{7,8})\)?', line)
    if mt:
        labels.setdefault(hex(int(mt.group(2), 16)), mt.group(1))
out = dict(functions=code, thunks=sorted(thunks), switches=switches, longjumps=longj, labels=labels, sites=sites)
json.dump(out, open(os.path.join(ROOT, 'build/gh.json'), 'w'))
open(os.path.join(ROOT, 'test/rr_gh.gba'), 'wb').write(D)
print('functions', len(code), 'long jumps', len(longj), 'thunks', len(thunks), 'named', sum(1 for c in code if c['name']))
