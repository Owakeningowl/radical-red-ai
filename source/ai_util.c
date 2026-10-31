// ai_util.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- MoveCantHitTarget  (ROM 0x90d9db0)
bool8 MoveCantHitTarget(u16 move,u8 bankDef)

{
  byte bVar1;
  int iVar2;
  
  if (((((gStatuses3[bankDef] & 0x11000040) == 0) ||
       (iVar2 = CheckTableForMove(move,&UNK_0904020e), iVar2 == 0)) &&
      ((-1 < (int)(gStatuses3[bankDef] << 0x18) ||
       (iVar2 = CheckTableForMove(move,&UNK_0904021e), iVar2 == 0)))) &&
     ((-1 < (int)(gStatuses3[bankDef] << 0xd) ||
      (iVar2 = CheckTableForMove(move,&UNK_09040224), iVar2 == 0)))) {
    bVar1 = ((byte)(gStatuses3[bankDef] >> 0x18) & 3) >> 1;
  }
  else {
    bVar1 = 1;
  }
  return bVar1;
}

// ---- MoveAlwaysHitsTarget  (ROM 0x90d9e10)
bool8 MoveAlwaysHitsTarget(u16 move,u8 bankDef)

{
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = move;
  if ((((((int)(gStatuses3[bankDef] << 2) < 0) && (gBattleMoves[uVar2].effect != 0x26 /* EFFECT_0HKO */)) ||
       (gBattleMoves[uVar2].accuracy == 0)) ||
      ((((gBattleWeather & 0x1007) != 0 &&
        (iVar3 = CheckTableForMove(uVar2,&UNK_0904022a,gBattleWeather,0x1007,uVar2,(uint)bankDef),
        iVar3 != 0)) && (iVar3 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar3 == 0)))) ||
     (iVar3 = sub_90748d2(uVar2), iVar3 != 0)) {
    bVar1 = 1;
  }
  else {
    iVar3 = IsAnyMaxMove(uVar2);
    bVar1 = 1 - (iVar3 == 0);
  }
  return bVar1;
}

// ---- ShouldAIFreeChoiceLockWithDynamax  (ROM 0x90d9e94)
bool8 ShouldAIFreeChoiceLockWithDynamax(u8 bankAtk,u8 bankDef)

{
  u8 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  AIScript AStack_60;
  
  uVar2 = (uint)bankAtk;
  iVar3 = CanDynamax();
  if (((iVar3 != 0) &&
      (((iVar3 = GetBankItemEffect(uVar2), iVar3 == 0x1d ||
        (iVar3 = GetBankAbility(uVar2), iVar3 == 0xd7)) ||
       (iVar3 = GetBankAbility(uVar2), iVar3 == 0xff)))) &&
     ((ushort)(gBattleStruct->choicedMove[uVar2] - 1) < 0xfffe)) {
    uVar4 = CheckMoveLimitations(uVar2,0,3);
    Memset(&AStack_60,0,0x48);
    PopulateAIScriptStructWithBaseAttackerData(&AStack_60,bankAtk);
    PopulateAIScriptStructWithBaseDefenderData(&AStack_60,bankDef);
    uVar5 = 0;
    do {
      iVar3 = GetMaxMove(uVar2,uVar5 & 0xff);
      if (iVar3 == 0) {
        return 0;
      }
      if (((*(uint *)((uVar5 + 0x2097917) * 4) & uVar4) == 0) &&
         (uVar1 = AIScript_Negatives(bankAtk,bankDef,(u16)iVar3,100,&AStack_60), 99 < uVar1)) {
        return 1;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != 4);
  }
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
  return 0;
}

// ---- MoveWillHit  (ROM 0x90d9f90)
bool8 MoveWillHit(u16 move,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = (uint)bankDef;
  iVar2 = GetBankAbility(bankAtk);
  if (((iVar2 == 0x7e) || (iVar2 = GetBankAbility(uVar3), iVar2 == 0x7e)) ||
     (((gStatuses3[uVar3] & 0x18) != 0 && (gDisableStructs[uVar3].bankWithSureHit == bankAtk)))) {
    bVar4 = true;
  }
  else {
    bVar1 = MoveCantHitTarget(move,bankDef);
    bVar4 = false;
    if (bVar1 == 0) {
      bVar1 = MoveAlwaysHitsTarget(move,bankDef);
      bVar4 = true;
      if ((bVar1 == 0) && (bVar4 = false, move == 0x5c /* Toxic */)) {
        iVar2 = IsOfType(bankAtk,3 /* Poison */);
        bVar4 = iVar2 != 0;
      }
    }
  }
  return bVar4;
}

// ---- MonMoveWillHit  (ROM 0x90da00c)
bool8 MonMoveWillHit(u16 move,Pokemon *monAtk,u8 bankDef)

{
  bool8 bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = GetMonAbility(monAtk);
  if ((iVar2 == 0x7e) || (iVar2 = GetBankAbility(bankDef), iVar2 == 0x7e)) {
    bVar3 = true;
  }
  else {
    bVar1 = MoveCantHitTarget(move,bankDef);
    bVar3 = false;
    if (bVar1 == 0) {
      bVar1 = MoveAlwaysHitsTarget(move,bankDef);
      bVar3 = true;
      if ((bVar1 == 0) && (bVar3 = false, move == 0x5c /* Toxic */)) {
        iVar2 = sub_90c1df8(monAtk,3);
        bVar3 = iVar2 != 0;
      }
    }
  }
  return bVar3;
}

// ---- MoveWouldHitBeforeOtherMove  (ROM 0x90da062)
bool8 MoveWouldHitBeforeOtherMove(u16 moveAtk,u8 bankAtk,u16 moveDef,u8 bankDef)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (moveDef == 0) {
    iVar1 = PriorityCalc(bankAtk,0,moveAtk,bankDef,bankDef);
    if (0 < iVar1) {
      return 1;
    }
  }
  else {
    iVar1 = PriorityCalc(bankAtk,0,moveAtk,bankDef,bankDef);
    iVar2 = PriorityCalc(bankDef,0,moveDef);
    if (iVar2 < iVar1) {
      return 1;
    }
  }
  iVar1 = sub_906f140(bankAtk);
  iVar2 = sub_906f140(bankDef);
  if (iVar2 < iVar1) {
    return 1;
  }
  uVar3 = SpeedCalc(bankAtk);
  uVar4 = SpeedCalc(bankDef);
  iVar1 = IsTrickRoomActive();
  uVar5 = uVar4;
  if (iVar1 != 0) {
    uVar5 = uVar3;
    uVar3 = uVar4;
  }
  return uVar5 < uVar3;
}

// ---- MoveWouldHitFirst  (ROM 0x90da0d2)
bool8 MoveWouldHitFirst(u16 move,u16 bankAtk,u16 bankDef)

{
  bool8 bVar1;
  u16 moveDef;
  
  moveDef = *(u16 *)(gNewBS + ((bankDef & 0xff) * 4 + (bankAtk & 0xff) + 0xf4) * 2 + 6);
  if (moveDef == 0xffff) {
    moveDef = 0;
  }
  bVar1 = MoveWouldHitBeforeOtherMove(move,(u8)bankAtk,moveDef,(u8)bankDef);
  return bVar1;
}

// ---- IsBankAsleep  (ROM 0x90da168)
bool8 IsBankAsleep(u8 bank)

{
  return (gBattleMons[bank].status1 & 7) != 0 && gBattleMons[bank].status1 != 1;
}

// ---- IsUsefulToFlinchTarget  (ROM 0x90da18c)
bool8 IsUsefulToFlinchTarget(u8 bankDef)

{
  bool8 bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = IsDynamaxed();
  bVar3 = false;
  if (iVar2 == 0) {
    bVar1 = IsBankAsleep(bankDef);
    if ((bVar1 == 0) || (iVar2 = MoveInMoveset(0xd6 /* Sleep Talk */,bankDef), iVar2 != 0)) {
      bVar3 = true;
    }
    else {
      iVar2 = MoveInMoveset(0xad /* Snore */,bankDef);
      bVar3 = iVar2 != 0;
    }
  }
  return bVar3;
}

// ---- IsBankIncapacitated  (ROM 0x90da1c4)
bool8 IsBankIncapacitated(u8 bank)

{
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)bank;
  bVar1 = IsBankAsleep(bank);
  if ((bVar1 != 0) || ((int)(gBattleMons[uVar2].status2 << 9) < 0)) {
    return 1;
  }
  iVar3 = GetBankAbility(uVar2);
  if (iVar3 == 0x36) {
    return gDisableStructs[uVar2].field_0x18 & 1;
  }
  return 0;
}

// ---- WillFaintFromWeatherSoon  (ROM 0x90da23a)
bool8 WillFaintFromWeatherSoon(u8 bank)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = (uint)bank;
  iVar2 = sub_90a0f2e();
  if ((iVar2 == 0) && (iVar2 = sub_90a0f92(uVar3), iVar2 == 0)) {
    bVar4 = false;
  }
  else {
    uVar1 = gBattleMons[uVar3].hp;
    uVar3 = GetBaseMaxHP(uVar3);
    bVar4 = (uint)uVar1 <= (uVar3 >> 4 & 0xffff);
  }
  return bVar4;
}

// ---- WillTakeSignificantDamageFromEntryHazards  (ROM 0x90da278)
bool8 WillTakeSignificantDamageFromEntryHazards(u8 bank,u8 healthFraction)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = GetBattlerSide(bank);
  if ((int)((uint)gSideStatuses[iVar1] << 0x1b) < 0) {
    GetBankPartyData(bank);
    iVar1 = GetMonAbility();
    if ((iVar1 != 0x73) && (iVar1 = GetBankItemEffect(bank), iVar1 != 0x87)) {
      uVar2 = GetBankPartyData(bank);
      iVar1 = GetBattlerSide(bank);
      uVar5 = 0;
      if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar1 * 0xb] << 0x1b) < 0) {
        uVar5 = sub_90c0094(uVar2);
      }
      iVar1 = GetBattlerSide(bank);
      if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar1 * 0xb] << 0x19) < 0) {
        iVar1 = sub_90c0c1e(uVar2);
        uVar5 = uVar5 + iVar1;
      }
      iVar1 = GetBattlerSide(bank);
      if (((&gSideTimers[0].field_0xa)[iVar1 * 0xb] & 3) != 0) {
        uVar3 = GetBattlerSide(bank);
        iVar1 = sub_90bff90(uVar2,uVar3);
        uVar5 = uVar5 + iVar1;
      }
      uVar4 = sub_90739b4(bank);
      if (uVar5 < uVar4) {
        uVar2 = GetBaseMaxHP(bank);
        uVar4 = sub_900042a(uVar2,healthFraction);
        return uVar4 <= uVar5;
      }
      return 1;
    }
  }
  return 0;
}

// ---- CanBeFlinched  (ROM 0x90da350)
bool8 CanBeFlinched(u8 bankDef,u8 bankAtk,u8 defAbility,u16 move)

{
  bool8 bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = CanFlinch(bankDef,defAbility,defAbility,move,move);
  if ((((iVar2 == 0) || (defAbility == 0x13 /* Shield Dust */)) || (iVar2 = GetBankItemEffect(bankDef), iVar2 == 0x8e)
      ) || (bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar1 == 0)) {
    bVar3 = false;
  }
  else {
    iVar2 = MoveBlockedBySubstitute(move,bankAtk,bankDef);
    bVar3 = iVar2 == 0;
  }
  return bVar3;
}

// ---- CountBanksPositiveStatStages  (ROM 0x90da394)
u8 CountBanksPositiveStatStages(u8 bank)

{
  u8 uVar1;
  int iVar2;
  
  iVar2 = 1;
  uVar1 = 0;
  do {
    if (6 < gBattleMons[bank].statStages[iVar2 + -1]) {
      uVar1 = uVar1 + 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 8);
  return uVar1;
}

// ---- CountBanksNegativeStatStages  (ROM 0x90da3c4)
u8 CountBanksNegativeStatStages(u8 bank)

{
  u8 uVar1;
  int iVar2;
  
  iVar2 = 1;
  uVar1 = 0;
  do {
    if (gBattleMons[bank].statStages[iVar2 + -1] < 6) {
      uVar1 = uVar1 + 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 8);
  return uVar1;
}

// ---- GetPokemonOnSideSpeedAverage  (ROM 0x90da3f4)
u16 GetPokemonOnSideSpeedAverage(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  
  cVar4 = gBattleMons[bank].hp != 0;
  uVar2 = 0;
  if ((bool)cVar4) {
    uVar2 = SpeedCalc();
    uVar2 = uVar2 & 0xffff;
  }
  uVar3 = 0;
  if (gBattleTypeFlags << 0x1f < 0) {
    uVar3 = 0;
    if (gBattleMons[bank ^ 2].hp != 0) {
      uVar3 = SpeedCalc();
      cVar4 = cVar4 + '\x01';
      uVar3 = uVar3 & 0xffff;
    }
  }
  uVar1 = sub_900042a(uVar2 + uVar3,cVar4);
  return uVar1;
}

// ---- GetTeamMaxSpeed  (ROM 0x90da454)
u16 GetTeamMaxSpeed(u8 bank)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  undefined1 uStack_1a;
  undefined1 auStack_19 [5];
  
  uVar1 = (uint)bank;
  iVar2 = LoadPartyRange(uVar1,&uStack_1a,auStack_19);
  uVar6 = 0;
  uVar5 = GetBattlerSide(uVar1);
  uVar7 = 0;
  do {
    if ((*(short *)(iVar2 + 0x20) != 0) &&
       (iVar3 = GetMonData(iVar2,0x2d,0,&GetMonData), iVar3 == 0)) {
      if (gBattlerPartyIndexes[uVar1] == uVar7) {
        uVar4 = SpeedCalc(uVar1);
      }
      else {
        uVar4 = sub_9071268(uVar5,iVar2);
      }
      if (uVar6 < uVar4) {
        uVar6 = uVar4;
      }
    }
    uVar7 = uVar7 + 1;
    iVar2 = iVar2 + 100;
  } while (uVar7 != 6);
  if (0xffff < uVar6) {
    uVar6 = 0xffff;
  }
  return (u16)uVar6;
}

// ---- WillBeFasterAfterSpeedDrop  (ROM 0x90da4e6)
bool8 WillBeFasterAfterSpeedDrop(u8 bankAtk,u8 bankDef,u8 reduceBy)

{
  sbyte sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = (uint)reduceBy;
  uVar4 = (uint)bankDef;
  sVar1 = gBattleMons[uVar4].statStages[2];
  iVar2 = GetBankAbility(uVar4);
  if (iVar2 == 0x8c) {
    uVar5 = (uVar5 & 0x7f) << 1;
  }
  if ((int)gBattleMons[uVar4].statStages[2] < (int)uVar5) {
    gBattleMons[uVar4].statStages[2] = 0;
  }
  else {
    gBattleMons[uVar4].statStages[2] = gBattleMons[uVar4].statStages[2] - (char)uVar5;
  }
  uVar5 = SpeedCalc(bankAtk);
  uVar3 = SpeedCalc(uVar4);
  gBattleMons[uVar4].statStages[2] = sVar1;
  return uVar5 <= uVar3;
}

// ---- WillBeFasterAfterMoveSpeedBuff  (ROM 0x90da554)
bool8 WillBeFasterAfterMoveSpeedBuff(u8 bankAtk,u8 bankDef,u16 move)

{
  sbyte sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  uVar4 = move;
  uVar2 = (uint)bankAtk;
  sVar1 = gBattleMons[uVar2].statStages[2];
  iVar6 = 2;
  if ((((gBattleMoves[uVar4].effect != 0x34 /* EFFECT_SPEED_UP_2 */) && (uVar4 != 0x1c4)) && (uVar4 != 0x1dd)) &&
     ((iVar6 = 1, gBattleMoves[uVar4].effect == 0x8f /* EFFECT_PSYCH_UP */ && (uVar4 != 0x265)))) {
    iVar6 = (int)gBattleMons[bankDef].statStages[2] - (int)sVar1;
    iVar6 = (int)(char)((byte)iVar6 & (char)~(byte)((uint)iVar6 >> 0x18) >> 7);
  }
  iVar3 = GetBankAbility(uVar2);
  if (iVar3 == 0x8c) {
    iVar6 = (iVar6 << 0x19) >> 0x18;
  }
  iVar6 = gBattleMons[uVar2].statStages[2] + iVar6;
  if (0xc < iVar6) {
    iVar6 = 0xc;
  }
  gBattleMons[uVar2].statStages[2] = (sbyte)iVar6;
  uVar4 = SpeedCalc(uVar2);
  uVar5 = SpeedCalc((uint)bankDef);
  gBattleMons[uVar2].statStages[2] = sVar1;
  return uVar5 <= uVar4;
}

// ---- GetBattleMonMove  (ROM 0x90da604)
u16 GetBattleMonMove(u8 bank,u8 i)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)i;
  uVar1 = 0;
  if (uVar3 < 4) {
    uVar1 = gBattleMons[bank].moves[uVar3];
    iVar2 = IsDynamaxed();
    if (iVar2 != 0) {
      *(ushort *)(gNewBS + 0x1bc) = uVar1;
      uVar1 = GetMaxMove((uint)bank,uVar3);
    }
  }
  return uVar1;
}

// ---- GetMonAbilityAfterTrace  (ROM 0x90da64c)
u8 GetMonAbilityAfterTrace(Pokemon *mon,u8 foe)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  
  uVar2 = GetMonAbility(mon);
  if ((-1 < gBattleTypeFlags << 0x1f) && (uVar2 == 0x24)) {
    pbVar3 = (byte *)GetAbilityLocation(foe);
    bVar1 = *pbVar3;
    iVar4 = CheckTableForAbility((uint)bVar1,&UNK_0900a008);
    if (iVar4 == 0) {
      uVar2 = (uint)bVar1;
    }
  }
  return (u8)uVar2;
}

// ---- TryReplaceImposterAbility  (ROM 0x90da684)
u8 TryReplaceImposterAbility(u8 ability,u8 monBank)

{
  int iVar1;
  
  if ((ability == 0xc5) && (iVar1 = sub_9074a88(monBank,1), iVar1 != 0)) {
    sub_9074a2c(monBank);
    ability = GetBankAbility();
  }
  return ability;
}

// ---- IsDamagingMoveUnusableByMon  (ROM 0x90da6aa)
bool8 IsDamagingMoveUnusableByMon(u16 move,Pokemon *monAtk,u8 bankDef)

{
  byte bVar1;
  ushort uVar2;
  u8 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined *puVar8;
  uint uVar9;
  
  uVar9 = (uint)bankDef;
  uVar4 = move;
  uVar3 = GetMonAbilityAfterTrace(monAtk,bankDef);
  if ((uVar3 != 0x98) && (iVar5 = CheckTableForMove(uVar4,&UNK_09040136), iVar5 == 0)) {
    uVar6 = GetBankAbility(uVar9);
    if (uVar6 == 0x50) goto LAB_090da7b8;
    if (uVar6 < 0x51) {
      if (uVar6 == 0x10) {
        puVar8 = &UNK_0903ff9e;
LAB_090da7ea:
        iVar5 = CheckTableForMove(uVar4,puVar8);
LAB_090da7e0:
        if (iVar5 != 0) {
          return 1;
        }
      }
      else if (uVar6 < 0x11) {
        if (uVar6 == 10) {
LAB_090da7b8:
          iVar5 = sub_908367c(monAtk,uVar4);
          if (iVar5 == 0xd) {
            return 1;
          }
        }
        else if (uVar6 == 0xb) goto LAB_090da790;
      }
      else {
        if (uVar6 == 0x1f) goto LAB_090da7b8;
        if (uVar6 == 0x2b) {
          iVar5 = sub_9073ba8(uVar4);
          goto LAB_090da7e0;
        }
        if (uVar6 == 0x12) goto LAB_090da76e;
      }
    }
    else if (uVar6 == 0x83) {
LAB_090da790:
      iVar5 = sub_908367c(monAtk,uVar4);
      if (iVar5 == 0xb) {
        return 1;
      }
    }
    else if (uVar6 < 0x84) {
      if (uVar6 == 0x71) {
        iVar5 = sub_908367c(monAtk,uVar4);
        if (iVar5 == 0xc) {
          return 1;
        }
      }
      else {
        puVar8 = &UNK_0903ff64;
        if (uVar6 == 0x74) goto LAB_090da7ea;
        if (uVar6 == 0x62) goto LAB_090da790;
      }
    }
    else if (uVar6 == 0xdd) {
      iVar5 = sub_906f0b8(monAtk,uVar4);
      if (0 < iVar5) {
        return 1;
      }
    }
    else if (uVar6 == 0xfe) {
LAB_090da76e:
      iVar5 = sub_908367c(monAtk,uVar4);
      if (iVar5 == 10) {
        return 1;
      }
    }
    else if ((uVar6 == 0xbc) && (iVar5 = sub_908367c(monAtk,uVar4), iVar5 == 4)) {
      return 1;
    }
  }
  bVar1 = gBattleMoves[uVar4].effect;
  if (bVar1 == 0x7d) {
    iVar5 = sub_90c1df8(monAtk,10);
    if (iVar5 == 0) {
      return 1;
    }
    goto LAB_090da708;
  }
  if (bVar1 < 0x7e) {
    if (bVar1 != 0x26) {
      if (bVar1 == 0x59) {
        return 1;
      }
      goto LAB_090da708;
    }
    uVar6 = GetMonData(monAtk,0x38,0);
    if (uVar6 < gBattleMons[uVar9].level) {
      return 1;
    }
    if (uVar4 != 0x149) goto LAB_090da708;
    iVar5 = IsOfType(uVar9,0xf /* Ice */);
  }
  else {
    if (bVar1 == 0x90) {
      return 1;
    }
    if (bVar1 != 0xb9) goto LAB_090da708;
    uVar2 = gBattleMons[uVar9].item;
    uVar7 = GetBankAbility(uVar9);
    iVar5 = sub_907659c(uVar2,uVar7);
  }
  if (iVar5 != 0) {
    return 1;
  }
LAB_090da708:
  iVar5 = IsDynamaxed(uVar9);
  if ((((iVar5 != 0) && (iVar5 = CheckTableForMove(uVar4,&UNK_0903fcee), iVar5 != 0)) ||
      (((int)((uint)gBattleWeather << 0x14) < 0 &&
       (iVar5 = sub_908367c(monAtk,uVar4), iVar5 == 0xb)))) ||
     (((int)((uint)gBattleWeather << 0x13) < 0 && (iVar5 = sub_908367c(monAtk,uVar4), iVar5 == 10))
     )) {
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
    return 1;
  }
  if (gTerrainType != '\x04') {
    return 0;
  }
  iVar5 = CheckGrounding(uVar9);
  if (iVar5 == 1) {
    iVar5 = sub_906f0b8(monAtk,uVar4);
    return (byte)((uint)((iVar5 >> 0x1f) - iVar5) >> 0x1f);
  }
  return 0;
}

// ---- GetFinalAIMoveDamageFromParty  (ROM 0x90da8a4)
u16 GetFinalAIMoveDamageFromParty(u16 move,Pokemon *monAtk,u8 bankDef,void *damageData)

{
  bool8 bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  uint uStack_20;
  uint auStack_1c [2];
  
  uVar6 = (uint)bankDef;
  uVar2 = move;
  GetMonIdAndSideByMon(monAtk,&uStack_20,auStack_1c);
  uVar3 = sub_90c1c9c(uVar2,monAtk);
  if ((((uStack_20 < 6) && (auStack_1c[0] < 2)) && (uVar3 < 4)) &&
     (uVar4 = *(uint *)(gNewBS + (((auStack_1c[0] * 6 + uStack_20) * 4 + uVar6) * 4 + uVar3 + 0xfa)
                                 * 4 + 8), uVar4 != 0xffffffff)) goto LAB_090da92e;
  if (uVar2 == 0) {
LAB_090da8fe:
    uVar4 = 0;
  }
  else {
    if (((gBattleMoves[uVar2].split == 2) || (gBattleMoves[uVar2].power == 0)) ||
       (bVar1 = IsDamagingMoveUnusableByMon(move,monAtk,bankDef), bVar1 != 0)) goto LAB_090da8fe;
    if (gBattleMoves[uVar2].effect == 0x26 /* EFFECT_0HKO */) {
      iVar7 = IsPlayerInControl(uVar6);
      if (iVar7 == 0) {
        bVar1 = MonMoveWillHit(move,monAtk,bankDef);
        if (bVar1 == 0) {
          uVar4 = 1;
          goto LAB_090da900;
        }
      }
      uVar4 = (uint)gBattleMons[uVar6].hp;
    }
    else {
      uVar5 = sub_9086dd8(~uVar6 & 1,uVar6,uVar2,monAtk,damageData);
      uVar5 = TryAdjustDamageForRaidBoss(uVar6,uVar5);
      uVar4 = MathMin(uVar5,gBattleMons[uVar6].maxHP);
      uVar4 = uVar4 & 0xffff;
    }
  }
LAB_090da900:
  uVar2 = gNewBS;
  iVar7 = ((auStack_1c[0] * 6 + uStack_20) * 4 + uVar6) * 4;
  *(uint *)(gNewBS + (iVar7 + uVar3 + 0xfa) * 4 + 8) = uVar4;
  iVar7 = uVar2 + iVar7;
  if (*(uint *)(iVar7 + 0x6f0) < uVar4) {
    *(uint *)(iVar7 + 0x6f0) = uVar4;
  }
LAB_090da92e:
  return (u16)uVar4;
}

// ---- MoveKnocksOutFromParty  (ROM 0x90da9d0)
bool8 MoveKnocksOutFromParty(u16 move,Pokemon *monAtk,u8 bankDef,void *damageData)

{
  ushort uVar1;
  u8 uVar2;
  u16 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  
  uVar7 = (uint)bankDef;
  if (damageData == (void *)0x0) {
    uVar2 = GetMonAbilityAfterTrace(monAtk,bankDef);
  }
  else {
    uVar2 = *(u8 *)((int)damageData + 0x10);
  }
  uVar4 = GetBankAbility(uVar7);
  uVar1 = gBattleMons[uVar7].species;
  bVar8 = false;
  if (uVar2 != 0x98) {
    iVar5 = CheckTableForMove(move,&UNK_09040136);
    bVar8 = iVar5 == 0;
  }
  iVar5 = MonMoveBlockedBySubstitute(move,monAtk,uVar7);
  if (iVar5 == 0) {
    if (bVar8) {
      uVar6 = CalcMoveSplitFromParty(monAtk,move);
      iVar5 = IsAffectedByDisguse(uVar4,uVar1,uVar6);
      if (iVar5 != 0) goto LAB_090daa1e;
    }
    uVar3 = GetFinalAIMoveDamageFromParty(move,monAtk,bankDef,damageData);
    bVar8 = gBattleMons[uVar7].hp <= uVar3;
  }
  else {
LAB_090daa1e:
    bVar8 = false;
  }
  return bVar8;
}

