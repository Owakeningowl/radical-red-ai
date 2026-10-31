#!/usr/bin/env python3
"""Compare the ROM's scoring with the public code, one move effect at a time.

    rrscore.py positives|negatives [--calls]

For each effect it lists the score changes the ROM can make and the ones the public code can make, following goto
labels on both sides, and prints only the effects that differ."""
import json, os, re, sys

ROOT = os.path.expanduser('~/Downloads/radical-red-ai')
which = sys.argv[1]
ROMFILE = {'positives': 'ai_positives', 'negatives': 'ai_negatives'}[which]
FUNC = {'positives': 'AIScript_Positives', 'negatives': 'AIScript_Negatives'}[which]
SRC = os.path.join(ROOT, 'cfru/src/Battle_AI', ROMFILE + '.c')


def effects():
    d = {}
    for line in open(os.path.join(ROOT, 'rr41/include/constants/battle_move_effects.h')):
        m = re.match(r'#define (EFFECT_\w+) (\d+)', line)
        if m:
            d[m.group(1)] = int(m.group(2))
    return d


def rom_function():
    t = open(os.path.join(ROOT, 'rr41_source', ROMFILE + '.c')).read()
    i = t.index(f'// ---- {FUNC} ')
    j = t.find('\n// ---- ', i + 10)
    return t[i:j if j > 0 else len(t)]


STAT = {'STAT_STAGE_ATK': 1, 'STAT_STAGE_DEF': 2, 'STAT_STAGE_SPEED': 3, 'STAT_STAGE_SPATK': 4, 'STAT_STAGE_SPDEF': 5, 'STAT_STAGE_ACC': 6, 'STAT_STAGE_EVASION': 7, 'STAT_STAGE_MAX': 12}


def num(s):
    if s in STAT:
        return STAT[s]
    try:
        return int(s, 0)
    except ValueError:
        return s


def rom_events(block):
    ev = set()
    for m in re.finditer(r'IncreaseViability\s*\([^,;]*,\s*(\w+)\)', block):
        ev.add(f'+{num(m.group(1))}')
    for m in re.finditer(r'DecreaseViability\s*\([^,;]*,\s*(\w+)\)', block):
        ev.add(f'-{num(m.group(1))}')
    for m in re.finditer(r'IncreaseStatusViability\s*\(&viability,\w+,(\w+),', block):
        ev.add(f'S{num(m.group(1))}')
    for m in re.finditer(r'IncreaseStatViability\s*\(&viability,\w+,(\w+),[^;]*?,(\w+),(\w+)\)', block):
        ev.add(f'B{num(m.group(1))}/s{num(m.group(2))}/l{num(m.group(3))}')
    for m in re.finditer(r'\b(Increase[A-Z]\w*Viability\w*|IncreaseViabilityFor\w+)\s*\(', block):
        n = m.group(1)
        if n not in ('IncreaseViability', 'IncreaseStatusViability', 'IncreaseStatViability'):
            ev.add(n)
    return ev


def src_events(block):
    ev = set()
    for m in re.finditer(r'INCREASE_VIABILITY\((\w+)\)', block):
        ev.add(f'+{num(m.group(1))}')
    for m in re.finditer(r'DECREASE_VIABILITY\((\w+)\)', block):
        ev.add(f'-{num(m.group(1))}')
    for m in re.finditer(r'INCREASE_STATUS_VIABILITY\((\w+)\)', block):
        ev.add(f'S{num(m.group(1))}')
    for m in re.finditer(r'INCREASE_STAT_VIABILITY\((\w+),\s*(\w+),\s*(\w+)\)', block):
        ev.add(f'B{num(m.group(3))}/s{num(m.group(1))}/l{num(m.group(2))}')
    for m in re.finditer(r'\b(Increase[A-Z]\w*Viability\w*|IncreaseViabilityFor\w+)\s*\(', block):
        ev.add(m.group(1))
    return ev


NOISE = {'GetBattlerSide','VarGet','FlagGet','GetMonData','CheckTableForMove','CheckTableForMoveEffect','GetBattlerPosition','Memset','GetBaseMoveTarget','ABILITY','GetHealthPercentage','IsOfType','CalcMoveSplit'}


def names(block):
    return set(re.findall(r'\b([A-Z][a-z]\w+)\s*\(', block)) - NOISE - {'IncreaseViability', 'DecreaseViability', 'IncreaseStatusViability', 'IncreaseStatViability', 'GetBankAbility', 'Random', 'MathMin', 'MathMax'}


