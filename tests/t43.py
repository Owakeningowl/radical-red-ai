from lab import *
L = Lab('dbl.st'); b = L.b
GCM = 0x02023DC4
def clr():
    nb = b.r32(NEWBS)
    for i in range(4): b.w8(nb + 0x888 + i, 0xFF)
def think(n):
    res = {}; bs = b.r32(BS)
    for _ in range(n):
        clr()
        for q in range(4): b.w16(GCM + 2 * q, 0)
        b.call(0x090c8ba4)
        nb = b.r32(NEWBS); b.w8(nb + 233, b.r8(nb + 233) & 0x7F)
        b.w32(RNG2, random.getrandbits(32)); b.w32(RNG, random.getrandbits(32))
        b.w8(bs + 146 + 1, 6); b.w8(bs + 92 + 1, 6); b.w8(ACT + 1, 0xFF); b.w8(COMM + 1, 0)
        for _ in range(150):
            b.g.wait(2); b.g.sync()
            if b.r8(COMM + 1) >= 4: break
        if b.r8(ACT + 1) == 2:
            k = 'SWITCH'
        else:
            slot = b.r8(0x20233C4 + 0x200 + 2); t = b.r8(0x20233C4 + 0x200 + 3)
            k = MOV.get(str(b.r16(BM + 88 + 12 + 2 * slot)), {}).get('name', '?') + '>' + {0:'L',2:'R',3:'partner'}.get(t, str(t))
        res[k] = res.get(k, 0) + 1
    return dict(sorted(res.items()))
NORMAL, WATER, GRASS, GROUND = 0, 11, 12, 4
W = dict(moves=['Tackle','Pound','Scratch','Slash'], atk=10, spa=10, spe=50, dfn=100, spd=100, hp=300, maxhp=300, status1=0, t1=NORMAL, t2=NORMAL)
PART = dict(W, spe=40)
ATK = ['Thunderbolt','Flamethrower','Psychic','Dark Pulse']
def run(title, ai, left, right, n=48):
    L.side(1, **dict(dict(hp=300, maxhp=300, spe=100, atk=100, dfn=100, spd=100, t1=14, t2=14, status1=0), **ai))
    L.side(0, **dict(W, **left)); L.side(2, **dict(W, **right)); L.side(3, **PART)
    print(title, '| style', L.style(1), '|', think(n)); sys.stdout.flush()

import json
ID={v['name']:int(k) for k,v in MOV.items() if isinstance(v,dict) and v.get('name')}
KO=0x90defc4
def setup(ai,left,right):
    L.side(1, **dict(dict(hp=300, maxhp=300, spe=100, atk=100, dfn=100, spd=100, t1=NORMAL, t2=NORMAL, status1=0), **ai))
    L.side(0, **dict(W, **left)); L.side(2, **dict(W, **right)); L.side(3, **PART)
def dmg(mv,atk,dfn):
    # smallest HP that survives, found by asking the ROM's own KO check
    base=BM+88*dfn+40
    keep=b.r16(base); lo,hi=1,999
    while lo<hi:
        m=(lo+hi)//2; b.w16(base,m); b.call(0x090c8ba4); b.call(0x090c8ed0,dfn)
        if b.call(KO,ID[mv],atk,dfn,1)&255: lo=m+1
        else: hi=m
    b.w16(base,keep); return lo-1
def run(title,ai,left,right,n=160,moves=None):
    setup(ai,left,right)
    r=think(n)
    print(title,'| style',b.r8(b.r32(NEWBS)+0x888+1),'|',r,'| dmg',moves and [dmg(m,1,d) for m,d in moves]); sys.stdout.flush()
ATK=['Thunderbolt','Flamethrower','Psychic','Dark Pulse']
ONE=['Thunderbolt']
TB=[('Thunderbolt',0),('Thunderbolt',2)]
SE=dict(t1=WATER,t2=WATER); RES=dict(t1=GRASS,t2=GRASS)

BIG=dict(hp=250,maxhp=300)
SPR=['Heat Wave','Thunderbolt','Psychic','Dark Pulse']
HWb=[('Heat Wave',0),('Heat Wave',2),('Thunderbolt',0),('Thunderbolt',2)]
P0=dict(moves=['Tackle','Pound','Scratch','Slash'],atk=10,spa=10,spe=40,hp=300,maxhp=300,t1=0,t2=0)
run('13 spread does 1/3+ to both vs single move KO on L',dict(moves=SPR,spa=140),dict(hp=70),dict(hp=300),n=60,moves=HWb)
run('14 spread weak (under 1/4) vs single move KO on L',dict(moves=SPR,spa=30),dict(hp=20),dict(hp=300),n=60,moves=HWb)
run('15 spread weak, no KO, single target strong',dict(moves=['Heat Wave','Thunderbolt','Hyper Beam','Dark Pulse'],spa=40),{},{},n=60,moves=HWb)
run('16 spread KOs both',dict(moves=SPR,spa=140),dict(hp=40),dict(hp=40),n=40,moves=HWb)
run('17 Earthquake, AI partner healthy, foes grounded',dict(moves=['Earthquake','Thunderbolt','Psychic','Dark Pulse'],atk=140,spa=140),{},{},n=60)
L.side(3,**dict(P0,t1=2,t2=2))
print('(partner now Flying)')
def run2(title,ai,left,right,n=60):
    L.side(1,**dict(dict(hp=300,maxhp=300,spe=100,atk=100,dfn=100,spd=100,t1=NORMAL,t2=NORMAL,status1=0),**ai))
    L.side(0,**dict(W,**left)); L.side(2,**dict(W,**right)); L.side(3,**dict(P0,t1=2,t2=2))
    print(title,'|',think(n)); sys.stdout.flush()
run2('18 same Earthquake with Flying partner',dict(moves=['Earthquake','Thunderbolt','Psychic','Dark Pulse'],atk=140,spa=140),{},{})
L.quit()
