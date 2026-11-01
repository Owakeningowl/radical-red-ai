from lab import *
import time
L = Lab(); b = L.b
DS = 0x2023E0C + 0x1C   # gDisableStructs[1]
F = ['Flamethrower', 'Psychic', 'Dark Pulse', 'Thunderbolt']
SN = 143
def backs(fs):
    w = max(5, fs // 2); r = dict(species=SN, moves=F, atk=30, spa=30, spe=20, dfn=999)
    return {
        'nothing':   dict(r, hp=140, maxhp=140, spd=w, dfn=5),
        'faster':    dict(r, hp=200, maxhp=200, spd=w, dfn=5, spe=300),
        'walls':     dict(r, hp=100, maxhp=100, spd=fs + 1, dfn=31),
        'resists':   dict(r, hp=300, maxhp=300, spd=fs * 3),
        'res+fast':  dict(r, hp=300, maxhp=300, spd=fs * 3, spe=300),
        'res+KO':    dict(r, hp=300, maxhp=300, spd=fs * 3, spa=999),
        'slowKO':    dict(r, hp=200, maxhp=200, spd=w, dfn=5, spa=999),
        'fastKO':    dict(r, hp=200, maxhp=200, spd=w, dfn=5, spa=999, spe=300),
        'fastKOfrail': dict(r, hp=30, maxhp=30, spd=w, dfn=5, spa=999, spe=300),
    }
NAMES = list(backs(100))
print('row | ' + ' | '.join(NAMES)); sys.stdout.flush()
FAST, SLOW = 150, 50
HURT = dict(harmless=30, h3=300, h2=500, ko=900)
HIT = dict(weak=100, h3=300, h2=500, ko=900)
def clear():
    for off in (6, 12, 14, 19): b.w8(DS + off, 0)
    b.w8(DS + 7, 0)
def encore(slot, mvname):
    b.w16(DS + 6, mv(mvname)); b.w8(DS + 12, slot); b.w8(DS + 14, 3)
def taunt(): b.w8(DS + 19, 3)
def row(name, you, ai_hit, spe, moves=None, after=None, foe=None, n=20, **ai):
    fs = HURT[you]
    a = dict(moves=moves or F, spa=HIT[ai_hit], spe=spe, hp=300, maxhp=300); a.update(ai)
    f = dict(moves=F, spa=fs, atk=30, spe=100, hp=300, maxhp=300); f.update(foe or {})
    out = []
    picks = {}
    for nm, m in backs(fs).items():
        L.bench(m); L.side(1, **a); L.side(0, **f); clear()
        if after: after()
        sw = 0
        nb = b.r32(NEWBS)
        for _ in range(n):
            for i in range(2): b.w8(nb + 0x888 + i, 0xFF)
            b.think()
            act, slot, o = b.choice()
            if act == 2: sw += 1
            else: picks[slot] = picks.get(slot, 0) + 1
        out.append(f'{100 * sw // n:3d}')
    clear()
    print(f'{name} | ' + ' | '.join(out) + f' | picks {dict(sorted(picks.items()))}'); sys.stdout.flush()
t0 = time.time()
row('01 you harmless, AI 3HKOs, AI faster', 'harmless', 'h3', FAST)
print('secs per row', int(time.time() - t0)); sys.stdout.flush()
row('02 weak attacks, you harmless', 'harmless', 'weak', SLOW)
row('03 weak attacks, you 3HKO', 'h3', 'weak', SLOW)
row('04 weak attacks, you 2HKO', 'h2', 'weak', SLOW)
row('05 weak attacks, you KO', 'ko', 'weak', SLOW)
row('06 you 3HKO, AI 3HKOs, slower', 'h3', 'h3', SLOW)
row('07 you 3HKO, AI 3HKOs, faster', 'h3', 'h3', FAST)
row('08 you 3HKO, AI 2HKOs, slower', 'h3', 'h2', SLOW)
row('09 you 2HKO, AI 3HKOs, slower', 'h2', 'h3', SLOW)
row('10 you 2HKO, AI 3HKOs, faster', 'h2', 'h3', FAST)
row('11 you 2HKO, AI 2HKOs, slower', 'h2', 'h2', SLOW)
row('12 you 2HKO, AI 2HKOs, faster', 'h2', 'h2', FAST)
row('13 you KO, AI 3HKOs, slower', 'ko', 'h3', SLOW)
row('14 you KO, AI 3HKOs, faster', 'ko', 'h3', FAST)
row('15 you KO, AI 2HKOs, slower', 'ko', 'h2', SLOW)
row('16 you KO, AI 2HKOs, faster', 'ko', 'h2', FAST)
row('17 you KO, AI KOs, slower', 'ko', 'ko', SLOW)
row('18 you KO, AI KOs, faster', 'ko', 'ko', FAST)
E = ['Pound', 'Flamethrower', 'Psychic', 'Dark Pulse']
row('20 Encored strong attack, you harmless', 'harmless', 'h3', SLOW, after=lambda: encore(0, 'Flamethrower'))
row('21 Encored strong attack, you 2HKO', 'h2', 'h3', SLOW, after=lambda: encore(0, 'Flamethrower'))
row('22 Encored strong attack, you KO', 'ko', 'h3', SLOW, after=lambda: encore(0, 'Flamethrower'))
row('23 Encored weak attack, others strong, you harmless', 'harmless', 'h3', SLOW, moves=E, atk=5, after=lambda: encore(0, 'Pound'))
row('24 Encored Swords Dance at +0, you harmless', 'harmless', 'h3', SLOW, moves=['Swords Dance'] + F[:3], atk=100, after=lambda: encore(0, 'Swords Dance'))
row('25 Encored Swords Dance at +6, you harmless', 'harmless', 'h3', SLOW, moves=['Swords Dance'] + F[:3], atk=100, stages={1: 12}, after=lambda: encore(0, 'Swords Dance'))
row('26 Encored Recover at full HP, you harmless', 'harmless', 'h3', SLOW, moves=['Recover'] + F[:3], after=lambda: encore(0, 'Recover'))
row('27 Encored Protect, you harmless', 'harmless', 'h3', SLOW, moves=['Protect'] + F[:3], after=lambda: encore(0, 'Protect'))
row('28 Encored Toxic, you already poisoned', 'harmless', 'h3', SLOW, moves=['Toxic'] + F[:3], foe=dict(status1=8), after=lambda: encore(0, 'Toxic'))
SET = ['Swords Dance', 'Recover', 'Toxic', 'Flamethrower']
row('30 Taunted, 3 status + weak attack', 'harmless', 'weak', SLOW, moves=SET, after=taunt)
row('31 Taunted, 3 status + strong attack', 'harmless', 'h3', SLOW, moves=SET, after=taunt)
row('32 Not Taunted, 3 status + weak attack', 'harmless', 'weak', SLOW, moves=SET)
row('40 weak attacks + Protect in set', 'harmless', 'weak', SLOW, moves=['Protect'] + F[:3])
row('41 weak attacks + U-turn in set', 'harmless', 'weak', SLOW, moves=['U-turn'] + F[:3], atk=5)
row('42 weak attacks + usable status move', 'harmless', 'weak', SLOW, moves=['Toxic'] + F[:3])
row('43 weak attacks, trapped by Mean Look', 'harmless', 'weak', SLOW, status2=0x4000000)
row('44 weak attacks, Mean Look but Ghost type', 'harmless', 'weak', SLOW, status2=0x4000000, t1=7, t2=7)
row('45 you KO, AI at +2 Sp. Atk, slower', 'ko', 'h3', SLOW, stages={4: 8})
row('46 you 2HKO, AI knows Nasty Plot, slower', 'h2', 'h3', SLOW, moves=['Nasty Plot'] + F[:3])
row('47 you KO, AI knows Nasty Plot, slower', 'ko', 'h3', SLOW, moves=['Nasty Plot'] + F[:3])
print('DONE')
L.quit()
