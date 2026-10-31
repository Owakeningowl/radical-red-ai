#!/usr/bin/env python3
"""Turn Ghidra's per-function output (build/decomp4) into the source tree rr41_source/.

    rrsrc.py            build the tree
    rrsrc.py cases      dump the move effect cases of the two scoring scripts to build/cases_*.json

Only names and comments are added here. The logic is what Ghidra read from the ROM."""
import bisect, collections, json, os, re, sys
sys.path.insert(0, os.path.dirname(__file__))
import rrv

ROOT = rrv.ROOT
IN = os.path.join(ROOT, 'build/decomp4')
OUT = os.path.join(ROOT, 'rr41_source')
gh = json.load(open(os.path.join(ROOT, 'build/gh.json')))
m = json.load(open(os.path.join(ROOT, 'build/map.json')))
ld = rrv.ld_names()
sf = rrv.src_funcs()
rows = rrv.rom_rows()
rf = rrv.rom_funcs(rows)
MOVES = json.load(open(os.path.join(ROOT, 'build/moves.json')))
ABIL = json.load(open(os.path.join(ROOT, 'build/abilities.json')))
TYPES = json.load(open(os.path.join(ROOT, 'build/types.json')))


def defs(path, pre):
    d = {}
    for line in open(os.path.join(ROOT, path), errors='ignore'):
        mt = re.match(r'#define (%s\w+)\s+(0x[0-9A-Fa-f]+|\d+)' % pre, line)
        if mt:
            d.setdefault(int(mt.group(2), 0), mt.group(1))
    return d


EFFECTS = defs('rr41/include/constants/battle_move_effects.h', 'EFFECT_')
ITEMEFF = defs('rr41/include/constants/hold_effects.h', 'ITEM_EFFECT_') if os.path.exists(os.path.join(ROOT, 'rr41/include/constants/hold_effects.h')) else {}
TYPENAMES = {0: 'Normal', 1: 'Fighting', 2: 'Flying', 3: 'Poison', 4: 'Ground', 5: 'Rock', 6: 'Bug', 7: 'Ghost', 8: 'Steel', 9: 'Mystery', 10: 'Fire', 11: 'Water', 12: 'Grass', 13: 'Electric', 14: 'Psychic', 15: 'Ice', 16: 'Dragon', 17: 'Dark', 18: 'Roostless', 19: 'Blank', 20: 'Fairy'}

# case labels: target address -> table indexes
CASE = collections.defaultdict(list)
for s in gh['switches']:
    for i, t in enumerate(s['targets']):
        CASE[(s['addr'], t)].append(i)
BYTARGET = collections.defaultdict(list)
for (a, t), v in CASE.items():
    BYTARGET[t].append((a, v))
BIGSWITCH = {s['addr'] for s in gh['switches'] if len(s['targets']) >= 240}
EFFOFF = {s['addr']: (1 if len(s['targets']) == 254 else 0) for s in gh['switches'] if len(s['targets']) >= 240}  # the 254 entry tables switch on moveEffect - 1

# struct offsets for gNewBS, the AI part only
AIS = next(f for f in TYPES['NewBattleStruct']['fields'] if f['name'] == 'ai')
AIF = TYPES[AIS['type'].replace('struct ', '')]['fields']
AIFIELDS = []
for f in AIF:
    if f['bits']:
        continue
    t = f['type']
    dims = [int(x) for x in re.findall(r'\[(\d+)\]', t)]
    base = {'u8': 1, 's8': 1, 'bool8': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4}.get(re.sub(r'\[.*', '', t), 4)
    size = base
    for d in dims:
        size *= d
    AIFIELDS.append((AIS['off'] + f['off'], size, f['name'], dims, base))
AIFIELDS.sort()
OFFS = [x[0] for x in AIFIELDS]


def field(off):
    i = bisect.bisect_right(OFFS, off) - 1
    if i >= 0 and off < AIFIELDS[i][0] + AIFIELDS[i][1]:
        o, size, name, dims, base = AIFIELDS[i]
        return 'ai.' + name + ('[+%d]' % (off - o) if off != o else '')
    return None


