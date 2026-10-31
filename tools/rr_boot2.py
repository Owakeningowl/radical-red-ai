import os, sys
sys.path.insert(0, os.path.expanduser('~/Downloads/null-zenith-ui/tools'))
from gd import GBA
W = os.path.expanduser('~/Downloads/radical-red-ai/test')
g = GBA(os.path.join(W, 'rr.gba'), os.path.join(W, 'rr.sav'), out=W)
cb = lambda: g.peek32(0x030030F4).split(': ')[1]
g.loadstate(os.path.join(W, 'field.st')) if False else None
g.wait(600)
for i in range(6):
    g.press('A', 4, 120)
g.wait(120)
print('title?', cb())
g.press('A', 4, 240); g.wait(300)
print(cb()); g.press('A', 4, 300); g.wait(200); g.shot('f1'); ow = cb(); print('overworld', ow)
print('party count', g.peek32(0x02024029 & ~3), 'first mon species raw', g.peek32(0x02024284))
g.savestate(os.path.join(W, 'field.st'))
g.quit()