def split_cases(text, case_re):
    """list of (ids, body)"""
    pos = [(m.start(), m.end(), m.group(1)) for m in re.finditer(case_re, text)]
    out = []
    i = 0
    while i < len(pos):
        ids = [pos[i][2]]
        j = i
        while j + 1 < len(pos) and not text[pos[j][1]:pos[j + 1][0]].strip():
            j += 1
            ids.append(pos[j][2])
        end = pos[j + 1][0] if j + 1 < len(pos) else len(text)
        out.append((ids, text[pos[j][1]:end]))
        i = j + 1
    return out


def closure(body, labels, depth=0, seen=None):
    seen = seen if seen is not None else set()
    txt = body
    if depth < 4:
        for g in re.findall(r'goto (\w+);', body):
            if g in labels and g not in seen:
                seen.add(g)
                txt += '\n' + closure(labels[g], labels, depth + 1, seen)
    return txt


def label_map(text):
    labels = {}
    for m in re.finditer(r'^\s*(\w+):\s*;?\s*$', text, re.M):
        name = m.group(1)
        if name in ('default',):
            continue
        rest = text[m.end():]
        k = re.search(r'^\s*case [\w]+:', rest, re.M)
        labels[name] = rest[:k.start()] if k else rest[:4000]
    return labels


# ROM
E_ALL = effects()
rom = rom_function()
sw = re.search(r'/\* EFFECT_', rom).start()
rom2 = rom[rom.rfind('switch', 0, sw):]
rlab = label_map(rom)
rcases = split_cases(rom2, r'case \d+: /\* (EFFECT_\w+) \*/')
R = {}
for ids, body in rcases:
    full = closure(body, rlab)
    for i in ids:
        if i not in E_ALL:
            continue
        k = E_ALL[i]
        if k in R:
            R[k] = (R[k][0] | rom_events(full), R[k][1] | names(full), R[k][2] + '\n/* next copy */\n' + body)
        else:
            R[k] = (rom_events(full), names(full), body)
# public source
src = open(SRC).read()
fn = src[src.index(f'u8 {FUNC}('):]
end = fn.find('\nu8 AIScript_', 10)
fn = fn[:end if end > 0 else len(fn)]
E = effects()
i0 = fn.index('switch (moveEffect)') if 'switch (moveEffect)' in fn else 0
main = fn[i0:]
slab = label_map(main)
scases = split_cases(main, r'\bcase (EFFECT_\w+):')
S = {}
for ids, body in scases:
    full = closure(body, slab)
    for n in ids:
        if n in E:
            S[E[n]] = (src_events(full), names(full), n)
same = diff = 0
callmode = '--calls' in sys.argv
out = []
for i in sorted(set(R) | set(S)):
    r = R.get(i)
    s = S.get(i)
    nm = s[2] if s else [k for k, v in E.items() if v == i][0] if i in E.values() else str(i)
    if not r or not s:
        continue
    a, b = {x for x in r[0] if 'uVar' not in x and 'bVar' not in x}, {x for x in s[0] if '/si' not in x}
    if which == 'negatives':
        a, b = a - {'-10', '-15', '-100'}, b - {'-10', '-15', '-100'}
    if a == b and (not callmode or r[1] == s[1]):
        same += 1
        continue
    diff += 1
    line = f'{i} {nm}: ROM only {sorted(map(str, a - b))}  public only {sorted(map(str, b - a))}'
    if callmode:
        line += f'  calls ROM+ {sorted(r[1] - s[1])[:6]} pub+ {sorted(s[1] - r[1])[:6]}'
    out.append(line)
print(f'{which}: effects in ROM {len(R)}, in public {len(S)}, same {same}, different {diff}')
if '--quiet' not in sys.argv:
    print('\n'.join(out))
if '--show' in sys.argv:
    for name in sys.argv[sys.argv.index('--show') + 1:]:
        i = E[name]
        print(f'===== {name} ({i})')
        body = R[i][2].split('/* next copy */')
        body = max(body, key=len)
        body = re.sub(r'^\s*/\* TARGET.*$', '', body, flags=re.M)
        body = re.sub(r'\n\s*\n', '\n', body)
        print(body[:int(os.environ.get('N', '1800'))])
