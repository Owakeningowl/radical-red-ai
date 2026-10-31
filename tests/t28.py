from lab import *
AB = json.load(open(os.path.expanduser('~/Downloads/radical-red-ai/build/abilities.json')))
UN = [int(k) for k, v in AB.items() if v == 'Unaware'][0]
L = Lab(); b = L.b
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=280, maxhp=300, spe=50)
glass = dict(species=143, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
L.bench(glass, glass, glass)
def S(t, probe, ai={}, foe={}, base=[], n=2):
    a = dict(moves=base + [probe], hp=200, maxhp=300, spe=100); a.update(ai)
    f = dict(FW); f.update(foe)
    r = L.run(a, f, n)
    v = sorted(set(x[len(base)] for x in r)) if r else ['sw']
    print(f'{t}: {"/".join(map(str,v))}', end=' ; '); sys.stdout.flush()
PH = ['Earthquake', 'Rock Slide', 'Toxic']; SP = ['Flamethrower', 'Thunderbolt', 'Toxic']
for st in (6, 7, 8, 9, 10, 11, 12):
    S(f'SD at {st-6:+d}', 'Swords Dance', dict(stages={1: st}), {}, PH)
print()
for st in (6, 7, 8, 9, 10):
    S(f'CM at {st-6:+d}', 'Calm Mind', dict(stages={4: st}), {}, SP)
print()
for st in (6, 7, 8, 9, 10):
    S(f'DD spe at {st-6:+d} slower', 'Dragon Dance', dict(spe=30, stages={3: st, 1: 8}), {}, PH)
print()
S('SD foe Unaware', 'Swords Dance', {}, dict(ability=UN), PH)
S('SD foe has Roar', 'Swords Dance', {}, dict(moves=['Roar', 'Pound', 'Scratch', 'Slash']), PH)
S('SD foe has Haze', 'Swords Dance', {}, dict(moves=['Haze', 'Pound', 'Scratch', 'Slash']), PH)
S('SD foe statused asleep', 'Swords Dance', dict(spe=30), dict(status1=3, atk=330), PH)
S('Toxic foe already poisoned', 'Toxic', {}, dict(status1=8), ['Earthquake', 'Rock Slide', 'Thunderbolt'])
S('Toxic foe Steel', 'Toxic', {}, dict(t1=8, t2=8), ['Earthquake', 'Rock Slide', 'Thunderbolt'])
S('Spore foe Grass', 'Spore', {}, dict(t1=12, t2=12), ['Earthquake', 'Rock Slide', 'Thunderbolt'])
S('Will-O foe special only', 'Will-O-Wisp', {}, dict(moves=['Flamethrower', 'Surf', 'Psychic', 'Ice Beam']), ['Earthquake', 'Rock Slide', 'Thunderbolt'])
S('Stealth Rock already up', 'Stealth Rock', {}, {}, ['Earthquake', 'Rock Slide', 'Thunderbolt'])
print()
L.quit()
