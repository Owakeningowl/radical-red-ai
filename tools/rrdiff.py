#!/usr/bin/env python3
"""Ordered compare of one source function with its ROM version. rrdiff.py FILE FUNC ROM_START ROM_END [--ni]
Prints only what differs: calls to known functions, known globals and small constants."""
import difflib, json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrmatch as R
from rr import *


def load(ni):
    names = dict(R.LD)
    p = os.path.join(R.ROOT, 'build/names.json')
    if os.path.exists(p):
        names.update({int(k): v for k, v in json.load(open(p)).items()})
    return names


def side_src(f, func, ni):
    if ni:
        return R.obj_funcs(f)[func]
    s = open(os.path.join(R.ROOT, 'tools/rrmatch.py')).read()
    # compiled with inlining: same reader, other folder
    import importlib
    old = R.obj_funcs.__code__
    import re, subprocess
    p = os.path.join(R.ROOT, 'build', f + '.o')
    os.makedirs(os.path.join(R.ROOT, 'build/ni_tmp'), exist_ok=True)
    return None


def main():
    f, func, a, b = sys.argv[1], sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4], 16)
    if '--inl' in sys.argv:
        R.OBJDIR = '.'
    names = load(True)
    size, toks = R.obj_funcs(f)[func]
    r = R.toks_rom(a, b, names)
    keep = lambda t: not t.startswith('p') and not t.startswith('c?:')
    A = []
    for t in toks:
        if t == 'p':
            continue
        if t.startswith('g:') and t[2:] not in R.LDN:
            continue
        if t.startswith('c:') and t[2:] not in set(names.values()):
            continue
        A.append(t)
    B = [t for t in r if keep(t)]
    sm = difflib.SequenceMatcher(None, A, B, autojunk=False)
    print(f'{func}: source {size} bytes {len(A)} tokens, ROM {b - a} bytes {len(B)} tokens, similarity {sm.ratio():.3f}')
    for tag, i, j, k, l in sm.get_opcodes():
        if tag != 'equal':
            print('  src', A[i:j][:24], '\n  rom', B[k:l][:24])


if __name__ == '__main__':
    main()
