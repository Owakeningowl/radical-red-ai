#!/usr/bin/env python3
"""Dump abilities and base stats to build/ (read only)."""
import json, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from rrtext import D, text, CH
EN = {v: k for k, v in CH.items() if len(v) == 1 and k not in (0xFA, 0xFB)}
EN["'"] = 0xB4
def enc(s): return bytes(EN[c] for c in s) + b'\xff'
AB0 = 0x10e32d1 - 17
ab = {}
for i in range(0, 300):
    n = text(AB0 + i * 17, 17)
    if i and (not n or '~' in n): break
    ab[i] = n
print(len(ab), 'abilities', ab[1], ab[2], ab[10], ab[11], ab[30], ab[0x56])
pat = bytes([45, 49, 49, 45, 65, 65, 12, 3])
idx = [m.start() for m in re.finditer(re.escape(pat), D)]
print([hex(i) for i in idx])
BS = None
for i in idx:
    if D[i + 28:i + 28 + 6] == bytes([60, 62, 63, 60, 80, 80]):
        BS = i - 28
print('base stats', hex(BS))
# species names
nm = enc('Bulbasaur')
cand = []
for m in re.finditer(re.escape(nm), D):
    for st in (11, 12, 13, 14):
        if D[m.start() + st:m.start() + st + 8] == enc('Ivysaur'):
            cand.append((m.start(), st))
print(cand)
s0, st = cand[-1]
s0 -= st
sp = {}
for i in range(0, 1500):
    b = BS + i * 28
    n = text(s0 + i * st, st)
    sp[i] = dict(name=n, hp=D[b], atk=D[b + 1], dfn=D[b + 2], spe=D[b + 3], spa=D[b + 4], spd=D[b + 5], t1=D[b + 6], t2=D[b + 7], a1=D[b + 22], a2=D[b + 23], ah=D[b + 26])
json.dump(ab, open('build/abilities.json', 'w'))
json.dump(sp, open('build/species.json', 'w'))
for i in (143, 94, 134, 135, 136, 121, 80, 502, 765):
    x = sp[i]; print(i, x['name'], x['t1'], x['t2'], ab.get(x['a1']), ab.get(x['a2']), ab.get(x['ah']))
want = {'Water Absorb', 'Volt Absorb', 'Flash Fire', 'Natural Cure', 'Regenerator', 'Levitate', 'Lightning Rod', 'Sap Sipper', 'Wonder Guard'}
seen = {}
for i, x in sp.items():
    for k in ('a1', 'a2', 'ah'):
        a = ab.get(x[k])
        if a in want and i > 0 and i < 400:
            seen.setdefault(a, []).append((i, x['name'], k))
for a, v in seen.items(): print(a, [hex(0) if False else (i, n, k) for i, n, k in v[:4]])
print({a: i for i, a in ab.items() if a in want})
