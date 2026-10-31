// ai_master.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- BattleAI_DoAIProcessing  (ROM 0x90c6f3c)
void BattleAI_DoAIProcessing(AIScript *aiScriptData)

{
  sbyte sVar1;
  AI_ThinkingStruct *pAVar2;
  byte bVar3;
  code *pcVar4;
  
LAB_090c6f42:
  do {
    pAVar2 = gBattleResources->ai;
    bVar3 = pAVar2->aiState;
    do {
      if (bVar3 == 2) {
        return;
      }
      if (bVar3 == 0) {
        if (gBattleMons[UNK_02023d6b].pp[pAVar2->movesetIndex] == 0) {
          pAVar2->moveConsidered = 0;
        }
        else {
          pAVar2->moveConsidered = gBattleMons[UNK_02023d6b].moves[pAVar2->movesetIndex];
        }
        pAVar2->aiState = 1;
        goto LAB_090c6f42;
      }
    } while (bVar3 != 1);
    if ((pAVar2->moveConsidered == 0) || (pAVar2->score[pAVar2->movesetIndex] < 1)) {
      pAVar2->score[pAVar2->movesetIndex] = 0;
    }
    else if ((pAVar2->aiLogicId < 0x20) &&
            (pcVar4 = *(code **)((uint)pAVar2->aiLogicId * 4 + 0x91491e0), pcVar4 != (code *)0x0)) {
      sVar1 = (*pcVar4)(UNK_02023d6b,gBattlerTarget,pAVar2->moveConsidered,
                        pAVar2->score[pAVar2->movesetIndex],aiScriptData);
      gBattleResources->ai->score[gBattleResources->ai->movesetIndex] = sVar1;
    }
    pAVar2 = gBattleResources->ai;
    bVar3 = pAVar2->movesetIndex + 1;
    pAVar2->movesetIndex = bVar3;
    if ((3 < bVar3) || (bVar3 = pAVar2->aiAction & 8, (pAVar2->aiAction & 8) != 0)) {
      bVar3 = pAVar2->aiState + 1;
    }
    pAVar2->aiState = bVar3;
  } while( true );
}

// ---- TryTempMegaEvolveAllBanks  (ROM 0x90c7008)
void TryTempMegaEvolveAllBanks
               (BattlePokemon *backupBattleMons,u16 *backupSpecies,u8 *backupAbilities)

{
  u8 uVar1;
  Pokemon *mon;
  undefined1 *puVar2;
  u8 *puVar3;
  int iVar4;
  undefined1 *in_r3;
  
  iVar4 = (int)backupBattleMons[6].nickname * 4;
  if (*(int *)(gNewBS + iVar4 + 4) == 0) {
    backupAbilities[0] = 0;
    backupAbilities[1] = 0;
    *in_r3 = 0;
  }
  else {
    mon = (Pokemon *)GetBankPartyData();
    *(ushort *)backupAbilities = mon->species;
    puVar2 = (undefined1 *)GetAbilityLocation(backupBattleMons);
    *in_r3 = *puVar2;
    memcpy_(backupSpecies,gBattleMons + (int)backupBattleMons);
    mon->species = *(ushort *)(*(int *)(gNewBS + iVar4 + 4) + 4);
    CalculateMonStats(mon);
    memcpy_((int)backupBattleMons * 0x58 + 0x2023be6,&mon->attack,10);
    puVar3 = (u8 *)GetAbilityLocation(backupBattleMons);
    uVar1 = GetMonAbilityAfterTrace(mon,~(byte)backupBattleMons & 1);
    *puVar3 = uVar1;
    if (gBattleTypeFlags << 3 < 0) {
      sub_909a9de(backupBattleMons);
    }
    else {
      iVar4 = (uint)mon->species * 0x1c;
      gBattleMons[(int)backupBattleMons].type1 = (&UNK_097b98f2)[iVar4];
      gBattleMons[(int)backupBattleMons].type2 = (&UNK_097b98f3)[iVar4];
    }
  }
  return;
}

// ---- WontHitTargetWithMove  (ROM 0x90c7120)
bool8 WontHitTargetWithMove(u8 bankAtk,u8 bankDef,u16 move)

{
  bool8 bVar1;
  int iVar2;
  
  if (((gStatuses3[bankDef] & 0x130400c0) == 0) ||
     (((iVar2 = GetBaseMoveTarget(move,bankAtk), iVar2 != 0 &&
       ((-1 < iVar2 << 0x1a || (iVar2 = sub_90da104(move,bankAtk,bankAtk ^ 2), iVar2 == 0)))) ||
      (bVar1 = MoveWillHit(move,bankAtk,bankDef), bVar1 != 0)))) {
    bVar1 = 0;
  }
  else {
    bVar1 = MoveWouldHitFirst(move,(ushort)bankAtk,(ushort)bankDef);
    bVar1 = 1 - (bVar1 == 0);
  }
  return bVar1;
}

// ---- HasChosenToDamageTarget  (ROM 0x90c7180)
bool8 HasChosenToDamageTarget(u8 bankAtk,u8 bankDef)

{
  bool8 bVar1;
  u16 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = (uint)bankAtk;
  if (((gBattleMons[uVar4].hp == 0) || (iVar3 = func_0x090db1c4(), iVar3 != 0)) ||
     (gChosenMovesByBanks[uVar4] == 0)) {
    bVar1 = 0;
  }
  else {
    bVar1 = 1;
    if (gBattleStruct->moveTarget[uVar4] != bankDef) {
      uVar2 = GetAIChosenMove(bankAtk,bankDef);
      uVar4 = GetBaseMoveTarget(uVar2,uVar4);
      bVar1 = 1 - ((uVar4 & 0x28) == 0);
    }
  }
  return bVar1;
}

// ---- PartnerWillKOTargetBeforeItCanAttack  (ROM 0x90c71e0)
bool8 PartnerWillKOTargetBeforeItCanAttack(u8 bankAtk,u8 bankDef)

{
  u8 bankAtk_00;
  bool8 bVar1;
  uint uVar2;
  
  uVar2 = bankAtk ^ 2;
  bankAtk_00 = (u8)uVar2;
  bVar1 = HasChosenToDamageTarget(bankAtk_00,bankDef);
  if (bVar1 != 0) {
    bVar1 = CanKnockOutWithFasterMove(bankDef,bankAtk_00,gChosenMovesByBanks[uVar2]);
    if ((bVar1 == 0) &&
       (bVar1 = CanKnockOutWithFasterMove(bankDef ^ 2,bankAtk_00,gChosenMovesByBanks[uVar2]),
       bVar1 == 0)) {
      bVar1 = MoveWouldHitFirst(gChosenMovesByBanks[uVar2],(u16)uVar2,(ushort)bankDef);
      return 1 - (bVar1 == 0);
    }
  }
  return 0;
}

// ---- HittingTargetWithUselessStatusMove  (ROM 0x90c722c)
bool8 HittingTargetWithUselessStatusMove(u8 bankAtk,u8 bankDef,u8 *actionOrMoveIndex)

{
  bool8 bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = (uint)bankAtk;
  uVar5 = (uint)gBattleMons[uVar2].moves[actionOrMoveIndex[bankDef]];
  uVar6 = uVar2;
  iVar4 = GetBattlerSide((uint)bankDef);
  iVar3 = GetBattlerSide(uVar2);
  if (((iVar4 == iVar3) || (gBattleMoves[uVar5].split != 2)) ||
     (iVar3 = GetBaseMoveTarget(uVar5,uVar2,uVar5 * 0xc,2,uVar6,iVar4,actionOrMoveIndex), iVar3 != 0
     )) {
    return 0;
  }
  bVar1 = PartnerWillKOTargetBeforeItCanAttack(bankAtk,bankDef);
  return 1 - (bVar1 == 0);
}

