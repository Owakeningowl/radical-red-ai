from lab import *
L = Lab(); b = L.b
for i in range(6):
    p = EP + 100 * i
    print(i, [b.r16(p + o) for o in (0x20, 0x22, 0x2C, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62)], b.r8(p + 0x54), hex(b.r32(p + 0x50)))
print('active idx', b.r8(IDX + 2), b.r8(IDX + 0), b.r8(IDX+1))
L.quit()
