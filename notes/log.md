# Radical Red 4.1 notes
ROM ~/Downloads/Radicalred.gba: text "Radical Red Version v4.1" at 0x10F6D61. CFRU based. AI script table 0x091491E0: [0] Negatives 0x90c904d [1] SemiSmart 0x90d6999 [2] Positives 0x90d10d5 [29] Roaming 0x90cfe05 [30] Safari 0x90cfe5d [31] FirstBattle 0x90cfead
Hooks: AI_TrySwitchOrUseItem 0x90c802d, GetMostSuitableMonToSwitchInto 0x90d8231, DoAIProcessing 0x90c6f3d, HandleItemUseBeforeAISetup 0x90c7989, OpponentHandleChooseMove 0x9068419, OpponentHandleChoosePokemon 0x9068a29
CFRU source (cfru/, commit b637a27, 2025-01): AI in src/Battle_AI/. Scripts: Negatives, SemiSmart, Positives; AIRandom separate RNG. ShouldSwitch order in CFRU: Absorb, PassOnWish, CanStopLockedMove, Perish, WonderGuard, OnlyBadMoves, NatCure/Regen, SemiInvulnTroll, Yawn, WhileAsleep, SecondaryDamage, AvoidDeath, OffensiveStatsLow, SaveSweeper.
CFRU party score (CalcMostSuitableMonToSwitchInto): KO +31, resist all +17, outspeed +14, revenge kill +8, wall +2, 2HKO +2, weak -1, faints -39, faints but outspeeds -15, remove hazards = max+1. Must VERIFY each in ROM: RR is a modified fork.
Doubles uses type matchups not damage for defensive part. Tools: tools/rr.py, tools/rrmatch.py (build/paired.json, build/names.json).
First matcher pass: 106/338 pairs. key: CalcMostSuitableMonToSwitchInto 0x90d7168, CanKnockOut 0x90dfed4. gcc16 inlines statics, so compile -fno-inline for pairing (build/ni).
ROM map: ShouldSwitch 0x90d824c (6956B, statics inlined). Negatives 0x90c904c-0x90cfe04 (main body 0x90c9252). Partner 0x90cfef4. Positives 0x90d10d4-0x90d6998 (body 0x90d11b4). SemiSmart 0x90d6998. CalcMostSuitable 0x90d7168 (3508B). TrySwitch 0x90c802c. rrdiff.py FILE FUNC START END [--inl] = ordered token diff.
ShouldSwitch ROM vs latest CFRU only 0.38 similar: RR fork differs (FlagGet at top, Random2, GetDoubleKillingScore...). Read ROM directly with tools/rrsum.py.
ROM ShouldSwitch top (0x90d8252...): FlagGet(0x1042) and FlagGet(134?) -> return FALSE. IsTrapped, sky drop -> FALSE. Random2()%4==0 -> return FALSE (needs live test). RR-custom code lives near 0x9350000 (e.g. 0x93508b0, 0x9350ac6). Plan: find CFRU base commit, then read only differences; live test with harness on a COPY of the save.
Base hunt: newest CFRU closest (CalcMost .623 vs .489 mid-2022, others ~.6 noise floor). Stop hunting. at/<sha>/ holds old copies. RR custom code region near 0x9350000: list what AI calls there.
0x93507cc-0x9351600: looks like out-of-line ai_switching statics, not new logic (0x93508b0 ~ TypeAbosorbingSwitchAbilityCheck with Random2%100 < 75 or 25, 0x9350a5e ~ ConfirmAISwitch). 0x93507cc used by Negatives = doubles check on partner's status move. 0x91521d0 = gBattleMoves (repointed). Next: extend matcher to this region. Be economical: user hit usage limit once.
Pairs: 0x93507cc PartnerMoveEffectIsStatusSameTarget, 0x93508b0 TypeAbosorbingSwitchAbilityCheck, 0x9350a5e ConfirmAISwitch, 0x9350ac6 ShouldSwitchIfWonderGuard, 0x9350fbe PredictedMoveWontDoTooMuchToMon, 0x93510ce ShouldSaveChoiceSweeper, 0x9351174 ShouldSaveSweeperForLaterHelper, 0x93511d8 ShouldSwitchToAvoidDeathHelper, 0x9351292 AnnoyingSecondaryDamageSwitchCheck, 0x93513c0 SwitchToBestResistMon, 0x9351510 PickMoveHumanLikelyToChoose. So that region = CFRU functions, NOT RR additions. Party score constants in ROM match CFRU: +14 outspeed, +31 KO, +8 revenge, +22 priority KO.
LIVE HARNESS WORKS: tools/rr_h.py + test/battle.st (real trainer battle, trainer 414 via RAM script, test/t_start.py). Copies only: test/rr.gba, test/rr.sav. BattlePokemon stride 88: hp +40, status1?, flags. ai=*(RES+20): score s8 at ai+4..7 (100 base), aiFlags ai+12 = 0x7 for this trainer. Re-think: COMM[1]=0 path as Parallel. Use random seeds. RNG2 0x20386D0 used by Random2; RNG 0x3005000.
Absorb on Parallel-style differs; CFRU source is base, ROM constants matched for party score.
ROM ShouldSwitch adds at top (not in CFRU source): FlagGet(0x1042) or FlagGet(134) -> no switching; Random2()%4==0 -> no switching this turn (25%): TEST LIVE. Then CFRU order. CFRU Absorb: uses predicted move (not last landed), skips if evasion>=+3, if foe not "damager" class & (just switched or 50%), if AI faster and can KO, etc; 2nd checks; repeat-switch 75/25 chance. Only bad moves: not if just switched in; picks best mon if outspeeds/walls/resists and predicted move won't do too much.
Rethink needs ClearCachedAIData (ai_master.c:1521) before COMM[1]=0.
CFRU switch rules read (see cfru/src/Battle_AI/ai_switching.c): NatCure asleep/frozen always (not badly poisoned!), other status HP>=50; Regenerator HP<=50 & predicted move KOs/2HKOs...; Yawn HP>25% etc; WhileAsleep 50% (75% stays if boosted); Leech 25% non urgent; urgent = cursed, nightmare, toxic counter>6; AvoidDeath: foe predicted move KOs AI, AI not first, HP>20 or perfect switch; new mon must be immune+(outspeeds/walls/resists) or walls/KO+faster & takes little, or foe dies to contact. All through party flags. ROM adds Random2%4 skip to verify.
Trainer flags 0x7 seen. Status offsets vanilla: status1 +76, status2 +80, stride 88.
gNewBS byte +233 bit7 = calculatedAIPredictions; CalculateAIPredictions 0x90c7b8c; ClearCachedAIData likely 0x9074950. think must clear both for valid tests. LoadPartyRange 0x9074010.
LIVE (controlled, strong AI, test/t3.py, random seeds): no reason 1/12 switch; Cursed 29/40 (72%, predicts 75 = 100 x skip); Leech 7/40 (18%, predicts 25x.75=19); Toxic counter 7: 33/40 (82, predicts 75); Toxic counter 3: 0/20; Asleep 13/30 (43, predicts 50x.75=38). Confirms ROM's Random2%4 skip = 25% no switching.

