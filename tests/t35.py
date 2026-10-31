from lab import *
L = Lab(); b = L.b
FM = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=250, spa=30, hp=300, maxhp=300, spe=50)
AI = dict(moves=['Flamethrower', 'Psychic', 'Ice Beam', 'Tackle'], hp=200, maxhp=300, atk=60, spa=60, spe=100)
wall = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=900, spd=900, spe=20, hp=300, atk=30, spa=30)
glass = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
L.bench(wall, glass)
for t, sp, n in (('AI under 1/3 of your HP', 60, 80), ('AI can 3HKO, not 2HKO', 300, 120), ('AI can 2HKO', 500, 120)):
    r = L.rate(dict(AI, spa=sp), FM, n)
    s = sum(v for k, v in r.items() if k != 'stay')
    print(f'{t}: {s}/{n} = {100*s//n}%'); sys.stdout.flush()
L.quit()
