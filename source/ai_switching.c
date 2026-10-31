// ai_switching.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- PredictedMoveWontKOMon  (ROM 0x90d6d08)
bool8 PredictedMoveWontKOMon(u8 activeBattler,Pokemon *mon,u8 foe)

{
  ushort uVar1;
  move_t mVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  
  mVar2 = IsValidMovePrediction(foe,activeBattler);
  uVar6 = (uint)mVar2;
  bVar7 = true;
  if (uVar6 != 0) {
    if ((gBattleMoves[uVar6].split != 2) && (gBattleMoves[uVar6].effect != 0xed /* EFFECT_SUCKER_PUNCH */)) {
      iVar3 = GetMonAbility(mon);
      uVar1 = mon->species;
      uVar4 = CalcMoveSplit(foe,uVar6);
      iVar5 = IsAffectedByDisguse(iVar3,uVar1,uVar4);
      if (iVar5 == 0) {
        iVar3 = sub_9086b40(foe,activeBattler,uVar6,mon,0);
        uVar4 = GetBattlerSide(activeBattler);
        iVar5 = GetMonEntryHazardDamage(mon,uVar4);
        uVar6 = iVar3 + iVar5;
      }
      else {
        uVar6 = 0;
        if (iVar3 == 0x9f) {
          uVar6 = (uint)(mon->maxHP >> 3);
        }
      }
      bVar7 = uVar6 < mon->hp;
    }
  }
  return bVar7;
}

// ---- PassOnWishSwitchingCheck  (ROM 0x90d6da8)
bool8 PassOnWishSwitchingCheck(Pokemon *party,u8 monId)