// ---- CanKnockOutFromParty  (ROM 0x90daa78)
bool8 CanKnockOutFromParty(Pokemon *monAtk,u8 bankDef,void *damageData)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  uVar3 = GetMonData(monAtk,0x37,0);
  bVar5 = false;
  if (damageData != (void *)0x0) {
    bVar5 = *(char *)((int)damageData + 0x54) != '\0';
  }
  if ((*(uint *)(&gBitTable + (uint)bankDef * 4) & (uint)gAbsentBattlerFlags) == 0) {
    uVar2 = CheckMoveLimitationsFromParty(monAtk,0,0xff);
    iVar4 = 0;
    do {
      if (bVar5) {
        move = GetBattleMonMove(*(u8 *)((int)damageData + 0x52),(u8)iVar4);
      }
      else {
        move = GetMonData(monAtk,iVar4 + 0xd,0,&GetMonData);
      }
      if (move == 0 /* - */) {
        return 0;
      }
      if (((((uVar3 & 7) == 0) || (move == 0xad /* Snore */)) &&
          ((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0)) &&
         (bVar1 = MoveKnocksOutFromParty(move,monAtk,bankDef,damageData), bVar1 != 0)) {
        return 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
  }
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
  return 0;
}

// ---- IsStatRecoilMove  (ROM 0x90dab2c)
bool8 IsStatRecoilMove(u16 move)

{
  bool8 bVar1;
  
  if ((gBattleMoves[move].effect == 0xb6 /* EFFECT_SUPERPOWER */) || (bVar1 = 0, gBattleMoves[move].effect == 0xcc /* EFFECT_OVERHEAT */)) {
    bVar1 = 1;
  }
  return bVar1;
}

// ---- GetMonPassiveRecovery  (ROM 0x90dab4c)
s32 GetMonPassiveRecovery(Pokemon *mon,u8 bank)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = GetMonAbility(mon,bank);
  iVar2 = sub_9074de4(mon);
  uVar5 = GetMonData(mon,0x3a,0);
  uVar6 = uVar5 & 0xffff;
  if (iVar2 == 0x2b) {
LAB_090dab78:
    iVar3 = MathMax(1,(uVar5 & 0xffff) >> 4);
  }
  else {
    iVar3 = 0;
    if (iVar2 == 0x4d) {
      iVar3 = sub_90c1df8(mon,3);
      if (iVar3 != 0) goto LAB_090dab78;
      iVar3 = MathMax(1,(uVar5 & 0xffff) >> 3);
      iVar3 = -iVar3;
    }
  }
  if ((((gBattleWeather & 0x1007) != 0) &&
      (iVar4 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar4 == 0)) &&
     (iVar2 = sub_9076620(iVar2), iVar2 == 0)) {
    if (uVar1 == 0x2c) {
      uVar5 = uVar6 >> 4;
    }
    else {
      if (uVar1 != 0x62) goto LAB_090dabb8;
      uVar5 = uVar6 >> 3;
    }
    iVar2 = MathMax(1,uVar5);
    iVar3 = iVar3 + iVar2;
  }
LAB_090dabb8:
  if ((((gBattleWeather & 0x860) != 0) &&
      (iVar2 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar2 == 0)) && ((uVar1 & 0xfd) == 0x60)) {
    iVar2 = MathMax(1,uVar6 >> 3);
    iVar3 = iVar3 - iVar2;
  }
  if ((((gBattleWeather & 0x180) == 0) ||
      (iVar2 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar2 != 0)) || (uVar1 != 0x69)) {
    if ((uVar1 != 0x68) || (uVar1 = sub_203e028(mon,0x37,0,&GetMonData), (uVar1 & 0x88) == 0))
    goto LAB_090dac14;
    uVar1 = uVar6 >> 3;
  }
  else {
    uVar1 = uVar6 >> 4;
  }
  iVar2 = MathMax(1,uVar1);
  iVar3 = iVar3 + iVar2;
LAB_090dac14:
  if ((gTerrainType == '\x02') && (iVar2 = sub_90751c8(mon), iVar2 == 1)) {
    iVar2 = MathMax(1,uVar6 >> 4);
    iVar3 = iVar3 + iVar2;
  }
  return iVar3;
}

// ---- GetAIChosenMove  (ROM 0x90dac90)
u16 GetAIChosenMove(u8 bankAtk,u8 bankDef)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  u16 uVar4;
  
  uVar2 = (uint)bankAtk;
  uVar1 = gChosenMovesByBanks[uVar2];
  if (uVar1 == 0) {
    uVar4 = *(u16 *)(gNewBS + (uVar2 * 4 + (uint)bankDef + 0xf4) * 2 + 6);
    if (uVar4 == 0xffff) {
      uVar4 = 0;
    }
  }
  else {
    if (*(char *)(gNewBS + uVar2 + 400) == '\0') {
      iVar3 = IsDynamaxed();
      if ((iVar3 == 0) && (*(char *)(gNewBS + uVar2 + 0x19e) == '\0')) {
        return uVar1;
      }
      iVar3 = GetMaxMoveByMove(uVar2,uVar1);
      if (iVar3 == 0) {
        return uVar1;
      }
    }
    else {
      iVar3 = ReplaceWithZMoveRuntime(uVar2,uVar1);
    }
    uVar4 = (u16)iVar3;
  }
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return uVar4;
}

// ---- IsTrapped  (ROM 0x90dad00)
bool8 IsTrapped(u8 bank,bool8 switching)

{
  uint uVar1;
  int iVar2;
  undefined4 in_r2;
  undefined4 in_r3;
  
  uVar1 = (uint)bank;
  iVar2 = IsOfType(uVar1,7 /* Ghost */,in_r2,in_r3,uVar1,switching);
  if (iVar2 == 0) {
    if (switching == 0) {
      iVar2 = GetBankAbility(uVar1);
      if ((iVar2 != 0x32) && (iVar2 = GetBankItemEffect(uVar1), iVar2 != 0x25)) goto LAB_090dad22;
    }
    else {
      iVar2 = GetBankItemEffect();
      if (iVar2 != 0x73) {
LAB_090dad22:
        if (((((gBattleMons[uVar1].status2 & 0x400e000) == 0) &&
             ((iVar2 = AbilityBattleEffects(0xc,uVar1,0x17,0,0), iVar2 == 0 ||
              (iVar2 = GetBankAbility(uVar1), iVar2 == 0x17)))) &&
            ((iVar2 = AbilityBattleEffects(0xc,uVar1,0x47,0,0), iVar2 == 0 ||
             (iVar2 = CheckGrounding(uVar1), iVar2 != 1)))) &&
           (((iVar2 = AbilityBattleEffects(0xc,uVar1,0x2a,0,0), iVar2 == 0 ||
             (iVar2 = IsOfType(uVar1,8 /* Steel */), iVar2 == 0)) && ((gStatuses3[uVar1] & 0x10000400) == 0))))
        {
          iVar2 = sub_9075264();
          return 1 - (iVar2 == 0);
        }
        return 1;
      }
    }
  }
  return 0;
}

// ---- ShouldUseHumanLikelyMove  (ROM 0x90dadcc)
bool8 ShouldUseHumanLikelyMove(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  iVar2 = IsPlayerInControl(bankAtk);
  if ((iVar2 == 0) && (bVar1 = IsTrapped(bankDef,1), bVar1 == 0)) {
    uVar3 = ViableMonCountFromBankLoadPartyRange(bankDef);
    bVar4 = uVar3 < 2;
  }
  else {
    bVar4 = true;
  }
  return bVar4;
}

// ---- GetSecondaryEffectDamage  (ROM 0x90dadf8)
u32 GetSecondaryEffectDamage(u8 bank)

{
  uint uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  uVar1 = (uint)bank;
  iVar16 = gNewBS + uVar1 * 4;
  uVar2 = *(u32 *)(iVar16 + 0x810);
  if (uVar2 == 0xffffffff) {
    iVar3 = GetBankAbility(uVar1);
    iVar17 = 0;
    if (iVar3 != 0x73) {
      if (UNK_02023f48 != '\x01') {
        iVar17 = sub_90a0fc8(uVar1);
      }
      if ((gBattleMons[uVar1].status1 & 7) != 1) {
        iVar3 = func_0x09090eb0(uVar1);
        iVar17 = iVar17 + iVar3;
      }
      iVar3 = func_0x09090f28(uVar1);
      iVar4 = GetBadDreamsDamage(uVar1);
      iVar5 = GetPoisonDamage(uVar1);
      iVar6 = sub_9090dac(uVar1);
      iVar7 = sub_9090df8(uVar1);
      iVar8 = sub_9090e6c(uVar1);
      iVar9 = func_0x09090ef0(uVar1);
      iVar10 = GetSeaOfFireDamage(uVar1);
      iVar11 = sub_9090fba(uVar1);
      iVar12 = GetGMaxVineLashDamage(uVar1);
      iVar13 = GetGMaxWildfireDamage(uVar1);
      iVar14 = GetGMaxCannonadeDamage(uVar1);
      iVar15 = sub_9091092(uVar1);
      iVar17 = iVar14 + iVar13 + iVar12 + iVar11 + iVar10 + iVar9 + iVar8 + iVar4 + iVar3 + iVar17 +
                                                                            iVar5 + iVar6 + iVar7 +
               iVar15;
    }
    *(int *)(iVar16 + 0x810) = iVar17;
    uVar2 = *(u32 *)(gNewBS + (uVar1 + 0x202) * 4 + 8);
  }
  return uVar2;
}

// ---- IsTakingSecondaryDamage  (ROM 0x90daf00)
bool8 IsTakingSecondaryDamage(u8 bank,bool8 checkConfusion)

{
  u32 uVar1;
  
  uVar1 = GetSecondaryEffectDamage(bank);
  return 1 - (uVar1 == 0);
}

// ---- WillFaintFromSecondaryDamage  (ROM 0x90daf5c)
bool8 WillFaintFromSecondaryDamage(u8 bank)

{
  ushort uVar1;
  u16 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  bool bVar16;
  
  uVar3 = (uint)bank;
  uVar1 = gBattleMons[uVar3].hp;
  uVar2 = GetAmountToRecoverBy(bank,0,0xb6);
  iVar4 = GetBankAbility(uVar3);
  if (((int)(gStatuses3[uVar3] << 0x1a) < 0) && ((gDisableStructs[uVar3].field_0xf & 0xf) == 0)) {
    return 1;
  }
  bVar16 = false;
  if (iVar4 != 0x73) {
    iVar4 = 0;
    if (UNK_02023f48 != '\x01') {
      iVar4 = sub_90a0fc8(uVar3);
    }
    if ((gBattleMons[uVar3].status1 & 7) != 1) {
      iVar5 = func_0x09090eb0(uVar3);
      iVar4 = iVar4 + iVar5;
    }
    if ((*(uint *)(&gBitTable + uVar3 * 4) & (uint)*(byte *)(gNewBS + 0xc3)) == 0) {
      iVar5 = func_0x09090f28(uVar3);
      iVar4 = iVar4 + iVar5;
    }
    iVar5 = GetBadDreamsDamage(uVar3);
    iVar6 = GetPoisonDamage(uVar3);
    iVar7 = sub_9090dac(uVar3);
    iVar8 = sub_9090e6c(uVar3);
    iVar9 = func_0x09090ef0(uVar3);
    iVar10 = GetSeaOfFireDamage(uVar3);
    iVar11 = GetGMaxVineLashDamage(uVar3);
    iVar12 = GetGMaxWildfireDamage(uVar3);
    iVar13 = GetGMaxCannonadeDamage(uVar3);
    iVar14 = sub_9090df8(uVar3);
    iVar15 = sub_9091092(uVar3);
    bVar16 = ((uint)uVar1 + (uint)uVar2 & 0xff) <=
             (uint)(iVar5 + iVar4 + iVar6 + iVar7 + iVar8 + iVar9 + iVar10 + iVar11 + iVar12 +
                    iVar13 + iVar14 + iVar15);
  }
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return bVar16;
}

// ---- GetContactDamage  (ROM 0x90db070)
u32 GetContactDamage(u16 move,u16 bankAtk,u16 bankDef)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  u32 uVar5;
  ushort uVar6;
  
  uVar4 = bankAtk & 0xff;
  uVar6 = bankDef & 0xff;
  iVar1 = MoveBlockedBySubstitute(move,uVar4,uVar6);
  if ((((iVar1 == 0) && (iVar1 = sub_9075008(uVar4), iVar1 == 0)) &&
      (iVar1 = GetBankAbility(uVar4), iVar1 != 0x73)) &&
     ((iVar1 = CheckTableForMove(move,&UNK_0903fe9a), iVar1 == 0 ||
      (iVar1 = GetBankItemEffect(uVar4), iVar1 != 0x8a)))) {
    iVar1 = GetBankAbility(uVar6);
    iVar2 = GetBankItemEffect(uVar6);
    uVar3 = GetBaseMaxHP(uVar4);
    uVar5 = 0;
    if (iVar1 == 0x7b) {
      uVar5 = uVar3 >> 3 & 0xffff;
    }
    if (iVar2 == 0x44) {
      uVar3 = __udivsi3(uVar3,6);
      uVar5 = uVar5 + (uVar3 & 0xffff);
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

// ---- GetContactDamageMonDef  (ROM 0x90db144)
u32 GetContactDamageMonDef(u16 bankAtk,Pokemon *monDef)

{
  u8 uVar1;
  int iVar2;
  uint uVar3;
  u32 uVar4;
  ushort uVar5;
  
  uVar5 = bankAtk & 0xff;
  iVar2 = sub_9075008(uVar5);
  if ((iVar2 == 0) && (iVar2 = GetBankAbility(uVar5), iVar2 != 0x73)) {
    uVar1 = GetMonAbilityAfterTrace(monDef,(u8)bankAtk);
    iVar2 = sub_9074de4(monDef);
    uVar3 = GetBaseMaxHP(uVar5);
    uVar4 = 0;
    if (uVar1 == 0x7b) {
      uVar4 = uVar3 >> 3 & 0xffff;
    }
    if (iVar2 == 0x44) {
      uVar3 = __udivsi3(uVar3,6);
      uVar4 = uVar4 + (uVar3 & 0xffff);
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

// ---- HighChanceOfBeingImmobilized  (ROM 0x90db19a)
bool8 HighChanceOfBeingImmobilized(u8 bank)

{
  u32 uVar1;
  u16 in_r1;
  u16 in_r2;
  
  uVar1 = GetContactDamage(in_r2,(ushort)bank,in_r1);
  return gBattleMons[bank].hp <= uVar1;
}

// ---- CalcSecondaryEffectChance  (ROM 0x90db220)
u16 CalcSecondaryEffectChance(u8 bank,u16 move,u8 ability)

{
  byte bVar1;
  int iVar2;
  u16 uVar3;
  
  bVar1 = gBattleMoves[move].secondaryEffectChance;
  uVar3 = (u16)bVar1;
  iVar2 = GetBankAbility();
  if ((iVar2 == 0x5c) && (iVar2 = CheckTableForMove(move,&UNK_0903fcfe), iVar2 != 0)) {
    uVar3 = 0;
  }
  else {
    iVar2 = GetBankAbility(bank);
    if ((iVar2 == 0x20) || (iVar2 = sub_9075444(bank), iVar2 != 0)) {
      uVar3 = (ushort)bVar1 << 1;
    }
  }
  return uVar3;
}

// ---- CalcAIAccuracy  (ROM 0x90db270)
u16 CalcAIAccuracy(u16 move,u8 bankAtk,u8 bankDef)

{
  byte bVar1;
  u16 uVar2;
  uint uVar3;
  
  uVar3 = move;
  uVar2 = AccuracyCalc(uVar3,bankAtk,bankDef);
  bVar1 = gBattleMoves[uVar3].effect;
  if (bVar1 == 0x50) {
    uVar2 = 0x31;
  }
  else if ((bVar1 == 0x1b) || (bVar1 == 0x75)) {
    uVar2 = uVar2 - 1;
  }
  else {
    if (uVar3 != 0x1ef) {
      return uVar2;
    }
    uVar2 = uVar2 - 5;
  }
  return uVar2;
}

// ---- ShouldPredictBankToMegaEvolve  (ROM 0x90db2b0)
bool8 ShouldPredictBankToMegaEvolve(u8 bank)

{
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = (uint)bank;
  iVar3 = IsPlayerInControl();
  if (iVar3 == 0) {
LAB_090db2bc:
    bVar1 = 1;
  }
  else {
    if (((1 < gBattleMons[uVar2].species - 0x437) &&
        ((int)(gBattleResources->ai->aiFlags << 0x1d) < 0)) &&
       (gDisableStructs[uVar2].isFirstTurn != 0)) {
      iVar3 = sub_90a9430((uint)gBattleMons[uVar2].species,gBattleMons[uVar2].item,
                          uVar2 * 0x58 + 0x2023bf0);
      if ((iVar3 == 0) || (iVar4 = sub_909ad90(), iVar4 != 0)) goto LAB_090db2bc;
      if ((&UNK_097b98f2)[iVar3 * 0x1c] == gBattleMons[uVar2].type1) {
        return (&UNK_097b98f3)[iVar3 * 0x1c] == gBattleMons[uVar2].type2;
      }
    }
    bVar1 = 0;
  }
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
  return bVar1;
}

// ---- BadIdeaToPutToSleep  (ROM 0x90db378)
bool8 BadIdeaToPutToSleep(u8 bankDef,u8 bankAtk)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = GetBankAbility();
  iVar2 = CanBePutToSleep((uint)bankDef,1,bankAtk);
  bVar3 = true;
  if ((((iVar2 != 0) && ((gStatuses3[bankDef] & 0x1800) == 0)) && (iVar1 != 0x30)) &&
     (iVar1 != 0x3d)) {
    if (iVar1 == 0x1c) {
      iVar1 = sub_90763c6(bankAtk);
    }
    else {
      if (iVar1 != 0x6b) {
        return 0;
      }
      if ((gBattleWeather & 0x1007) == 0) {
        return 0;
      }
      iVar1 = UNK_02023f48 - 1;
    }
    bVar3 = iVar1 != 0;
  }
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
  return bVar3;
}

// ---- IsValidMovePrediction  (ROM 0x90db402)
move_t IsValidMovePrediction(u8 bankAtk,u8 bankDef)

{
  move_t mVar1;
  
  mVar1 = *(move_t *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef + 0xf4) * 2 + 6);
  if (mVar1 == 0xffff) {
    mVar1 = 0;
  }
  return mVar1;
}

// ---- IsPredictedToSwitch  (ROM 0x90db424)
bool8 IsPredictedToSwitch(u8 bankAtk,u8 bankDef)

{
  return *(short *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef + 0xf4) * 2 + 6) == -1;
}

// ---- StoreSwitchPrediction  (ROM 0x90db460)
void StoreSwitchPrediction(u8 bankAtk,u8 bankDef)

{
  *(undefined2 *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef + 0xf4) * 2 + 6) = 0xffff;
  return;
}

// ---- MoveInMovesetAndUsable  (ROM 0x90db690)
bool8 MoveInMovesetAndUsable(u16 move,u8 bank)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = FindMovePositionInMoveset(move);
  bVar3 = false;
  if (uVar1 < 4) {
    uVar2 = *(uint *)(&gBitTable + uVar1 * 4);
    uVar1 = CheckMoveLimitations(bank,0,0xff);
    bVar3 = (uVar2 & uVar1) == 0;
  }
  return bVar3;
}

// ---- DamagingMoveInMoveset  (ROM 0x90db6c0)
bool8 DamagingMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar4);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) && (gBattleMoves[uVar3].split != 2))
        && (gBattleMoves[uVar3].power != 0)) &&
       ((gBattleMoves[uVar3].effect != 0x59 /* EFFECT_COUNTER */ && (gBattleMoves[uVar3].effect != 0x90 /* EFFECT_MIRROR_COAT */)))) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- PhysicalMoveInMoveset  (ROM 0x90db720)
bool8 PhysicalMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (iVar4 = CalcMoveSplit(bank,uVar3), iVar4 == 0)) && (gBattleMoves[uVar3].power != 0)) &&
       (gBattleMoves[uVar3].effect != 0x59 /* EFFECT_COUNTER */)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- GoodIdeaToParalyzeSelf  (ROM 0x90db784)
bool8 GoodIdeaToParalyzeSelf(u8 bankAtk)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar2 = GetBankAbility();
  iVar3 = CanBeParalyzed(bankAtk,0);
  bVar4 = false;
  if (iVar3 != 0) {
    if ((((iVar2 == 0x3f) || (iVar2 == 0x70)) ||
        ((iVar2 == 0x3e && (bVar1 = PhysicalMoveInMoveset(bankAtk), bVar1 != 0)))) ||
       (iVar2 = MoveInMoveset(0x107 /* Facade */,bankAtk), iVar2 != 0)) {
      bVar4 = true;
    }
    else {
      iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,bankAtk);
      bVar4 = iVar2 != 0;
    }
  }
  return bVar4;
}

// ---- BadIdeaToParalyze  (ROM 0x90db7dc)
bool8 BadIdeaToParalyze(u8 bankDef,u8 bankAtk)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = GetBankItemEffect();
  iVar3 = GetBankAbility(bankDef);
  iVar4 = CanBeParalyzed(bankDef,1);
  if (iVar4 == 0) {
    return 1;
  }
  if (iVar2 == 2) {
    return 1;
  }
  if (iVar2 == 9) {
    return 1;
  }
  if (iVar3 == 0x3d) {
    return 1;
  }
  if (iVar3 == 0x70) {
    return 1;
  }
  if (iVar3 == 0x1c) {
    iVar2 = CanBeParalyzed(bankAtk,1);
    if ((iVar2 != 0) && (bVar1 = GoodIdeaToParalyzeSelf(bankAtk), bVar1 == 0)) {
      return 1;
    }
    goto LAB_090db82a;
  }
  if (iVar3 != 0x3f) {
    if (iVar3 == 0x1e) {
      bVar1 = IsTrapped(bankDef,1);
      if (bVar1 == 0) {
        if ((-1 < gBattleTypeFlags << 0x1f) &&
           (uVar5 = ViableMonCountFromBankLoadPartyRange(bankDef), 1 < uVar5)) {
          return 1;
        }
        if ((gBattleTypeFlags << 0x1f < 0) &&
           (uVar5 = ViableMonCountFromBankLoadPartyRange(bankDef), 2 < uVar5)) {
          return 1;
        }
      }
      goto LAB_090db82a;
    }
    bankAtk = bankDef;
    if (iVar3 != 0x3e) {
      if (((iVar3 == 0x6b) && ((gBattleWeather & 0x1007) != 0)) && (UNK_02023f48 != '\x01')) {
        return 1;
      }
      goto LAB_090db82a;
    }
  }
  bVar1 = PhysicalMoveInMoveset(bankAtk);
  if (bVar1 != 0) {
    return 1;
  }
LAB_090db82a:
  iVar2 = MoveInMoveset(0x107 /* Facade */,bankDef);
  if (iVar2 == 0) {
    iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,bankDef);
    return 1 - (iVar2 == 0);
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
  return 1;
}

// ---- GoodIdeaToPoisonSelf  (ROM 0x90db8c0)
bool8 GoodIdeaToPoisonSelf(u8 bankAtk)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar2 = GetBankAbility();
  iVar3 = CanBePoisoned(bankAtk,bankAtk,0);
  bVar4 = false;
  if (iVar3 != 0) {
    if (((((iVar2 == 0x3f) || ((iVar2 - 0x68U & 0xf7) == 0)) || (iVar2 == 0x73)) ||
        (((iVar2 == 0x92 || (iVar2 == 0x3e)) && (bVar1 = PhysicalMoveInMoveset(bankAtk), bVar1 != 0)
         ))) || (iVar2 = MoveInMoveset(0x107 /* Facade */,bankAtk), iVar2 != 0)) {
      bVar4 = true;
    }
    else {
      iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,bankAtk);
      bVar4 = iVar2 != 0;
    }
  }
  return bVar4;
}

// ---- RealPhysicalMoveInMoveset  (ROM 0x90db99c)
bool8 RealPhysicalMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (iVar4 = CalcMoveSplit(bank,uVar3), iVar4 == 0)) && (gBattleMoves[uVar3].power != 0)) &&
       (((gBattleMoves[uVar3].effect != 0x59 /* EFFECT_COUNTER */ && (uVar3 != 0xfc)) &&
        ((uVar3 != 0x217 && (uVar3 != 0x2b4)))))) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- SpecialMoveInMoveset  (ROM 0x90dba64)
bool8 SpecialMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (iVar4 = CalcMoveSplit(bank,uVar3), iVar4 == 1)) && (gBattleMoves[uVar3].power != 0)) &&
       (gBattleMoves[uVar3].effect != 0x90 /* EFFECT_MIRROR_COAT */)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- CountUsefulStatChanges  (ROM 0x90dbac8)
u8 CountUsefulStatChanges(u8 bankWithBuffs,u8 bankToGetBuffs,bool8 debuff)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  bVar8 = false;
  if (debuff == 0) {
    bVar1 = MoveInMovesetAndUsable(0x1e2 /* Stored Power */,bankToGetBuffs);
    bVar8 = true;
    if (bVar1 == 0) {
      bVar1 = MoveInMovesetAndUsable(0x25a /* Power Trip */,bankToGetBuffs);
      bVar8 = bVar1 != 0;
    }
  }
  uVar7 = 1;
  uVar4 = 0;
  do {
    uVar5 = (byte)gBattleMons[bankWithBuffs].statStages[uVar7 - 1] - 6;
    uVar6 = uVar5 & 0xff;
    iVar2 = uVar5 * 0x1000000;
    iVar3 = iVar2 >> 0x18;
    if (debuff == 0) {
      iVar3 = (iVar2 >> 0x1f) - iVar3;
    }
    if (-1 < iVar3) goto LAB_090dbb5a;
    if (bVar8) goto sw_dbb34_1;
    uVar5 = (uVar7 & 0xff) - 2;
    if (5 < uVar5) {
      bVar1 = RealPhysicalMoveInMoveset(bankToGetBuffs);
      uVar5 = (uint)bVar1;
      goto LAB_090dbb4a;
    }
                        switch(uVar5) {
    case 0:
      bVar1 = MoveSplitOnTeam(~bankToGetBuffs & 1,0);
      if (bVar1 == 0) {
        uVar5 = MoveInMoveset(0x2b4 /* Body Press */,bankToGetBuffs);
        goto LAB_090dbb4a;
      }
    case 1:
    case 4:
    case 5:
sw_dbb34_1:
      if (debuff != 0) {
        uVar6 = -uVar6;
      }
      uVar4 = uVar4 + uVar6 & 0xff;
      break;
    case 2:
      bVar1 = SpecialMoveInMoveset(bankToGetBuffs);
      uVar5 = (uint)bVar1;
      goto LAB_090dbb4a;
    case 3:
      bVar1 = MoveSplitOnTeam(~bankToGetBuffs & 1,1);
      uVar5 = (uint)bVar1;
LAB_090dbb4a:
      if (uVar5 != 0) goto sw_dbb34_1;
    }
LAB_090dbb5a:
    uVar7 = uVar7 + 1;
    if (uVar7 == 8) {
      return (u8)uVar4;
    }
  } while( true );
}

// ---- GoodIdeaToBurnSelf  (ROM 0x90dbba0)
bool8 GoodIdeaToBurnSelf(u8 bankAtk)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar2 = GetBankAbility();
  iVar3 = CanBeBurned(bankAtk,0);
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = iVar2 - 0x61U & 0xff;
  if (uVar4 < 0x13) {
    if ((int)((0x48001U >> uVar4) << 0x1f) < 0) {
      return 1;
    }
LAB_090dbbfe:
    if (iVar2 != 0x3e) goto LAB_090dbbe0;
    bVar1 = PhysicalMoveInMoveset(bankAtk);
  }
  else {
    if (iVar2 != 0x93) goto LAB_090dbbfe;
    bVar1 = SpecialMoveInMoveset(bankAtk);
  }
  if (bVar1 != 0) {
    return 1;
  }
LAB_090dbbe0:
  iVar2 = MoveInMoveset(0x107 /* Facade */,bankAtk);
  if (iVar2 == 0) {
    iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,bankAtk);
    return iVar2 != 0;
  }
  return 1;
}

// ---- BadIdeaToBurn  (ROM 0x90dbc14)
bool8 BadIdeaToBurn(u8 bankDef,u8 bankAtk)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = GetBankItemEffect();
  iVar3 = GetBankAbility(bankDef);
  iVar4 = CanBeBurned(bankDef,1);
  if (iVar4 == 0) {
    return 1;
  }
  if ((iVar2 - 5U & 0xfb) == 0) {
    return 1;
  }
  if (iVar3 == 0x3d) {
    return 1;
  }
  if (iVar3 == 0x73) {
    return 1;
  }
  if (iVar3 == 0x70) {
    return 1;
  }
  if (iVar3 == 0x1c) {
    iVar2 = CanBeBurned(bankAtk,1);
    if ((iVar2 != 0) && (bVar1 = GoodIdeaToBurnSelf(bankAtk), bVar1 == 0)) {
      return 1;
    }
    goto LAB_090dbc66;
  }
  if (iVar3 == 0x3f) {
LAB_090dbcc4:
    bVar1 = PhysicalMoveInMoveset(bankAtk);
  }
  else {
    if (iVar3 == 0x1e) {
      bVar1 = IsTrapped(bankDef,1);
      if (bVar1 == 0) {
        if ((-1 < gBattleTypeFlags << 0x1f) &&
           (uVar5 = ViableMonCountFromBankLoadPartyRange(bankDef), 1 < uVar5)) {
          return 1;
        }
        if ((gBattleTypeFlags << 0x1f < 0) &&
           (uVar5 = ViableMonCountFromBankLoadPartyRange(bankDef), 2 < uVar5)) {
          return 1;
        }
      }
      goto LAB_090dbc66;
    }
    if (iVar3 != 0x93) {
      bankAtk = bankDef;
      if (iVar3 != 0x3e) {
        if (((iVar3 == 0x6b) && ((gBattleWeather & 0x1007) != 0)) && (UNK_02023f48 != '\x01')) {
          return 1;
        }
        goto LAB_090dbc66;
      }
      goto LAB_090dbcc4;
    }
    bVar1 = SpecialMoveInMoveset(bankDef);
  }
  if (bVar1 != 0) {
    return 1;
  }
