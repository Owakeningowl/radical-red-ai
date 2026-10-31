#!/usr/bin/env python3
"""rrview.py FILE FUNC [start end] : a compact reading view of a function from rr41_source"""
import re, sys, os
ROOT = os.path.expanduser('~/Downloads/radical-red-ai/rr41_source/')
f, func = sys.argv[1], sys.argv[2]
t = open(ROOT + f + '.c').read()
i = t.index(f'// ---- {func} ')
j = t.find('\n// ---- ', i + 10)
b = t[i:j if j > 0 else len(t)]
k = b.find('\n  \n')
if k > 0:
    b = b[k:]
out = []
for l in b.split('\n'):
    s = l.rstrip()
    if not s.strip() or s.strip() in ('{', '}'):
        continue
    if re.match(r'\s*/\* TARGET', s):
        continue
    ind = len(s) - len(s.lstrip())
    s = ' ' * (ind // 2) + s.strip()
    s = s.replace('(uint)', '').replace('(int)', '').replace('(u8)', '').replace('(u16)', '').replace('gBattleResources->ai->', 'ai.')
    s = re.sub(r'/\* GetBattlerSide or Random or VarGet \*/ stub\(0x5119', 'VarGet(0x5119', s)
    s = re.sub(r'/\* ([^*]*?) \*/ stub\(', r'\1?(', s)
    out.append(s[:118])
a = int(sys.argv[3]) if len(sys.argv) > 3 else 0
e = int(sys.argv[4]) if len(sys.argv) > 4 else len(out)
print(f'lines {len(out)}')
print('\n'.join(out[a:e]))