def thunk_targets(addr):
    """per stub, the functions this ROM function reaches through it"""
    res = collections.defaultdict(list)
    r = rf.get(addr)
    if not r:
        return res
    import rrv as R
    i0 = bisect.bisect_left(ADDRS, addr)
    j0 = bisect.bisect_left(ADDRS, r['end'])
    known = {}
    for x, op, args in rows[i0:j0]:
        if op.startswith('ldr') and '[pc' in args:
            t = ((x + 4) & ~3) + R.pc_off(args)
            try:
                v = R.u32(t)
            except Exception:
                continue
            d = R.regnum(args.split(',')[0])
            known[d] = v
        elif op == 'bl':
            mt = re.search(r'0x([0-9a-f]+)', args)
            if mt:
                t = int(mt.group(1), 16)
                if t in STUBS:
                    v = known.get(STUBS[t])
                    if v is not None:
                        res[t].append(v & ~1)
    return res


ADDRS = [r[0] for r in rows]
idx = {r[0]: i for i, r in enumerate(rows)}
STUBS = {t: rrv.regnum(rows[idx[t]][2]) for t in gh['thunks'] if t in idx}
INV = {a: n for n, a in m.items()}
INV.update({a: n for a, n in ld.items() if a >= 0x8000000})


EXTRA = {0x825e45c: 'gBitTable', 0x203e028: 'gTerrainType'}


def name_of(a):
    return INV.get(a) or INV.get(a & ~1)


RENAME = {
    0x90c904c: {'uVar29': 'bankDef_', 'uVar17': 'bankAtk_', 'pBVar23': 'move', 'uVar9': 'move', 'uVar25': 'moveEffect', 'iVar12': 'moveSplit', 'uVar13': 'moveTarget', 'uVar14': 'moveType',
                'bVar24': 'moveFlags', 'uVar10': 'moveAcc', 'pBVar26': 'partnerMove', 'moveDef': 'partnerMove', 'uVar27': 'partner', 'bankDef_00': 'partner', 'uStack_34': 'predictedMove', 'uVar8': 'predictedMove', 'auStack_1a': 'viabilityPtr'},
    0x90d10d4: {'uVar14': 'predictedMove', 'uVar3': 'style', 'uVar9': 'move', 'uStack_3c': 'move', 'uVar15': 'atkAbility', 'uVar26': 'defAbility', 'uVar17': 'moveType', 'iVar16': 'moveSplit', 'uVar13': 'bankAtk_', 'pBVar22': 'bankDef_', 'bVar5': 'moveEffect'},
}


