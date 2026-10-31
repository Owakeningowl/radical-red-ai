from lab import *
L = Lab(); b = L.b
print({hex(f): b.call(0x806E6D0 | 1, f) & 1 for f in (0x1032, 0x1033, 0x1034, 0x1042, 0x86)})
print('turn', b.r8(0x2023BCE), 'switchesInARow', [b.r8(b.r32(NEWBS) + 469 + i) for i in range(4)])
L.quit()
