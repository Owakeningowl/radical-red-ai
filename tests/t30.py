from lab import *
L = Lab(); b = L.b
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=300, maxhp=300, spe=50)
ATK = ['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle']
AIW = dict(moves=ATK, hp=300, maxhp=300, atk=60, spa=60, spe=100)
base = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=200, spd=200, spe=100, atk=30, spa=30)
glass = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
P = os.path.join(W, 'battle.st')
def R(t, ai, foe, mon, n=24):
    c = 0
    for _ in range(n):
        b.g.loadstate(P); b.g.wait(2); b.w16(0x2023F1C, 0)
        L.bench(mon, glass)
        r = L.rate(ai, foe, 1)
        c += sum(v for k, v in r.items() if k != 'stay')
    print(f'{t}: {c}/{n} = {100*c//n}%'); sys.stdout.flush()
TB = dict(FW, moves=['Thunderbolt', 'Pound', 'Scratch', 'Tackle'], spa=40)
FT = dict(FW, moves=['Flamethrower', 'Pound', 'Scratch', 'Tackle'], spa=40)
FSt = dict(FW, moves=['Flamethrower', 'Growl', 'Leer', 'Toxic'], spa=40)
J = dict(base, species=135, hp=300, maxhp=300); Jh = dict(J, hp=150); F = dict(base, species=136, hp=300, maxhp=300)
R('weak T-bolt, Jolteon full HP', AIW, TB, J)
R('weak T-bolt, Jolteon hurt', AIW, TB, Jh)
R('weak Flamethrower, Flash Fire', AIW, FT, F)
R('same, your style not attacker', AIW, FSt, F)
R('same, AI slower and can KO you', dict(AIW, spe=30, spa=900), FT, F)
R('same, AI faster and can KO you', dict(AIW, spa=900), FT, F)
R('same, AI +1 boost', dict(AIW, stages={4: 7}), FT, F)
R('same, AI +2 boost', dict(AIW, stages={4: 8}), FT, F)
R('T-bolt predicted, only Flash Fire back', AIW, TB, F)
R('strong T-bolt 2HKO, Jolteon full', AIW, dict(TB, spa=500), J)
L.quit()