LAB_090dbc66:
  iVar2 = MoveInMoveset(0x107 /* Facade */,bankDef);
  if (iVar2 == 0) {
    iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,bankDef);
    return 1 - (iVar2 == 0);
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
  return 1;
}

// ---- MoveSplitInMoveset  (ROM 0x90dbd78)
bool8 MoveSplitInMoveset(u8 bank,u8 moveSplit)

{
  bool8 bVar1;
  bool8 bVar2;
  
  if (moveSplit == 0) {
    bVar2 = PhysicalMoveInMoveset(bank);
  }
  else if (moveSplit == 1) {
    bVar2 = SpecialMoveInMoveset(bank);
  }
  else {
    bVar1 = PhysicalMoveInMoveset(bank);
    bVar2 = false;
    if (bVar1 == 0) {
      bVar2 = SpecialMoveInMoveset(bank);
      bVar2 = bVar2 == 0;
    }
  }
  return bVar2;
}

// ---- PhysicalMoveInMonMoveset  (ROM 0x90dbda8)
bool8 PhysicalMoveInMonMoveset(Pokemon *mon,u8 moveLimitations)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = CheckMoveLimitationsFromParty(mon,0,moveLimitations);
  iVar4 = 0xd;
  while( true ) {
    uVar3 = GetMonData(mon,iVar4,0);
    uVar3 = uVar3 & 0xffff;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar4 + 0x209790a) * 4) & uVar1) == 0) &&
         (iVar2 = CalcMoveSplitFromParty(mon,uVar3), iVar2 == 0)) &&
        (gBattleMoves[uVar3].power != 0)) && (gBattleMoves[uVar3].effect != 0x59 /* EFFECT_COUNTER */)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 0x11) {
      return 0;
    }
  }
  return 1;
}

// ---- SpecialMoveInMonMoveset  (ROM 0x90dbe14)
bool8 SpecialMoveInMonMoveset(Pokemon *mon,u8 moveLimitations)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = CheckMoveLimitationsFromParty(mon,0,moveLimitations);
  iVar4 = 0xd;
  while( true ) {
    uVar3 = GetMonData(mon,iVar4,0);
    uVar3 = uVar3 & 0xffff;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar4 + 0x209790a) * 4) & uVar1) == 0) &&
         (iVar2 = CalcMoveSplitFromParty(mon,uVar3), iVar2 == 1)) &&
        (gBattleMoves[uVar3].power != 0)) && (gBattleMoves[uVar3].effect != 0x90 /* EFFECT_MIRROR_COAT */)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 0x11) {
      return 0;
    }
  }
  return 1;
}

// ---- MagicCoatableMovesInMoveset  (ROM 0x90dbe7c)
bool8 MagicCoatableMovesInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  undefined4 in_r3;
  int iVar3;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar3 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar3);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar3 + 0x2097917) * 4) & uVar2) == 0) &&
       ((gBattleMoves[uVar1].flags & 4) != 0)) break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HasProtectionMoveInMoveset  (ROM 0x90dbed4)
bool8 HasProtectionMoveInMoveset(u8 bank,u8 checkType)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 in_r3;
  int iVar6;
  int iVar7;
  
  uVar4 = (uint)checkType;
  uVar2 = (uint)bank;
  uVar3 = CheckMoveLimitations(uVar2,0,0xff,in_r3,uVar2,uVar4);
  iVar7 = 0;
  iVar5 = uVar2 * 0x58;
  do {
    uVar1 = GetBattleMonMove(bank,(u8)iVar7);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar7 + 0x2097917) * 4) & uVar3) == 0) &&
       (gBattleMoves[*(ushort *)((int)gBattleMons[0].moves + iVar7 * 2 + iVar5)].effect == 0x6f /* EFFECT_PROTECT */)) {
      if (uVar1 == 0x27b) {
        iVar6 = uVar4 << 0x1c;
joined_r0x090dbf66:
        if (iVar6 < 0) {
          return 1;
        }
      }
      else if (uVar1 < 0x27c) {
        if (uVar1 == 0x20f) {
          return 1;
        }
        if (uVar1 == 0x237) {
          return 1;
        }
        if (uVar1 == 0xb6) {
          return 1;
        }
      }
      else {
        if (uVar1 == 0x27d) {
          iVar6 = uVar4 << 0x1e;
          goto joined_r0x090dbf66;
        }
        if (uVar1 < 0x27d) {
          if (((int)(uVar4 << 0x1b) < 0) && (gDisableStructs[uVar2].isFirstTurn != 0)) {
            return 1;
          }
        }
        else if (uVar1 == 0x27e) {
          iVar6 = uVar4 << 0x1d;
          goto joined_r0x090dbf66;
        }
      }
    }
    iVar7 = iVar7 + 1;
    if (iVar7 == 4) {
      return 0;
    }
  } while( true );
}

// ---- HasContactProtectionMoveInMoveset  (ROM 0x90dbfa4)
bool8 HasContactProtectionMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  u16 uVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar4 = 0;
  do {
    uVar1 = GetBattleMonMove(bank,(u8)iVar4);
    if (uVar1 == 0) {
      return 0;
    }
    if ((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) {
      if (uVar1 == 0x244) {
        return 1;
      }
      if (uVar1 < 0x245) {
        if (uVar1 == 0x20f) {
          return 1;
        }
        uVar3 = 0x237;
      }
      else {
        if (uVar1 == 0x318) {
          return 1;
        }
        if (uVar1 == 0x334) {
          return 1;
        }
        uVar3 = 0x2c4;
      }
      if (uVar1 == uVar3) {
        return 1;
      }
    }
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  } while( true );
}

// ---- BadIdeaToMakeContactWith  (ROM 0x90dc010)
bool8 BadIdeaToMakeContactWith(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = (uint)bankDef;
  uVar6 = uVar5;
  iVar2 = GetBankAbility();
  uVar3 = GetBankAbility(uVar5);
  if (uVar3 == 0x79) {
    if (((gBattleMons[UNK_02023d6b].statStages[2] < 1) || (iVar4 = GetBankAbility(), iVar4 == 0xbf))
       && ((iVar4 = GetBankAbility(UNK_02023d6b), iVar4 != 0xbf ||
           (0xb < gBattleMons[UNK_02023d6b].statStages[2])))) goto LAB_090dc036;
    iVar4 = iVar2 + -0xf2;
LAB_090dc0be:
    uVar3 = (uint)(iVar4 != 0);
LAB_090dc086:
    iVar4 = GetBankItemEffect(uVar5);
    if ((iVar4 != 0x44) || (iVar2 == 0x73)) {
      if (uVar3 == 0) {
        bVar1 = HasContactProtectionMoveInMoveset(bankDef);
        uVar3 = (uint)(bVar1 != 0);
      }
      goto LAB_090dc0a4;
    }
  }
  else {
    if (uVar3 < 0x7a) {
      if (uVar3 == 0x31) {
        uVar3 = CanBeBurned(bankAtk,uVar5);
      }
      else if (uVar3 < 0x32) {
        if (uVar3 == 9) {
          uVar3 = CanBeParalyzed(bankAtk,uVar5);
        }
        else {
          if (uVar3 != 0x1b) goto LAB_090dc036;
          iVar4 = CanBePoisoned(bankAtk,uVar5,1);
          if ((iVar4 == 0) && (iVar4 = CanBeParalyzed(bankAtk,uVar5), iVar4 == 0)) {
            iVar4 = sub_90763c6(bankAtk,1);
            goto LAB_090dc0be;
          }
          uVar3 = 1;
        }
      }
      else if (uVar3 == 0x38) {
        uVar3 = sub_9075a8c(bankAtk,uVar5);
      }
      else {
        if (uVar3 != 0x77) goto LAB_090dc036;
        uVar3 = 0;
        iVar4 = AbilityBattleEffects(0x13,0,6,0,0,uVar6);
        if (iVar4 == 0) goto LAB_090dc068;
      }
      goto LAB_090dc086;
    }
    if (uVar3 < 0xa5) {
      if ((uVar3 < 0xa3) && (uVar3 != 0x7a)) {
        if (uVar3 == 0x7b) {
LAB_090dc068:
          iVar4 = iVar2 + -0x73;
          goto LAB_090dc0be;
        }
        goto LAB_090dc036;
      }
    }
    else if (uVar3 != 0xf1) {
LAB_090dc036:
      uVar3 = 0;
      goto LAB_090dc086;
    }
  }
  uVar3 = 1;
LAB_090dc0a4:
  return (bool8)uVar3;
}

// ---- MoveTypeInMoveset  (ROM 0x90dc130)
bool8 MoveTypeInMoveset(u8 bank,u8 moveType)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar4);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) &&
       (uVar3 = GetMoveTypeSpecial(bank), uVar3 == moveType)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- DamagingMoveTypeInMoveset  (ROM 0x90dc178)
bool8 DamagingMoveTypeInMoveset(u8 bank,u8 moveType)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if ((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
        (uVar4 = GetMoveTypeSpecial(bank,uVar3), uVar4 == moveType)) &&
       (gBattleMoves[uVar3].split != 2)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- DamagingAllHitMoveTypeInMoveset  (ROM 0x90dc1d8)
bool8 DamagingAllHitMoveTypeInMoveset(u8 bank,u8 moveType)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (uVar4 = GetMoveTypeSpecial(bank,uVar3), uVar4 == moveType)) &&
        (gBattleMoves[uVar3].split != 2)) && ((gBattleMoves[uVar3].target & 0x20) != 0)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HasSnatchableMove  (ROM 0x90dc29c)
bool8 HasSnatchableMove(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  undefined4 in_r3;
  int iVar3;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar3 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar3);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar3 + 0x2097917) * 4) & uVar2) == 0) &&
       ((gBattleMoves[uVar1].flags & 8) != 0)) break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- MoveEffectInMoveset  (ROM 0x90dc2f4)
bool8 MoveEffectInMoveset(u8 moveEffect,u8 bank)

{
  u16 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar3 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar3);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar3 + 0x2097917) * 4) & uVar2) == 0) &&
       (gBattleMoves[uVar1].effect == moveEffect)) break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- StatusMoveInMoveset  (ROM 0x90dc410)
bool8 StatusMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar4);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) &&
       (iVar3 = CalcMoveSplit(bank), iVar3 == 2)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- IsSuckerPunchOkayToUseThisRound  (ROM 0x90dc458)
bool8 IsSuckerPunchOkayToUseThisRound(u16 move,u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar7 = (uint)bankDef;
  uVar5 = (uint)bankAtk;
  uVar2 = move;
  uVar6 = uVar7;
  uVar3 = FindMovePositionInMoveset();
  if (((2 < gBattleResources->ai->aiFlags) && (uVar3 < 4)) &&
     (iVar4 = GetBattlerSide(uVar5), iVar4 == 1)) {
    uVar8 = (uint)gBattleMons[uVar5].pp[uVar3];
    uVar6 = CalculatePPWithBonus(uVar2,gBattleMons[uVar5].ppBonuses,uVar3,&CalculatePPWithBonus,uVar2,uVar8,uVar6);
    if (uVar8 < uVar6) {
      bVar1 = StatusMoveInMoveset(bankDef);
      if (bVar1 == 0) {
        bVar1 = DamagingPriorityMoveInMovesetThatAffects(bankDef,bankAtk);
        if (bVar1 == 0) goto LAB_090dc474;
        uVar6 = SpeedCalc(uVar7);
        uVar3 = SpeedCalc(uVar5);
        if (uVar6 <= uVar3) goto LAB_090dc474;
      }
      if (*(char *)(gNewBS + uVar5 + 0x1e1) == '\0') {
        return 0;
      }
    }
  }
LAB_090dc474:
  uVar6 = (uint)*(ushort *)(gNewBS + (uVar7 * 4 + uVar5 + 0xf4) * 2 + 6);
  if (((uVar6 - 1 & 0xffff) < 0xfffe) && (gBattleMoves[uVar6].split != 2)) {
    bVar1 = MoveWouldHitFirst((u16)uVar2,(ushort)bankAtk,(ushort)bankDef);
    return 1 - (bVar1 == 0);
  }
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return 0;
}

// ---- IsDamagingMoveUnusable  (ROM 0x90dc540)
bool8 IsDamagingMoveUnusable(u16 move,u8 bankAtk,u8 bankDef)

{
  byte bVar1;
  ushort uVar2;
  bool8 bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  uVar11 = (uint)bankDef;
  uVar9 = (uint)bankAtk;
  uVar4 = move;
  uVar7 = uVar4;
  uVar12 = uVar9;
  uVar13 = uVar11;
  iVar5 = GetBankAbility(uVar9);
  if ((iVar5 != 0x98) && (iVar5 = CheckTableForMove(uVar4,&UNK_09040136), iVar5 == 0)) {
    uVar6 = GetBankAbility(uVar11);
    if (uVar6 == 0x50) goto LAB_090dc66e;
    if (uVar6 < 0x51) {
      if (uVar6 == 0x10) {
        puVar10 = &UNK_0903ff9e;
LAB_090dc6a2:
        iVar5 = CheckTableForMove(uVar4,puVar10);
LAB_090dc698:
        if (iVar5 != 0) {
          return 1;
        }
      }
      else if (uVar6 < 0x11) {
        if (uVar6 == 10) {
LAB_090dc66e:
          iVar5 = GetMoveTypeSpecial(uVar9,uVar4);
          if (iVar5 == 0xd) {
            return 1;
          }
        }
        else if (uVar6 == 0xb) goto LAB_090dc646;
      }
      else {
        if (uVar6 == 0x1f) goto LAB_090dc66e;
        if (uVar6 == 0x2b) {
          iVar5 = sub_9073ba8(uVar4);
          goto LAB_090dc698;
        }
        if (uVar6 == 0x12) goto LAB_090dc624;
      }
    }
    else if (uVar6 == 0x83) {
LAB_090dc646:
      iVar5 = GetMoveTypeSpecial(uVar9,uVar4);
      if (iVar5 == 0xb) {
        return 1;
      }
    }
    else if (uVar6 < 0x84) {
      if (uVar6 == 0x71) {
        iVar5 = GetMoveTypeSpecial(uVar9,uVar4);
        if (iVar5 == 0xc) {
          return 1;
        }
      }
      else {
        puVar10 = &UNK_0903ff64;
        if (uVar6 == 0x74) goto LAB_090dc6a2;
        if (uVar6 == 0x62) goto LAB_090dc646;
      }
    }
    else if (uVar6 == 0xdd) {
      iVar5 = PriorityCalc(uVar9,0,uVar4);
      if (0 < iVar5) {
        return 1;
      }
    }
    else if (uVar6 == 0xfe) {
LAB_090dc624:
      iVar5 = GetMoveTypeSpecial(uVar9,uVar4);
      if (iVar5 == 10) {
        return 1;
      }
    }
    else if ((uVar6 == 0xbc) && (iVar5 = GetMoveTypeSpecial(uVar9,uVar4), iVar5 == 4)) {
      return 1;
    }
  }
  bVar1 = gBattleMoves[uVar4].effect;
  if (bVar1 == 0x9e) {
    if (gDisableStructs[uVar9].isFirstTurn == 0) {
      return 1;
    }
    goto LAB_090dc59c;
  }
  if (bVar1 < 0x9f) {
    if (bVar1 == 0x26) {
      if (gBattleMons[uVar9].level < gBattleMons[uVar11].level) {
        return 1;
      }
      if ((uVar4 == 0x149) &&
         (iVar5 = IsOfType(uVar11,0xf /* Ice */,gBattleMons[uVar9].level,0x149,uVar7,uVar12,uVar13),
         iVar5 != 0)) {
        return 1;
      }
      iVar5 = IsDynamaxed(uVar11);
      if ((iVar5 != 0) && (iVar5 = sub_908ee64(uVar11), iVar5 == 0)) {
        return 1;
      }
      iVar5 = GetBankAbility(uVar9);
      if (((iVar5 != 0x98) && (iVar5 = CheckTableForMove(uVar4,&UNK_09040136), iVar5 == 0)) &&
         (iVar5 = GetBankAbility(uVar11), iVar5 == 5)) {
        return 1;
      }
      goto LAB_090dc59c;
    }
    if (bVar1 != 0x7d) goto LAB_090dc59c;
    uVar7 = IsOfType(uVar9,10 /* Fire */,gBattleMoves,0x7d,uVar7,uVar12,uVar13);
  }
  else {
    if (bVar1 == 0xb9) {
      uVar2 = gBattleMons[uVar11].item;
      uVar8 = GetBankAbility(uVar11);
      iVar5 = sub_907659c(uVar2,uVar8);
      if (iVar5 != 0) {
        return 1;
      }
      goto LAB_090dc59c;
    }
    if (bVar1 != 0xed) goto LAB_090dc59c;
    bVar3 = IsSuckerPunchOkayToUseThisRound(move,bankAtk,bankDef);
    uVar7 = (uint)bVar3;
  }
  if (uVar7 == 0) {
    return 1;
  }
LAB_090dc59c:
  iVar5 = IsDynamaxed(uVar11);
  if ((((iVar5 != 0) && (iVar5 = CheckTableForMove(uVar4,&UNK_0903fcc0), iVar5 != 0)) ||
      ((iVar5 = IsRaidBattle(), iVar5 != 0 &&
       ((uVar7 = GetBattlerAtPosition(1), uVar7 == uVar9 &&
        (iVar5 = CheckTableForMove(uVar4,&UNK_0903fcc0), iVar5 != 0)))))) ||
     (((((int)((uint)gBattleWeather << 0x14) < 0 &&
        (iVar5 = GetMoveTypeSpecial(uVar9,uVar4), iVar5 == 0xb)) ||
       (((int)((uint)gBattleWeather << 0x13) < 0 &&
        (iVar5 = GetMoveTypeSpecial(uVar9,uVar4), iVar5 == 10)))) &&
      (iVar5 = AbilityBattleEffects(0x13,0,0xd,0,0), iVar5 == 0)))) {
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
    return 1;
  }
  if (gTerrainType != '\x04') {
    return 0;
  }
  iVar5 = CheckGrounding(uVar11);
  if (iVar5 == 1) {
    iVar5 = PriorityCalc(uVar9,0,uVar4);
    return (byte)((uint)((iVar5 >> 0x1f) - iVar5) >> 0x1f);
  }
  return 0;
}

// ---- IsUsablePhazingMove  (ROM 0x90dc7d8)
bool8 IsUsablePhazingMove(u16 move,u8 bankAtk,u8 bankDef)

{
  byte bVar1;
  bool8 bVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = move;
  bVar1 = gBattleMoves[uVar4].effect;
  if (bVar1 == 0x1c) {
    iVar3 = IsDynamaxed(bankDef);
    if (((iVar3 != 0) || (bVar2 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar2 != 0)) &&
       (uVar4 != 0x231)) {
      return 0;
    }
  }
  else if ((bVar1 != 0x19) && (uVar4 != 0x231)) {
    if (bVar1 != 0xde) {
      return 0;
    }
    uVar4 = AI_SpecialTypeCalc(uVar4,bankAtk,bankDef);
    if ((uVar4 & 0x29) == 0) {
      bVar2 = IsDamagingMoveUnusable(move,bankAtk,bankDef);
      return bVar2 == 0;
    }
    return 0;
  }
  return 1;
}

// ---- DamagingPriorityMoveInMovesetThatAffects  (ROM 0x90dc8d0)
bool8 DamagingPriorityMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar5 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar5);
    uVar4 = move;
    if (uVar4 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) && (gBattleMoves[uVar4].split != 2))
        && (iVar3 = PriorityCalc(bankAtk,0,uVar4), 0 < iVar3)) &&
       ((uVar4 = AI_SpecialTypeCalc(uVar4,bankAtk,bankDef), (uVar4 & 0x29) == 0 &&
        (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 == 0)))) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- MoveInMovesetWithAccuracyLessThan  (ROM 0x90dc950)
bool8 MoveInMovesetWithAccuracyLessThan(u8 bankAtk,u8 bankDef,u8 acc,bool8 ignoreStatusMoves)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bankAtk,(u8)iVar4);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if ((((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) &&
        (((ignoreStatusMoves == 0 || (gBattleMoves[uVar3].split != 2)) &&
         (gBattleMoves[uVar3].accuracy != 0)))) &&
       (((gBattleMoves[uVar3].target & 0x50) == 0 &&
        (uVar3 = AccuracyCalc(uVar3,bankAtk,bankDef), uVar3 < acc)))) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- AllMovesInMovesetWithAccuracyLessThan  (ROM 0x90dc9d4)
bool8 AllMovesInMovesetWithAccuracyLessThan(u8 bankAtk,u8 bankDef,u8 acc,bool8 ignoreStatusMoves)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff);
  iVar5 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar5);
    uVar4 = move;
    if (uVar4 == 0) {
      return 1;
    }
    if ((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
        ((ignoreStatusMoves == 0 || (gBattleMoves[uVar4].split != 2)))) &&
       ((gBattleMoves[uVar4].accuracy == 0 ||
        (((uVar3 = GetBaseMoveTarget(uVar4,bankAtk), (uVar3 & 0x50) != 0 ||
          (bVar1 = MoveWillHit(move,bankAtk,bankDef), bVar1 != 0)) ||
         (uVar4 = AccuracyCalc(uVar4,bankAtk,bankDef), acc <= uVar4)))))) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 1;
    }
  }
  return 0;
}

// ---- FlinchingMoveInMoveset  (ROM 0x90dca74)
bool8 FlinchingMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  undefined4 in_r3;
  int iVar3;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar3 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar3);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar3 + 0x2097917) * 4) & uVar2) == 0) && (gBattleMoves[uVar1].effect == 0x1f /* EFFECT_FLINCH_HIT */))
    break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HealingMoveInMoveset  (ROM 0x90dcac8)
bool8 HealingMoveInMoveset(u8 bank)

{
  byte bVar1;
  u16 uVar2;
  uint uVar3;
  undefined4 in_r3;
  int iVar4;
  
  uVar3 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar4 = 0;
  while( true ) {
    uVar2 = GetBattleMonMove(bank,(u8)iVar4);
    if (uVar2 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar3) == 0) &&
       ((((bVar1 = gBattleMoves[uVar2].effect, bVar1 == 0x20 || (bVar1 == 0x84)) || (bVar1 == 0xa2))
        || (bVar1 == 0xb3)))) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HealingMoveInMonMoveset  (ROM 0x90dcb28)
bool8 HealingMoveInMonMoveset(Pokemon *mon)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitationsFromParty(mon,0,0xff);
  iVar4 = 0xd;
  while( true ) {
    uVar3 = GetMonData(mon,iVar4,0);
    if ((uVar3 & 0xffff) == 0) {
      return 0;
    }
    if (((*(uint *)((iVar4 + 0x209790a) * 4) & uVar2) == 0) &&
       ((((bVar1 = gBattleMoves[uVar3 & 0xffff].effect, bVar1 == 0x20 || (bVar1 == 0x84)) ||
         (bVar1 == 0xa2)) || (bVar1 == 0xb3)))) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 0x11) {
      return 0;
    }
  }
  return 1;
}

// ---- SoundMoveInMoveset  (ROM 0x90dcb8c)
bool8 SoundMoveInMoveset(u8 bank)

{
  u16 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bank,0,0xff);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bank,(u8)iVar4);
    if (uVar1 == 0) {
      return 0;
    }
    if (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) && (iVar3 = sub_9073ba8(), iVar3 != 0))
    break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- MoveThatCanHelpAttacksHitInMoveset  (ROM 0x90dcbd0)
bool8 MoveThatCanHelpAttacksHitInMoveset(u8 bank)

{
  byte bVar1;
  u16 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar3 = CheckMoveLimitations(bank,0,0xff,in_r3,bank);
  iVar5 = 0;
  do {
    uVar2 = GetBattleMonMove(bank,(u8)iVar5);
    uVar4 = (uint)uVar2;
    if (uVar4 == 0) {
      return 0;
    }
    if ((*(uint *)((iVar5 + 0x2097917) * 4) & uVar3) == 0) {
      bVar1 = gBattleMoves[uVar4].effect;
      if (bVar1 == 0x37) {
        return 1;
      }
      if (bVar1 < 0x38) {
        if (bVar1 == 0xf) {
          return 1;
        }
        if (bVar1 == 0x18) {
          return 1;
        }
      }
      else {
        if (bVar1 == 0x40) {
          return 1;
        }
        if (bVar1 == 0x5e) {
          if (uVar4 != 0x252) {
            return 1;
          }
          goto LAB_090dcc26;
        }
      }
      if (((uVar4 == 0x19b) || (uVar4 == 0x204)) || (uVar4 == 0x199)) {
        return 1;
      }
    }
LAB_090dcc26:
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  } while( true );
}

// ---- DamagingMoveThaCanBreakThroughSubstituteInMoveset  (ROM 0x90dcc54)
bool8 DamagingMoveThaCanBreakThroughSubstituteInMoveset(u8 bankAtk,u8 bankDef)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bankAtk,(u8)iVar5);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if ((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) && (gBattleMoves[uVar3].split != 2)) &&
       (iVar4 = MoveBlockedBySubstitute(uVar3,bankAtk,bankDef), iVar4 == 0)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- ContactMovesThatAffectTargetInMoveset  (ROM 0x90dccb0)
bool8 ContactMovesThatAffectTargetInMoveset(u8 bankAtk,u8 bankDef)

{
  u16 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar5 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bankAtk,(u8)iVar5);
    if (uVar1 == 0) {
      return 0;
    }
    if ((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
        (iVar3 = CheckContact(uVar1,bankAtk), iVar3 != 0)) &&
       (uVar4 = AI_SpecialTypeCalc(uVar1,bankDef,bankAtk), (uVar4 & 0x29) == 0)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- BadIdeaToPoison  (ROM 0x90dcd0c)
undefined8 BadIdeaToPoison(undefined4 param_1,undefined4 param_2)

{
  u8 bank;
  bool8 bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  u8 bank_00;
  
  iVar2 = GetBankItemEffect();
  iVar3 = GetBankAbility(param_1);
  iVar4 = GetBankAbility(param_2);
  iVar5 = CanBePoisoned(param_1,param_2,1);
  if ((((iVar5 != 0) && (iVar2 != 4)) && (iVar2 != 9)) &&
     (((iVar3 != 0x3d && ((iVar3 - 0x68U & 0xf7) != 0)) && (iVar3 != 0x73)))) {
    bank = (u8)param_2;
    bank_00 = (u8)param_1;
    if (iVar3 == 0x1c) {
      iVar2 = CanBePoisoned(param_2,param_1,1);
      if ((iVar2 == 0) || (bVar1 = GoodIdeaToPoisonSelf(bank), bVar1 != 0)) {
LAB_090dcd70:
        if (iVar4 == 0xd1) {
LAB_090dcd76:
          bVar1 = ContactMovesThatAffectTargetInMoveset(bank,bank_00);
          if (bVar1 != 0) goto LAB_090dcd36;
        }
        if (((iVar3 != 0x6b) || ((gBattleWeather & 0x1007) == 0)) || (UNK_02023f48 == '\x01')) {
LAB_090dcd86:
          iVar2 = MoveInMoveset(0x107 /* Facade */,param_1);
          if (iVar2 == 0) {
            iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,param_1);
            uVar6 = (uint)(iVar2 != 0);
            goto LAB_090dcd38;
          }
        }
      }
    }
    else if (iVar3 == 0x3f) {
      bVar1 = PhysicalMoveInMoveset(bank);
      if (bVar1 == 0) goto LAB_090dcd70;
    }
    else if (iVar3 == 0x1e) {
      bVar1 = IsTrapped(bank_00,1);
      if ((bVar1 != 0) ||
         (((gBattleTypeFlags << 0x1f < 0 ||
           (uVar6 = ViableMonCountFromBankLoadPartyRange(param_1), uVar6 < 2)) &&
          ((-1 < gBattleTypeFlags << 0x1f ||
           (uVar6 = ViableMonCountFromBankLoadPartyRange(param_1), uVar6 < 3)))))) {
LAB_090dcdda:
        if (iVar4 == 0xd1) goto LAB_090dcd76;
        goto LAB_090dcd86;
      }
    }
    else {
      if ((iVar3 != 0x92) && (iVar3 != 0x3e)) goto LAB_090dcd70;
      bVar1 = PhysicalMoveInMoveset(bank_00);
      if (bVar1 == 0) goto LAB_090dcdda;
    }
  }
LAB_090dcd36:
  uVar6 = 1;
LAB_090dcd38:
  return CONCAT44(param_1,uVar6);
}

