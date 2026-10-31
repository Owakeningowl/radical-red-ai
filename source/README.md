# Radical Red 4.1 AI source

The full AI, decompiled from the v4.1 ROM with Ghidra. 507 functions and about 30,000 lines of C.

The logic is what the ROM does. Names, comments and case labels were added afterwards. Where a function matched the public CFRU code it has its CFRU name. Radical Red's own source is not public, so this is the closest thing to it.

This is decompiler output for reading. It will not compile as it is.

## Files

| File | What is in it |
| --- | --- |
| `ai_master.c` | Picking a move, predicting your move, doubles target choice, the Hardcore re-pick |
| `ai_negatives.c` | Every penalty on a move (`AIScript_Negatives`) |
| `ai_positives.c` | Every bonus on a move (`AIScript_Positives`) |
| `ai_advanced.c` | Styles, setup, protect, phazing, pivots, the score tables per style |
| `ai_switching.c` | Hard switching and scoring back Pokemon |
| `ai_util.c` | KO checks, damage helpers, "bad idea" and "good idea" checks |
| `ai_partner.c` | Scoring moves used on its own partner in doubles |
| `ai_other.c` | Functions in the AI's part of the ROM that didn't match anything public |
| `called_from_ai.c` | Functions in other files that the AI calls directly, like damage and accuracy |
| `FUNCTIONS.tsv` | Every function: ROM address, name, file, and where the name came from |
| `include/rr41_ids.h` | Move, ability, effect and type numbers |

## Where to find each rule

| Rule | Function |
| --- | --- |
| Which AI a trainer uses | `GetAIFlags` |
| Picks the highest score | `ChooseMoveOrAction_Singles` code inside `BattleAI_ChooseMoveOrAction` |
| Doubles target choice | `BattleAI_ChooseMoveOrAction` and `ChooseTarget_Doubles` |
| Guessing your move | `PredictMovesForBanks`, inside `CalculateAIPredictions` |
| A Pokemon's style | `PredictFightingStyle` |
| Fast kill, slow kill, last stand, strongest move | end of `AIScript_Positives` |
| Status move score by style | `IncreaseStatusViability` |
| Setup score by style | `IncreaseStatViability`, `ShouldTryToSetUpStat` |
| Slow kill score by style | `IncreaseViabilityForSlowKOMove` |
| Doubles damage levels | `UpdateBestDoubleKillingMoveScore`, table at ROM `0x93504b0` |
| Penalties doubled in doubles | `DecreaseViability` |
| All hard switch rules, with the 25% skip | `ShouldSwitch` |
| "Weak attacks" rule | `CalcOnlyBadMovesLeftInMoveset` |
| Back Pokemon and post KO scores | `CalcMostSuitableMonToSwitchInto` |
| Hardcore re-pick | `RechooseAIMoveAfterSwitchIfNecessary` |

## Reading it

- `viability` is the score. A move starts at 100, so `IncreaseViability(&viability,9)` is the doc's "+9".
- `style` is the AI's style for the Pokemon. `IncreaseStatusViability(&viability,style,2,...)` adds the amount for that style, with 2 as the base.
- `bankAtk` is the Pokemon choosing, `bankDef` is the target.
- Bit tests look odd, because that is how the CPU does them. `gBattleTypeFlags << 0x1f < 0` means it is a double battle.
- Flag `0x1034` is Hardcore, `0x1032` is Minimal Grinding, `0x1042` is a scripted trial battle.
- Variable names like `uVar3` are the decompiler's. Only the two big scoring functions have renamed variables.

## Limits

- 267 of the 297 functions in the AI's part of the ROM have names. The other 30 are in `ai_other.c`, under `sub_` plus their address.
- 546 calls still go to unnamed helpers, mostly outside the AI.
- 53 calls go through a shared stub whose target couldn't be pinned down. They read `/* A or B */ stub(`.
- Names were matched by comparing code, so a small helper could be misnamed. `FUNCTIONS.tsv` says where each name came from. The logic is unaffected.

## How it was built

From `~/Downloads/radical-red-ai`:

1. `tools/ghidra_prep.py` makes an analysis copy of the ROM with GCC's switch tables resolved.
2. `tools/ghrun.sh` runs Ghidra with `tools/ghscripts/RRDecomp.java`.
3. `tools/rrsrc.py` adds names and writes this folder.

`tools/rrscore.py` compares the scoring with the public code, one move effect at a time.
