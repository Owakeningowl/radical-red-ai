// ai_partner.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- AIScript_Partner  (ROM 0x90cfef4)
u8 AIScript_Partner(u8 bankAtk,u8 bankAtkPartner,u16 originalMove,u8 originalViability,
                   AIScript *data)

{
  sbyte sVar1;
  u8 bankAtk_00;
  byte bVar2;
  ushort move;
  u8 uVar3;
  u8 class;
  u8 uVar4;
  bool8 bVar5;
  u16 move_00;
  u16 uVar6;
  u16 uVar7;
  move_t mVar8;
  move_t mVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  byte *pbVar17;
  uint uVar18;
  uint uVar19;
  ushort bankDef;
  uint uVar20;
  byte bVar21;
  bool bVar22;
  bool bVar23;
  bool bVar24;
  uint uStack_40;
  ushort auStack_1a [3];
  
  uVar19 = (uint)bankAtkPartner;
  uVar18 = (uint)bankAtk;
  uVar3 = GetBankFightingStyle(bankAtk);
  class = GetBankFightingStyle(bankAtkPartner);
  auStack_1a[0] = (ushort)originalViability;
  move_00 = TryReplaceMoveWithZMove(bankAtk,bankAtkPartner,originalMove);
  uVar20 = (uint)move_00;
  bVar2 = gBattleMoves[uVar20].effect;
  iVar10 = GetMoveTypeSpecial(uVar18,uVar20);
  move = data->partnerMove;
  uStack_40 = move;
  iVar11 = GetBankItemEffect(uVar19);
  pbVar17 = &data->foe1;
  uVar4 = GetAIAbility(bankAtk,*pbVar17,move_00);
  bVar21 = data->atkPartnerAbility;
  iVar12 = IsTargetAbilityIgnored(bVar21,uVar4,uVar20);
  bVar21 = bVar21 & -(iVar12 == 0);
  iVar12 = CalcMoveSplit(uVar18,uVar20);
  uVar13 = DoesProtectionMoveBlockMove(uVar18,uVar19,uVar20,uStack_40);
  iVar14 = GetBaseMoveTarget(uVar20,uVar18);
  bankDef = (ushort)bankAtkPartner;
  if (iVar14 == 8 || (uVar13 & 0xff) != 0) goto LAB_090cffc2;
  if (bVar21 == 0x71) {
    if (((iVar10 == 0xc) && (bVar5 = IsClassDoublesSpecific(class), bVar5 == 0)) &&
       (bVar5 = RealPhysicalMoveInMoveset(bankAtkPartner), bVar5 != 0)) {
      sVar1 = gBattleMons[uVar19].statStages[0];
joined_r0x090d0218:
      if (sVar1 < 0xc) goto LAB_090d01e0;
    }
    goto LAB_090d00e0;
  }
  if (bVar21 < 0x72) {
    if (bVar21 != 0x12) {
      if (0x12 < bVar21) {
        if (bVar21 == 0x50) {
          if (((iVar10 == 0xd) && (bVar5 = IsClassDoublesSpecific(class), bVar5 == 0)) &&
             (gBattleMons[uVar19].statStages[2] < 0xc)) {
            uVar4 = *pbVar17;
            uVar6 = SpeedCalc(uVar19);
            uVar7 = SpeedCalc(*pbVar17);
            bVar5 = GoodIdeaToRaiseSpeedAgainst(bankAtkPartner,uVar4,1,uVar6,uVar7);
            if (bVar5 == 0) {
              uVar4 = data->foe2;
              uVar6 = SpeedCalc(uVar19);
              uVar7 = SpeedCalc(data->foe2);
              bVar5 = GoodIdeaToRaiseSpeedAgainst(bankAtkPartner,uVar4,1,uVar6,uVar7);
              uVar15 = (uint)bVar5;
LAB_090d0184:
              if (uVar15 == 0) goto LAB_090d00e0;
            }
LAB_090d01e0:
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
        else {
          if (bVar21 == 0x62) goto LAB_090d018a;
          if (bVar21 != 0x1f) goto LAB_090cffc2;
          if (iVar10 == 0xd) goto LAB_090d0062;
        }
        goto LAB_090d00e0;
      }
      if (bVar21 == 10) {
        if (iVar10 == 0xd) goto LAB_090d00d6;
        goto LAB_090d00e0;
      }
      if (bVar21 == 0xb) {
LAB_090d018a:
        if (iVar10 == 0xb) {
          IncreaseHealPartnerViability((s16 *)auStack_1a,uVar3,bankAtkPartner);
        }
      }
LAB_090cffc2:
      if (bVar2 != 0xa4) {
        if (bVar2 < 0xa5) {
          if (bVar2 == 0x73) {
            if ((bVar21 != 8) &&
               ((0x1d < (byte)(bVar21 + 0xa1) ||
                (-1 < (int)((0x20180001U >> (uint)(byte)(bVar21 + 0xa1)) << 0x1f)))))
            goto LAB_090d07ec;
            goto LAB_090d07b8;
          }
          goto LAB_090cffd8;
        }
        goto LAB_090d0ede;
      }
LAB_090d094e:
      if (((bVar21 != 0x69) && (bVar21 != 0x3b)) && (bVar21 != 0xab)) goto LAB_090d097c;
      goto LAB_090d0952;
    }
    if ((iVar10 == 10) &&
       (((bVar5 = IsClassDoublesSpecific(class), bVar5 == 0 &&
         (bVar5 = DamagingMoveTypeInMoveset(bankAtkPartner,10 /* Fire */), bVar5 != 0)) &&
        (-1 < (int)(gBattleResources->flags->flags[uVar19] << 0x1f))))) goto LAB_090d01e0;
LAB_090d00e0:
    if (bVar2 == 0xa4) goto LAB_090d094e;
    if (0xa4 < bVar2) {
LAB_090d0ede:
      if (bVar2 == 0xce) {
        if (((uVar20 == 0x28b) && (iVar10 = sub_905fafe(bVar21), iVar10 != 0)) &&
           ((gBattleMons[uVar19].statStages[1] < 0xc || (gBattleMons[uVar19].statStages[4] < 0xc))))
        {
          IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
        }
      }
      else if (bVar2 < 0xcf) {
        if (bVar2 == 0xb0) {
          bVar5 = IsClassDoublesSpecific(class);
          if (bVar5 == 0) {
            if (uVar20 == 0x2b5) {
              if ((bVar21 != 0xbf) && (uVar13 == 0)) {
                bVar5 = RealPhysicalMoveInMoveset(bankAtkPartner);
                if ((bVar5 == 0) || (0xb < gBattleMons[uVar19].statStages[0])) {
                  bVar5 = SpecialMoveInMoveset(bankAtkPartner);
                  if ((bVar5 != 0) && (gBattleMons[uVar19].statStages[3] < 0xc)) {
                    IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                  }
                }
                else {
                  IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                }
              }
            }
            else if (uVar20 == 0x2d7) {
              if ((((uVar13 == 0) && (gBattleMons[uVar19].statStages[0] < 0xc)) && (bVar21 != 0xbf))
                 && (bVar5 = RealPhysicalMoveInMoveset(bankAtkPartner), bVar5 != 0)) {
                IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
              }
            }
            else if (((uStack_40 != 0) && (uVar13 == 0)) &&
                    ((gBattleMoves[uStack_40].split != 2 &&
                     ((iVar10 = IsRaidBattle(), iVar10 == 0 ||
                      (-1 < (int)((uint)*(byte *)(gNewBS + 0x1b5) << 0x1d))))))) {
              if (gChosenMovesByBanks[uVar19] != 0) {
                uVar3 = GetBattlerSide(gBattleStruct->moveTarget[uVar19]);
                return uVar3;
              }
              IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
            }
          }
        }
        else if (bVar2 < 0xb1) {
          if ((((bVar2 == 0xa6) && (gBattleMons[uVar19].statStages[3] < 0xc)) &&
              (bVar5 = IsClassDoublesSpecific(class), bVar5 == 0)) &&
             ((iVar10 = CanBeConfused(uVar19,uVar18), iVar10 == 0 || ((iVar11 - 8U & 0xff) < 2)))) {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
        else if ((bVar2 == 0xb2) || (bVar2 == 0xbf)) {
          pbVar17 = (byte *)GetAbilityLocation(uVar18);
          uVar18 = (uint)*pbVar17;
          bVar23 = (uVar18 + 0x70 & 0xff) < 2;
          bVar22 = bVar21 == 0x36;
          bVar24 = (byte)(bVar21 + 0x70) < 2;
          if (uVar20 < 0x1dd) {
            if (uVar20 < 0x1db) {
              if (uVar20 == 0x110) {
                if (((uVar13 == 0) && (uVar18 == 0x36 || bVar23)) && (!bVar22 && !bVar24)) {
                  IncreaseDoublesDamageViabilityToScore
                            ((s16 *)auStack_1a,uVar3,(bVar22 || bVar24) + 0xc,bankAtk,bankAtkPartner
                            );
                }
              }
              else if (((uVar20 == 0x11d) && ((uVar13 & 0xff) == 0 && (uVar18 != 0x36 && !bVar23)))
                      && (bVar22 || bVar24)) {
                IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
              }
              goto LAB_090d02f2;
            }
          }
          else {
            if (uVar20 == 0x218) {
              if (((uVar13 == 0) && (bVar22 || bVar24)) && (*(byte *)(uVar18 + 0x9123a05) < 0x80)) {
                IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
              }
              goto LAB_090d02f2;
            }
            if (uVar20 != 0x28f) goto LAB_090d02f2;
          }
          if ((uVar13 == 0) && (bVar22 || bVar24)) {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
      }
      else if (bVar2 == 0xe9) {
        if (uVar13 == 0) {
          IncreaseHealPartnerViability((s16 *)auStack_1a,uVar3,bankAtkPartner);
        }
      }
      else if (bVar2 < 0xea) {
        if (bVar2 == 0xe4) {
          if (uVar20 == 0x288) {
            pbVar17 = &data->foe1;
            mVar8 = IsValidMovePrediction(*pbVar17,bankAtkPartner);
            mVar9 = IsValidMovePrediction(*pbVar17,bankAtkPartner);
            if (((bVar21 == 10) || (bVar21 == 0x50)) || (bVar21 == 0x1f)) {
              if (((mVar8 == 0) || (iVar10 = GetMoveTypeSpecial(*pbVar17,mVar8), iVar10 != 0)) ||
                 (iVar10 = DoesProtectionMoveBlockMove(*pbVar17,uVar19,mVar8,uStack_40), iVar10 != 0
                 )) {
                if (mVar9 != 0) {
                  iVar10 = GetMoveTypeSpecial(data->foe2,mVar9);
                  if ((iVar10 == 0) &&
                     (iVar10 = DoesProtectionMoveBlockMove(data->foe2,uVar19,mVar9,uStack_40),
                     iVar10 == 0)) {
                    IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
                  }
                }
              }
              else {
                IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
              }
            }
          }
        }
        else if (((((bVar2 == 0xe8) && (uVar20 == 0x290)) && (uVar13 == 0)) && (bVar21 == 0x19)) &&
                (((gBattleMons[uVar19].type1 != 0xb || (gBattleMons[uVar19].type2 != 0xb)) ||
                 (gBattleMons[uVar19].type3 != 0xb)))) {
          IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
        }
      }
      else if (bVar2 == 0xec) {
        if (uVar13 == 0) {
          if (uVar20 == 0x29d) {
            bVar5 = MoveWouldHitFirst(move,bankDef,(ushort)data->foe1);
            if (((bVar5 == 0) ||
                (bVar5 = MoveWouldHitFirst(move,bankDef,(ushort)data->foe2), bVar5 == 0)) &&
               ((gBattleMoves[uStack_40].effect != 0x59 /* EFFECT_COUNTER */ && (gBattleMoves[uStack_40].effect != 0x90 /* EFFECT_MIRROR_COAT */))
               )) {
              IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
            }
          }
          else if (uVar20 == 0x29e) {
            bVar5 = MoveWouldHitFirst(move_00,(ushort)bankAtk,bankDef);
            if (bVar5 != 0) {
              uStack_40 = (uint)*(ushort *)(&gLastPrintedMoves + uVar19 * 2);
            }
            if ((uStack_40 != 0) && (gBattleMoves[uStack_40].split != 2)) {
              uVar18 = GetBaseMoveTarget(uStack_40,uVar19);
              if ((uVar18 & 0x28) == 0) {
                IncreaseViability((s16 *)auStack_1a,1);
              }
              else {
                IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
              }
            }
          }
        }
      }
      else if ((((bVar2 == 0xef) && (uVar20 == 0x28a)) &&
               (iVar10 = CheckGrounding(uVar18), iVar10 == 1)) &&
              ((bVar5 = DamagingAllHitMoveTypeInMoveset(bankAtkPartner,4), bVar5 != 0 &&
               (uVar18 = AI_SpecialTypeCalc(0x59,uVar19,uVar18), (uVar18 & 0xc) == 0)))) {
        IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
      }
      goto LAB_090d02f2;
    }
    if (bVar2 == 0x73) {
LAB_090d07ec:
      if (iVar11 != 0x54) {
LAB_090d07f2:
        iVar10 = IsOfType(uVar19,5 /* Rock */);
        if ((((iVar10 == 0) && (iVar10 = IsOfType(uVar19,8 /* Steel */), iVar10 == 0)) &&
            (iVar10 = IsOfType(uVar19,4 /* Ground */), iVar10 == 0)) &&
           ((iVar10 = MoveInMoveset(0x261 /* Shore Up */,uVar19), iVar10 == 0 &&
            (iVar10 = MoveInMoveset(0x137 /* Weather Ball */,uVar19), iVar10 == 0)))) goto LAB_090d02f2;
      }
LAB_090d07b8:
      bVar5 = IsClassDoublesTeamSupport(uVar3);
      if (bVar5 == 0) {
        IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
        goto LAB_090d02f2;
      }
    }
    else {
LAB_090cffd8:
      if (bVar2 < 0x74) {
LAB_090d02a4:
        if (bVar2 == 0xe) {
          if (((uVar20 == 0x280) && (uVar13 == 0)) &&
             ((bVar21 != 0xbf && (gBattleMons[uVar19].statStages[4] < 0xc)))) {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
        else if (bVar2 < 0xf) {
          if (((bVar2 == 10) && (uVar20 == 0x150)) &&
             ((bVar21 != 0xbf && ((bVar21 != 0x2b && (gBattleMons[uVar19].statStages[0] < 0xc))))))
          {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
        else if (bVar2 == 0x10) {
          if (((uVar20 == 0x1e3) && (uVar13 == 0)) &&
             ((bVar21 != 0xbf && (bVar5 = IsClassDoublesSpecific(class), bVar5 == 0)))) {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
        }
        else if (bVar2 == 0x20) {
          if (uVar20 != 0x2dc) {
            if (0x2dc < uVar20) {
              if (uVar20 - 0x3e2 < 2) {
                IncreaseHealPartnerViability((s16 *)auStack_1a,uVar3,bankAtkPartner);
              }
              goto LAB_090d02f2;
            }
            if (uVar20 == 0x25d) {
              uVar18 = gBattleMons[uVar19].status1;
              if ((uVar18 != 0) && (uVar13 == 0)) {
                if ((uVar18 & 0x88) == 0) {
                  if ((int)(uVar18 << 0x1b) < 0) {
                    gBattleMons[uVar19].status1 = 0;
                    bVar5 = GoodIdeaToBurnSelf(bankAtkPartner);
                    if (bVar5 == 0) {
                      IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                    }
                    gBattleMons[uVar19].status1 = uVar18;
                  }
                  else if ((int)(uVar18 << 0x19) < 0) {
                    gBattleMons[uVar19].status1 = 0;
                    bVar5 = GoodIdeaToParalyzeSelf(bankAtkPartner);
                    if (bVar5 == 0) {
                      IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                    }
                    gBattleMons[uVar19].status1 = uVar18;
                  }
                  else if ((int)(uVar18 << 0x1a) < 0) {
                    gBattleMons[uVar19].status1 = 0;
                    iVar10 = sub_90dba10(uVar19);
                    if (iVar10 == 0) {
                      IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                    }
                    gBattleMons[uVar19].status1 = uVar18;
                  }
                  else if (((uVar18 & 7) != 0) &&
                          (((uStack_40 != 0xd6 && (uStack_40 != 0xad)) ||
                           (bVar5 = MoveWouldHitFirst(0x25d,(ushort)bankAtk,bankDef), bVar5 == 0))))
                  {
                    IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                  }
                }
                else {
                  gBattleMons[uVar19].status1 = 0;
                  bVar5 = GoodIdeaToPoisonSelf(bankAtkPartner);
                  if (bVar5 == 0) {
                    IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                  }
                  gBattleMons[uVar19].status1 = uVar18;
                }
              }
              goto LAB_090d02f2;
            }
            if (uVar20 != 0x2c3) goto LAB_090d02f2;
          }
          if (uVar13 == 0) {
            IncreaseHealPartnerViability((s16 *)auStack_1a,uVar3,bankAtkPartner);
          }
        }
        goto LAB_090d02f2;
      }
      if (bVar2 == 0x89) {
LAB_090d08aa:
        iVar10 = sub_9076620(iVar11);
        if ((iVar10 != 0) ||
           (((((bVar21 != 0x22 && (bVar21 != 0x3b)) &&
              (((bVar21 + 0x35 & 0xfd) != 0 && ((bVar21 != 0x60 && (bVar21 != 0xe1)))))) &&
             (bVar5 = MoveEffectInMoveset(0x97 /* EFFECT_SOLARBEAM */,bankAtkPartner), bVar5 == 0)) &&
            ((((bVar5 = MoveEffectInMoveset(0x84 /* EFFECT_MORNING_SUN */,bankAtkPartner), bVar5 == 0 &&
               (iVar10 = MoveInMoveset(0x137 /* Weather Ball */,uVar19), iVar10 == 0)) &&
              (iVar10 = MoveInMoveset(0x4a /* Growth */,uVar19), iVar10 == 0)) &&
             (bVar5 = DamagingMoveTypeInMoveset(bankAtkPartner,10 /* Fire */), bVar5 == 0))))))
        goto LAB_090d02f2;
        bVar5 = IsClassDoublesTeamSupport(uVar3);
        if (bVar5 == 0) {
          IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
          goto LAB_090d02f2;
        }
      }
      else {
        if (0x89 < bVar2) {
          if (bVar2 == 0x8f) {
LAB_090d0e6c:
            if (uVar20 != 0x265) {
              IncreasePsychUpViability((s16 *)auStack_1a,uVar3,bankAtk,bankAtkPartner);
            }
            goto LAB_090d02f2;
          }
          if (bVar2 != 0x9a) goto LAB_090d02f2;
          if (bVar21 != 0xc6) {
            if (bVar21 == 0xf1) {
              if ((iVar12 != 2) &&
                 (bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1), bVar5 == 0)) {
                uVar20 = ~uVar18 & 1;
                iVar10 = GetBankAbility(uVar20);
                uVar13 = uVar20 | 2;
                iVar11 = GetBankAbility(uVar13);
                if ((((gBattleMons[uVar20].hp == 0) || (iVar10 != 0xbf)) &&
                    ((gBattleMons[uVar13].hp == 0 || (iVar11 != 0xbf)))) &&
                   ((iVar10 = sub_90becd0(3,uVar20,uVar18,iVar10), iVar10 != 0 ||
                    (iVar10 = sub_90becd0(3,uVar13,uVar18,iVar11), iVar10 != 0)))) {
                  IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
                }
              }
            }
            else if ((((bVar21 == 0xad) && (iVar12 != 2)) &&
                     (gBattleMons[uVar19].statStages[1] < 0xc)) &&
                    (bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1), bVar5 == 0)) {
              IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
            }
            goto LAB_090d02f2;
          }
          if (iVar10 != 0x11) goto LAB_090d02f2;
          goto LAB_090d0362;
        }
LAB_090d0312:
        if (bVar2 == 0x76) {
          if (((gBattleMons[uVar19].statStages[0] < 0xc) &&
              (bVar5 = IsClassDoublesSpecific(class), bVar5 == 0)) &&
             ((iVar10 = CanBeConfused(uVar19,uVar18), iVar10 == 0 || ((iVar11 - 8U & 0xff) < 2)))) {
            IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
          }
          goto LAB_090d02f2;
        }
        if ((bVar2 != 0x88) || (iVar10 = sub_9076620(iVar11), iVar10 != 0)) goto LAB_090d02f2;
        bVar5 = MoveEffectInMoveset(0x98 /* EFFECT_THUNDER */,bankAtkPartner);
        if ((bVar5 == 0) &&
           ((iVar10 = MoveInMoveset(0x137 /* Weather Ball */,uVar19), iVar10 == 0 && (iVar11 != 0x4f)))) {
          if ((byte)(bVar21 - 0x21) < 0x1b) {
            if (-1 < (int)((0x4000801U >> (uint)(byte)(bVar21 - 0x21)) << 0x1f)) {
LAB_090d086e:
              if ((((bVar21 != 0x62) &&
                   (bVar5 = MoveEffectInMoveset(0x98 /* EFFECT_THUNDER */,bankAtkPartner), bVar5 == 0)) &&
                  (iVar10 = MoveInMoveset(0x137 /* Weather Ball */,uVar19), iVar10 == 0)) &&
                 (bVar5 = DamagingMoveTypeInMoveset(bankAtkPartner,0xb /* Water */), bVar5 == 0))
              goto LAB_090d02f2;
            }
          }
          else if (bVar21 != 0x6b) goto LAB_090d086e;
        }
        bVar5 = IsClassDoublesTeamSupport(uVar3);
        if (bVar5 == 0) {
          IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
          goto LAB_090d02f2;
        }
      }
    }
  }
  else {
    if (bVar21 == 0xbc) {
      if (iVar10 == 4) {
LAB_090d00d6:
        IncreaseHealPartnerViability((s16 *)auStack_1a,uVar3,bankAtkPartner);
      }
      goto LAB_090d00e0;
    }
    if (bVar21 < 0xbd) {
      if (bVar21 == 0x7a) {
        uVar15 = SpeedCalc(uVar18);
        uVar16 = SpeedCalc(*pbVar17);
        if (uVar16 < (uVar15 & 0xff)) {
          bVar5 = CanKnockOut(*pbVar17,bankAtk);
        }
        else {
          bVar5 = Can2HKO(*pbVar17,bankAtk);
        }
        if (bVar5 == 0) {
          uVar16 = SpeedCalc(data->foe2);
          bankAtk_00 = data->foe2;
          if (uVar16 < (uVar15 & 0xff)) {
            bVar5 = CanKnockOut(bankAtk_00,bankAtk);
          }
          else {
            bVar5 = Can2HKO(bankAtk_00,bankAtk);
          }
          if (((((bVar5 == 0) && ((uVar4 == 0x36 || ((byte)(uVar4 + 0x70) < 2)))) &&
               (iVar14 = CheckContact(uVar20,uVar18), iVar14 != 0)) &&
              (((gChosenMovesByBanks[uVar19] == 0 || (gBattleStruct->moveTarget[uVar19] != uVar18))
               || (gBattleMoves[uStack_40].effect != 0xbf /* EFFECT_SKILL_SWAP */)))) &&
             ((uVar15 = sub_9083c94(uVar20,uVar18,uVar19,0,0), (uVar15 & 0x29) == 0 &&
              (iVar14 = sub_90dfa24(uVar20,uVar18,uVar19), iVar14 != 0)))) {
            IncreaseDoublesDamageViabilityToScore
                      ((s16 *)auStack_1a,uVar3,0xc,bankAtk,bankAtkPartner);
          }
        }
      }
      else {
        if (bVar21 != 0x83) goto LAB_090cffc2;
        if (iVar10 == 0xb) {
LAB_090d0062:
          bVar5 = IsClassDoublesSpecific(class);
          if ((bVar5 == 0) && (bVar5 = SpecialMoveInMoveset(bankAtkPartner), bVar5 != 0)) {
            sVar1 = gBattleMons[uVar19].statStages[3];
            goto joined_r0x090d0218;
          }
        }
      }
      goto LAB_090d00e0;
    }
    if (bVar21 == 0xc6) {
      if (((iVar10 != 0x11) || (iVar12 == 2)) || (bVar5 = IsClassDoublesSpecific(class), bVar5 != 0)
         ) goto LAB_090d00e0;
      if ((bVar2 == 0xbc) && (iVar14 = sub_90745b4(uVar19), iVar14 != 0)) goto LAB_090d02f2;
      bVar5 = RealPhysicalMoveInMoveset(bankAtkPartner);
      if ((bVar5 == 0) ||
         ((0xb < gBattleMons[uVar19].statStages[0] ||
          (bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1), bVar5 != 0))))
      goto LAB_090d00e0;
      IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
      if (bVar2 == 0xa4) goto LAB_090d097c;
      if (0xa4 < bVar2) goto LAB_090d0ede;
      if (bVar2 == 0x73) goto LAB_090d07ec;
      if (bVar2 < 0x74) goto LAB_090d02a4;
      if (bVar2 == 0x89) goto LAB_090d08aa;
      if (bVar2 < 0x8a) goto LAB_090d0312;
      if (bVar2 == 0x8f) goto LAB_090d0e6c;
      if (bVar2 != 0x9a) goto LAB_090d02f2;
LAB_090d0362:
      if ((((iVar12 != 2) && (bVar5 = RealPhysicalMoveInMoveset(bankAtkPartner), bVar5 != 0)) &&
          (gBattleMons[uVar19].statStages[0] < 0xc)) &&
         (bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1), bVar5 == 0)) {
        IncreaseHelpingHandViability((s16 *)auStack_1a,uVar3);
      }
      goto LAB_090d02f2;
    }
    if (bVar21 != 0xf5) {
      if (bVar21 != 0xbf) goto LAB_090cffc2;
      bVar5 = IsClassDoublesSpecific(class);
      if (bVar5 == 0) {
        uVar15 = CheckTableForMovesEffect(uVar20,&UNK_0903f90f);
        goto LAB_090d0184;
      }
      goto LAB_090d00e0;
    }
    if (iVar11 != 0x55) {
      if (iVar12 != 2) goto LAB_090d03d6;
      goto LAB_090d00e0;
    }
    if (iVar12 != 2) {
      if ((iVar10 == 0xb) &&
         (bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1), bVar5 == 0)) {
        IncreaseViability((s16 *)auStack_1a,0x11);
      }
LAB_090d03d6:
      bVar5 = IsClassDoublesSpecific(class);
      if ((((bVar5 == 0) && ((iVar10 - 10U & 0xff) < 2)) &&
          (iVar14 = IsTrickRoomActive(), iVar14 == 0)) && (gBattleMons[uVar19].statStages[2] < 0xc))
      {
        uVar4 = data->foe1;
        uVar6 = SpeedCalc(uVar19);
        uVar7 = SpeedCalc(data->foe1);
        bVar5 = GoodIdeaToRaiseSpeedAgainst(bankAtkPartner,uVar4,6,uVar6,uVar7);
        if (bVar5 == 0) {
          uVar4 = data->foe2;
          uVar6 = SpeedCalc(uVar19);
          uVar7 = SpeedCalc(data->foe2);
          bVar5 = GoodIdeaToRaiseSpeedAgainst(bankAtkPartner,uVar4,6,uVar6,uVar7);
          if (bVar5 == 0) goto LAB_090d00e0;
        }
        bVar5 = MoveKnocksOutXHits(move_00,bankAtk,bankAtkPartner,1);
        if (bVar5 == 0) goto LAB_090d01e0;
      }
      goto LAB_090d00e0;
    }
    if (bVar2 != 0xa4) {
      if (0xa4 < bVar2) goto LAB_090d0ede;
      if (bVar2 == 0x73) goto LAB_090d07f2;
      if (0x73 < bVar2) {
        if (bVar2 != 0x89) {
          if (0x89 < bVar2) {
            if (bVar2 != 0x8f) goto LAB_090d02f2;
            goto LAB_090d0e6c;
          }
          goto LAB_090d0312;
        }
        goto LAB_090d08aa;
      }
      goto LAB_090d02a4;
    }
LAB_090d097c:
    if (((1 < (byte)(bVar21 + 0x8e)) && (iVar10 = MoveInMoveset(0x3b /* Blizzard */,uVar19), iVar10 == 0)) &&
       ((iVar10 = MoveInMoveset(0x243 /* Aurora Veil */,uVar19), iVar10 == 0 &&
        (iVar10 = MoveInMoveset(0x137 /* Weather Ball */,uVar19), iVar10 == 0)))) goto LAB_090d02f2;
LAB_090d0952:
    bVar5 = IsClassDoublesTeamSupport(uVar3);
    if (bVar5 == 0) {
      IncreaseStatusViability((s16 *)auStack_1a,uVar3,2,bankAtk,bankAtkPartner);
      goto LAB_090d02f2;
    }
  }
  IncreaseViability((s16 *)auStack_1a,0x11);
LAB_090d02f2:
  uVar3 = MathMin((int)(short)auStack_1a[0],0xff);
  return uVar3;
}
