// ai_negatives.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- AIScript_Negatives  (ROM 0x90c904c)
u8 AIScript_Negatives(u8 bankAtk,u8 bankDef,u16 originalMove,u8 originalViability,AIScript *data)

{
  byte partner;
  byte bVar1;
  ushort partnerMove;
  sbyte sVar2;
  u8 uVar3;
  bool8 bVar4;
  u8 uVar5;
  u8 uVar6;
  u8 uVar7;
  ushort predictedMove;
  u16 move;
  ushort moveAcc;
  u16 uVar11;
  int moveSplit;
  uint moveTarget;
  uint moveType;
  int iVar15;
  int iVar16;
  uint bankAtk_;
  byte *pbVar18;
  undefined1 *puVar19;
  ushort bankAtk_00;
  undefined4 uVar20;
  uint extraout_r1;
  undefined *puVar21;
  undefined4 extraout_r1_00;
  BattlePokemon *pBVar22;
  BattlePokemon *move;
  byte moveFlags;
  uint moveEffect;
  BattlePokemon *partnerMove;
  uint partner;
  BattlePokemon *pBVar28;
  uint bankDef_;
  undefined8 uVar30;
  uint predictedMove;
  ushort uStack_30;
  byte bStack_1c;
  byte bStack_1b;
  ushort viabilityPtr [3];
  
  bankDef_ = (uint)bankDef;
  bankAtk_ = (uint)bankAtk;
  uStack_30 = (ushort)originalViability;
  viabilityPtr[0] = uStack_30;
  predictedMove = IsValidMovePrediction(bankDef,bankAtk);
  predictedMove = (uint)predictedMove;
  move = TryReplaceMoveWithZMove(bankAtk,bankDef,originalMove);
  move = (BattlePokemon *)move;
  uVar3 = GetAIAbility(bankAtk,bankDef,move);
  data->atkAbility = uVar3;
  uVar3 = GetAIAbility(bankDef,bankAtk,predictedMove);
  data->defAbility = uVar3;
  moveSplit = IsTargetAbilityIgnored(uVar3,data->atkAbility,move);
  if (moveSplit != 0) {
    data->defAbility = 0;
  }
  moveEffect = (uint)gBattleMoves[move].effect;
  moveSplit = CalcMoveSplit(bankAtk_,move);
  moveTarget = GetBaseMoveTarget(move,bankAtk_);
  moveType = GetMoveTypeSpecial(bankAtk_,move);
  moveFlags = gBattleMoves[move].flags;
  moveAcc = AccuracyCalc(move,bankAtk_,bankDef_);
  partnerMove = data->partnerMove;
  partnerMove = (BattlePokemon *)(uint)partnerMove;
  partner = data->bankAtkPartner;
  partner = (uint)partner;
  if ((BattlePokemon *)(uint)gDisableStructs[bankAtk_].disabledMove == move) {
    uVar20 = 100;
    goto LAB_090c9118;
  }
  if (-1 < (int)(moveTarget << 0x1b)) {
    if ((((gBattleResources->ai->aiFlags == 1) &&
         (__umodsi3(gRandomTurnNumber,100), (extraout_r1 & 0xffff) < 0x32)) &&
        (bVar4 = DamagingMoveInMoveset(bankAtk), bVar4 != 0)) && (bankDef_ != partner)) {
      if (((gBattleTypeFlags & 1) == 0) ||
         ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)) ||
          (iVar16 = CountAliveMonsInBattle(2,bankAtk_,bankDef_), iVar16 == 1)))) {
        bVar4 = MoveKnocksOutPossiblyGoesFirstWithBestAccuracy(move,bankAtk,bankDef,1);
        if (bVar4 == 0) {
          bVar4 = IsStrongestMove(move,bankAtk,bankDef);
          if (bVar4 == 0) goto LAB_090c91f0;
          uVar3 = 2;
        }
        else {
          uVar3 = 7;
        }
        IncreaseViability((s16 *)viabilityPtr,uVar3);
      }
      else {
        IncreaseDoublesDamageViability((s16 *)viabilityPtr,0xff,bankAtk,bankDef,move);
      }
    }
LAB_090c91f0:
    iVar16 = sub_90750c4();
    if (((iVar16 == 0) || (iVar16 = CheckTableForMove(move,&UNK_0903f930), iVar16 == 0)) &&
       (((iVar16 = CheckGrounding(bankDef_), iVar16 != 0 ||
         ((((moveType != 4 /* Ground */ || (move == 0x23c /* 1000 Arrows */)) || (data->atkAbility == 0xe9 /* Bone Zone  */)) ||
          ((move == 0x9b /* Bonemerang */ || (data->atkAbility == 0x98 /* Mold Breaker */)))))) ||
        (data->defAbility == 0x1a /* Levitate */)))) {
      iVar16 = CheckTableForMove(move,&UNK_0903ffd8);
      if ((iVar16 != 0) && (iVar16 = IsAffectedByPowder(bankDef_), iVar16 == 0)) {
        DecreaseViability(viabilityPtr,10);
      }
      iVar16 = IsDynamaxed(bankDef_);
      if ((iVar16 != 0) && (iVar16 = CheckTableForMove(move,&UNK_0903fcee), iVar16 != 0))
      goto LAB_090c923a;
      if (data->atkAbility == 0x98 /* Mold Breaker */) {
LAB_090c93c6:
        if ((((data->atkAbility == 0x57 /* Prankster */) && (moveSplit == 2)) && ((moveTarget & 0x50) == 0)) &&
           (iVar16 = IsOfType(bankDef_,0x11 /* Dark */), iVar16 != 0)) {
          iVar16 = GetBattlerSide(bankAtk_);
          iVar15 = GetBattlerSide(bankDef_);
          if (iVar16 == iVar15) goto LAB_090c9402;
        }
        else {
LAB_090c9402:
          if (gTerrainType == '\x03') {
            iVar16 = CheckTableForMovesEffect(move,&UNK_0903f908);
            if ((iVar16 != 0) ||
               (iVar16 = CheckTableForMovesEffect(move,&UNK_0903f91e), iVar16 != 0))
            goto LAB_090c9424;
          }
          else if (gTerrainType == '\x04') {
            iVar16 = PriorityCalc(bankAtk_,0,move);
            if (0 < iVar16) goto LAB_090c9424;
          }
          else if ((gTerrainType == '\x01') && ((moveEffect == 1 || (moveEffect == 0xbb)))) {
LAB_090c9424:
            iVar16 = CheckGrounding(bankDef_);
            if (iVar16 == 1) goto LAB_090c923a;
          }
          if ((1 < gBattleResources->ai->aiFlags) && (bankDef_ != partner)) {
            if (moveType == 10 /* Fire */) {
              bVar4 = HasUsedMove(bankDef,0x28c);
              if ((bVar4 != 0) && (gBattleResources->ai->simulatedRNG[0] < 0x4b)) goto LAB_090c9868;
            }
            else if ((moveType == 0 /* Normal */) &&
                    ((((bVar4 = HasUsedMove(bankDef,0x288), bVar4 != 0 &&
                       (gBattleResources->ai->simulatedRNG[0] < 0x4b)) &&
                      (iVar16 = IsElectricAbsorptionAblity(data->defAbility), iVar16 != 0)) ||
                     ((*(short *)(&gLastResultingMoves + bankDef_ * 2) == 0x297 &&
                      (iVar16 = IsElectricAbsorptionAblity(data->defAbility), iVar16 != 0)))))) {
LAB_090c9868:
              uVar20 = 0x13;
              goto LAB_090c9118;
            }
          }
          if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
              ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
                (gBattleMons[partner].hp == 0)) || ((moveTarget & 0x28) == 0)))) ||
             (((((moveSplit != 2 || (gBattleResources->ai->aiFlags < 2)) ||
                (0x4a < gBattleResources->ai->simulatedRNG[0])) ||
               ((bVar4 = HasUsedMove(bankDef,0x27e), bVar4 == 0 &&
                ((gBattleMons[data->bankDefPartner].hp == 0 ||
                 (bVar4 = HasUsedMove(data->bankDefPartner,0x27e), bVar4 == 0)))))) &&
              (iVar16 = GetBattlerSide(bankDef_), -1 < (int)((uint)gSideStatuses[iVar16] << 0x14)))))
          goto LAB_090c9984;
        }
LAB_090c923a:
        uVar20 = 10;
        goto LAB_090c9118;
      }
      uVar30 = CheckTableForMove(move,&UNK_09040136);
      if ((int)uVar30 != 0) goto LAB_090c93c6;
      bVar1 = data->defAbility;
      if (bVar1 == 0x74) {
        puVar21 = &UNK_0903ff64;
LAB_090c962e:
        iVar16 = CheckTableForMove(move,puVar21);
LAB_090c9624:
        if (iVar16 != 0) goto LAB_090c923a;
LAB_090c9348:
        if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
            (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)))) || (bankDef_ == partner)) goto LAB_090c93c6;
        bVar1 = data->defPartnerAbility;
        if (bVar1 == 0x5a) {
          if (((int)((uint)moveFlags << 0x1d) < 0) && ((moveTarget & 0x68) != 0)) goto LAB_090c94ec;
LAB_090c93aa:
          if ((moveTarget & 0x28) == 0) {
            if (data->atkPartnerAbility == 0x1f /* Lightning Rod */) {
              if (moveType == 0xd /* Electric */) goto LAB_090c9800;
            }
            else if ((data->atkPartnerAbility == 0x83 /* Storm Drain */) && (moveType == 0xb /* Water */)) {
LAB_090c9800:
              iVar16 = sub_9073f4c(move,data->atkAbility);
              if (iVar16 == 0) goto LAB_090c923a;
            }
          }
          goto LAB_090c93c6;
        }
        if (bVar1 < 0x5b) {
          if (bVar1 == 0x1f) {
            if (moveType == 0xd /* Electric */) {
LAB_090c97a2:
              iVar16 = sub_9073f4c(move,data->atkAbility);
              if (iVar16 == 0) goto LAB_090c94ec;
            }
          }
          else if ((bVar1 == 0x4e) && ((moveEffect == 1 || (moveEffect == 0xbb)))) goto LAB_090c923a;
          goto LAB_090c93aa;
        }
        if (bVar1 != 0xc9) {
          if (bVar1 == 0xdd) {
            iVar16 = PriorityCalc(bankAtk_,0,move);
            if (0 < iVar16) goto LAB_090c923a;
          }
          else if ((bVar1 == 0x83) && (moveType == 0xb /* Water */)) goto LAB_090c97a2;
          goto LAB_090c93aa;
        }
        iVar16 = CheckTableForMove(move,&UNK_0904024c);
        if (iVar16 == 0) goto LAB_090c93aa;
        goto LAB_090c923a;
      }
      if (bVar1 < 0x75) {
        if (bVar1 == 0x34) {
          if ((moveEffect == 0x12) || (moveEffect == 0x3a)) goto LAB_090c923a;
        }
        else if (bVar1 < 0x35) {
          if (bVar1 == 0x12) {
LAB_090c94f6:
            if (moveType == 10 /* Fire */) goto LAB_090c92ca;
          }
          else if (bVar1 < 0x13) {
            if (bVar1 == 0xb) {
LAB_090c9444:
              if (moveType == 0xb /* Water */) goto LAB_090c92ca;
            }
            else {
              puVar21 = &UNK_0903ff9e;
              if (bVar1 == 0x10) goto LAB_090c962e;
              if (bVar1 == 10) goto LAB_090c92c4;
            }
          }
          else if (bVar1 == 0x1f) {
LAB_090c92c4:
            if (moveType == 0xd /* Electric */) goto LAB_090c92ca;
          }
          else {
            if (bVar1 == 0x2b) {
              iVar16 = sub_9073ba8(move);
              goto LAB_090c9624;
            }
            if ((bVar1 == 0x1d) &&
               ((iVar16 = CheckTableForMovesEffect(move,&UNK_0903f90f), iVar16 != 0 ||
                (move == 0x230 /* Parting Shot */)))) goto LAB_090c923a;
          }
        }
        else if (bVar1 == 0x5a) {
          if ((int)((uint)moveFlags << 0x1d) < 0) goto LAB_090c94ec;
        }
        else if (bVar1 < 0x5b) {
          if (bVar1 == 0x4e) {
            if ((moveEffect == 1) || (moveEffect == 0xbb)) goto LAB_090c923a;
          }
          else {
            if (bVar1 == 0x50) goto LAB_090c92c4;
            if (bVar1 == 0x48) goto LAB_090c94d2;
          }
        }
        else if (bVar1 == 0x6e) {
          iVar16 = CalcMoveSplit(bankDef_,move);
          if ((iVar16 == 2) && ((gBattleMoves[move].target & 0xf7) == 0)) {
            uVar20 = 0x14;
            goto LAB_090c9118;
          }
        }
        else if (bVar1 == 0x71) {
          if (((moveType == 0xc /* Grass */) && (bankDef_ != partner)) &&
             (iVar16 = VarGet(0x5119,(int)((ulonglong)uVar30 >> 0x20),0x71000000,&VarGet
                                   ), iVar16 != 0x10)) goto LAB_090c94ec;
        }
        else if (bVar1 == 0x62) goto LAB_090c9444;
        goto LAB_090c9348;
      }
      if (bVar1 == 0xc6) {
        if ((((moveType == 0x11 /* Dark */) && (moveSplit != 2)) &&
            ((bankDef_ != partner &&
             ((gBattleMons[bankDef_].statStages[0] < 0xc &&
              (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,2), bVar4 == 0)))))) &&
           (bVar4 = RealPhysicalMoveInMoveset(bankDef), bVar4 != 0)) {
          uVar20 = 4;
LAB_090c95aa:
          DecreaseViability(viabilityPtr,uVar20);
        }
        goto LAB_090c9348;
      }
      if (bVar1 < 199) {
        if (bVar1 == 0x95) {
          if (moveSplit == 2) {
            moveAcc = 0x32;
          }
        }
        else if (bVar1 < 0x96) {
          if (bVar1 == 0x8e) {
            if ((((moveSplit == 2) &&
                 (iVar16 = CheckTableForMovesEffect(move,&UNK_0903f90f), iVar16 != 0)) &&
                (bankDef_ != partner)) && (gBattleMons[bankDef_].statStages[0] < 0xc)) {
              bVar4 = RealPhysicalMoveInMoveset(bankDef);
LAB_090c96e8:
              if (bVar4 != 0) {
                uVar20 = 8;
                goto LAB_090c9118;
              }
            }
          }
          else if (bVar1 == 0x8f) {
            if (((moveSplit == 2) &&
                (iVar16 = CheckTableForMovesEffect(move,&UNK_0903f90f), iVar16 != 0)) &&
               ((bankDef_ != partner && (gBattleMons[bankDef_].statStages[3] < 0xc)))) {
              bVar4 = SpecialMoveInMoveset(bankDef);
              goto LAB_090c96e8;
            }
          }
          else if (bVar1 == 0x83) goto LAB_090c9444;
        }
        else if (bVar1 == 0xbc) {
          if (moveType == 4 /* Ground */) {
LAB_090c92ca:
            if (bankDef_ != partner) goto LAB_090c94ec;
          }
        }
        else if (bVar1 == 0xbf) {
          iVar16 = CheckTableForMovesEffect(move,&UNK_0903f90f);
          if (iVar16 != 0) goto LAB_090c92ca;
        }
        else if ((bVar1 == 0xaa) &&
                (iVar16 = GetBankPartyData(bankDef_), *(short *)(iVar16 + 0x20) == 0x3df))
        goto LAB_090c94d2;
        goto LAB_090c9348;
      }
      if (bVar1 != 0xdf) {
        if (0xdf < bVar1) {
          if (bVar1 == 0xf5) {
            if (((((moveSplit != 2) && ((moveType - 10 & 0xff) < 2)) && (bankDef_ != partner)) &&
                ((gBattleMons[bankDef_].statStages[2] < 0xc &&
                 (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar4 == 0)))) &&
               (data->defSpeed < data->atkSpeed)) {
              bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,2);
              uVar20 = 5;
              if (bVar4 == 0) {
                uVar20 = 9;
              }
              goto LAB_090c95aa;
            }
          }
          else {
            if (bVar1 == 0xfe) goto LAB_090c94f6;
            if (bVar1 == 0xe7) {
LAB_090c94d2:
              iVar16 = CheckTableForMovesEffect(move,&UNK_0903f908);
              goto LAB_090c9624;
            }
          }
          goto LAB_090c9348;
        }
        if (bVar1 != 0xcb) {
          if (bVar1 == 0xdd) {
            iVar16 = PriorityCalc(bankAtk_,0,move);
            if (0 < iVar16) goto LAB_090c923a;
          }
          else if ((bVar1 == 0xc9) &&
                  (iVar16 = CheckTableForMove(move,&UNK_0904024c), iVar16 != 0))
          goto LAB_090c94ec;
          goto LAB_090c9348;
        }
        if (((gBattleWeather & 0x860) == 0) ||
           (((iVar16 = sub_9076620(data->defItemEffect), iVar16 != 0 ||
             (iVar16 = CheckTableForMovesEffect(move,&UNK_0903f908), iVar16 == 0)) ||
            (iVar16 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar16 != 0)))) goto LAB_090c9348;
        goto LAB_090c923a;
      }
      if ((moveType != 5 /* Rock */) || (moveSplit == 2)) goto LAB_090c9348;
LAB_090c94ec:
      uVar20 = 0x14;
LAB_090c9118:
      DecreaseViability(viabilityPtr,uVar20);
      return (u8)viabilityPtr[0];
    }
    goto LAB_090c9250;
  }
