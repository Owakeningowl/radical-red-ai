from lab import *
L = Lab(); b = L.b
foe = dict(moves=['Tackle', 'Pound', 'Scratch', 'Quick Attack'], atk=30, spa=30, spe=50)
def ko(moves, ai={}, f={}):
    return L.run(dict(moves=moves, **ai), dict(foe, **f), 1)[0][0]
def thresh(moves, ai={}, f={}, lo=1, hi=2000):
    # biggest HP that still counts as a KO
    while hi - lo > 1:
        mid = (lo + hi) // 2
        if ko(moves, ai, dict(f, hp=mid, maxhp=2000)) >= 8: lo = mid
        else: hi = mid
    return lo
F = ['Flamethrower', 'Growl', 'Leer', 'Tail Whip']
E = ['Earthquake', 'Growl', 'Leer', 'Tail Whip']
T = ['Tackle', 'Growl', 'Leer', 'Tail Whip']
print('Flamethrower raw 41:', thresh(F))
print('Earthquake raw 46:', thresh(E))
print('Tackle STAB raw (19+... ):', thresh(T))
print('Earthquake atk200 raw 90:', thresh(E, dict(atk=200)))
print('Flame foe spd200 raw 21:', thresh(F, {}, dict(spd=200)))
print('species/level', b.r16(BM+88), b.r8(BM+88+42), b.r16(BM), b.r8(BM+42), 'types', b.r8(BM+88+33), b.r8(BM+88+34), b.r8(BM+33))
L.quit()
