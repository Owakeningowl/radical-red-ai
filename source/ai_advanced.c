// ai_advanced.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- BetterToKOLastFoeMon  (ROM 0x90c3b48)
bool BetterToKOLastFoeMon(u8 param_1,undefined4 param_2)

{
  bool8 bVar1;
  uint uVar2;
  
  bVar1 = CanKnockOut((u8)param_2,param_1);
  if ((bVar1 == 0) && (bVar1 = Can2HKO((u8)param_2,param_1), bVar1 == 0)) {
    return false;
  }
  uVar2 = ViableMonCountFromBank(param_2);
  return uVar2 < 2;
}

// ---- ShouldUseSubstitute  (ROM 0x90c3b7a)
bool8 ShouldUseSubstitute(u8 bankAtk,u8 bankDef)

{
  ushort uVar1;
  bool8 bVar2;
  move_t move;
  u32 uVar3;
  uint uVar4;
  
  move = IsValidMovePrediction(bankDef,bankAtk);
  bVar2 = IsBankIncapacitated(bankDef);
  if (bVar2 == 0) {
    if (move == 0 /* - */) {
      return 0;
    }
    bVar2 = MoveWouldHitFirst(0xa4,(ushort)bankAtk,(ushort)bankDef);
    if (bVar2 != 0) {
      uVar3 = GetFinalAIMoveDamage(move,bankDef,bankAtk,1,(void *)0x0);
      uVar4 = MathMax(1,gBattleMons[bankAtk].maxHP >> 2);
      return uVar3 < uVar4;
    }
    bVar2 = IsPredictedToSwitch(bankDef,bankAtk);
    if (bVar2 == 0) {
      uVar1 = gBattleMons[bankAtk].hp;
      uVar3 = GetFinalAIMoveDamage(move,bankDef,bankAtk,1,(void *)0x0);
      return (int)(uint)(gBattleMons[bankAtk].maxHP >> 2) < (int)(uVar1 - uVar3);
    }
  }
  return 1;
}

// ---- IsWorthSettingHazards  (ROM 0x90c3c20)
bool IsWorthSettingHazards(void)

{
  int iVar1;
  undefined4 uVar2;
  uint extraout_r1;
  bool bVar3;
  
  iVar1 = ViableMonCountFromBankLoadPartyRange();
  bVar3 = false;
  if (((iVar1 != 2) && (bVar3 = true, iVar1 == 3)) && ((gBattleTypeFlags & 0x6000100) != 0)) {
    uVar2 = Random(3);
    __umodsi3(uVar2,100);
    bVar3 = 0x4f < (extraout_r1 & 0xffff);
  }
  return bVar3;
}

// ---- ShouldTryToSetUpStat  (ROM 0x90c3c64)
bool8 ShouldTryToSetUpStat(u8 bankAtk,u8 bankDef,u16 move,u8 stat,u8 statLimit)

