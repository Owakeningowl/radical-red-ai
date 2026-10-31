"""Score lab: builds a controlled matchup and reads the real AI's move scores."""
import sys, os, json
sys.path.insert(0, os.path.expanduser('~/Downloads/radical-red-ai/tools'))
from rr_h import *
MOV = json.load(open(os.path.expanduser('~/Downloads/radical-red-ai/build/moves.json')))
ID = {v['name']: int(k) for k, v in MOV.items()}
def mv(n): return ID[n] if isinstance(n, str) else n
class Lab:
    def __init__(self, state='battle.st'):
        self.b = B(state)
        self.b.w16(0x2023F1C, 0)  # this gym battle starts with sandstorm: clear it
        self.blank = self.b.r8(BM + 88 + 24)
    def side(self, slot, moves=None, **k):
        d = dict(atk=100, dfn=100, spe=100, spa=100, spd=100, hp=300, maxhp=300, status1=0, status2=0, status3=0,
                 ability=0, item=0, t1=0, t2=0, level=50, stages=None)
        d.update(k)
        b = self.b; base = BM + 88 * slot
        b.active(slot, atk=d['atk'], dfn=d['dfn'], spe=d['spe'], spa=d['spa'], spd=d['spd'], hp=d['hp'], maxhp=d['maxhp'],
                 status1=d['status1'], status2=d['status2'], status3=d['status3'],
                 moves=[mv(m) for m in moves] if moves else None) if moves else b.active(slot, atk=d['atk'], dfn=d['dfn'], spe=d['spe'], spa=d['spa'], spd=d['spd'], hp=d['hp'], maxhp=d['maxhp'], status1=d['status1'], status2=d['status2'], status3=d['status3'])
        b.w8(base + 32, d['ability']); b.w16(base + 46, d['item'])
        b.w8(base + 33, d['t1']); b.w8(base + 34, d['t2']); b.w8(base + 24, self.blank)
        b.w8(base + 42, d['level'])
        st = d['stages'] or {}
        # 1 atk 2 def 3 speed 4 spatk 5 spdef 6 acc 7 eva
        for i in range(1, 8):
            b.w8(base + 24 + i, st.get(i, 6))
    def run(self, ai, foe, n=2, **k):
        """ai/foe: dicts of side() args. returns list of score tuples"""
        self.side(1, **ai); self.side(0, **foe)
        out = []
        nb = self.b.r32(NEWBS)
        self.switched = self.total = 0
        tries = 0
        while len(out) < n and tries < n * 12:
            tries += 1
            for i in range(2):
                self.b.w8(nb + 0x888 + i, 0xFF)
            self.b.think()
            self.total += 1
            if self.b.choice()[0] == 2:
                self.switched += 1
                continue
            out.append(tuple(self.scores()))
        return out
    def mon(self, i, species=None, moves=None, hp=200, maxhp=None, atk=100, dfn=100, spe=100, spa=100, spd=100, item=0, level=50, status=0):
        b = self.b; p = EP + 100 * i
        if species is not None: b.w16(p + 0x20, species)
        b.w16(p + 0x22, item)
        if moves:
            for k in range(4):
                m = mv(moves[k]) if k < len(moves) else 0
                b.w16(p + 0x2C + 2 * k, m); b.w8(p + 0x34 + k, 20 if m else 0)
        b.w8(p + 0x4B, b.r8(p + 0x4B) & 0x7F)  # not the hidden ability
        b.w32(p + 0x50, status); b.w8(p + 0x54, level)
        b.w16(p + 0x56, hp); b.w16(p + 0x58, maxhp or max(hp, 1))
        for off, v in ((0x5A, atk), (0x5C, dfn), (0x5E, spe), (0x60, spa), (0x62, spd)):
            b.w16(p + off, v)
    def bench(self, *mons):
        # mons fill slots 1.. ; the rest are fainted
        for i in range(1, 6):
            if i - 1 < len(mons):
                self.mon(i, **mons[i - 1])
            else:
                self.b.w16(EP + 100 * i + 0x56, 0)
    def rate(self, ai, foe, n=40, cool=0):
        self.side(1, **ai); self.side(0, **foe)
        nb = self.b.r32(NEWBS)
        res = {}
        for _ in range(n):
            for i in range(2):
                self.b.w8(nb + 0x888 + i, 0xFF)
            self.b.think()
            a, m, o = self.b.choice()
            k = ('switch%d' % o) if a == 2 else 'stay'
            res[k] = res.get(k, 0) + 1
        return res
    def style(self, slot=1):
        return self.b.r8(self.b.r32(NEWBS) + 0x888 + slot)
    def scores(self):
        a = self.b.r32(self.b.r32(RES) + 20)
        return [self.b.r8(a + 4 + i) - 100 for i in range(4)]
    def show(self, title, ai, foe, n=2):
        r = self.run(ai, foe, n)
        names = [MOV[str(mv(m))]['name'] if m else '-' for m in ai['moves']]
        u = sorted(set(r))
        act = self.b.choice()
        print(f'{title}: ' + ' | '.join(f'{nm} {"/".join(str(x[i]) for x in u)}' for i, nm in enumerate(names)) + f'  [switched {self.switched}/{self.total}]')
        return r
    def quit(self):
        self.b.quit()
