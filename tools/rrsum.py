#!/usr/bin/env python3
"""Short listing for reading: only calls, comparisons, branches, named globals and constants. rrsum.py START END"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrmatch as R
from rr import *
names = dict(R.LD)
p = os.path.join(R.ROOT, 'build/names.json')
if os.path.exists(p):
    names.update({int(k): v for k, v in json.load(open(p)).items()})


def nm(v):
    return names.get(v) or names.get(v & ~1)


def main():
    a, b = int(sys.argv[1], 16), int(sys.argv[2], 16)
    rows = R.dis_rom(a, b)
    lits = set()
    for x, op, args in rows:
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            t = ((x + 4) & ~3) + int(m.group(1))
            lits.update((t, t + 2))
    targets = set()
    for x, op, args in rows:
        if x in lits:
            continue
        if op[:1] == 'b' and op not in ('bl', 'bx', 'bic'):
            m = re.match(r'0x([0-9a-f]+)', args)
            if m:
                targets.add(int(m.group(1), 16))
    out = []
    for x, op, args in rows:
        if x in lits or not op:
            continue
        lab = f'{x & 0xFFFFF:05x}' + (':' if x in targets else ' ')
        m = re.search(r'\[pc, #(\d+)\]', args)
        if op.startswith('ldr') and m:
            v = u32(((x + 4) & ~3) + int(m.group(1)))
            n = nm(v)
            out.append(f'{lab} ={n or hex(v)}')
        elif op == 'bl':
            m2 = re.match(r'0x([0-9a-f]+)', args)
            v = int(m2.group(1), 16) if m2 else 0
            out.append(f'{lab} CALL {nm(v) or hex(v)}')
        elif op == 'cmp':
            out.append(f'{lab} cmp {args}')
        elif op in ('ands', 'tst', 'orrs', 'lsrs', 'lsls') and op in ('ands', 'tst', 'orrs'):
            out.append(f'{lab} {op} {args}')
        elif op == 'movs' and '#' in args and not args.endswith('#0'):
            out.append(f'{lab} mov {args}')
        elif op in ('adds', 'subs') and args.count('#') and int(args.split('#')[1]) > 1:
            out.append(f'{lab} {op} {args}')
        elif op[:1] == 'b' and op not in ('bl', 'bx', 'bic'):
            out.append(f'{lab} {op} {args.split()[0][-5:] if args else ""}')
        elif op in ('strb', 'strh', 'str') and 'sp' not in args:
            out.append(f'{lab} {op} {args}')
        elif op.startswith('pop') or op == 'bx':
            out.append(f'{lab} RET')
    print('\n'.join(out))


if __name__ == '__main__':
    main()
