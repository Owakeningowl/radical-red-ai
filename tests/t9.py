from lab import *
L = Lab(); b = L.b
foe = dict(moves=['Tackle', 'Pound', 'Scratch', 'Quick Attack'], atk=30, spa=30, spe=50, hp=280, maxhp=300)
ATK = ['Flamethrower', 'Thunderbolt', 'Ice Beam']
CL = {
 'Attacker': (dict(item=186), ['Flamethrower', 'Thunderbolt', 'Ice Beam']),
 'Setup':    (dict(), ['Flamethrower', 'Thunderbolt', 'Swords Dance']),
 'Status':   (dict(), ['Flamethrower', 'Thunderbolt', 'Ice Beam']),
 'Stall':    (dict(), ['Flamethrower', 'Rest', 'Sleep Talk']),
 'BatonP':   (dict(), ['Baton Pass', 'Flamethrower', 'Thunderbolt']),
 'Cleric':   (dict(), ['Heal Bell', 'Flamethrower', 'Thunderbolt']),
 'Screens':  (dict(), ['Reflect', 'Light Screen', 'Flamethrower']),
 'Phazer':   (dict(), ['Haze', 'Flamethrower', 'Thunderbolt']),
 'Hazards':  (dict(), ['Spikes', 'Flamethrower', 'Thunderbolt']),
}
PROBES = ['Toxic', 'Thunder Wave', 'Will-O-Wisp', 'Spore', 'Swords Dance', 'Nasty Plot', 'Dragon Dance', 'Agility', 'Iron Defense', 'Recover', 'Substitute', 'Protect', 'Leech Seed', 'Stealth Rock', 'Spikes', 'Reflect', 'Aurora Veil', 'Taunt', 'Encore', 'Roar', 'Haze', 'Rain Dance', 'U-turn', 'Knock Off', 'Trick Room', 'Tailwind', 'Rapid Spin', 'Defog', 'Fake Out', 'Explosion', 'Destiny Bond', 'Perish Song', 'Yawn', 'Curse', 'Belly Drum', 'Wish', 'Heal Bell', 'Baton Pass']
print('probe'.ljust(14) + ' '.join(k.rjust(8) for k in CL))
for p in PROBES:
    row = []
    for k, (extra, base) in CL.items():
        moves = base + [p]
        if p in base:
            row.append('   .'.rjust(8)); continue
        ai = dict(moves=moves, spe=100, hp=200, maxhp=300, **extra)
        rs = L.run(ai, foe, 2)
        vals = sorted(set(r[3] for r in rs))
        row.append(('/'.join(map(str, vals))+'c%d'%L.style()).rjust(8))
    print(p.ljust(14) + ' '.join(row))
    sys.stdout.flush()
L.quit()