def clean(text, addr):
    for a, b in RENAME.get(addr, {}).items():
        text = re.sub(r'\b%s\b' % a, b, text)
    text = re.sub(r'\(BattlePokemon \*\)(0x[0-9a-f]+|\d+)\b', r'\1', text)
    text = re.sub(r'\(int\)move\b', 'move', text)
    text = re.sub(r'\(uint\)move\b', 'move', text)
    # noise
    text = re.sub(r'/\* WARNING: (Inlined function|Globals starting|Unknown calling|Type propagation|Possible PIC|Switch is manually|Could not inline|Instruction at|Removing unreachable|Heritage)[^*]*\*/\n?', '', text)
    text = re.sub(r'^\s*\n(?=\s*\n)', '', text, flags=re.M)
    # calls through a constant pointer
    text = re.sub(r'\(\*\(code \*\)&([A-Za-z_]\w*)\)', r'\1', text)

    def unk(mo):
        a = int(mo.group(1), 16)
        return name_of(a) or mo.group(0)
    text = re.sub(r'\(\*\(code \*\)&UNK_([0-9a-f]+)\)', unk, text)
    text = re.sub(r'\b_g([A-Z]\w*)', r'g\1', text)
    text = re.sub(r'\b_?UNK_([0-9a-f]+)', lambda k: name_of(int(k.group(1), 16)) or EXTRA.get(int(k.group(1), 16)) or k.group(0), text)
    # marks left at stub calls. A deeply indented mark sits right before a call that stayed a stub.
    pending = []

    def mark(mo):
        if mo.group(2):
            if len(mo.group(1)) >= 32:
                pending.append(mo.group(2))
            return ''
        tok = mo.group(0)
        if tok in (';', '{', '}'):
            pending.clear()
            return tok
        if pending:
            return pending.pop(0) + '('
        return tok
    text = re.sub(r'^([ \t]*)/\* TARGET (\w+) \*/[ \t]*\n|\bstub_[0-9a-f]+\(|[;{}]', mark, text, flags=re.M)
    # stubs that could not be inlined
    tt = thunk_targets(addr)

    def st(mo):
        t = int(mo.group(1), 16)
        c = collections.Counter(tt.get(t, []))
        names = [name_of(a) or hex(a) for a, _ in c.most_common()]
        if len(names) == 1:
            return names[0] + '('
        if names:
            return f"/* {' or '.join(names[:3])} */ stub("
        return mo.group(0)
    text = re.sub(r'\bstub_([0-9a-f]+)\(', st, text)
    # switch tables
    text = re.sub(r'switch\((.*?) & 0xf+e\) \{', r'switch(\1) {', text)
    text = re.sub(r'switch\((.*?) & 0xfe\) \{', r'switch(\1) {', text)

    def case(mo):
        t = int(mo.group(2), 16)
        hits = BYTARGET.get(t)
        if not hits:
            return mo.group(0)
        out = []
        for a, ids in hits:
            big = a in BIGSWITCH
            for i in ids:
                if big:
                    out.append(f"case {i}: /* {EFFECTS.get(i + EFFOFF[a], '?')} */")
                else:
                    out.append(f'case {i}:')
        ind = mo.group(1)
        return ind + ('\n' + ind).join(out)
    text = re.sub(r'^(\s*)case (0x[0-9a-f]+):', case, text, flags=re.M)
    text = re.sub(r'override_jmp_([0-9a-f]+)_case_(\d+)', lambda k: f'sw_{k.group(1)[-5:]}_{k.group(2)}', text)
    # gNewBS offsets into field names
    text = re.sub(r'\bgNewBS \+ (0x[0-9a-f]+)', lambda k: ('gNewBS->' + field(int(k.group(1), 16))) if field(int(k.group(1), 16)) else k.group(0), text)
    lines = []
    for ln in text.split('\n'):
        if lines and ln.strip().startswith('case ') and ln.strip() in [x.strip() for x in lines[-6:]]:
            continue
        lines.append(ln)
    text = '\n'.join(lines)
    # the viability variable
    v = re.search(r'IncreaseViability\(\(s16 \*\)&(\w+),', text) or re.search(r'DecreaseViability\(\(s16 \*\)&(\w+),', text)
    if v:
        text = re.sub(r'\b%s\b' % v.group(1), 'viability', text)
    text = text.replace('(s16 *)&viability', '&viability')

    # constants worth a name
    def effect(mo):
        n = int(mo.group(2), 0)
        return f'{mo.group(1)}{mo.group(2)} /* {EFFECTS.get(n, "?")} */'
    text = re.sub(r'(MoveEffectInMoveset\()(0x[0-9a-f]+|\d+)', effect, text)
    text = re.sub(r'(\.effect [!=]= )(0x[0-9a-f]+|\d+)', effect, text)

    def move(mo):
        n = int(mo.group(2), 0)
        nm = MOVES.get(str(n), {}).get('name')
        return f'{mo.group(1)}{mo.group(2)} /* {nm} */' if nm else mo.group(0)
    text = re.sub(r'((?:MoveInMoveset|MoveInMovesetAndUsable|MoveEffectInMoveset_)\()(0x[0-9a-f]+|\d+)', move, text)

    def abil(mo):
        n = int(mo.group(2), 0)
        nm = ABIL.get(str(n))
        return f'{mo.group(1)}{mo.group(2)} /* {nm} */' if nm else mo.group(0)
    text = re.sub(r'((?:[aA]tkAbility|[dD]efAbility|[pP]artnerAbility|\.ability|->ability) [!=]= )(0x[0-9a-f]+|\d+)', abil, text)

    def typ(mo):
        n = int(mo.group(2), 0)
        return f'{mo.group(1)}{mo.group(2)} /* {TYPENAMES.get(n, "?")} */'
    text = re.sub(r'(\bmoveType [!=]= )(0x[0-9a-f]+|\d+)', typ, text)
    text = re.sub(r'(\b(?:move|predictedMove|partnerMove) [!=]= )(0x[0-9a-f]+|\d+)', move, text)
    text = re.sub(r'(IsOfType\(\w+,)(0x[0-9a-f]+|\d+)', typ, text)
    text = re.sub(r'(DamagingMoveTypeInMoveset\(\w+,)(0x[0-9a-f]+|\d+)', typ, text)
    return text


