import sys,os
sys.path.insert(0,os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
b=B('battle.st')
print('var 0x5010',hex(b.call(0x0806E454,0x5010)&0xffff) if False else '')
print('gBattleTypeFlags',hex(b.r32(TF)))
b.quit()