{
  bool8 bVar1;
  move_t move_00;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  BattlePokemon *pBVar8;
  
  uVar7 = (uint)stat;
  uVar6 = (uint)bankDef;
  uVar2 = (uint)bankAtk;
  if (uVar7 == 0xff) {
    uVar2 = AI_SpecialTypeCalc(move,uVar2,uVar6,0xff,uVar2,uVar6,move);
    return (uVar2 & 0x29) == 0;
  }
  iVar3 = GetBankAbility(uVar6);
  if (((iVar3 == 0x8d) && (bVar1 = MoveInMovesetAndUsable(0x1e2 /* Stored Power */,(u8)uVar2), bVar1 == 0)) &&
     (bVar1 = MoveInMovesetAndUsable(0x25a /* Power Trip */,(u8)uVar2), bVar1 == 0)) {
    if (uVar7 != 2) {
      return 0;
    }
    bVar1 = MoveInMovesetAndUsable(0x2b4 /* Body Press */,(u8)uVar2);
    if (bVar1 == 0) {
      return 0;
    }
  }
  bVar1 = WillFaintFromSecondaryDamage((u8)uVar2);
  if (bVar1 != 0) {
    return 0;
  }
  if (uVar7 == 0xfe) {
    return 1;
  }
  pBVar8 = gBattleMons;
  uVar4 = 0;
  if (((-1 < (int)(gBattleMons[uVar2].status1 << 0x18)) ||
      (uVar4 = GetBankAbility(uVar2), uVar4 == 0x68)) ||
     ((uVar4 = GetBankAbility(uVar2), uVar4 == 0x73 ||
      ((uVar4 = GetBankAbility(uVar2), uVar4 == 0x92 ||
       (uVar4 = func_0x090dd734(uVar2), 0x4b < uVar4)))))) {
    uVar4 = Random(uVar4);
    uVar4 = uVar4 & 1;
    bVar1 = MoveEffectInMoveset(0x19 /* EFFECT_HAZE */,bankDef);
    if (((bVar1 != 0) ||
        ((iVar3 = MoveInMoveset(0x231 /* Topsy-Turvy */,uVar6), iVar3 != 0 ||
         (bVar1 = MoveEffectInMoveset(0x8f /* EFFECT_PSYCH_UP */,bankDef), bVar1 != 0)))) && (uVar4 == 0)) {
      return 0;
    }
    iVar3 = MoveInMoveset(0x2e /* Roar */,uVar6);
    if (((((iVar3 != 0) || (iVar3 = MoveInMoveset(0x12 /* Whirlwind */,uVar6), iVar3 != 0)) ||
         ((iVar3 = MoveInMoveset(0x1bc /* Dragon Tail */,uVar6), iVar3 != 0 &&
          (iVar3 = IsOfType(uVar2,0x17 /* ? */), iVar3 == 0)))) ||
        ((iVar3 = MoveInMoveset(0x1bd /* Circle Throw */,uVar6), iVar3 != 0 && (iVar3 = IsOfType(uVar2,7 /* Ghost */), iVar3 == 0))
        )) && ((uVar5 = ViableMonCountFromBank(uVar2), 1 < uVar5 && (uVar4 == 0)))) {
      return 0;
    }
    iVar3 = sub_90dc344(uVar6);
    if (((iVar3 != 0) && (bVar1 = Can2HKO(bankDef,(u8)uVar2), bVar1 != 0)) && (uVar4 == 0)) {
      return 0;
    }
    if ((gBattleTypeFlags & 1) != 0) {
      uVar4 = ~uVar2 & 1;
      if (((pBVar8[uVar4].hp != 0) && (pBVar8[uVar4 | 2].hp != 0)) ||
         (gBattleMons[uVar2 ^ 2].hp != 0)) {
        iVar3 = ((uVar2 & 1) == 0) + 2;
        if (pBVar8[uVar4].hp != 0) {
          bVar1 = MoveWouldHitFirst(move,(u16)uVar2,(u16)uVar4);
          if (bVar1 == 0) {
            bVar1 = Can2HKO((u8)uVar4,(u8)uVar2);
          }
          else {
            bVar1 = CanKnockOut((u8)uVar4,(u8)uVar2);
          }
          if (bVar1 != 0) {
            return 0;
          }
          if (8 < gBattleMons[uVar2].statStages[uVar7 - 1]) {
            return 0;
          }
        }
        pBVar8 = gBattleMons;
        if (gBattleMons[iVar3].hp == 0) {
          return 1;
        }
        bVar1 = MoveWouldHitFirst(move,(u16)uVar2,(u16)iVar3);
        if (bVar1 == 0) {
          bVar1 = Can2HKO((u8)iVar3,(u8)uVar2);
        }
        else {
          bVar1 = CanKnockOut((u8)iVar3,(u8)uVar2);
        }
        if (bVar1 == 0) {
          return ((byte)pBVar8[uVar2].statStages[uVar7 - 1] < 9) -
                 (pBVar8[uVar2].statStages[uVar7 - 1] >> 7);
        }
        return 0;
      }
    }
    bVar1 = MoveWouldHitFirst(move,(u16)uVar2,(ushort)bankDef);
    if (bVar1 == 0) {
      iVar3 = sub_90db47c(uVar6);
      if ((iVar3 != 0) ||
         ((((move_00 = IsValidMovePrediction(bankDef,(u8)uVar2), uVar7 == 3 &&
            (gBattleMons[uVar2].statStages[2] < 9)) &&
           ((bVar1 = MoveKnocksOutXHits(move_00,bankDef,(u8)uVar2,1), bVar1 == 0 &&
            (bVar1 = WillBeFasterAfterMoveSpeedBuff((u8)uVar2,bankDef,move), bVar1 != 0)))) ||
          ((bVar1 = Can2HKO(bankDef,(u8)uVar2), bVar1 == 0 &&
           (gBattleMons[uVar2].statStages[uVar7 - 1] < 10)))))) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
        return 1;
      }
    }
    else {
      iVar3 = sub_90e031c(uVar6,uVar2);
      if (iVar3 == 0) {
        if ((gStatuses3[uVar6] & 0x130400c0) == 0) {
          return ((byte)gBattleMons[uVar2].statStages[uVar7 - 1] < 9) -
                 (gBattleMons[uVar2].statStages[uVar7 - 1] >> 7);
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
        }
        return 1;
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return 0;
}

// ---- GoodIdeaToSwapTimers  (ROM 0x90c3f80)
bool8 GoodIdeaToSwapTimers(u8 *timers,u8 sideAtk,u8 sideDef,bool8 wantToKeep)

{
  return ((uint)(timers + -1) & 0xff) < 3;
}

// ---- IsClassKillerSweeper  (ROM 0x90c3faa)
bool8 IsClassKillerSweeper(u8 class)

{
  return class == 5;
}

// ---- IsClassTeamSupport  (ROM 0x90c3fb2)
bool8 IsClassTeamSupport(u8 class)

{
  return (byte)(class - 6) < 4;
}

// ---- IsClassBatonPass  (ROM 0x90c3fc4)
bool8 IsClassBatonPass(u8 class)

{
  return class == 6;
}

// ---- IsClassScreener  (ROM 0x90c3fcc)
bool8 IsClassScreener(u8 class)

{
  return (class - 4 & 0xfb) == 0;
}

// ---- IsClassSupportScreener  (ROM 0x90c3fd8)
bool8 IsClassSupportScreener(u8 class)

{
  bool8 bVar1;
  
  bVar1 = IsClassScreener(class);
  return bVar1 != 0 && (byte)(class - 6) < 4;
}

// ---- IsClassCleric  (ROM 0x90c3ff6)
bool8 IsClassCleric(u8 class)

{
  return class == 7;
}

// ---- IsClassDoublesPhazer  (ROM 0x90c3ffe)
bool8 IsClassDoublesPhazer(u8 class)

{
  return class == 0x10;
}

// ---- IsClassPhazer  (ROM 0x90c4006)
bool8 IsClassPhazer(u8 class)

{
  return class == 9 || class == 0x10;
}

// ---- IsClassEntryHazards  (ROM 0x90c4016)
bool8 IsClassEntryHazards(u8 class)

{
  return class == 10;
}

// ---- IsClassDoublesAllOutAttacker  (ROM 0x90c401e)
bool8 IsClassDoublesAllOutAttacker(u8 class)

{
  return class == 0xb;
}

// ---- IsClassDoublesSetupAttacker  (ROM 0x90c4026)
bool8 IsClassDoublesSetupAttacker(u8 class)

{
  return class == 0xc;
}

// ---- IsClassDoublesTrickRoomSetup  (ROM 0x90c402e)
bool8 IsClassDoublesTrickRoomSetup(u8 class)

{
  return class == 0xe;
}

// ---- IsClassDoublesTrickRoomer  (ROM 0x90c4036)
bool8 IsClassDoublesTrickRoomer(u8 class)

{
  return (byte)(class - 0xd) < 2;
}

// ---- IsClassDoublesUtility  (ROM 0x90c4048)
bool8 IsClassDoublesUtility(u8 class)

{
  return class == 0xf;
}

// ---- IsClassDoublesTeamSupport  (ROM 0x90c4050)
bool8 IsClassDoublesTeamSupport(u8 class)

{
  return (byte)(class - 0x11) < 2;
}

// ---- IsClassDoublesSpecific  (ROM 0x90c4062)
bool8 IsClassDoublesSpecific(u8 class)

{
  return class == 0x12;
}

// ---- IsClassDoublesAttacker  (ROM 0x90c407c)
bool8 IsClassDoublesAttacker(u8 class)

{
  return (byte)(class - 0xb) < 3;
}

// ---- IsClassDamager  (ROM 0x90c408e)
bool8 IsClassDamager(u8 class)

{
  bool8 bVar1;
  bool bVar2;
  
  bVar2 = true;
  if ((2 < class - 1) && (bVar1 = IsClassDoublesAttacker(class), bVar1 == 0)) {
    bVar2 = class == 4;
  }
  return bVar2;
}

// ---- IsClassGoodToTaunt  (ROM 0x90c40ac)
bool8 IsClassGoodToTaunt(u8 class)

{
  bool8 bVar1;
  
  bVar1 = 0;
  if (class < 0x13) {
    bVar1 = (byte)(0x6c5f0 >> (uint)class) & 1;
  }
  return bVar1;
}

// ---- PredictFightingStyle  (ROM 0x90c40c4)
u8 PredictFightingStyle(u16 *moves,u8 ability,u8 itemEffect,u8 bank)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  char cVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  ushort *puVar14;
  uint uVar15;
  u8 uVar16;
  byte bVar17;
  uint uVar18;
  uint uVar19;
  char cVar20;
  ushort *puStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  uint uStack_28;
  uint uStack_24;
  
  uVar12 = (uint)bank;
  uVar9 = (uint)ability;
  uVar13 = 1;
  if (uVar12 == 0xff) {
    uVar13 = ~gBattleTypeFlags & 1;
  }
  else if (((gBattleTypeFlags & 1) != 0) &&
          ((gBattleMons[~uVar12 & 1].hp == 0 || (uVar13 = 0, gBattleMons[~uVar12 & 1 | 2].hp == 0)))
          ) {
    uVar13 = (uint)(gBattleMons[uVar12 ^ 2].hp == 0);
  }
  puVar14 = moves + 4;
  if (uVar13 == 0) {
    uVar13 = 0;
    uVar19 = 0;
    bVar1 = false;
    bVar6 = false;
    bVar7 = false;
    bVar4 = false;
    bVar3 = false;
    bVar5 = false;
    bVar2 = false;
    do {
      uVar18 = (uint)*moves;
      if (uVar18 != 0) {
        if (uVar18 == 0x278) {
          bVar1 = true;
          goto LAB_090c43e2;
        }
        bVar17 = gBattleMoves[uVar18].effect;
        if (bVar17 == 0x41) goto LAB_090c4470;
        if (bVar17 < 0x42) {
          if (bVar17 == 0x1c) {
LAB_090c445c:
            bVar5 = true;
          }
          else if (bVar17 < 0x1d) {
            if (bVar17 < 0xe) {
              if ((0xb < bVar17) || (bVar17 == 10)) {
LAB_090c4484:
                if (uVar18 == 0x1df) {
                  if ((uVar12 != 0xff) && (iVar8 = IsOfType(uVar12,0xc /* Grass */), iVar8 != 0)) {
LAB_090c449e:
                    uVar19 = uVar19 + 1 & 0xff;
                  }
                }
                else if ((uVar18 != 0x24f) || (uVar9 - 0x39 < 2)) goto LAB_090c449e;
              }
            }
            else {
              if (bVar17 == 0xf) goto LAB_090c4484;
              if (bVar17 == 0x19) goto LAB_090c445c;
            }
          }
          else {
            if (bVar17 == 0x32) goto LAB_090c4484;
            if (bVar17 < 0x33) {
              if ((bVar17 == 0x23) || (bVar17 == 0x2e)) goto LAB_090c4470;
            }
            else if ((0x33 < bVar17) && ((bVar17 < 0x36 || (bVar17 == 0x37)))) goto LAB_090c4484;
          }
        }
        else if (bVar17 == 0xac) {
          bVar2 = true;
        }
        else if (bVar17 < 0xad) {
          if (bVar17 == 0x7c) {
LAB_090c4470:
            bVar7 = true;
          }
          else if (bVar17 < 0x7d) {
            if (bVar17 == 0x66) goto LAB_090c4470;
            if (((bVar17 == 0x6f) && (3 < uVar18 - 0x27b)) && (uVar18 != 0xcb)) {
              bVar6 = true;
            }
          }
          else if (bVar17 == 0x7f) {
            if (uVar18 != 0xe2) {
LAB_090c4520:
              bVar4 = true;
            }
          }
          else if ((bVar17 == 0x9e) && (uVar18 == 0xfc)) {
            bVar3 = true;
          }
        }
        else if (bVar17 < 0xd5) {
          if (0xd2 < bVar17) goto LAB_090c4484;
          if (bVar17 == 0xb6) {
            if ((itemEffect == 0x84) && (uVar18 != 0x1fd)) goto LAB_090c4520;
          }
          else if (bVar17 == 0xd0) goto LAB_090c4484;
        }
        else {
          if (bVar17 == 0xde) goto LAB_090c445c;
          if ((bVar17 == 0xef) && (uVar18 != 0x28a)) goto LAB_090c4470;
        }
LAB_090c43e2:
        if (((gBattleMoves[uVar18].split != 2) && (uVar18 != 0x1f1)) && (uVar18 != 0xfc)) {
          uVar13 = uVar13 + 1 & 0xff;
        }
      }
      moves = moves + 1;
      if (puVar14 == moves) {
        uVar16 = 0xd;
        if (!bVar1) {
          if (bVar2) {
            return 0xf;
          }
          bVar1 = bVar3;
          if (((uVar9 == 0x16) || (bVar1 = bVar4, bVar3)) && (bVar1)) {
            return 0xf;
          }
          if (bVar5) {
            if (uVar13 == 3) {
              return 0xc;
            }
            if (uVar13 != 2) {
              return 0x10;
            }
            if (bVar6) {
              return 0xc;
            }
            return 0x10;
          }
          if ((3 < uVar13) || ((uVar13 == 3 && (bVar6)))) {
            if (itemEffect == 0x85) {
              return 0xd;
            }
            if (itemEffect == 0x62) {
              return 0xd;
            }
            if (itemEffect == 0x18) {
              return 0xd;
            }
            return 0xb;
          }
          if ((uVar13 + uVar19 == 3) || ((uVar13 + uVar19 == 2 && (bVar6)))) {
            if (itemEffect == 0x85) {
              return 0xd;
            }
            if (itemEffect == 0x62) {
              return 0xd;
            }
            return (itemEffect == 0x18) + 0xc;
          }
          if (!bVar7) {
            return 0xf;
          }
          uVar16 = 0x11;
        }
        if (uVar13 < 2) {
          uVar16 = uVar16 + 1;
        }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
        return uVar16;
      }
    } while( true );
  }
  cVar20 = '\0';
  bVar17 = 0;
  uStack_24 = 0;
  uStack_30 = 0;
  uStack_34 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  cVar11 = '\0';
  cVar10 = '\0';
  puStack_3c = moves;
  do {
    uVar19 = gNewBS;
    uVar18 = (uint)*puStack_3c;
    if (uVar18 == 0) goto LAB_090c4264;
    uVar15 = (uint)gBattleMoves[uVar18].effect;
    if (uVar18 == 0xe2) {
      if ((uVar12 == 0xff) || (uVar19 = ViableMonCountFromBankLoadPartyRange(uVar12), 1 < uVar19)) {
        return 6;
      }
      if (uVar15 == 0x54) {
LAB_090c45b6:
        uStack_30 = uVar13;
      }
      else {
        if (0x54 < uVar15) goto LAB_090c45e0;
        if (uVar15 == 0x23) {
LAB_090c418c:
          cVar10 = cVar10 + '\x01';
        }
        else {
          if (uVar15 < 0x24) {
LAB_090c41a8:
            if (uVar15 == 0x19) {
              return 9;
            }
            if (uVar15 == 0x1c) {
              uStack_34 = uVar13;
              goto LAB_090c41b6;
            }
          }
          else {
            if (uVar15 == 0x2a) {
              return 5;
            }
            if (uVar15 == 0x41) goto LAB_090c418c;
          }
LAB_090c41f2:
          iVar8 = IsChoiceItemEffectOrAbility(itemEffect,uVar9);
          if (iVar8 != 0) {
            return 1;
          }
          if (itemEffect == 0x46) {
            return 1;
          }
        }
      }
    }
    else {
      if (uVar15 == 0x54) goto LAB_090c45b6;
      if (uVar15 < 0x55) {
        if (uVar15 != 0x23) {
          if (uVar15 < 0x24) goto LAB_090c41a8;
          if (uVar15 == 0x2a) {
            return 5;
          }
          if (uVar15 != 0x41) goto LAB_090c41f2;
          if (uVar18 == 0x243) {
            iVar8 = GetBattlerSide(uVar12,0xc,0x1b24,&GetBattlerSide);
            if (*(char *)(uVar19 + iVar8 + 0x15) == '\0') {
              uStack_28 = uVar13;
            }
            goto LAB_090c41b6;
          }
        }
        goto LAB_090c418c;
      }
LAB_090c45e0:
      if (uVar15 != 0x6f) {
        if (uVar15 < 0x70) {
          if (uVar15 == 0x66) {
            return 7;
          }
          if (uVar15 == 0x6a) {
            return 5;
          }
        }
        else {
          if (uVar15 == 0xb3) {
            return 7;
          }
          if (uVar15 == 0xde) {
            return 9;
          }
        }
        goto LAB_090c41f2;
      }
      uStack_24 = uVar13;
    }
LAB_090c41b6:
    if (gBattleMoves[uVar18].split == 2) {
      if (uVar15 != 0x70) {
        if (uVar15 < 0x71) {
          if ((uVar15 < 10) || ((0x10 < uVar15 && (6 < uVar15 - 0x32)))) goto LAB_090c41dc;
        }
        else if (uVar15 != 0xd0) {
          if (uVar15 < 0xd1) {
            if ((uVar15 != 0x8b) && (uVar15 != 0xce)) {
LAB_090c41dc:
              cVar11 = cVar11 + '\x01';
              goto LAB_090c4264;
            }
          }
          else if (1 < (uVar15 + 0x2d & 0xff)) goto LAB_090c41dc;
        }
        goto LAB_090c4250;
      }
LAB_090c4288:
      if (uVar18 == 0x1d5) {
        iVar8 = GetBattlerSide();
        iVar8 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar8 * 0xb] << 0x1c;
joined_r0x090c42fa:
        if (iVar8 < 0) goto LAB_090c4264;
      }
      else {
        if (uVar18 < 0x1d6) {
          uVar19 = 0x1d4;
        }
        else {
          if (uVar18 == 0x1e1) {
            iVar8 = GetBattlerSide();
            iVar8 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar8 * 0xb] << 0x1a;
            goto joined_r0x090c42fa;
          }
          uVar19 = 0x2ee;
        }
        if (uVar18 == uVar19) {
          iVar8 = GetBattlerSide(~uVar12 & 1);
          iVar8 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar8 * 0xb] << 0x1b;
          goto joined_r0x090c42fa;
        }
        iVar8 = GetBattlerSide();
        if (((&gSideTimers[0].field_0xa)[iVar8 * 0xb] & 3) == 3) goto LAB_090c4264;
      }
      cVar20 = cVar20 + '\x01';
    }
    else {
      bVar17 = bVar17 + 1;
      if (uVar15 == 0x70) goto LAB_090c4288;
      if (uVar15 < 0x71) {
        if ((uVar15 < 10) || ((0x10 < uVar15 && (6 < uVar15 - 0x32)))) goto LAB_090c4264;
LAB_090c4250:
        uStack_38 = uVar13;
      }
      else {
        if (uVar15 == 0xd0) goto LAB_090c4250;
        if (uVar15 < 0xd1) {
          if ((uVar15 == 0x8b) || (uVar15 == 0xce)) goto LAB_090c4250;
        }
        else if ((uVar15 + 0x2d & 0xff) < 2) goto LAB_090c4250;
      }
    }
LAB_090c4264:
    puStack_3c = puStack_3c + 1;
    if (puStack_3c == puVar14) {
      if ((cVar10 != '\0') || (uStack_28 != 0)) {
        return 8;
      }
      if (cVar20 != '\0') {
        return (uStack_34 == 0) + 9;
      }
      if (2 < bVar17) {
        if (uStack_38 != 0) {
          return 2;
        }
        if (cVar11 == '\0') {
          return 1;
        }
        return 3;
      }
      if (((uStack_30 == 0) || (uStack_24 == 0)) && (bVar17 == 2)) {
        if (uStack_38 != 0) {
          return 2;
        }
        if (cVar11 != '\0') {
          return 3;
        }
        if (uStack_34 != 0) {
          return 3;
        }
      }
      return 5;
    }
  } while( true );
}

// ---- PredictBankFightingStyle  (ROM 0x90c4618)
u8 PredictBankFightingStyle(u8 bank)

{
  u8 uVar1;
  u8 itemEffect;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  ushort *moves;
  u16 *puVar5;
  u16 *puVar6;
  uint uVar7;
  bool bVar8;
  u16 auStack_20 [6];
  
  uVar3 = (uint)bank;
  uVar1 = GetBankAbility();
  itemEffect = GetBankItemEffect(uVar3);
  iVar4 = IsDynamaxed(uVar3);
  if (iVar4 == 0) {
    moves = gBattleMons[uVar3].moves;
  }
  else {
    iVar4 = IsRaidBattle();
    bVar8 = false;
    if (iVar4 != 0) {
      uVar7 = GetBattlerAtPosition(1);
      bVar8 = uVar7 == uVar3;
    }
    Memset(auStack_20,0,8);
    uVar7 = 0;
    do {
      if (bVar8) {
        puVar5 = (u16 *)(uVar7 * 2);
        uVar2 = puVar5[uVar3 * 0x2c + 0x1011df8];
        if (gBattleMoves[uVar2].split != 2) goto LAB_090c46ae;
        puVar6 = auStack_20;
      }
      else {
LAB_090c46ae:
        uVar2 = GetMaxMove(uVar3,uVar7 & 0xff);
        puVar6 = (u16 *)(uVar7 << 1);
        puVar5 = auStack_20;
      }
      uVar7 = uVar7 + 1;
      *(ushort *)((int)puVar6 + (int)puVar5) = uVar2;
    } while (uVar7 != 4);
    moves = auStack_20;
  }
  uVar1 = PredictFightingStyle(moves,uVar1,itemEffect,bank);
  return uVar1;
}

