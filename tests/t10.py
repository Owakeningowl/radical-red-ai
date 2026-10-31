from lab import *
L = Lab(); b = L.b
foe = dict(moves=['Earthquake', 'Growl', 'Leer', 'Tail Whip'], atk=3000, spa=900, spe=100)
Q = ['Flamethrower', 'Thunderbolt', 'Psychic', 'Quick Attack']
def P():
    nb=b.r32(NEWBS)
    print('   pivotflag', hex(b.r8(nb+453)), 'strongestfirst', b.call(0x90e0edc,98,1,0)&1)
L.show('slower, foe KOs, QA', dict(moves=Q, spe=30), foe, 3); P()
L.show('faster than nobody, Mach Punch', dict(moves=['Flamethrower','Thunderbolt','Psychic','Mach Punch'], spe=30), foe, 3); P()
L.quit()
