from lab import *
L = Lab(); b = L.b
nb = b.r32(NEWBS)
def scan():
    out = []
    prev = None
    for off in range(0x3F0, 0x7C0, 4):
        v = b.r32(nb + off)
        c = 'F' if v == 0xFFFFFFFF else ('0' if v == 0 else 'x')
        if c != prev:
            out.append(f'{off:#x}:{c}')
            prev = c
    return out[:40]
print(scan())
b.call(0x090c8ed4); b.g.wait(2); b.g.sync()
print(scan())
L.quit()
