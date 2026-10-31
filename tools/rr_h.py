"""Run the real Radical Red AI in a live battle, on a copy of the ROM and save."""
import os, random, struct, subprocess, sys
sys.path.insert(0, os.path.expanduser('~/Downloads/null-zenith-ui/tools'))
from gd import GBA
W = os.path.expanduser('~/Downloads/radical-red-ai/test')
BIN = '/opt/devkitpro/devkitARM/bin/arm-none-eabi-'
BM, TF, RES, BS, NEWBS = 0x02023BE4, 0x02022B4C, 0x02023FF4, 0x02023FE8, 0x0203E038
COMM, ACT, IDX, EP, PP = 0x02023E82, 0x02023D7C, 0x02023BCE, 0x0202402C, 0x02024284
ACTIVE, MAINF, CB1, RNG, RNG2 = 0x02023BC4, 0x03004F84, 0x030030F0, 0x03005000, 0x020386D0
STUB = 0x0203FC00
RESULT = STUB + 0x60
_ASM = """
.thumb
.syntax unified
push {r4,lr}
ldr r2,lit_active
movs r3,#1
strb r3,[r2]
ldr r0,lit_a0
ldr r1,lit_a1
ldr r2,lit_a2
ldr r3,lit_a3
ldr r4,lit_fn
bl tramp
ldr r1,lit_res
str r0,[r1]
ldr r0,lit_main
ldr r1,lit_orig
str r1,[r0]
pop {r4,pc}
tramp: bx r4
.align 2
lit_active: .word 0x02023BC4
lit_a0: .word 0
lit_a1: .word 0
lit_fn: .word 0
lit_res: .word %d
lit_main: .word 0
lit_orig: .word 0
lit_a2: .word 0
lit_a3: .word 0
""" % RESULT


def _stub():
    p = os.path.join(W, 'stub')
    subprocess.run([BIN + 'as', '-mcpu=arm7tdmi', '-o', p + '.o', '-'], input=_ASM, text=True, check=True)
    subprocess.run([BIN + 'objcopy', '-O', 'binary', '-j', '.text', p + '.o', p + '.bin'], check=True)
    return open(p + '.bin', 'rb').read()


_S = _stub()
_L = len(_S) - 9 * 4


class B:
    def __init__(self, state=None):
        self.g = GBA(os.path.join(W, 'rr.gba'), os.path.join(W, 'rr.sav'), out=W)
        if state:
            self.g.loadstate(os.path.join(W, state))
            self.g.wait(2)

    def r32(self, a):
        return int(self.g.peek32(a).split(': ')[1], 16)

    def r16(self, a):
        return (self.r32(a & ~3) >> ((a & 2) * 8)) & 0xFFFF

    def r8(self, a):
        return (self.r32(a & ~3) >> ((a & 3) * 8)) & 0xFF

    def s8(self, a):
        v = self.r8(a)
        return v - 256 if v > 127 else v

    def w16(self, a, v):
        self.g.cmd(f'poke16 {a:#x} {v & 0xFFFF:#x}')

    def w8(self, a, v):
        h = a & ~1
        o = self.r16(h)
        self.w16(h, (o & 0xFF00) | (v & 0xFF) if not a & 1 else (o & 0xFF) | ((v & 0xFF) << 8))

    def w32(self, a, v):
        self.w16(a, v & 0xFFFF)
        self.w16(a + 2, (v >> 16) & 0xFFFF)

    def wblock(self, a, d):
        for i in range(0, len(d), 2):
            self.w16(a + i, struct.unpack_from('<H', d, i)[0])

    def call(self, fn, a0=0, a1=0, a2=0, a3=0, via=MAINF):
        orig = self.r32(via)
        blob = bytearray(_S)
        struct.pack_into('<I', blob, _L + 4, a0)
        struct.pack_into('<I', blob, _L + 8, a1)
        struct.pack_into('<I', blob, _L + 12, fn | 1)
        struct.pack_into('<I', blob, _L + 20, via)
        struct.pack_into('<I', blob, _L + 24, orig)
        struct.pack_into('<I', blob, _L + 28, a2)
        struct.pack_into('<I', blob, _L + 32, a3)
        self.wblock(STUB, bytes(blob))
        self.w32(RESULT, 0xDEADBEEF)
        self.w32(via, STUB | 1)
        for _ in range(200):
            self.g.wait(1)
            self.g.sync()
            if self.r32(via) == orig:
                break
        return self.r32(RESULT)

    def quit(self):
        self.g.quit()


def think(self, seed=None):
    s = seed if seed is not None else random.getrandbits(32)
    self.w32(RNG2, s)
    self.w32(RNG, random.getrandbits(32))
    bs = self.r32(BS)
    self.w8(bs + 146 + 1, 6)
    self.w8(bs + 92 + 1, 6)
    self.w8(ACT + 1, 0xFF)
    if getattr(self, 'clear', None):
        self.call(self.clear)
    self.w8(COMM + 1, 0)
    for _ in range(120):
        self.g.wait(2)
        self.g.sync()
        if self.r8(COMM + 1) >= 4:
            return True
    return False


def scores(self):
    ai = self.r32(self.r32(RES) + 20)
    return [self.s8(ai + 4 + i) - 100 for i in range(4)]


def choice(self):
    bs = self.r32(BS)
    return (self.r8(ACT + 1), self.r8(bs + 92 + 1), self.r8(bs + 146 + 1))


def rate(self, n=20):
    res = {}
    for _ in range(n):
        self.think()
        a, m, o = self.choice()
        k = ('switch', m) if a == 2 else ('act', a)
        res[k] = res.get(k, 0) + 1
    return res


B.think = think
B.scores = scores
B.choice = choice
B.rate = rate


def think3(self, seed=None):
    s = seed if seed is not None else random.getrandbits(32)
    self.call(0x090c8ba4); self.call(0x090c8ed0)
    nb = self.r32(NEWBS)
    self.w8(nb + 233, self.r8(nb + 233) & 0x7F)
    self.w32(RNG2, s)
    self.w32(RNG, random.getrandbits(32))
    bs = self.r32(BS)
    self.w8(bs + 146 + 1, 6)
    self.w8(bs + 92 + 1, 6)
    self.w8(ACT + 1, 0xFF)
    self.w8(COMM + 1, 0)
    for _ in range(150):
        self.g.wait(2)
        self.g.sync()
        if self.r8(COMM + 1) >= 4:
            return True
    return False


def active(self, slot, **k):
    b = BM + 88 * slot
    for name, off in dict(atk=2, dfn=4, spe=6, spa=8, spd=10, hp=40, maxhp=44).items():
        if name in k:
            self.w16(b + off, k[name])
    if 'moves' in k:
        for i in range(4):
            m = k['moves'][i] if i < len(k['moves']) else 0
            self.w16(b + 12 + i * 2, m)
            self.w8(b + 36 + i, 20 if m else 0)
    if 'status1' in k:
        self.w32(b + 76, k['status1'])
    if 'status2' in k:
        self.w32(b + 80, k['status2'])
    if 'status3' in k:
        self.w32(0x02023DFC + 4 * slot, k['status3'])


B.think = think3
B.active = active