LAB_090c9984:
  iVar16 = sub_9075520(bankAtk_);
  if (((iVar16 != 0) && (iVar16 = sub_9073ba8(move), iVar16 != 0)) ||
     ((iVar16 = sub_90754f0(bankAtk_), iVar16 != 0 && (iVar16 = sub_9073b90(move), iVar16 != 0))))
  goto LAB_090c9250;
  uVar30 = IsRaidBattle();
  uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
  if ((int)uVar30 != 0) {
    iVar16 = CheckTableForMove(move,&UNK_0903fca8);
    if (iVar16 != 0) goto LAB_090c9250;
    uVar30 = GetBattlerPosition(bankAtk_);
    uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
    if ((int)uVar30 == 1) {
      uVar30 = CheckTableForMove(move,&UNK_0903fcc0);
      uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
      if ((int)uVar30 != 0) goto LAB_090c9250;
    }
    if (bankDef_ != bankAtk_) {
      uVar30 = GetBattlerPosition(bankDef_);
      uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
      if ((((int)uVar30 == 1) && ((int)((uint)*(byte *)(gNewBS + 0x1b5) << 0x1d) < 0)) &&
         (moveSplit == 2)) goto LAB_090c923a;
    }
  }
  if ((((int)((uint)gBattleWeather << 0x14) < 0) && (moveType == 0xb /* Water */)) && (moveSplit != 2)) {
    uVar30 = AbilityBattleEffects(0x13,0,0xd,0,0);
    uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
    if (((int)uVar30 == 0) && (move != 0x326 /* Hydro Steam */)) goto LAB_090c94ec;
  }
  bankAtk_00 = (ushort)bankAtk;
  if (((int)((uint)gBattleWeather << 0x13) < 0) && (moveType == 10 /* Fire */)) {
    if (moveSplit == 2) {
      if (moveEffect - 1 < 0xfe) {
                            switch(moveEffect - 1) {
        case 0: /* EFFECT_SLEEP */
          goto sw_c9a8c_0;
        case 2: /* EFFECT_ABSORB */
          goto sw_c9a8c_2;
        case 6: /* EFFECT_EXPLOSION */
          goto sw_c9a8c_6;
        case 7: /* EFFECT_DREAM_EATER */
          goto sw_c9a8c_7;
        case 8: /* EFFECT_MIRROR_MOVE */
          goto sw_c9a8c_8;
        case 84: /* EFFECT_SPLASH */
          goto sw_c9a8c_84;
        case 152: /* EFFECT_TELEPORT */
          goto sw_c9a8c_152;
        case 9: /* EFFECT_ATTACK_UP */
        case 49: /* EFFECT_ATTACK_UP_2 */
          goto sw_c9a8c_9;
        case 10: /* EFFECT_DEFENSE_UP */
        case 50: /* EFFECT_DEFENSE_UP_2 */
        case 155: /* EFFECT_DEFENSE_CURL */
          goto sw_c9a8c_10;
        case 11: /* EFFECT_SPEED_UP */
        case 51: /* EFFECT_SPEED_UP_2 */
          goto sw_c9a8c_11;
        case 12: /* EFFECT_SPECIAL_ATTACK_UP */
        case 52: /* EFFECT_SPECIAL_ATTACK_UP_2 */
          goto sw_c9a8c_12;
        case 13: /* EFFECT_SPECIAL_DEFENSE_UP */
        case 53: /* EFFECT_SPECIAL_DEFENSE_UP_2 */
          goto sw_c9a8c_13;
        case 14: /* EFFECT_ACCURACY_UP */
        case 54: /* EFFECT_ACCURACY_UP_2 */
          goto sw_c9a8c_14;
        case 15: /* EFFECT_EVASION_UP */
        case 55: /* EFFECT_EVASION_UP_2 */
        case 107: /* EFFECT_MINIMIZE */
          goto sw_c9a8c_15;
        case 17: /* EFFECT_ATTACK_DOWN */
        case 57: /* EFFECT_ATTACK_DOWN_2 */
          goto sw_c9a8c_17;
        case 18: /* EFFECT_DEFENSE_DOWN */
        case 58: /* EFFECT_DEFENSE_DOWN_2 */
          goto sw_c9a8c_18;
        case 19: /* EFFECT_SPEED_DOWN */
        case 59: /* EFFECT_SPEED_DOWN_2 */
          goto sw_c9a8c_19;
        case 20: /* EFFECT_SPECIAL_ATTACK_DOWN */
        case 60: /* EFFECT_SPECIAL_ATTACK_DOWN_2 */
          goto sw_c9a8c_20;
        case 21: /* EFFECT_SPECIAL_DEFENSE_DOWN */
        case 61: /* EFFECT_SPECIAL_DEFENSE_DOWN_2 */
          goto sw_c9a8c_21;
        case 22: /* EFFECT_ACCURACY_DOWN */
        case 62: /* EFFECT_ACCURACY_DOWN_2 */
          goto sw_c9a8c_22;
        case 25: /* EFFECT_BIDE */
          goto sw_c9a8c_25;
        case 27: /* EFFECT_ROAR */
          goto sw_c9a8c_27;
        case 29: /* EFFECT_CONVERSION */
          goto sw_c9a8c_29;
        case 36: /* EFFECT_REST */
          goto sw_c9a8c_36;
        case 31: /* EFFECT_RESTORE_HP */
        case 131: /* EFFECT_MORNING_SUN */
          goto sw_c9a8c_31;
        case 32: /* EFFECT_TOXIC */
        case 65: /* EFFECT_POISON */
          goto sw_c9a8c_32;
        case 34: /* EFFECT_LIGHT_SCREEN */
          goto sw_c9a8c_34;
        case 37: /* EFFECT_0HKO */
          goto sw_c9a8c_37;
        case 44: /* EFFECT_RECOIL_IF_MISS */
          goto sw_c9a8c_44;
        case 45: /* EFFECT_MIST */
          goto sw_c9a8c_45;
        case 46: /* EFFECT_FOCUS_ENERGY */
          goto sw_c9a8c_46;
        case 47: /* EFFECT_RECOIL */
          goto sw_c9a8c_47;
        case 48: /* EFFECT_CONFUSE */
          goto sw_c9a8c_48;
        case 56: /* EFFECT_TRANSFORM */
          goto sw_c9a8c_56;
        case 64: /* EFFECT_REFLECT */
          goto sw_c9a8c_64;
        case 66: /* EFFECT_PARALYZE */
        case 3:
          goto sw_c9a8c_66;
        case 78: /* EFFECT_SUBSTITUTE */
          goto sw_c9a8c_78;
        case 79: /* EFFECT_RECHARGE */
          goto sw_c9a8c_79;
        case 99: /* EFFECT_SPITE */
          goto sw_c9a8c_99;
        case 81: /* EFFECT_MIMIC */
          goto sw_c9a8c_81;
        case 83: /* EFFECT_LEECH_SEED */
          goto sw_c9a8c_83;
        case 85: /* EFFECT_DISABLE */
          goto sw_c9a8c_85;
        case 88: /* EFFECT_COUNTER */
        case 143: /* EFFECT_MIRROR_COAT */
          goto sw_c9a8c_88;
        case 89: /* EFFECT_ENCORE */
          goto sw_c9a8c_89;
        case 188: /* EFFECT_ENDEAVOR */
          goto sw_c9a8c_188;
        case 90: /* EFFECT_PAIN_SPLIT */
          goto sw_c9a8c_90;
        case 91: /* EFFECT_SNORE */
          goto sw_c9a8c_91;
        case 96: /* EFFECT_SLEEP_TALK */
          goto sw_c9a8c_96;
        case 92: /* EFFECT_CONVERSION_2 */
          goto sw_c9a8c_92;
        case 93: /* EFFECT_LOCK_ON */
          goto sw_c9a8c_93;
        case 94: /* EFFECT_SKETCH */
          goto sw_c9a8c_94;
        case 97: /* EFFECT_DESTINY_BOND */
          goto sw_c9a8c_97;
        case 100: /* EFFECT_FALSE_SWIPE */
          goto sw_c9a8c_100;
        case 101: /* EFFECT_HEAL_BELL */
          goto sw_c9a8c_101;
        case 105: /* EFFECT_MEAN_LOOK */
          goto sw_cf924_105;
        case 106: /* EFFECT_NIGHTMARE */
          goto sw_c9a8c_106;
        case 108: /* EFFECT_CURSE */
          goto sw_c9a8c_108;
        case 110: /* EFFECT_PROTECT */
          goto sw_c9a8c_110;
        case 111: /* EFFECT_SPIKES */
          goto sw_c9a8c_111;
        case 112: /* EFFECT_FORESIGHT */
          goto sw_c9a8c_112;
        case 113: /* EFFECT_PERISH_SONG */
          goto sw_c9a8c_113;
        case 114: /* EFFECT_SANDSTORM */
          goto sw_c9a8c_114;
        case 117: /* EFFECT_SWAGGER */
          goto sw_c9a8c_117;
        case 119: /* EFFECT_ATTRACT */
          goto sw_c9a8c_119;
        case 123: /* EFFECT_SAFEGUARD */
          goto sw_c9a8c_123;
        case 124: /* EFFECT_BURN_UP */
          goto sw_c9a8c_124;
        case 126: /* EFFECT_BATON_PASS */
          goto sw_c9a8c_126;
        case 128: /* EFFECT_RAPID_SPIN */
          goto sw_c9a8c_128;
        case 23: /* EFFECT_EVASION_DOWN */
        case 63: /* EFFECT_EVASION_DOWN_2 */
          goto sw_c9a8c_23;
        case 135: /* EFFECT_RAIN_DANCE */
          goto sw_c9a8c_135;
        case 136: /* EFFECT_SUNNY_DAY */
          goto sw_c9a8c_136;
        case 141: /* EFFECT_BELLY_DRUM */
          goto sw_c9a8c_141;
        case 142: /* EFFECT_PSYCH_UP */
          goto sw_c9a8c_142;
        case 24: /* EFFECT_HAZE */
          goto sw_c9a8c_24;
        case 147: /* EFFECT_FUTURE_SIGHT */
          goto sw_c9a8c_147;
        case 150: /* EFFECT_SOLARBEAM */
          goto sw_c9a8c_150;
        case 38: /* EFFECT_RAZOR_WIND */
        case 74: /* EFFECT_SKY_ATTACK */
        case 144: /* EFFECT_SKULL_BASH */
          goto sw_c9a8c_38;
        case 154: /* EFFECT_SEMI_INVULNERABLE */
          goto sw_c9a8c_154;
        case 157: /* EFFECT_FAKE_OUT */
          goto sw_c9a8c_157;
        case 159: /* EFFECT_STOCKPILE */
          goto sw_c9a8c_159;
        case 160: /* EFFECT_SPIT_UP */
          goto sw_c9a8c_160;
        case 161: /* EFFECT_SWALLOW */
          goto sw_c9a8c_161;
        case 163: /* EFFECT_HAIL */
          goto sw_c9a8c_163;
        case 164: /* EFFECT_TORMENT */
          goto sw_c9a8c_164;
        case 165: /* EFFECT_FLATTER */
          goto sw_c9a8c_165;
        case 166: /* EFFECT_WILL_O_WISP */
        case 1:
          goto sw_c9a8c_166;
        case 167: /* EFFECT_MEMENTO */
          goto sw_c9a8c_167;
        case 169: /* EFFECT_FOCUS_PUNCH */
          goto sw_c9a8c_169;
        case 172: /* EFFECT_NATURE_POWER */
          goto sw_c9a8c_172;
        case 173: /* EFFECT_CHARGE */
          goto sw_c9a8c_173;
        case 174: /* EFFECT_TAUNT */
          goto sw_c9a8c_174;
        case 171: /* EFFECT_FOLLOW_ME */
        case 175: /* EFFECT_HELPING_HAND */
          goto sw_c9a8c_171;
        case 176: /* EFFECT_TRICK */
          goto sw_c9a8c_176;
        case 177: /* EFFECT_ROLE_PLAY */
          goto sw_c9a8c_177;
        case 178: /* EFFECT_WISH */
          goto sw_c9a8c_178;
        case 179: /* EFFECT_ASSIST */
          goto sw_c9a8c_179;
        case 180: /* EFFECT_INGRAIN */
          goto sw_c9a8c_180;
        case 182: /* EFFECT_MAGIC_COAT */
          goto sw_c9a8c_182;
        case 183: /* EFFECT_RECYCLE */
          goto sw_c9a8c_183;
        case 186: /* EFFECT_YAWN */
          goto sw_c9a8c_186;
        case 187: /* EFFECT_KNOCK_OFF */
          goto sw_c9a8c_187;
        case 190: /* EFFECT_SKILL_SWAP */
          goto sw_c9a8c_190;
        case 191: /* EFFECT_IMPRISON */
          goto sw_c9a8c_191;
        case 192: /* EFFECT_REFRESH */
          goto sw_c9a8c_192;
        case 194: /* EFFECT_SNATCH */
          goto sw_c9a8c_194;
        case 200: /* EFFECT_MUD_SPORT */
          goto sw_c9a8c_200;
        case 204: /* EFFECT_TICKLE */
          goto sw_c9a8c_204;
        case 205: /* EFFECT_COSMIC_POWER */
          goto sw_c9a8c_205;
        case 206: /* EFFECT_EXTREME_EVOBOOST */
          goto sw_c9a8c_206;
        case 207: /* EFFECT_BULK_UP */
          goto sw_c9a8c_207;
        case 209: /* EFFECT_WATER_SPORT */
          goto sw_c9a8c_209;
        case 210: /* EFFECT_CALM_MIND */
          goto sw_c9a8c_210;
        case 211: /* EFFECT_DRAGON_DANCE */
          goto sw_c9a8c_211;
        case 212: /* EFFECT_STAT_SWAP_SPLIT */
          goto sw_c9a8c_212;
        case 217: /* EFFECT_ME_FIRST */
          goto sw_c9a8c_217;
        case 219: /* EFFECT_NATURAL_GIFT */
          goto sw_c9a8c_219;
        case 225: /* EFFECT_SET_TERRAIN */
          goto sw_c9a8c_225;
        case 226: /* EFFECT_PLEDGE */
          goto sw_c9a8c_226;
        case 227: /* EFFECT_FIELD_EFFECTS */
          goto sw_c9a8c_227;
        case 228: /* EFFECT_FLING */
          goto sw_c9a8c_228;
        case 230: /* EFFECT_ATTACK_BLOCKERS */
          goto sw_c9a8c_230;
        case 231: /* EFFECT_TYPE_CHANGES */
          goto sw_c9a8c_231;
        case 232: /* EFFECT_HEAL_TARGET */
          goto sw_c9a8c_232;
        case 233: /* EFFECT_TOPSY_TURVY_ELECTRIFY */
          goto sw_c9a8c_233;
        case 234: /* EFFECT_FAIRY_LOCK_HAPPY_HOUR */
          goto sw_c9a8c_234;
        case 235: /* EFFECT_INSTRUCT_AFTER_YOU_QUASH */
          goto sw_c9a8c_235;
        case 236: /* EFFECT_SUCKER_PUNCH */
          goto sw_c9a8c_236;
        case 238: /* EFFECT_TEAM_EFFECTS */
          goto sw_c9a8c_238;
        case 239: /* EFFECT_CAMOUFLAGE */
          goto sw_c9a8c_239;
        case 241: /* EFFECT_LAST_RESORT */
          goto sw_c9a8c_241;
        case 253: /* ? */
          goto sw_c9a8c_253;
        case 184: /* EFFECT_BLANK_185 */
          goto sw_c9a8c_184;
        }
      }
      goto sw_c9a8c_82;
    }
    uVar30 = AbilityBattleEffects(0x13,0,0xd,0,0);
    uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
    if ((int)uVar30 == 0) goto LAB_090c94ec;
    if (moveEffect - 1 < 0xfe) {
                          switch(moveEffect - 1) {
      case 0: /* EFFECT_SLEEP */
        goto sw_c9a8c_0;
      case 82: /* EFFECT_METRONOME */
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 7:
      case 8:
      case 9:
      case 1: /* EFFECT_POISON_HIT */
      case 3: /* EFFECT_BURN_HIT */
      case 4: /* EFFECT_FREEZE_HIT */
      case 5: /* EFFECT_PARALYZE_HIT */
      case 16: /* EFFECT_ALWAYS_HIT */
      case 26: /* EFFECT_RAMPAGE */
      case 28: /* EFFECT_MULTI_HIT */
      case 30: /* EFFECT_FLINCH_HIT */
      case 33: /* EFFECT_PAY_DAY */
      case 35: /* EFFECT_TRI_ATTACK */
      case 39: /* EFFECT_SUPER_FANG */
      case 40: /* EFFECT_DRAGON_RAGE */
      case 41: /* EFFECT_TRAP */
      case 42: /* EFFECT_HIGH_CRITICAL */
      case 43: /* EFFECT_DOUBLE_HIT */
      case 67: /* EFFECT_ATTACK_DOWN_HIT */
      case 68: /* EFFECT_DEFENSE_DOWN_HIT */
      case 69: /* EFFECT_SPEED_DOWN_HIT */
      case 70: /* EFFECT_SPECIAL_ATTACK_DOWN_HIT */
      case 71: /* EFFECT_SPECIAL_DEFENSE_DOWN_HIT */
      case 72: /* EFFECT_ACCURACY_DOWN_HIT */
      case 73: /* EFFECT_EVASION_DOWN_HIT */
      case 75: /* EFFECT_CONFUSE_HIT */
      case 76: /* EFFECT_SPECIAL_DEFENSE_DOWN_2_HIT */
      case 77: /* EFFECT_BLANK_78 */
      case 80: /* EFFECT_RAGE */
      case 82: /* EFFECT_METRONOME */
      case 86: /* EFFECT_LEVEL_DAMAGE */
      case 87: /* EFFECT_PSYWAVE */
      case 95: /* EFFECT_SPEED_UP_1_HIT */
      case 98: /* EFFECT_FLAIL */
      case 102: /* EFFECT_QUICK_ATTACK */
      case 103: /* EFFECT_TRIPLE_KICK */
      case 104: /* EFFECT_THIEF */
      case 109: /* EFFECT_SPECIAL_ATTACK_UP_HIT */
      case 115: /* EFFECT_BLANK_116 */
      case 116: /* EFFECT_ROLLOUT */
      case 118: /* EFFECT_FURY_CUTTER */
      case 120: /* EFFECT_BLANK_121 */
      case 121: /* EFFECT_PRESENT */
      case 122: /* EFFECT_BLANK_123 */
      case 125: /* EFFECT_MAGNITUDE */
      case 127: /* EFFECT_PURSUIT */
      case 129: /* EFFECT_SONICBOOM */
      case 130: /* EFFECT_BLANK_83 */
      case 132: /* EFFECT_BLANK_133 */
      case 133: /* EFFECT_BLANK_134 */
      case 134: /* EFFECT_DEFENSE_UP_2_HIT */
      case 137: /* EFFECT_DEFENSE_UP_HIT */
      case 138: /* EFFECT_ATTACK_UP_HIT */
      case 139: /* EFFECT_ALL_STATS_UP_HIT */
      case 140: /* EFFECT_HIGHER_OFFENSES_DEFENSES_UP_HIT */
      case 145: /* EFFECT_TWISTER */
      case 146: /* EFFECT_EARTHQUAKE */
      case 148: /* EFFECT_GUST */
      case 149: /* EFFECT_SPLINTER */
      case 151: /* EFFECT_THUNDER */
      case 153: /* EFFECT_BEAT_UP */
      case 156: /* EFFECT_SPRINGTIDE_STORM */
      case 158: /* EFFECT_UPROAR */
      case 162: /* EFFECT_BLANK_A3 */
      case 168: /* EFFECT_BLANK_169 */
      case 170: /* EFFECT_SMELLINGSALT */
      case 181: /* EFFECT_SUPERPOWER */
      case 185: /* EFFECT_BRICK_BREAK */
      case 189: /* EFFECT_BLANK_190 */
      case 193: /* EFFECT_GRUDGE */
      case 195: /* EFFECT_BLANK_196 */
      case 196: /* EFFECT_SECRET_POWER */
      case 197: /* EFFECT_ATK_SPATK_UP */
      case 198: /* EFFECT_ATK_ACC_UP */
      case 199: /* EFFECT_DEF_SPD_UP */
      case 201: /* EFFECT_VENOM_DRENCH */
      case 202: /* EFFECT_PLAY_NICE */
      case 203: /* EFFECT_OVERHEAT */
      case 208: /* EFFECT_BAD_POISON_HIT */
      case 213: /* EFFECT_BLANK_214 */
      case 214: /* EFFECT_BLANK_215 */
      case 215: /* EFFECT_BLANK_216 */
      case 216: /* EFFECT_BLANK_217 */
      case 218: /* EFFECT_EAT_BERRY */
      case 220: /* EFFECT_SMACK_DOWN */
      case 221: /* EFFECT_REMOVE_TARGET_STAT_CHANGES */
      case 222: /* EFFECT_RELIC_SONG */
      case 223: /* EFFECT_BLANK_224 */
      case 224: /* EFFECT_BLANK_225 */
      case 229: /* EFFECT_FEINT */
      case 237: /* EFFECT_IGNORE_REDIRECTION */
      case 240: /* EFFECT_FLAMEBURST */
      case 242: /* EFFECT_DAMAGE_SET_TERRAIN */
      case 243: /* EFFECT_TEATIME */
      case 244: /* EFFECT_POLTERGEIST */
      case 245: /* EFFECT_SKY_DROP */
      case 246: /* ? */
      case 247: /* ? */
      case 248: /* ? */
      case 249: /* ? */
      case 250: /* ? */
      case 251: /* ? */
      case 252: /* EFFECT_MAX_MOVE */
        goto sw_c9a8c_82;
      case 2: /* EFFECT_ABSORB */
        goto sw_c9a8c_2;
      case 6: /* EFFECT_EXPLOSION */
        goto sw_c9a8c_6;
      case 7: /* EFFECT_DREAM_EATER */
        goto sw_c9a8c_7;
      case 8: /* EFFECT_MIRROR_MOVE */
        goto sw_c9a8c_8;
      case 84: /* EFFECT_SPLASH */
        goto sw_c9a8c_84;
      case 152: /* EFFECT_TELEPORT */
        goto sw_c9a8c_152;
      case 9: /* EFFECT_ATTACK_UP */
      case 49: /* EFFECT_ATTACK_UP_2 */
        goto sw_c9a8c_9;
      case 10: /* EFFECT_DEFENSE_UP */
      case 50: /* EFFECT_DEFENSE_UP_2 */
      case 155: /* EFFECT_DEFENSE_CURL */
        goto sw_c9a8c_10;
      case 11: /* EFFECT_SPEED_UP */
      case 51: /* EFFECT_SPEED_UP_2 */
        goto sw_c9a8c_11;
      case 12: /* EFFECT_SPECIAL_ATTACK_UP */
      case 52: /* EFFECT_SPECIAL_ATTACK_UP_2 */
        goto sw_c9a8c_12;
      case 13: /* EFFECT_SPECIAL_DEFENSE_UP */
      case 53: /* EFFECT_SPECIAL_DEFENSE_UP_2 */
        goto sw_c9a8c_13;
      case 14: /* EFFECT_ACCURACY_UP */
      case 54: /* EFFECT_ACCURACY_UP_2 */
        goto sw_c9a8c_14;
      case 15: /* EFFECT_EVASION_UP */
      case 55: /* EFFECT_EVASION_UP_2 */
      case 107: /* EFFECT_MINIMIZE */
        goto sw_c9a8c_15;
      case 17: /* EFFECT_ATTACK_DOWN */
      case 57: /* EFFECT_ATTACK_DOWN_2 */
        goto sw_c9a8c_17;
      case 18: /* EFFECT_DEFENSE_DOWN */
      case 58: /* EFFECT_DEFENSE_DOWN_2 */
        goto sw_c9a8c_18;
      case 19: /* EFFECT_SPEED_DOWN */
      case 59: /* EFFECT_SPEED_DOWN_2 */
        goto sw_c9a8c_19;
      case 20: /* EFFECT_SPECIAL_ATTACK_DOWN */
      case 60: /* EFFECT_SPECIAL_ATTACK_DOWN_2 */
        goto sw_c9a8c_20;
      case 21: /* EFFECT_SPECIAL_DEFENSE_DOWN */
      case 61: /* EFFECT_SPECIAL_DEFENSE_DOWN_2 */
        goto sw_c9a8c_21;
      case 22: /* EFFECT_ACCURACY_DOWN */
      case 62: /* EFFECT_ACCURACY_DOWN_2 */
        goto sw_c9a8c_22;
      case 25: /* EFFECT_BIDE */
        goto sw_c9a8c_25;
      case 27: /* EFFECT_ROAR */
        goto sw_c9a8c_27;
      case 29: /* EFFECT_CONVERSION */
        goto sw_c9a8c_29;
      case 36: /* EFFECT_REST */
        goto sw_c9a8c_36;
      case 31: /* EFFECT_RESTORE_HP */
      case 131: /* EFFECT_MORNING_SUN */
        goto sw_c9a8c_31;
      case 32: /* EFFECT_TOXIC */
      case 65: /* EFFECT_POISON */
        goto sw_c9a8c_32;
      case 34: /* EFFECT_LIGHT_SCREEN */
        goto sw_c9a8c_34;
      case 37: /* EFFECT_0HKO */
        goto sw_c9a8c_37;
      case 44: /* EFFECT_RECOIL_IF_MISS */
        goto sw_c9a8c_44;
      case 45: /* EFFECT_MIST */
        goto sw_c9a8c_45;
      case 46: /* EFFECT_FOCUS_ENERGY */
        goto sw_c9a8c_46;
      case 47: /* EFFECT_RECOIL */
        goto sw_c9a8c_47;
      case 48: /* EFFECT_CONFUSE */
        goto sw_c9a8c_48;
      case 56: /* EFFECT_TRANSFORM */
        goto sw_c9a8c_56;
      case 64: /* EFFECT_REFLECT */
        goto sw_c9a8c_64;
      case 66: /* EFFECT_PARALYZE */
      case 3:
        goto sw_c9a8c_66;
      case 78: /* EFFECT_SUBSTITUTE */
        goto sw_c9a8c_78;
      case 79: /* EFFECT_RECHARGE */
        goto sw_c9a8c_79;
      case 99: /* EFFECT_SPITE */
        goto sw_c9a8c_99;
      case 81: /* EFFECT_MIMIC */
        goto sw_c9a8c_81;
      case 83: /* EFFECT_LEECH_SEED */
        goto sw_c9a8c_83;
      case 85: /* EFFECT_DISABLE */
        goto sw_c9a8c_85;
      case 88: /* EFFECT_COUNTER */
      case 143: /* EFFECT_MIRROR_COAT */
        goto sw_c9a8c_88;
      case 89: /* EFFECT_ENCORE */
        goto sw_c9a8c_89;
      case 188: /* EFFECT_ENDEAVOR */
        goto sw_c9a8c_188;
      case 90: /* EFFECT_PAIN_SPLIT */
        goto sw_c9a8c_90;
      case 91: /* EFFECT_SNORE */
        goto sw_c9a8c_91;
      case 96: /* EFFECT_SLEEP_TALK */
        goto sw_c9a8c_96;
      case 92: /* EFFECT_CONVERSION_2 */
        goto sw_c9a8c_92;
      case 93: /* EFFECT_LOCK_ON */
        goto sw_c9a8c_93;
      case 94: /* EFFECT_SKETCH */
        goto sw_c9a8c_94;
      case 97: /* EFFECT_DESTINY_BOND */
        goto sw_c9a8c_97;
      case 100: /* EFFECT_FALSE_SWIPE */
        goto sw_c9a8c_100;
      case 101: /* EFFECT_HEAL_BELL */
        goto sw_c9a8c_101;
      case 105: /* EFFECT_MEAN_LOOK */
        goto sw_c9a8c_105;
      case 106: /* EFFECT_NIGHTMARE */
        goto sw_c9a8c_106;
      case 108: /* EFFECT_CURSE */
        goto sw_c9a8c_108;
      case 110: /* EFFECT_PROTECT */
        goto sw_c9a8c_110;
      case 111: /* EFFECT_SPIKES */
        goto sw_c9a8c_111;
      case 112: /* EFFECT_FORESIGHT */
        goto sw_c9a8c_112;
      case 113: /* EFFECT_PERISH_SONG */
        goto sw_c9a8c_113;
      case 114: /* EFFECT_SANDSTORM */
        goto sw_c9a8c_114;
      case 117: /* EFFECT_SWAGGER */
        goto sw_c9a8c_117;
      case 119: /* EFFECT_ATTRACT */
        goto sw_c9a8c_119;
      case 123: /* EFFECT_SAFEGUARD */
        goto sw_c9a8c_123;
      case 124: /* EFFECT_BURN_UP */
        goto sw_c9a8c_124;
      case 126: /* EFFECT_BATON_PASS */
        goto sw_c9a8c_126;
      case 128: /* EFFECT_RAPID_SPIN */
        goto sw_c9a8c_128;
      case 23: /* EFFECT_EVASION_DOWN */
      case 63: /* EFFECT_EVASION_DOWN_2 */
        goto sw_c9a8c_23;
      case 135: /* EFFECT_RAIN_DANCE */
        goto sw_c9a8c_135;
      case 136: /* EFFECT_SUNNY_DAY */
        goto sw_c9a8c_136;
      case 141: /* EFFECT_BELLY_DRUM */
        goto sw_c9a8c_141;
      case 142: /* EFFECT_PSYCH_UP */
        goto sw_c9a8c_142;
      case 24: /* EFFECT_HAZE */
        goto sw_c9a8c_24;
      case 147: /* EFFECT_FUTURE_SIGHT */
        goto sw_c9a8c_147;
      case 150: /* EFFECT_SOLARBEAM */
        goto sw_c9a8c_150;
      case 38: /* EFFECT_RAZOR_WIND */
      case 74: /* EFFECT_SKY_ATTACK */
      case 144: /* EFFECT_SKULL_BASH */
        goto sw_c9a8c_38;
      case 154: /* EFFECT_SEMI_INVULNERABLE */
        goto sw_c9a8c_154;
      case 157: /* EFFECT_FAKE_OUT */
        goto sw_c9a8c_157;
      case 159: /* EFFECT_STOCKPILE */
        goto sw_c9a8c_159;
      case 160: /* EFFECT_SPIT_UP */
        goto sw_c9a8c_160;
      case 161: /* EFFECT_SWALLOW */
        goto sw_c9a8c_161;
      case 163: /* EFFECT_HAIL */
        goto sw_c9a8c_163;
      case 164: /* EFFECT_TORMENT */
        goto sw_c9a8c_164;
      case 165: /* EFFECT_FLATTER */
        goto sw_c9a8c_165;
      case 166: /* EFFECT_WILL_O_WISP */
      case 1:
        goto sw_c9a8c_166;
      case 167: /* EFFECT_MEMENTO */
        goto sw_c9a8c_167;
      case 169: /* EFFECT_FOCUS_PUNCH */
        goto sw_c9a8c_169;
      case 172: /* EFFECT_NATURE_POWER */
        goto sw_c9a8c_172;
      case 173: /* EFFECT_CHARGE */
        goto sw_c9a8c_173;
      case 174: /* EFFECT_TAUNT */
        goto sw_c9a8c_174;
      case 171: /* EFFECT_FOLLOW_ME */
      case 175: /* EFFECT_HELPING_HAND */
        goto sw_c9a8c_171;
      case 176: /* EFFECT_TRICK */
        goto sw_c9a8c_176;
      case 177: /* EFFECT_ROLE_PLAY */
        goto sw_c9a8c_177;
      case 178: /* EFFECT_WISH */
        goto sw_c9a8c_178;
      case 179: /* EFFECT_ASSIST */
        goto sw_c9a8c_179;
      case 180: /* EFFECT_INGRAIN */
        goto sw_c9a8c_180;
      case 182: /* EFFECT_MAGIC_COAT */
        goto sw_c9a8c_182;
      case 183: /* EFFECT_RECYCLE */
        goto sw_c9a8c_183;
      case 186: /* EFFECT_YAWN */
        goto sw_c9a8c_186;
      case 187: /* EFFECT_KNOCK_OFF */
        goto sw_c9a8c_187;
      case 190: /* EFFECT_SKILL_SWAP */
        goto sw_c9a8c_190;
      case 191: /* EFFECT_IMPRISON */
        goto sw_c9a8c_191;
      case 192: /* EFFECT_REFRESH */
        goto sw_c9a8c_192;
      case 194: /* EFFECT_SNATCH */
        goto sw_c9a8c_194;
      case 200: /* EFFECT_MUD_SPORT */
        goto sw_c9a8c_200;
      case 204: /* EFFECT_TICKLE */
        goto sw_c9a8c_204;
      case 205: /* EFFECT_COSMIC_POWER */
        goto sw_c9a8c_205;
      case 206: /* EFFECT_EXTREME_EVOBOOST */
        goto sw_c9a8c_206;
      case 207: /* EFFECT_BULK_UP */
        goto sw_c9a8c_207;
      case 209: /* EFFECT_WATER_SPORT */
        goto sw_c9a8c_209;
      case 210: /* EFFECT_CALM_MIND */
        goto sw_c9a8c_210;
      case 211: /* EFFECT_DRAGON_DANCE */
        goto sw_c9a8c_211;
      case 212: /* EFFECT_STAT_SWAP_SPLIT */
        goto sw_c9a8c_212;
      case 217: /* EFFECT_ME_FIRST */
        goto sw_c9a8c_217;
      case 219: /* EFFECT_NATURAL_GIFT */
        goto sw_c9a8c_219;
      case 225: /* EFFECT_SET_TERRAIN */
        goto sw_c9a8c_225;
      case 226: /* EFFECT_PLEDGE */
        goto sw_c9a8c_226;
      case 227: /* EFFECT_FIELD_EFFECTS */
        goto sw_c9a8c_227;
      case 228: /* EFFECT_FLING */
        goto sw_c9a8c_228;
      case 230: /* EFFECT_ATTACK_BLOCKERS */
        goto sw_c9a8c_230;
      case 231: /* EFFECT_TYPE_CHANGES */
        goto sw_c9a8c_231;
      case 232: /* EFFECT_HEAL_TARGET */
        goto sw_c9a8c_232;
      case 233: /* EFFECT_TOPSY_TURVY_ELECTRIFY */
        goto sw_c9a8c_233;
      case 234: /* EFFECT_FAIRY_LOCK_HAPPY_HOUR */
        goto sw_c9a8c_234;
      case 235: /* EFFECT_INSTRUCT_AFTER_YOU_QUASH */
        goto sw_c9a8c_235;
      case 236: /* EFFECT_SUCKER_PUNCH */
        goto sw_c9a8c_236;
      case 238: /* EFFECT_TEAM_EFFECTS */
        goto sw_c9a8c_238;
      case 239: /* EFFECT_CAMOUFLAGE */
        goto sw_c9a8c_239;
      case 241: /* EFFECT_LAST_RESORT */
        goto sw_c9a8c_241;
      case 253: /* ? */
        goto sw_c9a8c_253;
      case 184: /* EFFECT_BLANK_185 */
        goto sw_c9a8c_184;
      }
    }
    goto sw_c9a8c_1;
  }
  if (0xfd < moveEffect - 1) goto sw_c9ecc_1;
                      switch(moveEffect - 1) {
  case 0: /* EFFECT_SLEEP */
sw_c9a8c_0:
    moveTarget = AI_SpecialTypeCalc(move,bankAtk_,bankDef_);
    moveTarget = moveTarget & 0x29;
joined_r0x090cdbaa:
    if (moveTarget == 0) {
LAB_090cdbb0:
      iVar16 = CanBePutToSleep(bankDef_,1,bankAtk_);
      if ((iVar16 != 0) && (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 == 0)) {
        iVar16 = PartnerMoveEffectIsStatusSameTarget(data,move,bankDef_);
        goto joined_r0x090cd65e;
      }
    }
    break;
  case 82: /* EFFECT_METRONOME */
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 7:
  case 8:
  case 9:
  case 1: /* EFFECT_POISON_HIT */
  case 3: /* EFFECT_BURN_HIT */
  case 4: /* EFFECT_FREEZE_HIT */
  case 5: /* EFFECT_PARALYZE_HIT */
  case 16: /* EFFECT_ALWAYS_HIT */
  case 26: /* EFFECT_RAMPAGE */
  case 28: /* EFFECT_MULTI_HIT */
  case 30: /* EFFECT_FLINCH_HIT */
  case 33: /* EFFECT_PAY_DAY */
  case 35: /* EFFECT_TRI_ATTACK */
  case 39: /* EFFECT_SUPER_FANG */
  case 40: /* EFFECT_DRAGON_RAGE */
  case 41: /* EFFECT_TRAP */
  case 42: /* EFFECT_HIGH_CRITICAL */
  case 43: /* EFFECT_DOUBLE_HIT */
  case 67: /* EFFECT_ATTACK_DOWN_HIT */
  case 68: /* EFFECT_DEFENSE_DOWN_HIT */
  case 69: /* EFFECT_SPEED_DOWN_HIT */
  case 70: /* EFFECT_SPECIAL_ATTACK_DOWN_HIT */
  case 71: /* EFFECT_SPECIAL_DEFENSE_DOWN_HIT */
  case 72: /* EFFECT_ACCURACY_DOWN_HIT */
  case 73: /* EFFECT_EVASION_DOWN_HIT */
  case 75: /* EFFECT_CONFUSE_HIT */
  case 76: /* EFFECT_SPECIAL_DEFENSE_DOWN_2_HIT */
  case 77: /* EFFECT_BLANK_78 */
  case 80: /* EFFECT_RAGE */
  case 82: /* EFFECT_METRONOME */
  case 86: /* EFFECT_LEVEL_DAMAGE */
  case 87: /* EFFECT_PSYWAVE */
  case 95: /* EFFECT_SPEED_UP_1_HIT */
  case 98: /* EFFECT_FLAIL */
  case 102: /* EFFECT_QUICK_ATTACK */
  case 103: /* EFFECT_TRIPLE_KICK */
  case 104: /* EFFECT_THIEF */
  case 109: /* EFFECT_SPECIAL_ATTACK_UP_HIT */
  case 115: /* EFFECT_BLANK_116 */
  case 116: /* EFFECT_ROLLOUT */
  case 118: /* EFFECT_FURY_CUTTER */
  case 120: /* EFFECT_BLANK_121 */
  case 121: /* EFFECT_PRESENT */
  case 122: /* EFFECT_BLANK_123 */
  case 125: /* EFFECT_MAGNITUDE */
  case 127: /* EFFECT_PURSUIT */
  case 129: /* EFFECT_SONICBOOM */
  case 130: /* EFFECT_BLANK_83 */
  case 132: /* EFFECT_BLANK_133 */
  case 133: /* EFFECT_BLANK_134 */
  case 134: /* EFFECT_DEFENSE_UP_2_HIT */
  case 137: /* EFFECT_DEFENSE_UP_HIT */
  case 138: /* EFFECT_ATTACK_UP_HIT */
  case 139: /* EFFECT_ALL_STATS_UP_HIT */
  case 140: /* EFFECT_HIGHER_OFFENSES_DEFENSES_UP_HIT */
  case 145: /* EFFECT_TWISTER */
  case 146: /* EFFECT_EARTHQUAKE */
  case 148: /* EFFECT_GUST */
  case 149: /* EFFECT_SPLINTER */
  case 151: /* EFFECT_THUNDER */
  case 153: /* EFFECT_BEAT_UP */
  case 156: /* EFFECT_SPRINGTIDE_STORM */
  case 158: /* EFFECT_UPROAR */
  case 162: /* EFFECT_BLANK_A3 */
  case 168: /* EFFECT_BLANK_169 */
  case 170: /* EFFECT_SMELLINGSALT */
  case 181: /* EFFECT_SUPERPOWER */
  case 185: /* EFFECT_BRICK_BREAK */
  case 189: /* EFFECT_BLANK_190 */
  case 193: /* EFFECT_GRUDGE */
  case 195: /* EFFECT_BLANK_196 */
  case 196: /* EFFECT_SECRET_POWER */
  case 197: /* EFFECT_ATK_SPATK_UP */
  case 198: /* EFFECT_ATK_ACC_UP */
  case 199: /* EFFECT_DEF_SPD_UP */
  case 201: /* EFFECT_VENOM_DRENCH */
  case 202: /* EFFECT_PLAY_NICE */
  case 203: /* EFFECT_OVERHEAT */
  case 208: /* EFFECT_BAD_POISON_HIT */
  case 213: /* EFFECT_BLANK_214 */
  case 214: /* EFFECT_BLANK_215 */
  case 215: /* EFFECT_BLANK_216 */
  case 216: /* EFFECT_BLANK_217 */
  case 218: /* EFFECT_EAT_BERRY */
  case 220: /* EFFECT_SMACK_DOWN */
  case 221: /* EFFECT_REMOVE_TARGET_STAT_CHANGES */
  case 222: /* EFFECT_RELIC_SONG */
  case 223: /* EFFECT_BLANK_224 */
  case 224: /* EFFECT_BLANK_225 */
  case 229: /* EFFECT_FEINT */
  case 237: /* EFFECT_IGNORE_REDIRECTION */
  case 240: /* EFFECT_FLAMEBURST */
  case 242: /* EFFECT_DAMAGE_SET_TERRAIN */
  case 243: /* EFFECT_TEATIME */
  case 244: /* EFFECT_POLTERGEIST */
  case 245: /* EFFECT_SKY_DROP */
  case 246: /* ? */
  case 247: /* ? */
  case 248: /* ? */
  case 249: /* ? */
  case 250: /* ? */
  case 251: /* ? */
  case 252: /* EFFECT_MAX_MOVE */
    goto sw_c9a8c_82;
  case 2: /* EFFECT_ABSORB */
sw_c9a8c_2:
    if ((data->defAbility == 0x40 /* Liquid Ooze */) &&
       (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar4 == 0)) {
      DecreaseViability(viabilityPtr,6);
    }
    if (move != 0x26a /* Strength Sap */) goto sw_c9ecc_1;
    if (data->defAbility != 0xbf /* Contrary */) {
      sVar2 = gBattleMons[bankDef_].statStages[0];
joined_r0x090caa36:
      if (0 < sVar2) goto sw_c9a8c_82;
    }
    break;
  case 6: /* EFFECT_EXPLOSION */
sw_c9a8c_6:
    if (((((data->atkAbility != 0x98 /* Mold Breaker */) &&
          (iVar16 = CheckTableForMove(move,&UNK_09040136), iVar16 == 0)) &&
         (iVar16 = AbilityBattleEffects(0x13,0,6,0,0), iVar16 != 0)) ||
        ((bVar4 = HasProtectionMoveInMoveset(bankDef,1), bVar4 != 0 &&
         (gDisableStructs[bankDef_].protectUses == 0)))) ||
       ((bVar4 = MoveEffectInMoveset(0x9b /* EFFECT_SEMI_INVULNERABLE */,bankDef), bVar4 != 0 ||
        (((data->defStatus3 & 0x130400c0) != 0 &&
         (bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef), bVar4 != 0)))))) break;
    iVar16 = ViableMonCountFromBank(bankDef_);
    if ((iVar16 != 1) || (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar4 == 0)) {
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
          (gBattleMons[partner].hp == 0)))) {
        bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1);
        if (bVar4 != 0) {
          bankAtk_ = ViableMonCountFromBank(bankDef_);
          bVar4 = 0;
          if (bankAtk_ < 2) goto sw_c9a8c_82;
          goto LAB_090ca442;
        }
        goto LAB_090ca4ce;
      }
      bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1);
      if (((bVar4 == 0) ||
          (bVar4 = MoveKnocksOutXHits(move,bankAtk,data->bankDefPartner,1), bVar4 == 0)) ||
         (bankAtk_ = ViableMonCountFromBank(bankDef_), 2 < bankAtk_)) goto LAB_090ca4ce;
    }
    goto sw_c9a8c_82;
  case 7: /* EFFECT_DREAM_EATER */