// ---- GetBankFightingStyle  (ROM 0x90c46dc)
u8 GetBankFightingStyle(u8 bank)

{
  u8 uVar1;
  u8 *puVar2;
  
  puVar2 = (u8 *)(gNewBS + bank + 0x888);
  if (*puVar2 == 0xff) {
    uVar1 = PredictBankFightingStyle(bank);
    *puVar2 = uVar1;
  }
  return *(u8 *)(gNewBS + bank + 0x888);
}

// ---- ShouldPrioritizeKOingFoesDoubles  (ROM 0x90c470c)
bool8 ShouldPrioritizeKOingFoesDoubles(u8 bank)

{
  u8 class;
  bool8 bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = GetBattlerSide(bank);
  bVar3 = true;
  if ((iVar2 != 0) && (1 < gBattleResources->ai->aiFlags)) {
    class = GetBankFightingStyle(bank);
    bVar1 = IsClassDoublesAttacker(class);
    bVar3 = bVar1 != 0;
  }
  return bVar3;
}

// ---- ShouldPrioritizeMostDamageDoubles  (ROM 0x90c4744)
bool8 ShouldPrioritizeMostDamageDoubles(u8 bank)

{
  u8 class;
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = GetBattlerSide(bank);
  bVar4 = true;
  if ((iVar3 != 0) && (2 < gBattleResources->ai->aiFlags)) {
    class = GetBankFightingStyle(bank);
    bVar1 = IsClassDoublesAttacker(class);
    bVar4 = false;
    if (bVar1 != 0) {
      uVar2 = Random2();
      bVar4 = (uVar2 & 3) == 0;
    }
  }
  return bVar4;
}

// ---- ShouldPrioritizeDangerousTarget  (ROM 0x90c478c)
bool8 ShouldPrioritizeDangerousTarget(u8 bank)

{
  u8 class;
  bool8 bVar1;
  int iVar2;
  
  iVar2 = GetBattlerSide(bank);
  bVar1 = 1;
  if ((iVar2 != 0) && (bVar1 = 0, 2 < gBattleResources->ai->aiFlags)) {
    class = GetBankFightingStyle(bank);
    bVar1 = IsClassDoublesAttacker(class);
    bVar1 = 1 - (bVar1 == 0);
  }
  return bVar1;
}

// ---- ShouldTrap  (ROM 0x90c47c4)
bool8 ShouldTrap(u8 bankAtk,u8 bankDef,u16 move,u8 class)

{
  bool8 bVar1;
  int iVar2;
  bool bVar3;
  
  bVar1 = WillFaintFromSecondaryDamage(bankAtk);
  if (((bVar1 == 0) && (class == 5)) && (iVar2 = HasMonToSwitchTo(bankDef), iVar2 != 0)) {
    bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
    if (bVar1 == 0) {
      bVar1 = CanKnockOut(bankDef,bankAtk);
      if (bVar1 != 0) goto LAB_090c47d6;
      bVar1 = Can2HKO(bankDef,bankAtk);
    }
    else {
      bVar1 = CanKnockOut(bankDef,bankAtk);
    }
    bVar3 = bVar1 == 0;
  }
  else {
LAB_090c47d6:
    bVar3 = false;
  }
  return bVar3;
}

// ---- GetAmountToRecoverBy  (ROM 0x90c4818)
u16 GetAmountToRecoverBy(u8 bankAtk,u8 bankDef,u16 move)

{
  byte bVar1;
  u16 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  u32 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  ushort uVar11;
  uint uVar12;
  uint uVar13;
  
  uVar10 = move;
  uVar12 = (uint)bankDef;
  uVar3 = (uint)bankAtk;
  if (uVar10 == 0xffff) {
    return gBattleMons[uVar3].maxHP - gBattleMons[uVar3].hp;
  }
  iVar4 = sub_90754f0(uVar3);
  if (iVar4 != 0) {
    return 0;
  }
  uVar5 = sub_90739b4(uVar3);
  uVar6 = GetBaseMaxHP(uVar3);
  bVar1 = gBattleMoves[uVar10].effect;
  uVar13 = uVar6;
  if (bVar1 == 0x25) goto LAB_090c4934;
  if (0x25 < bVar1) {
    if (bVar1 == 0x6f) {
      iVar4 = GetBankAbility(uVar3);
      iVar8 = GetBankItemEffect(uVar3);
      if (((int)(gStatuses3[uVar3] << 0x15) < 0) &&
         (uVar12 = MathMax(1,uVar6 >> 4 & 0xffff), iVar8 == 0x68)) {
        uVar13 = sub_900042a((uVar12 & 0xffff) * 0x82,100);
        uVar13 = uVar13 & 0xffff;
      }
      else {
        uVar13 = 0;
      }
      for (uVar12 = 0; uVar12 < gBattlersCount; uVar12 = uVar12 + 1 & 0xff) {
        if ((((int)(gStatuses3[uVar12] << 0x1d) < 0) &&
            (iVar9 = GetBankAbility(uVar12), iVar9 != 0x73)) && ((gStatuses3[uVar12] & 3) == uVar3))
        {
          uVar10 = GetBaseMaxHP(uVar12);
          iVar9 = MathMax(1,uVar10 >> 3 & 0xffff);
          uVar13 = uVar13 + iVar9 & 0xffff;
        }
      }
      if ((iVar8 == 0x2b) || ((iVar8 == 0x4d && (iVar8 = IsOfType(uVar3,3 /* Poison */), iVar8 != 0)))) {
        iVar8 = MathMax(1,uVar6 >> 4 & 0xffff);
        uVar13 = uVar13 + iVar8 & 0xffff;
      }
      if ((&UNK_02023f40)[uVar3] != '\0') {
        iVar8 = MathMax(1,uVar6 >> 1 & 0xffff);
        uVar13 = uVar13 + iVar8 & 0xffff;
      }
      if ((((gBattleWeather & 0x1007) != 0) &&
          (iVar8 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar8 == 0)) &&
         (iVar8 = sub_9076728(uVar3), iVar8 != 0)) {
        uVar12 = uVar6 >> 4;
        if (iVar4 != 0x2c) {
          if (iVar4 != 0x62) goto LAB_090c4ad4;
          uVar12 = uVar6 >> 3;
        }
        iVar8 = MathMax(1,uVar12 & 0xffff);
        uVar13 = uVar13 + iVar8 & 0xffff;
      }
LAB_090c4ad4:
      if ((((gBattleWeather & 0x180) != 0) &&
          (iVar8 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar8 == 0)) && (iVar4 == 0x69)) {
        iVar8 = MathMax(1,uVar6 >> 4 & 0xffff);
        uVar13 = uVar13 + iVar8 & 0xffff;
      }
      if (((gBattleMons[uVar3].status1 & 0x88) != 0) && (iVar4 == 0x68)) {
        iVar4 = MathMax(1,uVar6 >> 3 & 0xffff);
        uVar13 = uVar13 + iVar4 & 0xffff;
      }
      if ((gTerrainType == '\x02') && (iVar4 = CheckGrounding(uVar3), iVar4 == 1)) {
        iVar4 = MathMax(1,uVar6 >> 4 & 0xffff);
        uVar13 = uVar13 + iVar4 & 0xffff;
      }
      uVar7 = GetSecondaryEffectDamage(bankAtk);
      if (uVar7 < uVar13) goto LAB_090c4934;
      goto LAB_090c48a2;
    }
    if (0x6f < bVar1) {
      if (bVar1 != 0x84) {
        if (bVar1 == 0xa2) {
          bVar1 = gDisableStructs[uVar3].stockpileCounter;
          if (bVar1 == 2) goto LAB_090c48e4;
          if (bVar1 == 3) goto LAB_090c4934;
          if (bVar1 == 1) {
            uVar6 = uVar6 >> 2 & 0xffff;
            goto LAB_090c4964;
          }
        }
        goto LAB_090c48a2;
      }
      if (((gBattleWeather == 0) ||
          (uVar11 = gBattleWeather & 0x2000, (gBattleWeather & 0x2000) != 0)) ||
         (iVar4 = AbilityBattleEffects(0x13,uVar11,0xd,uVar11,uVar11), iVar4 != 0)) {
LAB_090c48f8:
        uVar6 = uVar6 >> 1;
        goto LAB_090c48e6;
      }
      if (uVar10 == 0x261) {
        if (((gBattleWeather & 0x18) != 0) &&
           (iVar4 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar4 == 0)) goto LAB_090c4934;
        goto LAB_090c48f8;
      }
      if ((gBattleWeather & 0x860) == 0) {
        if (gBattleWeather != 0) goto LAB_090c48e0;
        goto LAB_090c48f8;
      }
      iVar4 = sub_9076636(uVar3);
      if (iVar4 != 0) goto LAB_090c4934;
      uVar6 = uVar6 >> 1 & 0xffff;
      goto LAB_090c4964;
    }
    if (bVar1 == 0x5b) {
      iVar4 = sub_90739b4(uVar12);
      uVar12 = MathMax(1,(int)(uVar5 + iVar4) >> 1);
      if (uVar5 < (uVar12 & 0xffff)) {
        uVar5 = (uVar12 & 0xffff) - uVar5;
        goto LAB_090c496a;
      }
    }
LAB_090c48a2:
    uVar13 = 0;
    goto LAB_090c4934;
  }
  if (bVar1 == 8) {
    iVar4 = GetBankAbility(uVar12);
    if ((iVar4 != 0xe7) && ((gBattleMons[uVar12].status1 & 7) == 0)) goto LAB_090c48a2;
LAB_090c487e:
    if (uVar10 == 0x26a) {
      iVar4 = sub_906b400(uVar3,uVar12);
      uVar5 = -iVar4;
    }
    else {
      uVar7 = GetFinalAIMoveDamage(move,bankAtk,bankDef,1,(void *)0x0);
      if ((uVar10 == 0x21c) || (uVar12 = (uVar7 & 0xffff) >> 1, uVar10 == 0x1d1)) {
        uVar12 = sub_900042a((uVar7 & 0xffff) * 0x4b,100);
      }
      uVar12 = MathMax(1,uVar12);
      iVar4 = GetBankItemEffect(uVar3);
      uVar13 = uVar12 & 0xffff;
      if (iVar4 != 0x68) goto LAB_090c4934;
      uVar5 = sub_900042a((uVar12 & 0xffff) * 0xd,10);
    }
  }
  else {
    if (bVar1 != 0x20) {
      if (bVar1 != 3) goto LAB_090c48a2;
      goto LAB_090c487e;
    }
    if ((uVar10 == 0x2c3) || (uVar10 == 0x2dc)) {
LAB_090c48e0:
      uVar6 = uVar6 >> 2;
    }
    else {
LAB_090c48e4:
      uVar6 = uVar6 >> 1;
    }
LAB_090c48e6:
    uVar6 = uVar6 & 0xffff;
LAB_090c4964:
    uVar5 = MathMax(1,uVar6);
  }
LAB_090c496a:
  uVar13 = uVar5 & 0xffff;
LAB_090c4934:
  uVar2 = MathMin(uVar13,gBattleMons[uVar3].maxHP - 1);
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
  return uVar2;
}

// ---- ShouldRecover  (ROM 0x90c4c08)
bool8 ShouldRecover(u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  u16 healAmount;
  
  healAmount = GetAmountToRecoverBy(bankAtk,bankDef,move);
  if ((move == 0xffff) ||
     (bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar1 != 0)) {
    bVar1 = CanKnockOut(bankDef,bankAtk);
    if ((bVar1 != 0) &&
       (bVar1 = CanKnockOutAfterHealing(bankDef,bankAtk,healAmount,1,0), bVar1 == 0)) {
      return 1;
    }
    bVar1 = Can2HKO(bankDef,bankAtk);
    if (((bVar1 != 0) && (bVar1 = IsBankIncapacitated(bankDef), bVar1 == 0)) &&
       (gBattleMons[bankAtk].hp < healAmount)) {
      return ~gBattleResources->ai->simulatedRNG[1] & 1;
    }
  }
  else {
    bVar1 = CanKnockOut(bankDef,bankAtk);
    if (((bVar1 == 0) && (bVar1 = IsBankIncapacitated(bankDef), bVar1 == 0)) &&
       (bVar1 = Can2HKO(bankDef,bankAtk), bVar1 != 0)) {
      bVar1 = CanKnockOutAfterHealing(bankDef,bankAtk,healAmount,1,1);
      return bVar1 == 0;
    }
  }
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
  return 0;
}

