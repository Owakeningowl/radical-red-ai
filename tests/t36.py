from lab import *
L = Lab(); b = L.b
FW = dict(moves=['Tackle', 'Pound', 'Scratch', 'Slash'], atk=30, spa=30, hp=280, maxhp=300, spe=50)
AT = ['Earthquake', 'Flamethrower', 'Thunderbolt']
SC = 0x2023DE4  # gSideTimers, 0 player side
print('player party hp', [b.r16(PP + 100 * i + 0x56) for i in range(6)])
def alive(n):
    for i in range(6):
        v = 50 if i < n else 0
        b.w16(PP + 100 * i + 0x56, v)
def S(t, probe, foe={}, base=AT, n=12):
    a = dict(moves=base + [probe], hp=200, maxhp=300, spe=100)
    f = dict(FW); f.update(foe)
    r = L.run(a, f, n)
    v = {}
    for x in r:
        v[x[len(base)]] = v.get(x[len(base)], 0) + 1
    print(f'{t}: {probe} {v}'); sys.stdout.flush()
for n in (6, 4, 3, 2, 1):
    alive(n)
    S(f'{n} of yours alive', 'Stealth Rock')
    S(f'{n} of yours alive', 'Spikes')
alive(6)
S('you know Rapid Spin', 'Stealth Rock', dict(moves=['Rapid Spin', 'Pound', 'Scratch', 'Slash']))
S('you know Defog', 'Stealth Rock', dict(moves=['Defog', 'Pound', 'Scratch', 'Slash']))
S('you know Magic Coat', 'Stealth Rock', dict(moves=['Magic Coat', 'Pound', 'Scratch', 'Slash']))
# Stealth Rock already up on your side: side timer byte
bs = gs = 0x2023DE4
for off in range(0, 12):
    pass
L.quit()
