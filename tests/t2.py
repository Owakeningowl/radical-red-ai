import sys,os,json
sys.path.insert(0,os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
b=B('battle.st')
bs=b.r32(BS)
print('start comm',b.r8(COMM),b.r8(COMM+1),'act',b.r8(ACT),b.r8(ACT+1),'mon',b.r8(bs+92+1),'out',b.r8(bs+146+1),'scores',b.scores())
# plain re-think, no RNG pokes, leaving action alone
for i in range(8):
    b.w8(bs+146+1,6); b.w8(bs+92+1,6)
    b.w8(COMM+1,0)
    for _ in range(60):
        b.g.wait(2); b.g.sync()
        if b.r8(COMM+1)>=4: break
    print(i,'comm',b.r8(COMM+1),'act',b.r8(ACT+1),'mon',b.r8(bs+92+1),'out',b.r8(bs+146+1),'scores',b.scores(),'exec',hex(b.r32(0x02023BC8)))
b.quit()
