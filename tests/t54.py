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


F4=['Flamethrower','Psychic','Dark Pulse','Thunderbolt']
def benches(*ms):
    for i in range(2,6):
        if i-2<len(ms): L.mon(i,**ms[i-2])
        else: b.w16(EP+100*i+0x56,0)
r=dict(species=143,moves=F4,atk=5,spa=5,spe=5)
def backsd(fs):
    w=max(5,fs//2)
    return dict(nothing=dict(r,hp=60,maxhp=60,spd=5,dfn=5),faster=dict(r,hp=200,maxhp=200,spd=w,dfn=5,spe=300),walls=dict(r,hp=100,maxhp=100,spd=fs+1,dfn=31),resists=dict(r,hp=500,maxhp=500,spd=fs*3+5,dfn=999),resKO=dict(r,hp=500,maxhp=500,spd=fs*3+5,dfn=999,spa=999),slowKO=dict(r,hp=200,maxhp=200,spd=w,dfn=5,spa=999),fastKO=dict(r,hp=200,maxhp=200,spd=w,dfn=5,spa=999,spe=300))

A=dict(species=143,moves=F4,hp=100,maxhp=100,spe=100,dfn=50,spd=100,atk=5,spa=999)
D=dict(species=143,moves=F4,hp=500,maxhp=500,spe=300,dfn=999,spd=999,atk=5,spa=30)
K=dict(species=143,moves=F4,hp=100,maxhp=100,spe=5,dfn=50,spd=100,atk=5,spa=999)
N=dict(species=143,moves=F4,hp=60,maxhp=60,spe=5,dfn=5,spd=5,atk=5,spa=5)
FO=dict(spa=300,moves=F4)
BEST=2112
def who(t,ms,ai,left,right,n=16):
    benches(*ms); setup(ai,left,right); res={}
    for _ in range(n):
        x=think(1)
        if 'SWITCH' in x:
            bs=b.r32(BS); k=(b.r8(bs+92+1),b.r8(bs+146+1),b.r8(0x20233C4+0x200+1)); res[k]=res.get(k,0)+1
    print(t,res); sys.stdout.flush()
FL=dict(FO,hp=100,maxhp=100,spe=50); FR=dict(FO,hp=900,maxhp=900,spe=200)
who('W1 [A,D] (A idx2, D idx3)',[A,D],dict(moves=F4,spa=30),FL,FR)
who('W2 [D,A] (D idx2, A idx3)',[D,A],dict(moves=F4,spa=30),FL,FR)
who('W3 [N,D] N useless, D good',[N,D],dict(moves=F4,spa=30),FL,FR)
who('W4 [D,N]',[D,N],dict(moves=F4,spa=30),FL,FR)
who('W5 [K,D] K KO L, slow, frail; D faster+resists both',[K,D],dict(moves=F4,spa=30),FL,FR)
print('DONE')
L.quit()