// ---- SleepMoveInMovesetWithLowAccuracy  (ROM 0x90dce78)
bool8 SleepMoveInMovesetWithLowAccuracy(u8 bankAtk,u8 bankDef)

{
  u16 uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 in_r3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk);
  iVar4 = 0;
  while( true ) {
    uVar1 = GetBattleMonMove(bankAtk,(u8)iVar4);
    uVar3 = (uint)uVar1;
    if (uVar3 == 0) {
      return 0;
    }
    if ((((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) && (gBattleMoves[uVar3].effect == 1 /* EFFECT_SLEEP */))
       && (uVar3 = AccuracyCalc(uVar3,bankAtk,bankDef), uVar3 < 0x55)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- PivotingMoveInMovesetThatAffects  (ROM 0x90dced4)
bool8 PivotingMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  uint uVar3;
  undefined4 in_r3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar4 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar4);
    uVar3 = move;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) && (uVar3 != 0xe2)) &&
        ((gBattleMoves[uVar3].effect == 0x7f /* EFFECT_BATON_PASS */ || (gBattleMoves[uVar3].effect == 0x99 /* EFFECT_TELEPORT */)))) &&
       ((gBattleMoves[uVar3].split == 2 ||
        ((uVar3 = AI_SpecialTypeCalc(uVar3,bankAtk,bankDef), (uVar3 & 0x29) == 0 &&
         (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 == 0)))))) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- FastPivotingMoveInMovesetThatAffects  (ROM 0x90dcf5c)
bool8 FastPivotingMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  uint uVar3;
  undefined4 in_r3;
  int iVar4;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar4 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar4);
    uVar3 = move;
    if (uVar3 == 0) {
      return 0;
    }
    if ((((((*(uint *)((iVar4 + 0x2097917) * 4) & uVar2) == 0) && (uVar3 != 0xe2)) &&
         (gBattleMoves[uVar3].effect == 0x7f /* EFFECT_BATON_PASS */)) &&
        ((gBattleMoves[uVar3].split == 2 ||
         ((uVar3 = AI_SpecialTypeCalc(uVar3,bankAtk,bankDef), (uVar3 & 0x29) == 0 &&
          (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 == 0)))))) &&
       (bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef), bVar1 != 0)) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- OffensiveSetupMoveInMoveset  (ROM 0x90dd068)
bool8 OffensiveSetupMoveInMoveset(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  u16 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte ability;
  uint uVar6;
  undefined4 in_r3;
  int iVar7;
  
  uVar3 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar7 = 0;
  do {
    move = GetBattleMonMove(bankAtk,(u8)iVar7);
    uVar4 = move;
    if (uVar4 == 0) {
      return 0;
    }
    if ((*(uint *)((iVar7 + 0x2097917) * 4) & uVar3) != 0) goto LAB_090dd0ca;
    ability = gBattleMoves[uVar4].effect;
    uVar6 = (uint)ability;
    if (uVar6 == 0x48) goto LAB_090dd0d8;
    if (uVar6 < 0x49) {
      if (uVar6 == 0x32) {
        return 1;
      }
      if (uVar6 < 0x33) {
        if (uVar6 == 0xd) {
          return 1;
        }
        if (uVar6 == 0x10) {
          return 1;
        }
        if (uVar6 == 10) {
          return 1;
        }
      }
      else {
        if (uVar6 == 0x38) {
          return 1;
        }
        if (uVar6 < 0x39) {
          uVar6 = uVar6 - 0x34;
joined_r0x090dd13e:
          if (uVar6 < 2) {
            return 1;
          }
        }
        else if (uVar6 == 0x45) goto LAB_090dd0d8;
      }
      goto LAB_090dd0ca;
    }
    if (uVar6 == 0xb6) {
LAB_090dd12a:
      iVar5 = GetBankAbility(bankAtk);
      if (iVar5 == 0xbf) {
LAB_090dd0e4:
        uVar4 = AI_SpecialTypeCalc(uVar4,bankAtk,bankDef);
        if (((uVar4 & 0x29) == 0) &&
           (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 != 0)) {
          return 1;
        }
      }
    }
    else {
      if (0xb6 < uVar6) {
        if (uVar6 == 0xd0) {
          return 1;
        }
        if (0xd0 < uVar6) {
          uVar6 = uVar6 + 0x2d & 0xff;
          goto joined_r0x090dd13e;
        }
        if (uVar6 != 0xcc) goto LAB_090dd0ca;
        goto LAB_090dd12a;
      }
      if (uVar6 == 0x8b) {
LAB_090dd0d8:
        uVar2 = CalcSecondaryEffectChance(bankAtk,move,ability);
        if (uVar2 < 0x32) goto LAB_090dd0ca;
        goto LAB_090dd0e4;
      }
      if (uVar6 < 0x8c) {
        if (uVar6 == 0x6e) goto LAB_090dd0d8;
      }
      else if (uVar6 == 0x8d) {
        iVar5 = sub_90743c0(bankAtk);
        ability = (byte)uVar6;
        if (iVar5 == 0) goto LAB_090dd0d8;
      }
      else if (uVar6 == 0x8e) {
        return 1;
      }
    }
LAB_090dd0ca:
    iVar7 = iVar7 + 1;
    if (iVar7 == 4) {
      return 0;
    }
  } while( true );
}

// ---- PhazingMoveInMovesetThatAffects  (ROM 0x90dd1b0)
bool8 PhazingMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  int iVar3;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff);
  iVar3 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar3);
    if (move == 0 /* - */) {
      return 0;
    }
    if (((*(uint *)((iVar3 + 0x2097917) * 4) & uVar2) == 0) &&
       (bVar1 = IsUsablePhazingMove(move,bankAtk,bankDef), bVar1 != 0)) break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HazardClearingMoveInMovesetThatAffects  (ROM 0x90dd1fc)
bool8 HazardClearingMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff);
  iVar5 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar5);
    uVar3 = move;
    if (uVar3 == 0) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (gBattleMoves[uVar3].effect == 0x81 /* EFFECT_RAPID_SPIN */)) &&
        (uVar4 = AI_SpecialTypeCalc(uVar3,bankAtk,bankDef), (uVar4 & 0x29) == 0)) &&
       ((gBattleMoves[uVar3].split == 2 ||
        (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 == 0)))) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- DoubleDamageWithStatusMoveInMovesetThatAffects  (ROM 0x90dd280)
bool8 DoubleDamageWithStatusMoveInMovesetThatAffects(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  
  uVar2 = CheckMoveLimitations(bankAtk,0,0xff,in_r3,bankAtk,bankDef);
  iVar5 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar5);
    if (move == 0 /* - */) {
      return 0;
    }
    if (((((*(uint *)((iVar5 + 0x2097917) * 4) & uVar2) == 0) &&
         (iVar3 = CheckTableForMove(move,&UNK_09040272), iVar3 != 0)) &&
        (uVar4 = AI_SpecialTypeCalc(move,bankAtk,bankDef), (uVar4 & 0x29) == 0)) &&
       (bVar1 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar1 == 0)) break;
    iVar5 = iVar5 + 1;
    if (iVar5 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HasUsedMove  (ROM 0x90dd2ec)
bool8 HasUsedMove(u8 bank,u16 move)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    uVar1 = gBattleResources->battleHistory->usedMoves[(uint)bank * 2][iVar2];
    if (uVar1 == 0) {
      return 0;
    }
    if (uVar1 == move) break;
    iVar2 = iVar2 + 1;
    if (iVar2 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HasUsedMoveWithEffect  (ROM 0x90dd318)
bool8 HasUsedMoveWithEffect(u8 bank,u8 effect)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = 0;
  while( true ) {
    uVar2 = (uint)gBattleResources->battleHistory->usedMoves[(uint)bank * 2][iVar1];
    if (uVar2 == 0) {
      return 0;
    }
    if (gBattleMoves[uVar2].effect == effect) break;
    iVar1 = iVar1 + 1;
    if (iVar1 == 4) {
      return 0;
    }
  }
  return 1;
}

// ---- HasUsedMoveWithEffectHigherThanChance  (ROM 0x90dd354)
bool8 HasUsedMoveWithEffectHigherThanChance(u8 bank,u8 effect,u8 chance)

{
  ushort move;
  u16 uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    move = gBattleResources->battleHistory->usedMoves[(uint)bank * 2][iVar2];
    if (move == 0 /* - */) {
      return 0;
    }
    if ((gBattleMoves[move].effect == effect) &&
       (uVar1 = CalcSecondaryEffectChance(bank,move,(char)move * '\f'), chance <= uVar1)) break;
    iVar2 = iVar2 + 1;
    if (iVar2 == 4) {
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
      return 0;
    }
  }
  return 1;
}

// ---- HasUsedPhazingMoveThatAffects  (ROM 0x90dd3a0)
bool8 HasUsedPhazingMoveThatAffects(u8 bankAtk,u8 bankDef)

{
  u16 move;
  bool8 bVar1;
  int iVar2;
  
  if ((gBattleMons[bankAtk].hp != 0) && (gBattleMons[bankDef].hp != 0)) {
    iVar2 = 0;
    do {
      move = gBattleResources->battleHistory->usedMoves[(uint)bankAtk * 2][iVar2];
      if (move == 0 /* - */) {
        return 0;
      }
      bVar1 = MoveInMovesetAndUsable(move,bankAtk);
      if ((bVar1 != 0) && (bVar1 = IsUsablePhazingMove(move,bankAtk,bankDef), bVar1 != 0)) {
        return 1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 4);
  }
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
  return 0;
}

// ---- BadIdeaToRaiseStatAgainst  (ROM 0x90dd40c)
bool8 BadIdeaToRaiseStatAgainst(u8 bankAtk,u8 bankDef,bool8 checkDefAbility)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = func_0x090db548(bankDef,bankAtk);
  if (iVar2 == 0) {
    iVar2 = func_0x090db628(bankDef,bankAtk);
    if (iVar2 != 0) {
      uVar3 = SpeedCalc(bankDef);
      uVar4 = SpeedCalc(bankAtk);
      if (uVar3 < uVar4) {
        return 1;
      }
    }
    bVar1 = HasUsedPhazingMoveThatAffects(bankDef,bankAtk);
    if (bVar1 == 0) {
      if ((checkDefAbility == 0 /* ------- */) || (iVar2 = GetBankAbility(bankDef), iVar2 != 0x8d)) {
        return 0;
      }
      bVar1 = WillFaintFromSecondaryDamage(bankDef);
      return bVar1 == 0;
    }
  }
  return 1;
}

// ---- BadIdeaToRaiseAccuracyAgainst  (ROM 0x90dd46e)
bool8 BadIdeaToRaiseAccuracyAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  u8 bankDef_00;
  uint uVar2;
  
  uVar2 = (uint)bankDef;
  while( true ) {
    bankDef_00 = (u8)uVar2;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (((bVar1 != 0) || (bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3f), bVar1 != 0)) ||
       ((amount < 2 &&
        ((bVar1 = HasUsedMoveWithEffect(bankDef_00,0x17), bVar1 != 0 ||
         (bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x49,0x4b), bVar1 != 0)))))) {
      return 1;
    }
    if (checkPartner == 0) {
      return 0;
    }
    if (-1 < gBattleTypeFlags << 0x1f) break;
    checkPartner = 0;
    uVar2 = uVar2 ^ 2;
    if (gBattleMons[uVar2].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  }
  return 0;
}

// ---- GoodIdeaToRaiseAccuracyAgainst  (ROM 0x90dd4e8)
bool8 GoodIdeaToRaiseAccuracyAgainst(u8 bankAtk,u8 bankDef,u8 amount)

{
  bool8 bVar1;
  bool bVar2;
  
  bVar1 = BadIdeaToRaiseAccuracyAgainst(bankAtk,bankDef,amount,1);
  bVar2 = false;
  if (bVar1 == 0) {
    bVar1 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,0x5a,1);
    bVar2 = bVar1 != 0;
  }
  return bVar2;
}

// ---- BadIdeaToRaiseSpeedAgainst  (ROM 0x90dd510)
bool8 BadIdeaToRaiseSpeedAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  int iVar2;
  u8 bankDef_00;
  uint uVar3;
  
  uVar3 = (uint)bankDef;
  while( true ) {
    iVar2 = IsTrickRoomActive();
    if ((iVar2 != 0) && (iVar2 = sub_9074c80(), iVar2 == 0)) {
      return 1;
    }
    bankDef_00 = (u8)uVar3;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (bVar1 != 0) {
      return 1;
    }
    bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3c);
    if (bVar1 != 0) {
      return 1;
    }
    if (amount < 2) {
      bVar1 = HasUsedMoveWithEffect(bankDef_00,0x14);
      if (bVar1 != 0) {
        return 1;
      }
      bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x46,0x4b);
      if (bVar1 != 0) {
        return 1;
      }
    }
    if (checkPartner == 0) {
      return 0;
    }
    if (-1 < gBattleTypeFlags << 0x1f) break;
    checkPartner = 0;
    uVar3 = uVar3 ^ 2;
    if (gBattleMons[uVar3].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  }
  return 0;
}

// ---- GoodIdeaToRaiseSpeedAgainst  (ROM 0x90dd5a0)
bool8 GoodIdeaToRaiseSpeedAgainst(u8 bankAtk,u8 bankDef,u8 amount,u16 atkSpeed,u16 defSpeed)

{
  bool8 bVar1;
  bool bVar2;
  
  if ((gBattleMons[bankDef].hp == 0) ||
     (bVar1 = BadIdeaToRaiseSpeedAgainst(bankAtk,bankDef,amount,1), bVar1 != 0)) {
    bVar2 = false;
  }
  else {
    if (2 < gBattleResources->ai->aiFlags) {
      defSpeed = GetTeamMaxSpeed(bankDef);
    }
    bVar2 = atkSpeed <= defSpeed;
  }
  return bVar2;
}

// ---- BadIdeaToRaiseSpDefenseAgainst  (ROM 0x90dd5f4)
bool8 BadIdeaToRaiseSpDefenseAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  u8 bankDef_00;
  uint uVar2;
  
  uVar2 = (uint)bankDef;
  while( true ) {
    bankDef_00 = (u8)uVar2;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (((bVar1 != 0) || (bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3e), bVar1 != 0)) ||
       ((amount < 2 &&
        ((bVar1 = HasUsedMoveWithEffect(bankDef_00,0x16), bVar1 != 0 ||
         (bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x48,0x4b), bVar1 != 0)))))) {
      return 1;
    }
    if (checkPartner == 0) {
      return 0;
    }
    if (-1 < gBattleTypeFlags << 0x1f) break;
    checkPartner = 0;
    uVar2 = uVar2 ^ 2;
    if (gBattleMons[uVar2].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  }
  return 0;
}

// ---- GoodIdeaToRaiseSpDefenseAgainst  (ROM 0x90dd670)
bool8 GoodIdeaToRaiseSpDefenseAgainst(u8 bankAtk,u8 bankDef,u8 amount)

{
  bool8 bVar1;
  u8 uVar2;
  bool bVar3;
  
  bVar1 = BadIdeaToRaiseSpDefenseAgainst(bankAtk,bankDef,amount,1);
  bVar3 = false;
  if (bVar1 == 0) {
    uVar2 = GetBankFightingStyle(bankDef);
    uVar2 = BankLikelyToUseMoveSplit(bankDef,uVar2);
    bVar3 = uVar2 == 1;
  }
  return bVar3;
}

// ---- BadIdeaToRaiseSpAttackAgainst  (ROM 0x90dd698)
bool8 BadIdeaToRaiseSpAttackAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  u8 bankDef_00;
  uint uVar2;
  
  uVar2 = (uint)bankDef;
  while( true ) {
    bankDef_00 = (u8)uVar2;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (((bVar1 != 0) || (bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3d), bVar1 != 0)) ||
       ((amount < 2 &&
        ((bVar1 = HasUsedMoveWithEffect(bankDef_00,0x15), bVar1 != 0 ||
         (bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x47,0x4b), bVar1 != 0)))))) {
      return 1;
    }
    if (checkPartner == 0) {
      return 0;
    }
    if (-1 < gBattleTypeFlags << 0x1f) break;
    checkPartner = 0;
    uVar2 = uVar2 ^ 2;
    if (gBattleMons[uVar2].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  }
  return 0;
}

// ---- GoodIdeaToRaiseSpAttackAgainst  (ROM 0x90dd714)
bool8 GoodIdeaToRaiseSpAttackAgainst(u8 bankAtk,u8 bankDef,u8 amount)

{
  bool8 bVar1;
  bool bVar2;
  
  bVar1 = BadIdeaToRaiseSpAttackAgainst(bankAtk,bankDef,amount,1);
  bVar2 = false;
  if (bVar1 == 0) {
    bVar1 = SpecialMoveInMoveset(bankAtk);
    bVar2 = bVar1 != 0;
  }
  return bVar2;
}

// ---- AnyStatIsRaised  (ROM 0x90dd7bc)
bool8 AnyStatIsRaised(u8 bank)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (6 < gBattleMons[bank].statStages[iVar1]) {
      return 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 7);
  return 0;
}

// ---- CountUsefulBoosts  (ROM 0x90dd7e8)
u8 CountUsefulBoosts(u8 bank)

{
  u8 uVar1;
  
  uVar1 = CountUsefulStatChanges(bank,bank,0);
  return uVar1;
}

// ---- CountUsefulDebuffs  (ROM 0x90dd7f4)
u8 CountUsefulDebuffs(u8 bank)

{
  u8 uVar1;
  
  uVar1 = CountUsefulStatChanges(bank,bank,1);
  return uVar1;
}

// ---- CountUsefulBoostsOfBankForBank  (ROM 0x90dd800)
u8 CountUsefulBoostsOfBankForBank(u8 bankWithBuffs,u8 bankToGetBuffs)

{
  u8 uVar1;
  
  uVar1 = CountUsefulStatChanges(bankWithBuffs,bankToGetBuffs,0);
  return uVar1;
}

// ---- CountUsefulDebuffsOfBankForBank  (ROM 0x90dd80a)
u8 CountUsefulDebuffsOfBankForBank(u8 bankWithDefuffs,u8 bankToGetDebuffs)

{
  u8 uVar1;
  
  uVar1 = CountUsefulStatChanges(bankWithDefuffs,bankToGetDebuffs,1);
  return uVar1;
}

// ---- GoodIdeaToSwapStatStages  (ROM 0x90dd814)
bool8 GoodIdeaToSwapStatStages(u8 bankAtk,u8 bankDef)

{
  u8 uVar1;
  u8 uVar2;
  u8 uVar3;
  u8 uVar4;
  
  uVar1 = CountUsefulBoostsOfBankForBank(bankDef,bankAtk);
  uVar2 = CountUsefulDebuffsOfBankForBank(bankAtk,bankAtk);
  uVar3 = CountUsefulDebuffsOfBankForBank(bankDef,bankAtk);
  uVar4 = CountUsefulBoostsOfBankForBank(bankAtk,bankAtk);
  return 1 < (int)(((uint)uVar1 + (uint)uVar2) - ((uint)uVar3 + (uint)uVar4));
}

// ---- AnyUsefulOffseniveStatIsRaised  (ROM 0x90dd920)
bool8 AnyUsefulOffseniveStatIsRaised(u8 bank)

{
  bool8 bVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 1;
  do {
    uVar2 = uVar3 & 0xff;
    if (6 < gBattleMons[bank].statStages[uVar3 - 1]) {
      if (uVar2 == 3) {
        return 1;
      }
      if (uVar2 == 4) {
        bVar1 = SpecialMoveInMoveset(bank);
      }
      else {
        if (uVar2 != 1) goto LAB_090dd964;
        bVar1 = PhysicalMoveInMoveset(bank);
      }
      if (bVar1 != 0) {
        return 1;
      }
    }
LAB_090dd964:
    uVar3 = uVar3 + 1;
    if (uVar3 == 8) {
      return 0;
    }
  } while( true );
}

// ---- PartyMemberStatused  (ROM 0x90dd974)
bool8 PartyMemberStatused(u8 bank,bool8 checkSoundproof)

{
  int iVar1;
  Pokemon *pPVar2;
  Pokemon *pPVar3;
  
  iVar1 = GetBattlerSide(bank);
  pPVar2 = gEnemyParty;
  if (iVar1 == 0) {
    pPVar2 = gPlayerParty;
  }
  pPVar3 = pPVar2 + 6;
  while (((checkSoundproof != 0 && (iVar1 = GetMonAbility(pPVar2), iVar1 == 0x2b)) ||
         (pPVar2->condition == 0))) {
    pPVar2 = pPVar2 + 1;
    if (pPVar3 == pPVar2) {
      return 0;
    }
  }
  return 1;
}

// ---- GetAIMoveEffectForMaxMove  (ROM 0x90dd9bc)
u8 GetAIMoveEffectForMaxMove(u16 move,u8 bankAtk,u8 bankDef)

