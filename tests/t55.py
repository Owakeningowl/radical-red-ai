from lab import *
FIRE = ['Flamethrower', 'Fire Blast', 'Heat Wave', 'Ember']
F4 = ['Flamethrower', 'Psychic', 'Dark Pulse', 'Thunderbolt']
# T: Water type, so it resists Fire by type, but frail, so the hits would 2HKO it
T = dict(species=9, moves=F4, hp=60, maxhp=60, spe=5, dfn=5, spd=5, atk=5, spa=5)
# U: Normal type, takes Fire neutrally, but so bulky no hit could 3HKO it
U = dict(species=143, moves=F4, hp=500, maxhp=500, spe=5, dfn=999, spd=999, atk=5, spa=5)
def pick(b):
    bs = b.r32(BS); return b.r8(bs + 92 + 1)
# singles
L = Lab('battle.st'); b = L.b
for order, name in (((T, U), 'idx1=T idx2=U'), ((U, T), 'idx1=U idx2=T')):
    L.bench(*order); res = {}
    L.side(1, moves=F4, spa=30, spe=50, hp=300, maxhp=300); L.side(0, moves=FIRE, spa=300, atk=30, spe=100, hp=300, maxhp=300)
    nb = b.r32(NEWBS)
    for _ in range(30):
        for i in range(2): b.w8(nb + 0x888 + i, 0xFF)
        b.think(); a, m, o = b.choice()
        if a == 2: res[m] = res.get(m, 0) + 1
    print('singles', name, 'came in:', res); sys.stdout.flush()
L.quit()
