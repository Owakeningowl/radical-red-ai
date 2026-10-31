from lab import *
import struct
L = Lab(); b = L.b
SN = 143
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=120, maxhp=300, spe=50)
def mon(**k):
    d = dict(species=SN, moves=['Earthquake', 'Pound', 'Scratch', 'Slash'], dfn=100, spd=100, spe=20, hp=300, atk=30, spa=30); d.update(k); return d
bs = b.r32(BS)
def calc(title, foe, *mons):
    L.side(1, moves=['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle'], hp=200, maxhp=300)
    L.side(0, **foe)
    L.bench(*mons)
    nb = b.r32(NEWBS)
    b.w8(bs + 92 + 1, 6)
    b.call(0x090c8ba4); b.call(0x090c8ed0)
    r = b.call(0x90d7168) & 255
    sc = []
    for off in (0x860, ):
        sc = [struct.unpack('<h', struct.pack('<H', b.r16(nb + off + 12 + 2 * i)))[0] for i in range(6)]
    fl = [b.r8(nb + 0x878 + 6 + i) for i in range(6)]
    print(title, 'best', r, 'scores', sc, 'flags', [hex(x) for x in fl]); sys.stdout.flush()
print('expected: fast KO survive 14+31+17?; resist 17; slow KO 31; dies slow 0; fast 14')
calc('A', dict(FW, atk=200), mon(spe=300, atk=300, dfn=900, spd=900), mon(dfn=900, spd=900), mon(atk=300, dfn=900, spd=900), mon(dfn=5, spd=5, hp=30), mon(spe=300, dfn=900, spd=900))
calc('B foe hits hard: fast mons survive 1 hit only', dict(FW, atk=400), mon(spe=300, atk=300), mon(atk=300), mon(spe=300), mon(), mon(dfn=5, spd=5, hp=30, spe=300))
calc('C fast dies but KOs; fast dies no KO; slow dies but KOs', dict(FW, atk=2000), mon(spe=300, atk=300), mon(spe=300), mon(atk=300), mon(), mon())
calc('D priority KO', dict(FW, atk=200), mon(moves=['Quick Attack', 'Pound', 'Scratch', 'Slash'], atk=900, dfn=900, spd=900), mon(moves=['Growl', 'Leer', 'Tail Whip', 'Sand Attack'], dfn=900, spd=900), mon(spe=300, atk=100, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=900, spd=900), mon(), mon())
L.quit()
