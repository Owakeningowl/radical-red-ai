import sys,os,struct
sys.path.insert(0,os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
b=B('field.st')
print('cb2',hex(b.r32(0x030030F4)),'cb1',hex(b.r32(CB1)))
trainer=int(sys.argv[1]) if len(sys.argv)>1 else 414
SCR=STUB+0x100
TXT=STUB+0x180
b.wblock(TXT,b'\xff\xff')
s=bytes([0x5C,3])+struct.pack('<HH',trainer,0)+struct.pack('<I',TXT)+bytes([2,2])
if len(s)%2: s+=b'\x00'
b.wblock(SCR,s)
print('enable',hex(b.call(0x08069940,via=CB1)))
print('setup',hex(b.call(0x08069AE4,SCR,via=CB1)))
hs=0x08014041
for i in range(400):
    b.g.wait(30); b.g.sync()
    m=b.r32(MAINF)
    if m==hs:
        print('action select at step',i,'comm',b.r8(COMM),b.r8(COMM+1)); 
        if b.r8(COMM)==2: break
    if i%6==5: b.g.press('A',4,10)
b.g.wait(120); b.g.sync()
print('main',hex(b.r32(MAINF)),'type',hex(b.r32(TF)),'cb2',hex(b.r32(0x030030F4)))
print('species',b.r16(BM),b.r16(BM+88),'hp',b.r16(BM+40),b.r16(BM+88+40),'idx',b.r16(IDX),b.r16(IDX+2),'comm',b.r8(COMM),b.r8(COMM+1))
res=b.r32(RES); ai=b.r32(res+20)
print('res',hex(res),'ai',hex(ai),'flags',hex(b.r32(ai+12)),'scores',[b.s8(ai+4+i) for i in range(4)])
print('newbs',hex(b.r32(NEWBS)))
b.g.shot('t_dbl')
b.g.savestate(os.path.join(W,'dbl.st'))
b.quit()
print('player party', [ (b.r16(PP+100*i+0x20), b.r16(PP+100*i+0x56)) for i in range(6)])
print('enemy party', [ (b.r16(EP+100*i+0x20), b.r16(EP+100*i+0x56)) for i in range(6)])
print('count', b.r8(0x2023BCC), 'mons', [b.r16(BM+88*i) for i in range(4)])