sw_c9a8c_7:
    if (data->defAbility != 0xe7 /* Comatose */) {
      bankAtk_ = data->defStatus1 & 7;
joined_r0x090ca5d0:
      if (bankAtk_ == 0) break;
    }
    goto sw_c9a8c_82;
  case 8: /* EFFECT_MIRROR_MOVE */
sw_c9a8c_8:
    if (move == 0x1c8 /* Copycat */) {
      bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
      if ((bVar4 == 0) && (predictedMove != 0 /* - */)) {
        iVar16 = CheckTableForMove(predictedMove,&UNK_0903f95e);
        if ((iVar16 == 0) && (bankAtk_ = FindMovePositionInMoveset(predictedMove,bankAtk_), 3 < bankAtk_))
        goto LAB_090ca544;
      }
      else if ((((ushort)(*(short *)(gNewBS + 0xec) - 1U) < 0xfffe) &&
               (iVar16 = CheckTableForMove(*(short *)(gNewBS + 0xec),&UNK_0903f95e), iVar16 == 0))
              && (bankAtk_ = FindMovePositionInMoveset(*(undefined2 *)(gNewBS + 0xec),bankAtk_),
                 3 < bankAtk_)) {
        predictedMove = *(ushort *)(gNewBS + 0xec);
LAB_090ca544:
        uVar3 = AIScript_Negatives(bankAtk,bankDef,predictedMove,originalViability,data);
        return uVar3;
      }
    }
    else {
      predictedMove = gBattleStruct->lastTakenMoveFrom[bankAtk_][bankDef_ + 1];
      if (predictedMove != 0 /* - */) goto LAB_090ca544;
    }
    break;
  case 84: /* EFFECT_SPLASH */
sw_c9a8c_84:
    iVar16 = IsTypeZCrystal(data->atkItem,gBattleMoves[move].type);
    if (iVar16 != 0) {
      bVar4 = *(bool8 *)(gNewBS + bankAtk_ + 0x194);
      goto joined_r0x090cc7c4;
    }
    break;
  case 152: /* EFFECT_TELEPORT */
sw_c9a8c_152:
    if ((int)(gBattleTypeFlags << 0x1c) < 0) {
      bankAtk_ = HasMonToSwitchTo();
      goto joined_r0x090ca5d0;
    }
    iVar16 = GetBattlerSide(bankAtk_);
    if (iVar16 == 0) {
      predictedMove = HasMonToSwitchTo(bankAtk_);
joined_r0x090cf81c:
      if (predictedMove != 0 /* - */) goto sw_c9a8c_82;
    }
    else if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
            (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)))) {
      bVar4 = IsTrapped(bankAtk,0);
      goto joined_r0x090cc7c4;
    }
    break;
  case 9: /* EFFECT_ATTACK_UP */
  case 49: /* EFFECT_ATTACK_UP_2 */
sw_c9a8c_9:
    if ((gBattleResources->ai->aiFlags < 2) ||
       ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility), iVar16 == 0 &&
        ((gDisableStructs[bankAtk_].field_0xe & 0xf) == 0)))) {
      if ((move == 0x150 /* Howl */) && (bankDef_ == partner))
      goto sw_c9a8c_82;
      if ((data->atkAbility != 0xbf /* Contrary */) && (gBattleMons[bankAtk_].statStages[0] < 0xc)) {
        bVar4 = RealPhysicalMoveInMoveset(bankAtk);
        goto joined_r0x090ce4be;
      }
    }
    break;
  case 10: /* EFFECT_DEFENSE_UP */
  case 50: /* EFFECT_DEFENSE_UP_2 */
  case 155: /* EFFECT_DEFENSE_CURL */
sw_c9a8c_10:
    if ((gBattleResources->ai->aiFlags < 2) ||
       ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility), iVar16 == 0 &&
        ((gDisableStructs[bankAtk_].field_0xe & 0xf) == 0)))) {
      if (move == 0x1de /* Flower Guard */) {
        if (bankDef_ == partner) goto sw_c9a8c_82;
        iVar16 = IsOfType(bankAtk_,0xc /* Grass */);
LAB_090ca746:
        if (iVar16 != 0) goto LAB_090ca716;
      }
      else if (move == 0x2a9 /* Stuff Cheeks */) {
        if (*(short *)(gNewBS + (bankAtk_ + 0x7c) * 2 + 6) != 0) {
          iVar16 = sub_90a52de();
          goto LAB_090ca746;
        }
      }
      else {
LAB_090ca716:
        if (data->atkAbility != 0xbf /* Contrary */) {
          sVar2 = gBattleMons[bankAtk_].statStages[1];
          goto joined_r0x090ce202;
        }
      }
    }
    break;
  case 11: /* EFFECT_SPEED_UP */
  case 51: /* EFFECT_SPEED_UP_2 */
sw_c9a8c_11:
    if (((data->atkAbility == 0xbf /* Contrary */) || (0xb < gBattleMons[bankAtk_].statStages[2])) ||
       ((1 < gBattleResources->ai->aiFlags &&
        ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect), iVar16 != 0 ||
         ((gDisableStructs[bankAtk_].field_0xe & 0xf) != 0)))))) break;
    iVar16 = IsTrickRoomActive();
    if (iVar16 != 0) {
      predictedMove = sub_9074c80();
      goto joined_r0x090cf81c;
    }
    goto sw_c9a8c_82;
  case 12: /* EFFECT_SPECIAL_ATTACK_UP */
  case 52: /* EFFECT_SPECIAL_ATTACK_UP_2 */
sw_c9a8c_12:
    if (move != 0x19e /* Work Up */) {
      if (0x19e < move) {
        if (move == 0x1df /* Rototiller */) {
          if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
             (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[partner].hp != 0)))) {
            iVar16 = IsOfType(bankAtk_,0xc /* Grass */);
            if ((((iVar16 != 0) && (iVar16 = CheckGrounding(bankAtk_), iVar16 != 0)) &&
                (data->atkAbility != 0xbf /* Contrary */)) &&
               (((gBattleMons[bankAtk_].statStages[0] < 0xc &&
                 (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) ||
                ((((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
                   (0 < gBattleMons[bankAtk_].statStages[0])) ||
                  ((gBattleMons[bankAtk_].statStages[3] < 0xc &&
                   (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)))) ||
                 ((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
                  (0 < gBattleMons[bankAtk_].statStages[3])))))))) goto sw_c9a8c_82;
            iVar16 = IsOfType(partner,0xc /* Grass */);
            if (((iVar16 != 0) && (iVar16 = CheckGrounding(partner), iVar16 != 0)) &&
               (data->atkPartnerAbility != 0xbf /* Contrary */)) {
              if ((((gBattleMons[partner].statStages[0] < 0xc) &&
                   (iVar16 = GetBankAbility(partner), iVar16 != 0xbf)) ||
                  ((iVar16 = GetBankAbility(partner), iVar16 == 0xbf &&
                   (0 < gBattleMons[partner].statStages[0])))) ||
                 ((gBattleMons[partner].statStages[3] < 0xc &&
                  (iVar16 = GetBankAbility(partner), iVar16 != 0xbf))))
              goto sw_c9a8c_82;
              iVar16 = GetBankAbility(partner);
              if (iVar16 == 0xbf) {
                sVar2 = gBattleMons[partner].statStages[3];
                goto joined_r0x090caa36;
              }
            }
          }
          else {
            iVar16 = IsOfType(bankAtk_,0xc /* Grass */);
            if (((iVar16 != 0) && (iVar16 = CheckGrounding(bankAtk_), iVar16 != 0)) &&
               (data->atkAbility != 0xbf /* Contrary */)) {
              if ((((gBattleMons[bankAtk_].statStages[0] < 0xc) &&
                   (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) ||
                  ((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
                   (0 < gBattleMons[bankAtk_].statStages[0])))) ||
                 ((gBattleMons[bankAtk_].statStages[3] < 0xc &&
                  (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf))))
              goto sw_c9a8c_82;
              iVar16 = GetBankAbility(bankAtk_);
              if (iVar16 == 0xbf) {
                sVar2 = gBattleMons[bankAtk_].statStages[3];
                goto joined_r0x090caa36;
              }
            }
          }
          break;
        }
        if (move != 0x24f /* Gear Up */) goto LAB_090ca7d6;
        if (data->atkAbility - 0x39 < 2) goto LAB_090ca8b4;
        if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
            ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[partner].hp != 0)) && (data->atkPartnerAbility - 0x39 < 2)))) &&
           ((((0xb < gBattleMons[partner].statStages[0] ||
              (iVar16 = GetBankAbility(partner), iVar16 == 0xbf)) &&
             ((iVar16 = GetBankAbility(partner), iVar16 != 0xbf ||
              (gBattleMons[partner].statStages[0] < 1)))) ||
            (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 == 0)))) {
          if (((gBattleMons[partner].statStages[3] < 0xc) &&
              (iVar16 = GetBankAbility(partner), iVar16 != 0xbf)) ||
             ((iVar16 = GetBankAbility(partner), iVar16 == 0xbf &&
              (0 < gBattleMons[partner].statStages[3])))) {
            bVar4 = SpecialMoveInMoveset(bankAtk);
            goto joined_r0x090ce4be;
          }
          break;
        }
        goto sw_c9a8c_82;
      }
      if (move != 0x4a /* Growth */) {
LAB_090ca7d6:
        if ((data->atkAbility != 0xbf /* Contrary */) &&
           (((gBattleMons[bankAtk_].statStages[3] < 0xc &&
             (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) ||
            ((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
             (0 < gBattleMons[bankAtk_].statStages[3])))))) {
          bVar4 = SpecialMoveInMoveset(bankAtk);
          goto joined_r0x090ce4be;
        }
        break;
      }
    }
