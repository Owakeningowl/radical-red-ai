from lab import *
L = Lab(); b = L.b
def pred(): 
    v = b.call(0x90db402, 0, 1) & 0xFFFF
    return 'predicted', ('SWITCH' if v == 0xFFFF else MOV.get(str(v), {}).get('name', v)), 'sw', b.call(0x90db424, 0, 1) & 1
foe = dict(moves=['Earthquake', 'Pound', 'Scratch', 'Tackle'], atk=900, spa=900, spe=100)
Q = ['Flamethrower', 'Thunderbolt', 'Psychic', 'Quick Attack']
L.show('slower, foe KOs, priority slot 4', dict(moves=Q, spe=30), foe, 3); print(pred())
L.show('same, priority strongest', dict(moves=['Quick Attack', 'Ember', 'Water Gun', 'Pound'], spe=30, atk=300, spa=10), foe, 3); print(pred())
L.show('same, foe atk 3000', dict(moves=Q, spe=30), dict(foe, atk=3000), 3); print(pred())
L.show('AI low HP 20', dict(moves=Q, spe=30, hp=20), foe, 3); print(pred())
# plain matchup: what does it predict
foe2 = dict(moves=['Tackle', 'Pound', 'Scratch', 'Quick Attack'], atk=30, spa=30, spe=50)
L.show('normal', dict(moves=Q), foe2, 2); print(pred())
foe3 = dict(moves=['Growl', 'Leer', 'Tail Whip', 'Sand Attack'], spe=50)
L.show('foe only has useless moves', dict(moves=Q), foe3, 2); print(pred())
L.quit()