{
  BattleStruct *pBVar1;
  bool8 bVar2;
  int iVar3;
  undefined4 uVar4;
  Pokemon *mon;
  
  mon = party + monId;
  if (mon->hp < mon->maxHP >> 1) {
    uVar4 = GetBattlerSide(gActiveBattler);
    iVar3 = sub_90c0cf4(mon,uVar4);
    if ((iVar3 == 0) &&
       (((gBattleTypeFlags & 1) != 0 ||
        (bVar2 = PredictedMoveWontKOMon(gActiveBattler,mon,~gActiveBattler & 1), bVar2 != 0)))) {
      pBVar1 = gBattleStruct;
      iVar3 = GetBattlerSide(gActiveBattler);
      pBVar1->switchoutIndex[iVar3] = monId;
      EmitTwoReturnValues(1,2,0);
      return 1;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
  return 0;
}

// ---- TheCalcForSemiInvulnerableTroll  (ROM 0x90d6e30)
bool8 TheCalcForSemiInvulnerableTroll(u8 bankAtk,u8 flags,bool8 checkLockedMoves)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  uint uVar6;
  uint uStack_2c;
  byte bStack_1a;
  byte abStack_19 [5];
  
  uVar2 = (uint)bankAtk;
  uVar6 = (uint)gActiveBattler;
  uStack_2c = uVar6;
  if ((gBattleTypeFlags << 0x1f < 0) &&
     (uStack_2c = uVar6 ^ 2,
     (*(uint *)(&gBitTable + (uVar6 ^ 2) * 4) & (uint)gAbsentBattlerFlags) != 0)) {
    uStack_2c = uVar6;
  }
  iVar3 = LoadPartyRange(uVar6,&bStack_1a,abStack_19);
  if ((((gStatuses3[uVar2] & 0x130400c0) != 0) ||
      ((checkLockedMoves != 0 && (gLockedMoves[uVar2] != 0)))) &&
     ((gActiveBattler == gBattleStruct->moveTarget[uVar2] &&
      ((bVar1 = AI_SpecialTypeCalc(gLockedMoves[uVar2],uVar2), gBattleMons[gActiveBattler].hp == 0
       || ((flags & bVar1) == 0)))))) {
    uVar4 = (uint)bStack_1a;
    psVar5 = (short *)(iVar3 + uVar4 * 100 + 0x20);
    for (; (int)uVar4 < (int)(uint)abStack_19[0]; uVar4 = uVar4 + 1) {
      if (((((psVar5[0x1b] != 0) && (*psVar5 != 0)) &&
           (iVar3 = GetMonData(psVar5 + -0x10,0x2d,0), iVar3 == 0)) &&
          ((gBattlerPartyIndexes[uVar6] != uVar4 && (gBattlerPartyIndexes[uStack_2c] != uVar4)))) &&
         ((gBattleStruct->monToSwitchIntoId[uVar6] != uVar4 &&
          ((gBattleStruct->monToSwitchIntoId[uStack_2c] != uVar4 &&
           (bVar1 = AI_TypeCalc(gLockedMoves[uVar2],uVar2,gActiveBattler,psVar5 + -0x10),
           (flags & bVar1) != 0)))))) {
        return (bool8)uVar4;
      }
      psVar5 = psVar5 + 0x32;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
  return 6;
}

// ---- RunAllSemiInvulnerableLockedMoveCalcs.isra.0  (ROM 0x90d6f7c)
longlong RunAllSemiInvulnerableLockedMoveCalcs_isra_0
                   (uint param_1,undefined4 param_2,undefined4 param_3)

{
  BattleStruct *pBVar1;
  u8 bankAtk;
  bool8 bVar2;
  int iVar3;
  bool8 checkLockedMoves;
  
  bankAtk = (u8)param_1;
  checkLockedMoves = (bool8)param_3;
  bVar2 = TheCalcForSemiInvulnerableTroll(bankAtk,8,checkLockedMoves);
  if (((bVar2 != 6) ||
      (((gBattleTypeFlags << 0x1f < 0 &&
        (bVar2 = TheCalcForSemiInvulnerableTroll((u8)param_2,8,checkLockedMoves), bVar2 != 6)) ||
       (bVar2 = TheCalcForSemiInvulnerableTroll(bankAtk,4,checkLockedMoves), bVar2 != 6)))) ||
     ((gBattleTypeFlags << 0x1f < 0 &&
      (bVar2 = TheCalcForSemiInvulnerableTroll((u8)param_2,4,checkLockedMoves), bVar2 != 6)))) {
    pBVar1 = gBattleStruct;
    iVar3 = GetBattlerSide(gActiveBattler);
    pBVar1->switchoutIndex[iVar3] = bVar2;
    EmitTwoReturnValues(1,2,0,&EmitTwoReturnValues,param_1,param_2,param_3);
  }
  return (ulonglong)param_1 << 0x20;
}

// ---- LoadBattlersAndFoes  (ROM 0x90d70ac)
void LoadBattlersAndFoes(u8 *battlerIn1,u8 *battlerIn2,u8 *foe1,u8 *foe2)

{
  byte bVar1;
  u8 uVar2;
  uint uVar3;
  
  uVar3 = gBattleTypeFlags;
  *battlerIn1 = gActiveBattler;
  if ((uVar3 & 1) == 0) {
    *battlerIn2 = gActiveBattler;
    bVar1 = ~gActiveBattler;
    *foe1 = bVar1 & 1;
    *foe2 = bVar1 & 1;
  }
  else {
    if ((*(uint *)(&gBitTable + (gActiveBattler ^ 2) * 4) & (uint)gAbsentBattlerFlags) == 0) {
      *battlerIn2 = (u8)(gActiveBattler ^ 2);
    }
    else {
      *battlerIn2 = gActiveBattler;
    }
    uVar3 = ~(uint)gActiveBattler & 1;
    if ((*(uint *)(&gBitTable + uVar3 * 4) & (uint)gAbsentBattlerFlags) == 0) {
      uVar2 = (u8)uVar3;
      if ((*(uint *)(&gBitTable + (uVar3 | 2) * 4) & (uint)gAbsentBattlerFlags) == 0) {
        *foe1 = uVar2;
        *foe2 = ((gActiveBattler & 1) == 0) + 2;
      }
      else {
        *foe2 = uVar2;
        *foe1 = uVar2;
      }
    }
    else {
      uVar2 = ((gActiveBattler & 1) == 0) + 2;
      *foe2 = uVar2;
      *foe1 = uVar2;
    }
  }
  return;
}

// ---- ResetBestMonToSwitchInto  (ROM 0x90d714c)
void ResetBestMonToSwitchInto(u8 bank)

{
  int iVar1;
  
  sub_90d7008();
  iVar1 = BankSideHasTwoTrainers(bank);
  if (iVar1 == 0) {
    sub_90d7008(bank ^ 2);
  }
  return;
}

// ---- CalcMostSuitableMonToSwitchInto  (ROM 0x90d7168)
u8 CalcMostSuitableMonToSwitchInto(void)

{
  bool bVar1;
  bool bVar2;
  u8 foe;
  u8 uVar3;
  bool8 bVar4;
  u16 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  s32 sVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  byte bVar16;
  uint extraout_r1;
  uint extraout_r1_00;
  undefined4 extraout_r1_01;
  short sVar17;
  byte bVar18;
  ushort uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  byte *pbVar23;
  int iVar24;
  uint uVar25;
  int iVar26;
  char cVar27;
  bool bVar28;
  bool bVar29;
  undefined8 uVar30;
  uint uStack_178;
  ushort *puStack_174;
  Pokemon *pPStack_170;
  uint uStack_16c;
  uint uStack_168;
  uint uStack_15c;
  uint uStack_158;
  uint uStack_154;
  uint uStack_14c;
  char *pcStack_148;
  uint uStack_140;
  byte bStack_10a;
  byte bStack_109;
  u8 uStack_108;
  u8 uStack_107;
  byte bStack_106;
  byte bStack_105;
  u8 auStack_104 [4];
  char acStack_100 [4];
  byte abStack_fc [8];
  char acStack_f4 [8];
  char acStack_ec [6];
  char acStack_e6 [2];
  u16 auStack_e4 [4];
  ushort auStack_dc [6];
  u8 uStack_d0;
  byte bStack_cf;
  Pokemon *pPStack_cc;
  u8 uStack_7e;
  char cStack_7c;
  undefined2 uStack_76;
  undefined2 uStack_74;
  undefined1 auStack_72 [6];
  Pokemon *pPStack_6c;
  undefined2 uStack_66;
  undefined1 uStack_64;
  char cStack_63;
  undefined2 uStack_58;
  ushort uStack_54;
  undefined1 uStack_25;
  
  Memset(auStack_dc,0,0xc);
  Memset(abStack_fc,0,6);
  Memset(acStack_f4,0,6);
  Memset(acStack_ec,0,6);
  uStack_178 = (uint)gBattleStruct->monToSwitchIntoId[gActiveBattler];
  if (uStack_178 == 6) {
    LoadBattlersAndFoes(&bStack_10a,&bStack_109,&uStack_108,&uStack_107);
    iVar6 = LoadPartyRange(gActiveBattler,&bStack_106,&bStack_105);
    cVar27 = '\0';
    uVar25 = (uint)bStack_106;
    iVar24 = iVar6 + uVar25 * 100;
    for (; uVar25 < bStack_105; uVar25 = uVar25 + 1) {
      if (((((*(short *)(iVar24 + 0x20) != 0) &&
            (iVar26 = GetMonData(iVar24,0x2d,0,&GetMonData), iVar26 == 0)) &&
           (*(short *)(iVar24 + 0x56) != 0)) &&
          ((gBattlerPartyIndexes[bStack_10a] != uVar25 &&
           (gBattlerPartyIndexes[bStack_109] != uVar25)))) &&
         ((gBattleStruct->monToSwitchIntoId[bStack_10a] != uVar25 &&
          (gBattleStruct->monToSwitchIntoId[bStack_109] != uVar25)))) {
        cVar27 = cVar27 + '\x01';
      }
      iVar24 = iVar24 + 100;
    }
    if (cVar27 == '\0') {
      ResetBestMonToSwitchInto(gActiveBattler);
    }
    else {
      uVar25 = (uint)bStack_106;
      iVar24 = 0;
      pPStack_170 = (Pokemon *)(iVar6 + uVar25 * 100);
      puStack_174 = auStack_dc + uVar25;
      uStack_16c = 6;
      uStack_168 = 6;
      uStack_15c = uStack_178;
      while( true ) {
        uVar20 = uVar25 + iVar24;
        if (bStack_105 <= uVar20) break;
        if (((((pPStack_170->species != 0) && (pPStack_170->hp != 0)) &&
             ((iVar6 = GetMonData(pPStack_170,0x2d,0,&GetMonData), foe = uStack_108, iVar6 == 0
              && ((((pPStack_170->condition & 7) == 0 || (pPStack_170->condition == 1)) &&
                  (gBattlerPartyIndexes[bStack_10a] != uVar20)))))) &&
            ((gBattlerPartyIndexes[bStack_109] != uVar20 &&
             (gBattleStruct->monToSwitchIntoId[bStack_10a] != uVar20)))) &&
           (gBattleStruct->monToSwitchIntoId[bStack_109] != uVar20)) {
          auStack_104[1] = uStack_107;
          auStack_104[0] = uStack_108;
          uVar15 = CheckMoveLimitationsFromParty(pPStack_170,0,0xff);
          uVar3 = GetMonAbilityAfterTrace(pPStack_170,foe);
          uVar3 = TryReplaceImposterAbility(uVar3,gActiveBattler);
          uVar7 = GetBattlerSide(gActiveBattler);
          uVar8 = sub_9071268(uVar7,pPStack_170);
          bVar28 = true;
          if ((gBattleTypeFlags & 1) != 0) {
            iVar6 = ViableMonCountFromBank(foe);
            bVar28 = iVar6 == 1;
          }
          uVar21 = uVar25 + iVar24 & 0xff;
          iVar6 = FlagGet(0x1042);
          if (iVar6 != 0) {
            uStack_16c._0_1_ = (byte)uStack_15c;
            uStack_15c = uVar21;
            break;
          }
          uVar30 = sub_90c1df8(pPStack_170,3);
          uVar7 = (undefined4)((ulonglong)uVar30 >> 0x20);
          bVar29 = false;
          if ((int)uVar30 != 0) {
            uVar30 = sub_90751c8(pPStack_170);
            uVar7 = (undefined4)((ulonglong)uVar30 >> 0x20);
            bVar29 = (int)uVar30 != 0;
          }
          acStack_f4[iVar24 + uVar25] = bVar29;
          uVar7 = GetBattlerSide(gActiveBattler,uVar7,uVar25,&GetBattlerSide);
          iVar6 = sub_90c0cf4(pPStack_170,uVar7);
          if (iVar6 == 0) {
            Memset(&uStack_d0,0,0x5c);
            uStack_d0 = gActiveBattler;
            pPStack_cc = pPStack_170;
            PopulateDamageCalcStructWithBaseAttackerData(&uStack_d0);
            sVar9 = GetMonPassiveRecovery(pPStack_170,gActiveBattler);
            iVar6 = sub_90743e8(gActiveBattler,0);
            for (uStack_14c = 0; uStack_14c < gBattlersCount >> 1; uStack_14c = uStack_14c + 1) {
              bVar16 = auStack_104[uStack_14c];
              uVar22 = (uint)bVar16;
              if ((gBattleMons[uVar22].hp != 0) && ((uStack_14c == 0 || (auStack_104[0] != uVar22)))
                 ) {
                bStack_cf = bVar16;
                PopulateDamageCalcStructWithBaseDefenderData();
                uVar10 = SpeedCalc(uVar22);
                if (uVar10 <= uVar8) {
                  *puStack_174 = *puStack_174 + 0xe;
                  abStack_fc[iVar24 + (uVar25 - 0xfc) + 0xfc] =
                       abStack_fc[iVar24 + (uVar25 - 0xfc) + 0xfc] | 0x40;
                }
                bVar4 = CanKnockOutFromParty(pPStack_170,bVar16,&uStack_d0);
                iVar26 = 0;
                if (bVar4 == 0) {
                  bVar29 = false;
                  do {
                    if ((*(uint *)((iVar26 + 0x2097917) * 4) & uVar15) == 0) {
                      if (cStack_7c == '\0') {
                        uVar10 = GetMonData(pPStack_170,iVar26 + 0xd,0,&GetMonData);
                        uVar10 = uVar10 & 0xffff;
                      }
                      else {
                        uVar5 = GetBattleMonMove(uStack_7e,(u8)iVar26);
                        uVar10 = (uint)uVar5;
                      }
                      if ((gBattleMoves[uVar10].effect == 0x81 /* EFFECT_RAPID_SPIN */) &&
                         (iVar13 = GetBattlerSide(gActiveBattler,0xc,uVar10 * 0xc,&GetBattlerSide),
                         (int)((uint)gSideStatuses[iVar13] << 0x1b) < 0)) {
                        if ((gBattleTypeFlags & 1) == 0) {
                          uVar14 = ViableMonCountFromBank(gActiveBattler);
                          acStack_ec[iVar24 + uVar25] = 1 < uVar14;
                        }
                        else {
                          uVar14 = ViableMonCountFromBank(gActiveBattler);
                          acStack_ec[iVar24 + uVar25] = 2 < uVar14;
                        }
                      }
                      uVar14 = gNewBS;
                      if (((uVar10 != 0) && (gBattleMoves[uVar10].split != 2)) &&
                         (iVar13 = GetBattlerSide(gActiveBattler),
                         (uint)(gBattleMons[uVar22].hp >> 1) <=
                         *(uint *)(uVar14 + ((iVar13 * 6 + uVar20) * 4 + uVar22 + 0x1ba) * 4 + 8)))
                      {
                        *puStack_174 = *puStack_174 + 2;
                        abStack_fc[iVar24 + (uVar25 - 0xfc) + 0xfc] =
                             abStack_fc[iVar24 + (uVar25 - 0xfc) + 0xfc] | 0x10;
                        goto LAB_090d765e;
                      }
                      bVar29 = true;
                    }
                    iVar26 = iVar26 + 1;
                  } while (iVar26 != 4);
                  if (!bVar29) {
                    *puStack_174 = 0xffff;
                    goto LAB_090d73c4;
                  }
                }
                else {
                  *puStack_174 = *puStack_174 + 0x1f;
                  iVar26 = uVar25 - 0xfc;
                  abStack_fc[iVar24 + iVar26 + 0xfc] = abStack_fc[iVar24 + iVar26 + 0xfc] | 1;
                  iVar13 = IsMoxieAbility(uVar3);
                  if ((iVar13 == 0) && (iVar13 = IsTrappedByAbility(uVar22,uVar3), iVar13 == 0)) {
                    iVar13 = 0;
                    uStack_154 = 0;
                    do {
                      if ((*(uint *)((iVar13 + 0x2097917) * 4) & uVar15) == 0) {
                        if (cStack_7c == '\0') {
                          uVar5 = GetMonData(pPStack_170,iVar13 + 0xd,0,&GetMonData);
                          iVar11 = sub_906f0b8(pPStack_170,uVar5);
                        }
                        else {
                          uVar5 = GetBattleMonMove(uStack_7e,(u8)iVar13);
                          iVar11 = PriorityCalc(uStack_7e,0,uVar5);
                        }
                        if (iVar11 < 1) {
                          *(undefined1 *)((int)auStack_e4 + uStack_154) = 0;
                          *(u16 *)(auStack_72 + uStack_154 * 2 + -2) = uVar5;
                        }
                        else {
                          iVar11 = uStack_154 << 1;
                          pcStack_148 = (undefined1 *)((int)auStack_e4 + uStack_154);
                          while( true ) {
                            if (iVar11 == 0) break;
                            *(undefined2 *)(auStack_72 + iVar11 + -2) =
                                 *(undefined2 *)(auStack_72 + iVar11 + -4);
                            *pcStack_148 = pcStack_148[-1];
                            iVar11 = iVar11 + -2;
                            pcStack_148 = pcStack_148 + -1;
                          }
                          uStack_74 = uVar5;
                          auStack_e4[0] = CONCAT11(auStack_e4[0]._1_1_,1);
                        }
                        uStack_154 = uStack_154 + 1 & 0xff;
                      }
                      iVar13 = iVar13 + 1;
                    } while (iVar13 != 4);
                    for (uVar10 = 0; uVar10 < uStack_154; uVar10 = uVar10 + 1) {
                      uVar19 = *(ushort *)(auStack_72 + uVar10 * 2 + -2);
                      uVar14 = (uint)uVar19;
                      if ((gBattleMoves[uVar14].effect == 0x81 /* EFFECT_RAPID_SPIN */) &&
                         (iVar13 = GetBattlerSide(gActiveBattler,0xc,uVar14 * 0xc,&GetBattlerSide),
                         (int)((uint)gSideStatuses[iVar13] << 0x1b) < 0)) {
                        if ((gBattleTypeFlags & 1) == 0) {
                          uVar12 = ViableMonCountFromBank(gActiveBattler);
                          acStack_ec[iVar24 + uVar25] = 1 < uVar12;
                        }
                        else {
                          uVar12 = ViableMonCountFromBank(gActiveBattler);
                          acStack_ec[iVar24 + uVar25] = 2 < uVar12;
                        }
                      }
                      if (((gBattleMoves[uVar14].split != 2) &&
                          (*(char *)((int)auStack_e4 + uVar10) != '\0')) &&
                         (bVar4 = MoveKnocksOutFromParty(uVar19,pPStack_170,bVar16,&uStack_d0),
                         bVar4 != 0)) {
                        uVar19 = *puStack_174;
                        *puStack_174 = uVar19 + 8;
                        bVar18 = abStack_fc[iVar24 + iVar26 + 0xfc];
                        abStack_fc[iVar24 + iVar26 + 0xfc] = bVar18 | 4;
                        if (-1 < (int)((uint)bVar18 << 0x19)) {
                          *puStack_174 = uVar19 + 0x16;
                          bVar18 = bVar18 | 0x44;
                          goto LAB_090d765c;
                        }
                        break;
                      }
                      if (((uVar14 == 0x22d) || (uVar14 == 0xe4)) &&
                         (bVar4 = MoveKnocksOutFromParty(uVar19,pPStack_170,bVar16,&uStack_d0),
                         bVar4 != 0)) goto LAB_090d7520;
                    }
                  }
                  else {
LAB_090d7520:
                    *puStack_174 = *puStack_174 + 8;
                    bVar18 = abStack_fc[iVar24 + iVar26 + 0xfc] | 4;
LAB_090d765c:
                    abStack_fc[iVar24 + iVar26 + 0xfc] = bVar18;
                  }
                }
LAB_090d765e:
                uVar10 = CheckMoveLimitations(uVar22,0,0xff);
                Memset(auStack_72,0,0x5a);
                uStack_74 = CONCAT11(gActiveBattler,bVar16);
                pPStack_6c = pPStack_170;
                PopulateDamageCalcStructWithBaseAttackerData(&uStack_74);
                PopulateDamageCalcStructWithBaseDefenderData(&uStack_74);
                uVar19 = pPStack_170->hp;
                uVar7 = GetBattlerSide(gActiveBattler);
                iVar26 = GetMonEntryHazardDamage(pPStack_170,uVar7);
                uVar14 = (uint)uVar19 - iVar26;
                uVar14 = uVar14 & (int)~uVar14 >> 0x1f;
                uStack_154._0_2_ = (undefined2)uVar14;
                uStack_58 = (undefined2)uStack_154;
                iVar26 = 0;
                bVar2 = false;
                bVar29 = false;
                uStack_158 = 0;
                do {
                  uVar5 = GetBattleMonMove(bVar16,(u8)iVar26);
                  if (uVar5 == 0) break;
                  if ((int)(gBattleMons[uVar22].status2 << 0x13) < 0) {
                    iVar13 = MoveInMoveset(gLockedMoves[uVar22],uVar22);
                    if ((iVar13 == 0) || (gLockedMoves[uVar22] == uVar5)) goto LAB_090d76ea;
                  }
                  else {
LAB_090d76ea:
                    if ((*(uint *)((iVar26 + 0x2097917) * 4) & uVar10) == 0) {
                      iVar13 = CalcMoveSplit(uVar22,uVar5);
                      if (iVar13 == 0) {
                        bVar29 = true;
                      }
                      else {
                        if (iVar13 != 1) goto LAB_090d7910;
                        bVar2 = true;
                      }
                      iVar13 = PriorityCalc(uVar22,0,uVar5);
                      if (iVar13 < 1) {
                        acStack_100[uStack_158] = '\0';
                        auStack_e4[uStack_158] = uVar5;
                      }
                      else {
                        iVar13 = uStack_158 << 1;
                        pcStack_148 = acStack_100 + uStack_158;
                        while( true ) {
                          if (iVar13 == 0) break;
                          *(undefined2 *)((int)auStack_e4 + iVar13) =
                               *(undefined2 *)(acStack_ec + iVar13 + 6);
                          *pcStack_148 = pcStack_148[-1];
                          iVar13 = iVar13 + -2;
                          pcStack_148 = pcStack_148 + -1;
                        }
                        auStack_e4[0] = uVar5;
                        acStack_100[0] = '\x01';
                      }
                      uStack_158 = uStack_158 + 1 & 0xff;
                    }
                  }
LAB_090d7910:
                  iVar26 = iVar26 + 1;
                } while (iVar26 != 4);
                cVar27 = '\0';
                bVar1 = false;
                for (pcStack_148 = (char *)0x0; pcStack_148 < uStack_158;
                    pcStack_148 = (char *)((int)pcStack_148 + 1)) {
                  uVar5 = auStack_e4[(int)pcStack_148];
                  if ((bVar28) && (1 < gBattleResources->ai->aiFlags)) {
                    uVar10 = sub_9086b40(uVar22,gActiveBattler,uVar5,pPStack_170,&uStack_74);
                    iVar26 = IsAffectedByDisguse(cStack_63,uStack_66,uStack_25);
                    if (iVar26 == 0) {
                      if ((uVar14 & 0xffff) <= uVar10) {
                        iVar26 = uVar25 - 0xfc;
                        if ((((int)((uint)abStack_fc[iVar24 + iVar26 + 0xfc] << 0x19) < 0) &&
                            (acStack_100[(int)pcStack_148] != '\0')) &&
                           ((gTerrainType != '\x04' ||
                            (iVar13 = sub_90751c8(pPStack_170), iVar13 == 0)))) {
                          abStack_fc[iVar24 + iVar26 + 0xfc] =
                               abStack_fc[iVar24 + iVar26 + 0xfc] & 0xbf;
                        }
                        if ((gBattleTypeFlags & 1) != 0) goto LAB_090d792e;
                        uVar19 = *puStack_174;
                        bVar16 = abStack_fc[iVar24 + iVar26 + 0xfc];
                        if ((bVar16 & 0x40) == 0) {
                          abStack_fc[iVar24 + iVar26 + 0xfc] = bVar16 | 0x80;
                          if ((short)uVar19 < 0x27) {
                            *puStack_174 = bVar16 & 0x40;
                            goto LAB_090d7a8c;
                          }
                          uVar19 = uVar19 - 0x27;
                          goto LAB_090d7a4e;
                        }
                        if ((bVar16 & 1) != 0) goto LAB_090d792e;
                        if ((short)uVar19 < 0xf) {
                          *puStack_174 = bVar16 & 1;
                          goto LAB_090d7a8c;
                        }
                        uVar19 = uVar19 - 0xf;
                        goto LAB_090d7a4e;
                      }
                      uStack_140 = uVar10;
                    }
                    else {
                      uStack_140 = 0;
                      if (cStack_63 == -0x61) {
                        uStack_140 = (uint)(uStack_54 >> 3);
                      }
                    }
                    iVar26 = sub_9073b08(pPStack_170,cStack_63,uVar5,uStack_64);
                    if (iVar26 != 0) {
                      uVar10 = uVar10 << 1;
                    }
                    iVar26 = MathMin(iVar6 + uVar14,pPStack_170->maxHP);
                    if ((int)(uStack_140 + uVar10) < sVar9 + iVar26) {
                      if (sVar9 * 2 + iVar26 <= (int)(uStack_140 + uVar10 + uVar10))
                      goto LAB_090d79f0;
                    }
                    else {
                      bVar1 = true;
                    }
                  }
                  else {
                    iVar26 = AI_TypeCalc(uVar5,uVar22,gActiveBattler,pPStack_170);
                    if (iVar26 << 0x1e < 0) goto LAB_090d792e;
                    if (iVar26 == 0) {
LAB_090d79f0:
                      cVar27 = cVar27 + '\x01';
                    }
                  }
                }
                if (bVar1) {
LAB_090d792e:
                  if ((short)*puStack_174 < 1) {
                    uVar19 = 0;
                  }
                  else {
                    uVar19 = *puStack_174 - 1;
                  }
LAB_090d7a4e:
                  *puStack_174 = uVar19;
                }
                else {
                  if (cVar27 == '\0') {
                    *puStack_174 = *puStack_174 + 0x11;
                    pbVar23 = abStack_fc + uVar25;
                    bVar18 = 2;
                    bVar16 = pbVar23[iVar24];
                  }
                  else {
                    iVar26 = gBattleMons[uVar22].statStages[0] * 2;
                    uVar10 = udivsi((uint)gBattleMons[uVar22].attack *
                                                (uint)*(byte *)(iVar26 + 0x9124898),
                                                *(undefined1 *)(iVar26 + 0x9124899));
                    iVar26 = gBattleMons[uVar22].statStages[3] * 2;
                    uVar22 = udivsi((uint)gBattleMons[uVar22].spAttack *
                                          (uint)*(byte *)(iVar26 + 0x9124898),
                                          *(undefined1 *)(iVar26 + 0x9124899));
                    if (((bVar29) &&
                        (uVar14 = GetMonData(pPStack_170,0x3c,0,&GetMonData), uVar14 <= uVar10))
                       || ((bVar2 && (uVar10 = GetMonData(pPStack_170,0x3f,0,&GetMonData),
                                     uVar10 <= uVar22)))) goto LAB_090d7a8c;
                    *puStack_174 = *puStack_174 + 2;
                    pbVar23 = abStack_fc + uVar25;
                    bVar16 = pbVar23[iVar24];
                    bVar18 = 8;
                  }
                  pbVar23[iVar24] = bVar18 | bVar16;
                }
              }
LAB_090d7a8c:
            }
            uVar19 = *puStack_174;
            sVar17 = 0x8c;
            if (bVar28) {
              sVar17 = 0x46;
            }
            if (((((short)uVar19 < sVar17) || (acStack_ec[iVar24 + uVar25] == '\0')) &&
                (uStack_178 != 6)) && ((short)uVar19 <= (short)auStack_dc[uStack_178])) {
              if (uVar19 == auStack_dc[uStack_178]) {
                if (abStack_fc[uStack_178] < 0x80) {
                  if (abStack_fc[iVar24 + uVar25] < 0x80) {
                    uVar7 = Random2();
                    __umodsi3(uVar7,100);
                    if ((extraout_r1 & 0xffff) < 0x32) goto LAB_090d7b9a;
                  }
                }
                else if (abStack_fc[iVar24 + uVar25] < 0x80) goto LAB_090d7b9a;
              }
              if ((uStack_168 == 6) || ((short)auStack_dc[uStack_168] < (short)*puStack_174)) {
LAB_090d7460:
                uStack_168 = uVar21;
              }
              else if (*puStack_174 == auStack_dc[uStack_168]) {
                if (abStack_fc[uStack_168] < 0x80) {
                  if (abStack_fc[iVar24 + uVar25] < 0x80) {
                    uVar7 = Random2();
                    __umodsi3(uVar7,100);
                    if ((extraout_r1_00 & 0xffff) < 0x32) goto LAB_090d7460;
                  }
                }
                else if (abStack_fc[iVar24 + uVar25] < 0x80) goto LAB_090d7460;
              }
            }
            else {
LAB_090d7b9a:
              uStack_168 = uStack_178;
              uStack_178 = uVar21;
            }
          }
LAB_090d73c4:
          uStack_16c = uStack_15c;
          uStack_15c = uVar21;
        }
        pPStack_170 = pPStack_170 + 1;
        puStack_174 = puStack_174 + 1;
        iVar24 = iVar24 + 1;
      }
      uVar25 = gNewBS;
      iVar6 = GetBattlerSide(gActiveBattler);
      memcpy_(uVar25 + iVar6 * 0xc + 0x860,auStack_dc);
      uVar25 = gNewBS;
      iVar6 = GetBattlerSide(gActiveBattler);
      memcpy_(uVar25 + iVar6 * 6 + 0x878,abStack_fc);
      uVar25 = gNewBS;
      if (uStack_178 == 6) {
        uVar20 = (uint)gActiveBattler;
        *(undefined2 *)(gNewBS + (uVar20 + 0x210) * 4 + 8) = 0;
        iVar6 = uVar25 + uVar20 * 2;
        *(undefined1 *)(iVar6 + 0x858) = 0;
        *(undefined1 *)(iVar6 + 0x840) = (undefined1)uStack_15c;
        *(undefined2 *)(uVar25 + uVar20 * 4 + 0x84a) = 0;
        *(undefined1 *)(iVar6 + 0x859) = 0;
        *(byte *)(iVar6 + 0x841) = (byte)uStack_16c;
        iVar6 = BankSideHasTwoTrainers();
        uVar25 = gNewBS;
        uStack_178 = uStack_15c;
        if (iVar6 != 0) goto LAB_090d71f6;
        uVar20 = gActiveBattler ^ 2;
        *(undefined2 *)(gNewBS + (uVar20 + 0x210) * 4 + 8) = 0;
        iVar6 = uVar25 + uVar20 * 2;
        *(undefined1 *)(iVar6 + 0x858) = 0;
        *(undefined1 *)(iVar6 + 0x840) = (undefined1)uStack_15c;
        *(undefined2 *)(uVar25 + uVar20 * 4 + 0x84a) = 0;
        *(undefined1 *)(iVar6 + 0x859) = 0;
        pbVar23 = (byte *)(iVar6 + 0x841);
      }
      else {
        uVar25 = (uint)abStack_fc[uStack_178];
        if ((-1 < (int)(uVar25 << 0x1e)) && ((uVar25 & 0x41) != 0x41)) {
          iVar6 = sub_878(gActiveBattler,extraout_r1_01,0x41,&GetBattlerSide);
          uVar25 = gNewBS;
          for (uVar20 = (uint)bStack_106; uVar20 < bStack_105; uVar20 = uVar20 + 1) {
            if (((acStack_ec[uVar20] != '\0') && (abStack_fc[uVar20] < 0x80)) ||
               ((((byte)(&gSideTimers[0].field_0xa)[iVar6 * 0xb] & 0xf) >> 2 != 0 &&
                (acStack_f4[uVar20] != '\0')))) {
              uVar15 = (uint)gActiveBattler;
              iVar6 = gNewBS + (uVar15 + 0x210) * 4;
              if ((int)(gBattleTypeFlags << 0x1f) < 0) {
                *(undefined2 *)(iVar6 + 8) = 0x8e;
                *(undefined1 *)(uVar25 + (uVar15 + 0x428) * 2 + 8) = 0x20;
                iVar6 = BankSideHasTwoTrainers();
                uVar25 = gNewBS;
                if (iVar6 == 0) {
                  uVar15 = (uint)gActiveBattler;
                  *(undefined2 *)(gNewBS + ((uVar15 ^ 2) + 0x210) * 4 + 8) = 0x8e;
                  *(undefined1 *)(uVar25 + ((uVar15 ^ 2) + 0x428) * 2 + 8) = 0x20;
                }
              }
              else {
                *(undefined2 *)(iVar6 + 8) = 0x47;
                *(undefined1 *)(uVar25 + (uVar15 + 0x428) * 2 + 8) = 0x20;
              }
              *(char *)(gNewBS + (gActiveBattler + 0x41c) * 2 + 8) = (char)uVar20;
              iVar6 = BankSideHasTwoTrainers();
              if (iVar6 == 0) {
                *(char *)(gNewBS + ((gActiveBattler ^ 2) + 0x41c) * 2 + 8) = (char)uVar20;
              }
              uStack_168 = uStack_178;
              uStack_178 = uVar20 & 0xff;
              break;
            }
          }
        }
        uVar25 = gNewBS;
        uVar20 = (uint)gActiveBattler;
        iVar6 = gNewBS + uVar20 * 2;
        *(undefined1 *)(iVar6 + 0x840) = (undefined1)uStack_178;
        *(undefined1 *)(iVar6 + 0x841) = (undefined1)uStack_168;
        *(ushort *)(uVar25 + (uVar20 + 0x210) * 4 + 8) = auStack_dc[uStack_178];
        *(ushort *)(uVar25 + uVar20 * 4 + 0x84a) = auStack_dc[uStack_168];
        *(byte *)(iVar6 + 0x858) = abStack_fc[uStack_178];
        *(byte *)(iVar6 + 0x859) = abStack_fc[uStack_168];
        if ((-1 < (int)(gBattleTypeFlags << 0x1f)) ||
           (iVar6 = BankSideHasTwoTrainers(), uVar25 = gNewBS, iVar6 != 0)) goto LAB_090d71f6;
        uVar20 = gActiveBattler ^ 2;
        iVar6 = gNewBS + uVar20 * 2;
        *(undefined1 *)(iVar6 + 0x840) = (undefined1)uStack_178;
        *(undefined1 *)(iVar6 + 0x841) = (undefined1)uStack_168;
        uVar19 = auStack_dc[uStack_168];
        *(ushort *)(uVar25 + (uVar20 + 0x210) * 4 + 8) = auStack_dc[uStack_178];
        *(ushort *)(uVar25 + uVar20 * 4 + 0x84a) = uVar19;
        *(byte *)(iVar6 + 0x858) = abStack_fc[uStack_178];
        pbVar23 = (byte *)(iVar6 + 0x859);
        uStack_16c._0_1_ = abStack_fc[uStack_168];
      }
      *pbVar23 = (byte)uStack_16c;
    }
  }
LAB_090d71f6:
  return (u8)uStack_178;
}

// ---- CalcMostSuitableMonSwitchIfNecessary  (ROM 0x90d7f1c)
void CalcMostSuitableMonSwitchIfNecessary(void)

{
  int iVar1;
  
  if ((*(char *)(gNewBS + gActiveBattler + 0x884) == '\0') && (gBattleMons[gActiveBattler].hp != 0))
  {
    CalcMostSuitableMonToSwitchInto();
    *(undefined1 *)(gNewBS + gActiveBattler + 0x884) = 1;
    iVar1 = BankSideHasTwoTrainers();
    if (iVar1 == 0) {
      *(undefined1 *)(gNewBS + (gActiveBattler ^ 2) + 0x884) = 1;
    }
  }
  return;
}

// ---- GetSecondMostSuitableMonToSwitchIntoFlags  (ROM 0x90d7f7c)
u8 GetSecondMostSuitableMonToSwitchIntoFlags(void)

{
  byte bVar1;
  u8 uVar2;
  uint in_r1;
  int iVar3;
  undefined4 uStack_14;
  
  uStack_14 = in_r1;
  LoadBattlersAndFoes((u8 *)&uStack_14,(u8 *)((int)&uStack_14 + 1),(u8 *)((int)&uStack_14 + 2),
                      (u8 *)((int)&uStack_14 + 3));
  CalcMostSuitableMonSwitchIfNecessary();
  iVar3 = gNewBS + (uint)gActiveBattler * 2;
  bVar1 = *(byte *)(iVar3 + 0x841);
  uVar2 = 0;
  if ((gBattleStruct->monToSwitchIntoId[uStack_14 & 0xff] != bVar1) &&
     (gBattleStruct->monToSwitchIntoId[uStack_14 >> 8 & 0xff] != bVar1)) {
    uVar2 = *(u8 *)(iVar3 + 0x859);
  }
  return uVar2;
}

// ---- GetMostSuitableMonToSwitchIntoFlags  (ROM 0x90d7fe4)
u8 GetMostSuitableMonToSwitchIntoFlags(void)

{
  byte bVar1;
  u8 uVar2;
  int iVar3;
  uint in_r1;
  undefined4 uStack_14;
  
  uStack_14 = in_r1;
  LoadBattlersAndFoes((u8 *)&uStack_14,(u8 *)((int)&uStack_14 + 1),(u8 *)((int)&uStack_14 + 2),
                      (u8 *)((int)&uStack_14 + 3));
  CalcMostSuitableMonSwitchIfNecessary();
  iVar3 = gNewBS + (uint)gActiveBattler * 2;
  bVar1 = *(byte *)(iVar3 + 0x840);
  if ((gBattleStruct->monToSwitchIntoId[uStack_14 & 0xff] == bVar1) ||
     (gBattleStruct->monToSwitchIntoId[uStack_14 >> 8 & 0xff] == bVar1)) {
    uVar2 = *(u8 *)(gNewBS + (uint)gActiveBattler * 2 + 0x859);
  }
  else {
    uVar2 = *(u8 *)(iVar3 + 0x858);
  }
  return uVar2;
}

// ---- GetMostSuitableMonToSwitchIntoScore  (ROM 0x90d8050)
s16 GetMostSuitableMonToSwitchIntoScore(void)

{
  byte bVar1;
  s16 sVar2;
  uint in_r1;
  uint uVar3;
  undefined4 uStack_14;
  
  uStack_14 = in_r1;
  LoadBattlersAndFoes((u8 *)&uStack_14,(u8 *)((int)&uStack_14 + 1),(u8 *)((int)&uStack_14 + 2),
                      (u8 *)((int)&uStack_14 + 3));
  CalcMostSuitableMonSwitchIfNecessary();
  uVar3 = (uint)gActiveBattler;
  bVar1 = *(byte *)(gNewBS + (uVar3 + 0x41c) * 2 + 8);
  if ((gBattleStruct->monToSwitchIntoId[uStack_14 & 0xff] == bVar1) ||
     (gBattleStruct->monToSwitchIntoId[uStack_14 >> 8 & 0xff] == bVar1)) {
    sVar2 = *(s16 *)(gNewBS + uVar3 * 4 + 0x84a);
  }
  else {
    sVar2 = *(s16 *)(gNewBS + (uVar3 + 0x210) * 4 + 8);
  }
  return sVar2;
}

// ---- GetSecondMostSuitableMonToSwitchIntoByParty  (ROM 0x90d80cc)
u8 GetSecondMostSuitableMonToSwitchIntoByParty(Pokemon *party)

{
  int iVar1;
  uint in_r1;
  byte bVar2;
  uint uVar3;
  Pokemon *pPVar4;
  undefined4 uStack_1c;
  
  pPVar4 = party;
  uStack_1c = in_r1;
  LoadBattlersAndFoes((u8 *)&uStack_1c,(u8 *)((int)&uStack_1c + 1),(u8 *)((int)&uStack_1c + 2),
                      (u8 *)((int)&uStack_1c + 3));
  CalcMostSuitableMonSwitchIfNecessary();
  bVar2 = *(byte *)(gNewBS + (uint)gActiveBattler * 2 + 0x841);
  uVar3 = (uint)bVar2;
  if ((((uVar3 == 6) || (gBattleStruct->monToSwitchIntoId[uStack_1c & 0xff] == uVar3)) ||
      (gBattleStruct->monToSwitchIntoId[uStack_1c >> 8 & 0xff] == uVar3)) ||
     (iVar1 = GetMonData(party + uVar3,0x39,0,&GetMonData,pPVar4), iVar1 == 0)) {
    bVar2 = 6;
  }
  return bVar2;
}

// ---- GetMostSuitableMonToSwitchIntoByParty  (ROM 0x90d8168)
u8 GetMostSuitableMonToSwitchIntoByParty(Pokemon *party)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte bStack_24;
  byte bStack_1c;
  byte bStack_1b;
  u8 uStack_1a;
  u8 auStack_19 [5];
  
  LoadBattlersAndFoes(&bStack_1c,&bStack_1b,&uStack_1a,auStack_19);
  CalcMostSuitableMonSwitchIfNecessary();
  bVar1 = *(byte *)(gNewBS + (gActiveBattler + 0x41c) * 2 + 8);
  uVar3 = (uint)bVar1;
  bStack_24 = *(byte *)(gNewBS + (uint)gActiveBattler * 2 + 0x841);
  if ((uVar3 == 6) || (iVar2 = GetMonData(party + uVar3,0x39,0), iVar2 == 0)) {
    CalcMostSuitableMonToSwitchInto();
    *(undefined1 *)(gNewBS + gActiveBattler + 0x884) = 1;
    iVar2 = BankSideHasTwoTrainers();
    if (iVar2 == 0) {
      *(undefined1 *)(gNewBS + (gActiveBattler ^ 2) + 0x884) = 1;
    }
  }
  if ((gBattleStruct->monToSwitchIntoId[bStack_1c] != uVar3) &&
     (gBattleStruct->monToSwitchIntoId[bStack_1b] != uVar3)) {
    bStack_24 = bVar1;
  }
  return bStack_24;
}

// ---- ShouldSwitch  (ROM 0x90d824c)
bool8 ShouldSwitch(Pokemon *party,u8 firstId,u8 lastId)

{
  u16 move;
  bool bVar1;
  BattleStruct *pBVar2;
  bool8 bVar3;
  byte bVar4;
  u8 uVar5;
  u8 uVar6;
  u8 uVar7;
  bool8 bVar8;
  u8 uVar9;
  u8 uVar10;
  move_t mVar11;
  move_t mVar12;
  short sVar13;
  u16 uVar14;
  ushort uVar15;
  s16 sVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  u32 uVar24;
  bool8 checkConfusion;
  bool8 checkConfusion_00;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  int iVar28;
  ushort *puVar29;
  char cVar30;
  byte bVar31;
  Pokemon *pPVar32;
  uint uVar33;
  bool bVar34;
  uint uStack_44;
  uint uStack_40;
  Pokemon *pPStack_3c;
  u8 uStack_1c;
  byte bStack_1b;
  byte bStack_1a;
  byte abStack_19 [5];
  
  uVar21 = (uint)lastId;
  uVar26 = (uint)firstId;
  iVar17 = FlagGet(0x1042);
  if (iVar17 != 0) {
    return 0;
  }
  iVar17 = FlagGet(0x10c0);
  if (iVar17 != 0) {
    return 0;
  }
  bVar3 = IsTrapped(gActiveBattler,1);
  if (bVar3 != 0) {
    return 0;
  }
  uVar27 = (uint)gActiveBattler;
  if ((gStatuses3[uVar27] & 0x11000000) != 0) {
    return 0;
  }
  uVar18 = 0;
  uVar25 = uVar27;
  if ((int)(gBattleTypeFlags << 0x1f) < 0) {
    uVar25 = (uint)gAbsentBattlerFlags;
    bVar4 = GetBattlerPosition(uVar27);
    iVar17 = GetBattlerAtPosition(bVar4 ^ 2);
    uVar18 = (uint)gActiveBattler;
    if ((*(uint *)(&gBitTable + iVar17 * 4) & uVar25) == 0) {
      bVar4 = GetBattlerPosition();
      uVar18 = GetBattlerAtPosition(bVar4 ^ 2);
    }
    uVar25 = uVar18;
  }
  uVar22 = Random2(uVar18);
  iVar17 = umodsi(uVar22,4);
  if (iVar17 == 0) {
    return 0;
  }
  pPStack_3c = party + uVar26;
  cVar30 = '\0';
  pPVar32 = pPStack_3c;
  for (uVar18 = uVar26; uVar18 < uVar21; uVar18 = uVar18 + 1) {
    sVar13 = GetMonData(pPVar32,0x41,0,&GetMonData);
    if ((((sVar13 != 0) && (sVar13 != 0x19c)) && (pPVar32->hp != 0)) &&
       (((gBattlerPartyIndexes[uVar27] != uVar18 && (gBattlerPartyIndexes[uVar25] != uVar18)) &&
        ((gBattleStruct->monToSwitchIntoId[uVar27] != uVar18 &&
         (gBattleStruct->monToSwitchIntoId[uVar25] != uVar18)))))) {
      cVar30 = cVar30 + '\x01';
    }
    pPVar32 = pPVar32 + 1;
  }
  if (cVar30 == '\0') {
    return 0;
  }
  LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
  bVar4 = bStack_1a;
  uVar33 = (uint)bStack_1a;
  mVar11 = IsValidMovePrediction(bStack_1a,gActiveBattler);
  bVar31 = abStack_19[0];
  uStack_40 = (uint)mVar11;
  uVar25 = (uint)abStack_19[0];
  mVar12 = IsValidMovePrediction(abStack_19[0],gActiveBattler);
  uVar27 = (uint)mVar12;
  uVar18 = (uint)gActiveBattler;
  if (((*(char *)(gNewBS + uVar18 + 0x1d1) != '\0') || (8 < gBattleMons[uVar18].statStages[6])) ||
     ((mVar11 == 0 && mVar12 == 0 ||
      ((gBattleMoves[uStack_40].split == 2 && (gBattleMoves[uVar27].split == 2))))))
  goto sw_d84e6_1;
  if ((gBattleTypeFlags & 1) != 0) {
    if (*(char *)(gNewBS + uVar18 + 0x1cd) == '\0') {
      uVar14 = *(u16 *)(gNewBS + (uVar18 * 4 + uVar33 + 0x3d4) * 2 + 8);
      move = *(u16 *)(gNewBS + (uVar18 * 4 + uVar25 + 0x3d4) * 2 + 8);
      uVar5 = GetDoubleKillingScore(uVar14,gActiveBattler,bVar4);
      if (((uVar5 < 10) && (uVar5 = GetDoubleKillingScore(move,gActiveBattler,bVar31), uVar5 < 10))
         && ((iVar17 = sub_9073ea4(gActiveBattler,7), iVar17 == 0 ||
             ((uVar5 = GetDoubleKillingScore(uVar14,gActiveBattler,bVar4), uVar5 < 6 &&
              (uVar5 = GetDoubleKillingScore(move,gActiveBattler,bVar31), uVar5 < 6))))))
      goto LAB_090d8470;
    }
    goto sw_d84e6_1;
  }
  uVar5 = PredictBankFightingStyle(bVar4);
  bVar3 = IsClassDamager(uVar5);
  if ((bVar3 == 0) &&
     ((*(char *)(gNewBS + gActiveBattler + 0x1cd) != '\0' ||
      (uVar18 = Random2(), (uVar18 & 1) != 0)))) goto sw_d84e6_1;
  bVar3 = MoveWouldHitFirst(mVar11,(ushort)bVar4,(ushort)gActiveBattler);
  if (bVar3 == 0) {
    bVar3 = CanKnockOut(gActiveBattler,bVar4);
    uVar18 = (uint)bVar3;
LAB_090d83ec:
    if (uVar18 != 0) goto sw_d84e6_1;
  }
  else {
    bVar3 = CanKnockOut(bVar4,gActiveBattler);
    if ((bVar3 == 0) && (bVar3 = CanKnockOut(gActiveBattler,bVar4), bVar3 != 0)) {
      uVar18 = sub_9073ea4(gActiveBattler,6);
      goto LAB_090d83ec;
    }
  }
  bVar3 = CanKnockOut(bVar4,gActiveBattler);
  if ((((bVar3 == 0) && (iVar17 = sub_9073ea4(gActiveBattler,7), iVar17 != 0)) ||
      (((int)(gBattleMons[gActiveBattler].status2 << 7) < 0 &&
       (bVar3 = DamagingMoveThaCanBreakThroughSubstituteInMoveset(bVar4,gActiveBattler), bVar3 == 0)
       ))) || ((((gDisableStructs[gActiveBattler].isFirstTurn == 0 &&
                 (gDisableStructs[uVar33].isFirstTurn == 0)) &&
                (*(ushort *)(gNewBS + (uVar33 * 4 + (uint)gActiveBattler + 0x104) * 2 + 6) ==
                 uStack_40)) && (gLastUsedMoves[uVar33] != uStack_40))))
  goto sw_d84e6_1;
LAB_090d8470:
  if (((uStack_40 == 0) || (gBattleMoves[uStack_40].split == 2)) ||
     (((gBattleTypeFlags & 1) != 0 &&
      (((uVar27 != 0 && (gBattleMoves[uVar27].split != 2)) &&
       (uVar18 = Random2(), (uVar18 & 1) != 0)))))) {
    bStack_1a = abStack_19[0];
    uStack_40 = uVar27;
  }
  bVar4 = bStack_1a;
  iVar17 = GetMoveTypeSpecial(bStack_1a,uStack_40);
  uVar22 = GetBankAbility(bVar4);
  iVar20 = sub_9073c04(uVar22,uStack_40);
  if ((iVar20 != 0) || (9 < iVar17 - 4U)) goto sw_d84e6_1;
                      switch(iVar17 - 4U) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    goto sw_d84e6_1;
  case 6:
    iVar28 = 0x12;
    iVar20 = 0xfe;
    goto LAB_090d874a;
  case 7:
    iVar28 = 0x83;
    iVar20 = 0x62;
    break;
  case 8:
    iVar28 = 0x71;
    goto LAB_090d87c0;
  case 0:
    iVar28 = 0xbc;
LAB_090d87c0:
    iVar20 = iVar28;
LAB_090d874a:
    iVar17 = iVar28;
    break;
  case 9:
    iVar28 = 0x50;
    iVar20 = 0x1f;
    iVar17 = 10;
  }
  iVar19 = func_0x090dea90(gActiveBattler,bVar4);
  if (((iVar19 != iVar17) && (iVar19 != iVar20)) && (iVar19 != iVar28)) {
    uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
    uVar27 = (uint)uVar5;
    if (((gBattleStruct->monToSwitchIntoId[uStack_1c] != uVar27) &&
        (gBattleStruct->monToSwitchIntoId[bStack_1b] != uVar27)) &&
       (iVar19 = sub_93508b0(party + uVar27,uVar27,uStack_40,iVar17,iVar20,iVar28), iVar19 != 0)) {
      return 1;
    }
    uVar5 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
    uVar18 = (uint)uVar5;
    if (((uVar18 != 6) && (gBattleStruct->monToSwitchIntoId[uStack_1c] != uVar18)) &&
       ((gBattleStruct->monToSwitchIntoId[bStack_1b] != uVar18 &&
        (iVar19 = sub_93508b0(party + uVar18,uVar18,uStack_40,iVar17,iVar20,iVar28), iVar19 != 0))))
    {
      return 1;
    }
    for (uVar25 = uVar26; uVar25 < uVar21; uVar25 = uVar25 + 1) {
      if ((((((pPStack_3c->hp != 0) && (pPStack_3c->species != 0)) &&
            (iVar19 = GetMonData(pPStack_3c,0x2d,0,&GetMonData), iVar19 == 0)) &&
           ((uVar25 != uVar27 && (uVar25 != uVar18)))) &&
          (((uVar25 != gBattlerPartyIndexes[uStack_1c] &&
            ((uVar25 != gBattlerPartyIndexes[bStack_1b] &&
             (uVar25 != gBattleStruct->monToSwitchIntoId[uStack_1c])))) &&
           (uVar25 != gBattleStruct->monToSwitchIntoId[bStack_1b])))) &&
         (iVar19 = sub_93508b0(pPStack_3c,uVar25 & 0xff,uStack_40,iVar17,iVar20,iVar28), iVar19 != 0
         )) {
        return 1;
      }
      pPStack_3c = pPStack_3c + 1;
    }
  }
sw_d84e6_1:
  LoadBattlersAndFoes(&bStack_1a,abStack_19,&uStack_1c,&bStack_1b);
  uVar27 = (uint)gActiveBattler;
  if (((&UNK_02023f40)[uVar27] != '\0') &&
     ((gBattleMons[uVar27].maxHP >> 1 <= gBattleMons[uVar27].hp ||
      (((bVar3 = CanKnockOut(uStack_1c,gActiveBattler), bVar3 != 0 ||
        (((int)(gBattleTypeFlags << 0x1f) < 0 &&
         (bVar3 = CanKnockOut(bStack_1b,gActiveBattler), bVar3 != 0)))) &&
       (bVar3 = HasProtectionMoveInMoveset(gActiveBattler,0x11), bVar3 == 0)))))) {
    uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
    uVar27 = (uint)uVar5;
    if (((gBattleStruct->monToSwitchIntoId[bStack_1a] != uVar27) &&
        (gBattleStruct->monToSwitchIntoId[abStack_19[0]] != uVar27)) &&
       (bVar3 = PassOnWishSwitchingCheck(party,uVar5), bVar3 != 0)) {
      return 1;
    }
    uVar5 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
    uVar18 = (uint)uVar5;
    if (((uVar18 != 6) && (gBattleStruct->monToSwitchIntoId[bStack_1a] != uVar18)) &&
       ((gBattleStruct->monToSwitchIntoId[abStack_19[0]] != uVar18 &&
        (bVar3 = PassOnWishSwitchingCheck(party,uVar5), bVar3 != 0)))) {
      return 1;
    }
    puVar29 = &party[uVar26].species;
    for (uStack_44 = uVar26; uStack_44 < uVar21; uStack_44 = uStack_44 + 1) {
      if (((puVar29[0x1b] != 0) && (*puVar29 != 0)) &&
         ((iVar17 = GetMonData((Pokemon *)(puVar29 + -0x10),0x2d,0,&GetMonData), iVar17 == 0 &&
          ((((((uStack_44 != gBattlerPartyIndexes[bStack_1a] &&
               (uStack_44 != gBattlerPartyIndexes[abStack_19[0]])) &&
              (uStack_44 != gBattleStruct->monToSwitchIntoId[bStack_1a])) &&
             ((uStack_44 != gBattleStruct->monToSwitchIntoId[abStack_19[0]] && (uStack_44 != uVar27)
              ))) && (uStack_44 != uVar18)) &&
           (bVar3 = PassOnWishSwitchingCheck(party,(u8)uStack_44), bVar3 != 0)))))) {
        return 1;
      }
      puVar29 = puVar29 + 0x32;
    }
  }
  uVar27 = ~(uint)gActiveBattler & 1;
  uVar18 = (uint)gLockedMoves[uVar27];
  if ((gBattleTypeFlags & 1) == 0) {
    if ((uVar18 != 0) && (gBattleMoves[uVar18].split != 2)) {
      uVar25 = uVar27;
      goto LAB_090d8a6c;
    }
  }
  else {
    uVar25 = uVar27 | 2;
    if (((uVar18 != 0) && (gBattleMoves[uVar18].split != 2)) ||
       ((gLockedMoves[uVar25] != 0 && (gBattleMoves[gLockedMoves[uVar25]].split != 2)))) {
LAB_090d8a6c:
      iVar17 = IsDynamaxed();
      if (((iVar17 == 0) || (*(char *)(gNewBS + gActiveBattler + 0x1a6) < '\x02')) &&
         (iVar17 = RunAllSemiInvulnerableLockedMoveCalcs_isra_0(uVar27,uVar25,1), iVar17 != 0)) {
        return 1;
      }
    }
  }
  iVar17 = ShouldSwitchIfPerishSong();
  if (iVar17 != 0) {
    return 1;
  }
  iVar17 = sub_9350ac6(party,uVar26,uVar21);
  if (iVar17 != 0) {
    return 1;
  }
  LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
  bVar4 = bStack_1a;
  if (*(char *)(gNewBS + gActiveBattler + 0x1cd) == '\0') {
    if ((gBattleTypeFlags & 1) == 0) {
      mVar11 = IsValidMovePrediction(bStack_1a,gActiveBattler);
      if ((((-1 < (int)(gBattleMons[gActiveBattler].status2 << 6)) ||
           (bVar3 = MoveKnocksOutXHits(mVar11,bVar4,gActiveBattler,1), bVar3 == 0)) ||
          (bVar3 = MoveWouldHitFirst(mVar11,(ushort)bVar4,(ushort)gActiveBattler), bVar3 == 0)) &&
         (bVar3 = OnlyBadMovesLeftInMoveset(gActiveBattler,bVar4), bVar3 != 0)) {
        uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
        uVar6 = GetMostSuitableMonToSwitchIntoFlags();
        if (((uVar6 & 0x4a) != 0) &&
           (iVar17 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,party + uVar5,bStack_1a,uVar6),
           iVar17 != 0)) goto LAB_090d872a;
        uVar7 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
        uVar9 = GetSecondMostSuitableMonToSwitchIntoFlags();
        if ((uVar7 != 6) &&
           (((uVar9 & 0x4a) != 0 &&
            (iVar17 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,party + uVar7,bStack_1a,uVar9),
            iVar17 != 0)))) {
LAB_090d8c1a:
          pBVar2 = gBattleStruct;
          iVar17 = GetBattlerSide(gActiveBattler);
          pBVar2->switchoutIndex[iVar17] = uVar7;
          goto LAB_090d8738;
        }
        if ((gBattleStruct->choicedMove[gActiveBattler] != 0) &&
           (iVar17 = CanBeChoiceLocked(), iVar17 != 0)) {
          if ((-1 < (int)((uint)uVar6 << 0x18)) &&
             (iVar17 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,party + uVar5,bStack_1a,uVar6)
             , iVar17 != 0)) goto LAB_090d872a;
          if ((-1 < (int)((uint)uVar9 << 0x18)) &&
             (iVar17 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,party + uVar5,bStack_1a,uVar9)
             , iVar17 != 0)) goto LAB_090d8c1a;
        }
      }
    }
    else if (((-1 < (int)(gBattleMons[gActiveBattler].status2 << 6)) &&
             ((gBattleMons[bStack_1a].hp == 0 ||
              (bVar3 = OnlyBadMovesLeftInMoveset(gActiveBattler,bStack_1a), bVar3 != 0)))) &&
            ((gBattleMons[abStack_19[0]].hp == 0 ||
             (bVar3 = OnlyBadMovesLeftInMoveset(gActiveBattler,abStack_19[0]), bVar3 != 0)))) {
LAB_090d872a:
      pBVar2 = gBattleStruct;
      iVar17 = GetBattlerSide(gActiveBattler);
      pBVar2->switchoutIndex[iVar17] = 6;
      goto LAB_090d8738;
    }
  }
  LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
  iVar17 = GetBankAbility(gActiveBattler);
  if (iVar17 == 0x1e) {
    bVar3 = WillTakeSignificantDamageFromEntryHazards(gActiveBattler,4);
    if (bVar3 != 0) goto LAB_090d8aec;
    iVar17 = GetBattlerSide(gActiveBattler);
    if ((((byte)(&gSideTimers[0].field_0xa)[iVar17 * 0xb] & 0xf) >> 2 != 0) &&
       ((gBattleMons[gActiveBattler].status1 & 0x88) != 0)) {
      GetBankPartyData();
      iVar17 = sub_9074eb8();
      if ((iVar17 != 0) &&
         ((iVar17 = IsOfType(gActiveBattler,3 /* Poison */), iVar17 == 0 &&
          (iVar17 = CheckGrounding(gActiveBattler), iVar17 != 0)))) {
        uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
        iVar17 = sub_90c1df8(party + uVar5,3);
        if ((iVar17 == 0) || (iVar17 = sub_90751c8(party + uVar5), iVar17 == 0)) goto LAB_090d8aec;
      }
    }
    uVar26 = (uint)gActiveBattler;
    if ((gBattleMons[uVar26].status1 & 7) == 0) {
      if ((gBattleMons[uVar26].status1 != 0) &&
         (gBattleMons[uVar26].maxHP >> 1 <= gBattleMons[uVar26].hp)) {
        uVar26 = IsDynamaxed();
LAB_090d8d0e:
        if (uVar26 == 0) goto LAB_090d8d14;
      }
      goto LAB_090d8aec;
    }
LAB_090d8d14:
    iVar17 = sub_93513c0(party,0,0xff);
    if (iVar17 != 0) {
      return 1;
    }
    uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
    bVar31 = bStack_1a;
    bVar4 = gActiveBattler;
    if ((gBattleTypeFlags & 1) == 0) {
      uVar6 = GetMostSuitableMonToSwitchIntoFlags();
      iVar17 = PredictedMoveWontDoTooMuchToMon(bVar4,party + uVar5,bVar31,uVar6);
      if ((iVar17 == 0) &&
         ((bVar3 = PredictedMoveWontKOMon(gActiveBattler,party + uVar5,bStack_1a), bVar3 == 0 ||
          (uVar26 = Random2(), (uVar26 & 1) != 0)))) goto LAB_090d8aec;
    }
    goto LAB_090d8d4a;
  }
  if ((((iVar17 == 0x56) &&
       (gBattleMons[gActiveBattler].hp <= gBattleMons[gActiveBattler].maxHP >> 1)) &&
      (iVar17 = IsDynamaxed(), iVar17 == 0)) &&
     (bVar3 = WillTakeSignificantDamageFromEntryHazards(gActiveBattler,3), bVar4 = bStack_1a,
     bVar3 == 0)) {
    uVar26 = (uint)bStack_1a;
    mVar11 = IsValidMovePrediction(bStack_1a,gActiveBattler);
    bVar31 = abStack_19[0];
    uVar21 = (uint)abStack_19[0];
    mVar12 = IsValidMovePrediction(abStack_19[0],gActiveBattler);
    if (((((gBattleMons[uVar26].hp != 0) && (mVar11 != 0)) &&
         (bVar3 = MoveKnocksOutXHits(mVar11,bVar4,gActiveBattler,1), bVar3 != 0)) ||
        (((iVar17 = IsDoubleBattle(), iVar17 != 0 && (gBattleMons[uVar21].hp != 0)) &&
         ((mVar12 != 0 && (bVar3 = MoveKnocksOutXHits(mVar12,bVar31,gActiveBattler,1), bVar3 != 0)))
         ))) && ((gBattleMons[uVar26].hp != 0 ||
                 ((iVar17 = IsDoubleBattle(), iVar17 != 0 &&
                  (uVar26 = (uint)abStack_19[0], gBattleMons[uVar26].hp != 0)))))) {
      mVar11 = IsValidMovePrediction(gActiveBattler,(u8)uVar26);
      if ((mVar11 != 0) &&
         (bVar3 = MoveWouldHitFirst(mVar11,(ushort)gActiveBattler,(u16)uVar26), bVar3 != 0)) {
        bVar3 = MoveKnocksOutXHits(mVar11,gActiveBattler,(u8)uVar26,1);
        uVar26 = (uint)bVar3;
        goto LAB_090d8d0e;
      }
      goto LAB_090d8d14;
    }
  }
