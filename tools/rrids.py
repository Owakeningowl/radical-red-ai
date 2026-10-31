#!/usr/bin/env python3
"""Compare CFRU's id headers with the ROM's real tables. Writes build/ids.json and patches rr41/include/constants."""
import json, re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from rrtext import D, text
ROOT = os.path.expanduser('~/Downloads/radical-red-ai')
def norm(s): return re.sub(r'[^a-z0-9]', '', s.lower())
# moves: full names table, index 0 = move 1
FULL, ST = 0x10eeeed, 17
rom_moves = {}
for i in range(0, 1020):
    n = text(FULL + ST * i, ST)
    if not n or '~' in n: break
    rom_moves[i + 1] = n
print('rom move names', len(rom_moves))
hdr = open(f'{ROOT}/rr41/include/constants/moves.h').read()
defs = {}
for m in re.finditer(r'^#define (MOVE_\w+)\s+(0x[0-9A-Fa-f]+|\d+)\s*$', hdr, re.M):
    defs[m.group(1)] = int(m.group(2), 0)
byname = {}
for i, n in rom_moves.items():
    byname.setdefault(norm(n), i)
same = diff = miss = 0
moved = {}
missing = []
for d, v in defs.items():
    if d in ('MOVE_NONE', 'MOVE_NAME_LENGTH'):
        continue
    k = norm(d[5:])
    r = byname.get(k)
    if r is None:
        cands = [i for nn, i in byname.items() if nn and len(nn) >= 5 and (nn.startswith(k) or k.startswith(nn))]
        r = cands[0] if len(cands) == 1 else None
    if r is None:
        # same id with a different spelling?
        missing.append((d, v, rom_moves.get(v)))
        miss += 1
    elif r == v:
        same += 1
    else:
        diff += 1
        moved[d] = (v, r)
print('moves same', same, 'moved', diff, 'not matched', miss)
print(' first moved', list(moved.items())[:6], ' last', list(moved.items())[-3:])
print(' unmatched', [(a, b, c) for a, b, c in missing][:24])
# effects: CFRU table effect for each move vs ROM effect
tab = open(f'{ROOT}/cfru/src/Tables/battle_moves.c').read()
cf = {}
for m in re.finditer(r'\[(MOVE_\w+)\]\s*=\s*\{\s*\.effect\s*=\s*(EFFECT_\w+)', tab):
    cf[m.group(1)] = m.group(2)
MV = 0x11521D0
effs = {}
for d, e in cf.items():
    i = defs.get(d)
    if i is None: continue
    if d in moved: i = moved[d][1]
    effs.setdefault(e, {})
    r = D[MV + 12 * i]
    effs[e][r] = effs[e].get(r, 0) + 1
hdr2 = open(f'{ROOT}/rr41/include/constants/battle_move_effects.h').read()
edefs = {m.group(1): int(m.group(2)) for m in re.finditer(r'#define (EFFECT_\w+) (\d+)', hdr2)}
emap, conflict = {}, []
for e, c in effs.items():
    best = max(c, key=c.get)
    emap[e] = best
    if edefs.get(e) != best:
        conflict.append((e, edefs.get(e), best, sum(c.values())))
print('effects mapped', len(emap), 'differ from header', conflict[:40])
json.dump(dict(moved=moved, effects=emap, missing=missing), open(f'{ROOT}/build/ids.json', 'w'), indent=0)
