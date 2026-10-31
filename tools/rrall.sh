#!/bin/zsh
# compile every CFRU source file for function names
cd ~/Downloads/radical-red-ai/rr41
G=/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
F=(-mthumb -mno-thumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mno-long-calls -march=armv4t -w -Os -fira-loop-pressure -fipa-pta -fno-tree-loop-distribute-patterns -iquote . -iquote src)
n=0
for f in src/*.c src/Tables/*.c; do
  b=$(basename $f .c)
  $G -c $F $f -o oall/$b.o 2>/dev/null &
  n=$((n+1))
  if [ $((n % 8)) = 0 ]; then wait; fi
done
wait
ls oall/*.o | wc -l