// ---- ShouldProtect  (ROM 0x90c4cc8)
u8 ShouldProtect(u8 bankAtk,u8 bankDef,u16 move)

{
  byte bVar1;
  bool8 bVar2;
  move_t mVar3;
  u16 uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  bool8 checkConfusion;
  u8 uVar12;
  uint uVar13;
  
  uVar13 = (uint)bankDef;
  uVar5 = (uint)bankAtk;
  mVar3 = IsValidMovePrediction(bankDef,bankAtk);
  bVar1 = gBattleMoves[mVar3].effect;
  uVar6 = GetBankAbility(uVar13);
  iVar7 = IsDynamaxed(uVar5);
  bVar2 = WillFaintFromSecondaryDamage(bankAtk);
  if ((bVar2 != 0) && (iVar8 = IsMoxieAbility(uVar6), iVar8 == 0)) {
    return 0;
  }
  bVar2 = IsBankIncapacitated(bankDef);
  if (bVar2 != 0) {
    return 0;
  }
  if (((((int)(gBattleMons[uVar5].status1 << 0x18) < 0) &&
       (iVar8 = GetBankAbility(uVar5), iVar8 != 0x68)) &&
      (iVar8 = GetBankAbility(uVar5), iVar8 != 0x73)) &&
     (iVar8 = GetBankAbility(uVar5), iVar8 != 0x92)) {
    return 0;
  }
  if (iVar7 == 0) {
    iVar8 = GetBankAbility(uVar5);
    iVar9 = GetBankItemEffect(uVar5);
    if (iVar9 == 0x4b) {
      iVar9 = CanBePoisoned(uVar5,uVar5,0);
      if (iVar9 != 0) {
        if ((iVar8 - 0x68U & 0xf7) == 0) {
          return 1;
        }
        if (iVar8 == 0x92) {
          return 1;
        }
        if (iVar8 == 0x73) {
          return 1;
        }
LAB_090c4d90:
        iVar8 = MoveInMoveset(0x107 /* Facade */,uVar5);
        if (iVar8 != 0) {
          return 1;
        }
      }
    }
    else if ((iVar9 == 0x4c) && (iVar9 = CanBeBurned(uVar5,0), iVar9 != 0)) {
      if (iVar8 == 0x3e) {
        return 1;
      }
      if ((iVar8 - 0x73U & 0xdf) == 0) {
        return 1;
      }
      goto LAB_090c4d90;
    }
    iVar8 = GetBankAbility(uVar5);
    if (iVar8 == 3) {
      uVar10 = SpeedCalc(uVar5);
      uVar11 = SpeedCalc(uVar13);
      if ((uVar10 <= uVar11) && (gBattleMons[uVar5].statStages[2] < 0xc)) {
        return 1;
      }
    }
  }
  iVar8 = IsDynamaxed(uVar13);
  if (((((iVar8 != 0) &&
        ((((iVar8 = IsRaidBattle(), iVar8 == 0 || (uVar10 = GetBattlerAtPosition(1), uVar10 != uVar13)) &&
          (iVar8 = IsDynamaxed(uVar5), iVar8 == 0)) &&
         ((iVar8 = sub_90ddfa4(uVar5,uVar13), iVar8 == 0 && (gBattleMoves[mVar3].split != 2)))))) ||
       (bVar1 == 7)) ||
      (((bVar1 == 0x9b && ((gStatuses3[uVar13] & 0x130400c0) != 0)) &&
       ((int)((uint)gBattleMoves[mVar3].flags << 0x1e) < 0)))) ||
     (((((gStatuses3[uVar13] & 0x1800) != 0 && (bVar2 = CanKnockOut(bankAtk,bankDef), bVar2 == 0))
       && (bVar2 = CanKnockOut(bankDef,bankAtk), bVar2 != 0)) &&
      (iVar8 = ViableMonCountFromBank(uVar5), iVar8 == 1)))) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x03004fa3) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x03004fa3) is written */
    return 1;
  }
  if (((gBattleTypeFlags & 1) == 0) ||
     (((gBattleMons[~uVar5 & 1].hp == 0 || (gBattleMons[~uVar5 & 1 | 2].hp == 0)) &&
      (gBattleMons[uVar5 ^ 2].hp == 0)))) {
    uVar4 = GetAmountToRecoverBy(bankAtk,bankDef,move);
    bVar2 = CanKnockOut(bankDef,bankAtk);
    if (bVar2 == 0) {
      bVar2 = Can2HKO(bankDef,bankAtk);
      if (bVar2 == 0) {
        return 0;
      }
      if (iVar7 != 0) {
        return 2;
      }
      uVar12 = 2;
    }
    else {
      if (iVar7 != 0) {
        return 2;
      }
      uVar12 = 1;
    }
    bVar2 = CanKnockOutAfterHealing(bankDef,bankAtk,uVar4,uVar12,(bool8)iVar7);
    if (bVar2 == 0) {
      return 1;
    }
    bVar2 = IsTakingSecondaryDamage(bankDef,checkConfusion);
    if (bVar2 == 0) {
      return 2;
    }
    return 1;
  }
  uVar13 = uVar5 ^ 2;
  if (gBattleMons[uVar13].hp == 0) {
    return 0;
  }
  uVar12 = (u8)uVar13;
  uVar4 = GetAIChosenMove(uVar12,bankDef);
  uVar10 = GetBankAbility(uVar5);
  if ((uVar10 == 0xe2) || (uVar4 == 0)) {
    if (iVar7 != 0) goto LAB_090c4f22;
  }
  else {
    if (iVar7 != 0) goto LAB_090c4f22;
    iVar7 = GetBankAbility(uVar5);
    if ((((iVar7 != 0xe2) && (iVar7 = GetBaseMoveTarget(uVar4,uVar13), iVar7 << 0x1a < 0)) &&
        (uVar13 = AI_SpecialTypeCalc(uVar4,uVar13,uVar5), (uVar13 & 0x29) == 0)) &&
       (bVar2 = IsDamagingMoveUnusable(uVar4,uVar12,bankAtk), bVar2 == 0)) {
      return 3;
    }
  }
  uVar12 = GetDoubleKillingScore(uVar4,uVar12,bankDef);
  uVar10 = (uint)uVar12;
  if (10 < uVar10) {
    return 4;
  }
LAB_090c4f22:
  iVar7 = Random2(uVar10);
  if ((iVar7 << 0x1f < 0) || (gDisableStructs[uVar5].protectUses != 0)) {
    return 0;
  }
  return UNK_03004fa3 != '\0';
}

// ---- ShouldPhaze  (ROM 0x90c4ffc)
bool8 ShouldPhaze(u8 bankAtk,u8 bankDef,u16 move,u8 class)

{
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  
  uVar4 = (uint)bankDef;
  uVar2 = (uint)bankAtk;
  iVar3 = IsDynamaxed(uVar4);
  if ((iVar3 == 0) && (bVar1 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1), bVar1 == 0)) {
    if (((gBattleTypeFlags & 1) == 0) ||
       (((gBattleMons[~uVar2 & 1].hp == 0 || (gBattleMons[~uVar2 & 1 | 2].hp == 0)) &&
        (gBattleMons[uVar2 ^ 2].hp == 0)))) {
      bVar1 = CanKnockOut(bankAtk,bankDef);
      if ((bVar1 == 0) &&
         ((-1 < (int)(gStatuses3[uVar4] << 0x1a) ||
          ((bVar5 = gDisableStructs[uVar4].field_0xf & 0xf, bVar5 != 1 &&
           ((bVar5 != 2 ||
            (bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar1 != 0)))))))) {
        if ((gBattleMoves[move].effect == 0x1c /* EFFECT_ROAR */) &&
           ((bVar1 = IsClassPhazer(class), bVar1 != 0 &&
            (((iVar3 = GetBattlerSide(uVar4),
              (int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1b) < 0 ||
              (iVar3 = GetBattlerSide(uVar4),
              ((byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] & 0xf) >> 2 != 0)) ||
             ((iVar3 = GetBattlerSide(uVar4), ((&gSideTimers[0].field_0xa)[iVar3 * 0xb] & 3) != 0 ||
              (iVar3 = GetBattlerSide(uVar4),
              (int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x19) < 0)))))))) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
          return 1;
        }
        goto LAB_090c5088;
      }
    }
    else {
      if (gBattleMoves[move].effect != 0x19 /* EFFECT_HAZE */) {
        if (gBattleMoves[move].effect == 0x1c /* EFFECT_ROAR */) {
          bVar1 = IsClassPhazer(class);
          if (bVar1 == 0) {
            return 0;
          }
          iVar3 = GetBattlerSide(uVar4);
          if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1b) < 0) {
            return 1;
          }
          iVar3 = GetBattlerSide(uVar4);
          if (((byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] & 0xf) >> 2 != 0) {
            return 1;
          }
          iVar3 = GetBattlerSide(uVar4);
          if (((&gSideTimers[0].field_0xa)[iVar3 * 0xb] & 3) != 0) {
            return 1;
          }
        }
LAB_090c5088:
        iVar3 = sub_90dd85a(uVar4);
        return iVar3 != 0;
      }
      if (gBattleMons[uVar2 ^ 2].hp != 0) {
        sub_90dd85a();
        return 0;
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return 0;
}

// ---- ShouldUseWishAromatherapy  (ROM 0x90c51c0)
bool8 ShouldUseWishAromatherapy(u8 bankAtk,u8 bankDef,u16 move,u8 class)