// ---- GetTotalDamageForTargets  (ROM 0x90c7298)
u32 GetTotalDamageForTargets(u16 move,u8 bankAtk,u8 baseBankDef)

{
  uint uVar1;
  u32 uVar2;
  int iVar3;
  uint uVar4;
  u32 uVar5;
  
  uVar4 = (uint)baseBankDef;
  uVar5 = 0;
  if (gBattleMons[uVar4].hp != 0) {
    uVar5 = GetFinalAIMoveDamage(move,bankAtk,baseBankDef,1,(void *)0x0);
    uVar5 = __udivsi3(uVar5 * 100,gBattleMons[uVar4].maxHP);
  }
  if ((gBattleMons[uVar4 ^ 2].hp != 0) &&
     (uVar1 = GetBaseMoveTarget(move,bankAtk), (uVar1 & 0x28) != 0)) {
    uVar2 = GetFinalAIMoveDamage(move,bankAtk,(u8)(uVar4 ^ 2),1,(void *)0x0);
    iVar3 = __udivsi3(uVar2 * 100,gBattleMons[uVar4].maxHP);
    uVar5 = uVar5 + iVar3;
  }
  return uVar5;
}

// ---- GetTargetsKnockedOut  (ROM 0x90c7330)
u8 GetTargetsKnockedOut(u16 move,u8 bankAtk,u8 baseBankDef)

{
  u8 bankAtk_00;
  bool8 bVar1;
  uint uVar2;
  uint uVar3;
  u32 uVar4;
  u32 uVar5;
  u8 bankDef;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  uVar7 = (uint)baseBankDef;
  uVar2 = move;
  uVar6 = bankAtk ^ 2;
  bankAtk_00 = (u8)uVar6;
  if (gBattleMons[uVar7].hp != 0) {
    bVar1 = MoveKnocksOutXHits(move,bankAtk,baseBankDef,1);
    bVar8 = true;
    if (bVar1 != 0) goto LAB_090c7356;
    if ((((gBattleMoves[uVar2].effect != 0x28 /* EFFECT_SUPER_FANG */) &&
         (bVar1 = HasChosenToDamageTarget(bankAtk_00,baseBankDef), bVar1 != 0)) &&
        (bVar1 = MoveWouldHitFirst(gChosenMovesByBanks[uVar6],(u16)uVar6,(ushort)baseBankDef),
        bVar1 != 0)) &&
       (uVar4 = GetFinalAIMoveDamage
                          (gChosenMovesByBanks[uVar6],bankAtk_00,baseBankDef,1,(void *)0x0),
       uVar4 < gBattleMons[uVar7].hp)) {
      uVar5 = GetFinalAIMoveDamage(move,bankAtk,baseBankDef,1,(void *)0x0);
      if (uVar4 < gBattleMons[uVar7].hp) {
        bVar8 = (uint)gBattleMons[uVar7].hp <= uVar4 + uVar5;
        goto LAB_090c7356;
      }
    }
  }
  bVar8 = false;
LAB_090c7356:
  uVar7 = uVar7 ^ 2;
  if (gBattleMons[uVar7].hp == 0) {
    return bVar8;
  }
  uVar3 = GetBaseMoveTarget(uVar2,(uint)bankAtk);
  if ((uVar3 & 0x28) == 0) {
    return bVar8;
  }
  bankDef = (u8)uVar7;
  bVar1 = MoveKnocksOutXHits(move,bankAtk,bankDef,1);
  if (bVar1 == 0) {
    if (gBattleMoves[uVar2].effect == 0x28 /* EFFECT_SUPER_FANG */) {
      return bVar8;
    }
    bVar1 = HasChosenToDamageTarget(bankAtk_00,bankDef);
    if (bVar1 == 0) {
      return bVar8;
    }
    bVar1 = MoveWouldHitFirst(gChosenMovesByBanks[uVar6],(u16)uVar6,(u16)uVar7);
    if (bVar1 == 0) {
      return bVar8;
    }
    uVar4 = GetFinalAIMoveDamage(gChosenMovesByBanks[uVar6],bankAtk_00,bankDef,1,(void *)0x0);
    if (gBattleMons[uVar7].hp <= uVar4) {
      return bVar8;
    }
    uVar5 = GetFinalAIMoveDamage(move,bankAtk,bankDef,1,(void *)0x0);
    if (gBattleMons[uVar7].hp <= uVar4) {
      return bVar8;
    }
    if (uVar4 + uVar5 < (uint)gBattleMons[uVar7].hp) {
      return bVar8;
    }
  }
  return bVar8 + 1;
}

// ---- UpdateBestDoublesKillingMoves  (ROM 0x90c7524)
void UpdateBestDoublesKillingMoves(void)

{
  byte bankAtk;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  for (uVar3 = 0; uVar3 < gBattlersCount; uVar3 = uVar3 + 1 & 0xff) {
    bankAtk = (&gBanksByTurnOrder)[uVar3];
    uVar4 = (uint)bankAtk;
    for (uVar2 = 0; uVar2 < gBattlersCount; uVar2 = uVar2 + 1 & 0xff) {
      if (((uVar4 != uVar2) && ((uVar4 ^ 2) != uVar2)) && (gBattleMons[uVar2].hp != 0)) {
        iVar1 = uVar2 + uVar4 * 4;
        UpdateBestDoubleKillingMoveScore
                  (bankAtk,(byte)uVar2,(u8)(uVar4 ^ 2),(byte)uVar2 ^ 2,
                   (s8 *)(gNewBS + (iVar1 + 500) * 4),(u16 *)(gNewBS + (iVar1 + 0x3d8) * 2));
      }
    }
  }
  return;
}

// ---- GetAIFlags  (ROM 0x90c77b0)
u32 GetAIFlags(void)

