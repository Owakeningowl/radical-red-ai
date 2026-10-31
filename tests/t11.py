from lab import *
L = Lab(); b = L.b
print('terrain', b.r8(0x203E028), 'weather', hex(b.r16(0x2023F1C)), 'side', hex(b.r16(0x2023DDE)), hex(b.r16(0x2023DE0)), 'battleflags', hex(b.r32(TF)))
print('statuses3', hex(b.r32(0x2023DFC)), hex(b.r32(0x2023E00)))
print('gRoomOverlay? ', [hex(b.r8(0x203E028+i)) for i in range(-8,9)])
L.quit()
