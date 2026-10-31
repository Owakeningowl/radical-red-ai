#!/usr/bin/env python3
"""rrcalls.py NAME : source calls and ROM calls side by side, with current names"""
import json, sys, os, difflib
sys.path.insert(0, os.path.dirname(__file__))
import rrv
sf = rrv.src_funcs(); rows = rrv.rom_rows(); rf = rrv.rom_funcs(rows)
m = json.load(open(os.path.join(rrv.ROOT, 'build/map.json')))
inv = {f'@{a:x}': n for n, a in m.items()}
for n in sys.argv[1:]:
    a = m[n]; r = rf[a]
    x = sf[n]['calls']; y = [inv.get(c, c) for c in r['calls']]
    print(f"== {n} {a:#x} rom size {r['end']-a} src size {sf[n]['size']}")
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, x, y, autojunk=False).get_opcodes():
        if op == 'equal':
            print('   =', ' '.join(x[i1:i2])[:150])
        else:
            print('   S', ' '.join(x[i1:i2])[:150]); print('   R', ' '.join(y[j1:j2])[:150])
