// ai_positives.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- AIScript_Positives  (ROM 0x90d10d4)
u8 AIScript_Positives(u8 bankAtk,u8 bankDef,u16 originalMove,u8 originalViability,AIScript *data)

{
  u16 defSpeed;
  ushort uVar1;
  bool bVar2;
  u8 style;
  u8 uVar4;
  byte moveEffect;
  bool8 bVar6;
  u8 uVar7;
  bool8 bVar8;
  move_t move;
  u16 move;
  move_t mVar10;
  ushort uVar11;
  u16 uVar12;
  uint bankAtk_;
  uint predictedMove;
  u8 *timers;
  uint atkAbility;
  int moveSplit;
  uint moveType;
  int iVar18;
  int iVar19;
  undefined4 uVar20;
  int iVar21;
  u8 extraout_r1;
  u8 extraout_r1_00;
  u8 extraout_r1_01;
  u8 sideAtk;
  bool8 extraout_r1_02;
  bool8 extraout_r1_03;
  u8 extraout_r1_04;
  u8 extraout_r1_05;
  u8 extraout_r1_06;
  byte checkConfusion;
  bool8 checkConfusion_00;
  bool8 checkConfusion_01;
  u8 extraout_r1_07;
  BattlePokemon *bankDef_;
  u8 uVar23;
  BattlePokemon *pBVar24;
  uint uVar25;
  uint defAbility;
  BattlePokemon *pBVar27;
  uint uVar28;
  int iVar29;
  byte *pbVar30;
  undefined8 uVar31;
  uint uStack_4c;
  uint move;
  uint uStack_38;
  undefined1 uStack_1d;
  ushort viability;
  ushort auStack_1a [3];
  
  bankDef_ = (BattlePokemon *)(uint)bankDef;
  bankAtk_ = (uint)bankAtk;
  move = IsValidMovePrediction(bankDef,bankAtk);
  predictedMove = move;
  style = GetBankFightingStyle(bankAtk);
  timers = (u8 *)(uint)style;
  uStack_38._0_2_ = (ushort)originalViability;
  viability = (ushort)uStack_38;
  move = TryReplaceMoveWithZMove(bankAtk,bankDef,originalMove);
  move = move;
  uVar4 = GetAIAbility(bankAtk,bankDef,move);
  atkAbility = (uint)uVar4;
  uVar4 = GetAIAbility(bankDef,bankAtk,move);
  moveSplit = IsTargetAbilityIgnored((uint)uVar4,atkAbility,move);
  pBVar24 = (BattlePokemon *)(move * 0xc);
  defAbility = (uint)uVar4 & -(uint)(moveSplit == 0);
  moveEffect = gBattleMoves[move].effect;
  moveType = GetMoveTypeSpecial(bankAtk_,move);
  moveSplit = CalcMoveSplit(bankAtk_,move);
  pBVar27 = (BattlePokemon *)(gBattleTypeFlags << 0x1f);
  if ((int)pBVar27 < 0) {
    if ((gBattleMons[data->foe1].hp == 0) ||
       (pBVar24 = gBattleMons + data->foe2, gBattleMons[data->foe2].hp == 0)) {
      pBVar24 = (BattlePokemon *)((uint)data->bankAtkPartner * 0x58);
      pBVar27 = 0x0;
      if (gBattleMons[data->bankAtkPartner].hp == 0) goto LAB_090d11c4;
    }
    pBVar27 = (BattlePokemon *)(uint)data->bankAtkPartner;
    if (pBVar27 == bankDef_) {
      style = AIScript_Partner(bankAtk,bankDef,originalMove,originalViability,data);
      return style;
    }
  }
LAB_090d11c4:
  bVar6 = (bool8)pBVar27;
  iVar18 = IsAnyMaxMove(move);
  checkConfusion = extraout_r1;
  if (iVar18 != 0) {
    pBVar24 = bankDef_;
    moveEffect = GetAIMoveEffectForMaxMove(move,bankAtk,bankDef);
    checkConfusion = extraout_r1_00;
  }
  uVar11 = viability;
  uVar23 = (u8)pBVar24;
  uVar4 = (u8)defAbility;
  if (moveEffect < 0xf3) {
                        switch(moveEffect) {
    case 6: /* EFFECT_PARALYZE_HIT */
      move = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x4a < move) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))
      goto sw_d11e4_67;
      break;
    case 67: /* EFFECT_PARALYZE */
    case 4:
    case 3:
sw_d11e4_67:
      bVar6 = BadIdeaToParalyze(bankDef,bankAtk);
      if ((bVar6 == 0) &&
         (bVar6 = IncreaseViabilityForSpeedControl(&viability,style,bankAtk,bankDef),
         bVar6 == 0)) {
        if ((((data->defSpeed < data->atkSpeed) || (data->atkSpeed <= data->defSpeed >> 1)) &&
            (bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects(bankAtk,bankDef), bVar6 == 0))
           && ((((-1 < (int)(gBattleTypeFlags << 0x1f) ||
                 (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                  (gBattleMons[data->bankAtkPartner].hp == 0)))) ||
                (bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects
                                   (data->bankAtkPartner,bankDef), bVar6 == 0)) &&
               (((bVar6 = FlinchingMoveInMoveset(bankAtk), bVar6 == 0 &&
                 ((data->defStatus2 & 0xf0000) == 0)) &&
                (iVar18 = func_0x09075a44(bankDef_), iVar18 == 0)))))) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
        else {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      break;
    case 4: /* EFFECT_BURN_HIT */
      move = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x4a < move) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))
      goto sw_d11e4_167;
      break;
    case 167: /* EFFECT_WILL_O_WISP */
    case 2:
    case 1:
sw_d11e4_167:
      bVar6 = BadIdeaToBurn(bankDef,bankAtk);
      if (bVar6 == 0) {
        bVar6 = IsClassDoublesUtility(style);
        if (((bVar6 == 0) && (bVar6 = IsClassDoublesTeamSupport(style), bVar6 == 0)) ||
           (bVar6 = PhysicalMoveInMoveset(bankDef), bVar6 == 0)) {
          iVar18 = CalcMoveSplit(bankDef_,predictedMove);
          if ((iVar18 == 0) && (bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,1), bVar6 != 0)) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
          else {
            bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects(bankAtk,bankDef);
            if ((bVar6 == 0) &&
               ((((-1 < (int)(gBattleTypeFlags << 0x1f) ||
                  (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                   (gBattleMons[data->bankAtkPartner].hp == 0)))) ||
                 (bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects
                                    (data->bankAtkPartner,bankDef), bVar6 == 0)) &&
                ((iVar18 = MoveInMoveset(0x2f1 /* InfernoMarch */,bankAtk_), iVar18 == 0 &&
                 (bVar6 = PhysicalMoveInMoveset(bankDef), bVar6 == 0)))))) {
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
            else {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
          }
        }
        else {
          bVar6 = IsClassDoublesUtility(style);
          if (bVar6 == 0) {
            IncreaseViability(&viability,0xb);
          }
          else {
            IncreaseViability(&viability,0xb);
          }
        }
      }
      break;
    case 2: /* EFFECT_POISON_HIT */
    case 209: /* EFFECT_BAD_POISON_HIT */
      move = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x4a < move) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))
      goto sw_d11e4_33;
      break;
    case 33: /* EFFECT_TOXIC */
    case 66: /* EFFECT_POISON */
    case 1:
    case 0:
    case 4:
sw_d11e4_33:
      iVar18 = BadIdeaToPoison(bankDef_,bankAtk_);
      if (iVar18 == 0) {
        iVar18 = MoveInMoveset(0x1a6 /* Venoshock */,bankAtk_);
        if (((iVar18 == 0) && (iVar18 = MoveInMoveset(0x2f4 /* Barb Barrage */,bankAtk_), iVar18 == 0)) &&
           (atkAbility != 200 /* Merciless */)) {
          bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects(bankAtk,bankDef);
          if ((((bVar6 == 0) &&
               ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
                ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                  (gBattleMons[data->bankAtkPartner].hp == 0)) ||
                 (bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects
                                    (data->bankAtkPartner,bankDef), bVar6 == 0)))))) ||
              (bVar6 = MoveEffectInMoveset(0xa7 /* EFFECT_WILL_O_WISP */,bankAtk), bVar6 == 0)) ||
             (((bVar6 = PhysicalMoveInMoveset(bankDef), bVar6 != 0 &&
               (bVar6 = BadIdeaToBurn(bankDef,bankAtk), bVar6 == 0)) && (defAbility != 0x12 /* Flash Fire */)))) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
          else {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      break;
    case 5: /* EFFECT_FREEZE_HIT */
      move = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x4a < move) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0)) {
sw_d55da_3:
        iVar18 = sub_90db3e8(bankDef_,bankAtk_);
        if (iVar18 == 0) {
          bVar6 = IsClassDoublesUtility(style);
          if (((bVar6 == 0) && (bVar6 = IsClassDoublesTeamSupport(style), bVar6 == 0)) ||
             (bVar6 = SpecialMoveInMoveset(bankDef), bVar6 == 0)) {
            iVar18 = CalcMoveSplit(bankDef_,predictedMove);
            if ((iVar18 == 1) && (bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,1), bVar6 != 0)) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
            else {
              bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects(bankAtk,bankDef);
              if (((bVar6 == 0) &&
                  (((-1 < (int)(gBattleTypeFlags << 0x1f) ||
                    (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                     (gBattleMons[data->bankAtkPartner].hp == 0)))) ||
                   (bVar6 = DoubleDamageWithStatusMoveInMovesetThatAffects
                                      (data->bankAtkPartner,bankDef), bVar6 == 0)))) &&
                 ((iVar18 = MoveInMoveset(0x2f6 /* BitterMalice */,bankAtk_), iVar18 == 0 &&
                  (bVar6 = SpecialMoveInMoveset(bankDef), bVar6 == 0)))) {
                IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
              }
              else {
                IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
              }
            }
          }
          else {
            bVar6 = IsClassDoublesUtility(style);
            if (bVar6 == 0) {
              IncreaseViability(&viability,0xb);
            }
            else {
              IncreaseViability(&viability,0xb);
            }
          }
        }
      }
      break;
    case 7: /* EFFECT_EXPLOSION */
      if ((predictedMove != 0 /* - */) && (gBattleMoves[predictedMove].effect != 0x6f /* EFFECT_PROTECT */)) {
        if (data->atkItemEffect == 0x5e) {
          if (data->atkItemQuality != moveType) goto LAB_090d180e;
          IncreaseViability(&viability,4);
        }
        else if ((data->atkItemEffect == 0x60) && (moveType = func_0x090dd734(bankAtk_), moveType < 0x1a))
        {
          IncreaseViability(&viability,4);
        }
        else {
LAB_090d180e:
          bVar6 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1);
          if (bVar6 == 0) {
            if (data->atkSpeed < data->defSpeed) {
              bVar6 = Can2HKO(bankAtk,bankDef);
              if (bVar6 != 0) {
                bVar6 = Can2HKO(bankDef,bankAtk);
                goto LAB_090d1846;
              }
            }
            else {
              bVar6 = Can2HKO(bankAtk,bankDef);
              if (bVar6 != 0) {
                bVar6 = CanKnockOut(bankDef,bankAtk);
LAB_090d1846:
                if (bVar6 == 0) break;
              }
            }
            IncreaseViability(&viability,4);
          }
          else {
            iVar18 = sub_90dd85a(bankDef_);
            if (iVar18 != 0) {
              IncreaseViability(&viability,4);
            }
          }
        }
      }
      break;
    case 140: /* EFFECT_ALL_STATS_UP_HIT */
      if (((move == 0x379 /* Z-Move 42 */) || (move == 0x37f /* Z-Move 48 */)) &&
         ((iVar18 = AI_SpecialTypeCalc(move,bankAtk_,bankDef_), iVar18 << 0x1c < 0 ||
          (((iVar18 = func_0x090db548(bankDef_,bankAtk_), iVar18 == 0 && (atkAbility != 0xbf /* Contrary */)) &&
           (defAbility != 0x8d /* Unaware */)))))) {
        IncreaseViability(&viability,5);
      }
      break;
    case 9: /* EFFECT_MIRROR_MOVE */
      if (move == 0x1c8 /* Copycat */) {
        bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
        if ((bVar6 == 0) && (predictedMove != 0 /* - */)) {
          iVar18 = CheckTableForMove(predictedMove,&UNK_0903f95e);
          if ((iVar18 == 0) && (iVar18 = MoveInMoveset(predictedMove,bankAtk_), iVar18 == 0))
          goto LAB_090d1956;
        }
        else if ((((ushort)(*(short *)(gNewBS + 0xec) - 1U) < 0xfffe) &&
                 (iVar18 = CheckTableForMove(*(short *)(gNewBS + 0xec),&UNK_0903f95e), iVar18 == 0))
                && (iVar18 = MoveInMoveset(*(undefined2 *)(gNewBS + 0xec),bankAtk_), iVar18 == 0)) {
          uVar11 = *(ushort *)(gNewBS + 0xec);
          goto LAB_090d1924;
        }
      }
      else {
        uVar11 = gBattleStruct->lastTakenMoveFrom[bankAtk_ - 3][(int)((int)bankDef_->moves + 1)];
        if (uVar11 != 0) goto LAB_090d1924;
      }
      break;
    case 10: /* EFFECT_ATTACK_UP */
      if (move == 0x199 /* Hone Claws */) {
        if (atkAbility != 0xbf /* Contrary */) {
          bVar6 = RealPhysicalMoveInMoveset(bankAtk);
          if ((bVar6 != 0) && (bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,1), bVar6 != 0))
          goto LAB_090d19f6;
          goto LAB_090d19b8;
        }
      }
      else if (atkAbility != 0xbf /* Contrary */) {
LAB_090d1a1e:
        uVar23 = 1;
        goto LAB_090d1a2e;
      }
      break;
    case 50: /* EFFECT_ATTACK_UP_2 */
      if (atkAbility != 0xbf /* Contrary */) {
        uVar23 = 2;
LAB_090d1a2e:
        bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,uVar23);
        if (bVar6 != 0) {
LAB_090d19f6:
          IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,1,8);
        }
      }
      break;
    case 11: /* EFFECT_DEFENSE_UP */
sw_d11e4_11:
      uVar23 = 1;
      if (atkAbility != 0xbf /* Contrary */) {
LAB_090d1a4a:
        bVar6 = GoodIdeaToRaiseDefenseAgainst(bankAtk,bankDef,uVar23);
        if (bVar6 != 0) goto LAB_090d1a5a;
      }
      break;
    case 51: /* EFFECT_DEFENSE_UP_2 */
      if (atkAbility != 0xbf /* Contrary */) {
        uVar23 = 2;
        goto LAB_090d1a4a;
      }
      break;
    case 13: /* EFFECT_SPECIAL_ATTACK_UP */
      if ((move == 0x19e /* Work Up */) || (move == 0x4a /* Growth */)) {
LAB_090d1ab0:
        bVar6 = RealPhysicalMoveInMoveset(bankAtk);
        if ((bVar6 != 0) && (bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,1), bVar6 != 0))
        goto LAB_090d19f6;
        bVar6 = SpecialMoveInMoveset(bankAtk);
        if (bVar6 == 0) break;
      }
      else if (atkAbility == 0xbf /* Contrary */) break;
      uVar23 = 1;
LAB_090d1aca:
      bVar6 = GoodIdeaToRaiseSpAttackAgainst(bankAtk,bankDef,uVar23);
      if (bVar6 != 0) {
LAB_090d1ada:
        IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,4,8);
      }
      break;
    case 53: /* EFFECT_SPECIAL_ATTACK_UP_2 */
      if (atkAbility != 0xbf /* Contrary */) {
LAB_090d1b26:
        uVar23 = 2;
        goto LAB_090d1aca;
      }
      break;
    case 14: /* EFFECT_SPECIAL_DEFENSE_UP */
