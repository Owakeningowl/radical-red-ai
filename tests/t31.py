from lab import *
L = Lab(); b = L.b
# look at Random2 live: consecutive values after seeding
for s in (1, 2, 12345, 987654321):
    b.w32(RNG2, s)
    v = [b.call(0x808322C) & 0xFFFF for _ in range(4)]
    print(hex(s), [hex(x) for x in v], 'state', hex(b.r32(RNG2)))
L.quit()
