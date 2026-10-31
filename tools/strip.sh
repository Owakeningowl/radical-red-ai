#!/bin/zsh
# strip.sh FILE A B : compact source lines A..B for reading
sed -n "$2,$3p" "$1" | sed -e 's://.*$::' -e 's/[[:space:]]*$//' | grep -v '^[[:space:]]*$' | grep -v '^[[:space:]]*[{}][[:space:]]*$' | sed -e 's/^\t\t\t\t\t\t*/\t\t\t\t/' -e 's/\t/ /g' -e 's/INCREASE_STATUS_VIABILITY/+S/g' -e 's/INCREASE_VIABILITY/+V/g' -e 's/AI_THINKING_STRUCT->//g' -e 's/data->//g' -e 's/gBattleMoves\[move\]/M/g' | cut -c1-120
