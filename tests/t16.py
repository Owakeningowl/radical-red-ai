from lab import *
L = Lab(); b = L.b
SN, GE, VA, JO, FL, ST = 143, 94, 134, 135, 136, 121   # Snorlax Gengar Vaporeon Jolteon Flareon Starmie
ATK = ['Flamethrower', 'Thunderbolt', 'Psychic', 'Tackle']
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=300, maxhp=300, spe=50)     # harmless
FB = dict(FW, atk=900)   # KOs the AI
AIW = dict(moves=ATK, hp=200, maxhp=300, atk=60, spa=60, spe=100)
AIS = dict(AIW, spe=30)
wall = dict(species=SN, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=900, spd=900, spe=20, hp=300, atk=30, spa=30)   # resists all
glass = dict(species=SN, moves=['Tackle', 'Pound', 'Scratch', 'Slash'], dfn=5, spd=5, spe=20, hp=30, atk=30, spa=30)      # dies
sweep = dict(species=SN, moves=['Earthquake', 'Pound', 'Scratch', 'Slash'], dfn=100, spd=100, spe=300, hp=300, atk=900, spa=30)   # faster KO, survives?
def R(t, ai, foe, n=40):
    r = L.rate(ai, foe, n)
    s = sum(v for k, v in r.items() if k != 'stay')
    print(f'{t}: switched {s}/{n} = {100*s//n}%  {r}'); sys.stdout.flush()
print('--- baseline')
L.bench(wall, glass); R('no reason, harmless foe', AIW, FW)
print('--- avoid death (foe KOs AI, AI moves second, AI cannot KO)')
L.bench(wall, glass); R('bench wall', AIS, FB)
L.bench(glass, glass); R('bench only dies', AIS, FB)
L.bench(sweep, glass); R('bench fast KO that survives', AIS, FB)
L.bench(wall, glass); R('AI faster instead', AIW, FB)
L.bench(wall, glass); R('AI low HP 15%', dict(AIS, hp=45), FB)
L.bench(wall, glass); R('AI paralysed under 1/3', dict(AIS, hp=90, status1=0x40), FB)
L.bench(wall, glass); R('AI can KO foe but slower', dict(AIS, spa=900), FB)
L.bench(wall, glass); R('AI can KO foe and faster', dict(AIW, spa=900), FB)
print('--- save the sweeper (AI faster, cannot KO; foe can KO)')
L.bench(sweep, glass); R('fast KO bench', AIW, FB)
L.bench(sweep, glass); R('no threat, fast KO bench', AIW, FW)
print('--- only bad moves')
useless = dict(AIW, moves=['Growl', 'Leer', 'Tail Whip', 'Sand Attack'])
L.bench(wall, glass); R('no attacks at all, harmless foe', useless, FW)
imm = dict(AIW, moves=['Tackle', 'Pound', 'Scratch', 'Slash'])
L.bench(wall, glass); R('all attacks immune (foe Ghost)', imm, dict(FW, t1=7, t2=7))
L.bench(glass, glass); R('all immune, bench dies', imm, dict(FB, t1=7, t2=7))
print('--- status')
L.bench(wall, glass)
for t, kw in [('Cursed', dict(status2=0x10000000)), ('Nightmare', dict(status2=0x08000000, status1=2)), ('Leech Seed', dict(status3=4)), ('Toxic count 3', dict(status1=0x80 | 0x300)), ('Toxic count 7', dict(status1=0x80 | 0x700)), ('Asleep', dict(status1=3)), ('Perish 1', dict(status3=0x20)), ('Yawn', dict(status3=0x1000)), ('Burned', dict(status1=0x10)), ('Atk -3 physical only', dict(moves=['Earthquake', 'Rock Slide', 'Tackle', 'Slash'], stages={1: 3})), ('SpA -3 special only', dict(moves=['Flamethrower', 'Thunderbolt', 'Surf', 'Ice Beam'], stages={4: 3})), ('Atk -2 physical only', dict(moves=['Earthquake', 'Rock Slide', 'Tackle', 'Slash'], stages={1: 4}))]:
    R(t, dict(AIW, **kw), FW)
L.quit()
