import os, sys
sys.path.insert(0, os.path.expanduser('~/Downloads/null-zenith-ui/tools'))
from gd import GBA
W = os.path.expanduser('~/Downloads/radical-red-ai/test')
g = GBA(os.path.join(W, 'rr.gba'), os.path.join(W, 'rr.sav'), out=W)
cb = lambda: g.peek32(0x030030F4).split(': ')[1]
g.wait(600); g.shot('b1'); print(cb())
for i in range(4):
    g.press('A', 4, 120)
g.wait(120); g.shot('b2'); print(cb())
g.press('A', 4, 240); g.wait(240); g.shot('b3'); print(cb())
g.press('A', 4, 240); g.wait(240); g.shot('b4'); print(cb())
g.savestate(os.path.join(W, 'field.st'))
g.quit()
