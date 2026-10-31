# decode Gen 3 text from the ROM
CH={0:' ',0xAB:'!',0xAC:'?',0xAD:'.',0xAE:'-',0xB0:'…',0xB1:'"',0xB2:'"',0xB3:"'",0xB4:"'",0xB8:',',0xBA:'/',0xF0:':',0xFE:'\n',0xFA:'\n',0xFB:'\n'}
for i in range(26): CH[0xBB+i]=chr(65+i); CH[0xD5+i]=chr(97+i)
for i in range(10): CH[0xA1+i]=str(i)
D=open(__import__('os').path.expanduser('~/Downloads/radical-red-ai/test/rr.gba'),'rb').read()
def text(off,n=300):
    o=[]
    i=off
    while i<off+n:
        c=D[i]
        if c==0xFF: break
        if c==0xFC: i+=2; continue
        if c==0xFD: o.append('{%d}'%D[i+1]); i+=2; continue
        o.append(CH.get(c,'~')); i+=1
    return ''.join(o)
