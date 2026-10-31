// ai_other.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- sub_90c5aa8  (ROM 0x90c5aa8)
uint sub_90c5aa8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = GetBattlerSide(param_1);
  iVar1 = GetBattlerSide(param_2);
  if ((((((*(char *)(gNewBS + 9 + iVar1) != '\0') ||
         (uVar3 = 1, *(char *)(gNewBS + 9 + iVar2) == '\0')) &&
        ((*(char *)(gNewBS + 0xb + iVar1) != '\0' ||
         (uVar3 = 1, *(char *)(gNewBS + 0xb + iVar2) == '\0')))) &&
       ((*(char *)(gNewBS + 0xd + iVar2) != '\0' ||
        (uVar3 = 1, *(char *)(gNewBS + 0xd + iVar1) == '\0')))) &&
      (((((*(char *)(gNewBS + 0x11 + iVar2) != '\0' ||
          (uVar3 = 1, *(char *)(gNewBS + 0x11 + iVar1) == '\0')) &&
         ((((*(char *)(gNewBS + 0x13 + iVar2) != '\0' ||
            (uVar3 = 1, *(char *)(gNewBS + 0x13 + iVar1) == '\0')) &&
           ((*(char *)(gNewBS + 0x15 + iVar2) != '\0' ||
            (uVar3 = 1, *(char *)(gNewBS + 0x15 + iVar1) == '\0')))) &&
          (((&gSideTimers[0].reflectTimer)[iVar2 * 0xb] != 0 ||
           (uVar3 = 1, (&gSideTimers[0].reflectTimer)[iVar1 * 0xb] == 0)))))) &&
        (((&gSideTimers[0].lightscreenTimer)[iVar2 * 0xb] != 0 ||
         (uVar3 = 1, (&gSideTimers[0].lightscreenTimer)[iVar1 * 0xb] == 0)))) &&
       (((((&gSideTimers[0].safeguardTimer)[iVar2 * 0xb] != 0 ||
          (uVar3 = 1, (&gSideTimers[0].safeguardTimer)[iVar1 * 0xb] == 0)) &&
         (((&gSideTimers[0].mistTimer)[iVar2 * 0xb] != 0 ||
          (uVar3 = 1, (&gSideTimers[0].mistTimer)[iVar1 * 0xb] == 0)))) &&
        (((((&gSideTimers[0].field_0xa)[iVar1 * 0xb] & 3) != 0 ||
          (uVar3 = 1, ((&gSideTimers[0].field_0xa)[iVar2 * 0xb] & 3) == 0)) &&
         (((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar1 * 0xb] << 0x1b) < 0 ||
          (uVar3 = 1, ((byte)(&gSideTimers[0].field_0xa)[iVar2 * 0xb] & 0x1f) >> 4 == 0)))))))))) &&
     (((int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar1 * 0xb] << 0x1a) < 0 ||
      (uVar3 = 1, ((byte)(&gSideTimers[0].field_0xa)[iVar2 * 0xb] & 0x3f) >> 5 == 0)))) {
    uVar3 = 0;
    if (-1 < (int)((uint)(byte)(&gSideTimers[0].field_0xa)[iVar1 * 0xb] << 0x19)) {
      uVar3 = ((byte)(&gSideTimers[0].field_0xa)[iVar2 * 0xb] & 0x7f) >> 6;
    }
  }
  return uVar3;
}

// ---- sub_90c70ec  (ROM 0x90c70ec)
void sub_90c70ec(int param_1,int param_2)

{
  BattlePokemon *backupBattleMons;
  
  for (backupBattleMons = 0x0;
      backupBattleMons < (BattlePokemon *)(uint)gBattlersCount;
      backupBattleMons = (BattlePokemon *)((uint)((int)&backupBattleMons->species + 1) & 0xff)) {
    TryTempMegaEvolveAllBanks
              (backupBattleMons,(u16 *)(param_1 + (int)backupBattleMons * 0x58),
               (u8 *)(param_2 + (int)backupBattleMons * 2));
  }
  return;
}

// ---- sub_90c748c  (ROM 0x90c748c)
void sub_90c748c(int param_1,undefined4 param_2,undefined2 *param_3,undefined1 *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  puVar3 = param_4;
  iVar1 = GetBankPartyData();
  *(undefined2 *)(iVar1 + 0x20) = *param_3;
  CalculateMonStats(iVar1);
  puVar2 = (undefined1 *)GetAbilityLocation(param_1);
  *puVar2 = *param_4;
  memcpy_(gBattleMons + param_1,param_2,0x58,&memcpy_,puVar3);
  return;
}

// ---- sub_90c74d0  (ROM 0x90c74d0)
void sub_90c74d0(int param_1,int param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  uint uVar2;
  
  for (uVar2 = 0; uVar2 < gBattlersCount; uVar2 = uVar2 + 1 & 0xff) {
    psVar1 = (short *)(param_2 + uVar2 * 2);
    if (*psVar1 != 0) {
      sub_90c748c(uVar2,param_1 + uVar2 * 0x58,psVar1,param_3 + uVar2,param_4);
    }
  }
  memset_(param_2,0,4);
  memset_(param_3,0,4);
  return;
}