## 2026-10-31 live findings (harness fixed)
- Real ClearCachedAIData = 0x90c8ba4 (0x9074950 was wrong). Style cache gNewBS+0x888+bank. type3 = BM+24, stat stages start at BM+25.
- Every trainer battle: AI flags forced to 7 (GetAIFlags ROM `lsls 28; bmi -> 7`); table value ignored. No difficulty split in AI.
- Flag 0x1042 = scripted "trial" battle (no switching).
- AI assumes a 93% damage roll: thresholds measured (Flamethrower raw 41 -> 38, EQ raw 46 -> 42).
- IsValidMovePrediction = 0x90db402(foe,ai), IsPredictedToSwitch = 0x90db424. names.json has mislabels; check before calling.
- RR changes confirmed: IncreaseStatusViability Setup class = 3+boost (if foe can't 2HKO); Reflect/Light Screen for screens class = +15; one screen move is enough for screens class; 25% skip of switching in singles and doubles.
- Doubles table 0x93504b0 equals source. gChosenMovesByBanks 0x2023DC4 must be cleared in tests (partnerHandling).
- Test states: test/battle.st (Brock, singles, sandstorm active - Lab clears it), test/dbl.st (Sabrina 420 doubles).
- notes/matrix.txt = live scores: 36 moves x 9 styles x 6 situations.

## final tests
r16/r17/r22/r23/r26/matrix in notes/. Real ClearMonCachedDamageCalcs = 0x90c8ed0. All switch-in scores confirmed live incl. 70 max case.
Switching stays near 75% for every "always" rule (25% skip). No re-choosing after player switches (ClearCached has one caller). Boss items are Mega Ring/Z-Power Ring; some trainers (Terry rival, Elite 4, Giovanni) also hold Full Restore.

## Hardcore and the hidden rules (2026-10-31)
- Flag 0x1034 = Hardcore (script sets it with 0x1032 = Minimal Grinding). The user's save has both on. 0x1042 = scripted trial battle.
- RechooseAIMoveAfterSwitch = 0x90c8f04 (battle script callasm pointer at 0x90096a3): only if 0x1034 on, 0x1042 off. Calls 0x90c8ca4(aiBank, playerBank).
- 0x90c8ca4: count = switchesInARow[player] at gNewBS+469+bank. >=9: Random%4==0, >=12: %3, >=16: %2 flags cheese. Else/also: secondPreviousMonIn[player] (gNewBS+477+bank) == current party index. Not if Yawned. Picks a new move with fresh caches, not Pursuit.
- OnlyBadMoves real rule: strongest attack does under 1/3 of your HP counts as bad (no pivot, no Protect in moveset). That is the "75% with no coin". Save sweeper coin path measured 40-47% vs 37.5 expected; fine.

## Source rebuild status
- rr41/ = copy of cfru src+include with FROSTBITE on. tools/rrv.py build/map/report/show, tools/rrcalls.py NAME.
- Token compare finds real RR differences (ShouldProtect lost some checks) mixed with inlining noise. ABILITY() is a real function in the ROM at 0x90757d0.
- No decompiler or Java on this Mac. Asked the user about Ghidra.

## Findings from the decompile (ROM truth)
- DecreaseViability doubles penalties in double battles.
- Thunder Wave: -2 if AI team's average speed > yours (GetPokemonOnSideSpeedAverage). Has Rest branch.
- Recoil-if-miss penalty below 70 accuracy (doc said 75).
- Taunt: flat +8 if target has any status move, plus S3 when predicted status or good-to-taunt style.
- Move 0x31c trap: +4, +8 if target Water or Steel, unless already flagged (RR custom, salt cure style).
- Flag 0x10C0 is debug only. VarGet(0x5119) values seen 16 and 18 in Negatives; meaning TBD.
- Negatives switch is on moveEffect-1, three table copies. 147/167 effects same score events as public.
- Rain Dance/Sunny Day usefulness check always passes: the move itself is Water/Fire type and MoveTypeInMoveset(AI, type) sees it.
- Var 0x5119 is set before boss fights (Brock 4, Surge 3, Sabrina 2, Koga 5, Lance 8, Jasmine 9, Terry 21/23/26). Checked for 16 (Sap Sipper case) and 18 (hazard removal, Yawn area) in Negatives.
- Hazards in ROM, singles: if you have under 4 Pokemon, or Magic Bounce: skips all later penalty checks. Else if you know Rapid Spin (AI not Ghost) / Defog / Magic Coat: 50% -10. HasUsedMove(Rapid Spin effect): 50% -9.

## 2026-10-31 PAUSED by user (doc rewrite for nuzlockers). Findings not yet in doc/doc.txt:
Plan: rewrite doc.txt around the user's questions: when does it switch, who comes in post KO, what move, anti-abuse (Hardcore re-pick), Encore/2HKO timing, "back mon can X, can it still switch" grid, max/lowest score reference, doubles picture guide with SVG arrows. Old detail goes in collapsed sections. Raw results: notes/r41.txt r44.txt r50.txt r51.txt r52.txt.
Scores: floor -100 (blocked moves: no PP, Encored away, Taunted status, Disabled), hard cap +155. Singles top +18 (Fell Stinger fast KO, live), normal top +15. Doubles top +19, Pledge +20 plus level = about +31 (read only). Immune attack is -15 (live), NOT "never clicked": fix doc lines 53 and 156.
Back mon grid (singles, 75% = rule fires): nothing/slow KO without resist/fast KO that dies to you = 0 always. Faster and safe: weak attacks only. Walls: weak attacks if you can 3HKO the AI; you KO and AI slower. Resists: weak attacks if you can 3HKO; you 2HKO 37 (AI 3HKOs you) or 19 (AI 2HKOs you); you KO either speed. Resists and KOs you: 75 on any turn unless AI has a fast kill. Fast kill and safe: weak attacks; you KO. AI knows usable setup move: 0 when you can't KO it. Old doc "Weak attacks" back mon list is wrong, replace it.
Encore: strong attack changes nothing; weak attack = weak rule; status that still works (Toxic healthy, Recover hurt) stays; dead status (Swords Dance, Recover full HP, Toxic on poisoned) 75 with faster/walls/resists/fast kill; Protect 0. Taunt + weak attack 75 with faster or fast kill. Choice locked weak or can't hit: 75 with any back mon that survives and is safe, even slow KO. Encore does not trap. No turn counter, rolls 75% each turn. Cooldown after AI switch: 0 switches that next turn (live).
2HKO answer: usually stays while you only 2HKO, switches once you can KO it (after one hit).
Doubles target: no slot bias, no super effective bonus. Attacking styles: KO 100 (160/160); KO beats SE (60/60); both KOable, foe that can KO AI 100 (60/60), else coin flip (57/43, 71/89); no KO, both take 50%+, foe that can KO AI 100 (160/160); no KO, more % max HP 63/37 (154/240, 151/240, even when other foe is SE). Support styles Utility, Phazer, Team Support: coin flip even with a KO (83/77, 51/49), because levels 5 and 6 score the same. Immune to all 100 other foe (48/48). Partner KOing a foe: other foe 60/60. Spread 1/3+ max HP on both beats single target KO (60/60); spread under 1/3 loses. Only the best move per target gets the level score. AI picks Earthquake even if it would KO its own partner (40/40). Damage for tie breaks is capped at target's current HP. Spread damage is 0.75x.
Doubles switching: needs weak attacks vs BOTH foes plus same back mon rules (faster 83, walls/resists 75 if you can 3HKO); you KO or 2HKO = 0. Post KO in doubles: scores ADD over both foes, faint only -1 (W1-W5 live, read incoming from bs+92+1). Old doc line "type matchups instead of damage" is wrong.
Prediction ties: when your attacks tie for damage, the AI picks what a human would: useful side effect, then your last move that landed on it, then super effective over not, then STAB, then base power, then random (PickMoveHumanLikelyToChoose 0x9351510). Doc says random: fix. playerSwitchedCount affects Pursuit.
Also pending: readable patched source in rr41/src (not started beyond measuring: 267 paired, 97 identical).

## 2026-10-31 "resists you" (t55 singles, t56 doubles)
Singles: damage based (none of your moves 3HKO it, after hazards, Wish, Leftovers-type healing, Multiscale, Disguise). Bulky Normal type beat frail Water type vs Fire moves, 38 of 38 switches.
Doubles with 2+ of your Pokemon alive (ViableMonCountFromBank(foe) != 1): type based only (AI_TypeCalc). Frail Water type beat bulky Normal, 33 of 33. No faint penalty in that path. Old W1-W5 claim (62 vs 45) was explained wrong: D won on the type path for another reason, so the doc no longer cites it.