{
  byte bVar1;
  bool8 bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  uint uVar7;
  uint uVar8;
  u8 uVar9;
  uint uVar10;
  uint uVar11;
  
  uVar4 = gNewBS;
  uVar7 = (uint)bankDef;
  uVar5 = (uint)bankAtk;
  uVar8 = move;
  if (uVar8 == 0x385) {
    return 0x6f;
  }
  bVar1 = gBattleMoves[uVar8].z_move_effect;
  uVar10 = (uint)bVar1;
  uVar11 = uVar10 - 1;
  if (0x2d < uVar11) {
    return 0;
  }
                      switch(uVar11) {
  case 33:
    return 0x20;
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
    if ((gBattleMons[uVar5].statStages[uVar11] < 0xc) ||
       (((gBattleTypeFlags << 0x1f < 0 && (gBattleMons[uVar5 ^ 2].hp != 0)) &&
        (gBattleMons[uVar5 ^ 2].statStages[uVar11] < 0xc)))) {
      return bVar1 + 9;
    }
    break;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    if ('\0' < *(char *)((int)gBattleMons[uVar7].moves + uVar10 + 7)) {
      return bVar1 + 0xc;
    }
    break;
  case 10:
    uVar4 = (uint)gBattleWeather;
    uVar9 = 0x89;
    uVar8 = 0x7860;
    goto LAB_090ddaac;
  case 11:
    uVar8 = 0x7807;
    uVar4 = (uint)gBattleWeather;
    uVar9 = 0x88;
    goto LAB_090ddaac;
  case 12:
    uVar8 = 0x7818;
    uVar4 = (uint)gBattleWeather;
    uVar9 = 0x73;
    goto LAB_090ddaac;
  case 13:
    uVar8 = 0x7980;
    uVar4 = (uint)gBattleWeather;
    uVar9 = 0xa4;
    goto LAB_090ddaac;
  case 14:
  case 15:
  case 16:
  case 17:
    if (((-1 < gBattleTypeFlags << 5) || ((_UNK_0203e044 & 0xf) == 0)) &&
       ((uint)gTerrainType != uVar10 - 0xe)) {
      return 0xe2;
    }
    break;
  case 22:
    uVar4 = CanBeParalyzed(uVar7,1);
    uVar9 = 0x43;
    goto LAB_090ddafc;
  case 29:
    uVar4 = CanBePoisoned(uVar7,uVar5,1);
    uVar9 = 0x42;
    goto LAB_090ddafc;
  case 23:
  case 41:
    uVar4 = CanBeConfused(uVar7,1);
    uVar9 = 0x31;
    goto LAB_090ddafc;
  case 24:
    if (-1 < (int)(gBattleMons[uVar5].status2 << 0xb)) {
      return 0x2f;
    }
    break;
  case 25:
    bVar2 = IsTrapped(bankDef,1);
    uVar4 = (uint)bVar2;
    uVar9 = 0x6a;
    goto joined_r0x090ddb38;
  case 26:
    iVar3 = GetBattlerSide(uVar5,uVar5,0xc,&GetBattlerSide);
    uVar9 = 0x41;
    uVar6 = (ushort)*(byte *)(uVar4 + iVar3 + 0x15);
    goto joined_r0x090ddc18;
  case 27:
    uVar4 = sub_9075a8c(uVar7);
    uVar9 = 0x78;
    goto LAB_090ddafc;
  case 28:
    if (*(short *)(gNewBS + (gBattlerPartyIndexes[uVar5] + 0x7c) * 2 + 6) == 0) {
      return 0;
    }
    iVar3 = sub_90a52de();
    if (iVar3 == 0) {
      return 0;
    }
    uVar6 = gBattleMons[uVar5].item;
    uVar9 = 0xb8;
    goto joined_r0x090ddc18;
  case 30:
    iVar3 = GetBattlerSide(uVar7,uVar5,0xc,&GetBattlerSide);
    iVar3 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x1b;
    goto joined_r0x090ddbc6;
  case 42:
    iVar3 = GetBattlerSide(uVar7);
    iVar3 = (uint)(byte)(&gSideTimers[0].field_0xa)[iVar3 * 0xb] << 0x19;
joined_r0x090ddbc6:
    if (-1 < iVar3) {
      return 0x70;
    }
    break;
  case 31:
    iVar3 = GetBattlerSide(uVar7);
    uVar4 = gNewBS;
    if ((((gSideStatuses[iVar3] & 0x123) != 0) ||
        (iVar3 = GetBattlerSide(uVar7), *(char *)(uVar4 + iVar3 + 0x15) != '\0')) ||
       (iVar3 = GetBattlerSide(uVar5), (gSideStatuses[iVar3] & 0x10) != 0)) {
      return 0x81;
    }
    iVar3 = GetBattlerSide(uVar7);
    uVar9 = 0x81;
    uVar6 = gSideStatuses[iVar3] & 0x10;
joined_r0x090ddc18:
    if (uVar6 == 0) {
      return uVar9;
    }
    break;
  case 34:
    return 100;
  case 35:
    uVar4 = sub_90750c4();
    uVar9 = 0xe4;
    goto joined_r0x090ddb38;
  case 37:
  case 45:
    return 0x2a;
  case 38:
    iVar3 = CanBePutToSleep(uVar7,1,uVar5,uVar10,uVar8,uVar7,uVar7);
    if (iVar3 == 0) {
      return 0;
    }
    uVar8 = 0x1800;
    uVar4 = gStatuses3[uVar7];
    uVar9 = 0xbb;
LAB_090ddaac:
    uVar4 = uVar4 & uVar8;
joined_r0x090ddb38:
    if (uVar4 == 0) {
      return uVar9;
    }
    break;
  case 39:
    if (0 < gBattleMons[uVar7].statStages[6]) {
      return 0x18;
    }
    break;
  case 40:
    bVar2 = PartyMemberStatused(bankAtk,0);
    uVar4 = (uint)bVar2;
    uVar9 = 0x66;
    goto LAB_090ddafc;
  case 43:
    uVar4 = func_0x09074c04(uVar7);
    uVar9 = 0xa5;
LAB_090ddafc:
    if (uVar4 != 0) {
      return uVar9;
    }
    break;
  case 44:
    if (0 < gBattleMons[uVar7].statStages[2]) {
      return 0x3c;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
  return 0;
}

// ---- ClearShouldAIUseZMoveByMoveAndMovePos  (ROM 0x90ddcdc)
void ClearShouldAIUseZMoveByMoveAndMovePos(u8 bankAtk,u8 bankDef,u8 movePos)

{
  *(undefined1 *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef) * 4 + (uint)movePos + 0x8b4) = 0xff;
  return;
}

// ---- CalcAIDynamaxMon  (ROM 0x90ddcfc)
void CalcAIDynamaxMon(u8 bank)

{
  ushort uVar1;
  byte bVar2;
  bool8 bVar3;
  uint uVar4;
  Pokemon *mon;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  byte bVar10;
  uint uStack_50;
  uint uStack_4c;
  uint uStack_48;
  int iStack_44;
  uint uStack_40;
  uint uStack_38;
  int iStack_2c;
  undefined1 uStack_1a;
  undefined1 auStack_19 [5];
  
  uVar4 = (uint)bank;
  uStack_38._0_1_ = 0xff;
  if ((gBattleTypeFlags << 1 < 0) && (*(char *)(gNewBS + uVar4 + 0x1a2) == '\0')) {
    mon = (Pokemon *)LoadPartyRange(uVar4,&uStack_1a,auStack_19);
    if (gBattleTypeFlags << 0x1f < 0) {
      uStack_50 = uVar4 ^ 2;
      uStack_48 = uStack_50;
      if (((*(uint *)(&gBitTable + uVar4 * 4) & (uint)gAbsentBattlerFlags) == 0) &&
         (uStack_48 = uVar4,
         (*(uint *)(&gBitTable + uStack_50 * 4) & (uint)gAbsentBattlerFlags) != 0)) {
        uStack_50 = uVar4;
      }
    }
    else {
      uStack_50 = uVar4;
      uStack_48 = uVar4;
    }
    uStack_4c = 0;
    uStack_40 = 0;
    bVar2 = 0;
    uStack_38 = 0xff;
    do {
      if ((((mon->species != 0) && (iVar5 = GetMonData(mon,0x39,0), iVar5 != 0)) &&
          (iVar5 = GetMonData(mon,0x2d,0), iVar5 == 0)) && (iVar5 = sub_908d8f0(mon), iVar5 != 0))
      {
        if ((uint)gBattlerPartyIndexes[uStack_48] == (uStack_4c & 0xffff)) {
          uVar7 = uStack_48;
LAB_090dddca:
          iStack_44 = GetBankItemEffect(uVar7);
          iStack_2c = GetBankAbility(uVar7);
          uVar1 = gBattleMons[uVar7].spAttack;
          iVar5 = gBattleMons[uVar7].statStages[0] * 2;
          uVar6 = udivsi((uint)*(byte *)(iVar5 + 0x9124898) * (uint)gBattleMons[uVar7].attack,
                               *(undefined1 *)(iVar5 + 0x9124899));
          iVar9 = gBattleMons[uVar7].statStages[3] * 2;
          iVar5 = (uint)*(byte *)(iVar9 + 0x9124898) * (uint)uVar1;
          uVar7 = udivsi(iVar5,*(undefined1 *)(iVar9 + 0x9124899),iVar5,&udivsi);
        }
        else {
          if ((uint)gBattlerPartyIndexes[uStack_50] == (uStack_4c & 0xffff)) {
            uVar7 = uStack_50;
            goto LAB_090dddca;
          }
          iStack_44 = sub_9074de4(mon);
          iStack_2c = GetMonAbility(mon);
          uVar6 = (uint)mon->attack;
          uVar7 = (uint)mon->spAttack;
        }
        bVar3 = PhysicalMoveInMonMoveset(mon,3);
        if (bVar3 == 0) {
          bVar3 = SpecialMoveInMonMoveset(mon,3);
          uVar6 = -(uint)(bVar3 != 0) & uVar7;
        }
        else {
          bVar3 = SpecialMoveInMonMoveset(mon,3);
          if ((bVar3 != 0) && (uVar6 < uVar7)) {
            uVar6 = uVar7;
          }
        }
        bVar10 = 4;
        if (((iStack_44 != 0x55) && (bVar10 = 3, iStack_44 != 0x1d)) && (iStack_2c != 0xd7)) {
          iVar5 = AbilityBattleEffects(0x13,0,0xd,0,0);
          if (iVar5 != 0) goto LAB_090dde8e;
          uVar7 = GetMonAbility(mon);
          if (uVar7 == 0x62) {
LAB_090ddf5c:
            uVar8 = 0xc;
LAB_090ddf04:
            iVar5 = sub_908d864(mon,uVar8);
            bVar10 = 2;
            if (iVar5 != 0) goto LAB_090ddf10;
          }
          else {
            if (0x62 < uVar7) {
              if (uVar7 != 0xab) {
                if (uVar7 < 0xac) {
                  if (uVar7 == 0x69) goto LAB_090ddf60;
                  if (uVar7 == 0x7c) goto LAB_090ddef2;
                }
                else {
                  if (uVar7 == 0xcd) goto LAB_090ddee0;
                  if (uVar7 == 0xfa) goto LAB_090ddf60;
                  uVar8 = 0xf;
                  if (uVar7 == 0xb9) goto LAB_090ddf04;
                }
                goto LAB_090dde8e;
              }
LAB_090ddf60:
              uVar8 = 0xe;
              goto LAB_090ddf04;
            }
            if (uVar7 == 0x2c) goto LAB_090ddf5c;
            if (uVar7 < 0x2d) {
              if (uVar7 == 0x21) goto LAB_090ddf5c;
              if (uVar7 == 0x22) {
LAB_090ddee0:
                uVar8 = 0xb;
                goto LAB_090ddf04;
              }
            }
            else {
              if (uVar7 == 0x5f) {
LAB_090ddef2:
                uVar8 = 0xd;
                goto LAB_090ddf04;
              }
              if (uVar7 == 0x60) goto LAB_090ddee0;
            }
          }
LAB_090dde8e:
          bVar10 = 0;
          if ((uVar6 != 0) && (iStack_44 != 0x6a)) {
            bVar10 = iStack_44 != 0x84;
          }
        }
LAB_090ddf10:
        iVar5 = MoveInMonMovesetThatCanChangeByGigantamaxing(mon);
        if (iVar5 != 0) {
          bVar10 = bVar10 + 1;
        }
        if (bVar2 <= bVar10) {
          if (bVar10 == bVar2) {
            if (uStack_40 < uVar6) {
LAB_090ddf68:
              uStack_40 = uVar6 & 0xff;
              uStack_38 = uStack_4c & 0xff;
              bVar2 = bVar10;
            }
          }
          else if (uVar6 != 0) goto LAB_090ddf68;
        }
      }
      uStack_4c = uStack_4c + 1;
      mon = mon + 1;
    } while (uStack_4c != 6);
  }
  uVar7 = gNewBS;
  iVar5 = GetBattlerSide(uVar4);
  *(undefined1 *)(uVar7 + iVar5 + 0x88c) = (undefined1)uStack_38;
  return;
}

// ---- TryReplaceMoveWithZMove  (ROM 0x90de018)
u16 TryReplaceMoveWithZMove(u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = move;
  uVar4 = (uint)bankAtk;
  iVar2 = IsAnyMaxMove(uVar5);
  if (iVar2 == 0) {
    if (((*(char *)(gNewBS + uVar4 + 0x194) == '\0') && (gBattleMoves[uVar5].split != 2)) &&
       (bVar1 = ShouldAIUseZMove(bankAtk,bankDef,move), bVar1 != 0)) {
      uVar3 = FindMovePositionInMoveset(uVar5,uVar4);
      if (uVar3 < 4) {
        uVar4 = sub_90bd7d0(uVar4,uVar3,uVar5);
LAB_090de072:
        if (uVar4 != 0) {
          *(u16 *)(gNewBS + 0x1bc) = move;
          goto LAB_090de02c;
        }
      }
    }
    else {
      iVar2 = IsDynamaxed(uVar4);
      if (((iVar2 != 0) ||
          ((*(char *)(gNewBS + uVar4 + 0x1a2) == '\0' &&
           (iVar2 = sub_90ddfa4(uVar4,bankDef), iVar2 != 0)))) &&
         ((iVar2 = IsRaidBattle(), iVar2 == 0 ||
          ((uVar3 = GetBattlerAtPosition(1), uVar4 != uVar3 ||
           (iVar2 = IsRaidBossUsingRegularMove(uVar4,uVar5), iVar2 == 0)))))) {
        uVar4 = GetMaxMoveByMove(uVar4,uVar5);
        goto LAB_090de072;
      }
    }
  }
  uVar4 = uVar5;
LAB_090de02c:
  return (u16)uVar4;
}

// ---- CalcStrongestMoveIgnoringMove  (ROM 0x90de0dc)
move_t CalcStrongestMoveIgnoringMove(u8 bankAtk,u8 bankDef,bool8 onlySpreadMoves,u16 ignoreMove)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  bool8 bVar5;
  bool8 bVar6;
  byte bVar7;
  byte bVar8;
  bool8 bVar9;
  bool8 bVar10;
  u16 uVar11;
  u16 uVar12;
  ushort uVar13;
  ushort uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  uint uVar27;
  bool bVar28;
  bool bVar29;
  int iStack_b4;
  u8 uStack_74;
  u8 uStack_73;
  
  uVar24 = (uint)bankDef;
  uVar15 = (uint)bankAtk;
  uVar27 = 0;
  uVar4 = gBattleMons[uVar24].hp;
  if (uVar4 == 0) goto LAB_090de282;
  uVar27 = (uint)gBattleMons[uVar15].moves[0];
  bVar5 = BadIdeaToMakeContactWith(bankAtk,bankDef);
  iVar16 = GetBankAbility(uVar15);
  bVar6 = IsTrapped(bankDef,1);
  if (bVar6 == 0) {
    if (((gBattleTypeFlags & 1) == 0) &&
       (uVar21 = ViableMonCountFromBankLoadPartyRange(uVar24), 1 < uVar21)) {
      bVar28 = false;
    }
    else {
      if (-1 < (int)(gBattleTypeFlags << 0x1f)) goto LAB_090de122;
      uVar21 = ViableMonCountFromBankLoadPartyRange(uVar24);
      bVar28 = uVar21 < 3;
    }
  }
  else {
LAB_090de122:
    bVar28 = true;
  }
  iVar17 = IsPlayerInControl(uVar24);
  bVar29 = true;
  if (iVar17 != 0) {
    bVar29 = *(char *)(gNewBS + 0x1cc) != '\0';
  }
  bVar6 = ShouldUseHumanLikelyMove(bankAtk,bankDef);
  iVar17 = GetBankAbility(uVar15);
  Memset(&uStack_74,0,0x5c);
  uVar18 = CheckMoveLimitations(uVar15,0,0xff);
  uStack_74 = bankAtk;
  uStack_73 = bankDef;
  PopulateDamageCalcStructWithBaseAttackerData(&uStack_74);
  PopulateDamageCalcStructWithBaseDefenderData(&uStack_74);
  iStack_b4 = 0;
  uVar21 = 0;
  uVar14 = 0;
  do {
    uVar11 = gBattleMons[uVar15].moves[iStack_b4];
    if (uVar11 == 0) break;
    uVar20 = uVar21;
    uVar13 = uVar14;
    if (uVar11 != ignoreMove) {
      uVar11 = TryReplaceMoveWithZMove(bankAtk,bankDef,uVar11);
      uVar19 = (uint)uVar11;
      if (((((*(uint *)((iStack_b4 + 0x2097917) * 4) & uVar18) == 0) &&
           (gBattleMoves[uVar19].power != 0)) &&
          ((onlySpreadMoves == 0 ||
           (uVar22 = GetBaseMoveTarget(uVar19,uVar15), (uVar22 & 0x28) != 0)))) &&
         ((bVar2 = gBattleMoves[uVar19].effect, bVar2 != 0x26 ||
          (((gBattleMons[uVar24].level <= gBattleMons[uVar15].level &&
            ((((uVar19 != 0x149 || (iVar25 = IsOfType(uVar24,0xf /* Ice */), iVar25 == 0)) &&
              (iVar25 = GetBankAbility(uVar24), iVar25 != 5)) &&
             ((iVar25 = IsDynamaxed(uVar24), iVar25 == 0 ||
              (iVar25 = sub_908ee64(uVar24), iVar25 != 0)))))) &&
           (bVar9 = MoveWillHit(uVar11,bankAtk,bankDef), bVar9 != 0)))))) {
        uVar12 = CalcFinalAIMoveDamage(uVar11,bankAtk,bankDef,1,&uStack_74);
        uVar20 = (uint)uVar12;
        if (uVar21 < uVar20) goto LAB_090de46a;
        if (((uVar20 == uVar21) && (bVar2 != 0x59)) && ((bVar2 & 0xfb) != 0x90)) {
          if (uVar27 == 0xe4) {
            if ((bVar28) || (!bVar29)) goto LAB_090de2f8;
          }
          else {
            if ((uVar19 != 0xe4) || ((bVar28 || (!bVar29)))) {
LAB_090de2f8:
              bVar3 = gBattleMoves[uVar27].effect;
              if (bVar3 != 0x94) {
                bVar7 = PriorityCalc(uVar15,0,uVar19);
                bVar8 = PriorityCalc(uVar15,0,uVar27);
                if (bVar7 <= bVar8) {
                  uVar21 = uVar20;
                  if (bVar7 != bVar8) goto LAB_090de43a;
                  bVar9 = MoveWillHit(uVar11,bankAtk,bankDef);
                  uVar13 = 100;
                  if (bVar9 == 0) {
                    uVar13 = CalcAIAccuracy(uVar11,bankAtk,bankDef);
                  }
                  uVar12 = (u16)uVar27;
                  if (uVar14 == 0) {
                    bVar9 = MoveWillHit(uVar12,bankAtk,bankDef);
                    if (bVar9 == 0) {
                      uVar14 = CalcAIAccuracy(uVar12,bankAtk,bankDef);
                      goto LAB_090de374;
                    }
                    uVar14 = 100;
                    if (uVar13 < 0x65) goto LAB_090de48c;
LAB_090de494:
                    uVar13 = uVar14;
                    iVar25 = CanBeChoiceLocked(uVar15);
                    uVar14 = uVar13;
                    if (iVar25 == 0) {
                      uVar21 = 0;
                      if (bVar5 != 0) {
                        iVar25 = CheckContact(uVar27,uVar15);
                        uVar21 = CheckContact(uVar19,uVar15);
                        if (iVar25 == 0) {
                          if (uVar21 != 0) goto LAB_090de278;
                          goto LAB_090de4a6;
                        }
                        if (uVar21 != 0) {
                          if (bVar3 == 0x1d) {
                            if (bVar2 != 0x1d) goto LAB_090de3a4;
                          }
                          else if (bVar2 == 0x1d) goto LAB_090de278;
                          goto LAB_090de4a6;
                        }
LAB_090de3a4:
                        uVar27 = uVar19;
                        goto LAB_090de278;
                      }
LAB_090de4a6:
                      if (iVar16 != 0x73) {
                        iVar25 = CheckRecoil(uVar27);
                        uVar21 = CheckRecoil(uVar19);
                        if (iVar25 == 0) {
                          if (uVar21 != 0) goto LAB_090de278;
                        }
                        else if (uVar21 == 0) goto LAB_090de3a4;
                      }
                      if (iVar17 != 0xbf) {
                        bVar9 = IsStatRecoilMove(uVar12);
                        bVar10 = IsStatRecoilMove(uVar11);
                        uVar21 = (uint)bVar10;
                        if (bVar9 == 0) {
                          if (uVar21 != 0) goto LAB_090de278;
                        }
                        else if (uVar21 == 0) goto LAB_090de3a4;
                      }
                      if (bVar6 != 0) {
                        uVar11 = PickMoveHumanLikelyToChoose(uVar11,uVar12,bankAtk,bankDef);
                        uVar27 = (uint)uVar11;
                        goto LAB_090de386;
                      }
                      iVar25 = Random2(uVar21);
                      uVar21 = uVar20;
                      if (-1 < iVar25 << 0x1f) goto LAB_090de43a;
                    }
                    else {
                      uVar22 = CalcVisualBasePower(uVar15,0,uVar19,1);
                      uVar23 = CalcVisualBasePower(uVar15,0,uVar27,1);
                      if (uVar22 <= uVar23) goto LAB_090de43a;
                    }
                    uVar21 = uVar20;
                    uVar27 = uVar19;
                  }
                  else {
LAB_090de374:
                    if (uVar13 <= uVar14) {
LAB_090de48c:
                      if (uVar13 != uVar14) goto LAB_090de380;
                      goto LAB_090de494;
                    }
                    if (uVar14 < 100) {
                      uVar27 = uVar19;
                    }
                    else {
LAB_090de380:
                      bVar1 = 99 < uVar13;
                      uVar13 = uVar14;
                      if (bVar1) goto LAB_090de494;
                    }
LAB_090de386:
                    uVar21 = uVar20;
                    uVar14 = uVar13;
                  }
                  goto LAB_090de43a;
                }
              }
LAB_090de46a:
              uVar21 = uVar20;
            }
            uVar27 = uVar19;
            uVar14 = 0;
          }
        }
LAB_090de43a:
        iVar25 = (uVar15 * 4 + uVar24) * 4;
        iVar26 = gNewBS + iVar25;
        *(uint *)(gNewBS + (iVar25 + iStack_b4 + 0xba) * 4 + 8) = uVar20;
        *(bool *)(iVar26 + iStack_b4 + 0x26e) = uVar4 <= uVar20;
        uVar20 = uVar21;
        uVar13 = uVar14;
      }
    }
LAB_090de278:
    iStack_b4 = iStack_b4 + 1;
    uVar21 = uVar20;
    uVar14 = uVar13;
  } while (iStack_b4 != 4);
LAB_090de282:
  return (move_t)uVar27;
}

// ---- RecalcStrongestMoveIgnoringMove  (ROM 0x90de4ec)
void RecalcStrongestMoveIgnoringMove(u8 bankAtk,u8 bankDef,u16 ignoreMove)

{
  uint uVar1;
  move_t mVar2;
  
  uVar1 = gNewBS;
  mVar2 = CalcStrongestMoveIgnoringMove(bankAtk,bankDef,0,ignoreMove);
  *(move_t *)(uVar1 + ((uint)bankAtk * 4 + (uint)bankDef + 0x114) * 2 + 6) = mVar2;
  return;
}

// ---- CalcStrongestMove  (ROM 0x90de514)
move_t CalcStrongestMove(u8 bankAtk,u8 bankDef,bool8 onlySpreadMoves)

{
  move_t mVar1;
  
  mVar1 = CalcStrongestMoveIgnoringMove(bankAtk,bankDef,onlySpreadMoves,0);
  return mVar1;
}

// ---- GetStrongestMove  (ROM 0x90de51e)
u16 GetStrongestMove(u8 bankAtk,u8 bankDef)

{
  move_t mVar1;
  int iVar2;
  
  iVar2 = gNewBS + ((uint)bankAtk * 4 + (uint)bankDef) * 2;
  if (*(short *)(iVar2 + 0x22e) == -1) {
    mVar1 = CalcStrongestMove(bankAtk,bankDef,0);
    *(move_t *)(iVar2 + 0x22e) = mVar1;
  }
  return *(u16 *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef + 0x114) * 2 + 6);
}

// ---- IsStrongestMoveHPDrainingMove  (ROM 0x90de560)
bool8 IsStrongestMoveHPDrainingMove(u8 bankAtk,u8 bankDef)

{
  u16 uVar1;
  
  uVar1 = GetStrongestMove(bankAtk,bankDef);
  return gBattleMoves[uVar1].effect == 3 /* EFFECT_ABSORB */ || gBattleMoves[uVar1].effect == 8 /* EFFECT_DREAM_EATER */;
}

// ---- BadIdeaToRaiseDefenseAgainst  (ROM 0x90de584)
bool8 BadIdeaToRaiseDefenseAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  u16 uVar2;
  int iVar3;
  u8 bankDef_00;
  uint uVar4;
  
  uVar4 = (uint)bankDef;
  do {
    bankDef_00 = (u8)uVar4;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (bVar1 != 0) {
      return 1;
    }
    bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3b);
    if (bVar1 != 0) {
      return 1;
    }
    if (checkPartner == 0) {
      if (1 < amount) {
        return 0;
      }
LAB_090de5fc:
      bVar1 = HasUsedMoveWithEffect(bankDef_00,0x13);
      if (((bVar1 != 0) || (bVar1 = HasUsedMoveWithEffect(bankDef_00,0xcd), bVar1 != 0)) ||
         (bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x45,0x4b), bVar1 != 0)) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
        return 1;
      }
      if (checkPartner == 0) {
        return 0;
      }
    }
    else {
      iVar3 = MoveInMoveset(0x2c4 /* Obstruct */,uVar4);
      if (iVar3 != 0) {
        uVar2 = GetStrongestMove(bankAtk,bankDef_00);
        iVar3 = CheckContact(uVar2,bankAtk);
        if (iVar3 != 0) {
          return 1;
        }
      }
      if (amount < 2) goto LAB_090de5fc;
    }
    if (-1 < gBattleTypeFlags << 0x1f) {
      return 0;
    }
    checkPartner = 0;
    uVar4 = uVar4 ^ 2;
    if (gBattleMons[uVar4].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  } while( true );
}

// ---- GoodIdeaToRaiseDefenseAgainst  (ROM 0x90de634)
bool8 GoodIdeaToRaiseDefenseAgainst(u8 bankAtk,u8 bankDef,u8 amount)

{
  bool8 bVar1;
  u8 uVar2;
  int iVar3;
  
  bVar1 = BadIdeaToRaiseDefenseAgainst(bankAtk,bankDef,amount,1);
  if (bVar1 == 0) {
    uVar2 = GetBankFightingStyle(bankDef);
    uVar2 = BankLikelyToUseMoveSplit(bankDef,uVar2);
    if (uVar2 == 0) {
      return 1;
    }
    iVar3 = MoveInMoveset(0x2b4 /* Body Press */,bankAtk);
    if (iVar3 != 0) {
      return 2;
    }
  }
  return 0;
}

// ---- BadIdeaToRaiseAttackAgainst  (ROM 0x90de66e)
bool8 BadIdeaToRaiseAttackAgainst(u8 bankAtk,u8 bankDef,u8 amount,bool8 checkPartner)

{
  bool8 bVar1;
  u16 uVar2;
  int iVar3;
  u8 bankDef_00;
  uint uVar4;
  
  uVar4 = (uint)bankDef;
  do {
    bankDef_00 = (u8)uVar4;
    bVar1 = BadIdeaToRaiseStatAgainst(bankAtk,bankDef_00,checkPartner);
    if (bVar1 != 0) {
      return 1;
    }
    bVar1 = HasUsedMoveWithEffect(bankDef_00,0x3a);
    if (bVar1 != 0) {
      return 1;
    }
    if (checkPartner == 0) {
      if (1 < amount) {
        return 0;
      }
LAB_090de6e4:
      bVar1 = HasUsedMoveWithEffect(bankDef_00,0x12);
      if (((bVar1 != 0) || (bVar1 = HasUsedMoveWithEffect(bankDef_00,0xcd), bVar1 != 0)) ||
         (bVar1 = HasUsedMoveWithEffectHigherThanChance(bankDef_00,0x44,0x4b), bVar1 != 0)) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
        return 1;
      }
      if (checkPartner == 0) {
        return 0;
      }
    }
    else {
      iVar3 = MoveInMoveset(0x20f /* Kings Shield */,uVar4);
      if (iVar3 != 0) {
        uVar2 = GetStrongestMove(bankAtk,bankDef_00);
        iVar3 = CheckContact(uVar2,bankAtk);
        if (iVar3 != 0) {
          return 1;
        }
      }
      if (amount < 2) goto LAB_090de6e4;
    }
    if (-1 < gBattleTypeFlags << 0x1f) {
      return 0;
    }
    checkPartner = 0;
    uVar4 = uVar4 ^ 2;
    if (gBattleMons[uVar4].hp == 0) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
      return 0;
    }
  } while( true );
}

// ---- GoodIdeaToRaiseAttackAgainst  (ROM 0x90de720)
bool8 GoodIdeaToRaiseAttackAgainst(u8 bankAtk,u8 bankDef,u8 amount)

{
  bool8 bVar1;
  bool bVar2;
  
  bVar1 = BadIdeaToRaiseAttackAgainst(bankAtk,bankDef,amount,1);
  bVar2 = false;
  if (bVar1 == 0) {
    bVar1 = RealPhysicalMoveInMoveset(bankAtk);
    bVar2 = bVar1 != 0;
  }
  return bVar2;
}

// ---- CalcFinalAIMoveDamage  (ROM 0x90de740)
u16 CalcFinalAIMoveDamage(u16 move,u8 bankAtk,u8 bankDef,u8 numHits,void *damageData)

{
  byte bVar1;
  bool8 bVar2;
  u16 uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  u32 uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uStack_20;
  
  uVar4 = (uint)numHits;
  uVar9 = (uint)bankDef;
  uVar11 = (uint)bankAtk;
  uVar10 = move;
  if ((((uVar10 == 0) || (uVar4 == 0)) || (gBattleMoves[uVar10].power == 0)) ||
     ((gBattleMoves[uVar10].split != 2 &&
      (bVar2 = IsDamagingMoveUnusable(move,bankAtk,bankDef), bVar2 != 0)))) {
    return 0;
  }
  bVar1 = gBattleMoves[uVar10].effect;
  if ((bVar1 != 0x59) && (bVar1 != 0x90)) {
    if (bVar1 == 0x26) {
      iVar8 = IsPlayerInControl(uVar11);
      if ((iVar8 == 0) || (bVar2 = MoveWillHit(move,bankAtk,bankDef), bVar2 != 0)) {
        return gBattleMons[uVar9].hp;
      }
      return 1;
    }
    uVar5 = AI_CalcDmg(uVar11,uVar9,uVar10,damageData);
    uVar6 = TryAdjustDamageForRaidBoss(uVar9,uVar5);
    if (gBattleMons[uVar9].hp <= uVar6) {
      return gBattleMons[uVar9].hp;
    }
    if (1 < uVar4) {
      if (damageData == (void *)0x0) {
        uStack_20 = GetBankAbility(uVar11);
        uVar11 = GetBankAbility(uVar9);
      }
      else {
        uStack_20 = (uint)*(byte *)((int)damageData + 0x10);
        uVar11 = (uint)*(byte *)((int)damageData + 0x11);
      }
      uVar7 = GetSecondaryEffectDamage(bankDef);
      iVar8 = IsDamageHalvedDueToFullHP(uVar9,uVar11,uVar10,uStack_20);
      uVar10 = uVar6;
      if (iVar8 != 0) {
        uVar10 = uVar6 << 1;
      }
      uVar6 = uVar6 + (uVar4 - 1) * uVar7 + (uVar4 - 1 & 0xff) * uVar10;
    }
    uVar10 = (uint)gBattleMons[uVar9].hp;
    if (uVar6 < uVar10) {
      uVar10 = uVar6;
    }
    goto LAB_090de7e4;
  }
  uVar4 = AI_SpecialTypeCalc(uVar10,uVar11,uVar9);
  if ((uVar4 & 0x29) == 0) {
    iVar8 = gNewBS + (uVar9 * 4 + uVar11) * 2;
    if (*(short *)(iVar8 + 0x22e) == -1) {
      uVar4 = (uint)*(ushort *)(iVar8 + 0x1ee);
      if (uVar4 == 0xffff) goto LAB_090de7d0;
    }
    else {
      uVar3 = GetStrongestMove(bankDef,bankAtk);
      uVar4 = (uint)uVar3;
    }
    if (((uVar4 == 0) || (gBattleMoves[uVar4].split == 2)) ||
       (iVar8 = MoveBlockedBySubstitute(uVar4,uVar9,uVar11), iVar8 != 0)) goto LAB_090de7d0;
    uVar7 = GetFinalAIMoveDamage((u16)uVar4,bankDef,bankAtk,1,(void *)0x0);
    if (uVar10 == 0x44) {
      iVar8 = CalcMoveSplit(uVar9,uVar4);
      uVar10 = uVar7 << 1;
      if (iVar8 != 0) {
LAB_090de866:
        uVar10 = 0;
      }
    }
    else if (uVar10 == 0xf3) {
      iVar8 = CalcMoveSplit(uVar9,uVar4);
      if (iVar8 != 1) goto LAB_090de866;
      uVar10 = uVar7 << 1;
    }
    else {
      uVar10 = uVar7 * 3 >> 1;
    }
    iVar8 = GetBankAbility(uVar11);
    if (iVar8 == 0x97) {
      uVar10 = uVar10 << 1;
    }
  }
  else {
LAB_090de7d0:
    uVar10 = 0;
  }
  uVar10 = MathMin(uVar10,gBattleMons[uVar9].hp);
LAB_090de7e4:
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return (u16)uVar10;
}