{
  byte bVar1;
  short sVar2;
  bool8 bVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  bool8 bVar10;
  uint uVar11;
  byte bStack_1a;
  byte abStack_19 [5];
  
  uVar5 = (uint)bankAtk;
  iVar6 = LoadPartyRange(uVar5,&bStack_1a,abStack_19);
  bVar1 = gBattleMoves[move].effect;
  if ((bVar1 == 0xb3) && (uVar8 = ViableMonCountFromBank(uVar5), uVar8 < 2)) {
    bVar3 = Can2HKO(bankDef,bankAtk);
    if ((bVar3 != 0) && (bVar3 = HasProtectionMoveInMoveset(bankAtk,1), bVar3 == 0)) {
      return 0;
    }
    bVar3 = WillFaintFromSecondaryDamage(bankAtk);
    if (bVar3 != 0) {
      return 0;
    }
  }
  bVar3 = CanKnockOut(bankAtk,bankDef);
  if ((bVar3 != 0) && (uVar8 = ViableMonCountFromBank(bankDef), uVar8 < 2)) {
    return 0;
  }
  bVar10 = 0;
  bVar3 = 0;
  uVar8 = 0;
  do {
    uVar11 = uVar8;
    iVar9 = iVar6 + uVar11 * 100;
    uVar8 = GetMonData(iVar9,0x39,0);
    uVar4 = GetMonData(iVar9,0x3a,0);
    iVar7 = GetMonData(iVar9,0x2d,0);
    if ((iVar7 == 0) && ((uVar8 & 0xffff) != 0)) {
      iVar7 = sub_900042a((uVar8 & 0xffff) * 100,uVar4);
      if ((iVar7 < 0x41) && ((bStack_1a <= uVar11 && (uVar11 < abStack_19[0])))) {
        bVar3 = 1;
      }
      iVar7 = GetMonData(iVar9,0x37,0);
      if ((iVar7 != 0) && ((move != 0xd7 /* Heal Bell */ || (iVar7 = GetMonAbility(iVar9), iVar7 != 0x2b)))) {
        bVar10 = 1;
      }
    }
    uVar8 = uVar11 + 1;
  } while (uVar11 + 1 != 6);
  if ((gBattleTypeFlags & 1) == 0) {
    if (class != 7) {
      return 0;
    }
LAB_090c52dc:
    if (bVar1 == 0x66) {
      return bVar10;
    }
    if (bVar1 == 0xb3) {
      return bVar3;
    }
    return 0;
  }
  uVar8 = ~uVar5 & 1;
  sVar2 = *(short *)(gBattleMons[0].pp + uVar8 * (uVar11 + 0x53) + 4);
  if ((sVar2 == 0) || (*(short *)(gBattleMons[0].pp + (uVar8 | 2) * (uVar11 + 0x53) + 4) == 0)) {
    if (gBattleMons[uVar5 ^ 2].hp == 0) {
      if (class == 7) goto LAB_090c52dc;
      if (sVar2 == 0) {
        return 0;
      }
    }
    else if (sVar2 == 0) goto LAB_090c5354;
  }
  if ((gBattleMons[uVar8 | 2].hp == 0) && (gBattleMons[uVar5 ^ 2].hp == 0)) {
    return 0;
  }
LAB_090c5354:
  if (bVar1 == 0x66) {
    return bVar10;
  }
  if (bVar1 == 0xb3) {
    bVar3 = ShouldRecover(bankAtk,bankDef,move);
    return bVar3;
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return 0;
}

// ---- MoveSplitOnTeam  (ROM 0x90c5384)
bool8 MoveSplitOnTeam(u8 bank,u8 split)

{
  short sVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 uStack_1a;
  undefined1 auStack_19 [5];
  
  iVar3 = LoadPartyRange(bank,&uStack_1a,auStack_19);
  iVar6 = iVar3 + 600;
  do {
    iVar7 = 0xd;
    do {
      iVar5 = GetMonData(iVar3,0x39,0);
      sVar1 = GetMonData(iVar3,iVar7,0);
      sVar2 = GetMonData(iVar3,iVar7 + 4,0);
      if ((((iVar5 != 0) && (sVar2 != 0)) && (sVar1 != 0)) &&
         (uVar4 = CalcMoveSplitFromParty(iVar3), uVar4 == split)) {
        return 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0x11);
    iVar3 = iVar3 + 100;
    if (iVar3 == iVar6) {
      return 0;
    }
  } while( true );
}

// ---- ShouldSetUpScreens  (ROM 0x90c5400)
bool8 ShouldSetUpScreens(u8 bankAtk,u8 bankDef,u16 move)

{
  uint uVar1;
  bool8 bVar2;
  move_t mVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  uVar1 = gNewBS;
  uVar7 = move;
  uVar6 = (uint)bankDef;
  uVar4 = (uint)bankAtk;
  iVar5 = GetBattlerSide(uVar4);
  if (*(char *)(uVar1 + iVar5 + 0x15) != '\0') {
    return 0;
  }
  if (((gBattleWeather & 0x180) == 0) ||
     (((uVar7 != 0x243 && (1 < uVar7 - 0x3bc)) || ((~gSideStatuses[uVar4] & 3) == 0)))) {
    mVar3 = IsValidMovePrediction(bankDef,bankAtk);
    bVar2 = RealPhysicalMoveInMoveset(bankDef);
    bVar8 = true;
    if (((bVar2 == 0) && (bVar8 = false, (gBattleTypeFlags & 1) != 0)) &&
       (((gBattleMons[~uVar4 & 1].hp != 0 && (gBattleMons[~uVar4 & 1 | 2].hp != 0)) ||
        (bVar8 = false, gBattleMons[uVar4 ^ 2].hp != 0)))) {
      bVar8 = false;
      if (gBattleMons[uVar6 ^ 2].hp != 0) {
        bVar2 = RealPhysicalMoveInMoveset((u8)(uVar6 ^ 2));
        bVar8 = bVar2 != 0;
      }
    }
    bVar2 = SpecialMoveInMoveset(bankDef);
    bVar9 = true;
    if (((bVar2 == 0) && (bVar9 = false, (gBattleTypeFlags & 1) != 0)) &&
       (((gBattleMons[~uVar4 & 1].hp != 0 && (gBattleMons[~uVar4 & 1 | 2].hp != 0)) ||
        (bVar9 = false, gBattleMons[uVar4 ^ 2].hp != 0)))) {
      bVar9 = false;
      if (gBattleMons[uVar6 ^ 2].hp != 0) {
        bVar2 = SpecialMoveInMoveset((u8)(uVar6 ^ 2));
        bVar9 = bVar2 != 0;
      }
    }
    if (gBattleMoves[uVar7].effect == 0x23 /* EFFECT_LIGHT_SCREEN */) {
      if ((bVar9 == false) && (bVar2 = MoveSplitOnTeam(bankDef,1), bVar2 == 0)) {
        return 0;
      }
      bVar10 = false;
      if (-1 < (int)((uint)gSideStatuses[uVar4] << 0x1f)) {
        bVar2 = MoveInMovesetAndUsable(0x73 /* Reflect */,bankAtk);
        bVar10 = bVar2 != 0;
      }
      if ((bVar8 != false || bVar9 != false) && (iVar5 = GetBankItemEffect(uVar4), iVar5 != 0x52)) {
        if (bVar8 == false) {
          if (bVar9 != false) {
            return 1;
          }
        }
        else if (bVar9 != false) {
          if (!bVar10) {
            return 1;
          }
          iVar5 = CalcMoveSplit(uVar6,mVar3);
          if (iVar5 == 0) {
            return 0;
          }
          return 1;
        }
        if (bVar10) {
          return bVar8 ^ 1;
        }
      }
    }
    else {
      if ((gBattleMoves[uVar7].effect != 0x41 /* EFFECT_REFLECT */) ||
         ((bVar8 == false && (bVar2 = MoveSplitOnTeam(bankDef,0), bVar2 == 0)))) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
        return 0;
      }
      bVar10 = false;
      if (-1 < (int)((uint)gSideStatuses[uVar4] << 0x1e)) {
        bVar2 = MoveInMovesetAndUsable(0x71 /* Light Screen */,bankAtk);
        bVar10 = bVar2 != 0;
      }
      if (bVar8 != false || bVar9 != false) {
        if (bVar8 == false) {
          if (bVar10) {
            return bVar9 ^ 1;
          }
        }
        else if (((bVar9 != false) && (bVar10)) && (iVar5 = CalcMoveSplit(uVar6,mVar3), iVar5 == 1))
        {
          return 0;
        }
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return 1;
}

// ---- ShouldUseFakeOut  (ROM 0x90c562c)
bool8 ShouldUseFakeOut(u8 bankAtk,u8 bankDef,u8 defAbility)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)bankAtk;
  if (((gDisableStructs[uVar3].isFirstTurn != 0) &&
      (bVar1 = IsUsefulToFlinchTarget(bankDef), bVar1 != 0)) &&
     (bVar1 = CanBeFlinched(bankDef,bankAtk,defAbility,0xfc), bVar1 != 0)) {
    if (((gBattleTypeFlags & 1) == 0) ||
       (((gBattleMons[~uVar3 & 1].hp == 0 || (gBattleMons[~uVar3 & 1 | 2].hp == 0)) &&
        (gBattleMons[uVar3 ^ 2].hp == 0)))) {
      iVar2 = CanBeChoiceLocked(uVar3);
      if ((iVar2 == 0) || (uVar3 = ViableMonCountFromBankLoadPartyRange(uVar3), 1 < uVar3)) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
        return 1;
      }
    }
    else {
      iVar2 = sub_90db59c(bankDef,uVar3,0xfc);
      if (iVar2 != 0) {
        return 0;
      }
      iVar2 = CanBeChoiceLocked(uVar3);
      if (iVar2 == 0) {
        return 1;
      }
      uVar3 = ViableMonCountFromBankLoadPartyRange(uVar3);
      if (2 < uVar3) {
        return 1;
      }
    }
    iVar2 = ViableMonCountFromBank(bankDef);
    if (iVar2 == 1) {
      bVar1 = MoveKnocksOutXHits(0xfc,bankAtk,bankDef,1);
      return 1 - (bVar1 == 0);
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return 0;
}

// ---- ShouldPivot  (ROM 0x90c5704)
bool8 ShouldPivot(u8 bankAtk,u8 bankDef,u16 move,u8 class)

{
  sbyte sVar1;
  undefined1 uVar2;
  bool8 bVar3;
  u8 uVar4;
  bool8 bVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  
  uVar12 = move;
  uVar11 = (uint)bankDef;
  uVar6 = (uint)bankAtk;
  if ((*(uint *)(&gBitTable + uVar6 * 4) & (uint)*(byte *)(gNewBS + 0x1c5)) != 0) {
    return 3;
  }
  bVar3 = AnyUsefulOffseniveStatIsRaised(bankAtk);
  if (bVar3 == 0) {
LAB_090c5742:
    bVar13 = 9 < gBattleMons[uVar11].statStages[6];
  }
  else {
    bVar3 = IsClassDamager(class);
    bVar13 = true;
    if (bVar3 == 0) goto LAB_090c5742;
  }
  uVar2 = gActiveBattler;
  gActiveBattler = bankAtk;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  uVar4 = GetMostSuitableMonToSwitchIntoFlags();
  uVar7 = (uint)uVar4;
  gActiveBattler = uVar2;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  uVar8 = GetBankAbility(uVar6);
  uVar9 = GetBankAbility(uVar11);
  bVar3 = WillTakeSignificantDamageFromEntryHazards(bankAtk,4);
  if (bVar3 != 0) {
    return 0;
  }
  if ((gBattleTypeFlags & 1) != 0) {
    if ((gBattleMons[~uVar6 & 1].hp != 0) && (gBattleMons[~uVar6 & 1 | 2].hp != 0)) {
      return 0;
    }
    if (gBattleMons[uVar6 ^ 2].hp != 0) {
      return 0;
    }
  }
  iVar10 = HasMonToSwitchTo(uVar6);
  if (iVar10 == 0) {
    return 1;
  }
  bVar3 = IsPredictedToSwitch(bankDef,bankAtk);
  if ((bVar3 != 0) && (bVar13 == false)) {
    return 2;
  }
  bVar3 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if (bVar3 == 0) {
    bVar3 = CanKnockOut(bankDef,bankAtk);
    if (bVar3 != 0) {
      return 1 - (gBattleMoves[uVar12].effect == 0x99 /* EFFECT_TELEPORT */);
    }
    bVar3 = Can2HKO(bankDef,bankAtk);
    if (bVar3 != 0) {
      bVar3 = CanKnockOut(bankAtk,bankDef);
      if (bVar3 != 0) {
        bVar3 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1);
        return bVar3 == 0;
      }
      bVar3 = IsClassDamager(class);
      if (bVar3 == 0) {
        return 0;
      }
      if (-1 < (int)(uVar7 << 0x1f)) {
        return 0;
      }
      if ((uVar4 & 0x4a) == 0) {
        return 0;
      }
      return 2;
    }
    bVar3 = CanKnockOut(bankAtk,bankDef);
    if (bVar3 != 0) {
      bVar3 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1);
      if (bVar3 == 0) {
        return bVar13 ^ 1;
      }
      return 0;
    }
    bVar3 = Can2HKO(bankAtk,bankDef);
    bVar5 = IsClassDamager(class);
    if (bVar3 != 0) {
      if (bVar5 == 0) {
        return 0;
      }
      if (gBattleMoves[uVar12].split == 2) {
        return 0;
      }
      if (((int)(uVar7 << 0x1f) < 0) && ((uVar4 & 0x4a) != 0)) {
        return 2;
      }
      if ((uVar7 & 0x22) == 0x22) {
        return 2;
      }
LAB_090c5868:
      iVar10 = func_0x09074fe0(uVar11);
      if (iVar10 != 0) {
        return 2;
      }
      iVar10 = IsAffectedBySturdy(uVar9,uVar11);
      if (iVar10 != 0) {
        return 2;
      }
      iVar10 = IsDamageHalvedDueToFullHP(uVar11,uVar9,uVar12,uVar8);
      if (iVar10 == 0) {
        return 0;
      }
      return 2;
    }
    if ((bVar5 != 0) && ((uVar7 & 0x41) == 0x41)) {
      return 2;
    }
    if (bVar13 != false) {
      return 0;
    }
    if ((uVar4 & 0x4a) == 0) {
      return 0;
    }
    if (((int)((uint)gSideStatuses[uVar6] << 0x1b) < 0) && ((int)(uVar7 << 0x1a) < 0)) {
      return 2;
    }
    bVar3 = WillFaintFromSecondaryDamage(bankAtk);
    if (bVar3 != 0) {
      return 2;
    }
    if (bVar5 == 0) {
      return 1;
    }
    bVar3 = RealPhysicalMoveInMoveset(bankAtk);
    bVar5 = SpecialMoveInMoveset(bankAtk);
    if (bVar3 != 0) goto joined_r0x090c5a84;
    if (bVar5 == 0) {
      return 1;
    }
  }
  else {
    bVar3 = CanKnockOutWithoutMove(move,bankAtk,bankDef,1);
    if (bVar3 != 0) {
      return 0;
    }
    bVar3 = CanKnockOut(bankAtk,bankDef);
    if (bVar3 != 0) {
      return 1;
    }
    bVar3 = IsClassDamager(class);
    if (bVar3 == 0) {
      if (bVar13 != false) {
        return 0;
      }
    }
    else {
      bVar5 = Can2HKO(bankAtk,bankDef);
      if (bVar5 != 0) {
        bVar3 = CanKnockOut(bankDef,bankAtk);
        if (bVar3 != 0) {
          return 2;
        }
        if (gBattleMoves[uVar12].split == 2) {
          return 0;
        }
        if (((int)(uVar7 << 0x1e) < 0) && ((uVar4 & 0x21) != 0)) {
          return 2;
        }
        goto LAB_090c5868;
      }
      if (bVar13 != false) {
        return 0;
      }
      if (gBattleMoves[uVar12].split != 2) {
        iVar10 = func_0x09074fe0(uVar11);
        if (iVar10 != 0) {
          return 2;
        }
        iVar10 = IsAffectedBySturdy(uVar9,uVar11);
        if (iVar10 != 0) {
          return 2;
        }
        iVar10 = IsDamageHalvedDueToFullHP(uVar11,uVar9,uVar12,uVar8);
        if (iVar10 != 0) {
          return 2;
        }
      }
    }
    if ((uVar4 & 10) == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
      return 0;
    }
    if (((int)((uint)gSideStatuses[uVar6] << 0x1b) < 0) && ((int)(uVar7 << 0x1a) < 0)) {
      return 2;
    }
    bVar5 = WillFaintFromSecondaryDamage(bankAtk);
    if (bVar5 != 0) {
      return 2;
    }
    if (bVar3 == 0) {
      return 0;
    }
    bVar3 = RealPhysicalMoveInMoveset(bankAtk);
    bVar5 = SpecialMoveInMoveset(bankAtk);
    if (bVar3 == 0) {
      if (bVar5 == 0) {
        return 1;
      }
    }
    else {
joined_r0x090c5a84:
      if (bVar5 == 0) {
        sVar1 = gBattleMons[uVar6].statStages[0];
        goto LAB_090c5932;
      }
    }
  }
  sVar1 = gBattleMons[uVar6].statStages[3];
LAB_090c5932:
  if (sVar1 < 4) {
    return 2;
  }
  return 1;
}

// ---- BankLikelyToUseMoveSplit  (ROM 0x90c5c38)
u8 BankLikelyToUseMoveSplit(u8 bank,u8 class)

{
  bool8 bVar1;
  
  bVar1 = PhysicalMoveInMoveset(bank);
  if (bVar1 == 0) {
    bVar1 = SpecialMoveInMoveset(bank);
    if (((bVar1 != 0) && (class - 1 < 3)) && (gBattleMons[bank].attack < gBattleMons[bank].spAttack)
       ) {
      return 1;
    }
  }
  else if ((class - 1 < 3) && (gBattleMons[bank].spAttack < gBattleMons[bank].attack)) {
    return 0;
  }
  return 2;
}

// ---- IncreaseStatusViability  (ROM 0x90c5c90)
void IncreaseStatusViability(s16 *originalViability,u8 class,u8 boost,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  s16 sVar2;
  u8 amount;
  s16 sStack_12;
  
  sStack_12 = *originalViability;
  if (class - 2 < 0x11) {
                        switch(class - 2) {
    case 0:
      bVar1 = Can2HKO(bankDef,bankAtk);
      if (bVar1 != 0) goto sw_c5caa_9;
    case 3:
    case 5:
    case 13:
      amount = boost + 3;
      break;
    case 1:
    case 7:
    case 10:
    case 11:
      amount = boost + 4;
      break;
    case 4:
      amount = 1;
      if (boost < 3) goto sw_c5caa_9;
      break;
    case 9:
      goto sw_c5caa_9;
    case 2:
    case 6:
    case 15:
    case 16:
      amount = boost + 2;
      break;
    case 8:
      amount = 3;
      break;
    case 12:
      amount = boost + 7;
      break;
    case 14:
      amount = boost + 8;
    }
    IncreaseViability(&sStack_12,amount);
  }
sw_c5caa_9:
  sVar2 = MathMin((int)sStack_12,0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseStatViability  (ROM 0x90c5d0c)
void IncreaseStatViability
               (s16 *originalViability,u8 class,u8 boost,u8 bankAtk,u8 bankDef,u16 move,u8 stat,
               u8 statLimit)

{
  sbyte sVar1;
  u8 uVar2;
  bool8 bVar3;
  s16 sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  u8 in_stack_ffffffc8;
  s16 asStack_1a [3];
  
  uVar7 = (uint)bankAtk;
  uVar8 = (uint)stat;
  asStack_1a[0] = *originalViability;
  if (statLimit < 0xc) {
    if (((gBattleTypeFlags & 1) != 0) &&
       (((gBattleMons[~uVar7 & 1].hp != 0 && (gBattleMons[~uVar7 & 1 | 2].hp != 0)) ||
        (gBattleMons[uVar7 ^ 2].hp != 0)))) {
LAB_090c5d64:
      iVar5 = IsRaidBattle();
      if (((iVar5 != 0) && (uVar6 = GetBattlerAtPosition(1), uVar7 == uVar6)) &&
         ((gBattleMoves[move].split == 2 &&
          ((uVar6 = func_0x0908f108(uVar7), 0x31 < uVar6 && (iVar5 = sub_908ee64(uVar7), iVar5 == 0)
           ))))) {
        sub_908ef3c(uVar7);
      }
      goto LAB_090c5e02;
    }
    uVar2 = GetBankFightingStyle(bankDef);
    if ((4 < (byte)(uVar2 - 5)) ||
       ((((gLastUsedMoves[bankDef] - 1 & 0xffff) < 0xfffe &&
         (gBattleMoves[gLastUsedMoves[bankDef]].split != 2)) || ((uVar8 != 1 && (uVar8 != 4)))))) {
      bVar3 = IsPredictedToSwitch(bankDef,bankAtk);
      if (bVar3 != 0) goto LAB_090c5e02;
      goto LAB_090c5d64;
    }
    uVar6 = class - 1;
    if (0x11 < uVar6) goto sw_c5e0a_10;
                        switch(uVar6) {
    case 0:
      goto sw_c6094_0;
    case 10:
      goto sw_c5e0a_10;
    case 2:
      goto sw_c5e0a_2;
    case 4:
      goto sw_c5e0a_4;
    case 5:
      goto sw_c6094_5;
    case 6:
      goto sw_c5e0a_6;
    case 3:
    case 7:
    case 16:
    case 17:
      goto sw_c5e0a_3;
    case 8:
      goto sw_c5e0a_8;
    case 9:
      goto sw_c5e0a_9;
    case 11:
      goto sw_c5e0a_11;
    case 12:
      goto sw_c5e0a_12;
    case 13:
      goto sw_c5e0a_13;
    case 14:
      goto sw_c5e0a_14;
    case 15:
      goto sw_c5e0a_15;
    }
sw_c5e0a_1:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
LAB_090c5e46:
    uVar2 = boost + 3;
    goto LAB_090c5f26;
  }
LAB_090c5e02:
  uVar6 = class - 1;
  if (0x11 < uVar6) goto sw_c5e0a_10;
                      switch(uVar6) {
  case 0:
    if (uVar8 != 0xff) {
sw_c6094_0:
      bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
      if (bVar3 == 0) {
        if ((gBattleMoves[move].split == 2) || ((uVar8 != 1 && (uVar8 != 4))))
        goto sw_c5e0a_10;
        uVar2 = 1;
        goto LAB_090c5f26;
      }
    }
    goto LAB_090c5e46;
  case 1:
    goto sw_c5e0a_1;
  case 10:
    goto sw_c5e0a_10;
  case 2:
sw_c5e0a_2:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 3;
    break;
  case 4:
sw_c5e0a_4:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 5;
    break;
  case 5:
    if (7 < uVar8) goto sw_c5e0a_10;
sw_c6094_5:
    uVar6 = 1 << uVar8;
    if ((uVar6 & 0x5a) == 0) {
      if ((uVar6 & 0x24) == 0) {
        if ((-1 < (int)(uVar6 << 0x18)) || (0xb < gBattleMons[uVar7].statStages[uVar8 - 1]))
        goto sw_c5e0a_10;
        uVar2 = 6;
        goto LAB_090c5f26;
      }
      sVar1 = gBattleMons[uVar7].statStages[uVar8 - 1];
      uVar2 = 4;
    }
    else {
      sVar1 = gBattleMons[uVar7].statStages[uVar8 - 1];
      uVar2 = 5;
    }
    if (9 < sVar1) goto sw_c5e0a_10;
    goto LAB_090c5f26;
  case 6:
sw_c5e0a_6:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 7;
    break;
  case 3:
  case 7:
  case 16:
  case 17:
sw_c5e0a_3:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    break;
  case 8:
sw_c5e0a_8:
    bVar3 = MoveEffectInMoveset(0x19 /* EFFECT_HAZE */,bankAtk);
    if ((bVar3 != 0) ||
       (bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8), bVar3 == 0))
    goto sw_c5e0a_10;
    class = 9;
    break;
  case 9:
sw_c5e0a_9:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 10;
    break;
  case 11:
sw_c5e0a_11:
    if (uVar8 < 8) {
      if (((uVar8 < 6) && (uVar8 != 1)) && ((uVar8 == 0 || (1 < uVar8 - 3))))
      goto sw_c5e0a_10;
    }
    else if (uVar8 < 0xfe) goto sw_c5e0a_10;
    if (6 < gBattleMons[uVar7].statStages[uVar8 - 1]) goto sw_c5e0a_10;
    uVar2 = 0x11;
LAB_090c5f26:
    IncreaseViability(asStack_1a,uVar2);
    goto sw_c5e0a_10;
  case 12:
sw_c5e0a_12:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 0xd;
    break;
  case 13:
sw_c5e0a_13:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 0xe;
    break;
  case 14:
sw_c5e0a_14:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 0xf;
    break;
  case 15:
sw_c5e0a_15:
    bVar3 = ShouldTryToSetUpStat(bankAtk,bankDef,move,stat,in_stack_ffffffc8);
    if (bVar3 == 0) goto sw_c5e0a_10;
    class = 0x10;
  }
  IncreaseStatusViability(asStack_1a,class,1,bankAtk,bankDef);
sw_c5e0a_10:
  sVar4 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar4;
  return;
}

// ---- IncreaseSleepViability  (ROM 0x90c60bc)
void IncreaseSleepViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  s16 sVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  u8 amount;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  s16 asStack_1a [3];
  
  uVar6 = (uint)bankDef;
  uVar5 = (uint)bankAtk;
  uVar8 = move;
  asStack_1a[0] = *originalViability;
  bVar1 = BadIdeaToPutToSleep(bankDef,bankAtk);
  if (bVar1 != 0) {
    return;
  }
  if ((((gBattleTypeFlags & 1) == 0) ||
      (((gBattleMons[~uVar5 & 1].hp == 0 || (gBattleMons[~uVar5 & 1 | 2].hp == 0)) &&
       (gBattleMons[uVar5 ^ 2].hp == 0)))) ||
     (((uVar7 = uVar6 ^ 2, gBattleMons[uVar7].hp == 0 ||
       (uVar3 = GetBaseMoveTarget(uVar8,uVar5), (uVar3 & 0x28) == 0)) ||
      (iVar4 = MoveBlockedBySubstitute(uVar8,uVar5,uVar7), iVar4 != 0)))) {
    bVar9 = false;
  }
  else {
    bVar1 = BadIdeaToPutToSleep((u8)uVar7,bankAtk);
    bVar9 = bVar1 == 0;
  }
  if (gBattleMoves[uVar8].effect == 0xbb /* EFFECT_YAWN */) {
    bVar1 = CanKnockOut(bankAtk,bankDef);
    if (((bVar1 != 0) && (iVar4 = func_0x090db4b8(uVar6,uVar5), iVar4 == 0)) &&
       (bVar1 = IsPredictedToSwitch(bankDef,bankAtk), bVar1 == 0)) {
      return;
    }
    iVar4 = GetBankAbility(uVar6);
    if (((iVar4 != 0x36) && (iVar4 = ViableMonCountFromBank(uVar5), iVar4 == 1)) &&
       (bVar1 = HasProtectionMoveInMoveset(bankAtk,1), bVar1 == 0)) {
      bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (bVar1 == 0) {
        bVar1 = Can2HKO(bankDef,bankAtk);
        if (bVar1 != 0) {
          return;
        }
      }
      else {
        bVar1 = CanKnockOut(bankDef,bankAtk);
        if (bVar1 != 0) {
          return;
        }
        bVar1 = Can2HKO(bankDef,bankAtk);
        if ((bVar1 != 0) && (bVar1 = HealingMoveInMoveset(bankAtk), bVar1 == 0)) {
          return;
        }
      }
    }
  }
  if (0x10 < class - 2) goto LAB_090c6254;
                      switch(class - 2) {
  case 0:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (uVar5 < 0x50) {
      class = 2;
      break;
    }
LAB_090c623c:
    amount = 9;
    goto LAB_090c623e;
  case 1:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (0x4f < uVar5) {
LAB_090c6272:
      amount = 8;
      goto LAB_090c623e;
    }
    class = 3;
    break;
  case 3:
    class = 5;
    break;
  case 4:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (0x4f < uVar5) goto LAB_090c623c;
    class = 6;
    break;
  case 5:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    amount = 7;
    if (0x4f < uVar5) goto LAB_090c623e;
    class = 7;
    break;
  case 2:
  case 6:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (0x4f < uVar5) goto LAB_090c6272;
    break;
  case 7:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (0x4f < uVar5) goto LAB_090c623c;
    class = 9;
    break;
  case 8:
    uVar5 = AccuracyCalc(uVar8,uVar5,uVar6);
    if (0x4f < uVar5) goto LAB_090c6272;
    class = 10;
    break;
  case 9:
    class = 0xb;
    break;
  case 10:
    amount = 0x12;
    if (bVar9) goto LAB_090c623e;
    class = 0xc;
    break;
  case 11:
    if (bVar9) {
LAB_090c6326:
      amount = 0x10;
      goto LAB_090c623e;
    }
    class = 0xd;
    break;
  case 12:
    if (bVar9) goto LAB_090c6326;
    class = 0xe;
    break;
  case 14:
    if (bVar9) goto sw_c6110_13;
    class = 0x10;
    break;
  case 13:
sw_c6110_13:
    amount = 0x11;
LAB_090c623e:
    IncreaseViability(asStack_1a,amount);
    goto LAB_090c6254;
  case 15:
  case 16:
    if (bVar9) {
      amount = 0x13;
      goto LAB_090c623e;
    }
  }
  IncreaseStatusViability(asStack_1a,class,3,bankAtk,bankDef);
LAB_090c6254:
  sVar2 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar2;
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return;
}

// ---- IncreaseSubstituteViability  (ROM 0x90c6370)
void IncreaseSubstituteViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  s16 sVar2;
  u8 uVar3;
  s16 asStack_1a [3];
  
  asStack_1a[0] = *originalViability;
  if (((int)(gBattleMons[bankAtk].status2 << 7) < 0) || (0x10 < class - 2))
  goto sw_c639c_9;
                      switch(class - 2) {
  case 0:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    uVar3 = 8;
    if (bVar1 == 0) goto sw_c639c_9;
    goto LAB_090c6412;
  case 9:
    goto sw_c639c_9;
  case 1:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 2;
    class = 3;
    break;
  case 3:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 2;
    class = 5;
    break;
  case 4:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 4;
LAB_090c6412:
    IncreaseViability(asStack_1a,uVar3);
    goto sw_c639c_9;
  case 5:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 7;
    break;
  case 2:
  case 6:
  case 15:
  case 16:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    break;
  case 7:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 9;
    break;
  case 8:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 10;
    break;
  case 10:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 0xc;
    break;
  case 11:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 0xd;
    break;
  case 12:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 0xe;
    break;
  case 13:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 0xf;
    break;
  case 14:
    bVar1 = ShouldUseSubstitute(bankAtk,bankDef);
    if (bVar1 == 0) goto sw_c639c_9;
    uVar3 = 1;
    class = 0x10;
  }
  IncreaseStatusViability(asStack_1a,class,uVar3,bankAtk,bankDef);
sw_c639c_9:
  sVar2 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseEntryHazardsViability  (ROM 0x90c64ec)
void IncreaseEntryHazardsViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  s16 sVar2;
  int iVar3;
  u8 uVar4;
  uint uVar5;
  s16 asStack_1a [3];
  
  uVar5 = move;
  asStack_1a[0] = *originalViability;
  bVar1 = HasUsedMoveWithEffect(bankDef,0xb7);
  if (bVar1 != 0) {
    return;
  }
  if (0x10 < class - 2) goto sw_c651e_9;
                      switch(class - 2) {
  case 0:
    iVar3 = IsWorthSettingHazards(bankDef);
    if (iVar3 == 0) goto sw_c651e_9;
    uVar4 = 2;
    class = 2;
    break;
  case 1:
    iVar3 = IsWorthSettingHazards(bankDef);
    if (iVar3 == 0) goto sw_c651e_9;
    uVar4 = 2;
    class = 3;
    break;
  case 3:
    iVar3 = IsWorthSettingHazards(bankDef);
    uVar4 = 1;
    if (iVar3 != 0) {
      uVar4 = 2;
    }
    class = 5;
    break;
  case 4:
    if (gBattleMoves[uVar5].effect == 0x70 /* EFFECT_SPIKES */) {
      bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      if (bVar1 == 0) {
        bVar1 = Can2HKO(bankDef,bankAtk);
      }
      else {
        bVar1 = CanKnockOut(bankDef,bankAtk);
        if (bVar1 != 0) goto sw_c651e_9;
        bVar1 = WillFaintFromSecondaryDamage(bankAtk);
      }
      if (bVar1 != 0) goto sw_c651e_9;
LAB_090c65be:
      uVar4 = 4;
      goto LAB_090c66ea;
    }
    uVar4 = 2;
    class = 6;
    break;
  case 5:
    iVar3 = IsWorthSettingHazards(bankDef);
    uVar4 = 1;
    if (iVar3 != 0) {
      uVar4 = 2;
    }
    class = 7;
    break;
  case 2:
  case 6:
    iVar3 = IsWorthSettingHazards(bankDef);
    if (iVar3 == 0) goto LAB_090c6600;
LAB_090c678e:
    uVar4 = 2;
    break;
  case 7:
    if (uVar5 == 0xbf) {
      iVar3 = GetBattlerSide(bankDef);
      uVar5 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1e;
LAB_090c6626:
      if ((uVar5 == 0) ||
         (((iVar3 = GetBattlerSide(bankDef),
           (int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1b) < 0 ||
           (iVar3 = MoveInMoveset(0x1d4 /* Stealth Rock */,bankAtk), iVar3 == 0)) &&
          ((iVar3 = sub_2023de4(bankDef),
           (int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1a) < 0 ||
           (iVar3 = MoveInMoveset(0x1e1 /* Sticky Web */,bankAtk), iVar3 == 0)))))) goto LAB_090c66b2;
      iVar3 = ViableMonCountFromBankLoadPartyRange(bankDef);
      if (iVar3 != 2) goto LAB_090c66c4;
      uVar4 = 1;
    }
    else {
      if (uVar5 == 0x1d5) {
        iVar3 = GetBattlerSide(bankDef);
        uVar5 = ((byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] & 0xf) >> 2;
        goto LAB_090c6626;
      }
LAB_090c66b2:
      iVar3 = ViableMonCountFromBankLoadPartyRange(bankDef);
      if (iVar3 == 2) {
LAB_090c66c4:
        uVar4 = 2;
      }
      else {
        uVar4 = 3;
      }
    }
    class = 9;
    break;
  case 8:
    uVar4 = 5;
    if ((uVar5 != 0x1d5) && (uVar4 = 7, uVar5 != 0x1e1)) {
      if (uVar5 != 0x1d4) goto LAB_090c65be;
      uVar4 = 6;
    }
LAB_090c66ea:
    IncreaseViability(asStack_1a,uVar4);
  case 9:
    goto sw_c651e_9;
  case 10:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    uVar4 = 1;
    if (iVar3 == 0) {
      uVar4 = 2;
    }
    class = 0xc;
    break;
  case 11:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    if (iVar3 == 0) {
      if (uVar5 == 0x1d4) {
        uVar4 = 0xd;
        goto LAB_090c66ea;
      }
      uVar4 = 2;
    }
    else {
      uVar4 = 1;
    }
    class = 0xd;
    break;
  case 12:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    uVar4 = 1;
    if (iVar3 == 0) {
      uVar4 = 2;
    }
    class = 0xe;
    break;
  case 13:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    uVar4 = 1;
    if (iVar3 == 0) {
      uVar4 = 2;
    }
    class = 0xf;
    break;
  case 14:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    uVar4 = 1;
    if (iVar3 == 0) {
      uVar4 = 2;
    }
    class = 0x10;
    break;
  case 15:
  case 16:
    iVar3 = BankSideHasTwoTrainers(bankDef);
    if (iVar3 == 0) goto LAB_090c678e;
LAB_090c6600:
    uVar4 = 1;
  }
  IncreaseStatusViability(asStack_1a,class,uVar4,bankAtk,bankDef);
sw_c651e_9:
  sVar2 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseFakeOutViability  (ROM 0x90c67a4)
void IncreaseFakeOutViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef,u16 move)