// ---- sub_90c75b8  (ROM 0x90c75b8)
void sub_90c75b8(int param_1,u8 param_2,u8 param_3,int param_4)

{
  u8 bank;
  bool8 bVar1;
  u16 currentMove;
  move_t move;
  uint uVar2;
  int iVar3;
  undefined1 uVar4;
  
  bank = (u8)param_1;
  currentMove = GetBattleMonMove(bank,param_3);
  move = IsValidMovePrediction(param_2,bank);
  if (((move == 0 /* - */) || (*(ushort *)(param_4 + 0x38) <= *(ushort *)(param_4 + 0x2e))) ||
     (bVar1 = MoveKnocksOutXHits(move,param_2,bank,1), bVar1 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar2 = GetBaseMoveTarget(currentMove,param_1);
    if ((uVar2 & 0x53) != 0) {
      return;
    }
    iVar3 = PriorityCalc(param_1,0,currentMove);
    if (iVar3 < 1) {
      return;
    }
    bVar1 = StrongestMoveGoesFirst(currentMove,bank,param_2);
    if (bVar1 == 0) {
      return;
    }
    uVar4 = 1;
  }
  *(undefined1 *)(gNewBS + param_1 + 0x8a0) = uVar4;
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return;
}

// ---- sub_90d7008  (ROM 0x90d7008)
undefined8 sub_90d7008(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = gNewBS;
  *(undefined2 *)(gNewBS + (param_1 + 0x210) * 4 + 8) = 0;
  iVar2 = uVar1 + param_1 * 2;
  *(undefined1 *)(iVar2 + 0x858) = 0;
  *(undefined1 *)(iVar2 + 0x840) = 6;
  *(undefined2 *)(uVar1 + param_1 * 4 + 0x84a) = 0;
  *(undefined1 *)(iVar2 + 0x859) = 0;
  *(undefined1 *)(iVar2 + 0x841) = 6;
  iVar2 = GetBattlerSide(param_1);
  memset_(uVar1 + iVar2 * 0xc + 0x860,0);
  uVar1 = gNewBS;
  iVar2 = GetBattlerSide(param_1);
  memset_(uVar1 + iVar2 * 6 + 0x878,0,6);
  return CONCAT44(&GetBattlerSide,uVar1);
}

// ---- sub_90da104  (ROM 0x90da104)
bool sub_90da104(undefined4 param_1,undefined4 param_2,int param_3)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  if (((gBattleMons[param_3].hp == 0) || (iVar2 = GetBankAbility(param_3), iVar2 == 0xe2)) ||
     (((gStatuses3[param_3] & 0x130400c0) != 0 &&
      (bVar1 = MoveWouldHitFirst((u16)param_1,(u16)param_2,(u16)param_3), bVar1 != 0)))) {
    bVar4 = false;
  }
  else {
    uVar3 = AI_SpecialTypeCalc(param_1,param_2,param_3);
    bVar4 = (uVar3 & 0x29) == 0;
  }
  return bVar4;
}

// ---- sub_90db3e8  (ROM 0x90db3e8)
undefined4 sub_90db3e8(undefined4 param_1)

{
  GetBankAbility();
  GetBankItemEffect(param_1);
  CanBeFrozen(param_1,1);
  return 1;
}

// ---- sub_90db47c  (ROM 0x90db47c)
bool sub_90db47c(int param_1,int param_2)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = (uint)*(ushort *)(gNewBS + (param_1 * 4 + param_2 + 0xf4) * 2 + 6);
  bVar2 = false;
  if ((uVar1 - 1 & 0xffff) < 0xfffe) {
    bVar2 = gBattleMoves[uVar1].effect == 0x9b /* EFFECT_SEMI_INVULNERABLE */;
  }
  return bVar2;
}

// ---- sub_90db59c  (ROM 0x90db59c)
void sub_90db59c(int param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(gNewBS + (param_1 * 4 + param_2 + 0xf4) * 2 + 6);
  if (uVar1 == 0xffff) {
    uVar1 = 0;
  }
  if ((param_3 != 0) && (gBattleMoves[uVar1].effect == 0x6f /* EFFECT_PROTECT */)) {
    DoesProtectionMoveBlockMove(param_2,param_1,param_3,uVar1,param_4);
  }
  return;
}

// ---- sub_90dba10  (ROM 0x90dba10)
bool sub_90dba10(undefined4 param_1)