// ---- GetAIAbility  (ROM 0x90dea44)
u8 GetAIAbility(u8 bankAtk,u8 bankDef,u16 move)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = (uint)bankAtk;
  uVar2 = GetBankAbility();
  if ((uVar2 != 0) && (*(char *)(gNewBS + uVar1 + 0x1e9) != '\0')) {
    iVar3 = sub_90de930(uVar1,bankDef,move,1,0);
    if (iVar3 != 0) {
      uVar2 = (uint)*(byte *)(gNewBS + uVar1 + 0x1e9);
    }
  }
  return (u8)uVar2;
}

// ---- GetFinalAIMoveDamage  (ROM 0x90deac4)
u32 GetFinalAIMoveDamage(u16 move,u8 bankAtk,u8 bankDef,u8 numHits,void *damageData)

{
  u16 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  u32 uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  uVar8 = (uint)numHits;
  uVar6 = (uint)bankDef;
  uVar2 = FindMovePositionInMoveset();
  if (uVar2 < 4) {
    iVar7 = (((uint)bankAtk * 4 + uVar6) * 4 + uVar2 + 0xba) * 4;
    uVar2 = *(uint *)(gNewBS + iVar7 + 8);
    if (uVar2 == 0xffffffff) {
      uVar1 = CalcFinalAIMoveDamage(move,bankAtk,bankDef,1,damageData);
      uVar2 = (uint)uVar1;
      *(uint *)(gNewBS + iVar7 + 8) = uVar2;
    }
    uVar9 = uVar8 * uVar2;
    if (1 < uVar8) {
      uVar3 = GetBankAbility((uint)bankAtk);
      uVar4 = GetBankAbility(uVar6);
      uVar5 = GetSecondaryEffectDamage(bankDef);
      iVar7 = IsDamageHalvedDueToFullHP(uVar6,uVar4,move,uVar3);
      uVar9 = uVar2;
      if (iVar7 != 0) {
        uVar9 = uVar2 << 1;
      }
      uVar9 = uVar2 + (uVar8 - 1) * uVar5 + (uVar8 - 1 & 0xff) * uVar9;
    }
    uVar2 = (uint)gBattleMons[uVar6].hp;
    if (uVar9 < gBattleMons[uVar6].hp) {
      uVar2 = uVar9;
    }
  }
  else {
    uVar1 = CalcFinalAIMoveDamage(move,bankAtk,bankDef,numHits,damageData);
    uVar2 = (uint)uVar1;
  }
  return uVar2;
}

// ---- ResistsAllMoves  (ROM 0x90deb8c)
bool8 ResistsAllMoves(u8 bankAtk,u8 bankDef)

{
  u16 move;
  uint uVar1;
  uint uVar2;
  u32 uVar3;
  int iVar4;
  
  uVar1 = CheckMoveLimitations(bankAtk,0,0xff);
  uVar2 = __udivsi3(gBattleMons[bankDef].hp,3);
  iVar4 = 0;
  while( true ) {
    move = GetBattleMonMove(bankAtk,(u8)iVar4);
    if (move == 0 /* - */) {
      return 1;
    }
    if (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar1) == 0) &&
       (uVar3 = GetFinalAIMoveDamage(move,bankAtk,bankDef,1,(void *)0x0), (uVar2 & 0xffff) <= uVar3)
       ) break;
    iVar4 = iVar4 + 1;
    if (iVar4 == 4) {
      return 1;
    }
  }
  return 0;
}

// ---- OnlyBadMovesLeftInMoveset  (ROM 0x90debfc)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

bool8 OnlyBadMovesLeftInMoveset(u8 bankAtk,u8 bankDef)

{
  ushort uVar1;
  uint uVar2;
  u8 uVar3;
  bool8 bVar4;
  u8 uVar5;
  u16 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  u32 uVar10;
  int iVar11;
  uint uVar12;
  bool8 checkConfusion;
  uint uVar13;
  int iVar14;
  char cVar15;
  bool bVar16;
  int iStack_70;
  undefined1 uStack_6c;
  AIScript AStack_60;
  
  uVar2 = gNewBS;
  uVar13 = (uint)bankDef;
  uVar7 = (uint)bankAtk;
  if (*(char *)(gNewBS + uVar7 * 4 + uVar13 + 0x890) != -1) goto LAB_090dee56;
  if (gBattleResources->ai->aiFlags == 1) {
LAB_090dec2e:
    bVar16 = false;
  }
  else {
    uVar8 = CheckMoveLimitations(uVar7,0);
    cVar15 = '\0';
    Memset(&AStack_60,0,0x48);
    PopulateAIScriptStructWithBaseAttackerData(&AStack_60,bankAtk);
    PopulateAIScriptStructWithBaseDefenderData(&AStack_60,bankDef);
    iStack_70 = 0;
    do {
      uVar6 = GetBattleMonMove(bankAtk,(u8)iStack_70);
      uVar9 = (uint)uVar6;
      uVar12 = uVar9;
      if (uVar9 == 0) break;
      if ((*(uint *)((iStack_70 + 0x2097917) * 4) & uVar8) == 0) {
        uVar3 = AIScript_Negatives(bankAtk,bankDef,uVar6,100,&AStack_60);
        uVar12 = (uint)uVar3;
        if (99 < uVar12) {
          if (gBattleMoves[uVar9].split == 2) goto LAB_090dec2e;
          if (gBattleMoves[uVar9].effect == 0xbc /* EFFECT_KNOCK_OFF */) {
            iVar11 = sub_90745b4(uVar13);
            if (iVar11 != 0) goto LAB_090dec2e;
            uVar12 = 0;
          }
          cVar15 = cVar15 + '\x01';
        }
      }
      iStack_70 = iStack_70 + 1;
    } while (iStack_70 != 4);
    iVar11 = IsDoubleBattle(uVar12);
    if ((iVar11 == 0) && (bVar4 = MoveEffectInMoveset(0x6f /* EFFECT_PROTECT */,bankAtk), bVar4 != 0)) goto LAB_090dec2e;
    uVar8 = gBattleMons[uVar7].status2 & 0x1000000;
    if (cVar15 == '\0') {
      if (((uVar8 == 0) ||
          (bVar4 = DamagingMoveThaCanBreakThroughSubstituteInMoveset(bankDef,bankAtk), bVar4 != 0))
         || (bVar4 = IsTakingSecondaryDamage(bankDef,checkConfusion), bVar4 == 0)) {
        bVar4 = ShouldAIFreeChoiceLockWithDynamax(bankAtk,bankDef);
        uVar8 = gNewBS;
        if (bVar4 == 0) goto LAB_090dee44;
        uVar1 = gBattlerPartyIndexes[uVar7];
        iVar11 = GetBattlerSide(uVar7);
        iVar14 = gNewBS + uVar7 * 4;
        *(char *)(uVar8 + iVar11 + 0x88c) = (char)uVar1;
        *(undefined1 *)(iVar14 + uVar13 + 0x8a4) = 1;
      }
      goto LAB_090dec2e;
    }
    if ((((uVar8 != 0) &&
         (bVar4 = DamagingMoveThaCanBreakThroughSubstituteInMoveset(bankDef,bankAtk), bVar4 == 0))
        || (bVar4 = PivotingMoveInMovesetThatAffects(bankAtk,bankDef), bVar4 != 0)) ||
       (((iVar11 = GetBankAbility(uVar13), iVar11 != 0x73 &&
         ((gBattleMons[uVar13].status2 & 0xe000) != 0)) ||
        ((bVar4 = IsTrapped(bankDef,1), bVar4 != 0 &&
         (((int)(gStatuses3[uVar13] << 0x1a) < 0 && ((gDisableStructs[uVar13].field_0xf & 0xf) != 0)
          ))))))) goto LAB_090dec2e;
    uVar6 = GetStrongestMove(bankAtk,bankDef);
    uVar10 = GetFinalAIMoveDamage(uVar6,bankAtk,bankDef,1,(void *)0x0);
    if (gBattleMons[uVar13].hp <= uVar10) goto LAB_090dec2e;
    uVar6 = GetAmountToRecoverBy(bankDef,bankAtk,0xb6);
    if ((uVar6 == 0) && (bVar4 = HealingMoveInMoveset(bankDef), bVar4 == 0)) {
      uVar8 = (uint)gBattleMons[uVar13].hp;
    }
    else {
      uVar8 = (uint)gBattleMons[uVar13].hp + (uint)uVar6 * 2;
    }
    if (uVar8 <= uVar10 * 3) goto LAB_090dec2e;
    bVar4 = ShouldAIFreeChoiceLockWithDynamax(bankAtk,bankDef);
    uVar8 = gNewBS;
    uVar3 = gActiveBattler;
    if (bVar4 != 0) {
      uVar1 = gBattlerPartyIndexes[uVar7];
      iVar11 = GetBattlerSide(uVar7);
      uStack_6c = (undefined1)uVar1;
      *(undefined1 *)(uVar8 + iVar11 + 0x88c) = uStack_6c;
      *(undefined1 *)(gNewBS + uVar7 * 4 + uVar13 + 0x8a4) = 1;
      bVar16 = false;
      goto LAB_090dee46;
    }
    gActiveBattler = bankAtk;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
    uVar5 = GetMostSuitableMonToSwitchIntoFlags();
    uVar8 = (uint)uVar5;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
    gActiveBattler = uVar3;
    if (uVar8 == 0) goto LAB_090dec2e;
    if ((uVar5 & 0x11) == 0) {
      if (-1 < (int)(uVar8 << 0x1e)) {
        if ((int)(uVar8 << 0x1c) < 0) {
          iVar11 = gBattleMons[uVar13].statStages[0] * 2;
          uVar8 = udivsi((uint)gBattleMons[uVar13].attack *
                               (uint)*(byte *)(iVar11 + 0x9124898),
                               *(undefined1 *)(iVar11 + 0x9124899));
          iVar11 = gBattleMons[uVar13].statStages[3] * 2;
          uVar12 = udivsi((uint)gBattleMons[uVar13].spAttack *
                                (uint)*(byte *)(iVar11 + 0x9124898),
                                *(undefined1 *)(iVar11 + 0x9124899),
                                (uint)gBattleMons[uVar13].spAttack,&udivsi);
          bVar4 = PhysicalMoveInMoveset(bankDef);
          if ((bVar4 == 0) || (uVar8 < gBattleMons[uVar7].defense)) {
            bVar4 = SpecialMoveInMoveset(bankDef);
            if (bVar4 == 0) goto LAB_090dec2e;
            bVar16 = gBattleMons[uVar7].spDefense <= uVar12;
            goto LAB_090dee46;
          }
        }
        goto LAB_090dee44;
      }
      bVar4 = ResistsAllMoves(bankDef,uVar3);
      bVar16 = bVar4 == 0;
    }
    else {
LAB_090dee44:
      bVar16 = true;
    }
  }
LAB_090dee46:
  *(bool *)(uVar2 + uVar7 * 4 + uVar13 + 0x890) = bVar16;
LAB_090dee56:
  return *(bool8 *)(gNewBS + uVar7 * 4 + uVar13 + 0x890);
}

// ---- ResistsAllMovesAtFullHealth  (ROM 0x90def80)
bool8 ResistsAllMovesAtFullHealth(u8 bankAtk,u8 bankDef)

{
  ushort uVar1;
  bool8 bVar2;
  
  uVar1 = gBattleMons[bankDef].hp;
  gBattleMons[bankDef].hp = gBattleMons[bankDef].maxHP;
  bVar2 = ResistsAllMoves(bankAtk,bankDef);
  gBattleMons[bankDef].hp = uVar1;
  return bVar2;
}

// ---- CalculateMoveKnocksOutXHits  (ROM 0x90defa0)
bool8 CalculateMoveKnocksOutXHits(u16 move,u8 bankAtk,u8 bankDef,u8 numHits)

{
  u32 uVar1;
  
  uVar1 = GetFinalAIMoveDamage(move,bankAtk,bankDef,numHits,(void *)0x0);
  return gBattleMons[bankDef].hp <= uVar1;
}

// ---- MoveKnocksOutXHits  (ROM 0x90defc4)
bool8 MoveKnocksOutXHits(u16 move,u8 bankAtk,u8 bankDef,u8 numHits)

{
  byte bVar1;
  ushort uVar2;
  bool8 bVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  u8 numHits_00;
  bool8 *pbVar10;
  
  uVar9 = (uint)bankDef;
  uVar8 = (uint)bankAtk;
  uVar6 = move;
  uVar2 = gBattleMons[uVar9].species;
  uVar4 = GetBankAbility(uVar9);
  iVar5 = MoveBlockedBySubstitute(uVar6,uVar8,uVar9);
  if (iVar5 == 0) {
    iVar5 = GetBankAbility(uVar8);
    if ((iVar5 != 0x98) && (iVar5 = CheckTableForMove(uVar6,&UNK_09040136), iVar5 == 0)) {
      uVar7 = CalcMoveSplit(uVar8,uVar6);
      iVar5 = IsAffectedByDisguse(uVar4,uVar2,uVar7);
      if (iVar5 != 0) goto LAB_090deff0;
    }
  }
  else {
LAB_090deff0:
    if (numHits != 0) {
      numHits = numHits - 1;
    }
  }
  iVar5 = (*(code *)0x9074f00)(uVar8,uVar6);
  if ((iVar5 == 1) && (numHits != 0)) {
    numHits = numHits - 1;
  }
  bVar1 = gBattleMoves[uVar6].effect;
  if (bVar1 == 7) {
    if (numHits == 0) {
      return 0;
    }
  }
  else if (bVar1 == 0x50) {
    if (numHits == 0) {
      return 0;
    }
    numHits = numHits - 1;
    if (numHits != 1) {
      if (numHits == 0) {
        return 0;
      }
      if (numHits != 2) goto LAB_090df0a4;
      goto LAB_090df0c2;
    }
  }
  else {
    if (numHits != 1) {
      if (numHits == 0) {
        return 0;
      }
      if (numHits != 2) goto LAB_090df0a4;
      if (bVar1 == 0x94) {
        return 0;
      }
LAB_090df0c2:
      uVar6 = FindMovePositionInMoveset(uVar6,uVar8);
      if (3 < uVar6) {
        numHits = 2;
        goto LAB_090df0a4;
      }
      pbVar10 = (bool8 *)(gNewBS + (uVar8 * 4 + uVar9) * 4 + uVar6 + 0x2ae);
      if (*pbVar10 != 0xff) {
        return *pbVar10;
      }
      numHits_00 = 2;
      goto LAB_090df044;
    }
    if (bVar1 == 0x94) {
      return 0;
    }
  }
  uVar6 = FindMovePositionInMoveset(uVar6,uVar8);
  if (3 < uVar6) {
    numHits = 1;
LAB_090df0a4:
    bVar3 = CalculateMoveKnocksOutXHits(move,bankAtk,bankDef,numHits);
    return bVar3;
  }
  pbVar10 = (bool8 *)(gNewBS + (uVar8 * 4 + uVar9) * 4 + uVar6 + 0x26e);
  numHits_00 = 1;
  if (*pbVar10 != 0xff) {
    return *pbVar10;
  }
LAB_090df044:
  bVar3 = CalculateMoveKnocksOutXHits(move,bankAtk,bankDef,numHits_00);
  *pbVar10 = bVar3;
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return bVar3;
}

// ---- CalcShouldAIDynamax  (ROM 0x90df114)
void CalcShouldAIDynamax(u8 bankAtk,u8 bankDef)