{
  u8 bankAtk_00;
  bool8 bVar1;
  bool8 bVar2;
  bool8 bVar3;
  u16 uVar4;
  s16 sVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  s16 asStack_1a [3];
  
  uVar9 = (uint)bankDef;
  uVar6 = (uint)bankAtk;
  asStack_1a[0] = *originalViability;
  if (((move == 0xfc /* Fake Out */) && ((gBattleTypeFlags & 1) != 0)) &&
     (((gBattleMons[~uVar6 & 1].hp != 0 && (gBattleMons[~uVar6 & 1 | 2].hp != 0)) ||
      (gBattleMons[uVar6 ^ 2].hp != 0)))) {
    uVar10 = uVar6 ^ 2;
    bankAtk_00 = (u8)uVar10;
    uVar4 = GetAIChosenMove(bankAtk_00,bankDef);
    if (((gBattleMons[uVar10].hp != 0) && (uVar4 == 0xfc)) &&
       (gBattleStruct->moveTarget[uVar10] == uVar9)) {
      return;
    }
    if (((gBattleMons[uVar9].hp == 0) || (uVar11 = uVar9 ^ 2, gBattleMons[uVar11].hp == 0)) ||
       ((gBattleMons[uVar10].hp != 0 &&
        ((uVar4 == 0xfc && (gBattleStruct->moveTarget[uVar10] == uVar11)))))) goto LAB_090c67be;
    bVar1 = CanKnockOut(bankDef,bankAtk);
    bVar12 = false;
    if (gBattleMons[uVar10].hp != 0) {
      bVar2 = CanKnockOut(bankDef,bankAtk_00);
      bVar12 = bVar2 != 0;
    }
    bVar2 = CanKnockOut((u8)uVar11,bankAtk);
    bVar13 = false;
    if (gBattleMons[uVar10].hp != 0) {
      bVar3 = CanKnockOut((u8)uVar11,bankAtk_00);
      bVar13 = bVar3 != 0;
    }
    if ((byte)((bVar2 != 0) + bVar13) <= (byte)((bVar1 != 0) + bVar12)) goto LAB_090c67be;
    uVar6 = AI_SpecialTypeCalc(0xfc,uVar6,uVar9);
    bVar12 = (uVar6 & 0x29) == 0;
  }
  else {
LAB_090c67be:
    bVar12 = false;
  }
  if (class - 0xb < 8) {
                        switch(class - 0xb) {
    case 0:
    case 1:
      cVar8 = '\x0f';
      break;
    case 2:
      iVar7 = IsTrickRoomActive();
      if (iVar7 != 0) goto LAB_090c6904;
    case 3:
    case 6:
    case 7:
      cVar8 = '\x11';
      break;
    case 4:
    case 5:
      cVar8 = '\x13';
    }
  }
  else {
    cVar8 = '\b';
  }
  IncreaseViability(asStack_1a,cVar8 - bVar12);
LAB_090c6904:
  sVar5 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar5;
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
  return;
}