def main():
    index = [l.split('\t') for l in open(os.path.join(IN, 'index.tsv')).read().splitlines()]
    groups = collections.defaultdict(list)
    order = {}
    for a, name, size in index:
        addr = int(a, 16)
        f = sf[name]['file'] if name in sf else ('ai_other' if 0x90c3e00 <= addr < 0x90e2000 or addr >= 0x9350000 else 'called_from_ai')
        groups[f].append((addr, name))
    os.makedirs(OUT, exist_ok=True)
    stats = {}
    for f, items in groups.items():
        items.sort()
        out = [f'// {f}.c', '// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.', '']
        for addr, name in items:
            p = os.path.join(IN, re.sub(r'[^A-Za-z0-9_]', '_', name) + '.c')
            if not os.path.exists(p):
                continue
            t = open(p).read()
            t = t.split('\n', 1)[1] if t.startswith('// ROM') else t
            out.append(f'// ---- {name}  (ROM {addr:#x})')
            out.append(clean(t, addr).strip('\n'))
            out.append('')
        open(os.path.join(OUT, f + '.c'), 'w').write('\n'.join(out))
        stats[f] = (len(items), sum(1 for x in out for _ in x.split('\n')))
    print(stats)
    hand = json.load(open(os.path.join(ROOT, 'build/names_manual.json')))
    with open(os.path.join(OUT, 'FUNCTIONS.tsv'), 'w') as w:
        w.write('rom_address\tname\tfile\tname_source\n')
        for f, items in sorted(groups.items()):
            for addr, name in items:
                how = 'unnamed' if name.startswith(('sub_', 'FUN_')) else 'read by hand' if name in hand else 'vanilla symbol' if addr in ld else 'matched to public CFRU'
                w.write(f'{addr:#x}\t{name}\t{f}.c\t{how}\n')
    os.makedirs(os.path.join(OUT, 'include'), exist_ok=True)
    with open(os.path.join(OUT, 'include/rr41_ids.h'), 'w') as w:
        w.write('// IDs used in the ROM. Numbers in the .c files are these.\n\n// Move effects\n')
        for k, v in sorted(EFFECTS.items()):
            w.write(f'#define {v} {k}\n')
        w.write('\n// Moves, names from the ROM\n')
        for k, v in sorted(MOVES.items(), key=lambda kv: int(kv[0])):
            nm = re.sub(r'[^A-Z0-9]+', '_', v['name'].upper()).strip('_')
            if nm:
                w.write(f"#define MOVE_{nm} {int(k):#x}\n")
        w.write('\n// Abilities, names from the ROM\n')
        for k, v in sorted(ABIL.items(), key=lambda kv: int(kv[0])):
            nm = re.sub(r'[^A-Z0-9]+', '_', v.upper()).strip('_')
            if nm:
                w.write(f"#define ABILITY_{nm} {int(k):#x}\n")
        w.write('\n// Types\n')
        for k, v in TYPENAMES.items():
            w.write(f'#define TYPE_{v.upper()} {k}\n')
    txt = ''.join(open(os.path.join(OUT, f + '.c')).read() for f in groups)
    named = sum(1 for f, it in groups.items() if f != 'called_from_ai' for a, n in it if not n.startswith('sub_'))
    tot = sum(len(it) for f, it in groups.items() if f != 'called_from_ai')
    print('AI functions named', named, 'of', tot)
    print('left: stub', len(re.findall(r'\bstub_[0-9a-f]+\(', txt)), 'ambiguous stub', len(re.findall(r'\*/ stub\(', txt)), 'code*', len(re.findall(r'\(\*\(code \*\)', txt)), 'UNK', len(re.findall(r'UNK_', txt)), 'sub_ calls', len(re.findall(r'\bsub_[0-9a-f]+\(', txt)))


if __name__ == '__main__':
    main()
