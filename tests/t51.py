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
BUF=0x20233C4+0x200+2
CD=461
FAST, SLOW = 150, 50
HURT = dict(harmless=30, h3=300, h2=500, ko=900)
HIT = dict(weak=100, h3=300, h2=500, ko=900)
def clear():
    for off in (6, 12, 14, 19): b.w8(DS + off, 0)
    b.w16(b.r32(BS)+200+2,0); b.w8(b.r32(NEWBS)+CD+1,0)
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
            else:
                sl=b.r8(BUF); picks[sl]=picks.get(sl,0)+1
        out.append(f'{100 * sw // n:3d}')
    clear()
    print(f'{name} | ' + ' | '.join(out) + f' | picks {dict(sorted(picks.items()))}'); sys.stdout.flush()

def choice(m): b.w16(b.r32(BS)+200+2,mv(m))
def cool(n): b.w8(b.r32(NEWBS)+CD+1,n)
E=['Pound','Flamethrower','Psychic','Dark Pulse']
row('50 Encored Toxic, you healthy','harmless','h3',SLOW,moves=['Toxic']+F[:3],after=lambda:encore(0,'Toxic'))
row('51 Encored Recover, AI at 40pct','harmless','h3',SLOW,moves=['Recover']+F[:3],hp=120,after=lambda:encore(0,'Recover'))
row('52 Encored weak attack, you 3HKO','h3','h3',SLOW,moves=E,atk=5,after=lambda:encore(0,'Pound'))
row('53 Choice locked weak attack, you harmless','harmless','h3',SLOW,moves=E,atk=5,item=186,after=lambda:choice('Pound'))
row('54 Choice locked weak attack, you 3HKO','h3','h3',SLOW,moves=E,atk=5,item=186,after=lambda:choice('Pound'))
row('55 Choice locked strong attack, you harmless','harmless','h3',SLOW,item=186,after=lambda:choice('Flamethrower'))
row('56 Choice locked move that cannot hit you','harmless','h3',SLOW,moves=['Thunderbolt','Flamethrower','Psychic','Dark Pulse'],item=186,foe=dict(t1=4,t2=4),after=lambda:choice('Thunderbolt'))
row('60 just switched in (cooldown 1): weak attacks, you 3HKO','h3','weak',SLOW,after=lambda:cool(1))
row('61 just switched in: you KO, AI slower','ko','h3',SLOW,after=lambda:cool(1))
row('62 just switched in: you 2HKO','h2','h3',SLOW,after=lambda:cool(1))
print('--- scores')
def sc(t,ai,foe):
    a=dict(hp=300,maxhp=300,spe=150,spa=100,atk=100); a.update(ai)
    f=dict(moves=F,spa=30,atk=30,spe=100,hp=300,maxhp=300); f.update(foe)
    L.bench(backs(30)['nothing']); clear()
    r=L.run(a,f,4)
    u=sorted(set(r)); print(t,'style',L.style(),[(m) for m in a['moves']],u[:3]); sys.stdout.flush()
sc('Fell Stinger fast kill',dict(moves=['Fell Stinger','Psychic','Dark Pulse','Thunderbolt'],atk=400),dict(hp=40))
sc('Fell Stinger, no kill',dict(moves=['Fell Stinger','Psychic','Dark Pulse','Thunderbolt'],atk=100),{})
sc('Status hit fast kill, Status style',dict(moves=['Nuzzle','Toxic','Pound','Scratch'],atk=400),dict(hp=40))
sc('Attacks that cannot hit',dict(moves=['Thunderbolt','Thunder','Discharge','Shock Wave']),dict(t1=4,t2=4))
sc('Status on immune',dict(moves=['Thunder Wave','Toxic','Flamethrower','Psychic']),dict(t1=4,t2=4,status1=8))
sc('Absorbed move',dict(moves=['Thunderbolt','Flamethrower','Psychic','Dark Pulse'],spa=300),dict(ability=10))
print('DONE')
L.quit()