{
  bool8 bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar2 = GetBankAbility();
  iVar3 = CanBeFrozen(param_1,param_1);
  bVar4 = false;
  if (iVar3 != 0) {
    if ((iVar2 == 0x70) ||
       (((iVar2 == 0x3e && (bVar1 = RealPhysicalMoveInMoveset((u8)param_1), bVar1 != 0)) ||
        (iVar2 = MoveInMoveset(0x107 /* Facade */,param_1), iVar2 != 0)))) {
      bVar4 = true;
    }
    else {
      iVar2 = MoveInMoveset(0x20d /* Psycho Shift */,param_1);
      bVar4 = iVar2 != 0;
    }
  }
  return bVar4;
}

// ---- sub_90dc344  (ROM 0x90dc344)
undefined8 sub_90dc344(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  u8 bank;
  bool8 bVar1;
  u16 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = 0;
  iVar8 = param_1;
  uVar3 = CheckMoveLimitations(param_1,0,0xff,param_4,param_1,param_2,param_3);
  uVar6 = 0;
  do {
    bank = (u8)param_1;
    uVar2 = GetBattleMonMove(bank,(u8)iVar7);
    uVar4 = (uint)uVar2;
    if (uVar4 == 0) break;
    if ((*(uint *)((iVar7 + 0x2097917) * 4) & uVar3) == 0) {
      if ((uVar4 == 0xf5) && (uVar6 < 2)) {
        uVar6 = 2;
      }
      else {
        iVar5 = GetBankAbility(param_1);
        if ((iVar5 == 0xb0) && ((bVar1 = MoveEffectInMoveset(3 /* EFFECT_ABSORB */,bank), bVar1 != 0 && (uVar6 != 3))))
        {
          uVar6 = 3;
        }
        else if (((gBattleMoves[uVar4].priority == 1) && (uVar6 == 0)) ||
                ((((iVar5 = GetBankAbility(param_1), iVar5 == 0xfc &&
                   (bVar1 = MoveTypeInMoveset(bank,10), bVar1 != 0)) ||
                  ((iVar5 = GetBankAbility(param_1), iVar5 == 0x75 &&
                   (bVar1 = MoveTypeInMoveset(bank,2), bVar1 != 0)))) &&
                 ((gBattleMons[param_1].hp == gBattleMons[param_1].maxHP && (uVar6 == 0)))))) {
          uVar6 = 1;
        }
      }
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 != 4);
  return CONCAT44(iVar8,uVar6);
}

// ---- sub_90dc84c  (ROM 0x90dc84c)
undefined8 sub_90dc84c(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  bool8 bVar1;
  u16 move;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  uVar2 = CheckMoveLimitations(param_1,0,0xff,param_4,param_3,param_2,param_3);
  iVar6 = 0;
  do {
    move = GetBattleMonMove((u8)param_1,(u8)iVar6);
    uVar5 = move;
    if (uVar5 == 0) break;
    if ((*(uint *)((iVar6 + 0x2097917) * 4) & uVar2) == 0) {
      if (gBattleMoves[uVar5].split != 2) {
        iVar4 = GetMoveTypeSpecial(param_1,uVar5);
        if (((iVar4 == param_3) &&
            (uVar5 = AI_SpecialTypeCalc(uVar5,param_1,param_2), (uVar5 & 0x29) == 0)) &&
           (bVar1 = IsDamagingMoveUnusable(move,(u8)param_1,(u8)param_2), bVar1 == 0)) {
          uVar3 = 1;
          goto LAB_090dc884;
        }
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 4);
  uVar3 = 0;
LAB_090dc884:
  return CONCAT44(param_3,uVar3);
}

// ---- sub_90dd758  (ROM 0x90dd758)
undefined8 sub_90dd758(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  uStack_1c = param_2;
  uStack_18 = param_3;
  iVar1 = LoadPartyRange(param_1,(int)&uStack_1c + 2,(int)&uStack_1c + 3);
  uVar4 = uStack_1c >> 0x10 & 0xff;
  iVar1 = iVar1 + uVar4 * 100;
  for (; (int)uVar4 < (int)(uStack_1c >> 0x18); uVar4 = uVar4 + 1) {
    if ((((*(short *)(iVar1 + 0x20) != 0) &&
         (iVar3 = GetMonData(iVar1,0x2d,0), iVar3 == 0)) &&
        (gBattlerPartyIndexes[param_1] != uVar4)) &&
       (uVar2 = 0, *(ushort *)(iVar1 + 0x56) < *(ushort *)(iVar1 + 0x58))) goto LAB_090dd7b2;
    iVar1 = iVar1 + 100;
  }
  uVar2 = 1;
LAB_090dd7b2:
  return CONCAT44(param_1,uVar2);
}

// ---- sub_90dd85a  (ROM 0x90dd85a)
undefined8 sub_90dd85a(uint param_1)

{
  u8 bank;
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  iVar2 = MoveInMoveset(0x1e2 /* Stored Power */,param_1);
  bVar5 = true;
  if (iVar2 == 0) {
    iVar2 = MoveInMoveset(0x1e2 /* Stored Power */,param_1);
    bVar5 = iVar2 != 0;
  }
  uVar4 = 1;
  do {
    bank = (u8)param_1;
    if (gBattleMons[param_1].statStages[uVar4 - 1] < 7) goto code_r0x090dd89e;
    if (bVar5) goto sw_dd8d0_1;
    uVar3 = (uVar4 & 0xff) - 2;
    if (5 < uVar3) {
      bVar1 = PhysicalMoveInMoveset(bank);
      uVar3 = (uint)bVar1;
      goto LAB_090dd8e0;
    }
                        switch(uVar3) {
    case 0:
      bVar1 = MoveSplitOnTeam((u8)(~param_1 & 1),0);
      if (bVar1 == 0) {
        uVar3 = MoveInMoveset(0x2b4 /* Body Press */,~param_1 & 1);
        goto LAB_090dd8e0;
      }
    case 1:
    case 4:
    case 5:
sw_dd8d0_1:
      uVar4 = 1;
      goto LAB_090dd8c0;
    case 2:
      bVar1 = SpecialMoveInMoveset(bank);
      uVar3 = (uint)bVar1;
      goto LAB_090dd8e0;
    }
    bVar1 = MoveSplitOnTeam(~bank & 1,1);
    uVar3 = (uint)bVar1;
LAB_090dd8e0:
    if (uVar3 != 0) goto sw_dd8d0_1;
code_r0x090dd89e:
    uVar4 = uVar4 + 1;
  } while (uVar4 != 8);
  uVar4 = 0;
  if ((int)(gBattleResources->flags->flags[param_1] << 0x1f) < 0) {
    bVar1 = DamagingMoveTypeInMoveset(bank,10 /* Fire */);
    uVar4 = (uint)(bVar1 != 0);
  }
LAB_090dd8c0:
  return CONCAT44(param_1,uVar4);
}

// ---- sub_90ddfa4  (ROM 0x90ddfa4)
bool sub_90ddfa4(uint param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = ~param_1 & 1;
  if ((((gBattleMons[uVar1].hp == 0) ||
       (bVar2 = true, *(char *)(gNewBS + param_1 * 4 + uVar1 + 0x8f4) == '\0')) &&
      (bVar2 = false, gBattleTypeFlags << 0x1f < 0)) && (gBattleMons[uVar1 | 2].hp != 0)) {
    bVar2 = *(char *)(gNewBS + param_1 * 4 + (uVar1 | 2) + 0x8f4) != '\0';
  }
  return bVar2;
}

// ---- sub_90de930  (ROM 0x90de930)
bool sub_90de930(int param_1,int param_2,uint param_3,int param_4,char param_5)

{
  bool8 bVar1;
  u16 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if ((param_4 == 0) || (*(int *)(gNewBS + (param_1 + 0x240) * 4 + 4) != 0)) {
    uVar5 = (uint)*(byte *)(gNewBS + param_1 + 0x1e9);
    if (uVar5 == 0) {
      uVar5 = GetBankAbility(param_1);
      uVar3 = GetBankMegaFormAbility(param_1,param_2);
    }
    else {
      uVar3 = GetBankAbility(param_1);
    }
    if ((gStatuses3[param_1] & 0x130400c0) == 0) {
      if ((((uVar5 != uVar3) && (gBattleMons[param_1].species != 0x11a)) &&
          (gBattleMons[param_1].species != 0x37b)) && (uVar3 != 0)) {
        if (uVar5 == 3) {
          if (param_3 == 0x237) {
            return true;
          }
          if (param_3 < 0x238) {
            if (param_3 == 0xc5) {
              return true;
            }
            if (param_3 == 0x20f) {
              return true;
            }
            if (param_3 == 0xb6) {
              return true;
            }
          }
          else {
            if (param_3 == 0x2c4) {
              return true;
            }
            if (param_3 == 0x318) {
              return true;
            }
            if (param_3 == 0x244) {
              return true;
            }
          }
        }
        if ((param_5 != '\0') && ((iVar4 = IsMoxieAbility(uVar5), iVar4 != 0 || (uVar5 == 3)))) {
          bVar1 = MoveWouldHitFirst((u16)param_3,(u16)param_1,(u16)param_2);
          if (bVar1 != 0) {
            uVar2 = CalcFinalAIMoveDamage((u16)param_3,(u8)param_1,(u8)param_2,1,(void *)0x0);
            return gBattleMons[param_2].hp <= uVar2;
          }
        }
      }
      return false;
    }
  }
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return true;
}

// ---- sub_90dfa24  (ROM 0x90dfa24)
bool sub_90dfa24(uint param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  bool8 bVar2;
  u16 move;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  u32 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  u8 uStack_94;
  u8 uStack_90;
  uint uStack_8c;
  uint uStack_84;
  u8 uStack_74;
  u8 uStack_73;
  undefined1 auStack_72 [94];
  
  uVar4 = CheckMoveLimitations(param_2,0,0xff);
  Memset(auStack_72,0,0x5a);
  uStack_94 = (u8)param_2;
  uStack_74 = uStack_94;
  uStack_90 = (u8)param_3;
  uStack_73 = uStack_90;
  PopulateDamageCalcStructWithBaseAttackerData(&uStack_74);
  PopulateDamageCalcStructWithBaseDefenderData(&uStack_74);
  uVar10 = 0;
  uStack_84 = 0xffffffff;
  uVar1 = 0;
  uStack_8c = 0xff;
  do {
    move = GetBattleMonMove(uStack_94,(u8)uVar10);
    uVar5 = move;
    if (uVar5 == 0) break;
    uVar9 = (uint)gBattleMoves[uVar5].effect;
    if (((*(uint *)((uVar10 + 0x2097917) * 4) & uVar4) == 0) &&
       (iVar6 = CheckContact(uVar5,param_2), iVar6 != 0)) {
      uVar8 = uVar9 - 0x7d & 0xff;
      if (uVar8 < 0x1f) {
        if (-1 < (int)((0x44980001U >> uVar8) << 0x1f)) {
LAB_090dfaba:
          uVar8 = uVar9 - 0x4b & 0xff;
          if (((0xe < uVar8) || (-1 < (int)((0x4021U >> uVar8) << 0x1f))) && (1 < uVar9 - 0x26)) {
            bVar2 = MoveWillHit(move,uStack_94,uStack_90);
            uVar3 = 0x65;
            if (bVar2 == 0) {
              uVar3 = AccuracyCalc(uVar5,param_2,param_3);
            }
            uVar7 = GetFinalAIMoveDamage(move,uStack_94,uStack_90,1,&uStack_74);
            if ((uVar7 < uStack_84) && (uVar1 < uVar3)) {
              uStack_8c = uVar10 & 0xff;
              uStack_84 = uVar7;
              uVar1 = uVar3;
            }
          }
        }
      }
      else if (uVar9 != 0x9e) goto LAB_090dfaba;
    }
    uVar10 = uVar10 + 1;
  } while (uVar10 != 4);
  bVar11 = false;
  if (uStack_8c != 0xff) {
    bVar11 = gBattleMons[param_2].moves[uStack_8c] == param_1;
  }
  return bVar11;
}

// ---- sub_90dfd28  (ROM 0x90dfd28)
undefined4 sub_90dfd28(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  u8 bank;
  bool8 bVar3;
  u16 move;
  u16 healAmount;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar4 = CheckMoveLimitations(param_1,0,0xff);
  sVar2 = *(short *)(gNewBS + (param_2 * 4 + param_1 + 0xf4) * 2 + 6);
  if (sVar2 == -1) {
    sVar2 = 0;
  }
  iVar7 = 0;
  do {
    bank = (u8)param_1;
    move = GetBattleMonMove(bank,(u8)iVar7);
    uVar5 = move;
    if (uVar5 == 0) {
      return 0;
    }
    if ((*(uint *)((iVar7 + 0x2097917) * 4) & uVar4) != 0) goto LAB_090dfd76;
    bVar1 = gBattleMoves[uVar5].effect;
    if (bVar1 == 0x84) {
LAB_090dfd90:
      healAmount = GetAmountToRecoverBy(bank,(u8)param_2,move);
      bVar3 = MoveWouldHitFirst(move,(u16)param_1,(u16)param_2);
      if ((bVar3 != 0) &&
         (bVar3 = CanKnockOutAfterHealing((u8)param_2,bank,healAmount,1,0), bVar3 == 0)) {
        return 1;
      }
    }
    else if ((byte)(bVar1 - 3) < 0x1e) {
      if ((int)((0x20000021U >> (uint)(byte)(bVar1 - 3)) << 0x1f) < 0) goto LAB_090dfd90;
    }
    else if ((bVar1 == 0x6f) &&
            (iVar6 = DoesProtectionMoveBlockMove(param_2,param_1,sVar2,uVar5), iVar6 != 0))
    goto LAB_090dfd90;
LAB_090dfd76:
    iVar7 = iVar7 + 1;
    if (iVar7 == 4) {
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
      return 0;
    }
  } while( true );
}

// ---- sub_90e031c  (ROM 0x90e031c)
undefined8 sub_90e031c(uint param_1,int param_2)

{
  u8 bankAtk;
  bool8 bVar1;
  u16 move;
  uint uVar2;
  u32 uVar3;
  u32 uVar4;
  u8 bankDef;
  uint uVar5;
  
  bankAtk = (u8)param_1;
  bankDef = (u8)param_2;
  bVar1 = CanKnockOut(bankAtk,bankDef);
  uVar2 = (uint)bVar1;
  uVar5 = 1;
  if (uVar2 == 0) {
    move = GetStrongestMove(bankAtk,bankDef);
    uVar3 = GetFinalAIMoveDamage(move,bankAtk,bankDef,1,(void *)0x0);
    uVar4 = GetSecondaryEffectDamage(bankDef);
    uVar5 = (uint)((uint)gBattleMons[param_2].hp <= uVar3 + uVar4);
    param_1 = uVar2;
  }
  return CONCAT44(param_1,uVar5);
}

// ---- sub_90e0364  (ROM 0x90e0364)
bool8 sub_90e0364(uint param_1)

{
  bool8 bVar1;
  uint uVar2;
  
  uVar2 = ~param_1 & 1;
  if (((*(uint *)(&gBitTable + uVar2 * 4) & (uint)gAbsentBattlerFlags) == 0) &&
     (bVar1 = CanKnockOut((u8)param_1,(u8)uVar2), bVar1 != 0)) {
    return 1;
  }
  bVar1 = 0;
  if ((gBattleTypeFlags & 1) != 0) {
    bVar1 = 0;
    if ((*(uint *)(&gBitTable + (uVar2 | 2) * 4) & (uint)gAbsentBattlerFlags) == 0) {
      bVar1 = CanKnockOut((u8)param_1,(u8)(uVar2 | 2));
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
  return bVar1;
}

// ---- sub_9350518  (ROM 0x9350518)
undefined4 sub_9350518(int param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if ((gBattleMons[param_1].status1 & param_2) == 0) {
    return 0;
  }
  uVar1 = StringCopy(&gBattleTextBuff1,param_3);
  return uVar1;
}

// ---- sub_93505ac  (ROM 0x93505ac)
undefined4 sub_93505ac(uint param_1)

{
  undefined4 uVar1;
  
  if (((gBattleTypeFlags << 5 < 0) && ((_UNK_0203e044 & 0xf) != 0)) || (gTerrainType == param_1)) {
    return 0;
  }
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
  gTerrainType = (byte)param_1;
  uVar1 = FlagGet(0x1034);
  return uVar1;
}

// ---- sub_9350712  (ROM 0x9350712)
void sub_9350712(ushort param_1)

{
  gBattleWeather = param_1 & 0xfaab;
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
  FlagGet(0x1034);
  return;
}

// ---- sub_93508b0  (ROM 0x93508b0)
void sub_93508b0(void)

{
  GetBattlerSide(gActiveBattler);
  return;
}

// ---- sub_9350ac6  (ROM 0x9350ac6)
undefined4 sub_9350ac6(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte bankAtk;
  bool8 bVar3;
  u8 uVar4;
  u16 move;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  ushort uVar9;
  code *pcVar10;
  short *psVar11;
  short *psVar12;
  undefined8 uVar13;
  int iStack_3c;
  
  if ((gBattleTypeFlags & 1) != 0) {
    return 0;
  }
  psVar11 = (short *)(~(uint)gActiveBattler & 1);
  iVar5 = GetBankAbility(psVar11);
  if (iVar5 != 0x19) {
    return 0;
  }
  bVar3 = WillFaintFromSecondaryDamage((u8)psVar11);
  bankAtk = gActiveBattler;
  if (bVar3 != 0) {
    return 0;
  }
  psVar12 = (short *)(uint)gActiveBattler;
  uVar4 = AdjustMoveLimitationFlagsForAI(gActiveBattler);
  uVar6 = CheckMoveLimitations(psVar12,0,uVar4);
  iStack_3c = 0;
LAB_09350b10:
  move = GetBattleMonMove(gActiveBattler,(u8)iStack_3c);
  uVar7 = move;
  if (uVar7 == 0) goto LAB_09350b7c;
  if ((*(uint *)((iStack_3c + 0x2097917) * 4) & uVar6) == 0) {
    iVar5 = CheckTableForMove(uVar7,&UNK_09040136);
    if (iVar5 != 0) {
      return 0;
    }
    if (gBattleMoves[uVar7].split == 2) {
      uVar13 = MoveBlockedBySubstitute(uVar7,psVar12,psVar11);
      uVar8 = (undefined4)((ulonglong)uVar13 >> 0x20);
      if ((int)uVar13 == 0) {
        bVar1 = gBattleMoves[uVar7].effect;
        if (bVar1 == 0x76) {
LAB_09350d9e:
          uVar7 = CanBeConfused(psVar11,1);
        }
        else {
          if (0x76 < bVar1) {
            if (bVar1 == 0xa8) {
              return 0;
            }
            if (bVar1 < 0xa9) {
              if (bVar1 == 0xa4) {
                uVar7 = HailHurts(psVar11);
                goto joined_r0x09350cc0;
              }
              if (bVar1 < 0xa5) {
                if (bVar1 == 0x7f) {
                  return 0;
                }
                if (bVar1 == 0x99) {
                  return 0;
                }
              }
              else {
                if (bVar1 == 0xa6) goto LAB_09350d9e;
                if (bVar1 == 0xa7) {
                  uVar7 = CanBeBurned(psVar11,1);
                  goto joined_r0x09350cc0;
                }
              }
            }
            else {
              if (bVar1 == 0xbb) {
LAB_09350d8c:
                uVar7 = CanBePutToSleep(psVar11,1,psVar12);
                goto joined_r0x09350cc0;
              }
              if (bVar1 < 0xbc) {
                if (bVar1 == 0xb1) {
                  if (uVar7 == 0x10f) {
                    uVar9 = gBattleMons[(int)psVar11].species;
                    uVar2 = (undefined1)gBattleMons[(int)psVar12].species;
                    iVar5 = sub_90744d8(uVar2,gBattleMons[(int)psVar12].item);
                    if ((iVar5 != 0) &&
                       (iVar5 = sub_90744d8(uVar2,gBattleMons[(int)psVar11].item), iVar5 != 0)) {
                      uVar9 = uVar9 & 0xff;
                      iVar5 = sub_90744d8(uVar9,gBattleMons[(int)psVar12].item);
                      if (iVar5 != 0) {
                        uVar13 = sub_90744d8(uVar9,gBattleMons[(int)psVar11].item);
                        uVar8 = (undefined4)((ulonglong)uVar13 >> 0x20);
                        if ((int)uVar13 != 0) {
                          pcVar10 = (code *)&GetBattlerSide;
                          goto stub_9350fbc;
                        }
                      }
                    }
                  }
                }
                else if ((bVar1 == 0xb3) && ((char)psVar12[0x1011fa0] == '\0')) {
                  return 0;
                }
              }
              else if (bVar1 == 0xe8) {
                if (uVar7 == 0x292) {
                  uVar8 = 7;
                  goto LAB_09350f38;
                }
                if (uVar7 == 0x294) goto LAB_09350f54;
              }
              else {
                if (bVar1 != 0xef) {
                  if ((bVar1 == 0xbf) && (uVar7 != 0x11d)) {
                    return 0;
                  }
                  goto LAB_09350b72;
                }
                if (uVar7 == 0x1d8) {
                  uVar7 = sub_90753d4(psVar12);
                  goto joined_r0x09350cc0;
                }
                if (uVar7 == 0x289) {
                  pcVar10 = (code *)&GetBattlerSide;
                  goto stub_9350fbc;
                }
              }
            }
            goto LAB_09350b72;
          }
          if (bVar1 == 0x43) {
            uVar7 = CanBeParalyzed(psVar11,1);
          }
          else if (bVar1 < 0x44) {
            if (bVar1 != 0x21) {
              if (bVar1 < 0x22) {
                if (bVar1 == 1) goto LAB_09350d8c;
                if (bVar1 == 0x1c) {
                  uVar7 = HasMonToSwitchTo(psVar11);
                  goto joined_r0x09350cc0;
                }
              }
              else {
                if (bVar1 == 0x31) goto LAB_09350d9e;
                if (bVar1 == 0x42) goto LAB_09350c8e;
              }
              goto LAB_09350b72;
            }
LAB_09350c8e:
            uVar7 = CanBePoisoned(psVar11,psVar12,1);
          }
          else {
            if (bVar1 != 0x6d) {
              if (bVar1 < 0x6e) {
                if (bVar1 == 0x54) {
LAB_09350f54:
                  uVar8 = 0xc;
LAB_09350f38:
                  iVar5 = IsOfType(psVar11,uVar8);
                  if (iVar5 == 0) {
                    return 0;
                  }
                }
                else if (bVar1 == 0x6b) {
                  uVar7 = gBattleMons[(int)psVar11].status1 & 7;
                  goto joined_r0x09350cc0;
                }
              }
              else {
                if (bVar1 != 0x72) {
                  if (bVar1 == 0x73) {
                    uVar7 = SandstormHurts(psVar11);
                    goto joined_r0x09350cc0;
                  }
                  if (bVar1 != 0x70) goto LAB_09350b72;
                  do {
                    pcVar10 = (code *)&GetBattlerSide;
                    psVar12 = psVar11;
                  } while (((uVar7 == 0x1d5) || (uVar7 == 0x1e1)) || (uVar7 != 0x1d4));
                  goto stub_9350fbc;
                }
                if (-1 < (int)(gStatuses3[(int)psVar11] << 0x1a)) {
                  return 0;
                }
              }
              goto LAB_09350b72;
            }
            uVar7 = IsOfType(psVar12,7 /* Ghost */);
          }
        }
joined_r0x09350cc0:
        if (uVar7 != 0) {
          return 0;
        }
      }
    }
    else {
      uVar4 = GetAIAbility(bankAtk,(u8)psVar11,move);
      iVar5 = sub_905faa2(uVar4);
      if (iVar5 != 0) {
        return 0;
      }
      iVar5 = AI_SpecialTypeCalc(uVar7,psVar12,psVar11);
      if (iVar5 << 0x1e < 0) {
        return 0;
      }
    }
  }
LAB_09350b72:
  iStack_3c = iStack_3c + 1;
  if (iStack_3c == 4) {
LAB_09350b7c:
    psVar11 = (short *)(param_1 + param_2 * 100 + 0x20);
    while( true ) {
      if (param_3 <= param_2) {
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
        return 0;
      }
      if ((psVar11[0x1b] != 0) && (*psVar11 != 0)) break;
      param_2 = param_2 + 1;
      psVar11 = psVar11 + 0x32;
    }
    uVar8 = 0x2d;
    pcVar10 = (code *)&GetMonData;
    psVar12 = psVar11 + -0x10;
stub_9350fbc:
    uVar8 = (*pcVar10)(psVar12,uVar8);
    return uVar8;
  }
  goto LAB_09350b10;
}

// ---- sub_93510ce  (ROM 0x93510ce)
undefined4 sub_93510ce(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 6) {
    if ((int)(param_2 << 0x18) < 0) {
      if ((param_2 & 0x41) == 0) {
LAB_093510e8:
        uVar2 = GetBattlerSide(gActiveBattler);
        return uVar2;
      }
    }
    else {
      iVar1 = PredictedMoveWontDoTooMuchToMon
                        (gActiveBattler,param_3 + param_1 * 100,~gActiveBattler & 1,param_2);
      if (iVar1 != 0) goto LAB_093510e8;
    }
  }
  return 0;
}

// ---- sub_9351174  (ROM 0x9351174)
undefined8 sub_9351174(int param_1,uint param_2,uint param_3,undefined4 param_4,byte param_5)

{
  bool8 bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  Pokemon *mon;
  
  uVar4 = (uint)param_5;
  if ((param_2 < 6) &&
     (((mon = (Pokemon *)(param_1 + param_2 * 100), (param_3 & 0x41) == 0x41 &&
       (iVar3 = PredictedMoveWontDoTooMuchToMon
                          (gActiveBattler,mon,param_4,param_3,param_1,uVar4,param_3), iVar3 != 0))
      || ((iVar3 = PredictedMoveKOsSelfDueToContact(gActiveBattler,mon,param_4), iVar3 != 0 &&
          (bVar1 = PredictedMoveWontKOMon(gActiveBattler,mon,(u8)param_4), bVar1 != 0)))))) {
    ConfirmAISwitch(param_2,uVar4);
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return CONCAT44(param_1,uVar2);
}

// ---- sub_9351292  (ROM 0x9351292)
longlong sub_9351292(uint param_1,uint param_2,int param_3,int param_4)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  longlong lVar5;
  
  if (5 < param_1) {
LAB_093512a4:
    return (ulonglong)param_1 << 0x20;
  }
  if (((param_4 == 0) &&
      (((uVar3 = ~(uint)gActiveBattler & 1, -1 < (int)(param_2 << 0x19) ||
        (((param_2 & 1) == 0 && ((-1 < (int)(param_2 << 0x1b) || ((int)(param_2 << 0x18) < 0))))))
       || ((-1 < gBattleTypeFlags << 0x1f &&
           (iVar2 = PredictedMoveWontDoTooMuchToMon
                              ((uint)gActiveBattler,param_3 + param_1 * 100,uVar3,param_2,param_1,
                               param_1,param_3), iVar2 == 0)))))) && ((param_2 & 10) == 0)) {
    bVar4 = false;
    if (gBattleMons[uVar3].hp != 0) {
      bVar1 = Can2HKO(gActiveBattler,(u8)uVar3);
      bVar4 = bVar1 != 0;
    }
    if ((((-1 < gBattleTypeFlags << 0x1f) || (gBattleMons[uVar3 | 2].hp == 0)) ||
        (bVar1 = Can2HKO(gActiveBattler,(u8)(uVar3 | 2)), bVar1 == 0)) && (!bVar4))
    goto LAB_093512a4;
  }
  lVar5 = GetBattlerSide(gActiveBattler);
  return lVar5;
}

// ---- sub_93513c0  (ROM 0x93513c0)
undefined4 sub_93513c0(Pokemon *param_1,undefined4 param_2,undefined4 param_3)

{
  u8 uVar1;
  u8 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = GetMostSuitableMonToSwitchIntoByParty(param_1);
  uVar2 = GetMostSuitableMonToSwitchIntoFlags();
  if ((5 < uVar1) ||
     (iVar3 = SwitchToBestResistMonHelper(param_2,param_1,uVar1,uVar2,param_3), iVar3 == 0)) {
    uVar1 = GetSecondMostSuitableMonToSwitchIntoByParty(param_1);
    uVar2 = GetSecondMostSuitableMonToSwitchIntoFlags();
    if ((5 < uVar1) ||
       (iVar3 = SwitchToBestResistMonHelper(param_2,param_1,uVar1,uVar2,param_3), iVar3 == 0)) {
      uVar4 = GetBattlerSide(gActiveBattler);
      return uVar4;
    }
  }
  return 1;
}
