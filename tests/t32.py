# which Random2 call decides the coin in the "resists you" switch?
from lab import *
L = Lab(); b = L.b
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=250, spa=30, hp=300, maxhp=300, spe=50)
AIW = dict(moves=['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle'], hp=200, maxhp=300, atk=60, spa=60, spe=100)
wall = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=900, spd=900, spe=20, hp=300, atk=30, spa=30)
glass = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
L.bench(wall, glass)
L.side(1, **AIW); L.side(0, **FW)
A, C = 0x41C64E6D, 0x3039
def seq(s, n=60):
    o = []
    for _ in range(n):
        s = (s * A + C) & 0xFFFFFFFF
        o.append(s >> 16)
    return o
rows = []
nb = b.r32(NEWBS)
for _ in range(300):
    for i in range(2): b.w8(nb + 0x888 + i, 0xFF)
    s = random.getrandbits(32)
    b.think(s)
    end = b.r32(RNG2)
    steps = None
    x = s
    for k in range(0, 3000):
        if x == end: steps = k; break
        x = (x * A + C) & 0xFFFFFFFF
    rows.append((s, b.choice()[0] == 2, steps))
print('switched', sum(r[1] for r in rows), 'of', len(rows))
from collections import Counter
print('steps', Counter(r[2] for r in rows).most_common(8))
best = []
for k in range(40):
    for name, f in (('%4!=0', lambda v: v % 4 != 0), ('&1', lambda v: v & 1), ('&2', lambda v: v & 2)):
        n1 = c1 = n0 = c0 = 0
        for s, sw, _ in rows:
            v = seq(s, 45)[k]
            if f(v): n1 += 1; c1 += sw
            else: n0 += 1; c0 += sw
        if n1 and n0:
            best.append((abs(c1 / n1 - c0 / n0), k, name, round(c1 / n1, 2), round(c0 / n0, 2)))
for x in sorted(best, reverse=True)[:6]:
    print(x)
L.quit()