LAB_090ca8b4:
    if (((((gBattleMons[bankAtk_].statStages[0] < 0xc) &&
          (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) ||
         ((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
          (0 < gBattleMons[bankAtk_].statStages[0])))) &&
        (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 != 0)) ||
       ((((gBattleMons[bankAtk_].statStages[3] < 0xc &&
          (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) ||
         ((iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf &&
          (0 < gBattleMons[bankAtk_].statStages[3])))) &&
        (bVar4 = SpecialMoveInMoveset(bankAtk), bVar4 != 0)))) {
      moveFlags = data->atkAbility;
joined_r0x090cd626:
      if (moveFlags != 0xbf) goto sw_c9a8c_82;
    }
    break;
  case 13: /* EFFECT_SPECIAL_DEFENSE_UP */
  case 53: /* EFFECT_SPECIAL_DEFENSE_UP_2 */
sw_c9a8c_13:
    if ((gBattleResources->ai->aiFlags < 2) ||
       ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility), iVar16 == 0 &&
        ((gDisableStructs[bankAtk_].field_0xe & 0xf) == 0)))) {
      if (move == 0x280 /* Aroma Mist */) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)))) {
joined_r0x090cf52c:
          if (bankDef_ == partner) goto sw_c9a8c_82;
        }
      }
      else {
LAB_090cd824:
        if (data->atkAbility != 0xbf /* Contrary */) {
          sVar2 = gBattleMons[bankAtk_].statStages[4];
joined_r0x090cccfa:
          if (sVar2 < 0xc) goto sw_c9a8c_82;
        }
      }
    }
    break;
  case 14: /* EFFECT_ACCURACY_UP */
  case 54: /* EFFECT_ACCURACY_UP_2 */
sw_c9a8c_14:
    if ((data->atkAbility == 0xbf /* Contrary */) ||
       (((0xb < gBattleMons[bankAtk_].statStages[5] ||
         (iVar16 = GetBankAbility(bankAtk_), iVar16 == 0xbf)) &&
        ((iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf || (gBattleMons[bankAtk_].statStages[5] < 1)
         ))))) {
LAB_090cacd2:
      DecreaseViability(viabilityPtr,10);
    }
    else {
      if (gBattleResources->ai->aiFlags < 2) goto sw_c9a8c_82;
      iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility);
      if ((iVar16 != 0) || ((gDisableStructs[bankAtk_].field_0xe & 0xf) != 0)) goto LAB_090cacd2;
    }
    if ((1 < gBattleResources->ai->aiFlags) &&
       (bVar4 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,100,0), bVar4 == 0)) {
      DecreaseViability(viabilityPtr,1);
    }
    goto sw_c9a8c_82;
  case 15: /* EFFECT_EVASION_UP */
  case 55: /* EFFECT_EVASION_UP_2 */
  case 107: /* EFFECT_MINIMIZE */
sw_c9a8c_15:
    if (move == 0x1e3 /* Acupressure */) {
      iVar16 = StatsMaxed(bankDef_);
      if (iVar16 == 0) {
        moveFlags = data->defAbility;
        goto joined_r0x090cd626;
      }
    }
    else if (data->atkAbility != 0xbf /* Contrary */) {
      if ((gBattleMons[bankAtk_].statStages[6] < 0xc) &&
         (iVar16 = GetBankAbility(bankAtk_), iVar16 != 0xbf)) goto sw_c9a8c_82;
      iVar16 = GetBankAbility(bankAtk_);
      if (iVar16 == 0xbf) {
        sVar2 = gBattleMons[bankAtk_].statStages[6];
        goto joined_r0x090caa36;
      }
    }
    break;
  case 17: /* EFFECT_ATTACK_DOWN */
  case 57: /* EFFECT_ATTACK_DOWN_2 */
sw_c9a8c_17:
    if (move == 0x22e /* Noble Roar */) {
LAB_090cae48:
      if ((gBattleMons[bankDef_].statStages[3] != 0) &&
         (bVar4 = SpecialMoveInMoveset(bankDef), bVar4 != 0)) goto LAB_090cae7e;
      pBVar28 = (BattlePokemon *)(bankDef_ * 0x58);
      pBVar22 = gBattleMons;
    }
    else {
      if (0x22e < move) {
        if (move != 0x26c /* Teary Look */) {
          if (move != 0x293 /* Venom Drench */) goto LAB_090cae94;
          if ((data->defStatus1 & 0x88) == 0) break;
          if (gBattleMons[bankDef_].statStages[2] != 0) goto LAB_090cae7e;
        }
        goto LAB_090cae48;
      }
      if (move == 0x1eb /* Play Nice */) goto LAB_090cae48;
LAB_090cae94:
      pBVar28 = gBattleMons;
      pBVar22 = (BattlePokemon *)(bankDef_ * 0x58);
    }
    if (*(char *)((int)pBVar22->moves + (int)((int)pBVar28->moves + 1)) == '\0') break;
    bVar4 = PhysicalMoveInMoveset(bankDef);
    predictedMove = (uint)bVar4;
    goto joined_r0x090cb868;
  case 18: /* EFFECT_DEFENSE_DOWN */
  case 58: /* EFFECT_DEFENSE_DOWN_2 */
sw_c9a8c_18:
    uVar20 = 2;
    moveFlags = data->defAbility;
    goto LAB_090caea6;
  case 19: /* EFFECT_SPEED_DOWN */
  case 59: /* EFFECT_SPEED_DOWN_2 */
sw_c9a8c_19:
    moveFlags = data->defAbility;
    uVar20 = 3;
    goto LAB_090caea6;
  case 20: /* EFFECT_SPECIAL_ATTACK_DOWN */
  case 60: /* EFFECT_SPECIAL_ATTACK_DOWN_2 */
sw_c9a8c_20:
    if (((move != 0x203 /* Captivate */) ||
        (((data->atkGender != 0xff && (data->defGender != 0xff)) &&
         (data->atkGender != data->defGender)))) &&
       (iVar16 = sub_90becd0(4,bankDef_,bankAtk_,data->defAbility), iVar16 != 0)) {
      bVar4 = SpecialMoveInMoveset(bankDef);
      predictedMove = (uint)bVar4;
      goto joined_r0x090cb868;
    }
    break;
  case 21: /* EFFECT_SPECIAL_DEFENSE_DOWN */
  case 61: /* EFFECT_SPECIAL_DEFENSE_DOWN_2 */
sw_c9a8c_21:
    moveFlags = data->defAbility;
    uVar20 = 5;
    goto LAB_090caea6;
  case 22: /* EFFECT_ACCURACY_DOWN */
  case 62: /* EFFECT_ACCURACY_DOWN_2 */
sw_c9a8c_22:
    moveFlags = data->defAbility;
    uVar20 = 6;
    goto LAB_090caea6;
  case 25: /* EFFECT_BIDE */
sw_c9a8c_25:
    bVar4 = DamagingMoveInMoveset(bankDef);
    if ((bVar4 != 0) && (bankAtk_ = func_0x090dd734(bankAtk_), 0x1d < bankAtk_)) {
      bankAtk_ = data->defStatus1 & 7;
      goto joined_r0x090cf272;
    }
    break;
  case 27: /* EFFECT_ROAR */
sw_c9a8c_27:
    if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
        ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
          (gBattleMons[partner].hp == 0)) ||
         ((gBattleMoves[(int)partnerMove].effect != 0x1c /* EFFECT_ROAR */ || (gChosenMovesByBanks[partner] == 0)))))) ||
       (gBattleStruct->moveTarget[partner] != bankDef_)) {
      bVar4 = WillFaintFromSecondaryDamage(bankDef);
      if (((bVar4 != 0) || (iVar16 = GetBadDreamsDamage(bankDef_), iVar16 != 0)) ||
         ((iVar16 = func_0x09090eb0(bankDef_), iVar16 != 0 ||
          (((iVar16 = func_0x09090ef0(bankDef_), iVar16 != 0 ||
            (iVar16 = func_0x09090f28(bankDef_), iVar16 != 0)) ||
           (moveTarget = GetPoisonDamage(bankDef_), gBattleMons[bankDef_].maxHP >> 2 <= moveTarget)))))) {
        DecreaseViability(viabilityPtr,10);
      }
      if ((0x1bb < move) &&
         ((move < 0x1be || (move == 0x1ec /* Roar of Time */))))
      goto sw_c9ecc_1;
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
          (gBattleMons[partner].hp != 0)))) {
        bankAtk_ = ViableMonCountFromBankLoadPartyRange(bankDef_);
        if ((2 < bankAtk_) && (data->defAbility != 0x15 /* Suction Cups */)) {
          iVar16 = data->defStatus3 << 0x15;
          goto joined_r0x090cc5ea;
        }
      }
      else {
        bankAtk_ = ViableMonCountFromBankLoadPartyRange(bankDef_);
        if ((1 < bankAtk_) && (data->defAbility != 0x15 /* Suction Cups */)) {
          iVar16 = data->defStatus3 << 0x15;
joined_r0x090cc5ea:
          if (-1 < iVar16) goto sw_c9a8c_82;
        }
      }
    }
    break;
  case 29: /* EFFECT_CONVERSION */
sw_c9a8c_29:
    bankAtk_ = IsOfType(bankAtk_,gBattleMoves[gBattleMons[bankAtk_].moves[0]].type);
    goto joined_r0x090cf272;
  case 36: /* EFFECT_REST */
sw_c9a8c_36:
    iVar16 = sub_9076642(bankAtk_);
    if (iVar16 == 0) {
      DecreaseViability(viabilityPtr,10);
    }
  case 31: /* EFFECT_RESTORE_HP */
  case 131: /* EFFECT_MORNING_SUN */
sw_c9a8c_31:
    if (move == 0x25d /* Purify */) {
      if (((data->defStatus1 & 0xff) == 0) ||
         (iVar16 = MoveBlockedBySubstitute(0x25d,bankAtk_,bankDef_), iVar16 != 0)) break;
      if (bankDef_ != partner) {
        iVar16 = func_0x090dd734(bankAtk_);
        if (iVar16 == 100) break;
        bankAtk_ = func_0x090dd734(bankAtk_);
        if (0x59 < bankAtk_) {
LAB_090cb176:
          DecreaseViability(viabilityPtr,8);
        }
      }
    }
    else {
      iVar16 = func_0x090dd734(bankAtk_);
      if (iVar16 == 100) break;
      bankAtk_ = func_0x090dd734(bankAtk_);
      if (0x59 < bankAtk_) {
LAB_090cb104:
        DecreaseViability(viabilityPtr,9);
      }
    }
    goto sw_c9a8c_82;
  case 32: /* EFFECT_TOXIC */
  case 65: /* EFFECT_POISON */
sw_c9a8c_32:
    if (((move != 0x26e /* Toxic Thread */) ||
        (iVar16 = sub_90becd0(3,bankDef_,bankAtk_,data->defAbility), iVar16 == 0)) ||
       (data->defAbility == 0xbf /* Contrary */)) {
      moveTarget = AI_SpecialTypeCalc(move,bankAtk_,bankDef_);
      if ((moveTarget & 0x29) == 0) {
sw_ceae8_0:
        iVar16 = CanBePoisoned(bankDef_,bankAtk_,1);
        if ((iVar16 != 0) && (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 == 0))
        {
          iVar16 = PartnerMoveEffectIsStatusSameTarget(data,move,bankDef_);
          goto joined_r0x090cd65e;
        }
      }
      break;
    }
    goto sw_c9a8c_82;
  case 34: /* EFFECT_LIGHT_SCREEN */
sw_c9a8c_34:
    iVar16 = GetBattlerSide(bankAtk_);
    if ((int)((uint)gSideStatuses[iVar16] << 0x1e) < 0) break;
LAB_090cb20e:
    if (((2 < gBattleResources->ai->aiFlags) && (bVar4 = IsBankIncapacitated(bankDef), bVar4 == 0))
       && ((bVar4 = HasUsedMoveWithEffect(bankDef,0xba), bVar4 != 0 ||
           (bVar4 = HasUsedMove(bankDef,0x204), bVar4 != 0)))) goto LAB_090cb104;
    goto sw_c9a8c_82;
  case 37: /* EFFECT_0HKO */
sw_c9a8c_37:
    bankAtk_ = AI_SpecialTypeCalc(move,bankAtk_,bankDef_);
    if (((bankAtk_ & 0x29) != 0) ||
       (((data->atkAbility != 0x98 /* Mold Breaker */ &&
         (iVar16 = CheckTableForMove(move,&UNK_09040136), iVar16 == 0)) &&
        (data->defAbility == 5 /* Sturdy */)))) break;
    goto sw_c9a8c_82;
  case 44: /* EFFECT_RECOIL_IF_MISS */
sw_c9a8c_44:
    if ((data->atkAbility != 0x73 /* Magic Guard */) && (uVar20 = 6, moveAcc < 0x46)) {
LAB_090cb832:
      DecreaseViability(viabilityPtr,uVar20);
    }
  case 1: /* EFFECT_POISON_HIT */
  case 3: /* EFFECT_BURN_HIT */
  case 4: /* EFFECT_FREEZE_HIT */
  case 5: /* EFFECT_PARALYZE_HIT */
  case 16: /* EFFECT_ALWAYS_HIT */
  case 26: /* EFFECT_RAMPAGE */
  case 28: /* EFFECT_MULTI_HIT */
  case 30: /* EFFECT_FLINCH_HIT */
  case 33: /* EFFECT_PAY_DAY */
  case 35: /* EFFECT_TRI_ATTACK */
  case 39: /* EFFECT_SUPER_FANG */
  case 40: /* EFFECT_DRAGON_RAGE */
  case 41: /* EFFECT_TRAP */
  case 42: /* EFFECT_HIGH_CRITICAL */
  case 43: /* EFFECT_DOUBLE_HIT */
  case 67: /* EFFECT_ATTACK_DOWN_HIT */
  case 68: /* EFFECT_DEFENSE_DOWN_HIT */
  case 69: /* EFFECT_SPEED_DOWN_HIT */
  case 70: /* EFFECT_SPECIAL_ATTACK_DOWN_HIT */
  case 71: /* EFFECT_SPECIAL_DEFENSE_DOWN_HIT */
  case 72: /* EFFECT_ACCURACY_DOWN_HIT */
  case 73: /* EFFECT_EVASION_DOWN_HIT */
  case 75: /* EFFECT_CONFUSE_HIT */
  case 76: /* EFFECT_SPECIAL_DEFENSE_DOWN_2_HIT */
  case 77: /* EFFECT_BLANK_78 */
  case 80: /* EFFECT_RAGE */
  case 86: /* EFFECT_LEVEL_DAMAGE */
  case 87: /* EFFECT_PSYWAVE */
  case 95: /* EFFECT_SPEED_UP_1_HIT */
  case 98: /* EFFECT_FLAIL */
  case 102: /* EFFECT_QUICK_ATTACK */
  case 103: /* EFFECT_TRIPLE_KICK */
  case 104: /* EFFECT_THIEF */
  case 109: /* EFFECT_SPECIAL_ATTACK_UP_HIT */
  case 115: /* EFFECT_BLANK_116 */
  case 116: /* EFFECT_ROLLOUT */
  case 118: /* EFFECT_FURY_CUTTER */
  case 120: /* EFFECT_BLANK_121 */
  case 121: /* EFFECT_PRESENT */
  case 122: /* EFFECT_BLANK_123 */
  case 125: /* EFFECT_MAGNITUDE */
  case 127: /* EFFECT_PURSUIT */
  case 129: /* EFFECT_SONICBOOM */
  case 130: /* EFFECT_BLANK_83 */
  case 132: /* EFFECT_BLANK_133 */
  case 133: /* EFFECT_BLANK_134 */
  case 134: /* EFFECT_DEFENSE_UP_2_HIT */
  case 137: /* EFFECT_DEFENSE_UP_HIT */
  case 138: /* EFFECT_ATTACK_UP_HIT */
  case 139: /* EFFECT_ALL_STATS_UP_HIT */
  case 140: /* EFFECT_HIGHER_OFFENSES_DEFENSES_UP_HIT */
  case 145: /* EFFECT_TWISTER */
  case 146: /* EFFECT_EARTHQUAKE */
  case 148: /* EFFECT_GUST */
  case 149: /* EFFECT_SPLINTER */
  case 151: /* EFFECT_THUNDER */
  case 153: /* EFFECT_BEAT_UP */
  case 156: /* EFFECT_SPRINGTIDE_STORM */
  case 158: /* EFFECT_UPROAR */
  case 162: /* EFFECT_BLANK_A3 */
  case 168: /* EFFECT_BLANK_169 */
  case 170: /* EFFECT_SMELLINGSALT */
  case 181: /* EFFECT_SUPERPOWER */
  case 185: /* EFFECT_BRICK_BREAK */
  case 189: /* EFFECT_BLANK_190 */
  case 193: /* EFFECT_GRUDGE */
  case 195: /* EFFECT_BLANK_196 */
  case 196: /* EFFECT_SECRET_POWER */
  case 197: /* EFFECT_ATK_SPATK_UP */
  case 198: /* EFFECT_ATK_ACC_UP */
  case 199: /* EFFECT_DEF_SPD_UP */
  case 201: /* EFFECT_VENOM_DRENCH */
  case 202: /* EFFECT_PLAY_NICE */
  case 203: /* EFFECT_OVERHEAT */
  case 208: /* EFFECT_BAD_POISON_HIT */
  case 213: /* EFFECT_BLANK_214 */
  case 214: /* EFFECT_BLANK_215 */
  case 215: /* EFFECT_BLANK_216 */
  case 216: /* EFFECT_BLANK_217 */
  case 218: /* EFFECT_EAT_BERRY */
  case 220: /* EFFECT_SMACK_DOWN */
  case 221: /* EFFECT_REMOVE_TARGET_STAT_CHANGES */
  case 222: /* EFFECT_RELIC_SONG */
  case 223: /* EFFECT_BLANK_224 */
  case 224: /* EFFECT_BLANK_225 */
  case 229: /* EFFECT_FEINT */
  case 237: /* EFFECT_IGNORE_REDIRECTION */
  case 240: /* EFFECT_FLAMEBURST */
  case 242: /* EFFECT_DAMAGE_SET_TERRAIN */
  case 243: /* EFFECT_TEATIME */
  case 244: /* EFFECT_POLTERGEIST */
  case 245: /* EFFECT_SKY_DROP */
  case 246: /* ? */
  case 247: /* ? */
  case 248: /* ? */
  case 249: /* ? */
  case 250: /* ? */
  case 251: /* ? */
  case 252: /* EFFECT_MAX_MOVE */
    goto sw_c9ecc_1;
  case 45: /* EFFECT_MIST */
sw_c9a8c_45:
    iVar16 = sub_9075378(bankAtk_);
    if (iVar16 == 0) {
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)) || (gBattleMoves[(int)partnerMove].effect != 0x2e /* EFFECT_MIST */))))
      goto sw_c9a8c_82;
      predictedMove = gChosenMovesByBanks[partner];
joined_r0x090cdb8e:
      if (predictedMove == 0 /* - */) goto sw_c9a8c_82;
    }
    break;
  case 46: /* EFFECT_FOCUS_ENERGY */
sw_c9a8c_46:
    if ((int)(data->atkStatus2 << 0xb) < 0) break;
    if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
        (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)))) && (gChosenMovesByBanks[partner] != 0)) {
      bankAtk_ = IsMaxMoveWithEffect(partnerMove,0x19);
      goto joined_r0x090cf272;
    }
    goto sw_c9a8c_82;
  case 47: /* EFFECT_RECOIL */
sw_c9a8c_47:
    if ((data->atkAbility != 0x73 /* Magic Guard */) && (data->atkAbility != 0x45 /* Rock Head */)) {
      moveTarget = GetFinalAIMoveDamage(move,bankAtk,bankDef,1,(void *)0x0);
      iVar16 = CheckTableForMove(move,&UNK_090401e6);
      if (iVar16 == 0) {
        iVar16 = CheckTableForMove(move,&UNK_090401f2);
        if (iVar16 != 0) {
LAB_090cb46c:
          moveTarget = __udivsi3(moveTarget,3);
          goto LAB_090cb41e;
        }
        iVar16 = CheckTableForMove(move,&UNK_09040200);
        if (iVar16 != 0) {
          moveTarget = moveTarget >> 1;
          goto LAB_090cb41e;
        }
        iVar16 = CheckTableForMove(move,&UNK_09040208);
        if (iVar16 != 0) {
          moveTarget = moveTarget << 1;
          goto LAB_090cb46c;
        }
        iVar16 = CheckTableForMove(move,&UNK_0904020a);
        if (iVar16 != 0) {
          moveTarget = moveTarget * 3 >> 2;
          goto LAB_090cb41e;
        }
        iVar16 = CheckTableForMove(move,&UNK_0904020c);
        if (iVar16 != 0) goto LAB_090cb41e;
        if ((move == 0x295 /* Mind Blown */) || (move == 0x2c8 /* Steel Beam */)) {
          iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
          if (iVar16 != 0) goto LAB_090cb104;
          moveTarget = (uint)(gBattleMons[bankAtk_].maxHP >> 1);
          goto LAB_090cb41e;
        }
      }
      else {
        moveTarget = moveTarget >> 2;
LAB_090cb41e:
        moveTarget = MathMax(1,moveTarget);
      }
      if ((gBattleMons[bankAtk_].hp <= moveTarget) &&
         (moveType = ViableMonCountFromBank(bankDef_), 1 < moveType)) {
        if (gBattleMons[bankDef_].hp <= moveTarget) {
          bVar4 = 1;
LAB_090ca442:
          bVar4 = CanKnockOutWithoutMove(move,bankAtk,bankDef,bVar4);
          if (bVar4 == 0) goto sw_c9a8c_82;
        }
LAB_090ca4ce:
        DecreaseViability(viabilityPtr,4);
        goto sw_c9a8c_82;
      }
    }
    goto sw_c9ecc_1;
  case 48: /* EFFECT_CONFUSE */
    goto sw_c9a8c_48;
  case 56: /* EFFECT_TRANSFORM */
sw_c9a8c_56:
    if (-1 < (int)(data->atkStatus2 << 10)) {
      bankAtk_ = data->defStatus2 & 0x1200000;
      goto joined_r0x090cf272;
    }
    break;
  case 64: /* EFFECT_REFLECT */
sw_c9a8c_64:
    bankDef_ = gNewBS;
    if (move == 0x243 /* Aurora Veil */) {
      iVar16 = GetBattlerSide(bankAtk_,0x243,&gNewBS,&GetBattlerSide);
      if (((*(char *)(bankDef_ + iVar16 + 0x15) == '\0') && ((gBattleWeather & 0x180) != 0)) &&
         (iVar16 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar16 == 0)) {
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          predictedMove = gBattleMons[data->foe1].hp;
          if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0))
          {
            if (predictedMove != 0 /* - */) {
LAB_090cb67e:
              if (gBattleMons[data->foe2].hp == 0) goto LAB_090cb692;
LAB_090cb6a4:
              if (gChosenMovesByBanks[partner] != 0) {
                iVar16 = IsMaxMoveWithEffect(partnerMove,0x1b);
                goto joined_r0x090cd65e;
              }
            }
          }
          else {
            if ((gBattleMoves[(int)partnerMove].effect == 0x41 /* EFFECT_REFLECT */) && (gChosenMovesByBanks[partner] != 0))
            break;
            if (predictedMove != 0 /* - */) goto LAB_090cb67e;
LAB_090cb692:
            if (gBattleMons[partner].hp != 0) goto LAB_090cb6a4;
          }
        }
        goto sw_c9a8c_82;
      }
    }
    else {
      iVar16 = sub_2023dc4(bankAtk_,move,0x243,&GetBattlerSide);
      if (((gSideStatuses[iVar16] & 1) == 0) &&
         (((gBattleTypeFlags & 1) == 0 ||
          ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
            (gBattleMons[partner].hp == 0)) ||
           ((gBattleMoves[(int)partnerMove].effect != 0x41 /* EFFECT_REFLECT */ || (gChosenMovesByBanks[partner] == 0))))))))
      goto LAB_090cb20e;
    }
    break;
  case 66: /* EFFECT_PARALYZE */
  case 3:
sw_c9a8c_66:
    iVar16 = CanBeParalyzed(bankDef_,1);
    if ((((iVar16 != 0) && (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 == 0))
        && (iVar16 = PartnerMoveEffectIsStatusSameTarget(data,move,bankDef_), iVar16 == 0)) &&
       ((move == 0x89 /* Glare */ ||
        (bankAtk_ = AI_SpecialTypeCalc(move,bankAtk_,bankDef_), (bankAtk_ & 0x29) == 0)))) {
      iVar16 = MoveInMoveset(0x9c /* Rest */,bankDef_);
      if (iVar16 == 0) {
        move = GetPokemonOnSideSpeedAverage(bankAtk);
        uVar11 = GetPokemonOnSideSpeedAverage(bankDef);
        if (uVar11 < move) {
          DecreaseViability(viabilityPtr,2);
        }
        goto sw_c9a8c_82;
      }
      goto LAB_090cb79a;
    }
    break;
  case 78: /* EFFECT_SUBSTITUTE */
sw_c9a8c_78:
    if (((int)(data->atkStatus2 << 7) < 0) || (bankAtk_ = func_0x090dd734(bankAtk_), bankAtk_ < 0x1a))
    break;
    iVar16 = sub_90746d8(data->defAbility);
    if ((iVar16 == 0) && (bVar4 = SoundMoveInMoveset(bankDef), bVar4 == 0))
    goto sw_c9a8c_82;
    goto LAB_090cb176;
  case 79: /* EFFECT_RECHARGE */
sw_c9a8c_79:
    if (((data->atkAbility != 0x36 /* Truant */) &&
        (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar4 != 0)) &&
       (bVar4 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1), bVar4 != 0)) {
LAB_090cb830:
      uVar20 = 9;
      goto LAB_090cb832;
    }
    goto sw_c9ecc_1;
  case 99: /* EFFECT_SPITE */
sw_c9a8c_99:
    bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
    if (bVar4 == 0) goto joined_r0x090cb868;
    if (0xfffd < (ushort)(gLastUsedMoves[bankDef_] - 1)) break;
    goto sw_c9a8c_82;
  case 81: /* EFFECT_MIMIC */
sw_c9a8c_81:
    bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
    if (bVar4 == 0) {
      if (predictedMove == 0 /* - */) goto LAB_090cb896;
    }
    else if (0xfffd < (ushort)(gLastUsedMoves[bankDef_] - 1)) {
LAB_090cb896:
      uVar20 = 10;
      goto LAB_090cb898;
    }
    goto LAB_090cae7e;
  case 83: /* EFFECT_LEECH_SEED */
sw_c9a8c_83:
    iVar16 = IsOfType(bankDef_,0xc /* Grass */);
    if (((iVar16 == 0) && (-1 < (int)(data->defStatus3 << 0x1d))) && (data->defAbility != 0x40 /* Liquid Ooze */)) {
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)))) &&
         ((gBattleMoves[(int)partnerMove].effect == 0x54 /* EFFECT_LEECH_SEED */ && (gChosenMovesByBanks[partner] != 0)))) {
        moveFlags = gBattleStruct->moveTarget[partner];
joined_r0x090cecf6:
        if (moveFlags == bankDef_) break;
      }
      goto LAB_090cae7e;
    }
    break;
  case 85: /* EFFECT_DISABLE */
sw_c9a8c_85:
    if ((((gDisableStructs[bankDef_].field_0xb & 0xf) == 0) && (data->defItemEffect != 0x1c)) &&
       ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
        ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
          (gBattleMons[partner].hp == 0)) ||
         (((gBattleMoves[(int)partnerMove].effect != 0x56 /* EFFECT_DISABLE */ || (gChosenMovesByBanks[partner] == 0)) ||
          (gBattleStruct->moveTarget[partner] != bankDef_)))))))) {
      bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
      if (bVar4 == 0) goto joined_r0x090cf81c;
      if ((ushort)(gLastUsedMoves[bankDef_] - 1) < 0xfffe) goto sw_c9a8c_82;
    }
    break;
  case 88: /* EFFECT_COUNTER */
  case 143: /* EFFECT_MIRROR_COAT */
sw_c9a8c_88:
    if (((gBattleMoves[predictedMove].split == 2) || (predictedMove == 0 /* - */)) ||
       (iVar16 = MoveBlockedBySubstitute(predictedMove,bankDef_,bankAtk_), iVar16 != 0)) {
      DecreaseViability(viabilityPtr,10);
    }
    if (((move == 0x209 /* Metal Burst */) &&
        (bVar4 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar4 != 0)) ||
       (iVar16 = Random(), -1 < iVar16 << 0x1f)) {
LAB_090cba70:
      uVar20 = 10;
      goto LAB_090cb832;
    }
    goto sw_c9ecc_1;
  case 89: /* EFFECT_ENCORE */
sw_c9a8c_89:
    if ((((gDisableStructs[bankDef_].field_0xe & 0xf) != 0) || (data->defItemEffect == 0x1c)) ||
       (((int)(gBattleTypeFlags << 0x1f) < 0 &&
        (((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)) &&
          ((gBattleMoves[(int)partnerMove].effect == 0x5a /* EFFECT_ENCORE */ && (gChosenMovesByBanks[partner] != 0)))) &&
         (gBattleStruct->moveTarget[partner] == bankDef_)))))) break;
    bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
    if (bVar4 == 0) goto joined_r0x090cf81c;
    iVar16 = sub_90a0104(bankDef_);
    goto joined_r0x090cd65e;
  case 188: /* EFFECT_ENDEAVOR */
sw_c9a8c_188:
    if ((uint)gBattleMons[bankAtk_].hp <=
        (uint)((int)((uint)gBattleMons[bankDef_].hp + (uint)gBattleMons[bankAtk_].hp) >> 1))
    goto sw_c9ecc_1;
    break;
  case 90: /* EFFECT_PAIN_SPLIT */
sw_c9a8c_90:
    if ((uint)((int)((uint)gBattleMons[bankDef_].hp + (uint)gBattleMons[bankAtk_].hp) >> 1) <
        (uint)gBattleMons[bankAtk_].hp) break;
    goto sw_c9a8c_82;
  case 91: /* EFFECT_SNORE */
sw_c9a8c_91:
    if ((1 < (data->atkStatus1 & 7)) || (data->atkAbility == 0xe7 /* Comatose */))
    goto sw_c9ecc_1;
    break;
  case 96: /* EFFECT_SLEEP_TALK */
sw_c9a8c_96:
    if (((data->atkStatus1 & 7) < 2) && (data->atkAbility != 0xe7 /* Comatose */)) break;
    goto sw_c9a8c_82;
  case 92: /* EFFECT_CONVERSION_2 */
sw_c9a8c_92:
    bVar4 = *(bool8 *)(gNewBS + bankDef_ + 0x65);
    goto joined_r0x090ce4be;
  case 93: /* EFFECT_LOCK_ON */
sw_c9a8c_93:
    if (move == 0x252 /* Laser Focus */) {
      iVar16 = sub_9075550(bankAtk_);
      if (iVar16 != 0) break;
      if (data->defAbility == 4 /* Battle Armor */) goto LAB_090cb176;
    }
    else {
      if ((((data->atkStatus3 & 0x18) != 0) || (data->atkAbility == 0x7e /* No Guard */)) ||
         (data->defAbility == 0x7e /* No Guard */)) break;
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)) &&
          ((gBattleMoves[(int)partnerMove].effect == 0x5e /* EFFECT_LOCK_ON */ && (gChosenMovesByBanks[partner] != 0)))))) {
        moveFlags = gBattleStruct->moveTarget[partner];
        goto joined_r0x090cf3b6;
      }
    }
    goto sw_c9a8c_82;
  case 94: /* EFFECT_SKETCH */
sw_c9a8c_94:
    if (gLastUsedMoves[bankDef_] != 0) goto LAB_090cae7e;
    break;
  case 97: /* EFFECT_DESTINY_BOND */
sw_c9a8c_97:
    if (*(char *)(gNewBS + bankAtk_ + 0x55) == '\0') {
      iVar16 = data->atkStatus2 << 6;
      goto joined_r0x090cc5ea;
    }
    break;
  case 100: /* EFFECT_FALSE_SWIPE */
sw_c9a8c_100:
    bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1);
    if (bVar4 != 0) {
      bVar4 = CanKnockOutWithoutMove(move,bankAtk,bankDef,0);
      goto joined_r0x090cc7c4;
    }
    goto sw_c9a8c_82;
  case 101: /* EFFECT_HEAL_BELL */
sw_c9a8c_101:
    iVar16 = sub_9073ba8(move);
    if (iVar16 == 0) {
      bVar4 = PartyMemberStatused(bankAtk,0);
      if (bVar4 == 0) break;
      if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        predictedMove = gBattleMons[data->foe1].hp;
        if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
          if (predictedMove != 0 /* - */) {
LAB_090cbe30:
            if (gBattleMons[data->foe2].hp == 0) goto LAB_090cbe44;
LAB_090cbe56:
            if (gChosenMovesByBanks[partner] != 0) {
              iVar16 = IsMaxMoveWithEffect(partnerMove,0x29);
              goto joined_r0x090cd65e;
            }
          }
        }
        else {
          if ((gBattleMoves[(int)partnerMove].effect == 0x66 /* EFFECT_HEAL_BELL */) && (gChosenMovesByBanks[partner] != 0))
          break;
          if (predictedMove != 0 /* - */) goto LAB_090cbe30;
LAB_090cbe44:
          if (gBattleMons[partner].hp != 0) goto LAB_090cbe56;
        }
      }
    }
    else {
      bVar4 = PartyMemberStatused(bankAtk,1);
      if (bVar4 == 0) break;
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)))) && (gBattleMoves[(int)partnerMove].effect == 0x66 /* EFFECT_HEAL_BELL */)) {
        predictedMove = gChosenMovesByBanks[partner];
        goto joined_r0x090cdb8e;
      }
    }
    goto sw_c9a8c_82;
  case 105: /* EFFECT_MEAN_LOOK */
sw_c9a8c_105:
    if (moveSplit != 2) goto sw_c9a8c_1;
sw_cf924_105:
    bVar4 = IsTrapped(bankDef,1);
    if (bVar4 != 0) break;
    if ((int)(gBattleTypeFlags << 0x1f) < 0) {
      predictedMove = gBattleMons[data->foe1].hp;
      if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
        if (predictedMove != 0 /* - */) {
LAB_090cbf0a:
          if (gBattleMons[data->foe2].hp == 0) goto LAB_090cbf1e;
LAB_090cbf30:
          if (gChosenMovesByBanks[partner] != 0) {
            iVar16 = IsMaxMoveWithEffect(partnerMove,0x1a);
            goto joined_r0x090cd65e;
          }
        }
      }
      else {
        if (((gBattleMoves[(int)partnerMove].effect == 0x6a /* EFFECT_MEAN_LOOK */) && (gChosenMovesByBanks[partner] != 0)) &&
           (gBattleStruct->moveTarget[partner] == bankDef_)) break;
        if (predictedMove != 0 /* - */) goto LAB_090cbf0a;
LAB_090cbf1e:
        if (gBattleMons[partner].hp != 0) goto LAB_090cbf30;
      }
    }
    goto sw_c9a8c_82;
  case 106: /* EFFECT_NIGHTMARE */
sw_c9a8c_106:
    if (((int)(data->defStatus2 << 4) < 0) ||
       (((data->defStatus1 & 7) == 0 && (data->defAbility != 0xe7 /* Comatose */)))) break;
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)) &&
        ((gBattleMoves[(int)partnerMove].effect == 0x6b /* EFFECT_NIGHTMARE */ && (gChosenMovesByBanks[partner] != 0)))))) {
      moveFlags = gBattleStruct->moveTarget[partner];
      goto joined_r0x090cf3b6;
    }
    goto sw_c9a8c_82;
  case 108: /* EFFECT_CURSE */
sw_c9a8c_108:
    iVar16 = IsOfType(bankAtk_,7 /* Ghost */);
    if (iVar16 == 0) {
      if (data->atkAbility == 0xbf /* Contrary */) {
        if ((gBattleMons[bankAtk_].statStages[0] < 1) && (gBattleMons[bankAtk_].statStages[1] < 1)) {
          sVar2 = gBattleMons[bankAtk_].statStages[2];
          goto joined_r0x090cccfa;
        }
      }
      else if ((0xb < gBattleMons[bankAtk_].statStages[0]) &&
              (0xb < gBattleMons[bankAtk_].statStages[1])) {
        sVar2 = gBattleMons[bankAtk_].statStages[2];
        goto joined_r0x090caa36;
      }
    }
    else {
      if (((int)(data->defStatus2 << 3) < 0) ||
         ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)))) &&
          (((gBattleMoves[(int)partnerMove].effect == 0x6d /* EFFECT_CURSE */ && (gChosenMovesByBanks[partner] != 0)) &&
           (gBattleStruct->moveTarget[partner] == bankDef_)))))) break;
      bankAtk_ = func_0x090dd734(bankAtk_);
      if (bankAtk_ < 0x33) {
LAB_090cc096:
        DecreaseViability(viabilityPtr,6);
      }
    }
    goto sw_c9a8c_82;
  case 110: /* EFFECT_PROTECT */
sw_c9a8c_110:
    if (move == 0x27c /* Mat Block */) {
      predictedMove = (ushort)gDisableStructs[bankAtk_].isFirstTurn;
LAB_090cc25c:
      if (predictedMove == 0 /* - */) break;
    }
    else if (move < 0x27d) {
      if (move == 0xcb /* Endure */) {
        if ((gBattleMons[bankAtk_].hp == 1) ||
           (bVar4 = IsTakingSecondaryDamage(bankAtk,0x58), bVar4 != 0)) break;
      }
      else if (move == 0x27b /* Crafty Guard */) goto LAB_090cc21a;
    }
    else if (move < 0x27f) {
LAB_090cc21a:
      if (-1 < (int)(gBattleTypeFlags << 0x1f)) break;
      if ((gBattleMons[data->foe1].hp == 0) || (gBattleMons[data->foe2].hp == 0)) {
        predictedMove = gBattleMons[partner].hp;
        goto LAB_090cc25c;
      }
    }
    if (((int)(gBattleMons[bankDef_].status2 << 9) < 0) ||
       (iVar16 = GetBankAbility(bankDef_), iVar16 == 199)) break;
    if ((gBattleMoves[*(ushort *)(&gLastResultingMoves + bankAtk_ * 2)].effect == 0x6f /* EFFECT_PROTECT */) &&
       ((1 < ((uint)(move[-8].otName + 7) & 0xffff) && (move != 0x27b /* Crafty Guard */)))) {
      bVar4 = WillFaintFromSecondaryDamage(bankAtk);
      if ((bVar4 == 0) || (iVar16 = IsMoxieAbility(data->defAbility), iVar16 != 0)) {
        if (gDisableStructs[bankAtk_].protectUses < 2) goto LAB_090cc190;
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)))) goto LAB_090cc184;
        uVar20 = 6;
      }
      else {
LAB_090cc184:
        uVar20 = 10;
      }
      DecreaseViability(viabilityPtr,uVar20);
    }
LAB_090cc190:
    if (((gBattleResources->ai->aiFlags == 1) && ((gBattleTypeFlags & 1) != 0)) &&
       (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
        (gBattleMons[partner].hp != 0)))) {
      uVar3 = ShouldProtect(bankAtk,bankDef,move);
      if ((uVar3 == 1) || (uVar3 == 4)) {
        IncreaseFoeProtectionViability((s16 *)viabilityPtr,0xff,bankAtk,bankDef);
      }
      else if (uVar3 == 3) {
        IncreaseAllyProtectionViability((s16 *)viabilityPtr,0xff);
      }
    }
    goto sw_c9a8c_82;
  case 111: /* EFFECT_SPIKES */
sw_c9a8c_111:
    if (((uint)&move[-9].level & 0xfffb) == 0) goto sw_c9ecc_1;
    bVar4 = IsBankIncapacitated(bankDef);
    if (((bVar4 == 0) && (bVar4 = HasUsedMoveWithEffect(bankDef,0x81), bVar4 != 0)) &&
       (iVar16 = Random(), -1 < iVar16 << 0x1f)) goto LAB_090cb104;
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
        (gBattleMons[partner].hp != 0)))) {
      uVar30 = ViableMonCountFromBank(bankDef_);
      uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
      if ((uint)uVar30 < 3) break;
    }
    else {
      moveTarget = ViableMonCountFromBank(bankDef_);
      if ((moveTarget < 4) || (iVar16 = GetBankAbility(~bankAtk_ & 1), iVar16 == 0x5a))
      goto sw_c9a8c_82;
      iVar16 = MoveInMoveset(0xe5 /* Rapid Spin */,bankDef_);
      if (((iVar16 == 0) ||
          ((iVar16 = IsOfType(bankAtk_,7 /* Ghost */), iVar16 != 0 ||
           (iVar16 = VarGet(0x5119), iVar16 == 0x12)))) &&
         ((iVar16 = MoveInMoveset(0x204 /* Defog */,bankDef_), iVar16 == 0 ||
          (iVar16 = VarGet(0x5119), iVar16 == 0x12)))) {
        uVar30 = MoveInMoveset(0x115 /* Magic Coat */,bankDef_);
        uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
        if ((int)uVar30 == 0) goto LAB_090cc3c2;
      }
      uVar30 = Random();
      uVar20 = (undefined4)((ulonglong)uVar30 >> 0x20);
      if (-1 < (int)uVar30 << 0x1f) {
        DecreaseViability(viabilityPtr,10);
        uVar20 = extraout_r1_00;
      }
    }
LAB_090cc3c2:
    if (move == 0x1d4 /* Stealth Rock */) {
      iVar16 = GetBattlerSide(bankDef_,uVar20,0x1d4,&GetBattlerSide);
      if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar16 * 0xb] << 0x1b) < 0) {
LAB_090cc60e:
        DecreaseViability(viabilityPtr,0x14);
      }
      else if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        predictedMove = gBattleMons[data->foe1].hp;
        if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
          if (predictedMove != 0 /* - */) {
LAB_090cc6ac:
            if (gBattleMons[data->foe2].hp == 0) goto LAB_090cc6c0;
LAB_090cc6d2:
            if ((gChosenMovesByBanks[partner] != 0) &&
               (iVar16 = IsMaxMoveWithEffect(partnerMove,0x1f), iVar16 != 0)) goto LAB_090cc60e;
          }
        }
        else {
          if ((gChosenMovesByBanks[partner] != 0) && (partnerMove == 0x1d4 /* Stealth Rock */))
          goto LAB_090cc60e;
          if (predictedMove != 0 /* - */) goto LAB_090cc6ac;
LAB_090cc6c0:
          if (gBattleMons[partner].hp != 0) goto LAB_090cc6d2;
        }
      }
    }
    else if (move < 0x1d5) {
      if (move == 0xbf /* Spikes */) {
        bankAtk_ = GetBattlerSide(bankDef_,uVar20,0xbf,&GetBattlerSide);
        move = 0xb;
        if (((&gSideTimers[0].field_0xa)[bankAtk_ * 0xb] & 3) == 3) break;
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          if ((gBattleMons[data->foe1].hp == 0) ||
             (bankAtk_ = (uint)data->foe2, gBattleMons[bankAtk_].hp == 0)) {
            bankAtk_ = partner * 0x58;
            move = gBattleMons + partner;
            if (gBattleMons[partner].hp == 0) goto LAB_090cc472;
          }
          move = (BattlePokemon *)(partner * 2);
          if ((gChosenMovesByBanks[partner] != 0) && (partnerMove == 0xbf /* Spikes */)) {
            bankAtk_ = GetBattlerSide(bankDef_,bankAtk_,move,&GetBattlerSide);
            move = 0xb;
            if (((&gSideTimers[0].field_0xa)[bankAtk_ * 0xb] & 3) == 2) break;
          }
        }
LAB_090cc472:
        if ((1 < gBattleResources->ai->aiFlags) &&
           (iVar16 = GetBattlerSide(bankDef_,bankAtk_,move,&GetBattlerSide),
           ((&gSideTimers[0].field_0xa)[iVar16 * 0xb] & 3) != 0)) {
          bVar4 = HazardClearingMoveInMovesetThatAffects(bankDef,bankAtk);
          goto joined_r0x090cc7c4;
        }
      }
    }
    else if (move == 0x1d5 /* Toxic Spikes */) {
      bankAtk_ = GetBattlerSide(bankDef_,uVar20,0x1d5,&GetBattlerSide);
      if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[bankAtk_ * 0xb] << 0x1c) < 0) break;
      move = 0xb;
      if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        if ((gBattleMons[data->foe1].hp == 0) ||
           (bankAtk_ = (uint)data->foe2, gBattleMons[bankAtk_].hp == 0)) {
          bankAtk_ = partner * 0x58;
          move = gBattleMons + partner;
          if (gBattleMons[partner].hp == 0) goto LAB_090cc788;
        }
        move = (BattlePokemon *)(partner * 2);
        if ((gChosenMovesByBanks[partner] != 0) &&
           (move = partnerMove, partnerMove == 0x1d5 /* Toxic Spikes */)) {
          bankAtk_ = GetBattlerSide(bankDef_,bankAtk_,0x1d5,&GetBattlerSide);
          move = 0xb;
          if (((byte)(&gSideTimers[0].field_0xa)[bankAtk_ * 0xb] & 0xf) >> 2 == 1) break;
        }
      }
LAB_090cc788:
      if ((1 < gBattleResources->ai->aiFlags) &&
         (iVar16 = GetBattlerSide(bankDef_,bankAtk_,move,&GetBattlerSide),
         ((byte)(&gSideTimers[0].field_0xa)[iVar16 * 0xb] & 0xf) >> 2 == 1)) {
        bVar4 = HazardClearingMoveInMovesetThatAffects(bankDef,bankAtk);
        goto joined_r0x090cc7c4;
      }
    }
    else if (move == 0x1e1 /* Sticky Web */) {
      iVar16 = GetBattlerSide(bankDef_);
      if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar16 * 0xb] << 0x1a) < 0) break;
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)) &&
          ((gChosenMovesByBanks[partner] != 0 && (partnerMove == 0x1e1 /* Sticky Web */)))))) {
        iVar16 = GetBattlerSide(bankDef_);
        iVar16 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar16 * 0xb] << 0x1a;
        goto joined_r0x090cc5ea;
      }
    }
    goto sw_c9a8c_82;
  case 112: /* EFFECT_FORESIGHT */
sw_c9a8c_112:
    if (move == 0x1c9 /* Miracle Eye */) {
      if ((int)(data->defStatus3 << 1) < 0) {
        DecreaseViability(viabilityPtr,10);
      }
      uVar20 = 0x11;
      if (4 < gBattleMons[bankDef_].statStages[6]) {
LAB_090cc804:
        iVar16 = IsOfType(bankDef_,uVar20);
        if ((iVar16 != 0) &&
           ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
            ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[partner].hp == 0)) ||
             (((gBattleMoves[(int)partnerMove].effect != 0x71 /* EFFECT_FORESIGHT */ || (gChosenMovesByBanks[partner] == 0)) ||
              (gBattleStruct->moveTarget[partner] != bankDef_))))))))
        goto sw_c9a8c_82;
      }
    }
    else {
      if ((int)(data->defStatus2 << 2) < 0) break;
      if (4 < gBattleMons[bankDef_].statStages[6]) {
        uVar20 = 7;
        goto LAB_090cc804;
      }
    }
    goto LAB_090cb104;
  case 113: /* EFFECT_PERISH_SONG */
