from lab import *
L = Lab(); b = L.b
foe = dict(moves=['Tackle', 'Pound', 'Scratch', 'Quick Attack'], atk=30, spa=30, spe=50)
def ko(moves, ai={}, f={}):
    return L.run(dict(moves=moves, **ai), dict(foe, **f), 1)[0][0]
def thresh(moves, ai={}, f={}, lo=1, hi=500):
    while hi - lo > 1:
        mid = (lo + hi) // 2
        if ko(moves, ai, dict(f, hp=mid, maxhp=2000)) >= 8: lo = mid
        else: hi = mid
    return lo
F = ['Flamethrower', 'Growl', 'Leer', 'Tail Whip']
E = ['Earthquake', 'Growl', 'Leer', 'Tail Whip']
print('addr check', [hex(b.r8(BM+i)) for i in range(32,36)], 'item', b.r16(BM+46))
b.w16(BM, 143)
print('foe species Snorlax: Flame', thresh(F), 'EQ', thresh(E))
L.quit()
