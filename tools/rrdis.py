#!/usr/bin/env python3
"""Annotated Radical Red disassembly: rrdis.py START END"""
import json, os, re, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from rr import *
from rrmatch import LD, dis_rom
names = dict(LD)
p = os.path.expanduser('~/Downloads/radical-red-ai/build/names.json')
if os.path.exists(p):
    names.update({int(k): v for k, v in json.load(open(p)).items()})


def nm(v):
    return names.get(v) or names.get(v & ~1)


def show(a, b):
    rows = dis_rom(a, b)
    lits = set()
    for x, op, args in rows:
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            t = ((x + 4) & ~3) + int(m.group(1))
            lits.update((t, t + 2))
    for x, op, args in rows:
        if x in lits or not op:
            continue
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            t = ((x + 4) & ~3) + int(m.group(1))
            v = u32(t)
            n = nm(v)
            args = f"{args.split(',')[0]}, ={v:#x}" + (f'  ; {n}' if n else '')
        elif op == 'bl':
            m2 = re.match(r'0x([0-9a-f]+)', args)
            if m2:
                v = int(m2.group(1), 16)
                n = nm(v)
                args = f'{v:#x}' + (f'  ; {n}' if n else '')
        print(f'{x:08x}  {op:6} {args}')


if __name__ == '__main__':
    show(int(sys.argv[1], 16), int(sys.argv[2], 16))
