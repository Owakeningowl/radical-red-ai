#!/usr/bin/env python3
"""Read struct layouts from debug info into build/types.json, for Ghidra."""
import json, re, subprocess
BIN = '/opt/devkitpro/devkitARM/bin/arm-none-eabi-'
t = subprocess.run([BIN + 'objdump', '--dwarf=info', 'rr41/o/types.o'], capture_output=True, text=True).stdout
dies = {}
stack = []
cur = None
for line in t.splitlines():
    m = re.match(r'\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: (\d+)(?: \((DW_TAG_\w+)\))?', line)
    if m:
        depth, off, num, tag = int(m.group(1)), int(m.group(2), 16), m.group(3), m.group(4)
        del stack[depth:]
        if num == '0':
            cur = None
            continue
        cur = dict(tag=tag, off=off, kids=[], parent=stack[-1] if stack else None)
        dies[off] = cur
        if stack:
            dies[stack[-1]]['kids'].append(off)
        stack.append(off)
        continue
    m = re.match(r'\s*<[0-9a-f]+>\s+(DW_AT_\w+)\s*:\s*(.*)$', line)
    if m and cur is not None:
        v = m.group(2).strip()
        cur[m.group(1)[6:]] = v.split(': ')[-1].strip() if m.group(1) == 'DW_AT_name' else v
def ref(v):
    m = re.search(r'<0x([0-9a-f]+)>', v or '')
    return int(m.group(1), 16) if m else None
def num(v):
    m = re.match(r'(\d+)', v or '')
    return int(m.group(1)) if m else 0
def tname(off, seen=()):
    if off is None:
        return 'void'
    d = dies[off]
    tag = d['tag']
    if tag == 'DW_TAG_base_type':
        size = num(d.get('byte_size'))
        return {1: 'u8', 2: 'u16', 4: 'u32', 8: 'u64'}.get(size, 'u8')
    if tag == 'DW_TAG_typedef':
        n = d.get('name')
        if n in ('u8', 's8', 'u16', 's16', 'u32', 's32', 'bool8', 'bool16', 'bool32'):
            return n
        return tname(ref(d.get('type')))
    if tag in ('DW_TAG_const_type', 'DW_TAG_volatile_type'):
        return tname(ref(d.get('type')))
    if tag == 'DW_TAG_enumeration_type':
        return {1: 'u8', 2: 'u16', 4: 'u32'}.get(num(d.get('byte_size')), 'u32')
    if tag == 'DW_TAG_pointer_type':
        return tname(ref(d.get('type'))) + '*'
    if tag == 'DW_TAG_array_type':
        dims = []
        for k in d['kids']:
            ub = dies[k].get('upper_bound')
            dims.append(num(ub) + 1 if ub is not None else 0)
        return tname(ref(d.get('type'))) + ''.join(f'[{x}]' for x in dims)
    if tag in ('DW_TAG_structure_type', 'DW_TAG_union_type'):
        n = d.get('name')
        return ('struct ' + n) if n else f'struct anon_{off:x}'
    if tag == 'DW_TAG_subroutine_type':
        return 'void'
    return 'u8'
out = {}
for off, d in dies.items():
    if d['tag'] not in ('DW_TAG_structure_type', 'DW_TAG_union_type'):
        continue
    n = d.get('name') or f'anon_{off:x}'
    if n in out or 'byte_size' not in d:
        continue
    fields = []
    for k in d['kids']:
        f = dies[k]
        if f['tag'] != 'DW_TAG_member':
            continue
        fields.append(dict(name=f.get('name', f'pad_{k:x}'), off=num(f.get('data_member_location')), type=tname(ref(f.get('type'))),
                           bits=num(f.get('bit_size')) if 'bit_size' in f else 0, bitoff=num(f.get('bit_offset') or f.get('data_bit_offset'))))
    out[n] = dict(size=num(d['byte_size']), fields=fields, union=d['tag'] == 'DW_TAG_union_type')
json.dump(out, open('build/types.json', 'w'))
print(len(out), 'structs;', {k: out[k]['size'] for k in ('NewBattleStruct', 'BattleStruct', 'DisableStruct', 'AIScript', 'Pokemon', 'BattlePokemon', 'BattleMove', 'AI_ThinkingStruct') if k in out})
ns = out.get('NewBattleStruct')
if ns:
    aif = [f for f in ns['fields'] if f['name'] == 'ai']
    print('ai at', aif[0]['off'] if aif else None, aif[0]['type'] if aif else None)
    a = out[aif[0]['type'].replace('struct ', '')] if aif else None
    base = aif[0]['off'] if aif else 0
    for f in a['fields']:
        if f['name'] in ('fightingStyle', 'switchesInARow', 'secondPreviousMonIn', 'switchingCooldown', 'goodToPivot', 'monIdToSwitchIntoScores', 'monIdToSwitchIntoFlags', 'movePredictions', 'damageByMove', 'monMaxDamage', 'monDamageByMove'):
            print(' ', f['name'], base + f['off'], hex(base + f['off']), f['type'])

# RR's own layout: the AI part of NewBattleStruct sits 68 bytes earlier than in the public code, checked against
# goodToPivot, switchingCooldown, switchesInARow, secondPreviousMonIn, monIdToSwitchIntoFlags and fightingStyle in the ROM.
# Fields before it don't line up with the public header, so they stay unnamed.
ns = out['NewBattleStruct']
new = []
for f in ns['fields']:
    if f['off'] >= 512:
        f = dict(f, off=f['off'] - 68)
        new.append(f)
new.append(dict(name='calculatedAIPredictions_bit7', off=233, type='u8', bits=0, bitoff=0))
ns['fields'] = new
ns['size'] -= 68
with open('build/types.txt', 'w') as w:
    for n, d in out.items():
        w.write(f"S\t{n}\t{d['size']}\n")
        for f in d['fields']:
            if f['bits']:
                continue
            w.write(f"F\t{f['off']}\t{f['type']}\t{f['name']}\n")
print('types.txt written')