{
  uint uVar1;
  u32 uVar2;
  int iVar3;
  
  if ((int)(gBattleTypeFlags << 0x18) < 0) {
    uVar2 = 0x40000000;
  }
  else if ((gBattleTypeFlags & 0x400) == 0) {
    if ((int)(gBattleTypeFlags << 0x1b) < 0) {
      uVar2 = 0x80000000;
    }
    else if (((gBattleTypeFlags & 0x6000100) == 0) &&
            (iVar3 = sub_909a418(_UNK_020386ae), iVar3 == 0)) {
      if ((((gBattleTypeFlags & 0x80800) == 0) || (_UNK_020386ae == 0x400)) &&
         (iVar3 = IsRaidBattle(), iVar3 == 0)) {
        uVar2 = 1;
        if (-1 < (int)(gBattleTypeFlags << 0xe)) {
          uVar2 = 3;
          if (-1 < (int)(gBattleTypeFlags << 0xd)) {
            if ((int)(gBattleTypeFlags << 10) < 0) {
              VarGet(0x5010);
            }
            uVar2 = 7;
            if (-1 < (int)(gBattleTypeFlags << 0x1c)) {
              uVar2 = *(u32 *)(&UNK_0823eae4 + (uint)_UNK_020386ae * 0x28);
            }
          }
        }
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = sub_909a830(gActiveBattler);
    }
  }
  else {
    uVar1 = func_0x090c774c(gActiveBattler);
    uVar2 = uVar1 | 0x20000000;
  }
  if ((gBattleTypeFlags & 0x400008) == 0x400000) {
    uVar2 = uVar2 | 1;
  }
  return uVar2;
}

// ---- BattleAI_SetupAIData  (ROM 0x90c7880)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void BattleAI_SetupAIData(u8 defaultScoreMoves)

{
  BattleResources *pBVar1;
  u8 uVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  undefined4 uVar6;
  u32 uVar7;
  byte extraout_r1;
  AI_ThinkingStruct *pAVar8;
  int iVar9;
  int iVar10;
  sbyte sVar11;
  AI_ThinkingStruct *pAVar12;
  
  uVar5 = (uint)defaultScoreMoves;
  pAVar8 = gBattleResources->ai;
  pAVar12 = pAVar8 + 1;
  do {
    pAVar8->aiState = 0;
    pBVar1 = gBattleResources;
    pAVar8 = (AI_ThinkingStruct *)&pAVar8->movesetIndex;
  } while (pAVar8 != pAVar12);
  pAVar12 = gBattleResources->ai;
  iVar9 = 0;
  do {
    sVar11 = (sbyte)(uVar5 & 1);
    if ((uVar5 & 1) != 0) {
      sVar11 = 100;
    }
    iVar10 = iVar9 + 1;
    pAVar12->score[iVar9] = sVar11;
    uVar5 = uVar5 >> 1;
    iVar9 = iVar10;
  } while (iVar10 != 4);
  pBVar1->AIScriptsStack->size = 0;
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
  UNK_02023d6b = gActiveBattler;
  if ((gBattleTypeFlags & 1) == 0) {
    gBattlerTarget = gActiveBattler ^ 1;
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
  }
  else {
    bVar3 = Random2(gActiveBattler);
    bVar4 = GetBattlerSide(gActiveBattler);
    gBattlerTarget = (bVar3 & 2) + (bVar4 ^ 1);
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
    if ((*(uint *)(&gBitTable + (uint)gBattlerTarget * 4) & (uint)gAbsentBattlerFlags) != 0) {
      gBattlerTarget = gBattlerTarget ^ 2;
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
    }
  }
  bVar3 = gActiveBattler;
  uVar2 = AdjustMoveLimitationFlagsForAI(UNK_02023d6b);
  uVar5 = CheckMoveLimitations(bVar3,0,uVar2);
  iVar9 = 0;
  do {
    if ((*(uint *)((iVar9 + 0x2097917) * 4) & uVar5) != 0) {
      gBattleResources->ai->score[iVar9] = 0;
    }
    uVar6 = sub_2097916();
    pAVar12 = gBattleResources->ai;
    __umodsi3(uVar6,100);
    iVar10 = iVar9 + 1;
    pAVar12->simulatedRNG[iVar9] = extraout_r1;
    iVar9 = iVar10;
  } while (iVar10 != 4);
  uVar7 = GetAIFlags();
  pAVar12->aiFlags = uVar7;
  return;
}

// ---- BattleAI_HandleItemUseBeforeAISetup  (ROM 0x90c7988)
void BattleAI_HandleItemUseBeforeAISetup(void)

{
  byte bVar1;
  BattleResources *pBVar2;
  int iVar3;
  BattleHistory *pBVar4;
  BattleHistory *pBVar5;
  byte *pbVar6;
  
  pBVar5 = gBattleResources->battleHistory;
  pBVar4 = pBVar5 + 1;
  do {
    *(undefined1 *)pBVar5->usedMoves[0] = 0;
    pBVar5 = (BattleHistory *)((int)pBVar5->usedMoves[0] + 1);
  } while (pBVar4 != pBVar5);
  if ((gBattleTypeFlags & 0x660098a) == 8) {
    if ((_UNK_020386ae != 0x400) && (iVar3 = sub_909a418(), pBVar2 = gBattleResources, iVar3 == 0))
    {
      iVar3 = 0;
      do {
        if (*(ushort *)(&UNK_0823eac8 + (uint)_UNK_020386ae * 0x28 + (iVar3 + 8) * 2) != 0) {
          pbVar6 = &pBVar2->battleHistory->itemsNo;
          bVar1 = *pbVar6;
          pBVar2->battleHistory->trainerItems[bVar1] =
               *(ushort *)(&UNK_0823eac8 + (uint)_UNK_020386ae * 0x28 + (iVar3 + 8) * 2);
          *pbVar6 = bVar1 + 1;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 != 4);
    }
  }
  BattleAI_SetupAIData(0xf);
  return;
}

// ---- PopulateAIScriptStructWithBaseAttackerData  (ROM 0x90c7a1c)
void PopulateAIScriptStructWithBaseAttackerData(AIScript *data,u8 bankAtk)

{
  byte bVar1;
  u8 uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (uint)bankAtk;
  uVar3 = gBattleMons[uVar4].item;
  data->atkSpecies = gBattleMons[uVar4].species;
  data->atkItem = uVar3;
  bVar1 = GetBankItemEffect(uVar4);
  data->atkItemEffect = bVar1;
  bVar1 = ItemId_GetHoldEffectParam(gBattleMons[uVar4].item);
  data->atkItemQuality = bVar1;
  data->atkStatus1 = gBattleMons[uVar4].status1;
  data->atkStatus2 = gBattleMons[uVar4].status2;
  uVar5 = gBattleMons[uVar4].personality;
  data->atkStatus3 = gStatuses3[uVar4];
  bVar1 = GetGenderFromSpeciesAndPersonality(data->atkSpecies,uVar5);
  data->atkGender = bVar1;
  data->atkAttack = gBattleMons[uVar4].attack;
  data->atkDefense = gBattleMons[uVar4].defense;
  uVar3 = SpeedCalc(uVar4);
  data->atkSpAtk = gBattleMons[uVar4].spAttack;
  data->atkSpDef = gBattleMons[uVar4].spDefense;
  uVar4 = gBattleTypeFlags;
  data->atkSpeed = uVar3;
  uVar2 = bankAtk;
  if ((uVar4 & 1) != 0) {
    uVar2 = bankAtk ^ 2;
  }
  data->bankAtkPartner = uVar2;
  bVar1 = 0;
  if ((uVar4 & 1) != 0) {
    bVar1 = GetBankAbility();
  }
  data->atkPartnerAbility = bVar1;
  bVar1 = ~bankAtk & 1;
  data->foe1 = bVar1;
  if ((gBattleTypeFlags & 1) != 0) {
    bVar1 = bVar1 | 2;
  }
  data->foe2 = bVar1;
  return;
}

// ---- PopulateAIScriptStructWithBaseDefenderData  (ROM 0x90c7ad4)
void PopulateAIScriptStructWithBaseDefenderData(AIScript *data,u8 bankDef)

{
  byte bVar1;
  u8 uVar2;
  bool8 bVar3;
  ushort uVar4;
  u16 uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = (uint)bankDef;
  uVar4 = gBattleMons[uVar6].item;
  data->defSpecies = gBattleMons[uVar6].species;
  data->defItem = uVar4;
  bVar1 = GetBankItemEffect(uVar6);
  data->defItemEffect = bVar1;
  bVar1 = ItemId_GetHoldEffectParam(gBattleMons[uVar6].item);
  data->defItemQuality = bVar1;
  data->defStatus1 = gBattleMons[uVar6].status1;
  data->defStatus2 = gBattleMons[uVar6].status2;
  uVar7 = gBattleMons[uVar6].personality;
  data->defStatus3 = gStatuses3[uVar6];
  bVar1 = GetGenderFromSpeciesAndPersonality(data->defSpecies,uVar7);
  data->defGender = bVar1;
  data->defAttack = gBattleMons[uVar6].attack;
  data->defDefense = gBattleMons[uVar6].defense;
  uVar4 = SpeedCalc(uVar6);
  data->defSpAtk = gBattleMons[uVar6].spAttack;
  data->defSpDef = gBattleMons[uVar6].spDefense;
  uVar6 = gBattleTypeFlags;
  data->defSpeed = uVar4;
  uVar2 = bankDef;
  if ((uVar6 & 1) != 0) {
    uVar2 = bankDef ^ 2;
  }
  data->bankDefPartner = uVar2;
  bVar1 = 0;
  if ((uVar6 & 1) != 0) {
    bVar1 = GetBankAbility();
  }
  data->defPartnerAbility = bVar1;
  data->partnerMove = 0;
  bVar3 = IsBankIncapacitated(data->bankAtkPartner);
  if (bVar3 == 0) {
    uVar5 = GetAIChosenMove(data->bankAtkPartner,bankDef);
    data->partnerMove = uVar5;
  }
  return;
}

// ---- CalculateAIPredictions  (ROM 0x90c7b8c)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void CalculateAIPredictions(void)

{
  u8 uVar1;
  bool8 bVar2;
  u8 uVar3;
  move_t mVar4;
  u16 uVar5;
  undefined4 uVar6;
  int iVar7;
  u8 uVar8;
  int extraout_r1;
  ushort uVar9;
  uint uVar10;
  uint uVar11;
  byte bVar12;
  BattlePokemon *backupBattleMons;
  int iVar13;
  byte bankDef;
  BattlePokemon *pBVar14;
  uint uVar15;
  uint uVar16;
  undefined4 uStack_7c;
  uint uStack_78;
  undefined4 uStack_74;
  AIScript AStack_70;
  
  backupBattleMons = 0x0;
  if (*(byte *)(gNewBS + 0xe9) < 0x80) {
    for (; backupBattleMons < (BattlePokemon *)(uint)gBattlersCount;
        backupBattleMons = (BattlePokemon *)((uint)((int)&backupBattleMons->species + 1U) & 0xff)) {
      uStack_78 = uStack_78 & 0xffffff00;
      uStack_74 = uStack_74 & 0xffff0000;
      if (((((gBattleMons[(int)backupBattleMons].status2 & 0x200000) == 0) &&
           (iVar7 = sub_90a9764(backupBattleMons), iVar7 == 0)) &&
          (iVar7 = sub_90a9534(backupBattleMons), iVar7 != 0)) &&
         (iVar7 = sub_90bd77c(backupBattleMons), uVar16 = gNewBS, iVar7 == 0)) {
        uVar6 = sub_90a9554(backupBattleMons);
        *(undefined4 *)(uVar16 + (int)backupBattleMons[6].nickname * 4 + 4) = uVar6;
        iVar7 = gNewBS + (int)backupBattleMons * 4;
        if (*(int *)(iVar7 + 0x904) == 0) {
          uVar6 = sub_90a9554(backupBattleMons,1);
          *(undefined4 *)(iVar7 + 0x904) = uVar6;
        }
      }
      if ((gBattleTypeFlags & 1) == 0) {
        TryTempMegaEvolveAllBanks(backupBattleMons,&AStack_70.atkSpecies,(u8 *)&uStack_74);
        for (pBVar14 = 0x0; uVar16 = gNewBS,
            pBVar14 < (BattlePokemon *)(uint)gBattlersCount;
            pBVar14 = (BattlePokemon *)((uint)((int)&pBVar14->species + 1) & 0xff)) {
          if ((backupBattleMons != pBVar14) &&
             (pBVar14 != (BattlePokemon *)((uint)backupBattleMons ^ 2))) {
            uVar1 = (u8)backupBattleMons;
            uVar8 = (u8)pBVar14;
            mVar4 = CalcStrongestMove(uVar1,uVar8,0);
            iVar7 = (int)(pBVar14[3].moves + (int)backupBattleMons * 2) * 2;
            *(move_t *)(uVar16 + iVar7 + 6) = mVar4;
            uVar16 = gNewBS;
            bVar2 = MoveKnocksOutXHits(*(u16 *)(gNewBS + iVar7 + 6),uVar1,uVar8,1);
            uVar15 = gNewBS;
            iVar13 = gNewBS + (int)backupBattleMons * 4;
            pBVar14[0x17].nickname[uVar16 + (int)backupBattleMons * 4 + 8] = bVar2;
            bVar2 = 1;
            if (pBVar14[0x17].nickname[iVar13 + 8] == 0) {
              bVar2 = MoveKnocksOutXHits(*(u16 *)(uVar15 + iVar7 + 6),uVar1,uVar8,2);
            }
            pBVar14[0x17].otName[gNewBS + (int)backupBattleMons * 4 + 0xc] = bVar2;
          }
        }
        if ((short)uStack_74 != 0) {
          sub_90c748c(backupBattleMons,&AStack_70,&uStack_74,&uStack_78);
        }
      }
    }
    if ((int)(gBattleTypeFlags << 0x1f) < 0) {
      UpdateBestDoublesKillingMoves();
    }
    uStack_78 = 0;
    uStack_74 = 0;
    Memset(&AStack_70,0,0x48);
    memcpy_(gNewBS->ai.pivotTo[+4],gNewBS + 0x1ee,0x20);
    memset_(gNewBS + 0x1ee,0,0x20,&memset_);
    for (uVar16 = 0; uVar16 < gBattlersCount; uVar16 = uVar16 + 1 & 0xff) {
      if (gBattleMons[uVar16].hp != 0) {
        uStack_7c = CheckMoveLimitations(uVar16,0,0xff);
        uVar1 = (u8)uVar16;
        PopulateAIScriptStructWithBaseAttackerData(&AStack_70,uVar1);
        for (uVar15 = 0; uVar15 < gBattlersCount; uVar15 = uVar15 + 1 & 0xff) {
          if ((uVar16 != uVar15) && (gBattleMons[uVar15].hp != 0)) {
            if (((gBattleMons[uVar16].status2 & 0x400000) == 0) &&
               (-1 < (int)((uint)(byte)gDisableStructs[uVar16].field_0x18 << 0x1f))) {
              bVar2 = IsBankAsleep(uVar1);
              if ((bVar2 != 0) && (bVar2 = MoveEffectInMoveset(0x61 /* EFFECT_SLEEP_TALK */,uVar1), bVar2 == 0)) {
                bVar2 = MoveEffectInMoveset(0x5c /* EFFECT_SNORE */,uVar1);
                uVar9 = 0;
                if (bVar2 == 0) goto LAB_090c7dc0;
              }
              if ((gBattleMons[uVar16].status2 & 0x1000) != 0) {
                iVar7 = MoveInMoveset(gLockedMoves[uVar16],uVar16);
                if (iVar7 != 0) {
                  uVar9 = gLockedMoves[uVar16];
                  goto LAB_090c7dc0;
                }
              }
              uVar10 = gBattleResources->ai->aiFlags;
              gBattleResources->ai->aiFlags = 7;
              uVar8 = (u8)uVar15;
              PopulateAIScriptStructWithBaseDefenderData(&AStack_70,uVar8);
              iVar7 = 0;
              do {
                uVar5 = gBattleMons[uVar16].moves[iVar7];
                if (uVar5 == 0) break;
                *(undefined1 *)((int)&uStack_74 + iVar7) = 0;
                *(undefined1 *)((int)&uStack_78 + iVar7) = 0;
                if ((*(uint *)((iVar7 + 0x2097917) * 4) & uStack_7c) == 0) {
                  uVar5 = TryReplaceMoveWithZMove(uVar1,uVar8,uVar5);
                  uVar3 = AIScript_Negatives(uVar1,uVar8,uVar5,100,&AStack_70);
                  *(u8 *)((int)&uStack_78 + iVar7) = uVar3;
                  uVar3 = AIScript_Positives(uVar1,uVar8,uVar5,uVar3,&AStack_70);
                  *(u8 *)((int)&uStack_78 + iVar7) = uVar3;
                }
                iVar7 = iVar7 + 1;
              } while (iVar7 != 4);
              gBattleResources->ai->aiFlags = uVar10;
              uVar11 = 0;
              uVar10 = 0;
              do {
                if (*(byte *)((int)&uStack_78 + uVar11) < *(byte *)((int)&uStack_78 + uVar10)) {
                  uVar11 = uVar10 & 0xff;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 != 4);
              bVar12 = (char)uVar11 + 1;
              uStack_74 = CONCAT31(uStack_74._1_3_,bVar12);
              uVar10 = 0;
              iVar7 = 0;
              do {
                uVar11 = uVar10 + 1;
                iVar13 = iVar7;
                if ((uVar11 != bVar12) &&
                   (*(char *)((int)&uStack_78 + uVar10) ==
                    *(char *)((int)&uStack_7c + *(byte *)((int)&uStack_74 + iVar7) + 3))) {
                  iVar13 = iVar7 + 1;
                  *(char *)((int)&uStack_74 + iVar7 + 1) = (char)uVar11;
                }
                uVar10 = uVar11;
                iVar7 = iVar13;
              } while (uVar11 != 4);
              uVar11 = 0;
              uVar10 = 0;
              do {
                if (*(byte *)((int)&uStack_78 + uVar11) < *(byte *)((int)&uStack_78 + uVar10)) {
                  uVar11 = uVar10 & 0xff;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 != 4);
              if (*(byte *)((int)&uStack_78 + uVar11) < 100) {
                StoreSwitchPrediction(uVar1,uVar8);
              }
              else {
                uVar6 = Random2();
                sub_900042e(uVar6,iVar13 + 1);
                func_0x090db448(uVar16,uVar15,
                                gBattleMons[uVar16].moves
                                [*(byte *)((int)&uStack_74 + extraout_r1) - 1]);
              }
              memset_(&uStack_78,0,4,&memset_);
            }
            else {
              uVar9 = 0;
LAB_090c7dc0:
              func_0x090db448(uVar16,uVar15,uVar9);
            }
          }
        }
      }
    }
    CalcAIDynamaxMon(0);
    CalcAIDynamaxMon(1);
    for (bVar12 = 0; bVar12 < gBattlersCount; bVar12 = bVar12 + 1) {
      for (bankDef = 0; bankDef < gBattlersCount; bankDef = bankDef + 1) {
        CalcShouldAIDynamax(bVar12,bankDef);
      }
    }
    *(byte *)(gNewBS + 0xe9) = *(byte *)(gNewBS + 0xe9) | 0x80;
    bVar12 = gActiveBattler;
    for (uVar16 = 0; (int)uVar16 < (int)(uint)gBattlersCount; uVar16 = uVar16 + 1) {
      iVar7 = GetBattlerPosition(uVar16 & 0xff);
      if ((((iVar7 != 0) || ((int)(gBattleTypeFlags << 7) < 0)) &&
          ((iVar7 = GetBattlerPosition(uVar16 & 0xff), iVar7 != 2 || (iVar7 = sub_90ad614(), iVar7 != 0)))
          ) && ((*(char *)(gNewBS + uVar16 + 0x884) != '\0' && (gBattleMons[uVar16].hp != 0)))) {
        ResetBestMonToSwitchInto((u8)uVar16);
        *(undefined1 *)(gNewBS + gActiveBattler + 0x884) = 0;
        iVar7 = BankSideHasTwoTrainers();
        if (iVar7 == 0) {
          *(undefined1 *)(gNewBS + (gActiveBattler ^ 2) + 0x884) = 0;
        }
      }
    }
    gActiveBattler = bVar12;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  }
  return;
}

// ---- BattleAI_ChooseMoveOrAction  (ROM 0x90c82c0)
/* WARNING: Restarted to delay deadcode elimination for space: stack */

u8 BattleAI_ChooseMoveOrAction(void)

{
  sbyte sVar1;
  bool8 bVar2;
  u8 uVar3;
  u16 uVar4;
  undefined4 uVar5;
  u8 *puVar6;
  int iVar7;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  u8 *puVar8;
  AI_ThinkingStruct *pAVar9;
  byte bVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  undefined1 auStack_d8 [4];
  u8 *puStack_d4;
  uint uStack_d0;
  undefined *puStack_cc;
  int iStack_c8;
  int iStack_c4;
  undefined1 *puStack_c0;
  uint uStack_bc;
  uint uStack_b8;
  uint uStack_b4;
  uint uStack_b0;
  uint uStack_ac;
  u8 *puStack_a8;
  uint uStack_a4;
  int iStack_a0;
  u8 *puStack_9c;
  u8 *puStack_98;
  u8 *puStack_94;
  u8 *puStack_90;
  uint uStack_8c;
  BattleMove *pBStack_88;
  uint uStack_84;
  u8 auStack_80 [4];
  byte abStack_7c [4];
  byte abStack_78 [4];
  byte abStack_74 [4];
  byte abStack_70 [4];
  uint uStack_6c;
  ushort auStack_68 [4];
  AIScript AStack_60;
  
  uStack_d0 = (uint)gCurrentMove;
  Memset(&AStack_60,0,0x48);
  puStack_c0 = auStack_d8 + -((uint)gBattlersCount * 0x58 + 8);
  iStack_c4 = gNewBS + 0x1e9;
  iStack_c8 = (int)puStack_c0 - ((uint)gBattlersCount * 2 + 8 & 0xfffffff8);
  sub_90c70ec(puStack_c0,iStack_c8,iStack_c4);
  PopulateAIScriptStructWithBaseAttackerData(&AStack_60,UNK_02023d6b);
  uVar11 = 0;
  if (gBattleTypeFlags << 0x1f < 0) {
    do {
      if ((UNK_02023d6b == uVar11) || (gBattleMons[uVar11].hp == 0)) {
        abStack_7c[uVar11] = 0xff;
        auStack_68[uVar11] = 0xffff;
      }
      else {
        BattleAI_SetupAIData(0xf);
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
        gBattlerTarget = (byte)uVar11;
        PopulateAIScriptStructWithBaseDefenderData(&AStack_60,gBattlerTarget);
        pAVar9 = gBattleResources->ai;
        pAVar9->aiLogicId = 0;
        pAVar9->movesetIndex = 0;
        for (uVar14 = pAVar9->aiFlags; pAVar9 = gBattleResources->ai, uVar14 != 0;
            uVar14 = uVar14 >> 1) {
          if ((int)(uVar14 << 0x1f) < 0) {
            pAVar9->aiState = 0;
            BattleAI_DoAIProcessing(&AStack_60);
          }
          pAVar9 = gBattleResources->ai;
          pAVar9->aiLogicId = pAVar9->aiLogicId + 1;
          pAVar9->movesetIndex = 0;
        }
        if ((int)((uint)pAVar9->aiAction << 0x1e) < 0) {
          abStack_7c[uVar11] = 4;
        }
        else if ((pAVar9->aiAction & 4) == 0) {
          abStack_78[0] = pAVar9->score[0];
          abStack_74[0] = 0;
          uVar14 = 1;
          uStack_84 = (uint)UNK_02023d6b * 0x58;
          iVar12 = 1;
          do {
            if (gBattleMons[UNK_02023d6b].moves[iVar12] != 0) {
              bVar10 = pAVar9->score[iVar12];
              if ((uint)abStack_78[0] == (int)(char)bVar10) {
                abStack_78[uVar14] = bVar10;
                abStack_74[uVar14] = (byte)iVar12;
                uVar14 = uVar14 + 1 & 0xff;
              }
              if ((int)(uint)abStack_78[0] < (int)(char)bVar10) {
                uVar14 = 1;
                abStack_78[0] = bVar10;
                abStack_74[0] = (byte)iVar12;
              }
            }
            iVar12 = iVar12 + 1;
          } while (iVar12 != 4);
          uVar5 = Random2();
          sub_900042e(uVar5,uVar14);
          abStack_7c[uVar11] = abStack_74[extraout_r1_00];
          auStack_68[uVar11] = (ushort)abStack_78[0];
          if (((UNK_02023d6b ^ 2) == uVar11) && (abStack_78[0] < 0x65)) {
            auStack_68[uVar11] = 0xffff;
          }
        }
        else {
          abStack_7c[uVar11] = 5;
        }
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 != 4);
    bVar2 = ShouldPrioritizeKOingFoesDoubles(UNK_02023d6b);
    uStack_b0 = (uint)bVar2;
    bVar2 = ShouldPrioritizeMostDamageDoubles(UNK_02023d6b);
    uStack_b8 = (uint)bVar2;
    bVar2 = ShouldPrioritizeDangerousTarget(UNK_02023d6b);
    uStack_b4 = (uint)bVar2;
    iStack_a0 = (int)(short)auStack_68[0];
    abStack_70[0] = 0;
    uVar11 = (uint)abStack_7c[0];
    uStack_a4 = (uint)gBattleMons[UNK_02023d6b].moves[uVar11];
    bVar2 = WontHitTargetWithMove(UNK_02023d6b,0,gBattleMons[UNK_02023d6b].moves[uVar11]);
    if (bVar2 != 0) {
      abStack_70[0] = 1;
      iStack_a0 = (int)(short)auStack_68[1];
      uVar11 = (uint)abStack_7c[1];
      uStack_a4 = (uint)gBattleMons[UNK_02023d6b].moves[uVar11];
    }
    uStack_8c = (uint)abStack_70[0];
    if (uVar11 < 4) {
      if (gBattleMoves[uStack_a4].split == 2) {
        uVar11 = 1;
        puStack_90 = (u8 *)0x0;
        puStack_94 = (u8 *)0x0;
      }
      else {
        iVar7 = GetBattlerSide((uint)abStack_70[0]);
        iVar12 = GetBattlerSide(UNK_02023d6b);
        if (iVar7 == iVar12) goto LAB_090c8824;
        uVar4 = TryReplaceMoveWithZMove(UNK_02023d6b,(u8)uStack_8c,(u16)uStack_a4);
        puStack_90 = (u8 *)0x0;
        uStack_a4 = (uint)uVar4;
        if (uStack_b0 != 0) {
          uVar3 = GetTargetsKnockedOut(uVar4,UNK_02023d6b,(u8)uStack_8c);
          puStack_90 = (u8 *)(uint)uVar3;
        }
        puStack_94 = (u8 *)0x0;
        uVar11 = 0;
        if (((uStack_b8 | uStack_b4) & 0xff) != 0) {
          puStack_94 = (u8 *)GetTotalDamageForTargets((u16)uStack_a4,UNK_02023d6b,(u8)uStack_8c);
          uVar11 = 0;
        }
      }
    }
    else {
LAB_090c8824:
      uVar11 = 0;
      puStack_90 = (u8 *)0x0;
      puStack_94 = (u8 *)0x0;
    }
    uVar14 = 1;
    puStack_98 = (u8 *)0x1;
    pBStack_88 = (BattleMove *)0x1;
    do {
      uStack_84 = (uint)puStack_98 & 0xff;
      puStack_a8 = (u8 *)(uint)puStack_98[(int)abStack_7c];
      puStack_9c = (u8 *)(uint)gBattleMons[0].moves
                               [(int)(puStack_a8 + (uint)UNK_02023d6b * 0x2c + 4 + -4)];
      bVar2 = WontHitTargetWithMove
                        (UNK_02023d6b,(u8)puStack_98,
                         gBattleMons[0].moves
                         [(int)(puStack_a8 + (uint)UNK_02023d6b * 0x2c + 4 + -4)]);
      puVar6 = (u8 *)(uint)bVar2;
      if (puVar6 != (u8 *)0x0) {
        if (pBStack_88 != (BattleMove *)0x0) {
          bVar2 = WontHitTargetWithMove(UNK_02023d6b,abStack_70[0],(u16)uStack_a4);
          puVar6 = (u8 *)(uint)bVar2;
          if (puVar6 != (u8 *)0x0) goto LAB_090c85de;
        }
        goto LAB_090c8846;
      }
LAB_090c85de:
      iVar12 = (int)(short)auStack_68[(int)puStack_98];
      if (iVar12 != iStack_a0) {
        if (iVar12 <= iStack_a0) goto LAB_090c8846;
        if (((-1 < iStack_a0) && (gBattleMoves[(int)puStack_9c].split == 2)) &&
           (puStack_9c != (u8 *)0x29f)) {
          puStack_a8 = &UNK_02023d6b;
          bVar2 = PartnerWillKOTargetBeforeItCanAttack(UNK_02023d6b,(u8)uStack_84);
          puVar6 = (u8 *)(uint)bVar2;
          if (puVar6 != (u8 *)0x0) {
            if (pBStack_88 != (BattleMove *)0x0) {
              bVar2 = HittingTargetWithUselessStatusMove(*puStack_a8,abStack_70[0],abStack_7c);
              puVar6 = (u8 *)(uint)bVar2;
              if (puVar6 != (u8 *)0x0) goto LAB_090c8acc;
            }
            goto LAB_090c8846;
          }
        }
LAB_090c8acc:
        abStack_70[0] = (byte)puStack_98;
        if ((uStack_84 & 2) == 0) {
          puVar6 = (u8 *)((int)puStack_9c * 0xc);
          if (puVar6[0x91521da] == 2) {
            iStack_a0 = iVar12;
            uVar11 = 1;
            pBStack_88 = (BattleMove *)(uStack_84 & 2);
          }
          else {
            if (uStack_b0 != 0) {
              uVar3 = GetTargetsKnockedOut((u16)puStack_9c,UNK_02023d6b,(u8)uStack_84);
              puVar6 = (u8 *)(uint)uVar3;
              puStack_90 = puVar6;
            }
            pBStack_88 = (BattleMove *)((uStack_b8 | uStack_b4) & 0xff);
            if (pBStack_88 == (BattleMove *)0x0) {
              uStack_8c = uStack_84;
              iStack_a0 = iVar12;
              uVar11 = 0;
            }
            else {
              puVar6 = (u8 *)GetTotalDamageForTargets((u16)puStack_9c,UNK_02023d6b,(u8)uStack_84);
              puStack_94 = puVar6;
              uStack_8c = uStack_84;
              iStack_a0 = iVar12;
LAB_090c8960:
              uVar11 = 0;
              pBStack_88 = (BattleMove *)0x0;
              uStack_8c = uStack_84;
            }
          }
        }
        else {
          iStack_a0 = iVar12;
          pBStack_88 = (BattleMove *)0x0;
        }
        uVar14 = 1;
        goto LAB_090c8846;
      }
      uStack_bc = (uint)gBattleMoves[(int)puStack_9c].split;
      uStack_ac = 1;
      if ((uVar11 == 0) && (uStack_ac = uVar11, puStack_a8 < &UndefinedInstruction)) {
        uStack_ac = (uint)(uStack_bc == 2);
      }
      uVar11 = uStack_ac;
      puStack_cc = &GetBattlerSide;
      puStack_d4 = (u8 *)GetBattlerSide(uStack_84);
      puVar6 = (u8 *)GetBattlerSide(UNK_02023d6b);
      if ((puStack_d4 == puVar6) || ((u8 *)0x3 < puStack_a8)) {
        if (uStack_bc == 2) {
LAB_090c8a6a:
          if (puStack_9c != (u8 *)0x29f) {
            bVar2 = PartnerWillKOTargetBeforeItCanAttack(UNK_02023d6b,(u8)uStack_84);
            puVar6 = (u8 *)(uint)bVar2;
            if (puVar6 != (u8 *)0x0) {
              if (pBStack_88 != (BattleMove *)0x0) {
                bVar2 = HittingTargetWithUselessStatusMove(UNK_02023d6b,abStack_70[0],abStack_7c);
                puVar6 = (u8 *)(uint)bVar2;
                if (puVar6 != (u8 *)0x0) goto LAB_090c86b0;
              }
              goto LAB_090c8846;
            }
          }
        }
        goto LAB_090c86b0;
      }
      if (uStack_bc == 2) goto LAB_090c8a6a;
      uVar4 = TryReplaceMoveWithZMove(UNK_02023d6b,(u8)uStack_84,(u16)puStack_9c);
      puVar6 = (u8 *)(uint)uVar4;
      puStack_9c = (u8 *)0x0;
      puStack_a8 = puVar6;
      if (uStack_b0 != 0) {
        uVar3 = GetTargetsKnockedOut(uVar4,UNK_02023d6b,(u8)uStack_84);
        puVar6 = (u8 *)(uint)uVar3;
        puStack_9c = puVar6;
      }
      puVar8 = (u8 *)((uStack_b8 | uStack_b4) & 0xff);
      if (puVar8 == (u8 *)0x0) {
        if (uStack_b0 == 0) goto LAB_090c86b0;
        puStack_a8 = puVar8;
LAB_090c8690:
        if (puStack_9c < puStack_90) goto LAB_090c8846;
        if (puStack_9c == puStack_90) {
          if (puStack_9c == (u8 *)0x0) goto LAB_090c896e;
          if (uStack_b4 == 0) goto LAB_090c86b0;
          goto LAB_090c8980;
        }
        goto LAB_090c8942;
      }
      puVar6 = (u8 *)GetTotalDamageForTargets((u16)puStack_a8,UNK_02023d6b,(u8)uStack_84);
      puStack_a8 = puVar6;
      if (uStack_b0 != 0) goto LAB_090c8690;
LAB_090c896e:
      if (((uStack_b4 == 0) || (puStack_a8 < (u8 *)0x32)) || (puStack_94 < (u8 *)0x32)) {
LAB_090c89ae:
        if (uStack_b8 == 0) {
LAB_090c86b0:
          abStack_70[uVar14] = (byte)puStack_98;
          uVar14 = uVar14 + 1 & 0xff;
          goto LAB_090c86c6;
        }
        if (puStack_94 <= puStack_a8) {
          if (puStack_a8 != puStack_94) goto LAB_090c8942;
          goto LAB_090c86b0;
        }
      }
      else {
LAB_090c8980:
        bVar2 = CanKnockOut((u8)uStack_84,UNK_02023d6b);
        uStack_bc = (uint)bVar2;
        bVar2 = CanKnockOut((u8)uStack_8c,UNK_02023d6b);
        puVar6 = (u8 *)(uint)bVar2;
        if (-1 < (int)(gBattleResources->ai->aiFlags << 0x1d)) goto LAB_090c86b0;
        if (uStack_bc == 0) {
          if (puVar6 == (u8 *)0x0) goto LAB_090c89ae;
          goto LAB_090c8846;
        }
        if (puVar6 != (u8 *)0x0) {
          iVar12 = sub_90a985c(uStack_84);
          uVar13 = 1;
          if (iVar12 == 0) {
            iVar12 = IsDynamaxed(uStack_84);
            uVar13 = (uint)(iVar12 != 0);
          }
          uStack_bc = uVar13;
          puVar6 = (u8 *)sub_90a985c(uStack_8c);
          iVar12 = 1;
          if (puVar6 == (u8 *)0x0) {
            iVar12 = IsDynamaxed(uStack_8c);
            puVar6 = (u8 *)(iVar12 + -1);
            iVar12 = (iVar12 - (int)puVar6) - (uint)(iVar12 == 0);
          }
          if (uVar13 == 0) {
            if (iVar12 != 0) goto LAB_090c8846;
          }
          else if (iVar12 != 0) goto LAB_090c86b0;
          if (uStack_bc == 0) goto LAB_090c86b0;
        }
LAB_090c8942:
        if (uStack_ac == 0) {
          abStack_70[0] = (byte)puStack_98;
          puStack_90 = puStack_9c;
          puStack_94 = puStack_a8;
          uStack_8c = uStack_84;
          goto LAB_090c8960;
        }
        uStack_6c = 0;
        puStack_98[(int)&uStack_6c] = 1;
        puVar6 = puStack_98;
        for (uVar11 = 0; uVar11 < uVar14; uVar11 = uVar11 + 1) {
          if (abStack_7c[abStack_70[uVar11]] < 4) {
            pBStack_88 = gBattleMoves;
            puVar6 = &PrefetchAbort;
            if (gBattleMoves[gBattleMons[UNK_02023d6b].moves[abStack_7c[abStack_70[uVar11]]]].split
                == 2) goto LAB_090c8a52;
          }
          else {
LAB_090c8a52:
            abStack_70[abStack_70[uVar11] + 4] = 1;
          }
        }
        uVar14 = 0;
        iVar12 = 0;
        do {
          if (abStack_70[iVar12 + 4] != 0) {
            puVar6 = auStack_80;
            abStack_70[uVar14] = (byte)iVar12;
            uVar14 = uVar14 + 1 & 0xff;
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 != 4);
        puStack_90 = puStack_9c;
        puStack_94 = puStack_a8;
        uVar11 = 1;
        uStack_8c = uStack_84;
LAB_090c86c6:
        pBStack_88 = (BattleMove *)0x0;
      }
LAB_090c8846:
      puStack_98 = puStack_98 + 1;
    } while (puStack_98 != &UndefinedInstruction);
    uVar5 = Random2(puVar6);
    sub_900042e(uVar5,uVar14);
    gBattlerTarget = abStack_70[extraout_r1_01];
    uVar11 = (uint)UNK_02023d6b;
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
    if ((((uint)gBattlerTarget == (uVar11 ^ 2)) && (iStack_a0 < 0)) &&
       (gBattlerTarget = (byte)(~uVar11 & 1), gBattleMons[~uVar11 & 1].hp == 0)) {
      gBattlerTarget = gBattlerTarget ^ 2;
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
    }
    uVar14 = (uint)gBattlerTarget;
    bVar10 = abStack_7c[uVar14];
    if (((gBattleMons[AStack_60.foe1].hp != 0) && (gBattleMons[AStack_60.foe2].hp != 0)) ||
       ((gBattleMons[AStack_60.bankAtkPartner].hp != 0 || (3 < bVar10)))) goto LAB_090c8364;
  }
  else {
    uVar11 = gBattleResources->ai->aiFlags;
    sub_80c7164();
    PopulateAIScriptStructWithBaseDefenderData(&AStack_60,gBattlerTarget);
    for (; pAVar9 = gBattleResources->ai, uVar11 != 0; uVar11 = uVar11 >> 1) {
      if ((int)(uVar11 << 0x1f) < 0) {
        pAVar9->aiState = 0;
        BattleAI_DoAIProcessing(&AStack_60);
      }
      pAVar9 = gBattleResources->ai;
      pAVar9->aiLogicId = pAVar9->aiLogicId + 1;
      pAVar9->movesetIndex = 0;
    }
    if ((int)((uint)pAVar9->aiAction << 0x1e) < 0) {
      bVar10 = 4;
      goto LAB_090c8364;
    }
    if ((pAVar9->aiAction & 4) != 0) {
      bVar10 = 5;
      goto LAB_090c8364;
    }
    uStack_6c = CONCAT31(uStack_6c._1_3_,pAVar9->score[0]);
    auStack_68[0] = auStack_68[0] & 0xff00;
    uVar11 = 1;
    uStack_84 = (uint)UNK_02023d6b * 0x58;
    iVar12 = 1;
    do {
      if (gBattleMons[UNK_02023d6b].moves[iVar12] != 0) {
        sVar1 = pAVar9->score[iVar12];
        if ((uStack_6c & 0xff) == (int)sVar1) {
          abStack_70[uVar11 + 4] = (byte)uStack_6c;
          *(char *)((int)auStack_68 + uVar11) = (char)iVar12;
          uVar11 = uVar11 + 1 & 0xff;
        }
        else if ((int)(uStack_6c & 0xff) < (int)sVar1) {
          uStack_6c = CONCAT31(uStack_6c._1_3_,sVar1);
          auStack_68[0] = CONCAT11(auStack_68[0]._1_1_,(char)iVar12);
          uVar11 = 1;
        }
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 != 4);
    uVar5 = Random2();
    sub_900042e(uVar5,uVar11);
    bVar10 = *(byte *)((int)auStack_68 + extraout_r1);
    uVar11 = (uint)UNK_02023d6b;
    if (3 < bVar10) goto LAB_090c8364;
    uVar14 = ~uVar11 & 1;
  }
  sub_90c75b8(uVar11,uVar14,bVar10,&AStack_60);
LAB_090c8364:
  sub_90c74d0(puStack_c0,iStack_c8,iStack_c4);
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
  gCurrentMove = (undefined2)uStack_d0;
  return bVar10;
}

// ---- ClearCachedAIData  (ROM 0x90c8ba4)
void ClearCachedAIData(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined2 *puVar8;
  int iStack_34;
  undefined2 *puStack_30;
  undefined1 *puStack_2c;
  int iStack_28;
  
  uVar1 = gNewBS;
  uVar4 = (uint)gBattlersCount;
  puStack_30 = (undefined2 *)(gNewBS->ai.backupAbilities[+1]);
  puVar6 = (undefined4 *)(gNewBS->ai.bestDoublesKillingMoves[+28]);
  for (uVar2 = 0; uVar2 < uVar4; uVar2 = uVar2 + 1) {
    iVar5 = uVar1 + uVar2;
    *(undefined1 *)(iVar5 + 0x884) = 0;
    *(undefined1 *)(iVar5 + 0x9d) = 0;
    *(undefined1 *)(iVar5 + 0x888) = 0xff;
    puVar6[0x3d] = 0;
    *puVar6 = 0xffffffff;
    puStack_2c = (undefined1 *)(uVar1 + 0x26e + uVar2 * 0x10);
    iStack_28 = uVar2 * 0x40 + uVar1;
    puVar3 = puVar6 + 4;
    puVar8 = puStack_30;
    do {
      *puVar8 = 0xffff;
      puVar8[0x10] = 0xffff;
      *(undefined1 *)puVar3 = 0xff;
      *(undefined1 *)(puVar3 + 4) = 0xff;
      *(undefined1 *)(puVar3 + 0x1c) = 0xff;
      *(undefined1 *)(puVar3 + 0x21) = 0;
      *(undefined1 *)(puVar3 + 0x35) = 0;
      iStack_34 = 0;
      puVar7 = puStack_2c;
      iVar5 = iStack_34;
      do {
        iStack_34 = iVar5;
        *(undefined4 *)(iStack_28 + iStack_34 * 4 + 0x2f0) = 0xffffffff;
        *puVar7 = 0xff;
        puVar7[0x40] = 0xff;
        puVar7[0x646] = 0xff;
        puVar7 = puVar7 + 1;
        iVar5 = iStack_34 + 1;
      } while (iStack_34 + 1 != 4);
      puVar8 = (undefined2 *)((int)puVar8 + iStack_34 + -1);
      puStack_2c = puStack_2c + 4;
      iStack_28 = iStack_28 + 0x10;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    } while (puVar8 != puStack_30 + uVar4);
    puStack_30 = puStack_30 + 4;
    puVar6 = puVar6 + 1;
  }
  return;
}

// ---- PickRaidBossRepeatedMove  (ROM 0x90c8ca4)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void PickRaidBossRepeatedMove(u8 moveLimitations)

{
  ushort move;
  u8 uVar1;
  u8 uVar2;
  u8 bankDef;
  u8 movePos;
  bool8 bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int in_r1;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = (uint)moveLimitations;
  if ((gBattleResources->ai->aiFlags & 4) == 0) {
    return;
  }
  iVar5 = IsPlayerInControl();
  if (iVar5 == 0) {
    return;
  }
  if ((gBattleTypeFlags & 0x6000100) != 0) {
    return;
  }
  uVar9 = (uint)*(byte *)(gNewBS + in_r1 + 0x1d5);
  bVar11 = false;
  if (8 < uVar9) {
    if (uVar9 - 9 < 3) {
      uVar6 = Random();
      uVar8 = 4;
    }
    else if (uVar9 - 0xc < 4) {
      uVar6 = Random(0);
      uVar8 = 3;
    }
    else {
      uVar6 = sub_2023be4();
      uVar8 = 2;
    }
    iVar5 = umodsi(uVar6,uVar8);
    bVar11 = iVar5 == 0;
  }
  uVar2 = gBattlerTarget;
  uVar1 = UNK_02023d6b;
  if (gChosenActionByBank[in_r1] != 2) {
    return;
  }
  if ((gStatuses3[in_r1] & 0x1800) != 0) {
    return;
  }
  if ((!bVar11) && ((ushort)*(byte *)(gNewBS + in_r1 + 0x1dd) != gBattlerPartyIndexes[in_r1])) {
    return;
  }
  gActiveBattler = moveLimitations;
  UNK_02023d6b = moveLimitations;
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  ClearCachedAIData();
  memset_(gNewBS + 0x1ee,0,0x20);
  if ((int)(gBattleTypeFlags << 0x1f) < 0) {
    UpdateBestDoublesKillingMoves();
  }
  BattleAI_SetupAIData(0xf);
  movePos = BattleAI_ChooseMoveOrAction();
  if (3 < movePos) {
    UNK_02023d6b = uVar1;
    gBattlerTarget = uVar2;
    return;
  }
  move = gBattleMons[uVar4].moves[movePos];
  uVar10 = move;
  uVar9 = GetBaseMoveTarget(uVar10,uVar4);
  if (gBattleMoves[uVar10].effect == 0x80 /* EFFECT_PURSUIT */) {
    UNK_02023d6b = uVar1;
    gBattlerTarget = uVar2;
    return;
  }
  gBattleStruct->chosenMovePositions[uVar4] = movePos;
  gChosenMovesByBanks[uVar4] = move;
  if (-1 < (int)(uVar9 << 0x1b)) {
    if ((uVar9 & 2) == 0) {
      if ((int)(uVar9 << 0x1c) < 0) {
        iVar5 = GetBattlerSide(uVar4,uVar10,uVar4 * 2,&GetBattlerSide);
        if (iVar5 == 0) {
          iVar5 = GetBattlerAtPosition(1);
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
          gBattlerTarget = (u8)iVar5;
          uVar6 = 3;
          if ((*(uint *)(&gBitTable + iVar5 * 4) & (uint)gAbsentBattlerFlags) == 0)
          goto LAB_090c8dba;
        }
        else {
          iVar5 = GetBattlerAtPosition(0);
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
          gBattlerTarget = (u8)iVar5;
          if ((*(uint *)(&gBitTable + iVar5 * 4) & (uint)gAbsentBattlerFlags) == 0)
          goto LAB_090c8dba;
          uVar6 = 2;
        }
        gBattlerTarget = GetBattlerAtPosition(uVar6);
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
      }
      goto LAB_090c8dba;
    }
    iVar7 = GetBattlerSide(gBattlerTarget);
    iVar5 = GetBattlerSide(uVar4);
    if (iVar7 == iVar5) goto LAB_090c8dba;
  }
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
  gBattlerTarget = moveLimitations;
LAB_090c8dba:
  bankDef = gBattlerTarget;
  gBattleStruct->moveTarget[uVar4] = gBattlerTarget;
  uVar4 = gNewBS;
  uVar9 = (uint)gActiveBattler;
  bVar3 = ShouldAIUseZMoveByMoveAndMovePos(moveLimitations,bankDef,move,movePos);
  *(bool8 *)(uVar4 + uVar9 + 400) = bVar3;
  gBattlerTarget = uVar2;
  UNK_02023d6b = uVar1;
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return;
}

// ---- RechooseAIMoveAfterSwitchIfNecessary  (ROM 0x90c8f04)
void RechooseAIMoveAfterSwitchIfNecessary(void)

{
  GetBattlerSide(UNK_0203e033);
  return;
}