sw_c9a8c_113:
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
        (gBattleMons[partner].hp != 0)))) {
      moveTarget = ViableMonCountFromBank(bankAtk_);
      if ((((moveTarget < 3) && (data->atkAbility != 0x2b /* Soundproof */)) &&
          ((data->atkPartnerAbility != 0x2b /* Soundproof */ &&
           (moveTarget = ViableMonCountFromBank(~bankAtk_ & 1), 2 < moveTarget)))) ||
         ((((bankAtk_ = ~bankAtk_ & 1, gBattleMons[bankAtk_].hp == 0 ||
            (iVar16 = GetBankAbility(bankAtk_), iVar16 == 0x2b)) ||
           ((int)(gStatuses3[bankAtk_] << 0x1a) < 0)) &&
          (((gBattleMons[bankAtk_ | 2].hp == 0 ||
            (iVar16 = GetBankAbility(((bankAtk & 1) == 0) + '\x02'), iVar16 == 0x2b)) ||
           ((int)(gStatuses3[bankAtk_ | 2] << 0x1a) < 0)))))) break;
      if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)))) &&
         ((gBattleMoves[move].effect == gBattleMoves[(int)partnerMove].effect &&
          (gChosenMovesByBanks[partner] != 0)))) {
        moveFlags = gBattleStruct->moveTarget[partner];
        goto joined_r0x090cf3b6;
      }
    }
    else {
      iVar16 = ViableMonCountFromBank(bankAtk_);
      if (((iVar16 == 1) && (data->atkAbility != 0x2b /* Soundproof */)) &&
         (bankDef_ = ViableMonCountFromBank(bankDef_), 1 < bankDef_)) {
        DecreaseViability(viabilityPtr,10);
      }
      if (((int)(gStatuses3[~bankAtk_ & 1] << 0x1a) < 0) ||
         (iVar16 = GetBankAbility(), iVar16 == 0x2b)) break;
    }
    goto sw_c9a8c_82;
  case 114: /* EFFECT_SANDSTORM */
sw_c9a8c_114:
    if ((gBattleWeather & 0x7818) == 0) {
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)))) || (gChosenMovesByBanks[partner] == 0))
      goto sw_c9a8c_82;
      moveFlags = gBattleMoves[(int)partnerMove].effect;
      if (((1 < (byte)(moveFlags + 0x78)) && (moveFlags != 0x73)) && (moveFlags != 0xa4)) {
        iVar16 = sub_908dd0c(partnerMove);
        goto joined_r0x090cd65e;
      }
    }
    break;
  case 117: /* EFFECT_SWAGGER */
sw_c9a8c_117:
    if (bankDef_ != partner) goto sw_c9a8c_48;
    if (data->defAbility == 0xbf /* Contrary */) goto LAB_090cb896;
    goto LAB_090cae7e;
  case 119: /* EFFECT_ATTRACT */
sw_c9a8c_119:
    iVar16 = sub_9075a8c(bankDef_,bankAtk_);
    if (iVar16 == 0) break;
    if ((int)(gBattleTypeFlags << 0x1f) < 0) {
      predictedMove = gBattleMons[data->foe1].hp;
      if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
        if (predictedMove != 0 /* - */) {
LAB_090ccbc6:
          if (gBattleMons[data->foe2].hp == 0) goto LAB_090ccbda;
LAB_090ccbec:
          if (gChosenMovesByBanks[partner] != 0) {
            iVar16 = IsMaxMoveWithEffect(partnerMove,0x1c);
            goto joined_r0x090cd65e;
          }
        }
      }
      else {
        if (((gBattleMoves[(int)partnerMove].effect == 0x78 /* EFFECT_ATTRACT */) && (gChosenMovesByBanks[partner] != 0)) &&
           (gBattleStruct->moveTarget[partner] == bankDef_)) break;
        if (predictedMove != 0 /* - */) goto LAB_090ccbc6;
LAB_090ccbda:
        if (gBattleMons[partner].hp != 0) goto LAB_090ccbec;
      }
    }
    goto sw_c9a8c_82;
  case 123: /* EFFECT_SAFEGUARD */
sw_c9a8c_123:
    iVar16 = sub_907531c(bankAtk_);
    if (iVar16 != 0) break;
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)) && (gBattleMoves[(int)partnerMove].effect == 0x7c /* EFFECT_SAFEGUARD */)))) {
      predictedMove = gChosenMovesByBanks[partner];
      goto joined_r0x090cdb8e;
    }
    goto sw_c9a8c_82;
  case 124: /* EFFECT_BURN_UP */
sw_c9a8c_124:
    moveTarget = IsOfType(bankAtk_,10 /* Fire */);
joined_r0x090cf8da:
    if (moveTarget != 0) goto sw_c9ecc_1;
    break;
  case 126: /* EFFECT_BATON_PASS */
sw_c9a8c_126:
    if ((((uint)((int)&move[-6].otId + 2) & 0xffff) < 2) || (move == 0x2d8 /* Flip Turn */))
    goto sw_c9ecc_1;
    iVar16 = HasMonToSwitchTo(bankAtk_);
    if (iVar16 == 0) break;
    if (move == 0x230 /* Parting Shot */) {
      if (data->defAbility == 0xbf /* Contrary */) {
        if (0xb < gBattleMons[bankDef_].statStages[0]) {
          sVar2 = gBattleMons[bankDef_].statStages[3];
          goto joined_r0x090cccfa;
        }
      }
      else {
        iVar16 = sub_90becd0(1,bankDef_,bankAtk_);
        if (iVar16 != 0) {
          bankAtk_ = sub_90becd0(4,bankDef_,bankAtk_,data->defAbility);
          goto joined_r0x090cf272;
        }
      }
    }
    else {
      if (move == 0x307 /* Shed Tail */) {
        bankAtk_ = func_0x090dd734(bankAtk_);
        goto joined_r0x090cd146;
      }
      if (((-1 < (int)(data->atkStatus2 << 7)) && ((data->atkStatus3 & 0x4a00400) == 0)) &&
         (bVar4 = AnyStatIsRaised(bankAtk), bVar4 == 0)) goto LAB_090cc096;
    }
    goto sw_c9a8c_82;
  case 128: /* EFFECT_RAPID_SPIN */
sw_c9a8c_128:
    if (move == 0x204 /* Defog */) {
      iVar16 = GetBattlerSide(bankDef_,uVar20,0x204,&GetBattlerSide);
      moveTarget = gNewBS;
      if (((((gSideStatuses[iVar16] & 0x123) != 0) ||
           (iVar16 = sub_2023be4(bankDef_), *(char *)(moveTarget + iVar16 + 0x15) != '\0')) ||
          (iVar16 = sub_2023be4(bankAtk_), (int)((uint)gSideStatuses[iVar16] << 0x1b) < 0)) &&
         ((int)(gBattleTypeFlags << 0x1f) < 0)) {
        predictedMove = gBattleMons[data->foe1].hp;
        if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
          if (predictedMove != 0 /* - */) {
LAB_090cceca:
            if (gBattleMons[data->foe2].hp == 0) goto LAB_090ccee0;
            goto LAB_090ccef2;
          }
        }
        else {
          if ((gBattleMoves[(int)partnerMove].effect == 0x81 /* EFFECT_RAPID_SPIN */) && (gChosenMovesByBanks[partner] != 0))
          break;
          if (predictedMove != 0 /* - */) goto LAB_090cceca;
LAB_090ccee0:
          if (gBattleMons[partner].hp != 0) {
LAB_090ccef2:
            if ((gChosenMovesByBanks[partner] != 0) &&
               (iVar16 = IsMaxMoveWithEffect(partnerMove,0x20), iVar16 != 0)) break;
          }
        }
      }
      iVar16 = GetBattlerSide(bankDef_);
      if ((-1 < (int)((uint)gSideStatuses[iVar16] << 0x1b)) &&
         ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
          ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
            (gBattleMons[partner].hp == 0)) ||
           ((gBattleMoves[(int)partnerMove].effect != 0x70 /* EFFECT_SPIKES */ ||
            (bVar4 = MoveWouldHitBeforeOtherMove(0x204,bankAtk,partnerMove,partner), bVar4 != 0))))))
         )) goto sw_c9a8c_23;
    }
    else {
      if (move != 0x2b2 /* Court Change */) goto sw_c9ecc_1;
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)))) ||
         ((gChosenMovesByBanks[partner] == 0 || (partnerMove != 0x2b2 /* Court Change */)))) {
        iVar15 = GetBattlerSide(bankDef_);
        iVar16 = GetBattlerSide(bankAtk_);
        if (iVar15 != iVar16) {
          if (gBattleResources->ai->aiFlags < 2) goto sw_c9a8c_82;
          iVar16 = sub_90c5aa8(bankAtk_,bankDef_);
          if (iVar16 != 0) {
            iVar16 = sub_90c5aa8(bankDef_,bankAtk_);
            goto joined_r0x090cd65e;
          }
        }
      }
    }
    break;
  case 23: /* EFFECT_EVASION_DOWN */
  case 63: /* EFFECT_EVASION_DOWN_2 */
sw_c9a8c_23:
    moveFlags = data->defAbility;
    uVar20 = 7;
LAB_090caea6:
    predictedMove = sub_90becd0(uVar20,bankDef_,bankAtk_,moveFlags);
joined_r0x090cb868:
    if (predictedMove != 0 /* - */) {
LAB_090cae7e:
      iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
joined_r0x090cd65e:
      if (iVar16 == 0) goto sw_c9a8c_82;
    }
    break;
  case 135: /* EFFECT_RAIN_DANCE */
sw_c9a8c_135:
    if ((gBattleWeather & 0x7807) == 0) {
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)) || (gChosenMovesByBanks[partner] == 0))))
      goto sw_c9a8c_82;
      moveFlags = gBattleMoves[(int)partnerMove].effect;
      if (((1 < (byte)(moveFlags + 0x78)) && (moveFlags != 0x73)) && (moveFlags != 0xa4)) {
        iVar16 = sub_908dd0c(partnerMove);
        goto joined_r0x090cd65e;
      }
    }
    break;
  case 136: /* EFFECT_SUNNY_DAY */
sw_c9a8c_136:
    if ((gBattleWeather & 0x7860) == 0) {
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)) || (gChosenMovesByBanks[partner] == 0))))
      goto sw_c9a8c_82;
      moveFlags = gBattleMoves[(int)partnerMove].effect;
      if (((1 < (byte)(moveFlags + 0x78)) && (moveFlags != 0x73)) && (moveFlags != 0xa4)) {
        iVar16 = sub_908dd0c(partnerMove);
        goto joined_r0x090cd65e;
      }
    }
    break;
  case 141: /* EFFECT_BELLY_DRUM */
sw_c9a8c_141:
    if (data->atkAbility != 0xbf /* Contrary */) {
      bankAtk_ = func_0x090dd734(bankAtk_);
joined_r0x090cd146:
      if (0x32 < bankAtk_) goto sw_c9a8c_82;
    }
    break;
  case 142: /* EFFECT_PSYCH_UP */
sw_c9a8c_142:
    if ((move != 0x265 /* Spect Thief */) && (move != 0x5a /* Soul Robbery */))
    goto sw_c9a8c_24;
    goto sw_c9ecc_1;
  case 24: /* EFFECT_HAZE */
sw_c9a8c_24:
    bankDef_ = gBattleResources->ai->aiFlags;
    if (bankDef_ < 3) {
      iVar16 = 0;
      do {
        if ((6 < gBattleMons[bankAtk_].statStages[iVar16]) ||
           (((gBattleTypeFlags & 1) != 0 &&
            ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[partner].hp != 0)) && (6 < gBattleMons[partner].statStages[iVar16]))))))
        goto LAB_090ca2dc;
        iVar16 = iVar16 + 1;
      } while (iVar16 != 7);
      if (bankDef_ == 2) goto LAB_090cd1fc;
    }
    else {
LAB_090cd1fc:
      uVar3 = CountUsefulBoosts(bankDef);
      uVar7 = CountUsefulDebuffs(bankAtk);
      uVar5 = CountUsefulDebuffs(bankDef);
      uVar6 = CountUsefulBoosts(bankAtk);
      if ((uint)uVar3 + (uint)uVar7 < (uint)uVar5 + (uint)uVar6) break;
    }
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)) && (gBattleMoves[(int)partnerMove].effect == moveEffect)))) {
      predictedMove = gChosenMovesByBanks[partner];
      goto joined_r0x090cdb8e;
    }
    goto sw_c9a8c_82;
  case 147: /* EFFECT_FUTURE_SIGHT */
sw_c9a8c_147:
    moveFlags = (&gWishFutureKnock)[bankDef_];
joined_r0x090cd7c6:
    if (moveFlags == 0) goto sw_c9ecc_1;
    break;
  case 150: /* EFFECT_SOLARBEAM */
sw_c9a8c_150:
    if (((gBattleWeather & 0x860) == 0) ||
       ((iVar16 = sub_9076620(data->atkItemEffect), iVar16 != 0 ||
        (iVar16 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar16 != 0))))
    goto sw_c9a8c_38;
    goto sw_c9ecc_1;
  case 38: /* EFFECT_RAZOR_WIND */
  case 74: /* EFFECT_SKY_ATTACK */
  case 144: /* EFFECT_SKULL_BASH */
sw_c9a8c_38:
    if (data->atkItemEffect != 0x7e) {
      bVar4 = WillFaintFromSecondaryDamage(bankAtk);
      uVar20 = 10;
      if (bVar4 == 0) {
        uVar20 = 4;
      }
      DecreaseViability(viabilityPtr,uVar20);
      moveTarget = data->defStatus1;
      if ((((-1 < (int)(moveTarget << 0x19)) && ((data->defStatus2 & 7) < 3)) &&
          ((data->defStatus2 & 0xf0000) == 0)) && (((moveTarget & 7) == 0 || (moveTarget == 1)))) {
        bVar4 = HasProtectionMoveInMoveset(bankDef,1);
        if ((bVar4 != 0) && (bVar4 = WillFaintFromSecondaryDamage(bankDef), bVar4 == 0)) {
LAB_090cd340:
          uVar20 = 8;
          goto LAB_090cb832;
        }
        if (data->defSpeed < data->atkSpeed) {
          bVar4 = CanKnockOut(bankDef,bankAtk);
          if ((bVar4 != 0) && (uVar20 = 4, predictedMove != 0 /* - */)) goto LAB_090cb832;
        }
        else {
          bVar4 = Can2HKO(bankDef,bankAtk);
          if ((bVar4 != 0) && (predictedMove != 0 /* - */)) goto LAB_090cd340;
        }
      }
    }
    goto sw_c9ecc_1;
  case 154: /* EFFECT_SEMI_INVULNERABLE */
sw_c9a8c_154:
    if (((predictedMove != 0 /* - */) &&
        (bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef), bVar4 != 0)) &&
       (gBattleMoves[predictedMove].effect == 0x9b /* EFFECT_SEMI_INVULNERABLE */)) {
      DecreaseViability(viabilityPtr,10);
    }
    bVar4 = WillFaintFromWeatherSoon(bankAtk);
    if ((bVar4 != 0) && ((move == 0x13 /* Fly */ || (move == 0x154 /* Bounce */))))
    goto LAB_090cba70;
    goto sw_c9ecc_1;
  case 157: /* EFFECT_FAKE_OUT */
sw_c9a8c_157:
    if ((gDisableStructs[bankAtk_].isFirstTurn == 0) ||
       (((move == 0xfc /* Fake Out */ &&
         (iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility), iVar16 != 0))
        && (((moveTarget = ViableMonCountFromBank(bankDef_), 1 < moveTarget ||
             (bVar4 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar4 == 0)) &&
            (iVar16 = HasMonToSwitchTo(bankAtk_), iVar16 == 0)))))) goto LAB_090cba70;
    goto sw_c9ecc_1;
  case 159: /* EFFECT_STOCKPILE */
sw_c9a8c_159:
    if (2 < gDisableStructs[bankAtk_].stockpileCounter) break;
    goto sw_c9a8c_82;
  case 160: /* EFFECT_SPIT_UP */
sw_c9a8c_160:
    if (gDisableStructs[bankAtk_].stockpileCounter != 0) goto sw_c9ecc_1;
    break;
  case 161: /* EFFECT_SWALLOW */
sw_c9a8c_161:
    if (gDisableStructs[bankAtk_].stockpileCounter != 0) goto sw_c9a8c_31;
    break;
  case 163: /* EFFECT_HAIL */
sw_c9a8c_163:
    if ((gBattleWeather & 0x7980) == 0) {
      if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
         ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
           (gBattleMons[partner].hp == 0)) || (gChosenMovesByBanks[partner] == 0))))
      goto sw_c9a8c_82;
      moveFlags = gBattleMoves[(int)partnerMove].effect;
      if (((1 < (byte)(moveFlags + 0x78)) && (moveFlags != 0x73)) && (moveFlags != 0xa4)) {
        iVar16 = sub_908dd0c(partnerMove);
        goto joined_r0x090cd65e;
      }
    }
    break;
  case 164: /* EFFECT_TORMENT */
sw_c9a8c_164:
    iVar16 = func_0x09074c04(bankDef_);
    if (iVar16 != 0) {
      if ((int)(gBattleTypeFlags << 0x1f) < 0) {
        predictedMove = gBattleMons[data->foe1].hp;
        if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0)) {
          if (predictedMove != 0 /* - */) {
LAB_090cd5c6:
            if (gBattleMons[data->foe2].hp == 0) goto LAB_090cd5dc;
LAB_090cd5ec:
            if ((gChosenMovesByBanks[partner] != 0) &&
               (iVar16 = IsMaxMoveWithEffect(partnerMove,0x2c), iVar16 != 0)) break;
          }
        }
        else {
          if (((gBattleMoves[(int)partnerMove].effect == 0xa5 /* EFFECT_TORMENT */) && (gChosenMovesByBanks[partner] != 0)) &&
             (gBattleStruct->moveTarget[partner] == bankDef_)) break;
          if (predictedMove != 0 /* - */) goto LAB_090cd5c6;
LAB_090cd5dc:
          if (gBattleMons[partner].hp != 0) goto LAB_090cd5ec;
        }
      }
      if (data->defItemEffect != 0x1c) goto LAB_090cae7e;
      uVar20 = 6;
LAB_090cb898:
      DecreaseViability(viabilityPtr,uVar20);
      goto LAB_090cae7e;
    }
    break;
  case 165: /* EFFECT_FLATTER */
sw_c9a8c_165:
    if (bankDef_ == partner) {
      moveFlags = data->defAbility;
      goto joined_r0x090cd626;
    }
sw_c9a8c_48:
    iVar16 = CanBeConfused(bankDef_,bankAtk_);
    if (((iVar16 == 0) || (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 != 0)) ||
       (iVar16 = PartnerMoveEffectIsStatusSameTarget(data,move,bankDef_), iVar16 != 0)) break;
    if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
        (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
         (gBattleMons[partner].hp == 0)))) || (gChosenMovesByBanks[partner] == 0))
    goto sw_c9a8c_82;
    iVar16 = sub_908ddb4(partnerMove);
    goto joined_r0x090cd65e;
  case 166: /* EFFECT_WILL_O_WISP */
  case 1:
sw_c9a8c_166:
    iVar16 = CanBeBurned(bankDef_,1);
    if ((iVar16 != 0) && (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 == 0)) {
      iVar16 = PartnerMoveEffectIsStatusSameTarget(data,move,bankDef_);
      goto joined_r0x090cd65e;
    }
    break;
  case 167: /* EFFECT_MEMENTO */
sw_c9a8c_167:
    moveTarget = ViableMonCountFromBankLoadPartyRange(bankAtk_);
    if ((1 < moveTarget) &&
       (((-1 < (int)(gBattleTypeFlags << 0x1f) ||
         (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
          (gBattleMons[partner].hp == 0)))) ||
        (((gBattleMoves[(int)partnerMove].effect != 0xa8 /* EFFECT_MEMENTO */ || (gChosenMovesByBanks[partner] == 0)) ||
         (gBattleStruct->moveTarget[partner] != bankDef_)))))) {
      if (0x1d5 < move) {
        if (move < 0x1d8) {
          iVar16 = sub_90dd758(bankAtk_);
          goto joined_r0x090cd65e;
        }
        if (move == 0x1ef /* Final Gambit */) goto sw_c9ecc_1;
      }
      iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_);
      if ((iVar16 == 0) &&
         ((0 < gBattleMons[bankDef_].statStages[0] || (0 < gBattleMons[bankDef_].statStages[3]))))
      goto LAB_090cae7e;
    }
    break;
  case 169: /* EFFECT_FOCUS_PUNCH */
sw_c9a8c_169:
    if (move != 0x245 /* Beak Blast */) {
      if (move == 0x260 /* Shell Trap */) {
        moveTarget = CheckContact(predictedMove,bankDef_);
        goto joined_r0x090cf8da;
      }
      if (((predictedMove != 0 /* - */) &&
          (iVar16 = MoveBlockedBySubstitute(predictedMove,bankDef_,bankAtk_), iVar16 == 0)) &&
         (gBattleMoves[predictedMove].split != 2)) {
        moveFlags = gBattleMoves[predictedMove].power;
        goto joined_r0x090cd7c6;
      }
    }
    goto sw_c9ecc_1;
  case 172: /* EFFECT_NATURE_POWER */
sw_c9a8c_172:
    predictedMove = sub_90a3700();
    goto LAB_090ca544;
  case 173: /* EFFECT_CHARGE */
sw_c9a8c_173:
    if (((int)(data->atkStatus3 << 0x16) < 0) ||
       ((1 < gBattleResources->ai->aiFlags &&
        ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect,data->atkAbility), iVar16 != 0 ||
         ((gDisableStructs[bankAtk_].field_0xe & 0xf) != 0)))))) break;
    bVar4 = DamagingMoveTypeInMoveset(bankAtk,0xd /* Electric */);
    if (bVar4 == 0) goto LAB_090cd824;
    goto sw_c9a8c_82;
  case 174: /* EFFECT_TAUNT */
sw_c9a8c_174:
    iVar16 = sub_90757f4(bankDef_);
    if ((iVar16 != 0) ||
       ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
         (((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)) &&
           ((gBattleMoves[(int)partnerMove].effect == 0xaf /* EFFECT_TAUNT */ && (gChosenMovesByBanks[partner] != 0)))) &&
          (gBattleStruct->moveTarget[partner] == bankDef_)))) ||
        ((iVar16 = GetBankAbility(bankDef_), iVar16 == 0xc ||
         (iVar16 = GetBankAbility(bankDef_), iVar16 == 0xc9)))))) break;
    goto sw_c9a8c_82;
  case 171: /* EFFECT_FOLLOW_ME */
  case 175: /* EFFECT_HELPING_HAND */
sw_c9a8c_171:
    if ((((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)))) &&
         ((gBattleMons[partner].hp != 0 &&
          ((gBattleMoves[(int)partnerMove].effect != moveEffect || (gChosenMovesByBanks[partner] == 0))))))
        && ((partnerMove == 0x0 /* - */ || (gBattleMoves[(int)partnerMove].split != 2)))) &&
       (gBattleStruct->monToSwitchIntoId[partner] == 6)) {
      iVar16 = sub_9073f4c(0,data->defAbility);
      goto joined_r0x090cd65e;
    }
    break;
  case 176: /* EFFECT_TRICK */
