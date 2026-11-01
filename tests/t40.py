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
# damage ladder for this AI: spa sets the size of the hit, so print it once per scenario through the outcome only
one = ['Thunderbolt']
TS = ['Thunderbolt','Reflect','Light Screen','Helping Hand']
run('A attacker, L super effective, R neutral, no KO', dict(moves=ATK, spa=60), dict(t1=WATER,t2=WATER), {})
run('B same but L is the neutral one',                 dict(moves=ATK, spa=60), {}, dict(t1=WATER,t2=WATER))
run('C support, L super effective, R neutral, no KO',  dict(moves=TS,  spa=60), dict(t1=WATER,t2=WATER), {})
run('D attacker, L SE but bulky so R takes more',      dict(moves=ATK, spa=60), dict(t1=WATER,t2=WATER,spd=400), {})
run('E attacker, SE KOs L, neutral does not KO R',     dict(moves=ATK, spa=120), dict(t1=WATER,t2=WATER,hp=120), dict(hp=300))
run('F attacker, neutral KOs low HP L, SE no KO on R', dict(moves=ATK, spa=60), dict(hp=20), dict(t1=WATER,t2=WATER))
run('G attacker, both can be KOd, L SE',               dict(moves=ATK, spa=120), dict(t1=WATER,t2=WATER,hp=40), dict(hp=40))
run('H only Thunderbolt, L immune, R neutral',         dict(moves=one, spa=60), dict(t1=GROUND,t2=GROUND), {})
run('I only Thunderbolt, L resists, R neutral',        dict(moves=one, spa=60), dict(t1=GRASS,t2=GRASS), {})
L.quit()