// ---- IncreasePivotViability  (ROM 0x90c6938)
void IncreasePivotViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef,u8 pivotType)

{
  s16 sVar1;
  u8 amount;
  uint uVar2;
  s16 sStack_1a;
  uint uStack_18;
  
  uStack_18 = (uint)bankAtk;
  uVar2 = (uint)class;
  sStack_1a = *originalViability;
  if (((gBattleTypeFlags & 1) == 0) ||
     (((gBattleMons[~uStack_18 & 1].hp == 0 || (gBattleMons[~uStack_18 & 1 | 2].hp == 0)) &&
      (gBattleMons[uStack_18 ^ 2].hp == 0)))) {
    if (uVar2 == 0xff) {
      if (pivotType == 3) {
sw_c69ba_1:
        amount = 9;
      }
      else {
sw_c69ba_0:
        amount = 3;
      }
    }
    else {
LAB_090c69ac:
      if (pivotType == 3) goto sw_c69ba_1;
      if (0x11 < uVar2 - 1) goto LAB_090c699a;
                          switch(uVar2 - 1) {
      case 0:
      case 9:
        goto sw_c69ba_0;
      case 1:
      case 2:
      case 4:
      case 5:
        goto sw_c69ba_1;
      case 3:
      case 6:
      case 7:
        amount = 7;
        break;
      case 8:
        amount = 4;
        break;
      case 12:
      case 13:
      case 14:
        amount = 0x10;
        break;
      case 15:
        amount = 0xe;
        break;
      case 16:
      case 17:
        amount = 0xf;
        break;
      case 10:
      case 11:
        goto sw_c69ba_10;
      }
    }
  }
  else {
    if (uVar2 != 0xff) goto LAB_090c69ac;
    if (pivotType == 3) goto sw_c69ba_1;
sw_c69ba_10:
    amount = 0x12;
  }
  IncreaseViability(&sStack_1a,amount);
LAB_090c699a:
  sVar1 = MathMin((int)sStack_1a,0xff);
  *originalViability = sVar1;
  return;
}

