from lab import *
L = Lab('dbl.st'); b = L.b
GCM = 0x02023DC4
def clr():
    nb = b.r32(NEWBS)
    for i in range(4): b.w8(nb + 0x888 + i, 0xFF)
BIGN=None
PC=[None]
def think(n):
    res = {}; bs = b.r32(BS)
    for _ in range(n):
        clr()
        for q in range(4): b.w16(GCM + 2 * q, 0)
        if PC[0]:
            b.w16(GCM+6,ID[PC[0][0]]); b.w8(b.r32(BS)+12+3,PC[0][1])
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

SP=['Heat Wave','Thunderbolt','Psychic','Dark Pulse']
HW=[('Heat Wave',0),('Thunderbolt',0)]
run('D1 spread 1/3+ on both vs single KO on L',dict(moves=SP,spa=400),dict(hp=130),{},n=60,moves=HW)
run('D2 spread 1/4 to 1/3 on both vs single',dict(moves=SP,spa=320),{},{},n=60,moves=HW)
run('D3 spread under 1/4 on both vs single',dict(moves=SP,spa=200),{},{},n=60,moves=HW)
run('D4 spread 1/3+ on both, no KOs',dict(moves=SP,spa=400),{},{},n=60,moves=HW)
EQ=['Earthquake','Thunderbolt','Psychic','Dark Pulse']
run('D5 Earthquake hits healthy partner',dict(moves=EQ,atk=300,spa=300),{},{},n=60)
PART.update(t1=2,t2=2)
run('D6 Earthquake, Flying partner',dict(moves=EQ,atk=300,spa=300),{},{},n=60)
PART.update(t1=0,t2=0)
PART_STRONG=dict(PART,spa=900)
PART.update(spa=900)
PC[0]=('Thunderbolt',0)
run('D7 partner already KOing L with its move',dict(moves=ATK,spa=120),dict(hp=100),{},n=60)
PC[0]=None; PART.update(spa=10)
run('D7b same with no partner move',dict(moves=ATK,spa=120),dict(hp=100),{},n=60)
HB=['Hyper Beam','Pound','Scratch','Slash']
run('D8 both KOable, only R can KO AI',dict(moves=ATK,spa=400,hp=60,maxhp=60),dict(hp=40),dict(hp=40,moves=HB,atk=400),n=60)
run('D9 both KOable, both can KO AI',dict(moves=ATK,spa=400,hp=60,maxhp=60),dict(hp=40,moves=HB,atk=400),dict(hp=40,moves=HB,atk=400),n=100)
run('D10 Phazer style, super effective KOs L only',dict(moves=['Roar','Thunderbolt','Toxic','Growl'],spa=120),dict(SE,hp=68,maxhp=68),dict(hp=68,maxhp=68),n=100)
print('--- doubles switching')
def dmon(i,**k):
    L.mon(i,**k)
def benches(*ms):
    for i in range(2,6):
        if i-2<len(ms): dmon(i,**ms[i-2])
        else: b.w16(EP+100*i+0x56,0)
F4=['Flamethrower','Psychic','Dark Pulse','Thunderbolt']
NOTH=dict(species=143,moves=F4,hp=60,maxhp=60,spe=5,dfn=5,spd=5,atk=5,spa=5)
RES=dict(species=143,moves=F4,hp=500,maxhp=500,spe=5,dfn=999,spd=999,atk=5,spa=5)
benches(NOTH)
def sw(t,ai,left,right,n=60):
    setup(ai,left,right); r=think(n); s=r.get('SWITCH',0); print(t,'switch',s,'of',n); sys.stdout.flush()
sw('S1 weak vs both, useless back mon',dict(moves=F4,spa=30),dict(spa=30),dict(spa=30))
sw('S2 weak vs L only, strong on R',dict(moves=F4,spa=120),dict(hp=300),dict(hp=40,maxhp=300))
sw('S3 foe can KO AI, AI strong, useless back mon',dict(moves=F4,spa=300,hp=60,maxhp=60),dict(moves=HB,atk=400),{})
benches(RES)
sw('S4 foe can KO AI, AI strong, resist back mon',dict(moves=F4,spa=300,hp=60,maxhp=60),dict(moves=HB,atk=400),{})
sw('S5 foe 2HKOs AI, AI strong, resist back mon',dict(moves=F4,spa=300),dict(spa=500,moves=F4),{})
print('--- doubles who comes in')
A=dict(species=143,moves=F4,hp=100,maxhp=100,spe=100,dfn=50,spd=100,atk=5,spa=999)
D=dict(species=143,moves=F4,hp=500,maxhp=500,spe=300,dfn=999,spd=999,atk=5,spa=30)
benches(A,D)
def who(t,ai,left,right,n=30):
    setup(ai,left,right); res={}
    bs=b.r32(BS)
    for _ in range(n):
        r=think(1)
        if 'SWITCH' in r:
            k=b.r8(bs+146+1); res[k]=res.get(k,0)+1
    print(t,res); sys.stdout.flush()
who('W1 idx2=KO L+faster than L, idx3=faster+resists both',dict(moves=F4,spa=30),dict(hp=100,maxhp=100,spa=300,moves=F4,spe=50),dict(hp=900,maxhp=900,spa=300,moves=F4,spe=200,spd=100))
print('DONE')
L.quit()
