from lab import *
L = Lab(); b = L.b
SN = 143
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=280, maxhp=300, spe=50)
FM = dict(FW, atk=330); FB = dict(FW, atk=900)
glass = dict(species=SN, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)
L.bench(glass, glass, glass)
AT = ['Earthquake', 'Flamethrower', 'Thunderbolt']
def S(t, probe, ai={}, foe={}, base=AT, n=3, idx=None):
    a = dict(moves=base + [probe], hp=200, maxhp=300, spe=100); a.update(ai)
    f = dict(FW); f.update(foe)
    r = L.run(a, f, n)
    i = len(base) if idx is None else idx
    v = sorted(set(x[i] for x in r)) if r else ['sw']
    print(f'{t}: {probe} {"/".join(map(str,v))} (style {L.style()}, sw {L.switched}/{L.total})'); sys.stdout.flush()
print('-- predicted switch')
imm = dict(moves=['Tackle','Pound','Scratch','Slash'])
S('foe all immune to AI (Ghost AI), AI KO', 'Psychic', dict(t1=7,t2=7), dict(hp=20, **imm), base=['Flamethrower','Thunderbolt','Ice Beam'])
S('foe all immune, AI no KO, Pursuit', 'Pursuit', dict(t1=7,t2=7), dict(**imm), base=['Flamethrower','Thunderbolt','Ice Beam'])
print('-- trap and perish')
S('Mean Look', 'Mean Look', {}, {}, base=['Toxic','Flamethrower','Thunderbolt'])
S('Perish, foe not trapped', 'Perish Song', {}, {}, base=['Toxic','Flamethrower','Thunderbolt'])
S('Perish, foe trapped', 'Perish Song', {}, dict(status2=0x04000000), base=['Toxic','Flamethrower','Thunderbolt'])
print('-- boosts: when')
S('Swords Dance at +2', 'Swords Dance', dict(stages={1:8}), {}, base=['Earthquake','Rock Slide','Toxic'])
S('Swords Dance at +1', 'Swords Dance', dict(stages={1:7}), {}, base=['Earthquake','Rock Slide','Toxic'])
S('Swords Dance foe Unaware', 'Swords Dance', {}, dict(ability=109), base=['Earthquake','Rock Slide','Toxic'])
S('Shell Smash', 'Shell Smash', dict(spe=30), {}, base=['Earthquake','Rock Slide','Toxic'])
S('Quiver Dance', 'Quiver Dance', dict(spe=30), {}, base=['Flamethrower','Thunderbolt','Toxic'])
S('Belly Drum', 'Belly Drum', {}, {}, base=['Earthquake','Rock Slide','Toxic'])
S('Curse', 'Curse', {}, {}, base=['Earthquake','Rock Slide','Toxic'])
S('Coil', 'Coil', {}, {}, base=['Earthquake','Rock Slide','Toxic'])
S('Encore, foe used status last', 'Encore', dict(spe=100), {}, base=['Toxic','Flamethrower','Thunderbolt'])
print('-- mega ring/rooms')
L.quit()