{
  u16 uVar1;
  ushort uVar2;
  ushort uVar3;
  bool8 bVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ushort uVar9;
  uint uVar10;
  char *pcVar11;
  
  uVar8 = (uint)bankDef;
  uVar6 = (uint)bankAtk;
  *(undefined1 *)(gNewBS + uVar6 * 4 + uVar8 + 0x8f4) = 0;
  if ((((uVar6 != uVar8) && (iVar7 = CanDynamax(), iVar7 != 0)) &&
      ((gStatuses3[uVar6] & 0x130400c0) == 0)) &&
     (((-1 < gBattleTypeFlags << 0x1f ||
       (((uVar10 = uVar6 ^ 2, gBattleMons[uVar10].hp == 0 ||
         (*(char *)(gNewBS + uVar10 + 0x19e) == '\0')) && (uVar8 != uVar10)))) &&
      (((iVar7 = IsRaidBattle(), iVar7 == 0 || (uVar10 = GetBattlerAtPosition(1), uVar10 != uVar6)) &&
       (((iVar7 = sub_90746e0(), iVar7 != 0 || (iVar7 = GetBattlerSide(uVar6), iVar7 != 0)
         ) || ((iVar7 = sub_90ad614(), iVar7 != 0 && (iVar7 = GetBattlerPosition(uVar6), iVar7 != 0)))))))
      ))) {
    uVar10 = gNewBS;
    iVar7 = GetBattlerSide(uVar6);
    uVar9 = (ushort)*(byte *)(uVar10 + iVar7 + 0x88c);
    if (uVar9 == gBattlerPartyIndexes[uVar6]) {
      if ((1 < gBattleResources->ai->aiFlags) ||
         (iVar7 = GetBattlerPosition(uVar6,uVar6 * 2,uVar9,&GetBattlerSide), iVar7 == 0)) {
        uVar1 = *(u16 *)(gNewBS + (uVar6 * 4 + uVar8 + 0xf4) * 2 + 6);
        if (((ushort)(uVar1 - 1) < 0xfffe) &&
           ((bVar4 = MoveWouldHitFirst(uVar1,(ushort)bankAtk,(ushort)bankDef), bVar4 != 0 &&
            (bVar4 = MoveKnocksOutXHits(uVar1,bankAtk,bankDef,1), bVar4 != 0)))) {
          return;
        }
        if (((-1 < gBattleTypeFlags << 0x1f) &&
            (uVar10 = ViableMonCountFromBank(uVar6), 1 < uVar10)) ||
           ((gBattleTypeFlags << 0x1f < 0 && (uVar10 = ViableMonCountFromBank(uVar6), 2 < uVar10)))
           ) {
          iVar7 = uVar8 * 4 + uVar6;
          uVar1 = *(u16 *)(gNewBS + (iVar7 + 0xf4) * 2 + 6);
          if ((((ushort)(uVar1 - 1) < 0xfffe) &&
              (bVar4 = MoveWouldHitFirst(uVar1,(ushort)bankDef,(ushort)bankAtk), bVar4 != 0)) &&
             ((uVar10 = FindMovePositionInMoveset(uVar1,uVar8), 3 < uVar10 ||
              (*(char *)(gNewBS + iVar7 * 4 + uVar10 + 0x26e) != '\0')))) {
            uVar9 = gBattleMons[uVar6].hp;
            uVar2 = gBattleMons[uVar6].maxHP;
            sVar5 = func_0x0908eab4(uVar6);
            gBattleMons[uVar6].hp = gBattleMons[uVar6].hp * sVar5;
            sVar5 = func_0x0908eab4(uVar6);
            uVar3 = gBattleMons[uVar6].maxHP;
            pcVar11 = (char *)(gNewBS + uVar6 + 0x1a6);
            *pcVar11 = *pcVar11 + '\x01';
            gBattleMons[uVar6].maxHP = uVar3 * sVar5;
            bVar4 = CalculateMoveKnocksOutXHits(uVar1,bankDef,bankAtk,1);
            pcVar11 = (char *)(gNewBS + uVar6 + 0x1a6);
            *pcVar11 = *pcVar11 + -1;
            gBattleMons[uVar6].maxHP = uVar2;
            gBattleMons[uVar6].hp = uVar9;
            if (bVar4 != 0) {
              return;
            }
          }
        }
        OnlyBadMovesLeftInMoveset(bankAtk,bankDef);
        iVar7 = GetBankItemEffect(uVar6);
        if (((iVar7 == 0x1d) || (iVar7 = GetBankAbility(uVar6), iVar7 == 0xd7)) &&
           (*(char *)(gNewBS + uVar6 * 4 + uVar8 + 0x8a4) == '\0')) {
          return;
        }
      }
      uVar10 = gNewBS;
      iVar7 = gNewBS + uVar6 * 4 + uVar8;
      *(undefined1 *)(iVar7 + 0x8f4) = 1;
      *(undefined2 *)(uVar10 + (uVar6 * 4 + uVar8 + 0x114) * 2 + 6) = 0xffff;
      *(undefined1 *)(iVar7 + 0x820) = 0xff;
      *(undefined1 *)(iVar7 + 0x830) = 0xff;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return;
}

// ---- CalcShouldAIUseZMove  (ROM 0x90df3c0)
bool8 CalcShouldAIUseZMove(u8 bankAtk,u8 bankDef,u16 move)

{
  ushort uVar1;
  bool8 bVar2;
  u16 move_00;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  byte bVar12;
  uint uStack_24;
  
  uVar11 = move;
  uVar10 = (uint)bankDef;
  uVar9 = (uint)bankAtk;
  if ((gBattleTypeFlags << 0x1f < 0) && ((uVar9 ^ 2) == uVar10)) {
    return 0;
  }
  if (*(char *)(gNewBS + uVar9 + 0x194) != '\0') {
    return 0;
  }
  iVar3 = sub_90bd7d0(uVar9,0xff,uVar11);
  uStack_24 = (uint)*(ushort *)(gNewBS + (uVar10 * 4 + uVar9 + 0xf4) * 2 + 6);
  if (uStack_24 == 0xffff) {
    uStack_24 = 0;
  }
  if (iVar3 == 0) {
    return 0;
  }
  if (iVar3 != 0xffff) {
    iVar4 = GetBankAbility(uVar9);
    uVar5 = GetBankAbility(uVar10);
    uVar1 = gBattleMons[uVar10].species;
    iVar6 = sub_905fa0c(uVar5,iVar4);
    uVar5 = uVar5 & -(uint)(iVar6 == 0);
    if ((uVar11 == 0xfc) && (bVar2 = ShouldUseFakeOut(bankAtk,bankDef,(u8)uVar5), bVar2 != 0)) {
      return 0;
    }
    iVar6 = IsTargetAbilityIgnored(uVar5,iVar4,iVar3);
    iVar7 = MoveBlockedBySubstitute(iVar3,uVar9,uVar10);
    if (iVar7 != 0) {
      return 0;
    }
    if (((uStack_24 == 0xa4) &&
        (bVar2 = MoveWouldHitFirst((u16)iVar3,(ushort)bankAtk,(ushort)bankDef), bVar2 == 0)) &&
       (iVar7 = MoveIgnoresSubstitutes(iVar3,iVar4), iVar7 == 0)) {
      return 0;
    }
    uVar8 = CalcMoveSplit(uVar9,iVar3);
    iVar3 = IsAffectedByDisguse(uVar5 & -(uint)(iVar6 == 0),uVar1,uVar8);
    if (iVar3 != 0) {
      return 0;
    }
    if (uStack_24 == 0xb6) {
      return 0;
    }
    if (uStack_24 == 0x20f) {
      return 0;
    }
    if (uStack_24 == 0x237) {
      return 0;
    }
    if (uStack_24 == 0x2c4) {
      return 0;
    }
    if (uStack_24 == 0x318) {
      return 0;
    }
    iVar3 = IsDynamaxed(uVar10);
    if ((iVar3 != 0) && (gBattleMoves[uStack_24].split == 2)) {
      return 0;
    }
    iVar3 = IsRaidBattle();
    if (((iVar3 != 0) && (iVar3 = sub_908ee64(uVar10), iVar3 != 0)) &&
       (iVar3 = GetBattlerSide(uVar9), iVar3 == 0)) {
      uVar5 = uVar9 ^ 2;
      move_00 = GetAIChosenMove((u8)uVar5,bankDef);
      if (gBattleMoves[move_00].split == 2) {
        return 0;
      }
      bVar2 = MoveWouldHitFirst(move_00,(u16)uVar5,(ushort)bankAtk);
      if (bVar2 != 0) {
        return 0;
      }
      if ((gChosenMovesByBanks[uVar5] != 0) && (gBattleStruct->moveTarget[uVar5] != uVar10)) {
        return 0;
      }
    }
    bVar12 = gBattleMoves[uVar11].effect;
    if (bVar12 == 0x91) {
      return 1;
    }
    if (bVar12 < 0x92) {
      if (bVar12 == 0x4b) {
        return 1;
      }
      if (bVar12 == 0x50) {
        return 1;
      }
    }
    else {
      if (bVar12 == 0x9b) {
        return 1;
      }
      if (bVar12 == 0xcc) {
        return 1;
      }
      if (bVar12 == 0x97) {
        return 1;
      }
    }
    bVar2 = IsStatRecoilMove(move);
    if (bVar2 == 0) {
      if (iVar4 != 0x73) goto LAB_090df602;
LAB_090df5d6:
      bVar2 = MoveKnocksOutXHits(move,bankAtk,bankDef,1);
      if ((bVar2 != 0) &&
         (((bVar2 = MoveWillHit(move,bankAtk,bankDef), bVar2 != 0 ||
           (uVar5 = AccuracyCalc(uVar11,uVar9,uVar10), 0x59 < uVar5)) &&
          (uVar5 = ViableMonCountFromBank(uVar10), 1 < uVar5)))) {
        return 0;
      }
    }
    else if (iVar4 == 0xbf) {
LAB_090df602:
      iVar3 = CheckRecoil(uVar11);
      if (iVar3 == 0) goto LAB_090df5d6;
    }
    iVar3 = IsTypeZCrystal(gBattleMons[uVar9].item,0);
    if ((iVar3 != 0) && (bVar2 = MoveEffectInMoveset(0xeb /* EFFECT_FAIRY_LOCK_HAPPY_HOUR */,bankAtk), bVar2 != 0)) {
      return 0;
    }
    if (uVar11 == 0x265) {
      uVar9 = sub_90dd85a(uVar10);
LAB_090df56e:
      return uVar9 == 0;
    }
sw_df630_5:
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
    return 1;
  }
  if (0x1c < gBattleMoves[uVar11].z_move_effect) {
    return 1;
  }
                      switch(gBattleMoves[uVar11].z_move_effect) {
  case 5:
  case 7:
    goto sw_df630_5;
  case 1:
    iVar3 = 1;
    do {
      while ((iVar3 == 1 &&
             ((bVar2 = RealPhysicalMoveInMoveset(bankAtk), bVar2 == 0 ||
              (bVar2 = SpecialMoveInMoveset(bankAtk), bVar2 == 0))))) {
        iVar3 = 2;
      }
      if (gBattleMons[uVar9].statStages[iVar3 + -1] < 6) {
        return 1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 8);
    break;
  case 2:
    uVar9 = StatsMaxed(uVar9);
    goto LAB_090df56e;
  case 3:
    return ~(byte)(gBattleMons[uVar9].status2 >> 0x14) & 1;
  case 4:
    return (byte)gBattleTypeFlags & 1;
  case 8:
  case 15:
  case 22:
    if (gBattleMons[uVar9].statStages[0] < 0xc) {
      bVar2 = RealPhysicalMoveInMoveset(bankAtk);
LAB_090df71e:
      return 1 - (bVar2 == 0);
    }
    break;
  case 9:
  case 16:
  case 23:
    bVar12 = gBattleMons[uVar9].statStages[1];
    goto LAB_090df730;
  case 11:
  case 18:
  case 25:
    if (gBattleMons[uVar9].statStages[3] < 0xc) {
      bVar2 = SpecialMoveInMoveset(bankAtk);
      goto LAB_090df71e;
    }
    break;
  case 12:
  case 19:
  case 26:
    bVar12 = gBattleMons[uVar9].statStages[4];
    goto LAB_090df730;
  case 10:
  case 17:
  case 24:
    bVar12 = gBattleMons[uVar9].statStages[2];
    goto LAB_090df730;
  case 13:
  case 20:
  case 27:
    if (gBattleMons[uVar9].statStages[5] < 0xc) {
      bVar2 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,0x5a,0);
      goto LAB_090df71e;
    }
    break;
  case 14:
  case 21:
  case 28:
    bVar12 = gBattleMons[uVar9].statStages[6];
LAB_090df730:
    return (bVar12 < 0xc) - ((char)bVar12 >> 7);
  case 6:
    if (gBattleMons[uVar9].hp != gBattleMons[uVar9].maxHP) {
      return 1;
    }
    if (gBattleTypeFlags << 0x1f < 0) {
      return 1;
    }
    if (gBattleMoves[uVar11].effect == 0x8e /* EFFECT_BELLY_DRUM */) {
      return 1;
    }
    if (uStack_24 != 0) {
      bVar2 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
      uVar9 = (uint)bVar2;
      goto LAB_090df56e;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return 0;
}

// ---- ShouldAIUseZMoveByMoveAndMovePos  (ROM 0x90df7f4)
bool8 ShouldAIUseZMoveByMoveAndMovePos(u8 bankAtk,u8 bankDef,u16 move,u8 movePos)

{
  bool8 bVar1;
  bool8 *pbVar2;
  
  pbVar2 = (bool8 *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef) * 4 + (uint)movePos + 0x8b4);
  bVar1 = *pbVar2;
  if (bVar1 == 0xff) {
    bVar1 = CalcShouldAIUseZMove(bankAtk,bankDef,move);
    *pbVar2 = bVar1;
  }
  return bVar1;
}

// ---- ShouldAIUseZMove  (ROM 0x90df824)
bool8 ShouldAIUseZMove(u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  uint uVar2;
  
  uVar2 = FindMovePositionInMoveset(move,bankAtk);
  if (uVar2 < 4) {
    bVar1 = ShouldAIUseZMoveByMoveAndMovePos(bankAtk,bankDef,move,(u8)uVar2);
  }
  else {
    bVar1 = CalcShouldAIUseZMove(bankAtk,bankDef,move);
  }
  return bVar1;
}

// ---- CanKnockOutWithoutMove  (ROM 0x90df84c)
bool8 CanKnockOutWithoutMove(u16 ignoredMove,u8 bankAtk,u8 bankDef,bool8 ignoreFutureAttacks)

{
  bool8 bVar1;
  bool8 bVar2;
  u16 move;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  bVar1 = IsBankAsleep(bankAtk);
  bVar2 = IsBankIncapacitated(bankAtk);
  if ((bVar2 == 0) &&
     (((*(uint *)(&gBitTable + (uint)bankAtk * 4) | *(uint *)(&gBitTable + (uint)bankDef * 4))
      & (uint)gAbsentBattlerFlags) == 0)) {
    uVar3 = CheckMoveLimitations((uint)bankAtk,0,0xff);
    iVar5 = 0;
    do {
      move = GetBattleMonMove(bankAtk,(u8)iVar5);
      uVar4 = move;
      if ((uVar4 != ignoredMove) &&
         ((ignoreFutureAttacks == 0 || (gBattleMoves[uVar4].effect != 0x94 /* EFFECT_FUTURE_SIGHT */)))) {
        if (uVar4 == 0) {
          return 0;
        }
        if ((((bVar1 == 0) || (uVar4 == 0xad)) &&
            ((*(uint *)((iVar5 + 0x2097917) * 4) & uVar3) == 0)) &&
           (bVar2 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar2 != 0)) {
          return 1;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 4);
  }
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
  return 0;
}

// ---- CanKnockOutWithFasterMove  (ROM 0x90df984)
bool8 CanKnockOutWithFasterMove(u8 bankAtk,u8 bankDef,u16 defMove)

{
  bool8 bVar1;
  bool8 bVar2;
  u16 move;
  uint uVar3;
  int iVar4;
  
  bVar1 = IsBankAsleep(bankAtk);
  if (((gBattleMons[bankAtk].hp != 0) && (gBattleMons[bankDef].hp != 0)) &&
     (bVar2 = IsBankIncapacitated(bankAtk), bVar2 == 0)) {
    uVar3 = CheckMoveLimitations((uint)bankAtk,0,0xff);
    iVar4 = 0;
    do {
      move = GetBattleMonMove(bankAtk,(u8)iVar4);
      if (move == 0 /* - */) {
        return 0;
      }
      if (((bVar1 == 0) || (move == 0xad /* Snore */)) &&
         (((*(uint *)((iVar4 + 0x2097917) * 4) & uVar3) == 0 &&
          ((bVar2 = MoveKnocksOutXHits(move,bankAtk,bankDef,1), bVar2 != 0 &&
           (bVar2 = MoveWouldHitBeforeOtherMove(move,bankAtk,defMove,bankDef), bVar2 != 0)))))) {
        return 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
  }
  return 0;
}

// ---- CanKnockOutAfterHealing  (ROM 0x90dfb5c)
bool8 CanKnockOutAfterHealing(u8 bankAtk,u8 bankDef,u16 healAmount,u8 numHits,bool8 dealOneHitFirst)

{
  ushort uVar1;
  bool8 bVar2;
  bool8 bVar3;
  u16 uVar4;
  ushort uVar5;
  u16 uVar6;
  uint uVar7;
  u32 uVar8;
  uint uVar9;
  int iVar10;
  int iStack_34;
  ushort uStack_2c;
  
  uVar9 = (uint)bankDef;
  bVar2 = IsBankAsleep(bankAtk);
  bVar3 = IsBankIncapacitated(bankAtk);
  if ((bVar3 == 0) &&
     (((uint)gAbsentBattlerFlags &
      (*(uint *)(&gBitTable + (uint)bankAtk * 4) | *(uint *)(&gBitTable + uVar9 * 4))) == 0))
  {
    uVar7 = CheckMoveLimitations((uint)bankAtk,0,0xff);
    uVar1 = gBattleMons[uVar9].hp;
    if (dealOneHitFirst == 0) {
      uVar5 = MathMin((uint)healAmount + (uint)uVar1,gBattleMons[uVar9].maxHP);
      gBattleMons[uVar9].hp = uVar5;
      iVar10 = 0;
      do {
        uVar6 = GetBattleMonMove(bankAtk,(u8)iVar10);
        if (uVar6 == 0) break;
        if (((bVar2 == 0) || (uVar6 == 0xad)) &&
           ((*(uint *)((iVar10 + 0x2097917) * 4) & uVar7) == 0)) {
          uVar6 = CalcFinalAIMoveDamage(uVar6,bankAtk,bankDef,numHits,(void *)0x0);
          if (gBattleMons[uVar9].hp <= uVar6) {
            gBattleMons[uVar9].hp = uVar1;
            return 1;
          }
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 != 4);
    }
    else {
      iStack_34 = 0;
      do {
        uVar6 = GetBattleMonMove(bankAtk,(u8)iStack_34);
        if (uVar6 == 0) break;
        if (((bVar2 == 0) || (uVar6 == 0xad)) &&
           ((uVar7 & *(uint *)((iStack_34 + 0x2097917) * 4)) == 0)) {
          uVar4 = CalcFinalAIMoveDamage(uVar6,bankAtk,bankDef,1,(void *)0x0);
          if ((uint)uVar1 <= (uint)uVar4) {
            gBattleMons[uVar9].hp = uVar1;
            return 1;
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
          }
          gBattleMons[uVar9].hp = (uVar1 + healAmount) - uVar4;
          uVar4 = GetAmountToRecoverBy(bankDef,0,0xb6);
          gBattleMons[uVar9].hp = uVar4 + gBattleMons[uVar9].hp;
          uVar8 = GetSecondaryEffectDamage(bankDef);
          if (uVar8 < gBattleMons[uVar9].hp) {
            uStack_2c = gBattleMons[uVar9].hp - (short)uVar8;
          }
          else {
            uStack_2c = 0;
          }
          gBattleMons[uVar9].hp = uStack_2c;
          uVar5 = MathMin(gBattleMons[uVar9].hp,gBattleMons[uVar9].maxHP);
          gBattleMons[uVar9].hp = uVar5;
          uVar6 = CalcFinalAIMoveDamage(uVar6,bankAtk,bankDef,numHits,(void *)0x0);
          if (gBattleMons[uVar9].hp <= uVar6) {
            gBattleMons[uVar9].hp = uVar1;
            return 1;
          }
        }
        iStack_34 = iStack_34 + 1;
      } while (iStack_34 != 4);
    }
    gBattleMons[uVar9].hp = uVar1;
  }
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
  return 0;
}

// ---- IsStrongestMove  (ROM 0x90dfe00)
bool8 IsStrongestMove(u16 currentMove,u8 bankAtk,u8 bankDef)

{
  move_t mVar1;
  int iVar2;
  
  iVar2 = gNewBS + ((uint)bankAtk * 4 + (uint)bankDef) * 2;
  if (*(short *)(iVar2 + 0x22e) == -1) {
    mVar1 = CalcStrongestMove(bankAtk,bankDef,0);
    *(move_t *)(iVar2 + 0x22e) = mVar1;
  }
  return *(u16 *)(gNewBS + ((uint)bankAtk * 4 + (uint)bankDef + 0x114) * 2 + 6) == currentMove;
}

// ---- Can2HKO  (ROM 0x90dfe50)
bool8 Can2HKO(u8 bankAtk,u8 bankDef)

{
  uint uVar1;
  bool8 bVar2;
  move_t mVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = (uint)bankDef;
  iVar6 = (uint)bankAtk * 4;
  if (*(char *)(gNewBS + iVar6 + uVar4 + 0x830) == -1) {
    iVar5 = gNewBS + (iVar6 + uVar4) * 2;
    if (*(short *)(iVar5 + 0x22e) == -1) {
      mVar3 = CalcStrongestMove(bankAtk,bankDef,0);
      *(move_t *)(iVar5 + 0x22e) = mVar3;
    }
    uVar1 = gNewBS;
    bVar2 = MoveKnocksOutXHits(*(u16 *)(gNewBS + (iVar6 + uVar4 + 0x114) * 2 + 6),bankAtk,bankDef,2)
    ;
    *(bool8 *)(uVar1 + iVar6 + uVar4 + 0x830) = bVar2;
  }
  return *(bool8 *)(gNewBS + (uint)bankAtk * 4 + uVar4 + 0x830);
}

// ---- CanKnockOut  (ROM 0x90dfed4)
bool8 CanKnockOut(u8 bankAtk,u8 bankDef)

{
  uint uVar1;
  bool8 bVar2;
  move_t mVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar5 = (uint)bankDef;
  uVar4 = (uint)bankAtk;
  if (((gBattleMons[uVar4].hp == 0) || (gBattleMons[uVar5].hp == 0)) ||
     (bVar2 = IsBankIncapacitated(bankAtk), bVar2 != 0)) {
    bVar2 = 0;
  }
  else {
    iVar7 = uVar4 * 4;
    if (*(char *)(gNewBS + iVar7 + uVar5 + 0x820) == -1) {
      iVar6 = gNewBS + (iVar7 + uVar5) * 2;
      if (*(short *)(iVar6 + 0x22e) == -1) {
        mVar3 = CalcStrongestMove(bankAtk,bankDef,0);
        *(move_t *)(iVar6 + 0x22e) = mVar3;
      }
      uVar1 = gNewBS;
      bVar2 = MoveKnocksOutXHits(*(u16 *)(gNewBS + (iVar7 + uVar5 + 0x114) * 2 + 6),bankAtk,bankDef,
                                 1);
      *(bool8 *)(uVar1 + iVar7 + uVar5 + 0x820) = bVar2;
      iVar7 = gNewBS + iVar7 + uVar5;
      if (*(char *)(iVar7 + 0x820) != '\0') {
        *(undefined1 *)(iVar7 + 0x830) = 1;
      }
    }
    bVar2 = *(bool8 *)(gNewBS + uVar4 * 4 + uVar5 + 0x820);
  }
  return bVar2;
}

// ---- GoodIdeaToLowerEvasion  (ROM 0x90dffa0)
bool8 GoodIdeaToLowerEvasion(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = (uint)bankDef;
  iVar2 = GetBankAbility(uVar5,bankAtk,move);
  iVar3 = IsClearBodyAbility();
  if ((((iVar3 == 0) && (iVar3 = AbilityPreventsLoweringAtk(iVar2,7), iVar3 == 0)) &&
      (iVar3 = sub_905fb84(iVar2), iVar3 == 0)) && (iVar2 != 0xbf)) {
    if (6 < gBattleMons[uVar5].statStages[6]) {
      return 1;
    }
    bVar1 = MoveInMovesetWithAccuracyLessThan(bankAtk,bankDef,0x5a,1);
    if (bVar1 != 0) {
      uVar4 = SpeedCalc(bankAtk);
      uVar5 = SpeedCalc(uVar5);
      if (uVar4 < uVar5) {
        bVar1 = Can2HKO(bankDef,bankAtk);
      }
      else {
        bVar1 = CanKnockOut(bankDef,bankAtk);
      }
      return bVar1 == 0;
    }
  }
  return 0;
}

// ---- GoodIdeaToLowerAccuracy  (ROM 0x90e0024)
bool8 GoodIdeaToLowerAccuracy(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if ((bVar1 != 0) || (bVar1 = CanKnockOut(bankAtk,bankDef), bVar4 = false, bVar1 == 0)) {
    iVar2 = GetBankAbility(bankDef);
    if ((iVar2 == 0xbf) || (iVar3 = IsClearBodyAbility(), iVar3 != 0)) {
      bVar4 = false;
    }
    else {
      iVar2 = AbilityPreventsLoweringAtk(iVar2,6);
      bVar4 = iVar2 == 0;
    }
  }
  return bVar4;
}

// ---- GoodIdeaToLowerSpeed  (ROM 0x90e006c)
bool8 GoodIdeaToLowerSpeed(u8 bankDef,u8 bankAtk,u16 move,u8 reduceBy)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if (bVar1 == 0) {
    bVar1 = CanKnockOut(bankAtk,bankDef);
    bVar6 = false;
    if (bVar1 != 0) goto LAB_090e00ac;
  }
  iVar2 = GetBankAbility(bankDef);
  uVar3 = SpeedCalc(bankAtk);
  uVar4 = SpeedCalc(bankDef);
  if ((((uVar4 < uVar3) || (iVar2 == 0xbf)) || (iVar5 = IsClearBodyAbility(iVar2), iVar5 != 0)) ||
     (iVar2 = AbilityPreventsLoweringAtk(iVar2,3), iVar2 != 0)) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
    if ((gBattleTypeFlags & 1) != 0) {
      bVar1 = WillBeFasterAfterSpeedDrop(bankAtk,bankDef,reduceBy);
      bVar6 = bVar1 != 0;
    }
  }
LAB_090e00ac:
  return bVar6;
}

// ---- GoodIdeaToLowerSpDef  (ROM 0x90e00e8)
bool8 GoodIdeaToLowerSpDef(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if ((bVar1 != 0) || (bVar1 = CanKnockOut(bankAtk,bankDef), bVar4 = false, bVar1 == 0)) {
    iVar2 = GetBankAbility((uint)bankDef);
    if (((gBattleMons[bankDef].statStages[4] < 5) ||
        (((bVar1 = SpecialMoveInMoveset(bankAtk), bVar1 == 0 ||
          (iVar3 = IsClearBodyAbility(iVar2), iVar3 != 0)) ||
         (iVar3 = AbilityPreventsLoweringAtk(iVar2,5), iVar3 != 0)))) ||
       (iVar3 = sub_905fb84(iVar2), iVar3 != 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = iVar2 != 0xbf;
    }
  }
  return bVar4;
}

// ---- GoodIdeaToLowerSpAtk  (ROM 0x90e0160)
bool8 GoodIdeaToLowerSpAtk(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if ((bVar1 != 0) || (bVar1 = CanKnockOut(bankAtk,bankDef), bVar4 = false, bVar1 == 0)) {
    iVar2 = GetBankAbility((uint)bankDef);
    if (((gBattleMons[bankDef].statStages[3] < 5) ||
        (((bVar1 = SpecialMoveInMoveset(bankDef), bVar1 == 0 ||
          (iVar3 = IsClearBodyAbility(iVar2), iVar3 != 0)) ||
         (iVar3 = AbilityPreventsLoweringAtk(iVar2,4), iVar3 != 0)))) ||
       (iVar3 = sub_905fb84(iVar2), iVar3 != 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = iVar2 != 0xbf;
    }
  }
  return bVar4;
}

// ---- GoodIdeaToLowerDefense  (ROM 0x90e01d8)
bool8 GoodIdeaToLowerDefense(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if ((bVar1 != 0) || (bVar1 = CanKnockOut(bankAtk,bankDef), bVar4 = false, bVar1 == 0)) {
    iVar2 = GetBankAbility((uint)bankDef);
    if (((gBattleMons[bankDef].statStages[1] < 5) ||
        (((bVar1 = PhysicalMoveInMoveset(bankAtk), bVar1 == 0 ||
          (iVar3 = IsClearBodyAbility(iVar2), iVar3 != 0)) ||
         (iVar3 = AbilityPreventsLoweringAtk(iVar2,2), iVar3 != 0)))) ||
       (iVar3 = sub_905fb84(iVar2), iVar3 != 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = iVar2 != 0xbf;
    }
  }
  return bVar4;
}

// ---- GoodIdeaToLowerAttack  (ROM 0x90e0250)
bool8 GoodIdeaToLowerAttack(u8 bankDef,u8 bankAtk,u16 move)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  
  bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
  if (((((bVar1 == 0) && (bVar1 = CanKnockOut(bankAtk,bankDef), bVar1 != 0)) ||
       (bVar1 = WillFaintFromSecondaryDamage(bankDef), bVar1 != 0)) ||
      ((iVar2 = GetBankAbility((uint)bankDef), gBattleMons[bankDef].statStages[0] < 5 ||
       (bVar1 = RealPhysicalMoveInMoveset(bankDef), bVar1 == 0)))) ||
     ((iVar3 = IsClearBodyAbility(iVar2), iVar3 != 0 ||
      ((iVar3 = AbilityPreventsLoweringAtk(iVar2,1), iVar3 != 0 ||
       (iVar3 = sub_905fb84(iVar2), iVar3 != 0)))))) {
    bVar1 = 0;
  }
  else {
    bVar1 = 1 - (iVar2 == 0xbf);
  }
  return bVar1;
}

// ---- UpdateBestDoubleKillingMoveScore  (ROM 0x90e03c4)
void UpdateBestDoubleKillingMoveScore
               (u8 bankAtk,u8 bankDef,u8 bankAtkPartner,u8 bankDefPartner,s8 *bestMoveScores,
               u16 *bestMove)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  bool8 bVar4;
  byte bVar5;
  u16 uVar6;
  u16 uVar7;
  u16 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  u32 uVar14;
  uint uVar15;
  undefined4 uVar16;
  uint uVar17;
  uint extraout_r1;
  u8 uVar18;
  uint uVar19;
  bool bVar20;
  ushort uVar21;
  uint uVar22;
  uint uVar23;
  int iVar24;
  uint *puVar25;
  byte *pbVar26;
  int iVar27;
  u8 *puVar28;
  uint uVar29;
  byte abStackY_825e53c [136700924];
  uint uStack_134;
  int iStack_130;
  uint uStack_110;
  u8 auStack_f4 [4];
  char acStack_f0 [4];
  undefined2 uStack_ec;
  u16 auStack_e8 [4];
  byte abStack_e0 [16];
  u8 auStack_d0 [188];
  
  uVar22 = (uint)bankDefPartner;
  uVar19 = (uint)bankAtkPartner;
  uVar17 = (uint)bankDef;
  uVar9 = (uint)bankAtk;
  Memset(abStack_e0,0,0x10);
  Memset(auStack_e8,0,8);
  bVar5 = gBattleStruct->moveTarget[uVar19];
  uVar23 = (uint)bVar5;
  uStack_134 = (uint)gChosenMovesByBanks[uVar19];
  if (uStack_134 != 0) {
    uVar6 = GetAIChosenMove(bankAtkPartner,bVar5);
    uStack_134 = (uint)uVar6;
  }
  uVar10 = CheckMoveLimitations(uVar9,0,0xff);
  acStack_f0[0] = '\x01' - (gBattleMons[uVar17].hp == 0);
  acStack_f0[1] = '\x01' - (gBattleMons[uVar22].hp == 0);
  iVar27 = 0;
  uStack_ec = 0;
  auStack_f4[0] = bankDef;
  auStack_f4[1] = bankDefPartner;
  uVar11 = CountAliveMonsInBattle(2,uVar9,uVar17);
  uVar16 = Random2(uVar11);
  __umodsi3(uVar16,100);
  if ((extraout_r1 & 0xffff) < 0x4b) {
    while( true ) {
      if (acStack_f0[iVar27] != '\0') {
        uVar18 = auStack_f4[iVar27];
        bVar4 = HasProtectionMoveInMoveset(uVar18,4);
        if ((bVar4 != 0) && (bVar4 = IsBankIncapacitated(uVar18), bVar4 == 0)) {
          bVar20 = true;
          goto LAB_090e046e;
        }
      }
      if (iVar27 == 1) break;
      iVar27 = 1;
    }
  }
  bVar20 = false;
LAB_090e046e:
  bVar4 = IsBankIncapacitated(bankAtkPartner);
  uVar6 = (u16)uStack_134;
  if (bVar4 == 0) {
    uStack_110 = uStack_134;
    bVar3 = false;
    if ((uStack_134 != 0) && (uStack_110 = (uint)(gBattleMoves[uStack_134].split != 2), 1 < uVar11))
    {
      uVar12 = GetBaseMoveTarget(uStack_134,uVar19);
      iVar27 = 0;
      if ((uVar12 & 0x28) == 0) {
        if ((uVar23 != uVar19) &&
           (bVar4 = MoveKnocksOutXHits(uVar6,bankAtkPartner,bVar5,1), bVar4 != 0)) {
          for (iVar27 = 0; iVar27 < (int)(uint)(gBattlersCount >> 1); iVar27 = iVar27 + 1) {
            if (auStack_f4[iVar27] == uVar23) {
              acStack_f0[iVar27 + 4] = '\x01';
            }
          }
        }
      }
      else {
        for (; iVar27 < (int)(uint)(gBattlersCount >> 1); iVar27 = iVar27 + 1) {
          bVar4 = MoveKnocksOutXHits(uVar6,bankAtkPartner,auStack_f4[iVar27],1);
          if (bVar4 != 0) {
            acStack_f0[iVar27 + 4] = '\x01';
          }
        }
        bVar3 = true;
        if ((((char)uStack_ec != '\0') && (uStack_ec._1_1_ != '\0')) &&
           (iVar27 = PriorityCalc(uVar19,0,uStack_134), iVar27 < 1)) {
          uVar12 = SpeedCalc(uVar19);
          uVar13 = SpeedCalc(uVar17);
          if ((uVar12 < uVar13) || (uVar13 = SpeedCalc(uVar22), uVar12 < uVar13)) {
            uStack_ec = uStack_ec & 0xff00;
            bVar3 = true;
          }
        }
      }
    }
  }
  else {
    bVar3 = false;
    uStack_110 = 0;
  }
  for (iVar27 = 0; iVar27 < (int)(uint)(gBattlersCount >> 1); iVar27 = iVar27 + 1) {
    if ((acStack_f0[iVar27] != '\0') && (acStack_f0[iVar27 + 4] == '\0')) {
      iVar24 = iVar27 * 0x5c;
      puVar28 = auStack_d0 + iVar24;
      memset_(puVar28,0,0x5c,&memset_);
      auStack_d0[iVar24] = bankAtk;
      auStack_d0[iVar24 + 1] = auStack_f4[iVar27];
      PopulateDamageCalcStructWithBaseAttackerData(puVar28);
      PopulateDamageCalcStructWithBaseDefenderData(puVar28);
    }
  }
  iStack_130 = 0;
  do {
    uVar7 = GetBattleMonMove(bankAtk,(u8)iStack_130);
    if (uVar7 == 0) break;
    if (gBattleMoves[uVar7].split != 2) {
      uVar7 = TryReplaceMoveWithZMove(bankAtk,bankDef,uVar7);
      uVar12 = (uint)uVar7;
      iVar27 = sub_90748d2();
      if ((iVar27 != 0) || (iVar27 = IsAnyMaxMove(uVar12), iVar27 != 0)) {
        auStack_e8[iStack_130] = uVar7;
      }
      puVar25 = (uint *)((iStack_130 + 0x2097917) * 4);
      if ((*puVar25 & uVar10) == 0) {
        uVar13 = GetBaseMoveTarget(uVar12,uVar9);
        if (bVar20) {
          iVar27 = 0;
          if ((uVar13 & 0x28) != 0) goto LAB_090e0a5a;
        }
        else {
          iVar27 = 0;
        }
        for (; iVar27 < (int)(uint)(gBattlersCount >> 1); iVar27 = iVar27 + 1) {
          if ((acStack_f0[iVar27] != '\0') &&
             (((iVar27 == 0 || ((uVar13 & 0x28) != 0)) && (acStack_f0[iVar27 + 4] == '\0')))) {
            bVar5 = auStack_f4[iVar27];
            uVar29 = (uint)bVar5;
            uVar14 = GetFinalAIMoveDamage(uVar7,bankAtk,bVar5,1,auStack_d0 + iVar27 * 0x5c);
            if (uVar14 != 0) {
              iVar24 = iStack_130 * 4 + -0xe0;
              bVar1 = abStack_e0[uVar29 + iVar24 + 0xe0];
              abStack_e0[uVar29 + iVar24 + 0xe0] = bVar1 + 4;
              bVar2 = gBattleMoves[uVar12].effect;
              if ((((bVar2 == 0x28) && (uStack_110 != 0)) && ((uVar23 == uVar29 || (bVar3)))) &&
                 (bVar4 = MoveWouldHitBeforeOtherMove(uVar6,bankAtkPartner,uVar7,bankAtk),
                 bVar4 != 0)) {
                abStack_e0[uVar29 + iStack_130 * 4] = bVar1 + 2;
              }
              bVar4 = MoveKnocksOutXHits(uVar7,bankAtk,bVar5,1);
              if (bVar4 == 0) {
                uVar15 = uVar29;
                bVar4 = IsStrongestMove(uVar7,bankAtk,bVar5);
                uVar18 = (u8)uVar15;
                if (bVar4 == 0) {
                  if (bVar2 == 0x47) {
                    uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                    if (0x31 < uVar8) {
                      bVar4 = GoodIdeaToLowerSpAtk(bVar5,bankAtk,uVar7);
                      uVar15 = (uint)bVar4;
                      goto LAB_090e08a4;
                    }
                  }
                  else if (bVar2 < 0x48) {
                    if (bVar2 == 6) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = BadIdeaToParalyze(bVar5,bankAtk);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e0944;
                      }
                    }
                    else if (bVar2 < 7) {
                      if (bVar2 == 4) {
                        uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                        if (0x31 < uVar8) {
                          bVar4 = BadIdeaToBurn(bVar5,bankAtk);
                          uVar15 = (uint)bVar4;
LAB_090e0944:
                          if (uVar15 == 0) goto LAB_090e0828;
                        }
                      }
                      else if (bVar2 < 5) {
                        if (bVar2 == 2) {
LAB_090e091a:
                          uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                          if (0x31 < uVar8) {
                            uVar15 = BadIdeaToPoison(uVar29,uVar9);
                            goto LAB_090e0944;
                          }
                        }
                      }
                      else {
                        uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                        if (0x31 < uVar8) {
                          uVar15 = sub_90db3e8(uVar29,uVar9);
                          goto LAB_090e0944;
                        }
                      }
                    }
                    else if (bVar2 == 0x44) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = GoodIdeaToLowerAttack(bVar5,bankAtk,uVar7);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if (bVar2 < 0x45) {
                      if (bVar2 == 0x1f) {
                        bVar4 = MoveWouldHitFirst(uVar7,(ushort)bankAtk,(ushort)bVar5);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if (bVar2 == 0x45) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = GoodIdeaToLowerDefense(bVar5,bankAtk,uVar7);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if ((bVar2 == 0x46) &&
                            (uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18), 0x31 < uVar8))
                    {
                      bVar4 = GoodIdeaToLowerSpeed(bVar5,bankAtk,uVar7,1);
                      uVar15 = (uint)bVar4;
                      goto LAB_090e08a4;
                    }
                  }
                  else if (bVar2 == 0x60) {
LAB_090e0904:
                    uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                    if (0x31 < uVar8) goto LAB_090e0828;
                  }
                  else if (bVar2 < 0x61) {
                    if (bVar2 == 0x49) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = GoodIdeaToLowerAccuracy(bVar5,bankAtk,uVar7);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if (bVar2 < 0x49) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = GoodIdeaToLowerSpDef(bVar5,bankAtk,uVar7);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if (bVar2 == 0x4a) {
                      uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18);
                      if (0x31 < uVar8) {
                        bVar4 = GoodIdeaToLowerEvasion(bVar5,bankAtk,uVar7);
                        uVar15 = (uint)bVar4;
                        goto LAB_090e08a4;
                      }
                    }
                    else if ((bVar2 == 0x4c) &&
                            (uVar8 = CalcSecondaryEffectChance(bankAtk,uVar7,uVar18), 0x31 < uVar8))
                    {
                      uVar15 = CanBeConfused(uVar29,uVar9);
LAB_090e08a4:
                      if (uVar15 != 0) goto LAB_090e0828;
                    }
                  }
                  else {
                    if (bVar2 == 0x8b) goto LAB_090e0904;
                    if (bVar2 < 0x8c) {
                      if (bVar2 == 0x6e) goto LAB_090e0904;
                    }
                    else if (bVar2 == 0x8d) {
                      iVar24 = sub_90743c0(uVar9);
                      if (iVar24 == 0) goto LAB_090e0904;
                    }
                    else if (bVar2 == 0xd1) goto LAB_090e091a;
                  }
                  if (uVar11 < 2) goto LAB_090e0828;
                  if (uVar14 < gBattleMons[uVar29].maxHP >> 2) {
                    pbVar26 = abStack_e0 + iStack_130 * 4;
                    bVar5 = pbVar26[uVar29] - 3;
                  }
                  else {
                    uVar15 = __udivsi3(gBattleMons[uVar29].maxHP,3);
                    if ((uVar15 & 0xffff) <= uVar14) goto LAB_090e0828;
                    pbVar26 = abStack_e0 + iStack_130 * 4;
                    bVar5 = pbVar26[uVar29] - 2;
                  }
                }
                else {
                  pbVar26 = abStack_e0 + iStack_130 * 4;
                  bVar5 = pbVar26[uVar29] + 1;
                }
                pbVar26[uVar29] = bVar5;
              }
              else {
                iVar24 = iStack_130 * 4 + -0xe0;
                bVar5 = abStack_e0[uVar29 + iVar24 + 0xe0];
                abStack_e0[uVar29 + iVar24 + 0xe0] = bVar5 + 2;
                if ((int)(gBattleMons[uVar29].status2 << 6) < 0) {
                  abStack_e0[uVar29 + iVar24 + 0xe0] = bVar5;
                }
              }
            }
          }
LAB_090e0828:
        }
        if (((int)(uVar13 << 0x1a) < 0) && (iVar27 = sub_90da104(uVar12,uVar9,uVar19), iVar27 != 0))
        {
          if (((gBattleMons[uVar19].status1 & 7) < 2) &&
             (-1 < (int)((uint)(byte)gDisableStructs[uVar19].field_0x18 << 0x1f))) {
            if (uStack_134 == 0) {
              bVar4 = HasProtectionMoveInMoveset(bankAtkPartner,0x14);
              if (bVar4 != 0) {
                if (gBattleMoves[*(ushort *)(&gLastResultingMoves + uVar19 * 2)].effect == 0x6f /* EFFECT_PROTECT */) {
                  bVar5 = gDisableStructs[uVar19].protectUses;
                  goto joined_r0x090e0a7a;
                }
                goto LAB_090e0a5a;
              }
            }
            else if (gBattleMoves[uStack_134].effect == 0x6f /* EFFECT_PROTECT */) {
              if (((uStack_134 - 0x27b & 0xfffd) != 0) &&
                 ((uStack_134 != 0x27c || (gDisableStructs[uVar19].isFirstTurn != 0))))
              goto LAB_090e0a5a;
            }
            else if (gBattleMoves[uStack_134].effect == 0x9b /* EFFECT_SEMI_INVULNERABLE */) {
              bVar5 = MoveWouldHitFirst(uVar7,(ushort)bankAtk,(ushort)bankAtkPartner);
joined_r0x090e0a7a:
              if (bVar5 == 0) goto LAB_090e0a5a;
            }
            (abStack_e0 + uVar19)[(int)(puVar25 + -0x2097917)] =
                 (abStack_e0 + uVar19)[(int)(puVar25 + -0x2097917)] - 3;
          }
          else {
            (abStack_e0 + uVar19)[(int)(puVar25 + -0x2097917)] =
                 (abStack_e0 + uVar19)[(int)(puVar25 + -0x2097917)] - 3;
          }
        }
      }
    }
LAB_090e0a5a:
    iStack_130 = iStack_130 + 1;
  } while (iStack_130 != 4);
  uVar10 = 1;
  uVar23 = 0;
  do {
    iVar24 = uVar10 * 4;
    iVar27 = uVar23 * 4 + -0xe0;
    iVar24 = (int)(((uint)abStack_e0[iVar24 + uVar17] + (uint)abStack_e0[iVar24 + uVar22] +
                   (uint)abStack_e0[iVar24 + uVar19]) * 0x1000000) >> 0x18;
    iVar27 = (int)(((uint)abStack_e0[uVar17 + iVar27 + 0xe0] +
                    (uint)abStack_e0[uVar22 + iVar27 + 0xe0] +
                   (uint)abStack_e0[uVar19 + iVar27 + 0xe0]) * 0x1000000) >> 0x18;
    if (iVar27 < iVar24) {
LAB_090e0548:
      uVar23 = uVar10 & 0xff;
    }
    else if (iVar24 == iVar27) {
      uVar21 = gBattleMons[uVar9].moves[uVar10];
      iVar27 = GetBaseMoveTarget(gBattleMons[uVar9].moves[uVar23],uVar9);
      uVar11 = GetBaseMoveTarget(uVar21,uVar9);
      if (((iVar27 << 0x1a < 0) && ((uVar11 & 0x28) == 8)) &&
         (iVar27 = sub_90da104(gBattleMons[uVar9].moves[uVar23],uVar9,uVar19), iVar27 != 0))
      goto LAB_090e0548;
    }
    uVar10 = uVar10 + 1;
    if (uVar10 == 4) {
      iVar27 = uVar23 * 4 + -0xe0;
      bestMoveScores[uVar17] = abStack_e0[uVar17 + iVar27 + 0xe0];
      bestMoveScores[uVar22] = abStack_e0[uVar22 + iVar27 + 0xe0];
      bestMoveScores[uVar19] = abStack_e0[uVar19 + iVar27 + 0xe0];
      uVar21 = auStack_e8[uVar23];
      if (auStack_e8[uVar23] == 0) {
        uVar21 = gBattleMons[uVar9].moves[uVar23];
      }
      *bestMove = uVar21;
      return;
    }
  } while( true );
}

// ---- RemoveDoublesKillingScore  (ROM 0x90e0b78)
void RemoveDoublesKillingScore(u8 bankAtk,u8 bankDef)

{
  int iVar1;
  
  iVar1 = (uint)bankAtk * 4 + (uint)bankDef;
  UpdateBestDoubleKillingMoveScore
            (bankAtk,bankDef,bankAtk ^ 2,bankDef ^ 2,(s8 *)(gNewBS + (iVar1 + 500) * 4),
             (u16 *)(gNewBS + (iVar1 + 0x3d8) * 2));
  return;
}

// ---- ForceCompleteDamageRecalculation  (ROM 0x90e0bac)
void ForceCompleteDamageRecalculation(u8 bankAtk)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  uVar1 = gNewBS;
  uVar2 = ~(uint)bankAtk & 1;
  uVar5 = uVar2 | 2;
  uVar3 = gBattleTypeFlags & 1;
  iVar4 = (uint)bankAtk * 4;
  *(undefined2 *)(gNewBS + (iVar4 + uVar2 + 0x114) * 2 + 6) = 0xffff;
  iVar6 = uVar1 + iVar4 + uVar2;
  *(undefined1 *)(iVar6 + 0x820) = 0xff;
  *(undefined1 *)(iVar6 + 0x830) = 0xff;
  if (uVar3 != 0) {
    iVar6 = uVar1 + iVar4 + uVar5;
    *(undefined2 *)(uVar1 + (iVar4 + uVar5 + 0x114) * 2 + 6) = 0xffff;
    *(undefined1 *)(iVar6 + 0x820) = 0xff;
    *(undefined1 *)(iVar6 + 0x830) = 0xff;
  }
  iVar6 = 0;
  do {
    *(undefined4 *)(uVar1 + iVar6 + (uVar2 + iVar4) * 0x10 + 0x2f0) = 0xffffffff;
    if (uVar3 != 0) {
      *(undefined4 *)(uVar1 + iVar6 + (uVar5 + iVar4) * 0x10 + 0x2f0) = 0xffffffff;
    }
    iVar6 = iVar6 + 4;
  } while (iVar6 != 0x10);
  if (uVar3 != 0) {
    RemoveDoublesKillingScore(bankAtk,(u8)uVar2);
    RemoveDoublesKillingScore(bankAtk,(u8)uVar5);
  }
  return;
}

// ---- ForceSpecificDamageRecalculation  (ROM 0x90e0c68)
void ForceSpecificDamageRecalculation(u8 bankAtk,u8 bankDef,u8 movePos)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = gNewBS;
  uVar4 = (uint)bankDef;
  iVar2 = (uint)bankAtk * 4;
  *(undefined2 *)(gNewBS + (iVar2 + uVar4 + 0x114) * 2 + 6) = 0xffff;
  iVar3 = uVar1 + iVar2 + uVar4;
  *(undefined1 *)(iVar3 + 0x820) = 0xff;
  *(undefined1 *)(iVar3 + 0x830) = 0xff;
  *(undefined4 *)(uVar1 + ((iVar2 + uVar4) * 4 + (uint)movePos + 0xba) * 4 + 8) = 0xffffffff;
  if (gBattleTypeFlags << 0x1f < 0) {
    uVar4 = uVar4 ^ 2;
    *(undefined2 *)(uVar1 + (iVar2 + uVar4 + 0x114) * 2 + 6) = 0xffff;
    iVar3 = uVar1 + iVar2 + uVar4;
    *(undefined1 *)(iVar3 + 0x820) = 0xff;
    *(undefined1 *)(iVar3 + 0x830) = 0xff;
    *(undefined4 *)(uVar1 + ((iVar2 + uVar4) * 4 + (uint)movePos + 0xba) * 4 + 8) = 0xffffffff;
    RemoveDoublesKillingScore(bankAtk,bankDef);
    RemoveDoublesKillingScore(bankAtk,(u8)uVar4);
  }
  return;
}

// ---- TryRemovePartnerDoublesKillingScore  (ROM 0x90e0d08)
bool8 TryRemovePartnerDoublesKillingScore(u8 bankAtk,u8 bankDef,u16 chosenMove,bool8 doSpeedCalc)

{
  u16 move;
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  uVar7 = (uint)bankDef;
  uVar3 = (uint)bankAtk;
  if (((gBattleTypeFlags << 0x1f < 0) && (gBattleMons[uVar7].hp != 0)) &&
     (uVar8 = uVar3 ^ 2, gBattleMons[uVar8].hp != 0)) {
    move = *(u16 *)(gNewBS + (uVar8 * 4 + uVar7 + 0x3d4) * 2 + 8);
    if (doSpeedCalc == 0) {
      if ((bankAtk & 2) != 0) {
        return 0;
      }
    }
    else {
      uVar4 = SpeedCalc(uVar3);
      uVar5 = SpeedCalc(uVar8);
      if (uVar4 < uVar5) {
        return 0;
      }
    }
    bVar1 = IsBankIncapacitated(bankAtk);
    if (bVar1 == 0) {
      iVar6 = GetBattlerSide(uVar3);
      iVar2 = GetBattlerSide(uVar7);
      if (((iVar6 != iVar2) &&
          (((uVar3 = CountAliveMonsInBattle(2,uVar3,uVar7), 1 < uVar3 ||
            (bVar1 = MoveWouldHitFirst(chosenMove,(ushort)bankAtk,(ushort)bankDef), bVar1 != 0)) ||
           (bVar1 = MoveWouldHitFirst(move,(u16)uVar8,(ushort)bankDef), bVar1 == 0)))) &&
         (bVar1 = MoveKnocksOutXHits(chosenMove,bankAtk,bankDef,1), bVar1 != 0)) {
        RemoveDoublesKillingScore((u8)uVar8,bankDef);
        RemoveDoublesKillingScore((u8)uVar8,bankDef ^ 2);
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return 0;
}

// ---- TryRemovePartnerDoublesKillingScoreComplete  (ROM 0x90e0df4)
void TryRemovePartnerDoublesKillingScoreComplete
               (u8 bankAtk,u8 bankDef,u16 chosenMove,u32 moveTarget,bool8 doSpeedCalc)

{
  bool8 bVar1;
  
  bVar1 = TryRemovePartnerDoublesKillingScore(bankAtk,bankDef,chosenMove,doSpeedCalc);
  if ((bVar1 == 0) && ((moveTarget & 0x28) != 0)) {
    TryRemovePartnerDoublesKillingScore(bankAtk,bankDef ^ 2,chosenMove,doSpeedCalc);
  }
  return;
}

// ---- GetDoubleKillingScore  (ROM 0x90e0e24)
u8 GetDoubleKillingScore(u16 move,u8 bankAtk,u8 bankDef)

{
  uint uVar1;
  u8 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  
  uVar5 = (uint)bankDef;
  uVar4 = (uint)bankAtk;
  uVar7 = uVar4 ^ 2;
  if ((gBattleMoves[gChosenMovesByBanks[uVar7]].effect == 0x6f /* EFFECT_PROTECT */) &&
     (iVar3 = GetBaseMoveTarget(move,uVar4), uVar1 = gNewBS, iVar3 << 0x1a < 0)) {
    pcVar6 = (char *)(gNewBS + uVar4 + 0x9d);
    if (*pcVar6 == '\0') {
      *pcVar6 = '\x01';
      iVar3 = uVar4 * 4 + uVar5;
      UpdateBestDoubleKillingMoveScore
                (bankAtk,bankDef,(u8)uVar7,bankDef ^ 2,(s8 *)(uVar1 + (iVar3 + 500) * 4),
                 (u16 *)(uVar1 + (iVar3 + 0x3d8) * 2));
    }
  }
  iVar3 = uVar4 * 4 + uVar5;
  uVar2 = 0;
  if (*(u16 *)(gNewBS + (iVar3 + 0x3d4) * 2 + 8) == move) {
    iVar3 = gNewBS + iVar3 * 4;
    uVar2 = *(char *)(iVar3 + (uVar5 ^ 2) + 2000) + *(char *)(iVar3 + uVar5 + 2000) +
            *(char *)(iVar3 + uVar7 + 2000);
  }
  return uVar2;
}

// ---- StrongestMoveGoesFirst  (ROM 0x90e0edc)
bool8 StrongestMoveGoesFirst(u16 currentMove,u8 bankAtk,u8 bankDef)

{
  byte bVar1;
  bool8 bVar2;
  bool8 bVar3;
  bool8 bVar4;
  byte bVar5;
  byte bVar6;
  bool8 bVar7;
  u16 uVar8;
  u16 move;
  ushort uVar9;
  u16 uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  u32 uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  int iVar22;
  uint uVar23;
  bool bVar24;
  bool bVar25;
  int iStack_ac;
  uint uStack_9c;
  u8 uStack_74;
  u8 uStack_73;
  undefined1 auStack_72 [94];
  
  uVar21 = (uint)bankDef;
  uVar20 = (uint)bankAtk;
  iVar22 = gNewBS + (uVar20 * 4 + uVar21) * 2;
  if (*(short *)(iVar22 + 0x24e) != -1) goto LAB_090e107a;
  uVar11 = CheckMoveLimitations(uVar20,0,0xff);
  bVar2 = BadIdeaToMakeContactWith(bankAtk,bankDef);
  iVar12 = GetBankAbility(uVar20);
  bVar3 = IsTrapped(bankDef,1);
  if (bVar3 == 0) {
    if (((gBattleTypeFlags & 1) == 0) &&
       (uVar23 = ViableMonCountFromBankLoadPartyRange(uVar21), 1 < uVar23)) {
      bVar24 = false;
    }
    else {
      if (-1 < (int)(gBattleTypeFlags << 0x1f)) goto LAB_090e0f30;
      uVar23 = ViableMonCountFromBankLoadPartyRange(uVar21);
      bVar24 = uVar23 < 3;
    }
  }
  else {
LAB_090e0f30:
    bVar24 = true;
  }
  iVar13 = IsPlayerInControl(uVar21);
  bVar25 = true;
  if (iVar13 != 0) {
    bVar25 = *(char *)(gNewBS + 0x1cc) != '\0';
  }
  bVar3 = ShouldUseHumanLikelyMove(bankAtk,bankDef);
  iVar13 = GetBankAbility(uVar20);
  Memset(auStack_72,0,0x5a);
  uStack_74 = bankAtk;
  uStack_73 = bankDef;
  PopulateDamageCalcStructWithBaseAttackerData(&uStack_74);
  uVar23 = 0;
  PopulateDamageCalcStructWithBaseDefenderData(&uStack_74);
  uStack_9c = 0;
  iStack_ac = 0;
  do {
    uVar8 = GetBattleMonMove(bankAtk,(u8)iStack_ac);
    if (uVar8 == 0) break;
    uVar8 = TryReplaceMoveWithZMove(bankAtk,bankDef,uVar8);
    uVar14 = (uint)uVar8;
    iVar16 = (*(code *)0x9074f00)(uVar20,uVar14);
    if ((iVar16 != 1) && ((uVar11 & *(uint *)((iStack_ac + 0x2097917) * 4)) == 0)) {
      uVar15 = GetFinalAIMoveDamage(uVar8,bankAtk,bankDef,1,&uStack_74);
      bVar4 = MoveWouldHitFirst(uVar8,(ushort)bankAtk,(ushort)bankDef);
      if ((bVar4 != 0) && (bVar1 = gBattleMoves[uVar14].effect, bVar1 != 0x94)) {
        if (uStack_9c < uVar15) {
          uStack_9c = uVar15;
LAB_090e114e:
          uVar23 = uVar14;
        }
        else if (uVar15 == uStack_9c) {
          bVar5 = PriorityCalc(uVar20,0,uVar14);
          bVar6 = PriorityCalc(uVar20,0,uVar23);
          if (bVar6 < bVar5) goto LAB_090e114e;
          if (bVar5 == bVar6) {
            if (uVar14 == 0xe4) {
              if ((!bVar24) && (bVar25)) goto LAB_090e114e;
            }
            else if ((uVar23 == 0xe4) && ((!bVar24 && (bVar25)))) goto LAB_090e106a;
            move = (u16)uVar23;
            bVar4 = MoveWillHit(move,bankAtk,bankDef);
            uVar9 = 100;
            if (bVar4 == 0) {
              uVar9 = CalcAIAccuracy(move,bankAtk,bankDef);
            }
            bVar4 = MoveWillHit(uVar8,bankAtk,bankDef);
            uVar10 = 100;
            if (bVar4 == 0) {
              uVar10 = CalcAIAccuracy(uVar8,bankAtk,bankDef);
            }
            if (uVar9 <= uVar10) {
              if ((uVar9 < uVar10) && (uVar9 < 100)) goto LAB_090e114e;
              iVar16 = CanBeChoiceLocked(uVar20);
              if (iVar16 == 0) {
                if (bVar2 != 0) {
                  iVar16 = CheckContact(uVar23,uVar20);
                  iVar17 = CheckContact(uVar14,uVar20);
                  if (iVar16 == 0) {
                    if (iVar17 != 0) goto LAB_090e106a;
                  }
                  else {
                    if (iVar17 == 0) goto LAB_090e114e;
                    if (gBattleMoves[uVar23].effect == 0x1d /* EFFECT_MULTI_HIT */) {
                      if (bVar1 != 0x1d) goto LAB_090e114e;
                    }
                    else if (bVar1 == 0x1d) goto LAB_090e106a;
                  }
                }
                if (iVar12 != 0x73) {
                  iVar16 = CheckRecoil(uVar23);
                  iVar17 = CheckRecoil(uVar14);
                  if (iVar16 == 0) {
                    if (iVar17 != 0) goto LAB_090e106a;
                  }
                  else if (iVar17 == 0) goto LAB_090e114e;
                }
                if (iVar13 != 0xbf) {
                  bVar4 = IsStatRecoilMove(move);
                  bVar7 = IsStatRecoilMove(uVar8);
                  if (bVar4 == 0) {
                    if (bVar7 != 0) goto LAB_090e106a;
                  }
                  else if (bVar7 == 0) goto LAB_090e114e;
                }
                if (bVar3 == 0) {
                  iVar16 = Random2();
                  if (iVar16 << 0x1f < 0) goto LAB_090e114e;
                }
                else {
                  uVar8 = PickMoveHumanLikelyToChoose(uVar8,move,bankAtk,bankDef);
                  uVar23 = (uint)uVar8;
                }
              }
              else if ((uVar9 == uVar10) || (99 < uVar10)) {
                uVar18 = CalcVisualBasePower(uVar20,0,uVar14,1);
                uVar19 = CalcVisualBasePower(uVar20,0,uVar23,1);
                if (uVar19 < uVar18) goto LAB_090e114e;
              }
            }
          }
        }
      }
    }
LAB_090e106a:
    iStack_ac = iStack_ac + 1;
  } while (iStack_ac != 4);
  *(short *)(iVar22 + 0x24e) = (short)uVar23;
LAB_090e107a:
  return *(u16 *)(gNewBS + (uVar20 * 4 + uVar21 + 0x124) * 2 + 6) == currentMove;
}

// ---- MoveKnocksOutPossiblyGoesFirstWithBestAccuracy  (ROM 0x90e11fc)
bool8 MoveKnocksOutPossiblyGoesFirstWithBestAccuracy
                (u16 checkMove,u8 bankAtk,u8 bankDef,bool8 checkGoingFirst)

{
  byte *pbVar1;
  ushort uVar2;
  bool8 bVar3;
  u16 uVar4;
  u16 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  u8 i;
  uint uVar9;
  ushort bankDef_00;
  uint uVar10;
  uint uStack_40;
  uint uStack_34;
  u8 auStack_1c [8];
  
  uVar9 = (uint)bankAtk;
  uVar6 = CheckMoveLimitations(uVar9,0,0xff);
  uVar10 = 0xff;
  uStack_34 = 0;
  uVar2 = 0;
  uStack_40 = 0;
  do {
    i = (u8)uStack_34;
    uVar4 = GetBattleMonMove(bankAtk,i);
    if (uVar4 == 0) break;
    uVar4 = TryReplaceMoveWithZMove(bankAtk,bankDef,uVar4);
    if ((*(uint *)((uStack_34 + 0x2097917) * 4) & uVar6) == 0) {
      uVar5 = CalcAIAccuracy(uVar4,bankAtk,bankDef);
      if (uVar5 == 0xffff) {
        uVar5 = 100;
      }
      bankDef_00 = (ushort)bankDef;
      if (((checkGoingFirst == 0) ||
          (bVar3 = MoveWouldHitFirst(uVar4,(ushort)bankAtk,bankDef_00), bVar3 != 0)) &&
         (bVar3 = MoveKnocksOutXHits(uVar4,bankAtk,bankDef,1), bVar3 != 0)) {
        bVar3 = MoveWillHit(uVar4,bankAtk,bankDef);
        if (((bVar3 == 0) || (99 < uVar2)) && (uVar5 <= uVar2)) {
          if (uVar5 != uVar2) goto LAB_090e12a8;
          iVar7 = PriorityCalc(uVar9,0,uVar4);
          iVar8 = PriorityCalc(uVar9,0,gBattleMons[uVar9].moves[uVar10]);
          if (iVar7 <= iVar8) {
LAB_090e131c:
            auStack_1c[uStack_40] = i;
            uStack_40 = uStack_40 + 1 & 0xff;
            uVar10 = uStack_34 & 0xff;
            goto LAB_090e12a8;
          }
          bVar3 = MoveWouldHitFirst(0x21,(ushort)bankAtk,bankDef_00);
          if (bVar3 == 0) {
LAB_090e130e:
            bVar3 = MoveWouldHitFirst(0x21,(ushort)bankAtk,bankDef_00);
            if (bVar3 != 0) goto LAB_090e131c;
          }
          else {
            iVar7 = PriorityCalc(uVar9,0,uVar4);
            iVar8 = sub_90dc344(bankDef);
            if (iVar7 < iVar8) goto LAB_090e130e;
          }
          auStack_1c[0] = i;
        }
        else {
          auStack_1c[0] = i;
          uVar2 = uVar5;
        }
        uStack_40 = 1;
        uVar10 = uStack_34 & 0xff;
        auStack_1c[0] = i;
      }
    }
LAB_090e12a8:
    uStack_34 = uStack_34 + 1;
  } while (uStack_34 != 4);
  bVar3 = 0;
  if (uVar10 != 0xff) {
    uVar10 = 0;
    do {
      if (uStack_40 <= (uVar10 & 0xff)) {
        return 0;
      }
      pbVar1 = auStack_1c + uVar10;
      uVar10 = uVar10 + 1;
    } while (gBattleMons[uVar9].moves[*pbVar1] != checkMove);
    bVar3 = 1;
  }
  return bVar3;
}

// ---- AdjustMoveLimitationFlagsForAI  (ROM 0x90e137c)
u8 AdjustMoveLimitationFlagsForAI(u8 bankAtk)

{
  return 0xff;
}

// ---- IncreaseViability  (ROM 0x90e1380)
void IncreaseViability(s16 *viability,u8 amount)

{
  s16 sVar1;
  
  sVar1 = MathMin((int)*viability + (uint)amount,0xff);
  *viability = sVar1;
  return;
}

// ---- DecreaseViability  (ROM 0x90e1394)
void DecreaseViability(short *param_1,uint param_2)

{
  if (gBattleTypeFlags << 0x1f < 0) {
    param_2 = (param_2 & 0x7fff) << 1;
  }
  if ((int)*param_1 < (int)param_2) {
    *param_1 = 0;
  }
  else {
    *param_1 = *param_1 - (short)param_2;
  }
  return;
}

// ---- PickMoveHumanLikelyToChoose  (ROM 0x9351510)
u16 PickMoveHumanLikelyToChoose(u16 move1,u16 move2,u8 playerBank,u8 aiBank)

{
  ushort uVar1;
  u16 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  u8 ability;
  
  uVar9 = (uint)aiBank;
  ability = playerBank;
  iVar3 = func_0x093514d4();
  iVar4 = func_0x093514d4(move2);
  if ((iVar3 == 0) || (uVar2 = CalcSecondaryEffectChance(playerBank,move1,ability), uVar2 < 0x32)) {
    if ((iVar4 == 0) || (uVar2 = CalcSecondaryEffectChance(playerBank,move2,ability), uVar2 < 0x32))
    goto LAB_0935154e;
  }
  else {
    if ((iVar4 == 0) || (uVar2 = CalcSecondaryEffectChance(playerBank,move1,ability), uVar2 < 0x32))
    goto LAB_09351540;
LAB_0935154e:
    uVar1 = gLastLandedMoves[uVar9];
    if (move1 == uVar1) {
      return uVar1;
    }
    if (move2 == uVar1) {
      return uVar1;
    }
    uVar5 = AI_SpecialTypeCalc(move1,playerBank,uVar9);
    uVar6 = AI_SpecialTypeCalc(move2,playerBank,uVar9);
    if ((uVar5 & 2) == 0) {
      if ((uVar6 & 2) != 0) goto LAB_093515f6;
    }
    else if ((uVar6 & 2) == 0) goto LAB_09351540;
    if ((uVar5 & 4) == 0) {
      if ((uVar6 & 4) != 0) goto LAB_09351540;
    }
    else if ((uVar6 & 4) == 0) goto LAB_093515f6;
    uVar7 = GetMoveTypeSpecial(playerBank,move1);
    uVar8 = GetMoveTypeSpecial(playerBank,move2);
    iVar3 = IsOfType(playerBank,uVar7);
    if (iVar3 == 0) {
      iVar3 = IsOfType(playerBank,uVar8);
      if (iVar3 != 0) goto LAB_093515f6;
    }
    else {
      iVar3 = IsOfType(playerBank,uVar8);
      if (iVar3 == 0) goto LAB_09351540;
    }
    uVar5 = CalcVisualBasePower(playerBank,uVar9,move1,0);
    uVar9 = CalcVisualBasePower(playerBank,uVar9,move2,0);
    if (uVar9 < uVar5) goto LAB_09351540;
    if (uVar9 <= uVar5) {
      uVar2 = Random2();
      return uVar2;
    }
  }
LAB_093515f6:
  move1 = move2;
LAB_09351540:
  return move1;
}
