# real AI: does it change its move when you switch back? call the ROM's own routine
from lab import *
L = Lab(); b = L.b
GCM = 0x02023DC4
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=300, maxhp=300, spe=50)
AIW = dict(moves=['Flamethrower', 'Thunderbolt', 'Ice Beam', 'Earthquake'], hp=300, maxhp=300, atk=300, spa=300, spe=100)
L.side(1, **AIW); L.side(0, **FW)
nb = b.r32(NEWBS)
bs = b.r32(BS)
def run(count, second, chosen=2, yawn=0, n=40):
    res = {}
    for _ in range(n):
        for i in range(2): b.w8(nb + 0x888 + i, 0xFF)
        b.w8(nb + 469, count)
        b.w8(nb + 477, second)
        b.w8(ACT + 0, chosen)
        b.w8(ACT + 1, 0)
        b.w32(0x2023DFC, yawn)
        b.w16(GCM + 2, 0xABC)
        b.w32(RNG, random.getrandbits(32))
        b.call(0x90c8ca4, 1, 0)
        v = b.r16(GCM + 2)
        k = 'kept' if v == 0xABC else 'repicked'
        res[k] = res.get(k, 0) + 1
    return res
idx = b.r8(IDX)
print('party index of your mon', idx, 'second prev now', b.r8(nb + 477))
print('count 0, not back to old mon   ', run(0, 0xFF))
print('count 0, back to old mon       ', run(0, idx))
print('count 8                        ', run(8, 0xFF))
print('count 9                        ', run(9, 0xFF))
print('count 12                       ', run(12, 0xFF))
print('count 16                       ', run(16, 0xFF))
print('back to old mon, you used a move', run(0, idx, chosen=0, n=10))
print('back to old mon, you are Yawned', run(0, idx, yawn=0x800, n=10))
L.quit()
