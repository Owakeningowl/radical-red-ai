from lab import *
L = Lab('dbl.st'); b = L.b
print('type', hex(b.r32(TF)), 'count', b.r8(0x2023BCC), 'main', hex(b.r32(MAINF)), 'comm', [b.r8(COMM+i) for i in range(4)])
print('mons', [(b.r16(BM+88*i), b.r16(BM+88*i+40)) for i in range(4)], 'idx', [b.r8(IDX+2*i) for i in range(4)])
print('player', [(b.r16(PP+100*i+0x20), b.r16(PP+100*i+0x56)) for i in range(6)])
print('enemy', [(b.r16(EP+100*i+0x20), b.r16(EP+100*i+0x56)) for i in range(6)])
ai = b.r32(b.r32(RES)+20)
print('flags', hex(b.r32(ai+12)), 'score', [b.r8(ai+4+i) for i in range(4)])
L.quit()
