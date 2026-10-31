from lab import *
L = Lab('dbl.st'); b = L.b
GCM = 0x02023DC4
def setm(slot, **k):
    L.side(slot, **k)
def clr():
    nb = b.r32(NEWBS)
    for i in range(4): b.w8(nb + 0x888 + i, 0xFF)
def thinkdbl(n=20):
    res = {}
    bs = b.r32(BS)
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
        a = b.r8(ACT + 1)
        if a == 2:
            k = 'SWITCH'
        else:
            slot = b.r8(0x20233C4 + 0x200 + 2); t = b.r8(0x20233C4 + 0x200 + 3)
            mv_ = b.r16(BM + 88 + 12 + 2 * slot) if slot < 4 else 0
            k = MOV.get(str(mv_), {}).get('name', mv_) + '>' + str(t)
        res[k] = res.get(k, 0) + 1
    return res
W = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=300, maxhp=300, spe=50)
A = dict(moves=['Flamethrower', 'Thunderbolt', 'Earthquake', 'Heat Wave'], hp=300, maxhp=300, spe=100, atk=100, spa=100)
P = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], hp=300, maxhp=300, spe=100, atk=30, spa=30)
def scen(t, ai, p0, p2, part=P, n=16):
    setm(1, **ai); setm(0, **p0); setm(2, **p2); setm(3, **part)
    print(t, thinkdbl(n)); sys.stdout.flush()



S1=['Flamethrower', 'Thunderbolt', 'Ice Beam', 'Psychic']
print('F1 right low, single', end=' '); scen('', dict(A, moves=S1, spa=300), W, dict(W, hp=20))
print('F2 left low, single', end=' '); scen('', dict(A, moves=S1, spa=300), dict(W, hp=20), W)
print('F3 both healthy, strong', end=' '); scen('', dict(A, moves=S1, spa=300), W, W)
print('F4 strong spread 50pct', end=' '); scen('', dict(A, moves=['Flamethrower', 'Thunderbolt', 'Heat Wave', 'Psychic'], spa=600), W, W)
print('F5 EQ, frail partner', end=' '); scen('', dict(A, moves=['Earthquake', 'Thunderbolt', 'Rock Slide', 'Psychic'], atk=600,spa=100), W, W, dict(P, hp=50))
print('F6 both KOable, right can KO AI', end=' '); scen('', dict(A, moves=S1, spa=300), dict(W, hp=20), dict(W, hp=20, atk=900))
print('F7 both KOable, left can KO AI', end=' '); scen('', dict(A, moves=S1, spa=300), dict(W, hp=20, atk=900), dict(W, hp=20))
print('F8 spread KOs both', end=' '); scen('', dict(A, moves=['Flamethrower', 'Thunderbolt', 'Heat Wave', 'Psychic'], spa=300), dict(W, hp=20), dict(W, hp=20))
print('F9 Toxic vs strong', end=' '); scen('', dict(A, moves=['Toxic','Flamethrower','Thunderbolt','Ice Beam'], spa=300), W, W)
print('F10 Toxic vs weak attacks', end=' '); scen('', dict(A, moves=['Toxic','Tackle','Pound','Scratch'], atk=40), W, W)
print('F11 Protect, threatened', end=' '); scen('', dict(A, moves=['Protect','Flamethrower','Thunderbolt','Ice Beam'], spa=300), dict(W, atk=900), W)
print('F12 Fake Out', end=' '); scen('', dict(A, moves=['Fake Out','Flamethrower','Thunderbolt','Ice Beam'], spa=300), W, W)
print('F13 Tailwind', end=' '); scen('', dict(A, moves=['Tailwind','Flamethrower','Thunderbolt','Ice Beam'], spa=300, spe=30), W, W)
print('F14 Trick Room', end=' '); scen('', dict(A, moves=['Trick Room','Flamethrower','Growl','Leer'], spa=300, spe=10), W, W)
print('F15 Spore', end=' '); scen('', dict(A, moves=['Spore','Flamethrower','Thunderbolt','Ice Beam'], spa=300), W, W)
print('F16 Rain Dance', end=' '); scen('', dict(A, moves=['Rain Dance','Surf','Thunderbolt','Ice Beam'], spa=300), W, W)
print('F17 Reflect', end=' '); scen('', dict(A, moves=['Reflect','Flamethrower','Growl','Leer'], spa=300), W, W)
print('F18 Helping Hand', end=' '); scen('', dict(A, moves=['Helping Hand','Flamethrower','Growl','Leer'], spa=300), W, W)
print('F19 Follow Me', end=' '); scen('', dict(A, moves=['Follow Me','Flamethrower','Thunderbolt','Ice Beam'], spa=300), W, W)
L.quit()
