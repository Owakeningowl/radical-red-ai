#!/usr/bin/env python3
"""List every FlagGet / VarGet in the AI code region with the constant it reads."""
import re, struct, subprocess
BIN = '/opt/devkitpro/devkitARM/bin/arm-none-eabi-'
ROM = 'test/rr.gba'
D = open(ROM, 'rb').read()
out = {}
for lo, hi in ((0x9060000, 0x90e2000), (0x9350000, 0x9352000)):
    t = subprocess.run([BIN + 'objdump', '-D', '-b', 'binary', '-m', 'arm', '-M', 'force-thumb', '--adjust-vma=0x8000000',
                        f'--start-address={lo:#x}', f'--stop-address={hi:#x}', ROM], capture_output=True, text=True).stdout.splitlines()
    rows = []
    for l in t:
        m = re.match(r'\s*([0-9a-f]+):\s+[0-9a-f ]+?\s+(\S+)\s*(.*)$', l)
        if m:
            rows.append((int(m.group(1), 16), m.group(2), m.group(3).split('@')[0].strip()))
    def lit(a, args):
        m = re.search(r'\[pc, #(\d+)\]', args)
        if not m: return None
        p = ((a + 4) & ~3) + int(m.group(1)) - 0x8000000
        return struct.unpack_from('<I', D, p)[0]
    for i, (a, op, args) in enumerate(rows):
        if op.startswith('ldr'):
            v = lit(a, args)
            if v in (0x806E6D1, 0x806E569, 0x806E6D0, 0x806E568):
                # look back for the constant in r0
                c = None
                for j in range(i - 1, max(i - 8, 0), -1):
                    a2, o2, x2 = rows[j]
                    if o2.startswith('ldr') and x2.startswith('r0,'):
                        c = lit(a2, x2); break
                    if o2 == 'movs' and x2.startswith('r0, #'):
                        c = int(x2.split('#')[1]); break
                out.setdefault(('Flag' if v & ~1 == 0x806E6D0 else 'Var', c), []).append(hex(a))
# only the Battle AI files
for k, v in sorted(out.items(), key=lambda x: str(x[0])):
    w = [a for a in v if 0x90c3c00 <= int(a, 16) < 0x90e2000 or int(a, 16) >= 0x9350000]
    if w:
        print(k[0], hex(k[1]) if k[1] is not None else '?', w[:8])
