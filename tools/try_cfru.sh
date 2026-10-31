#!/bin/bash
# try_cfru.sh SHA : download one CFRU commit's source and compile its AI files with inlining on and off
s=$1; r=~/Downloads/radical-red-ai; d=$r/at/$s
if [ ! -d "$d/src/Battle_AI" ] && [ ! -f "$d/src/Battle_AI/ai_master.c" ]; then
  mkdir -p "$d"
  curl -sL "https://codeload.github.com/Skeli789/Complete-Fire-Red-Upgrade/tar.gz/$s" | tar xz -C "$d" --strip-components=1 --include='*/src/*' --include='*/include/*' 2>/dev/null
fi
G=/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
F="-mthumb -mno-thumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mno-long-calls -march=armv4t -w -Os -fira-loop-pressure -fipa-pta -iquote . -iquote src"
mkdir -p "$d/o"
cd "$d" || exit 1
ls src/Battle_AI/ >/dev/null 2>&1 || { echo "no ai dir $s"; ls src | head -3; exit 1; }
for f in src/Battle_AI/*.c; do b=$(basename $f .c); $G -c $F $f -o o/$b.o 2>&1 | grep -m1 error | cut -c1-110 & done; wait
ls o/*.o 2>/dev/null | wc -l