sw_d11e4_14:
      if (atkAbility != 0xbf /* Contrary */) {
LAB_090d1b34:
        uVar23 = 1;
LAB_090d1b36:
        bVar6 = GoodIdeaToRaiseSpDefenseAgainst(bankAtk,bankDef,uVar23);
        if (bVar6 != 0) {
          IncreaseStatViability(&viability,style,1,bankAtk,bankDef,move,5,10);
        }
      }
      break;
    case 54: /* EFFECT_SPECIAL_DEFENSE_UP_2 */
      uVar23 = 2;
      if (atkAbility != 0xbf /* Contrary */) goto LAB_090d1b36;
      break;
    case 52: /* EFFECT_SPEED_UP_2 */
      if (atkAbility != 0xbf /* Contrary */) {
        defSpeed = data->defSpeed;
        uVar12 = data->atkSpeed;
        uVar23 = 2;
LAB_090d2236:
        bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,uVar23,uVar12,defSpeed);
        if (bVar6 != 0) goto LAB_090d2246;
      }
      break;
    case 15: /* EFFECT_ACCURACY_UP */
      if (atkAbility != 0xbf /* Contrary */) {
LAB_090d19b8:
        uVar23 = 1;
LAB_090d19ba:
        bVar6 = GoodIdeaToRaiseAccuracyAgainst(bankAtk,bankDef,uVar23);
        if (bVar6 != 0) {
          IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,6,0xc);
        }
      }
      break;
    case 55: /* EFFECT_ACCURACY_UP_2 */
      if (atkAbility != 0xbf /* Contrary */) {
        uVar23 = 2;
        goto LAB_090d19ba;
      }
      break;
    case 16: /* EFFECT_EVASION_UP */
      if ((((move == 0x1e3 /* Acupressure */) && ((BattlePokemon *)(uint)data->bankAtkPartner != bankDef_)) &&
          (atkAbility != 0xbf /* Contrary */)) && (bVar6 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef,1), bVar6 == 0)) {
        IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,0xfe,0xc);
      }
      break;
    case 208: /* EFFECT_BULK_UP */
      if (atkAbility != 0xbf /* Contrary */) {
        bVar6 = RealPhysicalMoveInMoveset(bankAtk);
        if ((bVar6 != 0) &&
           (bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,(move == 0x2f0 /* VictoryDance */) + 1),
           bVar6 != 0)) goto LAB_090d19f6;
        bVar6 = GoodIdeaToRaiseDefenseAgainst(bankAtk,bankDef,1);
        if (bVar6 != 0) {
          IncreaseStatViability(&viability,style,1,bankAtk,bankDef,move,2,8);
        }
      }
      break;
    case 211: /* EFFECT_CALM_MIND */
      if (atkAbility != 0xbf /* Contrary */) {
        if (move == 0x19f /* Quiver Dance */) {
          if (defAbility != 0xe8 /* Dancer */) {
            bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,2,data->atkSpeed,data->defSpeed);
            if (bVar6 != 0) goto LAB_090d2246;
            goto LAB_090d1d5e;
          }
          break;
        }
        if (move == 0x1dd /* Geomancy */) {
          if (((data->atkItemEffect != 0x7e) &&
              (((((iVar18 = IsTypeZCrystal(data->atkItem,0x17), iVar18 == 0 ||
                  (iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0)) ||
                 (*(char *)(gNewBS + bankAtk_ + 0x194) != '\0')) &&
                (bVar6 = IsBankIncapacitated(bankDef), bVar6 == 0)) &&
               ((bVar6 = CanKnockOut(bankDef,bankAtk), bVar6 != 0 ||
                (iVar18 = func_0x090db1c4(bankDef_), iVar18 == 0)))))) ||
             (bVar6 = PhazingMoveInMovesetThatAffects(bankDef,bankAtk), bVar6 != 0)) break;
          bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,2,data->atkSpeed,data->defSpeed);
          if (bVar6 != 0) goto LAB_090d2246;
          bVar6 = GoodIdeaToRaiseSpAttackAgainst(bankAtk,bankDef,2);
          if (bVar6 == 0) {
            bVar6 = GoodIdeaToRaiseSpDefenseAgainst(bankAtk,bankDef,2);
            if (bVar6 != 0) {
              IncreaseStatViability(&viability,style,1,bankAtk,bankDef,0x1dd,5,8);
            }
            break;
          }
        }
        else {
LAB_090d1d5e:
          bVar6 = GoodIdeaToRaiseSpAttackAgainst(bankAtk,bankDef,1);
          if (bVar6 == 0) {
            bVar6 = GoodIdeaToRaiseSpDefenseAgainst(bankAtk,bankDef,1);
            if (bVar6 != 0) {
              IncreaseStatViability(&viability,style,1,bankAtk,bankDef,move,5,8);
            }
            break;
          }
        }
        goto LAB_090d1ada;
      }
      break;
    case 212: /* EFFECT_DRAGON_DANCE */
      if (move == 0x1c4 /* Shell Smash */) {
        if (atkAbility != 0xbf /* Contrary */) {
          bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,2,data->atkSpeed,data->defSpeed);
          if (bVar6 == 0) {
            bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,2);
            if (bVar6 != 0) goto LAB_090d19f6;
            goto LAB_090d1b26;
          }
          goto LAB_090d2246;
        }
LAB_090d1fbe:
        bVar6 = GoodIdeaToRaiseDefenseAgainst(bankAtk,bankDef,1);
        if (bVar6 == 0) goto LAB_090d1b34;
LAB_090d1a5a:
        if (bVar6 == 1) {
          IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,1,10);
        }
        else {
          IncreaseStatViability(&viability,style,1,bankAtk,bankDef,move,2,8);
        }
      }
      else {
        if (atkAbility == 0xbf /* Contrary */) break;
        bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,1,data->atkSpeed,data->defSpeed);
        if (bVar6 == 0) goto LAB_090d1a1e;
LAB_090d2246:
        IncreaseStatViability(&viability,style,3,bankAtk,bankDef,move,3,8);
      }
      break;
    case 207: /* EFFECT_EXTREME_EVOBOOST */
      iVar18 = func_0x090db548(bankDef_,bankAtk_);
      if (iVar18 == 0) {
        uVar11 = uVar11 & 0xff;
        if (move == 0x2b3 /* Clang Soul */) {
          bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,1);
          if ((bVar6 == 0) &&
             ((bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,3), bVar6 == 0 ||
              (bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,2), bVar6 != 0)))) {
LAB_090d1e30:
            if (((atkAbility != 0xbf /* Contrary */) &&
                ((bVar6 = RealPhysicalMoveInMoveset(bankAtk), bVar6 == 0 ||
                 (IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,1,8),
                 viability == uVar11)))) &&
               ((bVar6 = SpecialMoveInMoveset(bankAtk), bVar6 == 0 ||
                (IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,4,8),
                viability == uVar11)))) {
              IncreaseStatViability(&viability,style,3,bankAtk,bankDef,move,3,8);
            }
          }
        }
        else if (move == 0x377 /* Z-Move 40 */) {
          iVar18 = 1;
          do {
            IncreaseStatViability(&viability,style,3,bankAtk,bankDef,0x377,(u8)iVar18,0xc);
            if (viability != uVar11) break;
            iVar18 = iVar18 + 1;
          } while (iVar18 != 6);
        }
        else if (move == 0x2aa /* No Retreat */) goto LAB_090d1e30;
      }
      break;
    case 156: /* EFFECT_DEFENSE_CURL */
      bVar6 = MoveEffectInMoveset(0x75 /* EFFECT_ROLLOUT */,bankAtk);
      if ((bVar6 == 0) || ((int)(data->atkStatus2 << 1) < 0)) goto sw_d11e4_11;
      IncreaseStatViability(&viability,style,5,bankAtk,bankDef,move,2,0xc);
      break;
    case 174: /* EFFECT_CHARGE */
      iVar18 = sub_90dc84c(bankAtk_,bankDef_,0xd);
      if (iVar18 == 0) goto sw_d11e4_14;
      IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      break;
    case 160: /* EFFECT_STOCKPILE */
      bVar6 = MoveEffectInMoveset(0xa2 /* EFFECT_SWALLOW */,bankAtk);
      if ((bVar6 == 0) && (bVar6 = MoveEffectInMoveset(0xa1 /* EFFECT_SPIT_UP */,bankAtk), bVar6 == 0))
      goto sw_d11e4_206;
      IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      break;
    case 206: /* EFFECT_COSMIC_POWER */
sw_d11e4_206:
      if (atkAbility != 0xbf /* Contrary */) goto LAB_090d1fbe;
      break;
    case 20: /* EFFECT_SPEED_DOWN */
      bVar6 = GoodIdeaToLowerSpeed(bankDef,bankAtk,move,1);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 60: /* EFFECT_SPEED_DOWN_2 */
      bVar6 = GoodIdeaToLowerSpeed(bankDef,bankAtk,move,2);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 205: /* EFFECT_TICKLE */
      bVar6 = GoodIdeaToLowerAttack(bankDef,bankAtk,move);
      if ((bVar6 != 0) || (bVar6 = GoodIdeaToLowerDefense(bankDef,bankAtk,move), bVar6 != 0)) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 25: /* EFFECT_HAZE */
      bVar6 = ShouldPhaze(bankAtk,bankDef,move,style);
      if (bVar6 == 0) {
        uVar23 = CountUsefulDebuffs(bankAtk);
        if (uVar23 != 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else {
        bVar6 = IsClassDoublesPhazer(style);
        if (bVar6 == 0) {
          bVar6 = IsClassPhazer(style);
          if (bVar6 == 0) {
            bVar6 = IsClassDoublesSetupAttacker(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0xc);
            }
          }
          else {
            IncreaseViability(&viability,8);
          }
        }
        else {
          IncreaseViability(&viability,0xf);
        }
      }
      break;
    case 28: /* EFFECT_ROAR */
      iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
      if ((iVar18 == 0) && (bVar6 = ShouldPhaze(bankAtk,bankDef,move,style), bVar6 != 0)) {
        bVar6 = IsClassDoublesPhazer(style);
        if (bVar6 == 0) {
          bVar6 = IsClassPhazer(style);
          if (bVar6 == 0) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
          else {
            bVar6 = CanKnockOut(bankDef,bankAtk);
            if ((bVar6 == 0) || ((byte)gBattleMoves[move].priority < 0x80)) {
              IncreaseViability(&viability,8);
            }
            else {
              IncreaseViability(&viability,1);
            }
          }
        }
        else {
          IncreaseViability(&viability,0x10);
        }
      }
      break;
    case 29: /* EFFECT_MULTI_HIT */
    case 44: /* EFFECT_DOUBLE_HIT */
    case 104: /* EFFECT_TRIPLE_KICK */
      uVar12 = GetStrongestMove(bankAtk,bankDef);
      moveEffect = extraout_r1_01;
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
          (moveEffect = data->bankAtkPartner, gBattleMons[moveEffect].hp == 0)))) {
        bVar6 = gBattleMoves[uVar12].effect;
        bVar8 = GoodIdeaToSwapTimers(timers,moveEffect,0xc,bVar6);
        if (((((bVar8 != 0) && (bVar8 = IsStrongestMove(move,bankAtk,bankDef), bVar8 == 0)) &&
             (bVar6 != 0x1d)) && ((bVar6 != 0x68 && (bVar6 != 0x2c)))) &&
           ((iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 != 0 ||
            (data->atkItemEffect == 0x1e)))) {
          IncreaseViability(&viability,3);
          break;
        }
      }
      if (move == 0x2cb /* Scale Shot */) goto sw_d11e4_12;
      break;
    case 12: /* EFFECT_SPEED_UP */
sw_d11e4_12:
      if (atkAbility != 0xbf /* Contrary */) {
        defSpeed = data->defSpeed;
        uVar12 = data->atkSpeed;
        uVar23 = 1;
        goto LAB_090d2236;
      }
      break;
    case 30: /* EFFECT_CONVERSION */
      if (move != 0x28e /* Reflect Type */) {
        uVar23 = (char)gBattleMons[bankAtk_].moves[0] * '\f';
        bVar6 = uVar23 - 0x30;
        iVar18 = IsOfType(bankAtk_,gBattleMoves[gBattleMons[bankAtk_].moves[0]].type);
        if ((iVar18 == 0) && (bVar6 = GoodIdeaToSwapTimers(timers,sideAtk,uVar23,bVar6), bVar6 != 0)
           ) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 31: /* EFFECT_FLINCH_HIT */
    case 7:
    case 6:
sw_d11e4_31:
      bVar6 = CanBeFlinched(bankDef,bankAtk,uVar4,move);
      if (bVar6 != 0) {
        if ((((atkAbility == 0x20 /* Serene Grace */) || ((int)(data->defStatus1 << 0x19) < 0)) ||
            (defAbility = data->defStatus2, (defAbility & 0xf0000) != 0)) ||
           (iVar18 = func_0x09075a44(bankDef_), iVar18 != 0)) {
          uVar23 = (u8)defAbility;
          bVar6 = IsUsefulToFlinchTarget(bankDef);
          if ((bVar6 != 0) &&
             ((move = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x3b < move ||
              (bVar6 = Can2HKO(bankAtk,bankDef), bVar6 == 0)))) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
        else if ((move == 0x2a1 /* Dbl IronBash */) && (bVar6 = IsUsefulToFlinchTarget(bankDef), bVar6 != 0)) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      break;
    case 37: /* EFFECT_REST */
      bVar6 = ResistsAllMovesAtFullHealth(bankDef,bankAtk);
      if ((bVar6 == 0) || (bVar6 = OffensiveSetupMoveInMoveset(bankDef,bankAtk), bVar6 != 0)) {
        if ((data->atkItemEffect != 3) &&
           ((((data->atkItemEffect != 9 && (bVar6 = MoveEffectInMoveset(0x61 /* EFFECT_SLEEP_TALK */,bankAtk), bVar6 == 0))
             && (bVar6 = MoveEffectInMoveset(0x5c /* EFFECT_SNORE */,bankAtk), bVar6 == 0)) &&
            ((atkAbility != 0x3d /* Shed Skin */ && (atkAbility != 0x30 /* Early Bird */)))))) {
          bVar6 = extraout_r1_02;
          if (((gBattleWeather & 0x1007) != 0) && ((UNK_02023f48 != '\x01' && (atkAbility == 0x6b /* Hydration */)))) {
            iVar18 = sub_9076620(data->atkItemEffect);
            bVar6 = extraout_r1_03;
            if (iVar18 == 0) goto sw_d11e4_32;
          }
          bVar6 = IsTakingSecondaryDamage(bankDef,bVar6);
          if ((bVar6 != 0) && (bVar6 = IsClassKillerSweeper(style), bVar6 != 0)) goto LAB_090d24e4;
          if ((data->atkStatus1 == 0) || (iVar18 = Random(), -1 < iVar18 << 0x1f)) break;
        }
        goto sw_d11e4_32;
      }
      if ((gBattleMons[bankAtk_].hp == gBattleMons[bankAtk_].maxHP) ||
         (bVar6 = IsTakingSecondaryDamage(bankDef,0x58), bVar6 == 0))
      goto sw_d11e4_32;
LAB_090d24e4:
      bVar6 = IsClassKillerSweeper(style);
      if (bVar6 == 0) {
        bVar6 = IsClassPhazer(style);
        if (bVar6 == 0) {
          bVar6 = IsClassDoublesTrickRoomSetup(style);
          if (bVar6 == 0) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
          else {
            IncreaseViability(&viability,0x10);
          }
        }
        else {
          IncreaseViability(&viability,8);
        }
      }
      else {
        IncreaseViability(&viability,8);
      }
      break;
    case 32: /* EFFECT_RESTORE_HP */
    case 132: /* EFFECT_MORNING_SUN */
    case 162: /* EFFECT_SWALLOW */
sw_d11e4_32:
      bVar6 = ShouldRecover(bankAtk,bankDef,move);
      if (bVar6 != 0) goto LAB_090d24e4;
      if (move == 0x2dc /* Jungle Heal */) goto LAB_090d239c;
      break;
    case 42: /* EFFECT_TRAP */
      iVar18 = MoveInMoveset(0xe5 /* Rapid Spin */,bankDef_);
      if (((iVar18 == 0) && (iVar18 = IsOfType(bankDef_,7 /* Ghost */), iVar18 == 0)) &&
         ((data->defStatus2 & 0xe000) == 0)) {
        if (move == 0x31c /* Salt Cure */) {
          if ((*(uint *)(&gBitTable + (int)bankDef_ * 4) & (uint)*(byte *)(gNewBS + 199)) == 0) {
            iVar18 = IsOfType(bankDef_,0xb /* Water */);
            if ((iVar18 == 0) && (iVar18 = IsOfType(bankDef_,8 /* Steel */), iVar18 == 0)) {
              IncreaseViability(&viability,4);
            }
            else {
              IncreaseViability(&viability,8);
            }
          }
        }
        else {
          bVar6 = ShouldTrap(bankAtk,bankDef,move,style);
          if (bVar6 != 0) {
            IncreaseViability(&viability,7);
          }
        }
      }
      break;
    case 46: /* EFFECT_MIST */
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
          (gBattleMons[data->bankAtkPartner].hp != 0)))) {
        bVar6 = IsClassDoublesTeamSupport(style);
        if ((bVar6 != 0) && (moveType = ViableMonCountFromBank(bankDef_), 1 < moveType)) {
          IncreaseViability(&viability,8);
        }
      }
      else {
        bVar6 = IsClassScreener(style);
        if (bVar6 != 0) {
          IncreaseViability(&viability,6);
        }
      }
      break;
    case 47: /* EFFECT_FOCUS_ENERGY */
      if (((atkAbility - 0x54 & 0xff) < 2) || (data->atkItemEffect == 0x29)) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      else {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 35: /* EFFECT_LIGHT_SCREEN */
    case 65: /* EFFECT_REFLECT */
      if ((move == 0x243 /* Aurora Veil */) || ((0x242 < move && (move - 0x3bc < 2)))) {
        bVar6 = ShouldSetUpScreens(bankAtk,bankDef,move);
        if (bVar6 != 0) {
          bVar6 = IsClassScreener(style);
          if (bVar6 == 0) {
            bVar6 = IsClassDoublesTeamSupport(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0xf);
            }
          }
          else {
            IncreaseViability(&viability,8);
          }
        }
      }
      else {
        bVar6 = ShouldSetUpScreens(bankAtk,bankDef,move);
        if (bVar6 != 0) {
          bVar6 = IsClassScreener(style);
          if (bVar6 == 0) {
            bVar6 = IsClassDoublesTeamSupport(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0xf);
            }
          }
          else {
            IncreaseViability(&viability,0xf);
          }
        }
      }
      break;
    case 68: /* EFFECT_ATTACK_DOWN_HIT */
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
         (((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))))
      goto sw_d11e4_18;
      break;
    case 18: /* EFFECT_ATTACK_DOWN */
    case 58: /* EFFECT_ATTACK_DOWN_2 */
    case 21:
