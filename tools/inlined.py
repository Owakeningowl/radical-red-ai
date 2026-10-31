#!/usr/bin/env python3
"""Find each source function inside a big ROM function it was merged into, and print what differs."""
import difflib, json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrmatch as R
names = dict(R.LD)
names.update({int(k): v for k, v in json.load(open(os.path.join(R.ROOT, 'build/names.json'))).items()})
known = set(names.values())
# compare only things both sides can name, plus numbers
def clean(t):
    out = []
    for x in t:
        if x == 'p' or x.startswith('c?:') or (x.startswith('g:') and x[2:] not in R.LDN) or (x.startswith('c:') and x[2:] not in known):
            continue
        out.append(x)
    return out
def main():
    f, a, b = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
    funcs = sys.argv[4:]
    B = clean(R.toks_rom(a, b, names))
    objs = R.obj_funcs(f)
    for fn in funcs:
        A = clean(objs[fn][1])
        best = None
        L = len(A)
        for s in range(0, max(len(B) - L // 2, 1), max(L // 6, 1)):
            w = B[s:s + int(L * 1.5) + 6]
            r = difflib.SequenceMatcher(None, A, w, autojunk=False).ratio()
            if not best or r > best[0]:
                best = (r, s, w)
        sm = difflib.SequenceMatcher(None, A, best[2], autojunk=False)
        print(f'== {fn}: {len(A)} tokens, best {best[0]:.2f} at token {best[1]}')
        for tag, i, j, k, l in sm.get_opcodes():
            if tag != 'equal' and (j - i <= 8 and l - k <= 8):
                print('   src', A[i:j], ' rom', best[2][k:l])
main()