LAB_090d8aec:
  uVar27 = ~(uint)gActiveBattler & 1;
  uVar26 = gStatuses3[uVar27] & 0x130400c0;
  uVar21 = uVar27;
  if ((gBattleTypeFlags & 1) == 0) {
joined_r0x090d9078:
    if (uVar26 != 0) goto LAB_090d8b14;
  }
  else {
    uVar21 = uVar27 | 2;
    if (uVar26 == 0) {
      uVar26 = gStatuses3[uVar21] & 0x130400c0;
      goto joined_r0x090d9078;
    }
LAB_090d8b14:
    iVar17 = IsDynamaxed();
    if (((iVar17 == 0) || (*(char *)(gNewBS + gActiveBattler + 0x1a6) < '\x02')) &&
       (iVar17 = RunAllSemiInvulnerableLockedMoveCalcs_isra_0(uVar27,uVar21,0), iVar17 != 0)) {
      return 1;
    }
  }
  if (((((((gStatuses3[gActiveBattler] & 0x1800) != 0) &&
         (iVar17 = GetBankAbility(), iVar17 != 0x1e)) &&
        ((iVar17 = GetBankItemEffect(gActiveBattler), iVar17 != 3 && (iVar17 != 9)))) &&
       ((iVar17 = IsDynamaxed(gActiveBattler), iVar17 == 0 ||
        (iVar17 = Random2(), iVar17 << 0x1f < 0)))) &&
      (uVar26 = (uint)gActiveBattler, gBattleMons[uVar26].maxHP >> 2 < gBattleMons[uVar26].hp)) &&
     (iVar17 = sub_90763c6(uVar26,0), iVar17 != 0)) {
    LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
    bVar4 = bStack_1a;
    uVar21 = (uint)bStack_1a;
    uVar26 = ViableMonCountFromBank(uVar21);
    if ((1 < uVar26) ||
       (((gBattleMons[uVar21].hp == 0 || (bVar3 = CanKnockOut(gActiveBattler,bVar4), bVar3 == 0)) &&
        ((gBattleMons[abStack_19[0]].hp == 0 ||
         (bVar3 = CanKnockOut(gActiveBattler,abStack_19[0]), bVar3 == 0)))))) {
      iVar17 = GetBattlerSide(gActiveBattler);
      for (bVar31 = 0; bVar31 < gBattlersCount; bVar31 = bVar31 + 1) {
        iVar20 = GetBattlerSide(bVar31);
        if (((iVar17 != iVar20) && (bVar3 = IsTrapped(bVar31,1), bVar3 != 0)) &&
           (bVar3 = IsTakingSecondaryDamage(bVar31,checkConfusion), bVar3 != 0)) goto LAB_090d90ac;
      }
      if ((((gBattleMons[gActiveBattler].statStages[6] < 9) ||
           (iVar17 = AbilityBattleEffects(0xc,(uint)gActiveBattler,0x8d,0,0), iVar17 != 0)) &&
          (((iVar17 = GetBankAbility(gActiveBattler), iVar17 != 0x30 &&
            ((iVar17 != 0x3d && (bVar3 = MoveEffectInMoveset(0x5c /* EFFECT_SNORE */,gActiveBattler), bVar3 == 0)))) &&
           (bVar3 = MoveEffectInMoveset(0x61 /* EFFECT_SLEEP_TALK */,gActiveBattler), bVar3 == 0)))) &&
         (((iVar17 = MoveInMoveset(0x271 /* Elec Terrain */,gActiveBattler), iVar17 == 0 ||
           (iVar17 = sub_90765b2(gActiveBattler), iVar17 == 0)) &&
          ((iVar17 = MoveInMoveset(0x273 /* Mist Terrain */,gActiveBattler), iVar17 == 0 ||
           (iVar17 = CheckGrounding(gActiveBattler), iVar17 == 0)))))) {
        bVar31 = abStack_19[0];
        if ((int)(gBattleTypeFlags << 0x1f) < 0) {
          uVar14 = *(u16 *)(((uint)gActiveBattler * 4 + (uint)abStack_19[0] + 0x3d4) * 2 + gNewBS +
                           8);
          uVar5 = GetDoubleKillingScore
                            (*(u16 *)(((uint)gActiveBattler * 4 + uVar21 + 0x3d4) * 2 + gNewBS + 8),
                             gActiveBattler,bVar4);
          if ((uVar5 < 0xc) &&
             (uVar5 = GetDoubleKillingScore(uVar14,gActiveBattler,bVar31), uVar5 < 0xc))
          goto LAB_090d93a8;
        }
        else {
          mVar11 = IsValidMovePrediction(bVar4,gActiveBattler);
          bVar3 = IsPredictedToSwitch(bVar4,gActiveBattler);
          if ((((bVar3 != 0) || (gBattleMoves[mVar11].effect == 0x6f /* EFFECT_PROTECT */)) ||
              (((gBattleMoves[mVar11].effect == 0x9b /* EFFECT_SEMI_INVULNERABLE */ &&
                (bVar3 = MoveWouldHitFirst(mVar11,(ushort)bVar4,(ushort)gActiveBattler), bVar3 != 0)
                ) || ((bVar3 = MoveWouldHitFirst(mVar11,(ushort)abStack_19[0],(ushort)gActiveBattler
                                                ), bVar3 != 0 &&
                      (bVar3 = CanKnockOut(bVar4,gActiveBattler), bVar3 != 0)))))) ||
             (bVar3 = CanKnockOut(gActiveBattler,bVar4), bVar3 == 0)) {
LAB_090d93a8:
            iVar17 = sub_9074ba4(gActiveBattler);
            if ((iVar17 != 0) ||
               (uVar5 = GetMostSuitableMonToSwitchIntoFlags(), (uVar5 & 0x41) == 0x41))
            goto LAB_090d8d4a;
          }
        }
      }
    }
  }
