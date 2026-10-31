#!/bin/zsh
# Decompile the AI. Output goes to rr41_decomp/
R=~/Downloads/radical-red-ai
export JAVA_HOME=$R/tools/dl/jdk25/jdk-25.0.5+8/Contents/Home
export PATH=$JAVA_HOME/bin:$PATH
mkdir -p $R/build/ghproj $R/build/decomp4
cd $R
$R/tools/dl/ghidra/ghidra_12.2_PUBLIC/support/analyzeHeadless $R/build/ghproj rr -import $R/test/rr_gh.gba -overwrite -noanalysis \
  -processor ARM:LE:32:v4t -loader BinaryLoader -loader-baseAddr 0x08000000 -scriptPath $R/tools/ghscripts \
  -postScript RRDecomp.java $R/build/gh.json $R/build/sigs.txt $R/build/decomp4 -deleteProject > $R/build/gh.log 2>&1
grep -E "RRDecomp|decompiled|functions |jump tables|signatures|instructions |ERROR" $R/build/gh.log | tail -30