sw_d11e4_18:
      bVar6 = GoodIdeaToLowerAttack(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 69: /* EFFECT_DEFENSE_DOWN_HIT */
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
         (((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))))
      goto sw_d11e4_19;
      break;
    case 19: /* EFFECT_DEFENSE_DOWN */
    case 59: /* EFFECT_DEFENSE_DOWN_2 */
    case 22:
sw_d11e4_19:
      bVar6 = GoodIdeaToLowerDefense(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 70: /* EFFECT_SPEED_DOWN_HIT */
      uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x31 < uVar12) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0)) {
sw_d55da_23:
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[data->bankAtkPartner].hp != 0)))) {
          iVar18 = IsClearBodyAbility(defAbility);
          if (((iVar18 == 0) && (defAbility != 0xbf /* Contrary */)) && (0 < gBattleMons[(int)bankDef_].statStages[2]))
          {
            IncreaseViabilityForSpeedControl(&viability,style,bankAtk,bankDef);
          }
        }
        else {
          bVar6 = GoodIdeaToLowerSpeed(bankDef,bankAtk,move,1);
          if (bVar6 != 0) {
            uVar20 = Random2();
            iVar18 = umodsi(uVar20,2);
            if (iVar18 == 0) {
              IncreaseViability(&viability,3);
            }
          }
        }
      }
      break;
    case 71: /* EFFECT_SPECIAL_ATTACK_DOWN_HIT */
      if ((((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
           (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
            (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
          ((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)))) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))
      goto sw_d11e4_21;
      break;
    case 21: /* EFFECT_SPECIAL_ATTACK_DOWN */
    case 61: /* EFFECT_SPECIAL_ATTACK_DOWN_2 */
    case 24:
sw_d11e4_21:
      bVar6 = GoodIdeaToLowerSpAtk(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 72: /* EFFECT_SPECIAL_DEFENSE_DOWN_HIT */
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
         (((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))))
      goto sw_d11e4_22;
      break;
    case 22: /* EFFECT_SPECIAL_DEFENSE_DOWN */
    case 62: /* EFFECT_SPECIAL_DEFENSE_DOWN_2 */
    case 25:
sw_d11e4_22:
      bVar6 = GoodIdeaToLowerSpDef(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 73: /* EFFECT_ACCURACY_DOWN_HIT */
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
         (((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))))
      goto sw_d11e4_23;
      break;
    case 23: /* EFFECT_ACCURACY_DOWN */
    case 63: /* EFFECT_ACCURACY_DOWN_2 */
    case 26:
sw_d11e4_23:
      bVar6 = GoodIdeaToLowerAccuracy(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 74: /* EFFECT_EVASION_DOWN_HIT */
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (uVar23 = data->bankAtkPartner * 'X', gBattleMons[data->bankAtkPartner].hp == 0)))) &&
         (((bVar6 = IsClassDamager(style), bVar6 == 0 &&
           (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x31 < uVar12)) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0))))
      goto sw_d11e4_24;
      break;
    case 24: /* EFFECT_EVASION_DOWN */
    case 64: /* EFFECT_EVASION_DOWN_2 */
    case 27:
sw_d11e4_24:
      bVar6 = GoodIdeaToLowerEvasion(bankDef,bankAtk,move);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 76: /* EFFECT_CONFUSE_HIT */
      uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if (((0x4a < uVar12) &&
          (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0)) &&
         (bVar6 = MoveWillHit(move,bankAtk,bankDef), bVar6 != 0))
      goto sw_d11e4_49;
      break;
    case 49: /* EFFECT_CONFUSE */
    case 6:
sw_d11e4_49:
      iVar18 = CanBeConfused(bankDef_,1);
      if ((iVar18 != 0) && (((gBattleTypeFlags & 0x6000100) == 0 || (1 < data->defItemEffect - 8)))
         ) {
        if (((int)(data->defStatus1 << 0x19) < 0) ||
           (((data->defStatus2 & 0xf0000) != 0 ||
            ((atkAbility == 0x20 /* Serene Grace */ && (bVar6 = FlinchingMoveInMoveset(bankAtk), bVar6 != 0)))))) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
        else {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 79: /* EFFECT_SUBSTITUTE */
      IncreaseSubstituteViability(&viability,style,bankAtk,bankDef);
      break;
    case 82: /* EFFECT_MIMIC */
      bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (bVar6 == 0) {
        if (predictedMove != 0 /* - */) {
          bVar6 = Can2HKO(bankDef,bankAtk);
          if ((bVar6 == 0) && (bVar6 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar6 != 0)) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
          else {
            bVar6 = MoveEffectInMoveset(0xc0 /* EFFECT_IMPRISON */,bankAtk);
            if (bVar6 != 0) {
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
          }
        }
      }
      else if ((ushort)(gLastUsedMoves[(int)bankDef_] - 1) < 0xfffe) {
        bVar6 = CanKnockOut(bankDef,bankAtk);
        if ((bVar6 == 0) &&
           (bVar6 = MoveKnocksOutXHits(gLastUsedMoves[(int)bankDef_],bankAtk,bankDef,1), bVar6 != 0))
        {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
        else {
          bVar6 = MoveEffectInMoveset(0xc0 /* EFFECT_IMPRISON */,bankAtk);
          if (bVar6 != 0) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
        }
      }
      break;
    case 84: /* EFFECT_LEECH_SEED */
      iVar18 = IsOfType(bankDef_,0xc /* Grass */);
      if (((iVar18 == 0) && (-1 < (int)(data->defStatus3 << 0x1d))) &&
         ((iVar18 = MoveInMoveset(0xe5 /* Rapid Spin */,bankDef_), iVar18 == 0 &&
          ((defAbility != 0x40 /* Liquid Ooze */ && (defAbility != 0x73 /* Magic Guard */)))))) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 85: /* EFFECT_SPLASH */
      iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type);
      if (((iVar18 != 0) && (iVar18 = IsMegaZMoveBannedBattle(), iVar18 == 0)) &&
         (*(char *)(gNewBS + bankAtk_ + 0x194) == '\0')) {
        IncreaseViability(&viability,9);
      }
      break;
    case 153: /* EFFECT_TELEPORT */
      if (((int)(gBattleTypeFlags << 0x1c) < 0) ||
         (iVar18 = GetBattlerSide(UNK_02023d6b), iVar18 == 0)) goto LAB_090d2f60;
      break;
    case 86: /* EFFECT_DISABLE */
      if (((gDisableStructs[(int)bankDef_].field_0xb & 0xf) == 0) && (data->defItemEffect != 0x1c)) {
        bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
        if (bVar6 == 0) {
          if ((predictedMove != 0 /* - */) && (gBattleMoves[predictedMove].split == 2)) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
        }
        else {
          uVar11 = gLastUsedMoves[(int)bankDef_];
          if ((uVar11 - 1 & 0xffff) < 0xfffe) {
            if (uVar11 == predictedMove) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
            else {
              bVar6 = MoveKnocksOutXHits(uVar11,bankDef,bankAtk,1);
              if (bVar6 != 0) {
                IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
              }
            }
          }
        }
      }
      break;
    case 90: /* EFFECT_ENCORE */
      if (((gDisableStructs[(int)bankDef_].field_0xe & 0xf) == 0) && (data->defItemEffect != 0x1c)) {
        bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
        if (bVar6 == 0) {
          if ((predictedMove != 0 /* - */) && (gBattleMoves[predictedMove].split == 2)) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
        else {
          moveType = (uint)gLastUsedMoves[(int)bankDef_];
          if (((moveType - 1 & 0xffff) < 0xfffe) &&
             ((gBattleMoves[moveType].split == 2 ||
              (iVar18 = AI_SpecialTypeCalc(moveType,bankDef_,bankAtk_), iVar18 << 0x1c < 0)))) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
      }
      break;
    case 91: /* EFFECT_PAIN_SPLIT */
      uVar11 = gBattleMons[bankAtk_].hp;
      uVar1 = gBattleMons[(int)bankDef_].hp;
      moveType = sub_900042a((uint)uVar11 * 0xc,10);
      if ((moveType & 0xffff) < (uint)((int)((uint)uVar1 + (uint)uVar11) >> 1))
      goto sw_d11e4_3;
      break;
    case 3: /* EFFECT_ABSORB */
    case 8: /* EFFECT_DREAM_EATER */
sw_d11e4_3:
      bVar6 = ShouldRecover(bankAtk,bankDef,move);
      if (bVar6 != 0) {
        bVar6 = IsClassKillerSweeper(style);
        if (bVar6 == 0) {
          bVar6 = IsClassDoublesTrickRoomSetup(style);
          if (bVar6 == 0) {
            if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
               (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
                (gBattleMons[data->bankAtkPartner].hp != 0)))) {
              IncreaseDoublesDamageViabilityToScore(&viability,style,5,bankAtk,bankDef);
            }
          }
          else {
            IncreaseViability(&viability,0x10);
          }
        }
        else {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      break;
    case 92: /* EFFECT_SNORE */
    case 97: /* EFFECT_SLEEP_TALK */
      if (((data->atkStatus1 & 7) != 0) && (data->atkStatus1 != 1)) {
        IncreaseViability(&viability,10);
      }
      break;
    case 94: /* EFFECT_LOCK_ON */
      if ((move == 0x252 /* Laser Focus */) && (bVar6 = CanKnockOut(bankAtk,bankDef), bVar6 == 0)) {
        if (data->defSpeed < data->atkSpeed) {
          bVar6 = CanKnockOut(bankDef,bankAtk);
        }
        else {
          bVar6 = Can2HKO(bankDef,bankAtk);
        }
        if (bVar6 == 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 96: /* EFFECT_SPEED_UP_1_HIT */
      uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if (0x4a < uVar12) goto sw_d11e4_12;
      break;
    case 98: /* EFFECT_DESTINY_BOND */
      bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (bVar6 == 0) {
        bVar6 = Can2HKO(bankDef,bankAtk);
        if (bVar6 != 0) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      else {
        bVar6 = CanKnockOut(bankDef,bankAtk);
        if (bVar6 != 0) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      break;
    case 100: /* EFFECT_SPITE */
      moveType = FindMovePositionInMoveset(predictedMove,bankDef_);
      bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (((bVar6 != 0) && (predictedMove != 0 /* - */)) &&
         ((moveType < 4 && (gBattleMons[(int)bankDef_].pp[moveType] < 5)))) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 102: /* EFFECT_HEAL_BELL */
      bVar6 = ShouldUseWishAromatherapy(bankAtk,bankDef,move,style);
      if (bVar6 != 0) {
        IncreaseViability(&viability,7);
      }
      break;
    case 107: /* EFFECT_NIGHTMARE */
      if ((defAbility != 0x73 /* Magic Guard */) &&
         ((defAbility == 0xe7 /* Comatose */ || (((data->defStatus1 & 7) != 0 && (data->defStatus1 != 1)))))) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 109: /* EFFECT_CURSE */
      iVar18 = IsOfType(bankAtk_,7 /* Ghost */);
      if (iVar18 == 0) {
        if (((atkAbility != 0xbf /* Contrary */) && (defAbility != 0x73 /* Magic Guard */)) &&
           (iVar18 = func_0x090db548(bankDef_,bankAtk_), iVar18 == 0)) {
          iVar18 = MoveInMoveset(0x1fe /* Gyro Ball */,bankAtk_);
          if (iVar18 == 0) {
            if (2 < gBattleMons[bankAtk_].statStages[2]) {
              if (gBattleMons[bankAtk_].statStages[0] < 8) {
                IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,1,8);
              }
              else if (gBattleMons[bankAtk_].statStages[1] < 8) {
                IncreaseStatViability(&viability,style,1,bankAtk,bankDef,move,2,8);
              }
            }
          }
          else {
            IncreaseStatViability(&viability,style,4,bankAtk,bankDef,move,1,0xc);
          }
        }
      }
      else {
        bVar6 = IsTrapped(bankDef,1);
        if (bVar6 == 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
        else {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      break;
    case 111: /* EFFECT_PROTECT */
      if (move == 0x27b /* Crafty Guard */) {
        if (((predictedMove != 0 /* - */) && (gBattleMoves[predictedMove].split == 2)) &&
           (-1 < (int)((uint)gBattleMoves[predictedMove].target << 0x1b))) {
          if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
             (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[data->bankAtkPartner].hp == 0)))) goto LAB_090d3518;
          IncreaseTeamProtectionViability(&viability,style);
        }
      }
      else if (move < 0x27c) {
        if (move == 0xcb /* Endure */) {
          bVar6 = CanKnockOut(bankDef,bankAtk);
          if (bVar6 != 0) {
            if ((gBattleMons[bankAtk_].maxHP >> 2 < gBattleMons[bankAtk_].hp) &&
               (iVar18 = sub_90a52f4(data->atkItemEffect), iVar18 != 0)) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
            else if (((1 < gBattleMons[bankAtk_].hp) &&
                     (bVar6 = CanKnockOut(bankDef,bankAtk), bVar6 != 0)) &&
                    ((bVar6 = MoveEffectInMoveset(99 /* EFFECT_FLAIL */,bankAtk), bVar6 != 0 ||
                     (bVar6 = MoveEffectInMoveset(0xbd /* EFFECT_ENDEAVOR */,bankAtk), bVar6 != 0)))) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
          }
        }
        else {
          if ((((move != 0x20f /* Kings Shield */) || (atkAbility != 0xd3 /* Stance Change */)) || (data->atkSpecies != 0x341)) ||
             ((bVar6 = IsBankIncapacitated(bankDef), bVar6 != 0 ||
              (moveType = Random(), (moveType & 1) != 0)))) goto LAB_090d3450;
          bVar6 = IsClassKillerSweeper(style);
          if (bVar6 == 0) {
            if (((gBattleTypeFlags & 1) == 0) ||
               (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                (gBattleMons[data->bankAtkPartner].hp == 0)))) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0x13);
            }
          }
          else {
            IncreaseViability(&viability,3);
          }
        }
      }
      else if (move == 0x27d /* Quick Guard */) {
        if ((predictedMove != 0 /* - */) && (iVar18 = PriorityCalc(bankDef_,0,predictedMove), 0 < iVar18)) {
          if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
             (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[data->bankAtkPartner].hp == 0)))) {
LAB_090d3518:
            move = 0xb6;
            goto LAB_090d3450;
          }
          IncreaseTeamProtectionViability(&viability,style);
        }
      }
      else if (move < 0x27d) {
        if (((gDisableStructs[bankAtk_].isFirstTurn != 0) && (predictedMove != 0 /* - */)) &&
           ((gBattleMoves[predictedMove].split != 2 &&
            (-1 < (int)((uint)gBattleMoves[predictedMove].target << 0x1b))))) {
          if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
             (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[data->bankAtkPartner].hp == 0)))) goto LAB_090d3518;
          IncreaseTeamProtectionViability(&viability,style);
        }
      }
      else if (move == 0x27e /* Wide Guard */) {
        if ((predictedMove == 0 /* - */) || ((gBattleMoves[predictedMove].target & 0x28) == 0)) {
          if ((((gBattleTypeFlags & 1) != 0) &&
              ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
                (gBattleMons[data->bankAtkPartner].hp != 0)) &&
               (((int)((uint)gBattleMoves[data->partnerMove].target << 0x1a) < 0 && (atkAbility != 0xe2 /* Telepathy */)
                ))))) &&
             (moveType = AI_SpecialTypeCalc((uint)data->partnerMove,data->bankAtkPartner,bankAtk_),
             (moveType & 0x29) == 0)) {
            IncreaseAllyProtectionViability(&viability,style);
          }
        }
        else {
          if (((gBattleTypeFlags & 1) == 0) ||
             (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[data->bankAtkPartner].hp == 0)))) goto LAB_090d3518;
          IncreaseTeamProtectionViability(&viability,style);
        }
      }
      else {
LAB_090d3450:
        uVar23 = ShouldProtect(bankAtk,bankDef,(u16)move);
        if ((uVar23 == 1) || (uVar23 == 4)) {
          IncreaseFoeProtectionViability(&viability,style,bankAtk,bankDef);
        }
        else if (uVar23 == 3) {
          IncreaseAllyProtectionViability(&viability,style);
        }
      }
      break;
    case 112: /* EFFECT_SPIKES */
      uStack_4c = LoadPartyRange(bankAtk_,&uStack_1d,auStack_1a);
      iVar18 = LoadPartyRange(bankDef_,&uStack_1d,auStack_1a);
      if (move == 0x2ee /* Stone Axe */) {
LAB_090d38c4:
        moveType = 0;
        do {
          iVar19 = iVar18 + moveType * 100;
          iVar21 = GetMonData(iVar19,0xb,0);
          if (((((iVar21 != 0) && (iVar21 = GetMonData(iVar19,0x2d,0,&GetMonData), iVar21 == 0))
               && (iVar21 = GetMonData(iVar19,0x39,0,&GetMonData), iVar21 != 0)) &&
              ((iVar21 = sub_9074eb8(iVar19), iVar21 != 0 &&
               (gBattlerPartyIndexes[data->foe1] != moveType)))) &&
             (gBattlerPartyIndexes[data->foe2] != moveType)) {
            IncreaseEntryHazardsViability(&viability,style,bankAtk,bankDef,move);
            break;
          }
          moveType = moveType + 1;
        } while (moveType != 6 /* Bug */);
      }
      else if (move < 0x2ef) {
        if (move == 0x1d5 /* Toxic Spikes */) {
          uStack_4c = 0;
          do {
            iVar21 = GetMonData(iVar18,0xb,0);
            if ((((iVar21 != 0) && (iVar21 = GetMonData(iVar18,0x2d,0,&GetMonData), iVar21 == 0)
                 ) && (iVar21 = GetMonData(iVar18,0x39,0,&GetMonData), iVar21 != 0)) &&
               (((iVar21 = sub_9074eb8(iVar18), iVar21 != 0 &&
                 (gBattlerPartyIndexes[data->foe1] != uStack_4c)) &&
                ((gBattlerPartyIndexes[data->foe2] != uStack_4c &&
                 (iVar21 = sub_90751c8(iVar18), iVar21 == 1)))))) {
              if ((int)(gBattleTypeFlags << 3) < 0) {
                uStack_38 = sub_909aa18(iVar18,0);
              }
              else {
                uStack_38 = (uint)(byte)(&UNK_097b98f2)[(uint)*(ushort *)(iVar18 + 0x20) * 0x1c];
              }
              if ((int)(gBattleTypeFlags << 3) < 0) {
                moveType = sub_909aa18(iVar18,1);
              }
              else {
                moveType = (uint)(byte)(&UNK_097b98f3)[(uint)*(ushort *)(iVar18 + 0x20) * 0x1c];
              }
              if ((uStack_38 == 3) || (moveType == 3 /* Poison */)) break;
              iVar21 = sub_90c1ed2(iVar18);
              if (iVar21 != 0) {
                IncreaseEntryHazardsViability(&viability,style,bankAtk,bankDef,0x1d5);
                break;
              }
            }
            uStack_4c = uStack_4c + 1;
            iVar18 = iVar18 + 100;
          } while (uStack_4c != 6);
        }
        else {
          if (move != 0x1e1 /* Sticky Web */) {
            if (move == 0x1d4 /* Stealth Rock */) goto LAB_090d38c4;
            goto LAB_090d398c;
          }
          iVar21 = uStack_4c + 600;
          do {
            iVar19 = GetMonData(uStack_4c,0x39,0);
            if (((iVar19 != 0) && (iVar19 = GetMonData(uStack_4c,0xb,0), iVar19 != 0)) &&
               (uStack_38 = GetMonData(uStack_4c,0x2d,0), uStack_38 == 0)) {
              do {
                iVar29 = iVar18 + uStack_38 * 100;
                iVar19 = GetMonData(iVar29,0x39,0);
                if (((((iVar19 != 0) &&
                      (iVar19 = GetMonData(iVar29,0xb,0,&GetMonData), iVar19 != 0)) &&
                     ((iVar19 = GetMonData(iVar29,0x2d,0,&GetMonData), iVar19 == 0 &&
                      ((iVar19 = sub_9074eb8(iVar29), iVar19 != 0 &&
                       (gBattlerPartyIndexes[data->foe1] != uStack_38)))))) &&
                    (gBattlerPartyIndexes[data->foe2] != uStack_38)) &&
                   (iVar19 = sub_90751c8(iVar29), iVar19 == 1)) {
                  uVar20 = GetBattlerSide(bankAtk_);
                  moveType = sub_9071268(uVar20,uStack_4c);
                  uVar20 = GetBattlerSide(bankDef_);
                  defAbility = sub_9071268(uVar20,iVar29);
                  if (moveType < defAbility) {
                    IncreaseEntryHazardsViability(&viability,style,bankAtk,bankDef,0x1e1);
                    goto sw_d11e4_0;
                  }
                }
                uStack_38 = uStack_38 + 1;
              } while (uStack_38 != 6);
            }
            uStack_4c = uStack_4c + 100;
          } while (iVar21 != uStack_4c);
        }
      }
      else {
        if ((0x3cf < move) && ((move < 0x3d2 || (move - 0x3e4 < 2))))
        goto LAB_090d38c4;
LAB_090d398c:
        moveType = 0;
        do {
          iVar19 = iVar18 + moveType * 100;
          iVar21 = GetMonData(iVar19,0xb,0);
          if (((iVar21 != 0) && (iVar21 = GetMonData(iVar19,0x2d,0,&GetMonData), iVar21 == 0))
             && (((iVar21 = GetMonData(iVar19,0x39,0,&GetMonData), iVar21 != 0 &&
                  (((iVar21 = sub_9074eb8(iVar19), iVar21 != 0 &&
                    (gBattlerPartyIndexes[data->foe1] != moveType)) &&
                   (gBattlerPartyIndexes[data->foe2] != moveType)))) &&
                 (iVar21 = sub_90751c8(iVar19), iVar21 == 1)))) {
            IncreaseEntryHazardsViability(&viability,style,bankAtk,bankDef,move);
            break;
          }
          moveType = moveType + 1;
        } while (moveType != 6 /* Bug */);
      }
      break;
    case 113: /* EFFECT_FORESIGHT */
      if (move == 0x1c9 /* Miracle Eye */) {
        if ((6 < gBattleMons[(int)bankDef_].statStages[6]) ||
           ((iVar18 = IsOfType(bankDef_,0x11 /* Dark */), iVar18 != 0 &&
            (bVar6 = DamagingMoveTypeInMoveset(bankAtk,0xe /* Psychic */), bVar6 != 0)))) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else if ((atkAbility != 0x53 /* Scrappy */) &&
              ((6 < gBattleMons[(int)bankDef_].statStages[6] ||
               ((iVar18 = IsOfType(bankDef_,7 /* Ghost */), iVar18 != 0 &&
                ((bVar6 = DamagingMoveTypeInMoveset(bankAtk,0 /* Normal */), bVar6 != 0 ||
                 (bVar6 = DamagingMoveTypeInMoveset(bankAtk,1 /* Fighting */), bVar6 != 0)))))))) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 114: /* EFFECT_PERISH_SONG */
      bVar6 = IsTrapped(bankDef,1);
      if (bVar6 != 0) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 115: /* EFFECT_SANDSTORM */
      bVar6 = IsClassDoublesSetupAttacker(style);
      if ((((bVar6 == 0) ||
           (iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type), iVar18 == 0)) ||
          (*(char *)(gNewBS + bankAtk_ + 0x194) != '\0')) ||
         ((iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0 || (atkAbility == 0xbf /* Contrary */)))) {
        bVar6 = IsClassDoublesSetupAttacker(style);
        if (bVar6 == 0) {
          if ((atkAbility != 8 /* Sand Veil */) && (atkAbility != 0x7c /* Sand Rush */)) {
LAB_090d3dc6:
            if (((((atkAbility != 0x5f /* Sand Force */) && (1 < (atkAbility - 0x72 & 0xff))) &&
                 (data->atkItemEffect != 0x54)) &&
                (((iVar18 = IsOfType(bankAtk_,5 /* Rock */), iVar18 == 0 &&
                  (iVar18 = IsOfType(bankAtk_,8 /* Steel */), iVar18 == 0)) &&
                 ((iVar18 = IsOfType(bankAtk_,4 /* Ground */), iVar18 == 0 &&
                  ((iVar18 = MoveInMoveset(0x261 /* Shore Up */,bankAtk_), iVar18 == 0 &&
                   (iVar18 = MoveInMoveset(0x137 /* Weather Ball */,bankAtk_), iVar18 == 0)))))))) &&
               (data->atkItemEffect != 0x4e)) break;
          }
        }
        else {
          if (atkAbility == 0x7c /* Sand Rush */) {
            IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
            break;
          }
          if (atkAbility != 8 /* Sand Veil */) goto LAB_090d3dc6;
        }
        bVar6 = IsClassDoublesTeamSupport(style);
        if (bVar6 == 0) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
        else {
          IncreaseViability(&viability,0x11);
        }
      }
      else {
        IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
      }
      break;
    case 117: /* EFFECT_ROLLOUT */
      bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,uVar23,bVar6);
      if ((bVar6 != 0) && ((int)(data->atkStatus2 << 1) < 0)) {
        IncreaseViability(&viability,8);
      }
      break;
    case 118: /* EFFECT_SWAGGER */
      iVar18 = MoveInMoveset(0x217 /* Foul Play */,bankAtk_);
      if ((iVar18 == 0) && (bVar6 = MoveEffectInMoveset(0x8f /* EFFECT_PSYCH_UP */,bankAtk), bVar6 == 0))
      goto sw_d11e4_49;
      IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      break;
    case 166: /* EFFECT_FLATTER */
      bVar6 = MoveEffectInMoveset(0x8f /* EFFECT_PSYCH_UP */,bankAtk);
      if (bVar6 == 0) goto sw_d11e4_49;
      IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      break;
    case 119: /* EFFECT_FURY_CUTTER */
      if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        if ((gBattleMons[data->foe1].hp == 0) || (gBattleMons[data->foe2].hp == 0)) {
          checkConfusion = data->bankAtkPartner;
          uVar23 = checkConfusion * 'X';
          if (gBattleMons[checkConfusion].hp == 0) goto LAB_090d3ef4;
        }
      }
      else {
LAB_090d3ef4:
        bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,uVar23,0);
        if ((bVar6 != 0) && (data->atkItemEffect == 0x6f)) {
          IncreaseViability(&viability,3);
        }
      }
      break;
    case 120: /* EFFECT_ATTRACT */
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[data->bankAtkPartner].hp != 0)))) ||
         ((bVar6 = WillFaintFromSecondaryDamage(bankDef), bVar6 == 0 ||
          (bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar6 != 0)))) {
        if (((data->defStatus1 & 0xff) == 0) &&
           ((iVar18 = func_0x09075a44(bankDef_), iVar18 == 0 &&
            (bVar6 = IsTrapped(bankDef,1), bVar6 == 0)))) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
        else {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      break;
    case 124: /* EFFECT_SAFEGUARD */
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
          (gBattleMons[data->bankAtkPartner].hp != 0)))) {
        bVar6 = IsClassDoublesTeamSupport(style);
        if ((bVar6 != 0) && (moveType = ViableMonCountFromBank(bankDef_), 1 < moveType)) {
          IncreaseViability(&viability,8);
        }
      }
      else {
        bVar6 = IsClassTeamSupport(style);
        if ((bVar6 != 0) &&
           ((gTerrainType != '\x03' || (iVar18 = CheckGrounding(bankAtk_), iVar18 == 0)))) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 127: /* EFFECT_BATON_PASS */
      if (move < 0x1bc) {
        if (0x1b9 < move) goto LAB_090d2f60;
        if ((move == 0xe2 /* Baton Pass */) && (bVar6 = IsClassBatonPass(style), bVar6 != 0)) {
          IncreaseViability(&viability,3);
        }
      }
      else if (move == 0x2d8 /* Flip Turn */) {
LAB_090d2f60:
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[data->bankAtkPartner].hp != 0)))) {
          iVar18 = HasMonToSwitchTo(bankAtk_);
          if (iVar18 == 0) break;
          if ((move == 100 /* Teleport */) && (iVar18 = IsTrickRoomActive(), iVar18 != 0)) {
            IncreaseViability(&viability,9);
          }
          GetBankPartyData(bankAtk_);
          iVar18 = GetMonAbility();
          if ((iVar18 == 0x16) && (bVar6 = MoveSplitOnTeam(bankDef,0), bVar6 != 0)) {
            bVar6 = IsClassDoublesUtility(style);
            uVar23 = 0x10;
            if (bVar6 == 0) {
              bVar6 = IsClassDoublesAllOutAttacker(style);
              if (bVar6 == 0) goto LAB_090d2fd6;
              uVar23 = 0x12;
            }
LAB_090d4128:
            IncreaseViability(&viability,uVar23);
          }
        }
        else {
          bVar6 = ShouldPivot(bankAtk,bankDef,move,style);
          if ((byte)(bVar6 - 2) < 2) {
            IncreasePivotViability(&viability,style,bankAtk,bankDef,bVar6);
          }
          else if (bVar6 == 0) {
            bVar6 = IsStrongestMove(move,bankAtk,bankDef);
            if (bVar6 != 0) {
              RecalcStrongestMoveIgnoringMove(bankAtk,bankDef,move);
            }
            DecreaseViability(&viability,9);
          }
          else if ((&UNK_02023f40)[bankAtk_] != '\0') {
            bVar6 = ShouldUseWishAromatherapy(bankAtk,bankDef,0x111,style);
            uVar23 = 7;
            if (bVar6 != 0) goto LAB_090d4128;
          }
        }