LAB_090d90ac:
  if (((*(char *)(gNewBS + gActiveBattler + 0x1cd) == '\0') &&
      ((bVar3 = IsBankAsleep(gActiveBattler), bVar3 != 0 &&
       (iVar17 = Random2(), iVar17 << 0x1f < 0)))) &&
     ((iVar17 = IsDynamaxed(gActiveBattler), iVar17 == 0 ||
      ((int)*(char *)(gNewBS + gActiveBattler + 0x1a6) <
       (int)(gBattleMons[gActiveBattler].status1 & 7))))) {
    iVar17 = GetBankAbility(gActiveBattler);
    uVar26 = (uint)gActiveBattler;
    if (((((((gBattleMons[uVar26].statStages[0] < 8) && (gBattleMons[uVar26].statStages[3] < 8)) &&
           (gBattleMons[uVar26].statStages[2] < 8)) && (gBattleMons[uVar26].statStages[6] < 9)) ||
         (iVar20 = sub_91521d0(), -1 < iVar20 << 0x1f)) &&
        ((((iVar17 != 0x3d && (iVar17 != 0x30)) &&
          ((iVar17 != 0x6b || (((gBattleWeather & 0x1007) == 0 || (UNK_02023f48 == '\x01')))))) &&
         (bVar3 = MoveEffectInMoveset(0x61 /* EFFECT_SLEEP_TALK */,gActiveBattler), bVar3 == 0)))) &&
       ((bVar3 = MoveEffectInMoveset(0x5c /* EFFECT_SNORE */,gActiveBattler), bVar3 == 0 &&
        (bVar3 = MoveEffectInMoveset(0x25 /* EFFECT_REST */,gActiveBattler), bVar3 == 0)))) {
      uVar5 = GetBankFightingStyle(gActiveBattler);
      bVar3 = IsClassKillerSweeper(uVar5);
      if ((bVar3 == 0) || (bVar3 = IsTrapped(~gActiveBattler & 1,1), bVar3 == 0)) {
        if (-1 < (int)(gBattleTypeFlags << 0x1f)) {
          uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
          uVar6 = GetMostSuitableMonToSwitchIntoFlags();
          uVar26 = party[uVar5].condition;
          if ((((uVar26 & 7) != 0) && (uVar26 != 1)) ||
             (iVar17 = PredictedMoveWontDoTooMuchToMon
                                 (gActiveBattler,party + uVar5,~gActiveBattler & 1,uVar6),
             iVar17 == 0)) goto LAB_090d9146;
        }
LAB_090d8d4a:
        pBVar2 = gBattleStruct;
        iVar17 = GetBattlerSide(gActiveBattler);
        pBVar2->switchoutIndex[iVar17] = 6;
LAB_090d8738:
        EmitTwoReturnValues(1,2,0,&EmitTwoReturnValues);
        return 1;
      }
    }
  }
