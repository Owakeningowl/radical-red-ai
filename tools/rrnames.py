#!/usr/bin/env python3
"""Dump move names and effects from the ROM to build/moves.json"""
import json, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from rrtext import D, text, CH
EN = {v: k for k, v in CH.items() if len(v) == 1 and k not in (0xFA, 0xFB)}
EN["'"] = 0xB4
def enc(s): return bytes(EN[c] for c in s) + b'\xff'
p = enc('Pound'); q = enc('Karate Chop')
base = stride = None
for m in re.finditer(re.escape(p), D):
    for st in (13, 14, 15, 16, 17, 18, 20):
        if D[m.start() + st:m.start() + st + len(q)] == q:
            print('candidate', hex(m.start()), st)
            base, stride = m.start() - 0, st
print('names', hex(base), stride)
# entry 0 is "-"
start = base - stride
MV = 0x11521D0
out = {}
for i in range(0, 1100):
    n = text(start + i * stride, stride)
    if i and (not n or '~' in n): 
        break
    e = D[MV + i * 12 + 0], D[MV + i * 12 + 1], D[MV + i * 12 + 2], D[MV + i * 12 + 3], D[MV + i * 12 + 4]
    out[i] = dict(name=n, effect=e[0], power=e[1], type=e[2], acc=e[3], pp=e[4], prio=struct.unpack('b', D[MV + i * 12 + 7:MV + i * 12 + 8])[0], split=D[MV + i * 12 + 10])
print(len(out), 'moves')
json.dump(out, open('build/moves.json', 'w'), indent=0)