LAB_090d2fd6:
        if (data->atkSpecies == 0x360) {
          IncreaseViability(&viability,0x12);
        }
      }
      else if (move == 0x307 /* Shed Tail */) {
        iVar18 = HasMonToSwitchTo(bankAtk_);
        if (iVar18 != 0) {
          IncreaseViability(&viability,3);
        }
      }
      else if (move == 0x230 /* Parting Shot */) goto LAB_090d2f60;
      break;
    case 128: /* EFFECT_PURSUIT */
      bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,uVar23,bVar6);
      if (bVar6 != 0) {
        bVar6 = IsPredictedToSwitch(bankDef,bankAtk);
        if (bVar6 == 0) {
          iVar18 = func_0x090db504(bankDef_,bankAtk_);
          if ((iVar18 != 0) &&
             (bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar6 == 0)) {
            IncreaseViability(&viability,3);
          }
        }
        else {
          IncreaseViability(&viability,3);
        }
      }
      break;
    case 129: /* EFFECT_RAPID_SPIN */
      uVar31 = GetBattlerSide(bankAtk_);
      moveType = (uint)((ulonglong)uVar31 >> 0x20);
      if ((int)((uint)gSideStatuses[(int)uVar31] << 0x1b) < 0) {
        if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
           (((gBattleMons[data->foe1].hp == 0 ||
             (moveType = (uint)data->foe2 * 0x58, gBattleMons[data->foe2].hp == 0)) &&
            (moveType = (uint)data->bankAtkPartner, gBattleMons[moveType].hp == 0)))) {
          uVar31 = ViableMonCountFromBank(bankAtk_);
          moveType = (uint)((ulonglong)uVar31 >> 0x20);
          if ((uint)uVar31 < 3) goto LAB_090d4246;
LAB_090d42b0:
          if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
             (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[data->bankAtkPartner].hp != 0)))) {
            IncreaseHelpingHandViability(&viability,style);
          }
          else {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
          break;
        }
LAB_090d4246:
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (moveType = (uint)data->bankAtkPartner, gBattleMons[moveType].hp != 0)))) {
          uVar31 = ViableMonCountFromBank(bankAtk_);
          moveType = (uint)((ulonglong)uVar31 >> 0x20);
          if (2 < (uint)uVar31) goto LAB_090d42b0;
        }
      }
      if (move == 0x204 /* Defog */) {
        iVar18 = GetBattlerSide(bankDef_,moveType,0x204,&GetBattlerSide);
        moveType = gNewBS;
        if (((gSideStatuses[iVar18] & 0x123) == 0) &&
           (iVar18 = GetMonData(bankDef_), *(char *)(moveType + iVar18 + 0x15) == '\0')) {
          iVar18 = GetMonData(bankDef_);
          if ((-1 < (int)((uint)gSideStatuses[iVar18] << 0x1b)) &&
             ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
              ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                (gBattleMons[data->bankAtkPartner].hp == 0)) ||
               ((gBattleMoves[data->partnerMove].effect != 0x70 /* EFFECT_SPIKES */ ||
                (bVar6 = MoveWouldHitBeforeOtherMove
                                   (0x204,bankAtk,data->partnerMove,data->bankAtkPartner),
                bVar6 != 0)))))))) goto sw_d11e4_24;
        }
        else if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
                (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
                 (gBattleMons[data->bankAtkPartner].hp != 0)))) {
          IncreaseHelpingHandViability(&viability,style);
        }
        else {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      else if (move == 0x2b2 /* Court Change */) {
        iVar18 = GetBattlerSide(bankAtk_);
        iVar21 = GetBattlerSide(bankDef_);
        if (((iVar18 != iVar21) && (iVar18 = sub_90c5aa8(bankAtk_,bankDef_), iVar18 != 0)) &&
           (iVar18 = sub_90c5aa8(bankDef_,bankAtk_), iVar18 == 0)) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else {
        iVar18 = AI_SpecialTypeCalc(move,bankAtk_,bankDef_);
        if ((-1 < iVar18 << 0x1c) &&
           (((int)(data->atkStatus3 << 0x1d) < 0 || ((data->atkStatus2 & 0xe000) != 0)))) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      break;
    case 136: /* EFFECT_RAIN_DANCE */
      bVar6 = IsClassDoublesSetupAttacker(style);
      if (((bVar6 == 0) ||
          (iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type), iVar18 == 0)) ||
         ((*(char *)(gNewBS + bankAtk_ + 0x194) != '\0' ||
          ((iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0 || (atkAbility == 0xbf /* Contrary */)))))) {
        bVar6 = IsClassDoublesSetupAttacker(style);
        if ((bVar6 == 0) || (atkAbility != 0x21 /* Swift Swim */)) {
          iVar18 = sub_9076620(data->atkItemEffect);
          if (iVar18 == 0) {
            moveType = atkAbility - 0x21 & 0xff;
            if (moveType < 0x1b) {
              if (-1 < (int)((0x4000801U >> moveType) << 0x1f)) goto LAB_090d45b6;
            }
            else if (atkAbility != 0x6b /* Hydration */) {
LAB_090d45b6:
              if ((((atkAbility != 0x62 /* Dry Skin */) && (bVar6 = MoveEffectInMoveset(0x98 /* EFFECT_THUNDER */,bankAtk), bVar6 == 0)) &&
                  (bVar6 = MoveEffectInMoveset(0x84 /* EFFECT_MORNING_SUN */,bankDef), bVar6 == 0)) &&
                 (((iVar18 = MoveInMoveset(0x137 /* Weather Ball */,bankAtk_), iVar18 == 0 &&
                   (bVar6 = MoveTypeInMoveset(bankAtk,0xb), bVar6 == 0)) &&
                  ((bVar6 = MoveTypeInMoveset(bankDef,10), bVar6 == 0 &&
                   (data->atkItemEffect != 0x4f)))))) break;
            }
            bVar6 = IsClassDoublesTeamSupport(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0x11);
            }
          }
        }
        else {
          IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
        }
      }
      else {
        IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
      }
      break;
    case 137: /* EFFECT_SUNNY_DAY */
      bVar6 = IsClassDoublesSetupAttacker(style);
      if (((bVar6 == 0) ||
          (iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type), iVar18 == 0)) ||
         ((*(char *)(gNewBS + bankAtk_ + 0x194) != '\0' ||
          ((iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0 || (atkAbility == 0xbf /* Contrary */)))))) {
        bVar6 = IsClassDoublesSetupAttacker(style);
        if ((bVar6 == 0) || (atkAbility != 0x22 /* Chlorophyll */)) {
          iVar18 = sub_9076620(data->atkItemEffect);
          if ((iVar18 == 0) &&
             ((((((((atkAbility == 0x22 /* Chlorophyll */ || (atkAbility == 0x3b /* Forecast */)) || ((atkAbility + 0x35 & 0xfd) == 0)) ||
                  ((atkAbility == 0x60 /* Solar Power */ || (atkAbility == 0xe1 /* Harvest */)))) ||
                 (bVar6 = MoveEffectInMoveset(0x97 /* EFFECT_SOLARBEAM */,bankAtk), bVar6 != 0)) ||
                ((bVar6 = MoveEffectInMoveset(0x84 /* EFFECT_MORNING_SUN */,bankAtk), bVar6 != 0 ||
                 (bVar6 = MoveEffectInMoveset(0x98 /* EFFECT_THUNDER */,bankDef), bVar6 != 0)))) ||
               (iVar18 = MoveInMoveset(0x137 /* Weather Ball */,bankAtk_), iVar18 != 0)) ||
              ((((iVar18 = MoveInMoveset(0x4a /* Growth */,bankAtk_), iVar18 != 0 ||
                 (bVar6 = MoveTypeInMoveset(bankAtk,10), bVar6 != 0)) ||
                (bVar6 = MoveTypeInMoveset(bankDef,0xb), bVar6 != 0)) ||
               (data->atkItemEffect == 0x50)))))) {
            bVar6 = IsClassDoublesTeamSupport(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0x11);
            }
          }
        }
        else {
          IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
        }
      }
      else {
        IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
      }
      break;
    case 139: /* EFFECT_ATTACK_UP_HIT */
      if (atkAbility != 0xbf /* Contrary */) {
        if (move == 0x22d /* Fell Stinger */) {
          if ((gBattleMons[bankAtk_].statStages[0] < 0xc) &&
             (bVar6 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar6 != 0)) {
            if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
               (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
                (gBattleMons[data->bankAtkPartner].hp != 0)))) {
              IncreaseDoublesDamageViabilityToScore(&viability,style,6,bankAtk,bankDef);
            }
            else {
              bVar6 = MoveWouldHitFirst(0x22d,(ushort)bankAtk,(ushort)bankDef);
              if (bVar6 == 0) {
                IncreaseViability(&viability,3);
              }
              else {
                IncreaseViability(&viability,9);
              }
            }
          }
        }
        else {
          moveType = move;
          if (atkAbility == 0x97 /* Parental Bond */) {
            moveType = 2;
            bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,2);
            if (bVar6 != 0) goto LAB_090d19f6;
          }
          uVar12 = CalcSecondaryEffectChance(bankAtk,move,(u8)moveType);
          if (0x4a < uVar12) goto LAB_090d1a1e;
        }
      }
      break;
    case 141: /* EFFECT_HIGHER_OFFENSES_DEFENSES_UP_HIT */
      if ((atkAbility != 0xbf /* Contrary */) &&
         (uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23), 0x4a < uVar12)) {
        iVar18 = sub_90743c0(bankAtk_);
        if (iVar18 != 0) goto LAB_090d1fbe;
        goto LAB_090d1ab0;
      }
      break;
    case 142: /* EFFECT_BELLY_DRUM */
      if (((atkAbility != 0xbf /* Contrary */) && (bVar6 = RealPhysicalMoveInMoveset(bankAtk), bVar6 != 0)) &&
         (bVar6 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef,1), bVar6 == 0)) {
        iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type);
        if ((iVar18 == 0) || (iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0)) {
          IncreaseStatViability(&viability,style,2,bankAtk,bankDef,move,1,8);
        }
        else {
          IncreaseStatViability(&viability,style,5,bankAtk,bankDef,move,1,0xc);
        }
      }
      break;
    case 143: /* EFFECT_PSYCH_UP */
      if (move == 0x265 /* Spect Thief */) {
        if (atkAbility != 0xbf /* Contrary */) {
          iVar18 = 1;
          do {
            if (7 < gBattleMons[(int)bankDef_].statStages[iVar18 + -1]) {
              bVar6 = IsClassDamager(style);
              if (bVar6 == 0) {
                IncreaseViability(&viability,3);
              }
              else {
                IncreaseStatViability(&viability,style,3,bankAtk,bankDef,0x265,0xff,0xc);
              }
              break;
            }
            iVar18 = iVar18 + 1;
          } while (iVar18 != 8);
        }
      }
      else {
        IncreasePsychUpViability(&viability,style,bankAtk,bankDef);
      }
      break;
    case 155: /* EFFECT_SEMI_INVULNERABLE */
      if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        if ((gBattleMons[data->foe1].hp == 0) || (gBattleMons[data->foe2].hp == 0)) {
          checkConfusion = data->bankAtkPartner;
          uVar23 = checkConfusion * 'X';
          if (gBattleMons[checkConfusion].hp == 0) goto LAB_090d499e;
        }
      }
      else {
LAB_090d499e:
        bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,uVar23,0);
        if (bVar6 != 0) {
          bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
          moveEffect = gBattleMoves[predictedMove].effect;
          if (bVar6 == 0) {
            if ((moveEffect == 0x9b) && ((data->defStatus3 & 0x130400c0) == 0)) {
              IncreaseViability(&viability,3);
            }
          }
          else if ((moveEffect == 7) || (moveEffect == 0x6f)) {
            IncreaseViability(&viability,3);
          }
        }
      }
      break;
    case 158: /* EFFECT_FAKE_OUT */
      if ((move == 0xfc /* Fake Out */) && (bVar6 = ShouldUseFakeOut(bankAtk,bankDef,uVar4), bVar6 != 0)) {
        IncreaseFakeOutViability(&viability,style,bankAtk,bankDef,move);
      }
      break;
    case 164: /* EFFECT_HAIL */
      bVar6 = MoveInMovesetAndUsable(0x243 /* Aurora Veil */,bankAtk);
      if (bVar6 == 0) {
        bVar6 = IsClassDoublesSetupAttacker(style);
        if ((((bVar6 == 0) || (iVar18 = IsTypeZCrystal(data->atkItem,moveType), iVar18 == 0)) ||
            (*(char *)(gNewBS + bankAtk_ + 0x194) != '\0')) ||
           ((iVar18 = IsMegaZMoveBannedBattle(), iVar18 != 0 || (atkAbility == 0xbf /* Contrary */)))) {
          bVar6 = IsClassDoublesSetupAttacker(style);
          if ((bVar6 == 0) || (atkAbility != 0xab /* Slush Rush */)) {
            if ((((atkAbility == 0x69 /* Ice Body */) || (atkAbility == 0x3b /* Forecast */)) || (atkAbility == 0xab /* Slush Rush */)) ||
               (((((atkAbility - 0x72 & 0xff) < 2 || (iVar18 = MoveInMoveset(0x3b /* Blizzard */,bankAtk_), iVar18 != 0))
                 || (iVar18 = MoveInMoveset(0x243 /* Aurora Veil */,bankAtk_), iVar18 != 0)) ||
                (((iVar18 = MoveInMoveset(0x137 /* Weather Ball */,bankAtk_), iVar18 != 0 ||
                  (bVar6 = MoveEffectInMoveset(0x84 /* EFFECT_MORNING_SUN */,bankDef), bVar6 != 0)) ||
                 (data->atkItemEffect == 0x51)))))) {
              bVar6 = IsClassDoublesTeamSupport(style);
              if (bVar6 == 0) {
                IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
              }
              else {
                IncreaseViability(&viability,0x11);
              }
            }
          }
          else {
            IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
          }
        }
        else {
          IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
        }
      }
      else {
        bVar6 = IsClassScreener(style);
        if (bVar6 == 0) {
          bVar6 = IsClassDoublesTeamSupport(style);
          if (bVar6 != 0) {
            IncreaseViability(&viability,0x11);
          }
        }
        else {
          IncreaseViability(&viability,8);
        }
      }
      break;
    case 165: /* EFFECT_TORMENT */
      iVar18 = IsChoiceItemEffectOrAbility(data->defItemEffect,defAbility);
      if (iVar18 == 0) {
        IncreaseStatusViability(&viability,style,0,bankAtk,bankDef);
      }
      else {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 172: /* EFFECT_FOLLOW_ME */
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[data->bankAtkPartner].hp != 0)) &&
           ((move != 0x268 /* Spotlight */ && (bVar6 = IsBankIncapacitated(bankDef), bVar6 == 0)))))) &&
         (((move != 0x1c5 /* Rage Powder */ || (iVar18 = IsAffectedByPowder(bankDef_), iVar18 != 0)) &&
          ((gBattleMons[data->bankAtkPartner].hp != 0 &&
           (mVar10 = IsValidMovePrediction(bankDef,data->bankAtkPartner),
           gBattleMoves[mVar10].split != 2)))))) {
        bVar6 = IsClassDoublesUtility(style);
        if (bVar6 == 0) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
        else {
          IncreaseViability(&viability,0x10);
        }
      }
      break;
    case 173: /* EFFECT_NATURE_POWER */
      uVar11 = sub_90a3700();
LAB_090d1924:
      move = uVar11;