sw_c9a8c_176:
    if (move == 0x282 /* Bestow */) {
      if (data->atkItem != 0) {
        predictedMove = sub_90744d8(data->atkSpecies);
        goto joined_r0x090cf81c;
      }
    }
    else {
      iVar16._0_2_ = data->defItem;
      iVar16._2_2_ = data->atkItem;
      if ((((iVar16 != 0) && (iVar16 = sub_90744d8(data->atkSpecies,data->atkItem), iVar16 != 0)) &&
          (iVar16 = sub_90744d8(data->atkSpecies,data->defItem), iVar16 != 0)) &&
         (((iVar16 = sub_90744d8(data->defSpecies,data->atkItem), iVar16 != 0 &&
           (iVar16 = sub_90744d8(data->defSpecies,data->defItem), iVar16 != 0)) &&
          (data->defAbility != 0x3c /* Sticky Hold */)))) goto sw_c9a8c_82;
    }
    break;
  case 177: /* EFFECT_ROLE_PLAY */
sw_c9a8c_177:
    pbVar18 = (byte *)GetAbilityLocation(bankAtk_);
    data->atkAbility = *pbVar18;
    pbVar18 = (byte *)GetAbilityLocation(bankDef_);
    moveFlags = *pbVar18;
    data->defAbility = moveFlags;
    if (((moveFlags != data->atkAbility) && (moveFlags != 0)) &&
       (iVar16 = CheckTableForAbility(data->atkAbility,&UNK_09009f98), iVar16 == 0)) {
      iVar16 = CheckTableForAbility(data->defAbility,0x9009f84);
      goto joined_r0x090cd65e;
    }
    break;
  case 178: /* EFFECT_WISH */
sw_c9a8c_178:
    bVar4 = (&UNK_02023f40)[bankAtk_];
joined_r0x090cc7c4:
    if (bVar4 != 0) break;
    goto sw_c9a8c_82;
  case 179: /* EFFECT_ASSIST */
sw_c9a8c_179:
    iVar16 = LoadPartyRange(bankAtk_,&bStack_1c,&bStack_1b);
    for (bankDef_ = (uint)bStack_1c;
        (bankDef_ < bStack_1b &&
        (((iVar15 = iVar16 + bankDef_ * 100, *(short *)(iVar15 + 0x20) == 0 ||
          (iVar15 = /* GetBattlerSide or Random or VarGet */ stub(iVar15,0x2d,0,&GetMonData), iVar15 != 0)) ||
         (gBattlerPartyIndexes[bankDef_] == gBattlerPartyIndexes[bankAtk_]))));
        bankDef_ = bankDef_ + 1 & 0xff) {
    }
    if (bStack_1b == bankDef_) break;
    goto sw_c9a8c_82;
  case 180: /* EFFECT_INGRAIN */
sw_c9a8c_180:
    if (move == 0x27f /* Aqua Ring */) {
      iVar16 = data->atkStatus3 << 8;
    }
    else {
      iVar16 = data->atkStatus3 << 0x15;
    }
    goto joined_r0x090cddc0;
  case 182: /* EFFECT_MAGIC_COAT */
sw_c9a8c_182:
    bVar4 = MagicCoatableMovesInMoveset(bankDef);
joined_r0x090ce4be:
    if (bVar4 == 0) break;
    goto sw_c9a8c_82;
  case 183: /* EFFECT_RECYCLE */
sw_c9a8c_183:
    if (move == 0x281 /* Belch */) {
      moveTarget = *(uint *)(&gBitTable + (uint)gBattlerPartyIndexes[bankAtk_] * 4) &
               (uint)*(byte *)(gNewBS + 200);
      goto joined_r0x090cf8da;
    }
    if (*(short *)(gNewBS + (bankAtk_ + 0x7c) * 2 + 6) != 0) {
      predictedMove = data->atkItem;
      goto joined_r0x090cdb8e;
    }
    break;
  case 186: /* EFFECT_YAWN */
sw_c9a8c_186:
    if ((data->defStatus3 & 0x1800) == 0) {
      moveTarget = data->defStatus1 & 7;
      goto joined_r0x090cdbaa;
    }
    break;
  case 187: /* EFFECT_KNOCK_OFF */
sw_c9a8c_187:
    if ((data->defItemEffect == 0x46) ||
       ((((data->defItemEffect == 0x1d && (data->atkAbility != 0xd7 /* Gorilla Tactics */)) &&
         (gBattleStruct->choicedMove[bankDef_] != 0)) && (data->atkAbility != 0xff /* Sage Power */)))) {
      move = GetStrongestMove(bankDef,bankAtk);
      if (move != 0 /* - */) {
        move = GetStrongestMove(bankDef,bankAtk);
        bankAtk_ = AI_SpecialTypeCalc(move,bankDef_,bankAtk_);
        if ((bankAtk_ & 0x29) == 0) goto sw_c9a8c_82;
      }
      goto LAB_090cb104;
    }
    goto sw_c9a8c_82;
  case 190: /* EFFECT_SKILL_SWAP */
sw_c9a8c_190:
    pbVar18 = (byte *)GetAbilityLocation(bankAtk_);
    data->atkAbility = *pbVar18;
    pbVar18 = (byte *)GetAbilityLocation(bankDef_);
    moveFlags = *pbVar18;
    data->defAbility = moveFlags;
    if (move == 0x218 /* Entrainment */) {
      if ((((data->atkAbility != 0 /* ------- */) && (iVar16 = IsDynamaxed(bankDef_), iVar16 == 0)) &&
          (iVar16 = CheckTableForAbility(data->atkAbility,0x9009fd5), iVar16 == 0)) &&
         ((iVar16 = CheckTableForAbility(data->defAbility,0x9009fe2), iVar16 == 0 &&
          (iVar16 = MoveBlockedBySubstitute(0x218,bankAtk_,bankDef_), iVar16 == 0)))) goto LAB_090cae7e;
    }
    else if (move < 0x219) {
      if (move == 0x1db /* Worry Seed */) {
        if ((moveFlags != 0xf) && (iVar16 = CheckTableForAbility(moveFlags,0x9009fb7), iVar16 == 0)) {
          iVar16 = MoveBlockedBySubstitute(0x1db,bankAtk_,bankDef_);
          goto joined_r0x090cd65e;
        }
      }
      else {
        if (move != 0x1dc /* Gastro Acid */) goto LAB_090cdc7c;
        iVar16 = IsAbilitySuppressed(bankDef_);
        if ((iVar16 == 0) &&
           (iVar16 = CheckTableForAbility(data->defAbility,0x9009fc5), iVar16 == 0)) {
          iVar16 = MoveBlockedBySubstitute(0x1dc,bankAtk_,bankDef_);
          goto joined_r0x090cd65e;
        }
      }
    }
    else {
      if (move == 0x232 /* Core Enforce */) goto sw_c9ecc_1;
      if (move == 0x28f /* Simple Beam */) {
        if ((moveFlags != 0x8c) && (iVar16 = CheckTableForAbility(moveFlags,0x9009fe2), iVar16 == 0)) {
          iVar16 = MoveBlockedBySubstitute(0x28f,bankAtk_,bankDef_);
          goto joined_r0x090cd65e;
        }
      }
      else {
LAB_090cdc7c:
        if ((((data->atkAbility != 0 /* ------- */) && (moveFlags != 0)) &&
            (iVar16 = IsDynamaxed(bankAtk_), iVar16 == 0)) &&
           ((iVar16 = IsDynamaxed(bankDef_), iVar16 == 0 &&
            (iVar16 = CheckTableForAbility(data->atkAbility,0x9009fa4), iVar16 == 0)))) {
          iVar16 = CheckTableForAbility(data->defAbility,0x9009fa4);
          goto joined_r0x090cd65e;
        }
      }
    }
    break;
  case 191: /* EFFECT_IMPRISON */
sw_c9a8c_191:
    iVar16 = data->atkStatus3 << 0x12;
joined_r0x090cddc0:
    if (iVar16 < 0) break;
    goto sw_c9a8c_82;
  case 192: /* EFFECT_REFRESH */
sw_c9a8c_192:
    moveTarget = data->atkStatus1;
    if ((moveTarget & 0xf8) != 0) {
      if (move != 0x20d /* Psycho Shift */) goto sw_c9a8c_82;
      if ((moveTarget & 0x88) != 0) goto sw_ceae8_0;
      if ((int)(moveTarget << 0x1b) < 0) goto sw_c9a8c_166;
      if ((int)(moveTarget << 0x19) < 0) goto sw_c9a8c_66;
      if ((moveTarget & 7) == 0) break;
      goto LAB_090cdbb0;
    }
    break;
  case 194: /* EFFECT_SNATCH */
sw_c9a8c_194:
    bVar4 = HasSnatchableMove(bankDef);
    if (bVar4 == 0) break;
    if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
        (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)))) && (gBattleMoves[(int)partnerMove].effect == 0xc3 /* EFFECT_SNATCH */)) {
      predictedMove = gChosenMovesByBanks[partner];
      goto joined_r0x090cdb8e;
    }
    goto sw_c9a8c_82;
  case 200: /* EFFECT_MUD_SPORT */
sw_c9a8c_200:
    iVar16 = sub_9075290();
    if (iVar16 != 0) break;
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)) && (gBattleMoves[(int)partnerMove].effect == 0xc9 /* EFFECT_MUD_SPORT */)))) {
      predictedMove = gChosenMovesByBanks[partner];
      goto joined_r0x090cdb8e;
    }
    goto sw_c9a8c_82;
  case 204: /* EFFECT_TICKLE */
sw_c9a8c_204:
    if ((data->defAbility != 0xbf /* Contrary */) &&
       (((gBattleMons[bankDef_].statStages[0] != 0 &&
         (bVar4 = PhysicalMoveInMoveset(bankDef), bVar4 != 0)) ||
        (gBattleMons[bankDef_].statStages[1] != 0)))) goto LAB_090cae7e;
    break;
  case 205: /* EFFECT_COSMIC_POWER */
sw_c9a8c_205:
    if ((data->atkAbility == 0xbf /* Contrary */) ||
       ((1 < gBattleResources->ai->aiFlags &&
        ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect), iVar16 != 0 ||
         ((gDisableStructs[bankAtk_].field_0xe & 0xf) != 0)))))) break;
    if (move == 0x28b /* Magnet Flux */) {
      if (bankDef_ == partner) goto sw_c9a8c_82;
      iVar16 = sub_905fafe(data->atkAbility);
      if (iVar16 == 0) break;
    }
LAB_090cdfe0:
    if (0xb < gBattleMons[bankAtk_].statStages[1]) {
      sVar2 = gBattleMons[bankAtk_].statStages[4];
      goto joined_r0x090ce202;
    }
    goto sw_c9a8c_82;
  case 206: /* EFFECT_EXTREME_EVOBOOST */
sw_c9a8c_206:
    iVar16 = sub_9073e20(bankAtk_);
    if (iVar16 == 0) {
      if (move == 0x2aa /* No Retreat */) {
        bankAtk_ = *(uint *)(&gBitTable + (uint)UNK_02023d6b * 4) & (uint)*(byte *)(gNewBS + 0xbe);
        goto joined_r0x090cf272;
      }
      if ((move != 0x2b3 /* Clang Soul */) ||
         (bankAtk_ = (uint)UNK_02023d6b, predictedMove = __udivsi3(gBattleMons[bankAtk_].maxHP,3),
         predictedMove < gBattleMons[bankAtk_].hp)) goto sw_c9a8c_82;
    }
    break;
  case 207: /* EFFECT_BULK_UP */
sw_c9a8c_207:
    if ((data->atkAbility == 0xbf /* Contrary */) ||
       ((1 < gBattleResources->ai->aiFlags &&
        ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect), iVar16 != 0 ||
         ((gDisableStructs[bankAtk_].field_0xe & 0xf) != 0)))))) break;
    if (move == 0x19b /* Coil */) {
      if (((0xb < gBattleMons[bankAtk_].statStages[5]) && (0xb < gBattleMons[bankAtk_].statStages[0]))
         && (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 == 0)) {
        sVar2 = gBattleMons[bankAtk_].statStages[1];
        goto joined_r0x090ce202;
      }
    }
    else if ((0xb < gBattleMons[bankAtk_].statStages[0]) &&
            (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 == 0)) {
      sVar2 = gBattleMons[bankAtk_].statStages[1];
joined_r0x090ce202:
      if (0xb < sVar2) break;
    }
    goto sw_c9a8c_82;
  case 209: /* EFFECT_WATER_SPORT */
sw_c9a8c_209:
    iVar16 = sub_90752bc();
    if (iVar16 != 0) break;
    if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
       ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
         (gBattleMons[partner].hp != 0)) && (gBattleMoves[(int)partnerMove].effect == 0xd2 /* EFFECT_WATER_SPORT */)))) {
      predictedMove = gChosenMovesByBanks[partner];
      goto joined_r0x090cdb8e;
    }
    goto sw_c9a8c_82;
  case 210: /* EFFECT_CALM_MIND */
sw_c9a8c_210:
    if ((data->atkAbility != 0xbf /* Contrary */) &&
       ((gBattleResources->ai->aiFlags < 2 ||
        ((iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect), iVar16 == 0 &&
         ((gDisableStructs[bankAtk_].field_0xe & 0xf) == 0)))))) {
      if (move == 0x19f /* Quiver Dance */) {
        if ((data->defAbility != 0xe8 /* Dancer */) &&
           ((gBattleMons[bankAtk_].statStages[2] < 0xc ||
            (((gBattleMons[bankAtk_].statStages[3] < 0xc &&
              (bVar4 = SpecialMoveInMoveset(bankAtk), bVar4 != 0)) ||
             (gBattleMons[bankAtk_].statStages[4] < 0xc)))))) {
          iVar16 = IsTrickRoomActive();
          goto joined_r0x090cd65e;
        }
      }
      else {
        if (move != 0x1dd /* Geomancy */) {
          if ((0xb < gBattleMons[bankAtk_].statStages[3]) ||
             (bVar4 = SpecialMoveInMoveset(bankAtk), bVar4 == 0)) {
            sVar2 = gBattleMons[bankAtk_].statStages[4];
            goto joined_r0x090ce202;
          }
          goto sw_c9a8c_82;
        }
        if (((gBattleMons[bankAtk_].statStages[2] < 0xc) ||
            ((gBattleMons[bankAtk_].statStages[3] < 0xc &&
             (bVar4 = SpecialMoveInMoveset(bankAtk), bVar4 != 0)))) ||
           (gBattleMons[bankAtk_].statStages[4] < 0xc)) {
          bankAtk_ = IsTrickRoomActive();
          goto joined_r0x090cf272;
        }
      }
    }
    break;
  case 211: /* EFFECT_DRAGON_DANCE */
sw_c9a8c_211:
    if (data->atkAbility != 0xbf /* Contrary */) {
      if (gBattleResources->ai->aiFlags < 2) {
        if (move == 0x1c4 /* Shell Smash */) {
LAB_090ce332:
          if (data->atkAbility == 0xbf /* Contrary */) goto LAB_090cdfe0;
          if ((((gBattleMons[bankAtk_].statStages[3] < 0xc) &&
               (bVar4 = SpecialMoveInMoveset(bankAtk), bVar4 != 0)) ||
              ((gBattleMons[bankAtk_].statStages[0] < 0xc &&
               (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 != 0)))) ||
             (gBattleMons[bankAtk_].statStages[2] < 0xc)) {
            iVar16 = IsTrickRoomActive();
            goto joined_r0x090cd65e;
          }
        }
        else {
LAB_090ce3a2:
          if ((((gBattleMons[bankAtk_].statStages[0] < 0xc) &&
               (bVar4 = PhysicalMoveInMoveset(bankAtk), bVar4 != 0)) ||
              (gBattleMons[bankAtk_].statStages[2] < 0xc)) &&
             ((move != 0x15d /* Dragon Dance */ || (data->defAbility != 0xe8 /* Dancer */)))) {
            iVar16 = IsTrickRoomActive();
            goto joined_r0x090cd65e;
          }
        }
      }
      else {
        iVar16 = IsChoiceItemEffectOrAbility(data->atkItemEffect);
        if ((iVar16 == 0) && ((gDisableStructs[bankAtk_].field_0xe & 0xf) == 0)) {
          if (move == 0x1c4 /* Shell Smash */) goto LAB_090ce332;
          if (data->atkAbility != 0xbf /* Contrary */) goto LAB_090ce3a2;
        }
      }
    }
    break;
  case 212: /* EFFECT_STAT_SWAP_SPLIT */
sw_c9a8c_212:
    if (bankDef_ != partner) {
      if (move == 0x21d /* Heart Swap */) {
        uVar3 = CountBanksPositiveStatStages(bankAtk);
        uVar7 = CountBanksNegativeStatStages(bankAtk);
        uVar5 = CountBanksPositiveStatStages(bankDef);
        uVar6 = CountBanksNegativeStatStages(bankDef);
        if ((uVar3 < uVar5) || (uVar6 < uVar7)) goto LAB_090cae7e;
      }
      else if (move < 0x21e) {
        if (move != 0x20b /* Power Swap */) {
          if (move == 0x20c /* Power Trick */) {
            if (gBattleMons[bankAtk_].attack <= gBattleMons[bankAtk_].defense) {
              bVar4 = PhysicalMoveInMoveset(bankAtk);
              goto joined_r0x090ce4be;
            }
          }
          else if (move == 0x207 /* Guard Swap */) {
            if ((gBattleMons[bankAtk_].statStages[1] < gBattleMons[bankDef_].statStages[4]) ||
               (gBattleMons[bankAtk_].statStages[4] < gBattleMons[bankDef_].statStages[4]))
            goto LAB_090cae7e;
            break;
          }
          goto sw_c9a8c_82;
        }
        if ((gBattleMons[bankAtk_].statStages[0] < gBattleMons[bankDef_].statStages[3]) ||
           (gBattleMons[bankAtk_].statStages[3] < gBattleMons[bankDef_].statStages[3]))
        goto LAB_090cae7e;
      }
      else if (move == 0x286 /* Guard Split */) {
        if ((uint)(byte)gBattleMons[bankAtk_].defense + (uint)(byte)gBattleMons[bankAtk_].spDefense <
            (uint)(byte)gBattleMons[bankDef_].defense + (uint)(byte)gBattleMons[bankDef_].spDefense)
        goto LAB_090cae7e;
      }
      else if (move == 0x28d /* Power Split */) {
        if ((uint)(byte)gBattleMons[bankAtk_].attack + (uint)(byte)gBattleMons[bankAtk_].spAttack <
            (uint)(byte)gBattleMons[bankDef_].attack + (uint)(byte)gBattleMons[bankDef_].spAttack)
        goto LAB_090cae7e;
      }
      else {
        if (move != 0x266 /* Speed Swap */) goto sw_c9a8c_82;
        iVar16 = IsTrickRoomActive();
        if (iVar16 == 0) {
          if (gBattleMons[bankAtk_].speed < gBattleMons[bankDef_].speed) goto LAB_090cae7e;
        }
        else if (gBattleMons[bankDef_].speed < gBattleMons[bankAtk_].speed)
        goto sw_c9a8c_82;
      }
      break;
    }
    goto sw_c9a8c_82;
  case 217: /* EFFECT_ME_FIRST */
sw_c9a8c_217:
    if ((move == 0x20a /* Me First */) &&
       ((predictedMove != 0 /* - */ && (bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef), bVar4 != 0)
        ))) goto LAB_090ca544;
    break;
  case 219: /* EFFECT_NATURAL_GIFT */
sw_c9a8c_219:
    iVar16 = sub_9074cc4();
    if ((iVar16 != 0) || (iVar16 = GetPocketByItemId(data->atkItem), iVar16 != 5)) break;
    goto sw_c9a8c_82;
  case 225: /* EFFECT_SET_TERRAIN */
sw_c9a8c_225:
    if (((((int)(gBattleTypeFlags << 0x1f) < 0) &&
         (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
          (gBattleMons[partner].hp != 0)))) &&
        ((gChosenMovesByBanks[partner] != 0 &&
         ((gBattleMoves[(int)partnerMove].effect == 0xe2 /* EFFECT_SET_TERRAIN */ || (iVar16 = sub_908dd40(partnerMove), iVar16 != 0)
          ))))) || (((int)(gBattleTypeFlags << 5) < 0 && ((_UNK_0203e044 & 0xf) != 0)))) break;
    puVar19 = (undefined1 *)((int)&move[-8].status1 + 3);
    if (puVar19 < (undefined1 *)0x4) {
                          switch((uint)puVar19) {
      case 0:
        if (gTerrainType == '\x01') goto LAB_090ca2dc;
        break;
      case 1:
        if (gTerrainType == '\x02') goto LAB_090ca2dc;
        break;
      case 2:
        if (gTerrainType == '\x03') goto LAB_090ca2dc;
        break;
      case 3:
        if (gTerrainType == '\x04') goto LAB_090ca2dc;
      }
    }
    goto sw_c9a8c_82;
  case 226: /* EFFECT_PLEDGE */
sw_c9a8c_226:
    if ((((((int)(gBattleTypeFlags << 0x1f) < 0) &&
          ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)) &&
           ((gBattleMons[partner].hp != 0 && (partnerMove != 0x0 /* - */)))))) &&
         (gBattleMoves[(int)partnerMove].effect == 0xe3 /* EFFECT_PLEDGE */)) &&
        ((move != partnerMove && ((gBattleMons[partner].status1 & 7) != 0)))) &&
       (gBattleMons[partner].status1 != 1)) goto LAB_090cba70;
    goto sw_c9ecc_1;
  case 227: /* EFFECT_FIELD_EFFECTS */
sw_c9a8c_227:
    if (move == 0x27a /* Wonder Room */) {
      iVar16 = sub_9075096();
      if ((iVar16 != 0) ||
         ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)))) &&
          ((gChosenMovesByBanks[partner] != 0 && (partnerMove == 0x27a /* Wonder Room */)))))) break;
    }
    else if (move < 0x27b) {
      if (move == 0x278 /* Trick Room */) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)) &&
            ((gChosenMovesByBanks[partner] != 0 &&
             ((partnerMove == 0x1d8 /* Tailwind */ || (partnerMove == 0x278 /* Trick Room */)))))))) {
          DecreaseViability(viabilityPtr,10);
        }
        iVar16 = IsTrickRoomActive();
        if (iVar16 == 0) {
          move = GetPokemonOnSideSpeedAverage(bankAtk);
          uVar11 = GetPokemonOnSideSpeedAverage(bankDef);
          if (uVar11 < move) break;
        }
        else {
          move = GetPokemonOnSideSpeedAverage(bankAtk);
          uVar11 = GetPokemonOnSideSpeedAverage(bankDef);
          if (move < uVar11) break;
        }
      }
      else if ((move == 0x279 /* Magic Room */) &&
              ((iVar16 = sub_9074cc4(), iVar16 != 0 ||
               ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
                 (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
                  (gBattleMons[partner].hp != 0)))) &&
                ((gChosenMovesByBanks[partner] != 0 && (partnerMove == 0x279 /* Magic Room */))))))))
      break;
    }
    else if (move == 0x288 /* Ion Deluge */) {
      iVar16 = sub_9075238();
      if ((iVar16 != 0) ||
         (((int)(gBattleTypeFlags << 0x1f) < 0 &&
          ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)) &&
           ((gChosenMovesByBanks[partner] != 0 && (partnerMove == 0x288 /* Ion Deluge */)))))))) break;
    }
    else {
      if (move == 0x297 /* Plasma Fists */) goto sw_c9ecc_1;
      if (move == 0x285 /* Gravity */) {
        iVar16 = sub_90750c4();
        if (((iVar16 != 0) && (iVar16 = IsOfType(bankAtk_,2 /* Flying */), iVar16 == 0)) &&
           (data->atkItemEffect != 0x67)) break;
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          predictedMove = gBattleMons[data->foe1].hp;
          if (((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) && (gBattleMons[partner].hp == 0))
          {
            if (predictedMove != 0 /* - */) {
LAB_090ce89c:
              if (gBattleMons[data->foe2].hp == 0) goto LAB_090ce8b0;
LAB_090ce8c2:
              if (gChosenMovesByBanks[partner] != 0) {
                bankAtk_ = IsMaxMoveWithEffect(partnerMove,0x24);
                goto joined_r0x090cf272;
              }
            }
          }
          else {
            if ((gChosenMovesByBanks[partner] != 0) && (partnerMove == 0x285 /* Gravity */)) break;
            if (predictedMove != 0 /* - */) goto LAB_090ce89c;
LAB_090ce8b0:
            if (gBattleMons[partner].hp != 0) goto LAB_090ce8c2;
          }
        }
      }
    }
    goto sw_c9a8c_82;
  case 228: /* EFFECT_FLING */