LAB_090d9146:
  iVar17 = func_0x090dea90(gActiveBattler,~gActiveBattler & 1);
  if (((iVar17 == 0x73) || (iVar20 = sub_90e0364(gActiveBattler), iVar20 != 0)) ||
     ((iVar20 = IsDynamaxed(gActiveBattler), iVar20 != 0 || (gBattleResources->ai->aiFlags < 2))))
  goto LAB_090d9158;
  if ((((int)(gStatuses3[gActiveBattler] << 0x1d) < 0) &&
      (uVar26 = Random2(), (uVar26 & 3) == 0)) &&
     ((bVar3 = AnyUsefulOffseniveStatIsRaised(gActiveBattler), bVar3 == 0 &&
      ((uVar22 = 0, (gBattleTypeFlags & 1) != 0 ||
       (bVar3 = CanKnockOut(gActiveBattler,~gActiveBattler & 1), bVar3 == 0)))))) {
LAB_090d95b4:
    bVar3 = WillTakeSignificantDamageFromEntryHazards(gActiveBattler,4);
    if (bVar3 == 0) {
      uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
      uVar6 = GetMostSuitableMonToSwitchIntoFlags();
      iVar17 = sub_9351292(uVar5,uVar6,party,uVar22);
      if (iVar17 != 0) {
        return 1;
      }
      uVar5 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
      uVar6 = GetSecondMostSuitableMonToSwitchIntoFlags();
      iVar17 = sub_9351292(uVar5,uVar6,party,uVar22);
      if (iVar17 != 0) {
        return 1;
      }
    }
  }
  else {
    uVar26 = gBattleMons[gActiveBattler].status1;
    if ((((1 < (uVar26 & 7)) && ((int)(gBattleMons[gActiveBattler].status2 << 4) < 0)) ||
        ((int)(gBattleMons[gActiveBattler].status2 << 3) < 0)) ||
       ((0x600 < (uVar26 & 0xf00) && (iVar17 != 0x68)))) {
LAB_090d9608:
      uVar22 = 1;
      goto LAB_090d95b4;
    }
    if (((uVar26 & 0x88) != 0) && (iVar17 != 0x68)) {
      GetBankPartyData();
      iVar17 = GetMonAbility();
      if (iVar17 == 0x68) goto LAB_090d9608;
    }
  }
