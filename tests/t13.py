from lab import *
import itertools
L = Lab()
W = sys.argv[1] if len(sys.argv) > 1 else 'all'
CL = {
 'Attacker': (dict(item=186), ['Earthquake', 'Flamethrower', 'Thunderbolt']),
 'Setup':    (dict(), ['Earthquake', 'Flamethrower', 'Swords Dance']),
 'Status':   (dict(), ['Earthquake', 'Flamethrower', 'Thunderbolt']),
 'Stall':    (dict(), ['Earthquake', 'Rest', 'Sleep Talk']),
 'BatonP':   (dict(), ['Baton Pass', 'Earthquake', 'Flamethrower']),
 'Cleric':   (dict(), ['Heal Bell', 'Earthquake', 'Flamethrower']),
 'Screens':  (dict(), ['Reflect', 'Light Screen', 'Earthquake']),
 'Phazer':   (dict(), ['Haze', 'Earthquake', 'Flamethrower']),
 'Hazards':  (dict(), ['Spikes', 'Earthquake', 'Flamethrower']),
}
PROBES = ['Toxic', 'Thunder Wave', 'Will-O-Wisp', 'Spore', 'Yawn', 'Leech Seed', 'Confuse Ray', 'Swords Dance', 'Nasty Plot', 'Dragon Dance', 'Calm Mind', 'Bulk Up', 'Agility', 'Iron Defense', 'Recover', 'Substitute', 'Protect', 'Stealth Rock', 'Spikes', 'Reflect', 'Taunt', 'Encore', 'Roar', 'Haze', 'Rain Dance', 'U-turn', 'Knock Off', 'Rapid Spin', 'Fake Out', 'Explosion', 'Destiny Bond', 'Wish', 'Heal Bell', 'Baton Pass', 'Tackle', 'Giga Drain']
FOEW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, dfn=100, spd=100, hp=280, maxhp=300)
FOEM = dict(FOEW, atk=330)   # 2HKO on 200 hp (about 80+ each)
FOEB = dict(FOEW, atk=900)   # KO on 200 hp
SC = {
 'safe,faster': (dict(spe=100), dict(FOEW, spe=50)),
 'safe,slower': (dict(spe=30), dict(FOEW, spe=50)),
 '2HKO,faster': (dict(spe=100), dict(FOEM, spe=50)),
 '2HKO,slower': (dict(spe=30), dict(FOEM, spe=50)),
 'KO,faster':   (dict(spe=100), dict(FOEB, spe=50)),
 'KO,slower':   (dict(spe=30), dict(FOEB, spe=50)),
}
out = open('../notes/matrix.txt', 'a')
for scn, (a, f) in SC.items():
    print('## ' + scn + '  ' + ' '.join(CL), file=out); out.flush()
    for p in PROBES:
        row = []
        for k, (extra, base) in CL.items():
            if p in base:
                row.append('.'); continue
            ai = dict(moves=base + [p], hp=200, maxhp=300, **extra, **a)
            rs = L.run(ai, f, 2)
            s = sorted(set(r[3] for r in rs))
            row.append(('/'.join(map(str, s)) if rs else 'sw') + ('!' if L.switched else ''))
        print(p.ljust(14) + ' '.join(x.rjust(6) for x in row), file=out); out.flush()
L.quit()
