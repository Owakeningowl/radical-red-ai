from lab import *
import struct
L = Lab(); b = L.b
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=1, maxhp=300, spe=50)
bs = b.r32(BS)
def calc(title):
    nb = b.r32(NEWBS)
    b.w8(bs + 92 + 1, 6)
    b.call(0x090c8ba4); b.call(0x090c8ed0)
    r = b.call(0x90d7168) & 255
    sc = [struct.unpack('<h', struct.pack('<H', b.r16(nb + 0x860 + 12 + 2 * i)))[0] for i in range(6)]
    fl = [b.r8(nb + 0x878 + 6 + i) for i in range(6)]
    print(title, 'best', r, sc, [hex(x) for x in fl]); sys.stdout.flush()
L.side(1, moves=['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle'], hp=200, maxhp=300)
L.side(0, **FW)
calc('real bench, foe hp1')
for i in range(1,6):
    p = EP + 100*i
    print(i, 'pp', [b.r8(p+0x34+k) for k in range(4)], 'moves', [b.r16(p+0x2c+2*k) for k in range(4)])
L.mon(1, moves=['Earthquake','Pound','Scratch','Slash'], hp=b.r16(EP+100+0x56), atk=300, dfn=100, spe=20, spa=30, spd=100)
calc('slot1 moves+stats poked')
print(hex(b.r32(EP+100+0x20)), b.r8(EP+100+0x54))
L.quit()