LAB_090d9158:
  uVar26 = (uint)gActiveBattler;
  if (*(char *)(gNewBS + uVar26 + 0x1cd) == '\0') {
    if (((-1 < (int)(gBattleMons[uVar26].status2 << 6)) && ((gBattleTypeFlags & 1) == 0)) &&
       (1 < gBattleResources->ai->aiFlags)) {
      uVar21 = ~uVar26 & 1;
      uVar5 = (u8)uVar21;
      mVar11 = IsValidMovePrediction(gActiveBattler,uVar5);
      mVar12 = IsValidMovePrediction(uVar5,gActiveBattler);
      uVar26 = (uint)gActiveBattler;
      if (((-1 < (int)(gBattleMons[uVar26].status1 << 0x19)) ||
          (uVar15 = __udivsi3(gBattleMons[uVar26].maxHP,3), uVar15 <= gBattleMons[uVar26].hp)) ||
         ((iVar17 = GetBankAbility(uVar26), iVar17 == 0x70 || (iVar17 == 0x1e)))) {
        if ((((gBattleMons[gActiveBattler].species != 0x315) &&
             (gBattleMons[gActiveBattler].species != 0x341)) ||
            ((gDisableStructs[gActiveBattler].protectUses != 0 ||
             ((((mVar12 == 0 || (iVar17 = CheckContact(mVar12,uVar21), iVar17 == 0)) ||
               (bVar3 = RealPhysicalMoveInMoveset(uVar5), bVar3 == 0)) ||
              ((iVar17 = GetBankAbility(gActiveBattler), iVar17 != 0xd3 ||
               (iVar17 = MoveInMoveset(0x20f /* Kings Shield */,gActiveBattler), iVar17 == 0)))))))) &&
           ((((iVar17 = GetBankAbility(gActiveBattler), iVar17 != 0xdb ||
              (*(char *)(gNewBS + gBattlerPartyIndexes[gActiveBattler] + 0xf8) != '\0')) &&
             (mVar12 != 0)) &&
            (((((mVar11 == 0 ||
                (bVar3 = MoveWouldHitFirst(mVar11,(ushort)gActiveBattler,(u16)uVar21), bVar3 == 0))
               && ((-1 < (int)(gBattleMons[gActiveBattler].status2 << 7) ||
                   (iVar17 = MoveBlockedBySubstitute(mVar12,uVar21), iVar17 == 0)))) &&
              ((bVar3 = MoveKnocksOutXHits(mVar12,uVar5,gActiveBattler,1), bVar3 != 0 &&
               (bVar3 = WillTakeSignificantDamageFromEntryHazards(gActiveBattler,3), bVar3 == 0))))
             && ((uVar26 = func_0x090dd734(gActiveBattler), 0x14 < uVar26 ||
                 (sVar16 = GetMostSuitableMonToSwitchIntoScore(), 0x45 < sVar16)))))))) {
          uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
          uVar6 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
          uVar7 = GetMostSuitableMonToSwitchIntoFlags();
          iVar17 = ShouldSwitchToAvoidDeathHelper(party,uVar21,mVar12,(uint)uVar5,uVar7);
          if (iVar17 != 0) {
            return 1;
          }
          uVar7 = GetSecondMostSuitableMonToSwitchIntoFlags();
          iVar17 = ShouldSwitchToAvoidDeathHelper(party,uVar21,mVar12,(uint)uVar6,uVar7);
          if (iVar17 != 0) {
            return 1;
          }
          iVar17 = GetBattlerSide(gActiveBattler);
          LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
          uVar26 = 0;
          do {
            sVar13 = GetMonData(party + uVar26,0x41,0,&GetMonData);
            if ((((((sVar13 != 0) && (sVar13 != 0x19c)) && (party[uVar26].hp != 0)) &&
                 (((uVar5 != uVar26 && (uVar6 != uVar26)) &&
                  ((gBattlerPartyIndexes[uStack_1c] != uVar26 &&
                   ((gBattlerPartyIndexes[bStack_1b] != uVar26 &&
                    (gBattleStruct->monToSwitchIntoId[uStack_1c] != uVar26)))))))) &&
                (gBattleStruct->monToSwitchIntoId[bStack_1b] != uVar26)) &&
               (iVar20 = ShouldSwitchToAvoidDeathHelper
                                   (party,uVar21,mVar12,uVar26 & 0xff,
                                    *(undefined1 *)(gNewBS + iVar17 * 6 + uVar26 + 0x878)),
               iVar20 != 0)) {
              return 1;
            }
            uVar26 = uVar26 + 1;
          } while (uVar26 != 6);
        }
      }
      goto LAB_090d916a;
    }
  }
  else {
LAB_090d916a:
    if (*(char *)(gNewBS + gActiveBattler + 0x1cd) != '\0') {
      return 0;
    }
  }
  uVar5 = GetBankFightingStyle(gActiveBattler);
  iVar17 = IsDynamaxed(gActiveBattler);
  if (((iVar17 == 0) && (bVar3 = IsClassDamager(uVar5), bVar3 != 0)) &&
     ((uVar26 = (uint)gActiveBattler, gBattleMons[uVar26].statStages[0] < 4 ||
      ((gBattleMons[uVar26].statStages[3] < 4 || (gBattleMons[uVar26].statStages[5] < 4)))))) {
    uVar26 = CheckMoveLimitations(uVar26,0,0xff);
    LoadBattlersAndFoes(&uStack_1c,&bStack_1b,&bStack_1a,abStack_19);
    bVar4 = bStack_1a;
    mVar11 = IsValidMovePrediction(gActiveBattler,bStack_1a);
    if ((mVar11 != 0x21d) &&
       ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
        (mVar11 = IsValidMovePrediction(gActiveBattler,abStack_19[0]), mVar11 != 0x21d)))) {
      iVar17 = 0;
      bVar1 = false;
      bVar34 = false;
      do {
        uVar14 = GetBattleMonMove(gActiveBattler,(u8)iVar17);
        uVar21 = (uint)uVar14;
        if (uVar21 == 0) break;
        if (((*(uint *)((iVar17 + 0x2097917) * 4) & uVar26) == 0) &&
           (gBattleMoves[uVar21].power != 0)) {
          iVar20 = CalcMoveSplit(gActiveBattler,uVar21);
          if (iVar20 == 0) {
            if (((gBattleMoves[uVar21].effect != 0x59 /* EFFECT_COUNTER */) && (uVar21 != 0x2b4)) && (uVar21 != 0x217)) {
              bVar34 = true;
            }
          }
          else if ((iVar20 == 1) && (gBattleMoves[uVar21].effect != 0x90 /* EFFECT_MIRROR_COAT */)) {
            bVar1 = true;
          }
        }
        iVar17 = iVar17 + 1;
      } while (iVar17 != 4);
      uVar26 = (uint)gActiveBattler;
      if (((((gBattleMons[uVar26].statStages[0] < 4) && (bVar34)) && (!bVar1)) ||
          (((gBattleMons[uVar26].statStages[3] < 4 && (bVar1)) &&
           ((!bVar34 || (gBattleMons[uVar26].statStages[0] < 4)))))) ||
         (((gBattleMons[uVar26].statStages[5] < 4 &&
           (bVar3 = AllMovesInMovesetWithAccuracyLessThan(gActiveBattler,bVar4,0x46,1), bVar3 != 0))
          && ((((gBattleTypeFlags & 1) == 0 ||
               (bVar3 = AllMovesInMovesetWithAccuracyLessThan(gActiveBattler,abStack_19[0],0x46,1),
               bVar3 != 0)) && (bVar3 = IsClassKillerSweeper(uVar5), bVar3 == 0)))))) {
        bVar34 = false;
        if (-1 < (int)(gBattleTypeFlags << 0x1f)) {
          bVar3 = FastPivotingMoveInMovesetThatAffects(gActiveBattler,bVar4);
          bVar34 = bVar3 != 0;
        }
        bVar3 = CanKnockOut(bVar4,gActiveBattler);
        if (((bVar3 == 0) &&
            ((-1 < (int)(gBattleTypeFlags << 0x1f) ||
             (bVar3 = CanKnockOut(abStack_19[0],gActiveBattler), bVar3 == 0)))) ||
           (gBattleMons[gActiveBattler].statStages[5] < 4)) {
          uVar5 = GetMostSuitableMonToSwitchIntoByParty(party);
          uVar6 = GetMostSuitableMonToSwitchIntoFlags();
          if (((uVar6 & 10) != 0) ||
             (((-1 < (int)(gBattleTypeFlags << 0x1f) && ((int)((uint)uVar6 << 0x19) < 0)) &&
              (iVar17 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,party + uVar5,bStack_1a),
              iVar17 != 0)))) {
            ConfirmAISwitch((uint)uVar5,bVar34);
            return 1;
          }
        }
      }
    }
  }
  if (*(char *)(gNewBS + gActiveBattler + 0x1cd) == '\0') {
    uVar26 = ~(uint)gActiveBattler & 1;
    uVar5 = (u8)uVar26;
    mVar11 = IsValidMovePrediction(uVar5,gActiveBattler);
    if (((((gBattleTypeFlags & 1) == 0) && (1 < gBattleResources->ai->aiFlags)) &&
        (iVar17 = IsDynamaxed(gActiveBattler), iVar17 == 0)) &&
       (((-1 < (int)(gBattleMons[gActiveBattler].status1 << 0x19) ||
         (iVar17 = GetBankAbility(), iVar17 == 0x70)) || (iVar17 == 0x3e)))) {
      uVar6 = GetBankFightingStyle(gActiveBattler);
      bVar3 = IsClassDamager(uVar6);
      if (bVar3 != 0) {
        bVar3 = CanKnockOut(gActiveBattler,uVar5);
        uVar6 = gActiveBattler;
        if (bVar3 != 0) {
          if (mVar11 != 0xfc) {
            return 0;
          }
          uVar22 = GetBankAbility(gActiveBattler);
          uVar23 = GetBankAbility(uVar26);
          iVar17 = IsTargetAbilityIgnored(uVar22,uVar23,0xfc);
          uVar7 = 0;
          if (iVar17 == 0) {
            uVar7 = GetBankAbility(gActiveBattler);
          }
          bVar3 = CanBeFlinched(uVar6,uVar5,uVar7,0xfc);
          if (bVar3 == 0) {
            return 0;
          }
          uVar24 = GetFinalAIMoveDamage(0xfc,uVar5,gActiveBattler,1,(void *)0x0);
          if (uVar24 < gBattleMons[gActiveBattler].maxHP >> 1) {
            return 0;
          }
        }
        if (((((-1 < (int)(gBattleMons[gActiveBattler].status2 << 7)) ||
              (bVar3 = DamagingMoveThaCanBreakThroughSubstituteInMoveset(uVar5,gActiveBattler),
              bVar3 != 0)) &&
             (bVar3 = WillTakeSignificantDamageFromEntryHazards(gActiveBattler,4), bVar3 == 0)) &&
            ((bVar3 = IsTrapped(uVar5,1), bVar3 == 0 ||
             (bVar3 = IsTakingSecondaryDamage(uVar5,checkConfusion_00), bVar3 == 0)))) &&
           (((bVar3 = CanKnockOut(uVar5,gActiveBattler), bVar3 != 0 &&
             (iVar17 = sub_90dfd28(gActiveBattler,uVar26), iVar17 == 0)) ||
            (((bVar3 = AnyUsefulOffseniveStatIsRaised(gActiveBattler), bVar3 == 0 &&
              (gBattleMons[gActiveBattler].statStages[6] < 9)) &&
             (((bVar3 = IsTakingSecondaryDamage(uVar5,0x58), bVar3 == 0 ||
               (bVar3 = IsTrapped(uVar5,1), bVar3 == 0)) &&
              ((bVar3 = OffensiveSetupMoveInMoveset(gActiveBattler,uVar5), bVar3 == 0 &&
               ((uVar6 = GetMostSuitableMonToSwitchIntoFlags(), (uVar6 & 1) != 0 ||
                (((uVar21 = Random2(), (uVar21 & 1) != 0 &&
                  (((bVar3 = Can2HKO(gActiveBattler,uVar5), bVar3 == 0 ||
                    ((int)(uVar21 << 0x1e) < 0)) &&
                   (bVar3 = ResistsAllMoves(uVar5,gActiveBattler), bVar3 == 0)))) &&
                 (bVar3 = IsStrongestMoveHPDrainingMove(gActiveBattler,uVar5), bVar3 == 0)))))))))))
            ))) {
          mVar11 = IsValidMovePrediction(gActiveBattler,uVar5);
          if (mVar11 == 0xfc) {
            uVar22 = GetBankAbility(uVar26);
            iVar17 = CanFlinch(uVar26,uVar22);
            if (iVar17 != 0) {
              return 0;
            }
          }
          bVar4 = gBattleMoves[mVar11].effect;
          if (bVar4 != 0x6f) {
            bVar3 = FastPivotingMoveInMovesetThatAffects(gActiveBattler,uVar5);
            bVar8 = CanKnockOut(uVar5,gActiveBattler);
            if (bVar8 == 0) {
LAB_090d9c22:
              iVar17 = sub_93513c0(party,bVar3,uVar26);
              return iVar17 != 0;
            }
            bVar8 = MoveWouldHitFirst(mVar11,(ushort)gActiveBattler,(u16)uVar26);
            if (bVar8 == 0) {
              if ((int)(gBattleMons[gActiveBattler].status2 << 6) < 0) {
                return 0;
              }
            }
            else if (bVar4 == 0x62) {
              return 0;
            }
            uVar6 = GetMostSuitableMonToSwitchIntoByParty(party);
            uVar7 = GetMostSuitableMonToSwitchIntoFlags();
            iVar17 = sub_9351174(party,uVar6,uVar7,uVar26,bVar3);
            if (iVar17 == 0) {
              uVar9 = GetSecondMostSuitableMonToSwitchIntoByParty(party);
              uVar10 = GetSecondMostSuitableMonToSwitchIntoFlags();
              iVar17 = sub_9351174(party,uVar9,uVar10,uVar26,bVar3);
              if (iVar17 == 0) {
                if ((gBattleStruct->choicedMove[gActiveBattler] != 0) &&
                   (iVar17 = CanBeChoiceLocked(), bVar4 = gActiveBattler, iVar17 != 0)) {
                  uVar15 = gBattleStruct->choicedMove[gActiveBattler];
                  gBattleStruct->choicedMove[gActiveBattler] = 0;
                  mVar11 = CalcStrongestMove(bVar4,uVar5,0);
                  bVar4 = gActiveBattler;
                  gBattleStruct->choicedMove[gActiveBattler] = uVar15;
                  uVar24 = GetFinalAIMoveDamage(mVar11,bVar4,uVar5,1,(void *)0x0);
                  if ((gBattleMons[uVar26].hp <= uVar24) &&
                     (bVar8 = MoveWouldHitFirst(mVar11,(ushort)gActiveBattler,(u16)uVar26),
                     bVar8 != 0)) {
                    iVar17 = sub_93510ce(uVar6,uVar7,party);
                    if (iVar17 != 0) {
                      return 1;
                    }
                    iVar17 = sub_93510ce(uVar9,uVar10,party);
                    if (iVar17 != 0) {
                      return 1;
                    }
                  }
                }
                goto LAB_090d9c22;
              }
            }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
            return 1;
          }
        }
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023d70) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return 0;
}

// ---- RemoveBestMonToSwitchInto  (ROM 0x90d9d78)
void RemoveBestMonToSwitchInto(u8 bank)

{
  int iVar1;
  
  func_0x090d6cb0();
  iVar1 = BankSideHasTwoTrainers(bank);
  if (iVar1 == 0) {
    func_0x090d6cb0(bank ^ 2);
  }
  return;
}

// ---- ConfirmAISwitch  (ROM 0x9350a5e)
void ConfirmAISwitch(undefined1 param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = gNewBS;
  uVar2 = (uint)gActiveBattler;
  if (param_2 == 0) {
    GetBattlerSide();
    return;
  }
  *(undefined1 *)(gNewBS + uVar2 + 0x1c6) = param_1;
  *(byte *)(uVar1 + 0x1c5) =
       (byte)*(undefined4 *)(&gBitTable + uVar2 * 4) | *(byte *)(uVar1 + 0x1c5);
  return;
}

// ---- PredictedMoveWontDoTooMuchToMon  (ROM 0x9350fbe)
undefined4
PredictedMoveWontDoTooMuchToMon(int param_1,Pokemon *param_2,undefined4 param_3,uint param_4)

{
  bool8 bVar1;
  move_t mVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  ushort uVar7;
  
  mVar2 = IsValidMovePrediction((u8)param_3,(u8)param_1);
  uVar3 = (uint)mVar2;
  if (-1 < (int)(param_4 * 0x1000000)) {
    if (((uVar3 == 0) || (gBattleMoves[uVar3].split == 2)) || (uVar3 == 0xe4)) {
      return 1;
    }
    if ((-1 < gBattleTypeFlags << 4) || (gBattleMons[param_1].moves[0] != 0)) {
      if ((param_4 & 2) != 0) {
        return 1;
      }
      if (gBattleMoves[uVar3].effect == 0xed /* EFFECT_SUCKER_PUNCH */) {
        return 1;
      }
      iVar4 = GetMonAbility(param_2);
      uVar7 = param_2->species;
      uVar5 = CalcMoveSplit(param_3,uVar3);
      iVar6 = IsAffectedByDisguse(iVar4,uVar7,uVar5);
      if (iVar6 == 0) {
        sub_9086b40(param_3,param_1,uVar3,param_2,0);
stub_93510cc:
        uVar5 = GetBattlerSide(param_1);
        return uVar5;
      }
      uVar7 = 0;
      if (iVar4 == 0x9f) {
        uVar7 = param_2->maxHP >> 3;
      }
      if (uVar7 < param_2->hp) {
        if ((ushort)(uVar7 * 2) < param_2->hp) {
          return 1;
        }
        if ((param_2->maxHP <= (ushort)(uVar7 * 2)) &&
           (bVar1 = HealingMoveInMonMoveset(param_2), bVar1 != 0)) goto stub_93510cc;
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return 0;
}

// ---- PredictedMoveKOsSelfDueToContact  (ROM 0x935113a)
bool PredictedMoveKOsSelfDueToContact(u8 param_1,Pokemon *param_2,int param_3)

{
  move_t mVar1;
  int iVar2;
  u32 uVar3;
  bool bVar4;
  
  mVar1 = IsValidMovePrediction((u8)param_3,param_1);
  iVar2 = CheckContact(mVar1,param_3);
  bVar4 = false;
  if (iVar2 != 0) {
    uVar3 = GetContactDamageMonDef((u16)param_3,param_2);
    bVar4 = gBattleMons[param_3].hp <= uVar3;
  }
  return bVar4;
}

// ---- ShouldSwitchToAvoidDeathHelper  (ROM 0x93511d8)
longlong ShouldSwitchToAvoidDeathHelper
                   (uint param_1,undefined4 param_2,undefined4 param_3,uint param_4,byte param_5)

{
  bool8 bVar1;
  int iVar2;
  uint uVar3;
  Pokemon *mon;
  longlong lVar4;
  
  if ((param_4 < 6) &&
     ((((mon = (Pokemon *)(param_1 + param_4 * 100), (param_5 & 0x4a) != 0 &&
        (uVar3 = AI_TypeCalc(param_3,param_2,gActiveBattler,mon,param_1,param_4,param_3),
        (uVar3 & 0x29) != 0)) ||
       ((-1 < gBattleTypeFlags << 4 &&
        ((((param_5 & 10) != 0 || ((param_5 & 0x41) == 0x41)) &&
         (iVar2 = PredictedMoveWontDoTooMuchToMon(gActiveBattler,mon,param_2,param_5), iVar2 != 0)))
        ))) || ((iVar2 = PredictedMoveKOsSelfDueToContact(gActiveBattler,mon,param_2), iVar2 != 0 &&
                (bVar1 = PredictedMoveWontKOMon(gActiveBattler,mon,(u8)param_2), bVar1 != 0)))))) {
    lVar4 = GetBattlerSide(gActiveBattler);
    return lVar4;
  }
  return (ulonglong)param_1 << 0x20;
}

// ---- SwitchToBestResistMonHelper  (ROM 0x9351372)
undefined8
SwitchToBestResistMonHelper(undefined4 param_1,int param_2,int param_3,int param_4,u8 param_5)

{
  bool8 bVar1;
  undefined4 uVar2;
  int iVar3;
  Pokemon *mon;
  
  if (param_4 << 0x1e < 0) {
LAB_09351380:
    ConfirmAISwitch(param_3,param_1);
    uVar2 = 1;
  }
  else {
    if (param_5 != 0xff) {
      mon = (Pokemon *)(param_2 + param_3 * 100);
      iVar3 = PredictedMoveKOsSelfDueToContact(gActiveBattler,mon,param_5);
      if ((iVar3 != 0) && (bVar1 = PredictedMoveWontKOMon(gActiveBattler,mon,param_5), bVar1 != 0))
      goto LAB_09351380;
    }
    uVar2 = 0;
  }
  return CONCAT44(param_1,uVar2);
}
