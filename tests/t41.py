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
run('1 attacker no KO: L super effective, R neutral',dict(moves=ATK,spa=60),SE,{},moves=TB)
run('2 attacker no KO: L super effective but bulky, R takes more',dict(moves=ATK,spa=60),dict(SE,spd=400),{},moves=TB)
run('3 utility no KO: L super effective, R neutral',dict(moves=ONE,spa=60),SE,{},moves=TB)
run('4 utility no KO: L resists, R neutral',dict(moves=ONE,spa=60),RES,{},moves=TB)
setup(dict(moves=ONE,spa=120),SE,{}); d=dmg('Thunderbolt',1,0); e=dmg('Thunderbolt',1,2); h=(d+e)//2
run('5 attacker: same HP, super effective KOs L, neutral cannot KO R',dict(moves=ATK,spa=120),dict(SE,hp=h,maxhp=h),dict(hp=h,maxhp=h),moves=TB)
run('6 utility: same HP, super effective KOs L, neutral cannot KO R',dict(moves=ONE,spa=120),dict(SE,hp=h,maxhp=h),dict(hp=h,maxhp=h),moves=TB)
run('7 attacker: neutral KOs low HP L, super effective no KO on R',dict(moves=ATK,spa=60),dict(hp=20),SE,n=60,moves=TB)
run('8 attacker: both KOd, L super effective',dict(moves=ATK,spa=120),dict(SE,hp=30),dict(hp=30),moves=TB)
run('9 attacker: both take 50pct+, no KO, R can KO the AI',dict(moves=ATK,spa=120,hp=60,maxhp=60),dict(SE,hp=d+40,maxhp=d+40),dict(hp=e+20,maxhp=e+20,moves=['Hyper Beam','Pound','Scratch','Slash'],atk=300),moves=TB)
L.quit()
