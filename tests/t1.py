import sys,os,json
sys.path.insert(0,os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
p=json.load(open(os.path.expanduser('~/Downloads/radical-red-ai/build/paired.json')))
b=B('battle.st')
b.clear=p.get('ClearCachedAIData')
print('clear',hex(b.clear) if b.clear else None,'enemy species',[b.r32(EP+100*i+0x20)&0 for i in range(1)],'count byte',b.r8(0x02024029))
print('AI mon: moves',[b.r16(BM+88+12+2*i) for i in range(4)],'hp',b.r16(BM+88+40),b.r16(BM+88+44),'spe',b.r16(BM+88+6),'player',[b.r16(BM+12+2*i) for i in range(4)],b.r16(BM+40),b.r16(BM+44),b.r16(BM+6))
print('enemy party hp',[b.r16(EP+100*i+86) for i in range(6)])
print('base rate',b.rate(10),b.scores())
SM=BM+88
s2=b.r32(SM+80)
b.w32(SM+80,s2|0x10000000); print('cursed',b.rate(40)); b.w32(SM+80,s2)
b.w32(0x02023DFC+4,0) if False else None
b.quit()