LAB_090d1956:
      style = AIScript_Positives(bankAtk,bankDef,move,originalViability,data);
      return style;
    case 175: /* EFFECT_TAUNT */
      if ((((data->defStatus1 & 7) == 0) || (bVar6 = MoveEffectInMoveset(0x61 /* EFFECT_SLEEP_TALK */,bankDef), bVar6 != 0))
         || (bVar6 = WillFaintFromSecondaryDamage(bankAtk), bVar6 != 0)) {
LAB_090d4d5e:
        bVar6 = StatusMoveInMoveset(bankDef);
        if (bVar6 != 0) {
          IncreaseViability(&viability,8);
        }
        if (gBattleMoves[predictedMove].split != 2) {
          uVar23 = GetBankFightingStyle(bankDef);
          bVar6 = IsClassGoodToTaunt(uVar23);
          if (bVar6 == 0) {
            bVar6 = IsClassDoublesUtility(style);
            if ((bVar6 == 0) || (bVar6 = HasProtectionMoveInMoveset(bankDef,6), bVar6 == 0)) {
              bVar6 = IsClassDoublesTeamSupport(style);
              if ((bVar6 == 0) || (bVar6 = HasProtectionMoveInMoveset(bankDef,6), bVar6 == 0)) {
                bVar6 = IsClassDoublesTrickRoomer(style);
                if ((bVar6 == 0) || (iVar18 = MoveInMoveset(0x278 /* Trick Room */,bankDef_), iVar18 == 0)) {
                  bVar6 = StatusMoveInMoveset(bankDef);
                  if (bVar6 != 0) {
                    IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
                  }
                }
                else {
                  IncreaseViability(&viability,0xd);
                }
              }
              else {
                IncreaseViability(&viability,0xd);
              }
            }
            else {
              IncreaseViability(&viability,0xf);
            }
            break;
          }
        }
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      else if (data->defSpeed < data->atkSpeed) {
        if (data->defStatus1 < 2) goto LAB_090d4d5e;
      }
      else if (data->defStatus1 < 3) goto LAB_090d4d5e;
      break;
    case 177: /* EFFECT_TRICK */
      moveEffect = data->atkItemEffect;
      if (moveEffect == 0x61) {
LAB_090d4fc2:
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      else if (moveEffect < 0x62) {
        if (moveEffect == 0x4b) {
          bVar6 = GoodIdeaToPoisonSelf(bankAtk);
          if ((bVar6 == 0) && (iVar18 = BadIdeaToPoison(bankDef_,bankAtk_), iVar18 == 0)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else if (moveEffect < 0x4c) {
          if (moveEffect != 0x1d) goto LAB_090d4e74;
          if ((data->atkItemQuality == 2) ||
             (bVar6 = MoveSplitInMoveset(data->atkItemQuality,bankDef), bVar6 == 0)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else if (moveEffect == 0x4c) {
          bVar6 = GoodIdeaToBurnSelf(bankAtk);
          if ((bVar6 == 0) && (bVar6 = BadIdeaToBurn(bankDef,bankAtk), bVar6 == 0)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else {
          if (moveEffect != 0x4d) goto LAB_090d4e74;
          iVar18 = IsOfType(bankDef_,3 /* Poison */);
          if (iVar18 == 0) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
      }
      else if (moveEffect == 0x6a) {
        iVar18 = IsRaidBattle();
        if ((((iVar18 == 0) && (iVar18 = IsDynamaxed(bankDef_), iVar18 != 0)) &&
            ('\x01' < (char)bankDef_[4].otName[gNewBS + 10])) &&
           ((bVar6 = DamagingMoveInMoveset(bankAtk), bVar6 != 0 ||
            (((int)(gBattleTypeFlags << 0x1f) < 0 &&
             ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
               (gBattleMons[data->bankAtkPartner].hp != 0)) &&
              ((gBattleMons[data->bankAtkPartner].hp != 0 &&
               (bVar6 = DamagingMoveInMoveset(data->bankAtkPartner), bVar6 != 0)))))))))) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else if (moveEffect < 0x6b) {
        if (moveEffect == 0x62) {
          iVar18 = MoveInMoveset(0x283 /* Fling */,bankDef_);
          if ((iVar18 == 0) || (iVar18 = CheckGrounding(bankDef_), iVar18 != 1)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else {
LAB_090d4e74:
          if ((move != 0x282 /* Bestow */) && (data->atkItem == 0)) {
            moveEffect = data->defItemEffect;
            if (moveEffect == 0x4d) {
              iVar18 = IsOfType(bankAtk_,3 /* Poison */);
              if (iVar18 != 0) {
                IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
              }
            }
            else if (moveEffect < 0x4e) {
              if (moveEffect == 0x4b) {
                bVar6 = GoodIdeaToPoisonSelf(bankAtk);
                if (bVar6 != 0) {
                  IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
                }
              }
              else if (moveEffect < 0x4c) {
                if (moveEffect != 0x1d) goto LAB_090d4ea2;
              }
              else {
                bVar6 = GoodIdeaToBurnSelf(bankAtk);
                if (bVar6 != 0) {
                  IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
                }
              }
            }
            else if (moveEffect == 0x62) {
              iVar18 = MoveInMoveset(0x283 /* Fling */,bankAtk_);
              if (iVar18 != 0) {
                IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
              }
            }
            else if ((moveEffect != 0x75) && (moveEffect != 0x61)) {
LAB_090d4ea2:
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
          }
        }
      }
      else {
        if (moveEffect == 0x75) goto LAB_090d4fc2;
        if (moveEffect != 0x88) goto LAB_090d4e74;
        if ((atkAbility & 0xfd) != 0x60) {
          if ((defAbility == 0x22 /* Chlorophyll */) || (defAbility == 0xcd /* Flower Gift */)) {
            if ((gBattleWeather & 0x860) != 0) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
          }
          else if ((defAbility == 0x21 /* Swift Swim */) && ((gBattleWeather & 0x1007) != 0)) {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
      }
      break;
    case 179: /* EFFECT_WISH */
      bVar6 = ShouldUseWishAromatherapy(bankAtk,bankDef,move,style);
      if (bVar6 == 0) goto sw_d11e4_32;
      IncreaseViability(&viability,8);
      break;
    case 181: /* EFFECT_INGRAIN */
      if (data->atkItemEffect == 0x68) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      else {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 182: /* EFFECT_SUPERPOWER */
      if (atkAbility == 0xbf /* Contrary */) {
        if (((move == 0x17b /* Hammer Arm */) || (move == 0x251 /* Ice Hammer */)) &&
           (bVar6 = GoodIdeaToRaiseSpeedAgainst(bankAtk,bankDef,1,data->atkSpeed,data->defSpeed),
           bVar6 != 0)) goto LAB_090d2246;
        if (move == 0x114 /* Superpower */) goto LAB_090d1a1e;
      }
      else if (data->atkItemEffect == 0x84) goto LAB_090d2f60;
      break;
    case 183: /* EFFECT_MAGIC_COAT */
      if ((gBattleMoves[predictedMove].split == 2) &&
         (moveType = GetBaseMoveTarget(predictedMove,bankDef_), (moveType & 0x48) != 0)) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 184: /* EFFECT_RECYCLE */
      if ((*(short *)(gNewBS + (gBattlerPartyIndexes[bankAtk_] + 0x7c) * 2 + 6) != 0) &&
         (data->atkItem == 0)) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 186: /* EFFECT_BRICK_BREAK */
      iVar18 = IsRaidBattle();
      if (iVar18 != 0) {
        iVar18 = GetBattlerSide(bankAtk_);
        if (((iVar18 == 0) &&
            (pBVar24 = (BattlePokemon *)gNewBS, (int)((uint)*(byte *)(gNewBS + 0x1b5) << 0x1d) < 0))
           && (pBVar24 = (BattlePokemon *)(uint)*(byte *)(gNewBS + 0x1b2),
              1 < (int)((uint)*(byte *)(gNewBS + 0x1b1) - (int)pBVar24))) {
          pBVar24 = bankDef_;
          iVar18 = MoveBlockedBySubstitute(move,bankAtk_);
          if (iVar18 == 0) {
            pBVar24 = bankDef_;
            iVar18 = AI_SpecialTypeCalc(move,bankAtk_);
            if (-1 < iVar18 << 0x1c) {
              IncreaseViability(&viability,0x12);
              break;
            }
          }
        }
      }
      uVar7 = (u8)pBVar24;
      iVar18 = GetBattlerSide(bankDef_);
      moveType = gNewBS;
      defAbility = (uint)gSideStatuses[iVar18] << 0x1e;
      uVar23 = extraout_r1_07;
      if (defAbility == 0 /* ------- */) {
        iVar18 = GetBattlerSide(bankDef_);
        defAbility = (uint)*(byte *)(moveType + iVar18 + 0x15);
        uVar23 = extraout_r1_04;
        if (defAbility == 0 /* ------- */) break;
      }
      bVar6 = GoodIdeaToSwapTimers(timers,uVar23,uVar7,(bool8)defAbility);
      if (bVar6 == 0) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      else {
        IncreaseViability(&viability,3);
      }
      break;
    case 188: /* EFFECT_KNOCK_OFF */
      moveType = data->defItemEffect - 0x61 & 0xff;
      if (((0x14 < moveType) || ((1 << moveType & 0x100003U) == 0)) &&
         ((iVar18 = sub_90745b4(bankDef_), iVar18 != 0 &&
          (bVar6 = MoveEffectInMoveset(0xb9 /* EFFECT_BLANK_185 */,bankAtk), bVar6 == 0)))) {
        if (move == 0x2d6 /* Corrode Gas */) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
        else {
          bVar6 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1);
          if (bVar6 == 0) {
            IncreaseViability(&viability,3);
          }
        }
      }
      break;
    case 191: /* EFFECT_SKILL_SWAP */
      if (move < 0x1dd) {
        if (move < 0x1db) {
          if ((move == 0x11d /* Skill Swap */) &&
             (*(char *)(atkAbility + 0x9123a05) < *(char *)(defAbility + 0x9123a05))) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
        }
        else {
LAB_090d5394:
          if ('\x04' < *(char *)(defAbility + 0x9123a05)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
      }
      else if (move == 0x218 /* Entrainment */) {
        if (((('\x04' < *(char *)(defAbility + 0x9123a05)) || (*(char *)(atkAbility + 0x9123a05) < '\x01'))
            && (defAbility != atkAbility)) && (iVar18 = IsAbilitySuppressed(bankDef_), iVar18 == 0)) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else if (move == 0x28f /* Simple Beam */) goto LAB_090d5394;
      break;
    case 192: /* EFFECT_IMPRISON */
      iVar18 = MoveInMoveset(predictedMove,bankAtk_);
      if (iVar18 == 0) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      else {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 193: /* EFFECT_REFRESH */
      if (move == 0x20d /* Psycho Shift */) {
        moveType = data->atkStatus1;
        if ((moveType & 0x88) != 0) goto sw_d11e4_33;
        if ((int)(moveType << 0x1b) < 0) goto sw_d11e4_167;
        if ((int)(moveType << 0x19) < 0) goto sw_d11e4_67;
        if ((int)(moveType << 0x1a) < 0) goto sw_d55da_3;
        if (((moveType & 7) != 0) && (moveType != 1 /* Fighting */)) goto sw_d11e4_1;
      }
      else {
LAB_090d239c:
        if ((data->atkStatus1 & 0xff) != 0) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      break;
    case 1: /* EFFECT_SLEEP */
    case 187: /* EFFECT_YAWN */
    case 0:
sw_d11e4_1:
      IncreaseSleepViability(&viability,style,bankAtk,bankDef,move);
      break;
    case 195: /* EFFECT_SNATCH */
      if ((int)((uint)gBattleMoves[predictedMove].flags << 0x1c) < 0) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 197: /* EFFECT_SECRET_POWER */
      uVar12 = CalcSecondaryEffectChance(bankAtk,move,uVar23);
      if ((0x3b < uVar12) &&
         (iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar18 == 0)) {
        moveType = sub_90a404c();
        moveType = (moveType & 0x3f) - 1;
        if (moveType < 0x22) {
                              switch(moveType) {
          case 67: /* EFFECT_PARALYZE */
          case 4:
          case 3:
            goto sw_d11e4_67;
          case 167: /* EFFECT_WILL_O_WISP */
          case 2:
          case 1:
            goto sw_d11e4_167;
          case 33: /* EFFECT_TOXIC */
          case 66: /* EFFECT_POISON */
          case 0:
          case 4:
            goto sw_d11e4_33;
          case 3:
          case 2:
            goto sw_d55da_3;
          case 31: /* EFFECT_FLINCH_HIT */
          case 7:
          case 6:
            goto sw_d11e4_31;
          case 18: /* EFFECT_ATTACK_DOWN */
          case 58: /* EFFECT_ATTACK_DOWN_2 */
          case 21:
            goto sw_d11e4_18;
          case 19: /* EFFECT_DEFENSE_DOWN */
          case 59: /* EFFECT_DEFENSE_DOWN_2 */
          case 22:
            goto sw_d11e4_19;
          case 23:
            goto sw_d55da_23;
          case 21: /* EFFECT_SPECIAL_ATTACK_DOWN */
          case 61: /* EFFECT_SPECIAL_ATTACK_DOWN_2 */
          case 24:
            goto sw_d11e4_21;
          case 22: /* EFFECT_SPECIAL_DEFENSE_DOWN */
          case 62: /* EFFECT_SPECIAL_DEFENSE_DOWN_2 */
          case 25:
            goto sw_d11e4_22;
          case 23: /* EFFECT_ACCURACY_DOWN */
          case 63: /* EFFECT_ACCURACY_DOWN_2 */
          case 26:
            goto sw_d11e4_23;
          case 24: /* EFFECT_EVASION_DOWN */
          case 64: /* EFFECT_EVASION_DOWN_2 */
          case 27:
            goto sw_d11e4_24;
          case 49: /* EFFECT_CONFUSE */
          case 6:
            goto sw_d11e4_49;
          case 1: /* EFFECT_SLEEP */
          case 187: /* EFFECT_YAWN */
          case 0:
            goto sw_d11e4_1;
          case 33:
            if (atkAbility != 0xbf /* Contrary */) {
              uVar11 = viability & 0xff;
              bVar6 = RealPhysicalMoveInMoveset(bankAtk);
              if ((((((bVar6 == 0) || (6 < gBattleMons[bankAtk_].statStages[0])) ||
                    (bVar6 = GoodIdeaToRaiseAttackAgainst(bankAtk,bankDef,1), bVar6 == 0)) ||
                   (IncreaseStatViability(&viability,style,3,bankAtk,bankDef,move,0xfe,7),
                   viability == uVar11)) &&
                  (((bVar6 = SpecialMoveInMoveset(bankAtk), bVar6 == 0 ||
                    (6 < gBattleMons[bankAtk_].statStages[3])) ||
                   ((bVar6 = GoodIdeaToRaiseSpAttackAgainst(bankAtk,bankDef,1), bVar6 == 0 ||
                    (IncreaseStatViability(&viability,style,3,bankAtk,bankDef,move,0xfe,7),
                    viability == uVar11)))))) &&
                 ((gBattleMons[bankAtk_].statStages[2] < 7 &&
                  (bVar6 = GoodIdeaToRaiseSpeedAgainst
                                     (bankAtk,bankDef,1,data->atkSpeed,data->defSpeed), bVar6 != 0))
                 )) {
                IncreaseStatViability(&viability,style,3,bankAtk,bankDef,move,0xfe,7);
              }
            }
          }
        }
      }
      break;
    case 201: /* EFFECT_MUD_SPORT */
      bVar6 = DamagingMoveTypeInMoveset(bankDef,0xd /* Electric */);
      if ((bVar6 != 0) && (bVar6 = DamagingMoveTypeInMoveset(bankAtk,0xd /* Electric */), bVar6 == 0)) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 210: /* EFFECT_WATER_SPORT */
      bVar6 = DamagingMoveTypeInMoveset(bankDef,10 /* Fire */);
      if ((bVar6 != 0) && (bVar6 = DamagingMoveTypeInMoveset(bankAtk,10 /* Fire */), bVar6 == 0)) {
        IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
      }
      break;
    case 213: /* EFFECT_STAT_SWAP_SPLIT */
      if (move == 0x21d /* Heart Swap */) {
        bVar2 = false;
        iVar18 = 1;
        do {
          if (gBattleMons[(int)bankDef_].statStages[iVar18 + -1] <
              gBattleMons[bankAtk_].statStages[iVar18 + -1]) goto sw_d11e4_0;
          if (gBattleMons[bankAtk_].statStages[iVar18 + -1] <
              gBattleMons[(int)bankDef_].statStages[iVar18 + -1]) {
            bVar2 = true;
          }
          iVar18 = iVar18 + 1;
        } while (iVar18 != 8);
        if (bVar2) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else if (move < 0x21e) {
        if (move == 0x20b /* Power Swap */) {
          if (gBattleMons[bankAtk_].statStages[0] < gBattleMons[(int)bankDef_].statStages[0]) {
            if (gBattleMons[bankAtk_].statStages[3] <= gBattleMons[(int)bankDef_].statStages[3]) {
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
          }
          else if ((gBattleMons[bankAtk_].statStages[3] < gBattleMons[(int)bankDef_].statStages[3]) &&
                  (gBattleMons[bankAtk_].statStages[0] <= gBattleMons[(int)bankDef_].statStages[0])) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
        }
        else if (move == 0x20c /* Power Trick */) {
          if (((-1 < (int)(data->atkStatus3 << 5)) && (data->atkAttack < data->atkDefense)) &&
             (bVar6 = PhysicalMoveInMoveset(bankAtk), bVar6 != 0)) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else if (move == 0x207 /* Guard Swap */) {
          if (gBattleMons[bankAtk_].statStages[1] < gBattleMons[(int)bankDef_].statStages[1]) {
            if (gBattleMons[bankAtk_].statStages[4] <= gBattleMons[(int)bankDef_].statStages[4]) {
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
          }
          else if ((gBattleMons[bankAtk_].statStages[4] < gBattleMons[(int)bankDef_].statStages[4]) &&
                  (gBattleMons[bankAtk_].statStages[1] <= gBattleMons[(int)bankDef_].statStages[1])) {
            IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
          }
        }
      }
      else if (move == 0x286 /* Guard Split */) {
        moveType = (uint)data->atkDefense;
        defAbility = (uint)data->atkSpDef;
        uVar25 = data->defDefense + moveType >> 1;
        uVar28 = data->defSpDef + defAbility >> 1;
        if (moveType < uVar25) {
          if (defAbility <= uVar28) goto LAB_090d5980;
        }
        else if ((defAbility < uVar28) && (moveType <= uVar25)) {
LAB_090d5980:
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else if (move == 0x28d /* Power Split */) {
        moveType = (uint)data->atkAttack;
        defAbility = (uint)data->atkSpAtk;
        uVar25 = data->defAttack + moveType >> 1;
        uVar28 = data->defSpAtk + defAbility >> 1;
        if (moveType < uVar25) {
          if (defAbility <= uVar28) goto LAB_090d59b4;
        }
        else if ((defAbility < uVar28) && (moveType <= uVar25)) {
LAB_090d59b4:
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else if ((move == 0x266 /* Speed Swap */) && (data->atkSpeed < data->defSpeed)) {
        IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
      }
      break;
    case 221: /* EFFECT_SMACK_DOWN */
      iVar18 = CheckGrounding(bankDef_);
      if ((iVar18 != 1) && (iVar18 = Random(iVar18), -1 < iVar18 << 0x1f)) {
        IncreaseViability(&viability,3);
      }
      break;
    case 222: /* EFFECT_REMOVE_TARGET_STAT_CHANGES */
      iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
      if ((iVar18 == 0) && (bVar6 = ShouldPhaze(bankAtk,bankDef,move,style), bVar6 != 0)) {
        bVar6 = IsClassDoublesPhazer(style);
        if (bVar6 == 0) {
          bVar6 = IsClassPhazer(style);
          if (bVar6 == 0) {
            bVar6 = IsClassDoublesSetupAttacker(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0xc);
            }
          }
          else {
            IncreaseViability(&viability,8);
          }
        }
        else {
          IncreaseViability(&viability,0x10);
        }
      }
      break;
    case 223: /* EFFECT_RELIC_SONG */
      if (data->atkSpecies == 0x2bd) {
        if (data->defDefense < data->defSpDef) {
          IncreaseViability(&viability,3);
        }
      }
      else if ((data->atkSpecies == 0x2ea) && (data->defSpDef < data->defDefense)) {
        IncreaseViability(&viability,3);
      }
      break;
    case 226: /* EFFECT_SET_TERRAIN */
      if (((data->atkStatus3 & 0x1800) != 0) && (iVar18 = CheckGrounding(bankAtk_), iVar18 != 0)) {
        if (move < 0x3a0) {
          if (((0x39d < move) || (move == 0x271 /* Elec Terrain */)) || (move == 0x273 /* Mist Terrain */))
          goto LAB_090d5aba;
        }
        else if (move - 0x3a8 < 2) {
LAB_090d5aba:
          IncreaseFakeOutViability(&viability,style,bankAtk,bankDef,move);
        }
      }
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
          (gBattleMons[data->bankAtkPartner].hp != 0)))) {
        bVar6 = IsClassDoublesSetupAttacker(style);
        if (bVar6 == 0) {
          bVar6 = IsClassDoublesTeamSupport(style);
          if (((bVar6 == 0) || (gBattleMons[data->bankAtkPartner].hp == 0)) ||
             (bVar6 = MoveInMovesetAndUsable(0x2c9 /* Expand Force */,data->bankAtkPartner), bVar6 == 0)) {
            bVar6 = IsClassDoublesUtility(style);
            if (((bVar6 == 0) || (gBattleMons[data->bankAtkPartner].hp == 0)) ||
               (bVar6 = MoveInMovesetAndUsable(0x2c9 /* Expand Force */,data->bankAtkPartner), bVar6 == 0)) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0xf);
            }
          }
          else {
            IncreaseViability(&viability,0xf);
          }
        }
        else {
          IncreaseViability(&viability,0x11);
        }
      }
      else {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 227: /* EFFECT_PLEDGE */
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[data->bankAtkPartner].hp != 0)) &&
          (bVar6 = MoveEffectInMoveset(0xe3 /* EFFECT_PLEDGE */,data->bankAtkPartner), bVar6 != 0)))) {
        IncreaseViability(&viability,0x14);
      }
      break;
    case 228: /* EFFECT_FIELD_EFFECTS */
      if (move == 0x285 /* Gravity */) {
LAB_090d5cd0:
        iVar18 = sub_90750c4();
        if (iVar18 == 0) {
          bVar6 = SleepMoveInMovesetWithLowAccuracy(bankAtk,bankDef);
          if (bVar6 == 0) {
            if (atkAbility != 0x1a /* Levitate */) {
              bVar6 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,0x5a,0);
              if (bVar6 == 0) {
                IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
              }
              else {
                IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
              }
            }
          }
          else {
            IncreaseSleepViability(&viability,style,bankAtk,bankDef,move);
          }
        }
      }
      else if (move < 0x286) {
        if (move == 0x279 /* Magic Room */) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
        else if (move == 0x27a /* Wonder Room */) {
          bVar6 = RealPhysicalMoveInMoveset(bankDef);
          if (((bVar6 != 0) && (data->atkDefense < data->atkSpDef)) ||
             ((bVar6 = SpecialMoveInMoveset(bankDef), bVar6 != 0 &&
              (data->atkSpDef < data->atkDefense)))) {
            IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
          }
        }
        else if ((move == 0x278 /* Trick Room */) && (iVar18 = IsTrickRoomActive(), iVar18 == 0)) {
          move = GetPokemonOnSideSpeedAverage(bankAtk);
          uVar12 = GetPokemonOnSideSpeedAverage(bankDef);
          if (move < uVar12) {
            bVar6 = IsClassDoublesTrickRoomer(style);
            if (bVar6 == 0) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
            }
            else {
              IncreaseViability(&viability,0x13);
            }
          }
        }
      }
      else if (move == 0x288 /* Ion Deluge */) {
        if ((((atkAbility == 10 /* Volt Absorb */) || (atkAbility == 0x50 /* Motor Drive */)) || (atkAbility == 0x1f /* Lightning Rod */)) &&
           (iVar18 = GetMoveTypeSpecial(bankDef_,predictedMove), iVar18 == 0)) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else if ((0x287 < move) && (move - 0x3ce < 2)) goto LAB_090d5cd0;
      break;
    case 229: /* EFFECT_FLING */
      iVar18 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
      if ((iVar18 == 0) && ((byte)(&UNK_09157a29)[(uint)data->atkItem * 2] - 2 < 7)) {
                            switch((byte)(&UNK_09157a29)[(uint)data->atkItem * 2] - 2) {
        case 67: /* EFFECT_PARALYZE */
        case 4:
        case 3:
          goto sw_d11e4_67;
        case 167: /* EFFECT_WILL_O_WISP */
        case 2:
        case 1:
          goto sw_d11e4_167;
        case 33: /* EFFECT_TOXIC */
        case 66: /* EFFECT_POISON */
        case 0:
        case 4:
          goto sw_d11e4_33;
        case 3:
        case 2:
          goto sw_d55da_3;
        case 31: /* EFFECT_FLINCH_HIT */
        case 7:
        case 6:
          goto sw_d11e4_31;
        }
      }
      break;
    case 230: /* EFFECT_FEINT */
      if (gBattleMoves[predictedMove].effect == 0x6f /* EFFECT_PROTECT */) {
        IncreaseViability(&viability,3);
      }
      break;
    case 231: /* EFFECT_ATTACK_BLOCKERS */
      if (move == 0x28c /* Powder */) {
        if ((gBattleMoves[predictedMove].split != 2) &&
           (iVar18 = GetMoveTypeSpecial(bankDef_,predictedMove), iVar18 == 10)) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      else if (move < 0x28d) {
        if (move == 0x26d /* Throat Chop */) {
          pBVar27 = bankDef_;
          bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
          uVar23 = (u8)pBVar27;
          moveEffect = extraout_r1_05;
          if (bVar6 != 0) {
            iVar18 = sub_9073ba8(predictedMove);
            moveEffect = extraout_r1_06;
            if (iVar18 != 0) {
              IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
              break;
            }
          }
          if ((int)(gBattleTypeFlags << 0x1f) < 0) {
            if ((gBattleMons[data->foe1].hp == 0) || (gBattleMons[data->foe2].hp == 0)) {
              moveEffect = data->bankAtkPartner;
              uVar23 = moveEffect * 'X';
              if (gBattleMons[moveEffect].hp == 0) goto LAB_090d6082;
            }
            IncreaseDoublesDamageViabilityToScore(&viability,style,5,bankAtk,bankDef);
          }
          else {
LAB_090d6082:
            bVar6 = GoodIdeaToSwapTimers(timers,moveEffect,uVar23,0);
            if ((bVar6 != 0) && (bVar6 = SoundMoveInMoveset(bankDef), bVar6 != 0)) {
              IncreaseViability(&viability,3);
            }
          }
        }
        else {
LAB_090d5f4a:
          bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
          if ((bVar6 == 0) || (iVar18 = func_0x090db4b8(bankDef_,bankAtk_), iVar18 == 0)) {
            bVar6 = HealingMoveInMoveset(bankDef);
            if (((bVar6 != 0) || (data->defItemEffect == 0x2b)) ||
               ((data->defItemEffect == 0x4d && (iVar18 = IsOfType(bankDef_,3 /* Poison */), iVar18 != 0)))) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
          }
          else {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
      }
      else if (move == 0x291 /* Telekinesis */) {
        bVar6 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,0x5a,0);
        if (bVar6 != 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else {
        if (move != 0x299 /* Embargo */) goto LAB_090d5f4a;
        if (data->defItemEffect != 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 232: /* EFFECT_TYPE_CHANGES */
      if ((move == 0x292 /* TrickoTreat */) || (move == 0x294 /* Woods Curse */)) {
        if (defAbility == 0x19 /* Wonder Guard */) {
          IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
        }
      }
      else if (((move == 0x290 /* Soak */) &&
               (bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,0x90,0x90), bVar6 != 0)) &&
              ((bVar6 = DamagingMoveTypeInMoveset(bankAtk,0xd /* Electric */), bVar6 != 0 ||
               (bVar6 = DamagingMoveTypeInMoveset(bankAtk,0xc /* Grass */), bVar6 != 0)))) {
        IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
      }
      break;
    case 234: /* EFFECT_TOPSY_TURVY_ELECTRIFY */
      if (move == 0x298 /* Electrify */) {
        iVar18 = GetMoveTypeSpecial(bankDef_,predictedMove);
        if ((iVar18 == 0) && (((atkAbility == 10 /* Volt Absorb */ || (atkAbility == 0x50 /* Motor Drive */)) || (atkAbility == 0x1f /* Lightning Rod */)))) {
          IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
        }
      }
      else {
        uVar23 = CountBanksPositiveStatStages(bankDef);
        uVar7 = CountBanksNegativeStatStages(bankDef);
        if (uVar7 < uVar23) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 235: /* EFFECT_FAIRY_LOCK_HAPPY_HOUR */
      if (move - 0x29a < 0xc) {
                            switch(move - 0x29a) {
        case 0:
          bVar6 = IsTrapped(bankDef,1);
          if ((bVar6 == 0) && (bVar6 = ShouldTrap(bankAtk,bankDef,0x29a,style), bVar6 != 0)) {
            IncreaseViability(&viability,8);
          }
          break;
        case 6:
        case 10:
        case 11:
          if ((((*(char *)(gNewBS + bankAtk_ + 0x194) == '\0') &&
               (iVar18 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type), iVar18 != 0))
              && (iVar18 = IsMegaZMoveBannedBattle(), iVar18 == 0)) &&
             (iVar18 = func_0x090db548(bankDef_,bankAtk_), iVar18 == 0)) {
            IncreaseViability(&viability,9);
          }
        }
      }
      break;
    case 236: /* EFFECT_INSTRUCT_AFTER_YOU_QUASH */
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[data->bankAtkPartner].hp != 0)) &&
          ((move == 0x29f /* Quash */ &&
           (bVar6 = MoveWouldHitFirst(data->partnerMove,(ushort)data->bankAtkPartner,(ushort)bankDef
                                     ), bVar6 == 0)))))) {
        bVar6 = IsClassDoublesTeamSupport(style);
        if (bVar6 == 0) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
        else {
          IncreaseViability(&viability,7);
        }
      }
      break;
    case 239: /* EFFECT_TEAM_EFFECTS */
      if (move == 0x289 /* Lucky Chant */) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[data->bankAtkPartner].hp != 0)))) {
          bVar6 = IsClassDoublesTeamSupport(style);
          if ((bVar6 != 0) && (moveType = ViableMonCountFromBank(bankDef_), 1 < moveType)) {
            IncreaseViability(&viability,8);
          }
        }
        else {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      else if (move == 0x28a /* Magnet Rise */) {
        iVar18 = CheckGrounding(bankAtk_);
        if (((iVar18 == 1) && (bVar6 = DamagingMoveTypeInMoveset(bankDef,4 /* Ground */), bVar6 != 0)) &&
           (moveType = AI_SpecialTypeCalc(0x59,bankDef_,bankAtk_), (moveType & 0xc) == 0)) {
          bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
          if ((bVar6 == 0) || (iVar18 = GetMoveTypeSpecial(bankDef_,predictedMove), iVar18 != 4)) {
            iVar18 = GetMoveTypeSpecial(bankDef_,predictedMove);
            if (iVar18 == 4) {
              IncreaseStatusViability(&viability,style,2,bankAtk,bankDef);
            }
            else {
              IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
            }
          }
          else {
            IncreaseStatusViability(&viability,style,3,bankAtk,bankDef);
          }
        }
      }
      else if (move == 0x1d8 /* Tailwind */) {
        IncreaseTailwindViability(&viability,style,bankAtk,bankDef);
      }
      break;
    case 240: /* EFFECT_CAMOUFLAGE */
      bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (bVar6 != 0) {
        if (moveSplit == 2) goto LAB_090d5552;
        iVar18 = AI_SpecialTypeCalc(predictedMove,bankDef_,bankAtk_);
        if (-1 < iVar18 << 0x1c) {
          IncreaseStatusViability(&viability,style,1,bankAtk,bankDef);
        }
      }
      break;
    case 241: /* EFFECT_FLAMEBURST */
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[data->bankAtkPartner].hp != 0)) &&
            ((pbVar30 = &data->bankDefPartner, gBattleMons[*pbVar30].hp != 0 &&
             (moveType = func_0x090dd734(), moveType < 0xc)))) &&
           (iVar18 = GetBankAbility(*pbVar30), iVar18 != 0x73)))) &&
         (iVar18 = IsOfType(*pbVar30,10), iVar18 == 0)) {
        IncreaseDoublesDamageViabilityToScore(&viability,style,10,bankAtk,bankDef);
      }
      break;
    case 242: /* EFFECT_LAST_RESORT */
      if (move == 0x2a3 /* Sky Drop */) {
        uVar23 = 0xa3;
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          if ((gBattleMons[data->foe1].hp == 0) ||
             (checkConfusion = data->foe2 * 'X', gBattleMons[data->foe2].hp == 0)) {
            checkConfusion = data->bankAtkPartner;
            uVar23 = checkConfusion * 'X';
            if (gBattleMons[checkConfusion].hp == 0) goto LAB_090d65b2;
          }
          bVar6 = IsTakingSecondaryDamage(bankDef,checkConfusion);
          if (bVar6 != 0) {
            IncreaseDoublesDamageViabilityToScore(&viability,style,5,bankAtk,bankDef);
          }
        }
        else {
LAB_090d65b2:
          bVar6 = GoodIdeaToSwapTimers(timers,checkConfusion,uVar23,0);
          if ((bVar6 != 0) &&
             (bVar6 = IsTakingSecondaryDamage(bankDef,checkConfusion_00), bVar6 != 0)) {
            IncreaseViability(&viability,3);
          }
        }
      }
    }
  }
sw_d11e4_0:
  if (moveSplit == 2) goto LAB_090d5552;
  auStack_1a[0] = viability;
  move = (u16)move;
  if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
     (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
      (gBattleMons[data->bankAtkPartner].hp != 0)))) {
    IncreaseDoublesDamageViability((s16 *)auStack_1a,style,bankAtk,bankDef,move);
  }
  else {
    bVar6 = IsPredictedToSwitch(bankDef,bankAtk);
    if (((bVar6 == 0) &&
        (bVar6 = MoveKnocksOutPossiblyGoesFirstWithBestAccuracy(move,bankAtk,bankDef,1), bVar6 != 0
        )) && ((moveType = AccuracyCalc(move,bankAtk_,bankDef_), 0x45 < moveType ||
               ((bVar6 = MoveThatCanHelpAttacksHitInMoveset(bankAtk), bVar6 == 0 ||
                (bVar6 = CanKnockOut(bankDef,bankAtk), bVar6 != 0)))))) {
      if (((gBattleMoves[predictedMove].effect != 0xed /* EFFECT_SUCKER_PUNCH */) ||
          ((bVar6 = IsClassDamager(style), bVar6 != 0 ||
           ((moveSplit = PriorityCalc(bankAtk_,0,move), 0 < moveSplit &&
            (data->defSpeed < data->atkSpeed)))))) &&
         ((-1 < (int)(data->defStatus2 << 6) || (bVar6 = CanKnockOut(bankDef,bankAtk), bVar6 != 0)))
         ) {
LAB_090d679e:
        uVar4 = 9;
        goto LAB_090d67a6;
      }
    }
    else {
      bVar6 = IsPredictedToSwitch(bankDef,bankAtk);
      if (((((bVar6 == 0) && (bVar6 = MoveEffectInMoveset(0x6f /* EFFECT_PROTECT */,bankAtk), bVar6 == 0)) &&
           (bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar6 == 0)) &&
          (bVar6 = MoveKnocksOutPossiblyGoesFirstWithBestAccuracy(move,bankAtk,bankDef,0),
          bVar6 != 0)) &&
         (((bVar6 = WillFaintFromSecondaryDamage(bankDef), bVar6 == 0 &&
           (bVar6 = HighChanceOfBeingImmobilized(bankDef), bVar6 == 0)) ||
          ((moveSplit = func_0x090db4b8(bankDef_,bankAtk_), moveSplit != 0 ||
           (moveSplit = IsMoxieAbility(atkAbility), moveSplit != 0)))))) {
        IncreaseViabilityForSlowKOMove((s16 *)auStack_1a,style,bankAtk,bankDef);
      }
      else {
        if (-1 < (int)(gBattleTypeFlags << 4)) {
          if (*(char *)(gNewBS + bankAtk_ + 0x8a0) != '\0') {
            moveEffect = 0x4b;
            if ((*(ushort *)(&gLastPrintedMoves + (int)bankDef_ * 2) != 0) &&
               (gBattleMoves[*(ushort *)(&gLastPrintedMoves + (int)bankDef_ * 2)].split == 2)) {
              moveEffect = 0x19;
            }
            if (moveEffect <= gBattleResources->ai->simulatedRNG[3]) goto LAB_090d66de;
          }
          bVar6 = MoveEffectInMoveset(0x6f /* EFFECT_PROTECT */,bankAtk);
          if (((((((bVar6 == 0) &&
                  (((bVar6 = IsTakingSecondaryDamage(bankDef,checkConfusion_01), bVar6 == 0 &&
                    (moveSplit = func_0x090db1c4(bankDef_), moveSplit == 0)) ||
                   (moveSplit = sub_90dfd28(bankAtk_,bankDef_), moveSplit == 0)))) &&
                 ((bVar6 = MoveKnocksOutXHits(move,bankDef,bankAtk,1), bVar6 != 0 &&
                  (bVar6 = StrongestMoveGoesFirst(move,bankAtk,bankDef), bVar6 != 0)))) &&
                ((bVar6 = IsClassEntryHazards(style), bVar6 == 0 ||
                 ((int)((uint)gBattleResources->ai->simulatedRNG[3] << 0x1f) < 0)))) &&
               ((bVar6 = IsClassPhazer(style), bVar6 == 0 ||
                ((moveSplit = PriorityCalc(bankAtk_,0,move), 0 < moveSplit &&
                 (data->atkSpeed < data->defSpeed)))))) &&
              ((bVar6 = IsClassKillerSweeper(style), bVar6 == 0 ||
               ((moveSplit = PriorityCalc(bankAtk_,0,move), 0 < moveSplit &&
                (data->atkSpeed < data->defSpeed)))))) &&
             ((((*(uint *)(&gBitTable + bankAtk_ * 4) & (uint)*(byte *)(gNewBS + 0x1c5)) == 0 &&
               ((bVar6 = MoveInMovesetAndUsable(0xfc /* Fake Out */,bankAtk), bVar6 == 0 ||
                (bVar6 = ShouldUseFakeOut(bankAtk,bankDef,uVar4), bVar6 == 0)))) &&
              ((gBattleMoves[predictedMove].effect != 0xed /* EFFECT_SUCKER_PUNCH */ ||
               ((bVar6 = IsClassDamager(style), bVar6 != 0 ||
                ((moveSplit = PriorityCalc(bankAtk_,0,move), 0 < moveSplit &&
                 (data->defSpeed < data->atkSpeed)))))))))) goto LAB_090d679e;
        }
LAB_090d66de:
        bVar6 = IsStrongestMove(move,bankAtk,bankDef);
        if ((bVar6 != 0) &&
           (((((bVar6 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar6 != 0 ||
               (bVar8 = WillFaintFromSecondaryDamage(bankDef), bVar8 == 0)) ||
              (moveSplit = func_0x090db4b8(bankDef_,bankAtk_), moveSplit != 0)) ||
             (moveSplit = IsMoxieAbility(atkAbility), moveSplit != 0)) &&
            (((-1 < (int)(data->defStatus2 << 6) ||
              (bVar8 = CanKnockOut(bankDef,bankAtk), bVar8 != 0)) || (bVar6 == 0)))))) {
          if (((auStack_1a[0] == 100) &&
              (bVar6 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar6 != 0)) &&
             ((moveSplit = func_0x090db5e4(bankDef_,bankAtk_), moveSplit == 0 &&
              (moveSplit = func_0x090db4b8(bankDef_,bankAtk_), moveSplit == 0)))) {
            bVar6 = IsClassCleric(style);
            uVar4 = 5;
            if (bVar6 == 0) {
              bVar6 = IsClassSupportScreener(style);
              if ((bVar6 == 0) && (bVar6 = IsClassBatonPass(style), bVar6 == 0)) {
                bVar6 = IsClassPhazer(style);
                if ((bVar6 == 0) && (bVar6 = IsClassKillerSweeper(style), bVar6 == 0)) {
                  bVar6 = IsClassEntryHazards(style);
                  uVar4 = 4;
                  if (bVar6 == 0) goto LAB_090d692a;
                }
                else {
                  uVar4 = 8;
                }
              }
              else {
                uVar4 = 6;
              }
            }
          }
          else {
LAB_090d692a:
            uVar4 = 2;
          }
LAB_090d67a6:
          IncreaseViability((s16 *)auStack_1a,uVar4);
        }
      }
    }
  }
  viability = auStack_1a[0];
