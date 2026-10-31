from lab import *
L = Lab(); b = L.b
foe = dict(moves=['Tackle', 'Pound', 'Scratch', 'Quick Attack'], atk=30, spa=30, spe=50)
def thresh(move, f={}, lo=1, hi=600):
    while hi - lo > 1:
        mid = (lo + hi) // 2
        r = L.run(dict(moves=[move, 'Growl', 'Leer', 'Tail Whip']), dict(foe, hp=mid, maxhp=2000, **f), 1)
        if r and r[0][0] >= 8: lo = mid
        else: hi = mid
    return lo
print('blank', L.blank)
for m in ['Flamethrower', 'Earthquake']:
    print(m, MOV[str(ID[m])]['power'], 'normal', thresh(m), 'fire', thresh(m, dict(t1=10, t2=10)), 'water', thresh(m, dict(t1=11, t2=11)))
    sys.stdout.flush()
print('ai', [b.r8(BM+88+i) for i in range(32,36)], 'foe', [b.r8(BM+i) for i in range(32,36)])
L.quit()
