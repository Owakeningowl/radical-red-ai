import sys,os,json
sys.path.insert(0,os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
b=B('battle.st')
def base():
    b.active(1,atk=300,dfn=300,spe=300,spa=300,spd=300,hp=300,maxhp=300,status1=0,status2=0,status3=0)
    b.active(0,atk=10,dfn=100,spe=100,spa=10,spd=100,hp=300,maxhp=300,status1=0,status2=0,status3=0)
base(); print('strong AI, no reason',b.rate(12),b.scores())
base(); b.active(1,status2=0x10000000); print('Cursed',b.rate(40))
base(); b.active(1,status3=4); print('Leech Seed',b.rate(40))
base(); b.active(1,status1=0x80|0x700); print('Toxic counter 7',b.rate(40))
base(); b.active(1,status1=0x80|0x300); print('Toxic counter 3',b.rate(20))
base(); b.active(1,status1=3); print('Asleep',b.rate(30))
b.quit()