sw_c9a8c_228:
    iVar16 = sub_9074cf0(data->atkItem,data->atkSpecies,data->atkAbility,bankAtk_,
                         *(undefined1 *)(gNewBS + bankAtk_ + 0x3d));
    if (iVar16 == 0) {
      DecreaseViability(viabilityPtr,10);
    }
    if ((byte)(&UNK_09157a29)[(uint)data->atkItem * 2] - 2 < 5) {
                          switch((byte)(&UNK_09157a29)[(uint)data->atkItem * 2] - 2) {
      case 0:
      case 4:
        goto sw_ceae8_0;
      case 66: /* EFFECT_PARALYZE */
      case 3:
        goto sw_c9a8c_66;
      case 166: /* EFFECT_WILL_O_WISP */
      case 1:
        goto sw_c9a8c_166;
      case 2:
        iVar16 = CanBeFrozen(bankDef_,1);
        if ((iVar16 == 0) || (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 != 0))
        goto LAB_090cba70;
      }
    }
    goto sw_c9ecc_1;
  case 230: /* EFFECT_ATTACK_BLOCKERS */
sw_c9a8c_230:
    if (move == 0x28c /* Powder */) {
      bVar4 = MoveTypeInMoveset(bankDef,10);
      if (bVar4 != 0) {
        if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
            (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)))) ||
           ((partnerMove != 0x28c /* Powder */ || (gChosenMovesByBanks[partner] == 0))))
        goto LAB_090cae7e;
        moveFlags = gBattleStruct->moveTarget[partner];
        goto joined_r0x090cecf6;
      }
    }
    else if (move < 0x28d) {
      if (move == 0x26d /* Throat Chop */) goto sw_c9ecc_1;
LAB_090ceb46:
      iVar16 = sub_90754f0(bankDef_);
      if (iVar16 == 0) {
        if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
            (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)))) ||
           ((move != partnerMove || (gChosenMovesByBanks[partner] == 0)))) goto LAB_090cae7e;
        moveFlags = gBattleStruct->moveTarget[partner];
joined_r0x090cf0ea:
        if (moveFlags != bankDef_) goto LAB_090cae7e;
      }
    }
    else if (move == 0x291 /* Telekinesis */) {
      if ((((data->defStatus3 & 0x20400400) == 0) && (iVar16 = sub_90750c4(), iVar16 == 0)) &&
         ((data->defItemEffect != 0x62 &&
          (iVar16 = sub_90c1a54(data->defSpecies,&UNK_09161f6a), iVar16 == 0)))) {
        if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
           ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)) ||
            ((partnerMove != 0x291 /* Telekinesis */ || (gChosenMovesByBanks[partner] == 0))))))
        goto LAB_090cae7e;
        moveFlags = gBattleStruct->moveTarget[partner];
        goto joined_r0x090cf0ea;
      }
    }
    else {
      if (move != 0x299 /* Embargo */) goto LAB_090ceb46;
      iVar16 = sub_9074cc4();
      if ((iVar16 == 0) && (*(char *)(gNewBS + bankDef_ + 0x3d) == '\0')) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)) &&
            ((partnerMove == 0x299 /* Embargo */ && (gChosenMovesByBanks[partner] != 0)))))) {
          moveFlags = gBattleStruct->moveTarget[partner];
          goto joined_r0x090cf0ea;
        }
        goto LAB_090cae7e;
      }
    }
    break;
  case 231: /* EFFECT_TYPE_CHANGES */
sw_c9a8c_231:
    if (move == 0x292 /* TrickoTreat */) {
      if (((gBattleMons[bankDef_].type1 != 7) && (gBattleMons[bankDef_].type2 != 7)) &&
         (gBattleMons[bankDef_].type3 != 7)) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)) &&
            ((partnerMove == 0x292 /* TrickoTreat */ && (gChosenMovesByBanks[partner] != 0)))))) {
          moveFlags = gBattleStruct->moveTarget[partner];
          goto joined_r0x090cf0ea;
        }
        goto LAB_090cae7e;
      }
    }
    else if (move == 0x294 /* Woods Curse */) {
      if (((gBattleMons[bankDef_].type1 != 0xc) && (gBattleMons[bankDef_].type2 != 0xc)) &&
         (gBattleMons[bankDef_].type3 != 0xc)) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)) &&
            ((partnerMove == 0x294 /* Woods Curse */ && (gChosenMovesByBanks[partner] != 0)))))) {
          moveFlags = gBattleStruct->moveTarget[partner];
          goto joined_r0x090cf0ea;
        }
        goto LAB_090cae7e;
      }
    }
    else {
      if (move != 0x290 /* Soak */) goto sw_c9a8c_82;
      if (((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
          (((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
             (gBattleMons[partner].hp == 0)) ||
            ((partnerMove != 0x290 /* Soak */ || (gChosenMovesByBanks[partner] == 0)))) ||
           (gBattleStruct->moveTarget[partner] != bankDef_)))) &&
         (((gBattleMons[bankDef_].type1 != 0xb || (gBattleMons[bankDef_].type2 != 0xb)) ||
          (gBattleMons[bankDef_].type3 != 0x14)))) goto LAB_090cae7e;
    }
    break;
  case 232: /* EFFECT_HEAL_TARGET */
sw_c9a8c_232:
    if (move != 0x259 /* Pollen Puff */) {
      if (bankDef_ == partner) goto LAB_090cefe0;
      break;
    }
    if (bankDef_ == partner) {
LAB_090cefe0:
      if (gBattleMons[bankDef_].hp == gBattleMons[bankDef_].maxHP) {
        DecreaseViability(viabilityPtr,10);
      }
      if (gBattleMons[bankDef_].maxHP >> 1 < gBattleMons[bankDef_].hp) goto LAB_090cb79a;
      goto LAB_090cae7e;
    }
    if (moveSplit == 2) goto sw_c9a8c_82;
    goto LAB_090cb2dc;
  case 233: /* EFFECT_TOPSY_TURVY_ELECTRIFY */
sw_c9a8c_233:
    if (move == 0x298 /* Electrify */) {
      bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef);
      if ((bVar4 != 0) && (iVar16 = GetMoveTypeSpecial(bankDef_,predictedMove), iVar16 != 0xd)) {
        if ((((int)(gBattleTypeFlags << 0x1f) < 0) &&
            (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)))) &&
           ((partnerMove == 0x298 /* Electrify */ && (gChosenMovesByBanks[partner] != 0)))) {
          moveFlags = gBattleStruct->moveTarget[partner];
          goto joined_r0x090cf0ea;
        }
        goto LAB_090cae7e;
      }
      break;
    }
    if (bankDef_ != partner) {
      uVar3 = CountBanksPositiveStatStages(bankDef);
      uVar7 = CountBanksNegativeStatStages(bankDef);
      if ((uVar3 == 0) ||
         ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
           (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
            (gBattleMons[partner].hp != 0)))) &&
          (((move == partnerMove && (gChosenMovesByBanks[partner] != 0)) &&
           (gBattleStruct->moveTarget[partner] == bankDef_)))))) break;
      if (uVar3 <= uVar7) goto sw_c9a8c_82;
      goto LAB_090cb79a;
    }
    goto sw_c9a8c_82;
  case 234: /* EFFECT_FAIRY_LOCK_HAPPY_HOUR */
sw_c9a8c_234:
    if (move[-8].pp + 2 < (byte *)0xc) {
                          switch((uint)(move[-8].pp + 2)) {
      case 0:
        iVar16 = sub_9075264();
        if ((iVar16 != 0) ||
           ((((int)(gBattleTypeFlags << 0x1f) < 0 &&
             (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[partner].hp != 0)))) &&
            ((gChosenMovesByBanks[partner] != 0 && (partnerMove == 0x29a /* Fairy Lock */))))))
        goto LAB_090ca2dc;
        break;
      case 6:
        if ((((gBattleTypeFlags & 0x608090a) != 8) ||
            (iVar16 = GetBattlerSide(bankAtk_,uVar20,0x608090a,&GetBattlerSide), iVar16 != 0)) ||
           ((int)((uint)*(byte *)(gNewBS + 0xe7) << 0x1a) < 0)) {
          iVar16 = IsTypeZCrystal(data->atkItem,moveType);
          if ((iVar16 != 0) && (*(char *)(gNewBS + bankAtk_ + 0x194) == '\0')) {
            bankAtk_ = IsMegaZMoveBannedBattle();
            goto joined_r0x090cf272;
          }
          goto LAB_090ca2dc;
        }
        break;
      case 10:
      case 11:
        iVar16 = IsTypeZCrystal(data->atkItem,moveType);
        if ((iVar16 != 0) && (data->atkItemQuality == moveType)) {
          bVar4 = *(bool8 *)(gNewBS + bankAtk_ + 0x194);
          goto joined_r0x090cc7c4;
        }
        goto LAB_090ca2dc;
      }
    }
    goto sw_c9a8c_82;
  case 235: /* EFFECT_INSTRUCT_AFTER_YOU_QUASH */
sw_c9a8c_235:
    if (move == 0x29e /* Instruct */) {
      bVar4 = MoveWouldHitFirst(0x29e,bankAtk_00,(ushort)bankDef);
      if (bVar4 != 0) {
        predictedMove = (uint)*(ushort *)(&gLastPrintedMoves + bankDef_ * 2);
      }
      if (((((predictedMove != 0 /* - */) && (iVar16 = IsDynamaxed(bankDef_), iVar16 == 0)) &&
           (iVar16 = CheckTableForMove(predictedMove,&UNK_0903f9ba), iVar16 == 0)) &&
          ((iVar16 = CheckTableForMove(predictedMove,&UNK_0904010e), iVar16 == 0 &&
           (iVar16 = CheckTableForMove(predictedMove,&UNK_090400fe), iVar16 == 0)))) &&
         ((iVar16 = sub_90748d2(predictedMove), iVar16 == 0 &&
          ((0xfffd < (ushort)(gLockedMoves[bankDef_] - 1) &&
           (-1 < (int)(gBattleMons[bankDef_].status2 << 0x13))))))) {
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          predictedMove = gBattleMons[data->foe1].hp;
          if ((predictedMove == 0 /* - */) || (gBattleMons[data->foe2].hp == 0)) {
            if (gBattleMons[partner].hp == 0) {
              if (predictedMove == 0 /* - */) goto LAB_090cfdc6;
            }
            else {
              if (partnerMove == 0x29e /* Instruct */) goto LAB_090cf4dc;
              if (predictedMove == 0 /* - */) goto joined_r0x090cf52c;
            }
LAB_090cf4fe:
            if (gBattleMons[data->foe2].hp != 0) goto joined_r0x090cf52c;
          }
          else {
            if (partnerMove != 0x29e /* Instruct */) goto LAB_090cf4fe;
LAB_090cf4dc:
            if ((gChosenMovesByBanks[partner] != 0) && (gBattleStruct->moveTarget[partner] == bankDef_))
            break;
            if (predictedMove != 0 /* - */) goto LAB_090cf4fe;
          }
          if (gBattleMons[partner].hp != 0) goto joined_r0x090cf52c;
        }
LAB_090cfdc6:
        if ((gBattleMoves[predictedMove].target & 0x6d) == 0) {
          if (predictedMove != 0x295 /* Mind Blown */) {
LAB_090cb79a:
            DecreaseViability(viabilityPtr,5);
          }
        }
        else if (predictedMove != 0x295 /* Mind Blown */) {
          if (predictedMove == 0x2c8 /* Steel Beam */) goto LAB_090cb79a;
          break;
        }
        goto sw_c9a8c_82;
      }
    }
    else if (move == 0x29f /* Quash */) {
      if ((((gBattleTypeFlags & 1) != 0) &&
          (((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)))) &&
         (bVar4 = MoveWouldHitFirst(0x29f,bankAtk_00,(ushort)bankDef), bVar4 != 0)) {
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
             (gBattleMons[partner].hp != 0)) &&
            ((partnerMove == 0x29f /* Quash */ && (gChosenMovesByBanks[partner] != 0)))))) {
          moveFlags = gBattleStruct->moveTarget[partner];
          goto joined_r0x090cf3b6;
        }
        goto sw_c9a8c_82;
      }
    }
    else if (((bankDef_ == partner) && ((gBattleTypeFlags & 1) != 0)) &&
            ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
              (gBattleMons[partner].hp != 0)) &&
             (bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef), bVar4 != 0)))) {
      if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
         ((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
           (gBattleMons[partner].hp != 0)) &&
          ((move == partnerMove && (gChosenMovesByBanks[partner] != 0)))))) {
        moveFlags = gBattleStruct->moveTarget[partner];
joined_r0x090cf3b6:
        if (moveFlags == bankDef_) break;
      }
      goto sw_c9a8c_82;
    }
    break;
  case 236: /* EFFECT_SUCKER_PUNCH */
sw_c9a8c_236:
    if (predictedMove == 0 /* - */) {
      iVar16 = Random();
      if ((-1 < iVar16 << 0x1f) ||
         (bVar4 = IsSuckerPunchOkayToUseThisRound(move,bankAtk,bankDef), bVar4 == 0))
      goto LAB_090cb830;
    }
    else if ((gBattleMoves[predictedMove].split == 2) ||
            (bVar4 = MoveWouldHitFirst(move,bankAtk_00,(ushort)bankDef), bVar4 == 0))
    goto LAB_090cb104;
    goto sw_c9ecc_1;
  case 238: /* EFFECT_TEAM_EFFECTS */
sw_c9a8c_238:
    bankDef_ = gNewBS;
    if (move == 0x289 /* Lucky Chant */) {
      iVar16 = GetBattlerSide(bankAtk_,uVar20,0x289,&GetBattlerSide);
      if ((*(char *)(bankDef_ + iVar16 + 0x11) == '\0') &&
         ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
          ((((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
            (gBattleMons[partner].hp == 0)) ||
           ((gChosenMovesByBanks[partner] == 0 || (partnerMove != 0x289 /* Lucky Chant */))))))))
      goto sw_c9a8c_82;
    }
    else if (move == 0x28a /* Magnet Rise */) {
      iVar16 = sub_90750c4();
      if ((((iVar16 == 0) && (*(char *)(gNewBS + bankAtk_ + 0x2d) == '\0')) &&
          (data->atkItemEffect != 0x62)) && ((data->atkStatus3 & 0x600400) == 0)) {
        predictedMove = CheckGrounding(bankAtk_);
        goto joined_r0x090cf81c;
      }
    }
    else {
      if ((move != 0x1d8 /* Tailwind */) ||
         ((iVar16 = GetBattlerSide(bankAtk_,uVar20,0x1d8,&GetBattlerSide),
          *(char *)(bankDef_ + iVar16 + 0x13) == '\0' &&
          ((((-1 < (int)(gBattleTypeFlags << 0x1f) ||
             (((gBattleMons[data->foe1].hp == 0 || (gBattleMons[data->foe2].hp == 0)) &&
              (gBattleMons[partner].hp == 0)))) ||
            ((gChosenMovesByBanks[partner] == 0 ||
             ((partnerMove != 0x1d8 /* Tailwind */ && (partnerMove != 0x278 /* Trick Room */)))))) &&
           ((iVar16 = IsTrickRoomActive(), iVar16 == 0 || (*(char *)(gNewBS + 3) == '\x01'))))))))
      goto sw_c9a8c_82;
    }
    break;
  case 239: /* EFFECT_CAMOUFLAGE */
sw_c9a8c_239:
    uVar20 = sub_90a46c0();
    bankAtk_ = IsOfType(bankAtk_,uVar20);
joined_r0x090cf272:
    if (bankAtk_ != 0) break;
    goto sw_c9a8c_82;
  case 241: /* EFFECT_LAST_RESORT */
sw_c9a8c_241:
    if (move == 0x2a2 /* Last Resort */) {
      moveTarget = sub_906cad4();
      goto joined_r0x090cf8da;
    }
    bVar4 = WillFaintFromWeatherSoon(bankAtk);
    if (((bVar4 == 0) && (iVar16 = MoveBlockedBySubstitute(move,bankAtk_,bankDef_), iVar16 == 0)) &&
       (moveTarget = sub_9084288(data->defSpecies,data->defAbility,data->defItemEffect,bankDef_,1),
       moveTarget < 2000)) goto sw_c9ecc_1;
    break;
  case 253: /* ? */
sw_c9a8c_253:
    if (((data->defItemEffect != 0x72) &&
        (iVar16 = IsOfType(bankDef_,gBattleMons[bankAtk_].type1), iVar16 == 0)) &&
       (iVar16 = IsOfType(bankDef_,gBattleMons[bankAtk_].type2), iVar16 == 0)) {
      moveTarget = IsOfType(bankDef_,gBattleMons[bankAtk_].type3);
      goto joined_r0x090cf8da;
    }
sw_c9ecc_1:
    if (moveSplit != 2) {
sw_c9a8c_1:
      if (bankDef_ != partner) {
LAB_090cb2dc:
        bankAtk_ = AI_SpecialTypeCalc(move,bankAtk_,bankDef_);
        if ((bankAtk_ & 0x29) != 0) {
          DecreaseViability(viabilityPtr,0xf);
        }
      }
    }
    goto sw_c9a8c_82;
  case 184: /* EFFECT_BLANK_185 */
sw_c9a8c_184:
    iVar16 = sub_907659c(data->defItem,data->defAbility);
    if (iVar16 == 0) goto sw_c9ecc_1;
  }
LAB_090ca2dc:
  DecreaseViability(viabilityPtr,10);
sw_c9a8c_82:
  if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
     (((((gBattleMons[data->foe1].hp != 0 && (gBattleMons[data->foe2].hp != 0)) ||
        (gBattleMons[partner].hp != 0)) &&
       ((partnerMove != 0x0 /* - */ && (gBattleMoves[(int)partnerMove].effect == 0xb0 /* EFFECT_HELPING_HAND */)))) &&
      (moveSplit == 2)))) {
    DecreaseViability(viabilityPtr,10);
  }
  if ((short)viabilityPtr[0] < 0) {
LAB_090c9250:
    uVar3 = 0;
  }
  else {
    uVar3 = (u8)viabilityPtr[0];
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023e80) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
  return uVar3;
}

// ---- AIScript_Roaming  (ROM 0x90cfe04)
u8 AIScript_Roaming(u8 bankAtk,u8 bankDef,u16 move,u8 originalViability,AIScript *data)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = GetBankAbility(bankAtk,bankDef,move);
  iVar3 = GetBankItemEffect(bankAtk);
  if (((iVar2 == 0x32) || (iVar3 == 0x25)) || (iVar2 = IsOfType(bankAtk,7 /* Ghost */), iVar2 != 0)) {
    gBattleResources->ai->aiAction = gBattleResources->ai->aiAction | 0xb;
  }
  else {
    bVar1 = IsTrapped(bankAtk,0);
    if (bVar1 != 0) {
      return originalViability;
    }
  }
  gBattleResources->ai->aiAction = gBattleResources->ai->aiAction | 0xb;
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
  return originalViability;
}

// ---- AIScript_Safari  (ROM 0x90cfe5c)
u8 AIScript_Safari(u8 bankAtk,u8 bankDef,u16 move,u8 originalViability,AIScript *data)

{
  undefined4 uVar1;
  byte bVar2;
  uint extraout_r1;
  AI_ThinkingStruct *pAVar3;
  byte bVar4;
  
  bVar2 = gBattleStruct->safariEscapeFactor;
  uVar1 = Random(bankAtk,bankDef);
  __umodsi3(uVar1,100);
  pAVar3 = gBattleResources->ai;
  if ((extraout_r1 & 0xff) < (uint)bVar2 * 0x5000000 >> 0x18) {
    bVar4 = 0xb;
    bVar2 = pAVar3->aiAction;
  }
  else {
    bVar2 = pAVar3->aiAction;
    bVar4 = 0xd;
  }
  pAVar3->aiAction = bVar4 | bVar2;
  return originalViability;
}

// ---- AIScript_FirstBattle  (ROM 0x90cfeac)
u8 AIScript_FirstBattle(u8 bankAtk,u8 bankDef,u16 move,u8 originalViability,AIScript *data)

{
  uint uVar1;
  undefined4 uStack_14;
  uint uStack_10;
  
  uStack_14._0_2_ = (ushort)bankDef;
  uStack_14 = (uint)CONCAT12(originalViability,(ushort)uStack_14);
  uStack_10 = move;
  uVar1 = func_0x090dd734(bankDef);
  if (uVar1 < 0x14) {
    if (gBattleMoves[move].split != 2) {
      DecreaseViability((int)&uStack_14 + 2,0x14);
    }
  }
  if ((int)uStack_14 < 0) {
    uStack_14._2_1_ = 0;
  }
  return uStack_14._2_1_;
}

// ---- PartnerMoveEffectIsStatusSameTarget  (ROM 0x93507cc)
bool PartnerMoveEffectIsStatusSameTarget(int param_1,undefined4 param_2,uint param_3)

{
  byte bVar1;
  ushort move;
  u16 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if (-1 < gBattleTypeFlags << 0x1f) {
    return false;
  }
  uVar5 = (uint)*(byte *)(param_1 + 0x3e);
  if (((gBattleMons[*(byte *)(param_1 + 0x42)].hp == 0) ||
      (gBattleMons[*(byte *)(param_1 + 0x43)].hp == 0)) && (gBattleMons[uVar5].hp == 0)) {
    return false;
  }
  if (gChosenMovesByBanks[uVar5] == 0) {
    return false;
  }
  bVar1 = gBattleStruct->moveTarget[uVar5];
  if (bVar1 != param_3) {
    return false;
  }
  move = *(ushort *)(param_1 + 0x44);
  uVar4 = (uint)gBattleMoves[move].effect;
  if (uVar4 == 0x21) {
    return true;
  }
  if (uVar4 < 0x22) {
    if (uVar4 != 2) {
      if (uVar4 < 3) {
        if (uVar4 == 1) {
          return true;
        }
        goto LAB_09350856;
      }
      uVar4 = uVar4 - 4;
      if (2 < uVar4) goto LAB_09350856;
    }
  }
  else {
    if (uVar4 == 0xa7) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
      return true;
    }
    if (uVar4 < 0xa8) {
      if (uVar4 - 0x42 < 2) {
        return true;
      }
      goto LAB_09350856;
    }
    if (uVar4 == 0xbb) {
      return true;
    }
    if (uVar4 != 0xd1) goto LAB_09350856;
  }
  uVar2 = CalcSecondaryEffectChance(*(byte *)(param_1 + 0x3e),move,(u8)uVar4);
  if ((0x4a < uVar2) && (iVar3 = MoveBlockedBySubstitute(param_2,uVar5,(uint)bVar1), iVar3 == 0)) {
    return true;
  }
LAB_09350856:
  iVar3 = IsMaxMoveWithStatusEffect(move);
  return iVar3 != 0;
}
