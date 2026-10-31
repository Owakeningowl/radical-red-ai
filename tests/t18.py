from lab import *
L = Lab(); b = L.b
SN = 143
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=300, maxhp=300, spe=50)
FE = dict(FW, moves=['Thunderbolt', 'Growl', 'Leer', 'Tail Whip'])
ATK = ['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle']
AIW = dict(moves=ATK, hp=200, maxhp=300, atk=60, spa=60, spe=100)
wall = dict(species=SN, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=900, spd=900, spe=20, hp=300, atk=30, spa=30)
glass = dict(species=SN, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
def R(t, ai, foe, n=24):
    r = L.rate(ai, foe, n)
    s = sum(v for k, v in r.items() if k != 'stay')
    print(f'{t}: {s}/{n} = {100*s//n}%'); sys.stdout.flush()
L.bench(wall, glass)
for sp in (100, 200, 300, 400, 500):
    R(f'neutral, spa {sp} (dmg ~{int((22*90*sp/100/50+2)*.93)} of 200)', AIW, dict(FE, spa=sp))
for sp in (50, 75, 100, 150):
    R(f'super effective, spa {sp} (dmg ~{int((22*90*sp/100/50+2)*2*.93)} of 200)', dict(AIW, t1=11, t2=11), dict(FE, spa=sp))
R('neutral spa 200, AI full 300', dict(AIW, hp=300), dict(FE, spa=200))
R('SE spa 100, AI full 300', dict(AIW, hp=300, t1=11, t2=11), dict(FE, spa=100))
R('SE spa 100, AI 2HKOs foe', dict(AIW, spa=300, t1=11, t2=11), dict(FE, spa=100))
R('SE spa 100, foe faster', dict(AIW, t1=11, t2=11), dict(FE, spa=100, spe=200))
L.quit()