// ---- IncreaseViabilityForSlowKOMove  (ROM 0x90c69f4)
void IncreaseViabilityForSlowKOMove(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  s16 sVar2;
  uint uVar3;
  int iVar4;
  u8 amount;
  s16 sStack_1a;
  uint uStack_18;
  
  uStack_18 = (uint)bankAtk;
  sStack_1a = *originalViability;
  if (class == 0xff) goto sw_c6a0e_0;
  uVar3 = class - 1;
  if (9 < uVar3) goto LAB_090c6a30;
                      switch(uVar3) {
  case 1:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if (iVar4 != 0) goto sw_c6a0e_0;
    break;
  case 0:
  case 2:
sw_c6a0e_0:
    amount = 8;
    goto LAB_090c6a2a;
  case 4:
  case 8:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if (iVar4 == 0) goto sw_c6a0e_0;
LAB_090c6a4a:
    amount = 9;
    goto LAB_090c6a2a;
  case 5:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if (iVar4 != 0) goto LAB_090c6a4a;
    bVar1 = Can2HKO(bankDef,bankAtk);
    if (bVar1 != 0) goto sw_c6a0e_0;
LAB_090c6a66:
    amount = 3;
    goto LAB_090c6a2a;
  case 6:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if (iVar4 != 0) goto LAB_090c6a4a;
    bVar1 = Can2HKO(bankDef,bankAtk);
    amount = 7;
    if (bVar1 != 0) goto LAB_090c6a2a;
    break;
  case 3:
  case 7:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if ((iVar4 != 0) || (bVar1 = Can2HKO(bankDef,bankAtk), bVar1 != 0)) goto LAB_090c6a4a;
    break;
  case 9:
    iVar4 = BetterToKOLastFoeMon(uStack_18,bankDef,uStack_18,sStack_1a,originalViability);
    if (iVar4 != 0) goto LAB_090c6a4a;
    bVar1 = Can2HKO(bankDef,bankAtk);
    if (bVar1 == 0) goto LAB_090c6a66;
  }
  amount = 6;
LAB_090c6a2a:
  IncreaseViability(&sStack_1a,amount);
LAB_090c6a30:
  sVar2 = MathMin((int)sStack_1a,0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseFoeProtectionViability  (ROM 0x90c6abc)
void IncreaseFoeProtectionViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  s16 sVar2;
  uint uVar3;
  u8 amount;
  s16 asStack_12 [3];
  
  asStack_12[0] = *originalViability;
  if (class == 0xff) {
sw_c6ad4_6:
    amount = 0xc;
    goto LAB_090c6afa;
  }
  uVar3 = class - 5;
  if (uVar3 < 0xe) {
                        switch(uVar3) {
    case 0:
      bVar1 = IsTrapped(bankDef,1);
      amount = 3;
      if (bVar1 != 0) goto sw_c6ad4_9;
      break;
    case 9:
sw_c6ad4_9:
      amount = 7;
      break;
    case 6:
      goto sw_c6ad4_6;
    case 7:
    case 10:
      amount = 10;
      break;
    case 8:
      amount = 4;
      break;
    case 11:
      amount = 0xd;
      break;
    case 12:
    case 13:
      amount = 1;
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      goto sw_c6ad4_1;
    }
LAB_090c6afa:
    IncreaseViability(asStack_12,amount);
  }
  else {
sw_c6ad4_1:
    IncreaseStatusViability(asStack_12,class,3,bankAtk,bankDef);
  }
  sVar2 = MathMin((int)asStack_12[0],0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseAllyProtectionViability  (ROM 0x90c6b2e)
void IncreaseAllyProtectionViability(s16 *originalViability,u8 class)

{
  s16 sVar1;
  u8 amount;
  uint uVar2;
  s16 asStack_12 [3];
  
  asStack_12[0] = *originalViability;
  if (class == 0xff) {
sw_c6b46_0:
    amount = 0xf;
  }
  else {
    uVar2 = class - 0xb;
    if (7 < uVar2) goto LAB_090c6b5a;
                        switch(uVar2) {
    case 0:
      goto sw_c6b46_0;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      amount = 0xe;
      break;
    case 2:
      amount = 0xc;
    }
  }
  IncreaseViability(asStack_12,amount);
LAB_090c6b5a:
  sVar1 = MathMin((int)asStack_12[0],0xff);
  *originalViability = sVar1;
  return;
}

// ---- IncreaseTeamProtectionViability  (ROM 0x90c6b70)
void IncreaseTeamProtectionViability(s16 *originalViability,u8 class)

{
  s16 sVar1;
  u8 amount;
  s16 asStack_12 [3];
  
  asStack_12[0] = *originalViability;
  if (class - 0xb < 8) {
                        switch(class - 0xb) {
    case 0:
      amount = 8;
      break;
    case 1:
    case 2:
    case 5:
      amount = 3;
      break;
    case 3:
      amount = 0xd;
      break;
    case 4:
    case 6:
    case 7:
      amount = 0xc;
    }
    IncreaseViability(asStack_12,amount);
  }
  sVar1 = MathMin((int)asStack_12[0],0xff);
  *originalViability = sVar1;
  return;
}

// ---- IncreaseTailwindViability  (ROM 0x90c6bb2)
void IncreaseTailwindViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  s16 sVar1;
  uint uVar2;
  uint uVar3;
  u8 uVar4;
  s16 asStack_1a [3];
  
  asStack_1a[0] = *originalViability;
  uVar2 = class - 4;
  if (uVar2 < 0xf) {
                        switch(uVar2) {
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
      uVar4 = 2;
      goto LAB_090c6be2;
    case 8:
      uVar2 = SpeedCalc(bankAtk);
      uVar3 = SpeedCalc(bankDef);
      if (uVar3 <= uVar2) goto LAB_090c6c08;
    case 13:
    case 14:
      uVar4 = 0x12;
      break;
    case 11:
      uVar4 = 0xb;
      break;
    case 1:
    case 6:
    case 7:
    case 9:
    case 10:
    case 12:
      goto sw_c6bc8_1;
    }
    IncreaseViability(asStack_1a,uVar4);
  }
  else {
sw_c6bc8_1:
    if (class - 0xb < 8) {
      uVar4 = 3;
    }
    else {
      uVar4 = 1;
    }
LAB_090c6be2:
    IncreaseStatusViability(asStack_1a,class,uVar4,bankAtk,bankDef);
  }
LAB_090c6c08:
  sVar1 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar1;
  return;
}

// ---- IncreaseHelpingHandViability  (ROM 0x90c6c2e)
void IncreaseHelpingHandViability(s16 *originalViability,u8 class)

{
  s16 sVar1;
  u8 amount;
  s16 asStack_12 [3];
  
  asStack_12[0] = *originalViability;
  if (class - 0xb < 8) {
                        switch(class - 0xb) {
    case 0:
      amount = 6;
      break;
    case 1:
    case 2:
    case 5:
      amount = 1;
      break;
    case 3:
      amount = 0xf;
      break;
    case 4:
      amount = 0xd;
      break;
    case 6:
    case 7:
      amount = 10;
    }
    IncreaseViability(asStack_12,amount);
  }
  sVar1 = MathMin((int)asStack_12[0],0xff);
  *originalViability = sVar1;
  return;
}

// ---- IncreaseHealPartnerViability  (ROM 0x90c6c74)
void IncreaseHealPartnerViability(s16 *originalViability,u8 class,u8 partner)

{
  short sVar1;
  ushort uVar2;
  s16 sVar3;
  int iVar4;
  u8 amount;
  s16 sStack_1a;
  uint uStack_18;
  
  uStack_18 = (uint)partner;
  sVar1 = *originalViability;
  uVar2 = gBattleMons[uStack_18].hp;
  if ((uVar2 == 0) ||
     (iVar4 = sub_900042a((uint)gBattleMons[uStack_18].maxHP << 1,3,gBattleMons + uStack_18,
                          gBattleMons,originalViability), (int)(uint)uVar2 <= iVar4)) {
    if (class - 0xb < 7) {
                          switch(class - 0xb) {
      case 0:
        amount = 7;
        break;
      case 1:
      case 2:
      case 5:
        amount = 2;
        break;
      case 3:
        amount = 0xc;
        break;
      case 4:
        amount = 0xf;
        break;
      case 6:
        amount = 0xd;
      }
      IncreaseViability(&sStack_1a,amount);
    }
    sVar3 = MathMin((int)sVar1,0xff);
    *originalViability = sVar3;
  }
  return;
}

// ---- IncreasePsychUpViability  (ROM 0x90c6ce0)
void IncreasePsychUpViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  s16 sVar2;
  byte stat;
  int iVar3;
  uint uVar4;
  int iStack_34;
  s16 sStack_22;
  byte abStack_20 [12];
  
  bVar1 = GoodIdeaToSwapStatStages(bankAtk,bankDef);
  if (bVar1 != 0) {
    abStack_20[0] = 1;
    abStack_20[1] = 4;
    abStack_20[2] = 3;
    abStack_20[3] = 6;
    abStack_20[4] = 7;
    abStack_20[5] = 2;
    abStack_20[6] = 5;
    sVar2 = *originalViability;
    iStack_34 = 0;
    sStack_22 = sVar2;
    do {
      stat = abStack_20[iStack_34];
      uVar4 = (uint)stat;
      iVar3 = (uint)(byte)gBattleMons[bankDef].statStages[uVar4 - 1] -
              (uint)(byte)gBattleMons[bankAtk].statStages[uVar4 - 1];
      if (0 < iVar3 * 0x1000000) {
        if (uVar4 == 1) {
          bVar1 = RealPhysicalMoveInMoveset(bankAtk);
          if (bVar1 == 0) {
LAB_090c6da8:
            if (((1 < uVar4 - 6) && (uVar4 != 3)) && (class != 5)) goto LAB_090c6db8;
          }
          else {
            stat = (byte)sVar2;
          }
        }
        else if ((uVar4 != 4) || (bVar1 = SpecialMoveInMoveset(bankAtk), bVar1 == 0))
        goto LAB_090c6da8;
        IncreaseStatViability(&sStack_22,class,(u8)iVar3,bankAtk,bankDef,0xf4,stat,8);
        break;
      }
LAB_090c6db8:
      iStack_34 = iStack_34 + 1;
    } while (iStack_34 != 7);
    sVar2 = MathMin((int)sStack_22,0xff);
    *originalViability = sVar2;
  }
  return;
}

// ---- IncreaseViabilityForSpeedControl  (ROM 0x90c6dd0)
bool8 IncreaseViabilityForSpeedControl(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef)

{
  s16 sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool8 bVar6;
  s16 asStack_1a [3];
  
  uVar5 = (uint)class;
  asStack_1a[0] = *originalViability;
  iVar2 = IsTrickRoomActive();
  if (iVar2 == 0) {
    uVar3 = SpeedCalc(bankDef);
    uVar4 = SpeedCalc((uint)bankAtk);
    if (uVar4 <= uVar3) {
LAB_090c6e14:
      if ((uVar5 == 0xf) || ((bVar6 = 0, 0xe < uVar5 && (uVar5 - 0x11 < 2)))) {
        IncreaseViability(asStack_1a,0xb);
        bVar6 = 1;
      }
      goto LAB_090c6dec;
    }
    uVar3 = bankAtk ^ 2;
    if (gBattleMons[uVar3].hp != 0) {
      uVar4 = SpeedCalc(bankDef);
      uVar3 = SpeedCalc(uVar3);
      if (uVar3 <= uVar4) goto LAB_090c6e14;
    }
  }
  bVar6 = 0;
LAB_090c6dec:
  sVar1 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar1;
  return bVar6;
}

// ---- IncreaseDoublesDamageViability  (ROM 0x90c6e5c)
void IncreaseDoublesDamageViability(s16 *originalViability,u8 class,u8 bankAtk,u8 bankDef,u16 move)

{
  u8 uVar1;
  s16 sVar2;
  uint uVar3;
  s16 sStack_12;
  
  uVar3 = (uint)class;
  sStack_12 = *originalViability;
  if (uVar3 == 0xff) {
    uVar3 = 0xb;
  }
  uVar1 = GetDoubleKillingScore(move,bankAtk,bankDef);
  IncreaseViability(&sStack_12,*(u8 *)((uVar3 - 0xb) * 0xd + 0x93504b0 + (uint)uVar1));
  sVar2 = MathMin((int)sStack_12,0xff);
  *originalViability = sVar2;
  return;
}

// ---- IncreaseDoublesDamageViabilityToScore  (ROM 0x90c6ea4)
void IncreaseDoublesDamageViabilityToScore
               (s16 *originalViability,u8 class,u8 score,u8 bankAtk,u8 bankDef)

{
  byte bankDef_00;
  bool8 bVar1;
  u16 move;
  s16 sVar2;
  u8 amount;
  uint uVar3;
  s16 asStack_1a [3];
  
  asStack_1a[0] = *originalViability;
  uVar3 = bankAtk ^ 2;
  if (gChosenMovesByBanks[uVar3] != 0) {
    move = GetAIChosenMove((u8)uVar3,bankDef);
    bankDef_00 = gBattleStruct->moveTarget[uVar3];
    if ((((uint)bankDef_00 == (uint)bankDef) && (bankDef_00 != uVar3)) &&
       (bVar1 = MoveKnocksOutXHits(move,(u8)uVar3,bankDef_00,1), bVar1 != 0)) {
      amount = *(u8 *)((class - 0xb) * 0xd + 0x93504b1);
      goto LAB_090c6f00;
    }
  }
  amount = *(u8 *)((class - 0xb) * 0xd + 0x93504b0 + (uint)score);
LAB_090c6f00:
  IncreaseViability(asStack_1a,amount);
  sVar2 = MathMin((int)asStack_1a[0],0xff);
  *originalViability = sVar2;
  return;
}