LAB_090d5552:
  if (((int)(data->atkStatus1 << 0x1a) < 0) &&
     (moveSplit = CheckTableForMove(move,&UNK_09040180), moveSplit != 0)) {
    style = 0x14;
    if (-1 < (int)(gBattleTypeFlags << 0x1f)) {
      style = 10;
    }
    IncreaseViability(&viability,style);
  }
  style = MathMin((int)(short)viability,0xff);
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return style;
}

// ---- AIScript_SemiSmart  (ROM 0x90d6998)
u8 AIScript_SemiSmart(u8 bankAtk,u8 bankDef,u16 originalMove,u8 originalViability,AIScript *data)

{
  byte bVar1;
  u8 uVar2;
  bool8 bVar3;
  u16 checkMove;
  move_t move;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ushort auStack_1a [3];
  
  if ((int)(gBattleResources->ai->aiFlags << 0x1d) < 0) {
    return originalViability;
  }
  checkMove = TryReplaceMoveWithZMove(bankAtk,bankDef,originalMove);
  uVar4 = (uint)checkMove;
  auStack_1a[0] = (ushort)originalViability;
  if ((gBattleTypeFlags << 0x1f < 0) &&
     ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
       (gBattleMons[data->bankAtkPartner].hp != 0)) && (data->bankAtkPartner == bankDef)))) {
    uVar2 = AIScript_Partner(bankAtk,bankDef,originalMove,originalViability,data);
    return uVar2;
  }
  uVar6 = (uint)gBattleMoves[uVar4].effect;
  if (uVar6 == 0x72) goto LAB_090d6a56;
  if (uVar6 < 0x73) {
    if (uVar6 < 0x36) {
      if (0x33 < uVar6) goto LAB_090d6a56;
      if (uVar6 < 0x22) {
        if (0x1e < uVar6) goto LAB_090d6a56;
        if (uVar6 < 0xe) {
          if ((0xb < uVar6) || (uVar6 < 0xb)) goto LAB_090d6a56;
        }
        else if (uVar6 == 0x1d) goto LAB_090d6a56;
      }
      else {
        if (uVar6 == 0x2c) goto LAB_090d6a56;
        if (0x2c < uVar6) {
          uVar7 = uVar6 - 0x31;
          goto LAB_090d6b08;
        }
        if (uVar6 == 0x25) goto LAB_090d6a56;
      }
    }
    else {
      if (uVar6 < 0x5d) {
        if ((0x59 < uVar6) || (uVar6 == 0x4c)) goto LAB_090d6a56;
        if (uVar6 < 0x4d) {
          uVar7 = uVar6 - 0x42;
        }
        else {
          if (uVar6 == 0x4f) goto LAB_090d6a56;
          uVar7 = uVar6 - 0x54;
          if (uVar6 < 0x4f) goto LAB_090d6a6c;
        }
      }
      else {
        if (uVar6 == 0x68) goto LAB_090d6a56;
        uVar7 = uVar6 - 0x61;
        if (0x68 < uVar6) {
          if ((uVar6 == 0x6b) || (uVar6 == 0x6f)) goto LAB_090d6a56;
          goto LAB_090d6a6c;
        }
      }
LAB_090d6b08:
      if (uVar7 < 2) {
LAB_090d6a56:
        uVar2 = AIScript_Positives(bankAtk,bankDef,originalMove,originalViability,data);
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
        return uVar2;
      }
    }
  }
  else if (uVar6 < 0xae) {
    if (0xab < uVar6) goto LAB_090d6a56;
    if (uVar6 < 0x9d) {
      if ((0x9a < uVar6) || (uVar6 == 0x7f)) goto LAB_090d6a56;
      if (uVar6 < 0x80) {
        if (uVar6 - 0x75 < 4) goto LAB_090d6a56;
      }
      else if (((uVar6 == 0x8b) || (uVar6 == 0x8e)) || (uVar6 == 0x84)) goto LAB_090d6a56;
    }
    else {
      if (uVar6 == 0xa2) goto LAB_090d6a56;
      if (0xa2 < uVar6) {
        uVar7 = uVar6 + 0x5a;
        goto LAB_090d6b8c;
      }
      if ((uVar6 == 0x9e) || (uVar6 == 0xa0)) goto LAB_090d6a56;
    }
  }
  else if (uVar6 < 0xd2) {
    if ((0xce < uVar6) || (uVar6 == 0xb7)) goto LAB_090d6a56;
    if (uVar6 < 0xb8) {
      if (uVar6 == 0xb3) goto LAB_090d6a56;
    }
    else if ((uVar6 + 0x46 & 0xff) < 3) goto LAB_090d6a56;
  }
  else {
    if (uVar6 == 0xdf) goto LAB_090d6a56;
    uVar7 = uVar6 + 0x2d;
    if (uVar6 < 0xe0) {
LAB_090d6b8c:
      uVar7 = uVar7 & 0xff;
      goto LAB_090d6b08;
    }
    if (((uVar6 == 0xe6) || (uVar6 == 0xf3)) || (uVar6 == 0xe3)) goto LAB_090d6a56;
  }
