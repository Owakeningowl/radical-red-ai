"""Shared helpers for the Radical Red ROM."""
import os, re, struct, subprocess
ROM = os.path.expanduser('~/Downloads/Radicalred.gba')
rom = open(ROM, 'rb').read()
BIN = '/opt/devkitpro/devkitARM/bin/arm-none-eabi-'
CFRU = os.path.expanduser('~/Downloads/radical-red-ai/cfru')


def u32(a):
    return struct.unpack_from('<I', rom, a & 0x1FFFFFF)[0]


def u16(a):
    return struct.unpack_from('<H', rom, a & 0x1FFFFFF)[0]


def hook_target(addr):
    """CFRU hook kinds: a small ldr/bx stub at the vanilla address. Returns the pointer it jumps to."""
    a = addr & 0x1FFFFFE
    for o in range(a, a + 16, 2):
        w = u16(o)
        if (w & 0xF800) == 0x4800:  # ldr rX,[pc,#n]
            lit = ((o + 4) & ~3) + (w & 0xFF) * 4
            v = u32(lit)
            if 0x08000000 <= v < 0x0A000000:
                return v
    return None


def hooks():
    out = {}
    for line in open(os.path.join(CFRU, 'hooks')):
        m = re.match(r'(\w+)\s+([0-9A-Fa-f]{7,8})\s+(\d)', line)
        if m:
            out[m.group(1)] = (int(m.group(2), 16), int(m.group(3)))
    return out
