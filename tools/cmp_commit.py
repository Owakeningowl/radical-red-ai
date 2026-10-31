#!/usr/bin/env python3
"""How close is a CFRU commit to the ROM? cmp_commit.py SHA... : similarity of big AI functions."""
import difflib, json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrmatch as R
names = dict(R.LD)
names.update({int(k): v for k, v in json.load(open(os.path.join(R.ROOT, 'build/names.json'))).items()})
known = set(names.values())
TARGETS = [('ai_switching', 'ShouldSwitch', 0x90d824c, 0x90d9d78), ('ai_switching', 'CalcMostSuitableMonToSwitchInto', 0x90d7168, 0x90d7f1c),
           ('ai_negatives', 'AIScript_Negatives', 0x90c904c, 0x90cfe04), ('ai_positives', 'AIScript_Positives', 0x90d10d4, 0x90d6998)]


def clean_src(t):
    out = []
    for x in t:
        if x == 'p' or (x.startswith('g:') and x[2:] not in R.LDN) or (x.startswith('c:') and x[2:] not in known):
            continue
        out.append(x)
    return out


rom = {k[1]: [x for x in R.toks_rom(k[2], k[3], names) if x != 'p' and not x.startswith('c?:')] for k in TARGETS}
for sha in sys.argv[1:]:
    R.OBJDIR = os.path.join('..', 'at', sha, 'o')
    row = [sha[:9]]
    for f, func, a, b in TARGETS:
        try:
            o = R.obj_funcs(f)
            if func not in o:
                row.append(f'{func[:12]}:none')
                continue
            size, t = o[func]
            A = clean_src(t)
            row.append(f'{func[:10]}:{difflib.SequenceMatcher(None, A, rom[func], autojunk=False).ratio():.3f}({size})')
        except Exception as e:
            row.append(f'{func[:8]}:err')
    print(' '.join(row), flush=True)