LAB_090d6a6c:
  if (gBattleMoves[uVar4].split == 2) goto LAB_090d6aca;
  move = IsValidMovePrediction(bankDef,bankAtk);
  bVar3 = MoveKnocksOutPossiblyGoesFirstWithBestAccuracy(checkMove,bankAtk,bankDef,1);
  if ((bVar3 == 0) ||
     (((uVar6 = AccuracyCalc(uVar4,bankAtk,bankDef), uVar6 < 0x46 &&
       (bVar3 = MoveThatCanHelpAttacksHitInMoveset(bankAtk), bVar3 != 0)) &&
      (bVar3 = CanKnockOut(bankDef,bankAtk), bVar3 == 0)))) {
    bVar3 = MoveEffectInMoveset(0x6f /* EFFECT_PROTECT */,bankAtk);
    if (((bVar3 == 0) &&
        (bVar3 = MoveWouldHitFirst(checkMove,(ushort)bankAtk,(ushort)bankDef), bVar3 == 0)) &&
       ((bVar3 = Can2HKO(bankDef,bankAtk), bVar3 != 0 &&
        (bVar3 = MoveKnocksOutPossiblyGoesFirstWithBestAccuracy(checkMove,bankAtk,bankDef,0),
        bVar3 != 0)))) {
      uVar2 = 8;
    }
    else {
      bVar3 = MoveEffectInMoveset(0x6f /* EFFECT_PROTECT */,bankAtk);
      if ((((bVar3 == 0) && (bVar3 = MoveKnocksOutXHits(move,bankDef,bankAtk,1), bVar3 != 0)) &&
          (bVar3 = StrongestMoveGoesFirst(checkMove,bankAtk,bankDef), bVar3 != 0)) &&
         (iVar5 = MoveInMoveset(0xfc /* Fake Out */,bankAtk), iVar5 == 0)) goto LAB_090d6abc;
      bVar3 = IsStrongestMove(checkMove,bankAtk,bankDef);
      if ((bVar3 == 0) ||
         (((bVar3 = MoveWouldHitFirst(checkMove,(ushort)bankAtk,(ushort)bankDef), bVar3 == 0 &&
           (bVar3 = WillFaintFromSecondaryDamage(bankDef), bVar3 != 0)) &&
          (((iVar5 = func_0x090db4b8(bankDef,bankAtk), iVar5 == 0 &&
            ((bVar1 = data->atkAbility, bVar1 != 0x76 && (bVar1 != 0x4d)))) && (bVar1 != 0x9d))))))
      goto LAB_090d6aca;
      uVar2 = 2;
    }
  }
  else {
LAB_090d6abc:
    uVar2 = 9;
  }
  IncreaseViability((s16 *)auStack_1a,uVar2);
LAB_090d6aca:
  if (((int)(data->atkStatus1 << 0x1a) < 0) &&
     (iVar5 = CheckTableForMove(uVar4,&UNK_09040180), iVar5 != 0)) {
    uVar2 = 0x14;
    if (-1 < gBattleTypeFlags << 0x1f) {
      uVar2 = 10;
    }
    IncreaseViability((s16 *)auStack_1a,uVar2);
  }
  return (u8)auStack_1a[0];
}
