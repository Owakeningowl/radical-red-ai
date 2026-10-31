// called_from_ai.c
// Radical Red 4.1 AI, decompiled from the ROM. Names come from CFRU where the function matched.

// ---- __udivsi3  (ROM 0x9000426)
void __udivsi3(void)

{
  udivsi();
  return;
}

// ---- sub_900042a  (ROM 0x900042a)
void sub_900042a(void)

{
  __divsi3();
  return;
}

// ---- sub_900042e  (ROM 0x900042e)
void sub_900042e(void)

{
  func_0x09000438();
  return;
}

// ---- __umodsi3  (ROM 0x900043c)
void __umodsi3(void)

{
  func_0x09000446();
  return;
}

// ---- Memset  (ROM 0x900044e)
void Memset(void)

{
  memset_();
  return;
}

// ---- AbilityBattleEffects  (ROM 0x905bf90)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

uint AbilityBattleEffects(uint param_1,uint param_2,int param_3,int param_4,ushort param_5)

{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint extraout_r1_03;
  uint extraout_r1_04;
  uint extraout_r1_05;
  undefined *puVar14;
  byte *pbVar15;
  byte bVar16;
  uint uVar17;
  undefined1 uVar18;
  ushort uVar19;
  uint uVar20;
  char *pcVar21;
  uint uVar22;
  undefined8 uVar23;
  ushort uVar24;
  uint uStack_3c;
  byte bStack_38;
  
  uStack_3c = (uint)param_5;
  if ((gBattleTypeFlags & 0x280) != 0) {
    return 0;
  }
  bVar2 = (byte)param_2;
  if (gBattlersCount <= UNK_02023d6b) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
    UNK_02023d6b = bVar2;
  }
  uVar19 = gBattleMons[UNK_02023d6b].species;
  uVar13 = gBattleMons[UNK_02023d6b].personality;
  uVar24 = gBattleMons[gBattlerTarget].species;
  uVar17 = gBattleMons[gBattlerTarget].personality;
  if (param_4 == 0) {
    gLastUsedAbility = GetBankAbility(param_2);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
  }
  else {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
    gLastUsedAbility = (byte)param_4;
  }
  if (uStack_3c == 0) {
    uStack_3c = (uint)gCurrentMove;
  }
  uVar22 = (uint)gBattleStruct->dynamicMoveType;
  if ((gBattleTypeFlags & 0xa000) == 0x8000) {
    iVar12 = GetBattlerSide(param_2);
    if (iVar12 == 1) {
      return 0;
    }
    if (gLastUsedAbility == 0x4d) {
      return 0;
    }
    if (gLastUsedAbility < 0x4e) {
      if (gLastUsedAbility == 0x24) {
        return 0;
      }
      if (gLastUsedAbility == 0x49) {
        return 0;
      }
      if (gLastUsedAbility == 0x16) {
        return 0;
      }
    }
    else {
      if (gLastUsedAbility == 0xbe) {
        return 0;
      }
      if (gLastUsedAbility < 0xbf) {
        if (gLastUsedAbility == 0x67) {
          return 0;
        }
      }
      else {
        if (gLastUsedAbility == 0xc0) {
          return 0;
        }
        if (gLastUsedAbility == 0xc5) {
          return 0;
        }
      }
    }
  }
  uVar20 = gNewBS;
  if ((*(byte *)(gNewBS + 0xe9) & 0x10) == 0) goto LAB_0905c066;
  *(byte *)(gNewBS + 0xe9) = *(byte *)(gNewBS + 0xe9) & 0xef;
  if (gLastUsedAbility == 0x67) {
LAB_0905c0f0:
    gStatuses3[param_2] = gStatuses3[param_2] | 0x80000;
  }
  else if (gLastUsedAbility < 0x68) {
    if (gLastUsedAbility == 0x16) goto LAB_0905c0f0;
    if (gLastUsedAbility == 0x24) {
      return 0;
    }
  }
  else if ((gLastUsedAbility == 0xbe) || (gLastUsedAbility == 0xc5)) goto LAB_0905c0f0;
LAB_0905c066:
  if (0x14 < param_1) {
    return 0;
  }
                      bStack_38 = (byte)param_3;
  switch(param_1) {
  case 6:
  case 8:
  case 9:
  case 10:
  case 11:
    goto sw_5c06c_6;
  case 0:
    uVar13 = gStatuses3[param_2];
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
    if ((uVar13 & 0x80000) == 0) {
      if (gLastUsedAbility == 0x9b) {
        if (gBattleMons[param_2].species == 0x260) {
          UNK_02023fdb = bVar2;
          func_0x09099924(param_2,0x2e1,1,1,0);
                              /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900079c);
          param_1 = 1;
        }
        else {
          UNK_02023fdb = bVar2;
          if (gBattleMons[param_2].species == 0x4ca) {
            func_0x09099924(param_2,0x4cb,1,1,0);
                                /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900079c);
            param_1 = 1;
          }
        }
      }
      else {
                    /* WARNING: Read-only address (ram,0x02023fd5) is written */
        if (gLastUsedAbility < 0x9c) {
          if (gLastUsedAbility == 0x46) {
LAB_0905c71c:
            uVar19 = gBattleWeather & 0x7860;
            UNK_02023fdb = bVar2;
            if ((gBattleWeather & 0x7860) == 0) {
              param_1 = sub_9350712(0x60,0x50,param_2,uVar19 + 0xb,uVar19 + 2,uVar19);
            }
          }
          else if (gLastUsedAbility < 0x47) {
            if (gLastUsedAbility == 0x16) {
              uVar13 = ~param_2 & 1;
              if ((gBattleMons[uVar13].status2 & 0x1000000) != 0) {
                uVar13 = uVar13 | 2;
                UNK_02023fdb = bVar2;
                if ((gBattleMons[uVar13].status2 & 0x1000000) != 0)
                goto sw_5c12a_1;
              }
              UNK_02023fdb = bVar2;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900059f,gBattleMons,uVar13,&BattleScriptPushCursorAndCallback);
              gBattleStruct->intimidateBank = bVar2;
              *(byte *)(gNewBS + 0xdd) = bVar2 + 1;
              param_1 = 1;
            }
            else if (gLastUsedAbility < 0x17) {
              if (gLastUsedAbility == 0xd) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                gBattleStringLoader = (undefined *)0x90e457c;
                UNK_02023fdb = bVar2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000589,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
              else if (gLastUsedAbility < 0xe) {
                if (gLastUsedAbility == 2) {
                  uVar19 = gBattleWeather & 0x7807;
                  UNK_02023fdb = bVar2;
                  if ((gBattleWeather & 0x7807) == 0) {
                    param_1 = sub_9350712(5,0x4f,param_2,uVar19 + 10,uVar19,uVar19);
                  }
                }
                else {
                  UNK_02023fdb = bVar2;
                  if (gLastUsedAbility == 7) {
                    param_1 = sub_9350518(param_2,0x40,&UNK_082500a4);
                  }
                }
              }
              else if (gLastUsedAbility == 0xf) {
                UNK_02023fdb = bVar2;
                param_1 = sub_9350518(param_2,7,&UNK_0825009c);
              }
              else {
                UNK_02023fdb = bVar2;
                if (gLastUsedAbility == 0x11) {
                  param_1 = sub_9350518(param_2,0x88,&UNK_08250094);
                }
              }
            }
            else {
              if (gLastUsedAbility == 0x29) goto LAB_0905c3f4;
              if (gLastUsedAbility < 0x2a) {
                if (gLastUsedAbility == 0x24) {
                  UNK_02023fdb = bVar2;
                                      uVar13 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(param_2,uVar13,0,&GetBattlerPosition);
                  uVar13 = ~uVar13 & 1;
                                      iVar12 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(uVar13);
                                      iVar11 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(uVar13 + 2);
                  if ((gBattleTypeFlags & 1) == 0) {
                    pcVar21 = (char *)GetAbilityLocation(iVar12);
                    if ((*pcVar21 != '\0') && (gBattleMons[iVar12].hp != 0)) {
                      puVar8 = (undefined1 *)GetAbilityLocation(iVar12);
                      iVar11 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                      if (iVar11 == 0) {
LAB_0905cb50:
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                        gActiveBattler = (byte)iVar12;
                        goto LAB_0905cab2;
                      }
                    }
                  }
                  else {
                    pcVar21 = (char *)GetAbilityLocation(iVar12);
                    if ((*pcVar21 == '\0') || (gBattleMons[iVar12].hp == 0)) {
LAB_0905cb22:
                      pcVar21 = (char *)GetAbilityLocation(iVar12);
                      if ((*pcVar21 != '\0') && (gBattleMons[iVar12].hp != 0)) {
                        puVar8 = (undefined1 *)GetAbilityLocation(iVar12);
                        iVar6 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                        if (iVar6 == 0) goto LAB_0905cb50;
                      }
                      pcVar21 = (char *)GetAbilityLocation(iVar11);
                      if ((*pcVar21 != '\0') && (gBattleMons[iVar11].hp != 0)) {
                        puVar8 = (undefined1 *)GetAbilityLocation(iVar11);
                        iVar12 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                        if (iVar12 == 0) {
                          uStack_3c._0_1_ = (byte)iVar11;
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                          gActiveBattler = (byte)uStack_3c;
                          goto LAB_0905cab2;
                        }
                      }
                    }
                    else {
                      puVar8 = (undefined1 *)GetAbilityLocation(iVar12);
                      iVar6 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                      if (iVar6 != 0) goto LAB_0905cb22;
                      puVar8 = (undefined1 *)GetAbilityLocation(iVar11);
                      iVar6 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                      if (((iVar6 != 0) ||
                          (pcVar21 = (char *)GetAbilityLocation(iVar11), *pcVar21 == '\0')) ||
                         (gBattleMons[iVar11].hp == 0)) goto LAB_0905cb22;
                                          uVar17 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub();
                                          gActiveBattler = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub((uVar17 & 1) << 1 | uVar13);
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
LAB_0905cab2:
                      puVar8 = (undefined1 *)GetAbilityLocation(gActiveBattler);
                      iVar12 = CheckTableForAbility(*puVar8,&UNK_0900a008);
                      if (iVar12 == 0) {
                        UNK_02023d6b = bVar2;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                        puVar8 = (undefined1 *)GetAbilityLocation(gActiveBattler);
                        puVar7 = (undefined1 *)GetAbilityLocation(param_2);
                        *puVar7 = *puVar8;
                        uVar23 = GetAbilityLocation(gActiveBattler);
                        gLastUsedAbility = *(byte *)uVar23;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
                                            /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900066e,(int)((ulonglong)uVar23 >> 0x20),&gLastUsedAbility,
                                     &BattleScriptPushCursorAndCallback);
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
                        UNK_02022ab9 = 4;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                        UNK_02022aba = gActiveBattler;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
                        gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
                        UNK_02022abb = (undefined1)gBattlerPartyIndexes[gActiveBattler];
                    /* WARNING (jumptable): Read-only address (ram,0x02022abc) is written */
                    /* WARNING: Read-only address (ram,0x02022abc) is written */
                        UNK_02022abc = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
                        UNK_02022ac9 = 9;
                        UNK_02022aca = gLastUsedAbility;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
                        gBattleTextBuff2 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
                        UNK_02022acb = 0xff;
                        param_1 = 1;
                      }
                    }
                  }
                }
                else {
                  UNK_02023fdb = bVar2;
                  if (gLastUsedAbility == 0x28) {
                    param_1 = sub_9350518(param_2,0x20,&UNK_082500b4);
                  }
                }
              }
              else if (gLastUsedAbility == 0x2e) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                gBattleStringLoader = &UNK_090e45a0;
                UNK_02023fdb = bVar2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
              else if (gLastUsedAbility == 0x3b) {
                UNK_02023fdb = bVar2;
                iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
                if (iVar12 == 0) {
                  iVar12 = AbilityBattleEffects(0x13,0,0x4a,0,0);
                  if (iVar12 == 0) {
                    iVar12 = GetBankItemEffect(param_2);
                    if (iVar12 == 0x51) {
                      uVar19 = gBattleWeather & 0x7980;
                      if ((gBattleWeather & 0x7980) == 0) {
                        sVar4 = 0xd;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd5) is written */
                        gStatAnimByte = CONCAT11(UNK_02023fd5,0xd);
                        uVar5 = 0x180;
                        uVar10 = 0x51;
                        uVar24 = uVar19 + 3;
LAB_0905c7b6:
                        uVar13 = sub_9350712(uVar5,uVar10,param_2,sVar4,uVar24,uVar19);
                        if (uVar13 != 0) {
                          iVar12 = GetBankItemEffect(param_2);
                          param_1 = uVar13;
                          if (iVar12 != 0x4e) {
                            param_1 = func_0x090a42a0(param_2);
                                                /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x90012f3);
                            gBattleStruct->castformToChangeInto = (char)param_1 - 1;
                          }
                        }
                      }
                    }
                    else {
                      iVar12 = GetBankItemEffect(param_2,iVar12);
                      if (iVar12 == 0x50) {
                        uVar19 = gBattleWeather & 0x7860;
                        if ((gBattleWeather & 0x7860) == 0) {
                          sVar4 = uVar19 + 0xb;
                          uVar5 = 0x60;
                          uVar10 = 0x50;
                          uVar24 = uVar19 + 2;
                          goto LAB_0905c7b6;
                        }
                      }
                      else {
                        iVar12 = GetBankItemEffect(param_2,iVar12);
                        if (iVar12 == 0x4e) {
                          uVar19 = gBattleWeather & 0x7818;
                          if ((gBattleWeather & 0x7818) == 0) {
                            sVar4 = uVar19 + 0xc;
                            uVar5 = 0x18;
                            uVar10 = 0x4e;
                            uVar24 = uVar19 + 1;
                            goto LAB_0905c7b6;
                          }
                        }
                        else {
                          iVar12 = GetBankItemEffect(param_2,iVar12);
                          if (iVar12 == 0x4f) {
                            uVar19 = gBattleWeather & 0x7807;
                            if ((gBattleWeather & 0x7807) == 0) {
                              sVar4 = uVar19 + 10;
                              uVar5 = 5;
                              uVar10 = 0x4f;
                              uVar24 = uVar19;
                              goto LAB_0905c7b6;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              else {
                UNK_02023fdb = bVar2;
                if (gLastUsedAbility == 0x2d) {
                  uVar19 = gBattleWeather & 0x7818;
                  if ((gBattleWeather & 0x7818) == 0) {
                    param_1 = sub_9350712(0x18,0x4e,param_2,uVar19 + 0xc,uVar19 + 1,uVar19);
                  }
                }
              }
            }
          }
          else if (gLastUsedAbility == 0x6f) {
            UNK_02023fdb = bVar2;
            if ((gBattleWeather & 0x7980) == 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
              gStatAnimByte = CONCAT11(UNK_02023fd5,0xd);
              param_1 = sub_9350712(0x180,0x51,param_2,0xd,(gBattleWeather & 0x7980) + 3,
                                    gBattleWeather & 0x7980);
            }
          }
          else if (gLastUsedAbility < 0x70) {
            if (gLastUsedAbility == 0x4d) {
LAB_0905cc1c:
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90e4629;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
            else if (gLastUsedAbility < 0x4e) {
              if (gLastUsedAbility == 0x49) goto LAB_0905cc1c;
              uVar17 = 0;
              UNK_02023fdb = bVar2;
              if (gLastUsedAbility == 0x4a) {
                for (; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
                  uVar22 = uVar17 & 0xff;
                  uVar23 = IsAbilitySuppressed(uVar22);
                  uVar13 = (uint)((ulonglong)uVar23 >> 0x20);
                  if ((int)uVar23 == 0) {
                    uVar23 = GetBankAbility(uVar22);
                    uVar13 = (uint)((ulonglong)uVar23 >> 0x20);
                    if ((int)uVar23 != 0) {
                      uVar10 = GetBankAbility(uVar22);
                      uVar23 = CheckTableForAbility(uVar10,0x900a021);
                      uVar13 = (uint)((ulonglong)uVar23 >> 0x20);
                      if ((int)uVar23 == 0) {
                        pbVar15 = (byte *)GetAbilityLocation(uVar22);
                        uVar13 = (uint)*pbVar15;
                        *(byte *)(gNewBS + uVar17 + 0x79) = *pbVar15;
                        *pbVar15 = 0;
                        *(undefined1 *)(gNewBS + uVar17 + 0x45) = 0;
                      }
                    }
                  }
                }
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                gBattleStringLoader = (undefined *)0x90e4a27;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000739,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
            }
            else if (gLastUsedAbility == 0x67) {
              uVar22 = param_2 ^ 1;
              iVar12 = gBattleMons[uVar22].statStages[1] * 2;
              UNK_02023fdb = bVar2;
                                  uVar13 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub((uint)*(byte *)(iVar12 + 0x9124898) *
                                    (uint)gBattleMons[uVar22].defense,
                                    *(undefined1 *)(iVar12 + 0x9124899));
              iVar12 = gBattleMons[uVar22].statStages[4] * 2;
              uVar17 = (uint)*(byte *)(iVar12 + 0x9124898);
                                  uVar17 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(uVar17 * gBattleMons[uVar22].spDefense,
                                    *(undefined1 *)(iVar12 + 0x9124899),uVar17,&udivsi);
              if (((gBattleTypeFlags & 1) != 0) &&
                 (uVar22 = param_2 ^ 3, gBattleMons[uVar22].hp != 0)) {
                iVar12 = gBattleMons[uVar22].statStages[1] * 2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub((uint)*(byte *)(iVar12 + 0x9124898) * (uint)gBattleMons[uVar22].defense
                             ,*(undefined1 *)(iVar12 + 0x9124899),iVar12 + 0x9124898,&udivsi);
                iVar12 = gBattleMons[uVar22].statStages[4] * 2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub((uint)*(byte *)(iVar12 + 0x9124898) *
                             (uint)gBattleMons[uVar22].spDefense,*(undefined1 *)(iVar12 + 0x9124899)
                             ,iVar12 + 0x9124898,&udivsi);
              }
              iVar12 = 4;
              if (uVar13 < uVar17) {
                iVar12 = 1;
              }
              iVar11 = param_2 * 0x58 + iVar12;
              cVar1 = (&UNK_02023be3)[iVar11 + 0x19];
              if (cVar1 < '\f') {
                (&UNK_02023be3)[iVar11 + 0x19] = cVar1 + '\x01';
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
                UNK_02022aba = (byte)iVar12;
                gStatChangeByte = UNK_02022aba | 0x10;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
                UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
                gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
                UNK_02022abb = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
                gBattleTextBuff2 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
                UNK_02022aca = 0xd2;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
                UNK_02022ac9 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
                UNK_02022acb = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
                UNK_02022acc = 0xff;
                UNK_02023d6b = bVar2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900071a,0,0xff,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
            }
            else {
              UNK_02023fdb = bVar2;
              if (gLastUsedAbility == 0x6c) {
                iVar12 = func_0x090852a4(param_2);
                if (iVar12 != 0) {
                                      /* BtlController_EmitSetMonData or ConvertIntToDecimalStringN */ stub(&gBattleTextBuff1,iVar12,0,1);
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                  gBattleStringLoader = &UNK_090e46e8;
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,extraout_r1,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                  param_1 = 1;
                }
              }
            }
          }
          else if (gLastUsedAbility == 0x91) {
            UNK_02023fdb = bVar2;
            *(undefined1 *)(uVar20 + param_2 + 0x45) = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
            gBattleStringLoader = &LAB_090e4612;
                                /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
            param_1 = 1;
          }
          else if (gLastUsedAbility < 0x92) {
            if (gLastUsedAbility == 0x84) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90e473f;
              UNK_02023fdb = bVar2;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
            else {
              UNK_02023fdb = bVar2;
              if (gLastUsedAbility == 0x85) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                gBattleStringLoader = &UNK_090e475c;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
            }
          }
          else {
            if (gLastUsedAbility == 0x99) goto LAB_0905d12a;
            if (0x99 < gLastUsedAbility) goto LAB_0905c71c;
            UNK_02023fdb = bVar2;
            if (gLastUsedAbility == 0x98) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90e45bd;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
        }
        else if (gLastUsedAbility == 0xc3) {
          UNK_02023fdb = bVar2;
          if ((gTerrainType == '\x01') && (*(char *)(uVar20 + param_2 + 0x19) == '\0')) {
            UNK_02022aba = func_0x09076762(param_2);
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
            gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
            UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
            UNK_02022abb = 0xff;
            *(byte *)(gNewBS + param_2 + 0x19) = UNK_02022aba;
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
            gBattleStringLoader = (undefined *)0x90e4aed;
                                /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,extraout_r1_01,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
            param_1 = 1;
          }
        }
        else if (gLastUsedAbility < 0xc4) {
          if (gLastUsedAbility == 0xb1) {
LAB_0905c3f4:
            UNK_02023fdb = bVar2;
            param_1 = sub_9350518(param_2,0x10,&UNK_082500ac);
          }
          else if (gLastUsedAbility < 0xb2) {
            if (gLastUsedAbility == 0xa9) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = &UNK_090e4650;
              UNK_02023fdb = bVar2;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
            else if (gLastUsedAbility < 0xaa) {
              if (gLastUsedAbility == 0xa6) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                gBattleStringLoader = (undefined *)0x90e470f;
                UNK_02023fdb = bVar2;
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                param_1 = 1;
              }
              else {
                UNK_02023fdb = bVar2;
                if ((gLastUsedAbility == 0xa8) && ((gBattleMons[param_2].status2 & 0x200000) == 0))
                {
                  if (gBattleMons[param_2].species == 0x3c3) {
                    if ((0x13 < gBattleMons[param_2].level) &&
                       (gBattleMons[param_2].maxHP >> 2 < gBattleMons[param_2].hp)) {
                      func_0x09099924(param_2,0x417,0,1,0);
                      puVar14 = &UNK_0900077e;
                      goto LAB_0905c392;
                    }
                  }
                  else if ((gBattleMons[param_2].species == 0x417) &&
                          ((gBattleMons[param_2].level < 0x14 ||
                           (gBattleMons[param_2].hp <= gBattleMons[param_2].maxHP >> 2)))) {
                    func_0x09099924(param_2,0x3c3,0,1,0);
                    puVar14 = &UNK_09000784;
LAB_0905c392:
                                        /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(puVar14);
                    param_1 = 1;
                  }
                  if (gBattleMons[param_2].species == 0x50c) {
                    if ((0x13 < gBattleMons[param_2].level) &&
                       (gBattleMons[param_2].maxHP >> 2 < gBattleMons[param_2].hp)) {
                      func_0x09099924(param_2,0x50d,1,1,0);
                                          /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(&UNK_0900077e);
                      param_1 = param_1 + 1 & 0xff;
                    }
                  }
                  else if ((gBattleMons[param_2].species == 0x50d) &&
                          ((gBattleMons[param_2].level < 0x14 ||
                           (gBattleMons[param_2].hp <= gBattleMons[param_2].maxHP >> 2)))) {
                    func_0x09099924(param_2,0x50c,1,1,0);
                                        /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(&UNK_09000784);
                    param_1 = param_1 + 1 & 0xff;
                  }
                }
              }
            }
            else if (gLastUsedAbility == 0xaa) {
              UNK_02023fdb = bVar2;
              if ((gBattleMons[param_2].status2 & 0x200000) == 0) {
                if ((gBattleMons[param_2].species == 0x3df) &&
                   (gBattleMons[param_2].hp <= gBattleMons[param_2].maxHP >> 1)) {
                  puVar9 = (undefined4 *)GetBankPartyData(param_2);
                                      uVar3 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(*puVar9,7);
                  func_0x09099924(param_2,uVar3,0,1,0);
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900078a);
                  param_1 = 1;
                }
                else if ((gBattleMons[param_2].species - 0x429 < 7) &&
                        (gBattleMons[param_2].maxHP >> 1 < gBattleMons[param_2].hp)) {
                  func_0x09099924(param_2,0x3df,0,1,0);
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000790);
                  param_1 = 1;
                }
              }
            }
            else {
              UNK_02023fdb = bVar2;
              if (gLastUsedAbility == 0xaf) goto LAB_0905c3f4;
            }
          }
          else if (gLastUsedAbility == 0xb7) {
            UNK_02023fdb = bVar2;
            param_1 = sub_93505ac(3,0x29,param_2);
          }
          else if (gLastUsedAbility < 0xb8) {
            if (gLastUsedAbility == 0xb5) {
LAB_0905d12a:
              UNK_02023fdb = bVar2;
              param_1 = sub_93505ac(1,0x27,param_2);
            }
            else {
              UNK_02023fdb = bVar2;
              if (gLastUsedAbility == 0xb6) {
                param_1 = sub_93505ac(2,0x28,param_2);
              }
            }
          }
          else if (gLastUsedAbility == 0xbe) {
            UNK_02023fdb = bVar2;
                                uVar17 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(param_2,uVar13,0,&GetBattlerSide);
            uVar22 = (uVar17 ^ 1) & 0xff;
            uVar13 = (uVar17 ^ 3) & 0xff;
            if (gForceSwitchHelper == '\x02') {
              uVar20 = (*(byte *)(gNewBS + 0xe5) & 0xf) >> 2;
              if ((gBattleTypeFlags & 1) != 0) {
                if (uVar13 == uVar20) {
                  uVar13 = uVar22;
                  goto LAB_0905cd30;
                }
                if (uVar22 != uVar20) goto LAB_0905ce0c;
                goto LAB_0905cd3c;
              }
              if (uVar22 != uVar20) goto LAB_0905ce0c;
            }
            else {
              if (uVar17 != 0xfe) {
LAB_0905ce0c:
                if ((gBattleMons[uVar22].hp != 0) && (gBattleMons[uVar22].item != 0)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d68) is written */
                    /* WARNING: Read-only address (ram,0x02023d68) is written */
                  uStack_3c._0_1_ = (byte)(uVar17 ^ 1);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6e) is written */
                    /* WARNING: Read-only address (ram,0x02023d6e) is written */
                  gEffectBank = (byte)uStack_3c;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                  gBattleStringLoader = &UNK_090e47da;
                  gLastUsedItem = gBattleMons[uVar22].item;
                  UNK_02023fdb = bVar2;
                  uVar10 = GetBankItemEffect(uVar22);
                  func_0x09073958(uVar22,uVar10);
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000699);
                  param_1 = 1;
                  goto sw_5c12a_1;
                }
              }
LAB_0905cd30:
              if ((int)(gBattleTypeFlags << 0x1f) < 0) {
LAB_0905cd3c:
                if (gBattleMons[uVar13].hp != 0) {
                  if (gBattleMons[uVar13].item != 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d68) is written */
                    /* WARNING: Read-only address (ram,0x02023d68) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6e) is written */
                    /* WARNING: Read-only address (ram,0x02023d6e) is written */
                    gEffectBank = (undefined1)uVar13;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                    gBattleStringLoader = &UNK_090e47da;
                    gLastUsedItem = gBattleMons[uVar13].item;
                    UNK_02023fdb = bVar2;
                    uVar10 = GetBankItemEffect(uVar13);
                    func_0x09073958(uVar13,uVar10);
                                        /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754);
                    param_1 = 1;
                  }
                }
              }
            }
          }
          else {
            if (gLastUsedAbility == 0xc0) goto LAB_0905cc1c;
            UNK_02023fdb = bVar2;
            if (gLastUsedAbility == 0xb8) {
              param_1 = sub_93505ac(4,0x2a,param_2);
            }
          }
        }
        else if (gLastUsedAbility == 0xe7) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = (undefined *)0x90e47a1;
          UNK_02023fdb = bVar2;
                              /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
          param_1 = 1;
        }
        else if (gLastUsedAbility < 0xe8) {
          if (gLastUsedAbility == 0xd4) {
            UNK_02023fdb = bVar2;
            if ((gBattleWeather & 0x5000) == 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
              gBattleWeather = 0x1005;
                    /* WARNING (jumptable): Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
              UNK_02023f48 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
              gStatAnimByte = CONCAT11(UNK_02023fd5,10);
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90e480b;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e87) is written */
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
              UNK_02023e87 = 4;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000563,0x1005,4,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
          else if (gLastUsedAbility < 0xd5) {
            if (gLastUsedAbility == 0xc5) {
              UNK_02023fdb = bVar2;
              iVar12 = sub_9074a88(param_2,0);
              if (iVar12 != 0) {
                uVar10 = sub_9074a2c(param_2);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                gBattlerTarget = (byte)uVar10;
                UNK_02023d6b = bVar2;
                func_0x090a117c(param_2,uVar10);
                                    /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x90006f0);
                param_1 = 1;
              }
            }
            else {
              UNK_02023fdb = bVar2;
              if ((gLastUsedAbility == 0xcd) && ((gBattleMons[param_2].status2 & 0x200000) == 0)) {
                if (gBattleMons[param_2].species == 0x1da) {
                  iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
                  if ((iVar12 == 0) && ((gBattleWeather & 0x860) != 0)) {
                    iVar12 = GetBankItemEffect(param_2);
                    if (iVar12 != 0x88) {
                      func_0x09099924(param_2,0x2ef,0,0,0);
                                          /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900079c);
                      param_1 = 1;
                    }
                  }
                }
                else if (gBattleMons[param_2].species == 0x2ef) {
                  iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
                  if ((iVar12 == 0) && ((gBattleWeather & 0x860) != 0)) {
                    iVar12 = GetBankItemEffect(param_2);
                    if (iVar12 != 0x88) goto sw_5c12a_1;
                  }
                  func_0x09099924(param_2,0x1da,0,0,0);
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900079c);
                  param_1 = 1;
                }
              }
            }
          }
          else if (gLastUsedAbility == 0xd6) {
            UNK_02023fdb = bVar2;
            if ((gBattleWeather & 0x6000) == 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
              gBattleWeather = 0x2000;
                    /* WARNING (jumptable): Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
              UNK_02023f48 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
              gStatAnimByte = CONCAT11(UNK_02023fd5,0x26);
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = &UNK_090e484c;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e87) is written */
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
              UNK_02023e87 = 4;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000563,0x2000,4,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
          else if (gLastUsedAbility < 0xd6) {
            UNK_02023fdb = bVar2;
            if ((gBattleWeather & 0x4800) == 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
              gBattleWeather = 0x860;
                    /* WARNING (jumptable): Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
              UNK_02023f48 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
              gStatAnimByte = CONCAT11(UNK_02023fd5,0xb);
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90e4827;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e87) is written */
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
              UNK_02023e87 = 4;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000563,0x860,4,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
          else {
            UNK_02023fdb = bVar2;
            if (gLastUsedAbility == 0xe5) {
              iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
              if ((iVar12 == 0) && ((gBattleWeather & 0x860) != 0)) {
                iVar12 = GetBankItemEffect(param_2);
                if ((iVar12 != 0x88) && (*(char *)(gNewBS + param_2 + 0x19) == '\0')) {
                  UNK_02022aba = func_0x09076762(param_2);
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
                  gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
                  UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
                  UNK_02022abb = 0xff;
                  *(byte *)(gNewBS + param_2 + 0x19) = UNK_02022aba;
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                  gBattleStringLoader = (undefined *)0x90e4ab3;
                                      /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,extraout_r1_00,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
                  param_1 = 1;
                }
              }
            }
          }
        }
        else if (gLastUsedAbility == 0xf2) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = &LAB_090e4684;
          UNK_02023fdb = bVar2;
                              /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
          param_1 = 1;
        }
        else if (gLastUsedAbility < 0xf3) {
          if (gLastUsedAbility == 0xee) {
            UNK_02023fdb = bVar2;
            if (gBattleMons[param_2].statStages[0] < 0xc) {
              UNK_02023d6b = bVar2;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                                  iVar12 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(param_2,uVar13,0x58,&GetBattlerSide);
              *(byte *)(gNewBS + iVar12 + 0x17) =
                   (byte)*(undefined4 *)
                          (&gBitTable + (uint)gBattlerPartyIndexes[UNK_02023d6b] * 4) |
                   *(byte *)(uVar20 + iVar12 + 0x17);
              gBattleMons[param_2].statStages[0] = gBattleMons[param_2].statStages[0] + 1;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
              gStatChangeByte = 0x11;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
              UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
              gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
              UNK_02022aba = 1;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
              UNK_02022abb = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
              gBattleTextBuff2 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
              UNK_02022aca = 0xd2;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
              UNK_02022ac9 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
              UNK_02022acb = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
              UNK_02022acc = 0xff;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900071a,0,0xff,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
          else {
            UNK_02023fdb = bVar2;
            if ((gLastUsedAbility == 0xef) && (gBattleMons[param_2].statStages[1] < 0xc)) {
              UNK_02023d6b = bVar2;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                                  iVar12 = /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(param_2,uVar13,0x58,&GetBattlerSide);
              *(byte *)(gNewBS + iVar12 + 0x17) =
                   (byte)*(undefined4 *)
                          (&gBitTable + (uint)gBattlerPartyIndexes[UNK_02023d6b] * 4) |
                   *(byte *)(uVar20 + iVar12 + 0x17);
              gBattleMons[param_2].statStages[1] = gBattleMons[param_2].statStages[1] + 1;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
              gStatChangeByte = 0x12;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
              UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
              UNK_02022aba = 2;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
              gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
              UNK_02022abb = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
              gBattleTextBuff2 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
              UNK_02022aca = 0xd2;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
              UNK_02022ac9 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
              UNK_02022acb = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
              UNK_02022acc = 0xff;
                                  /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x900071a,0,0xff,&BattleScriptPushCursorAndCallback);
              param_1 = 1;
            }
          }
        }
        else if (gLastUsedAbility == 0xfd) {
          UNK_02023fdb = bVar2;
          func_0x090749f8(0);
          func_0x090749f8(1);
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = (undefined *)0x90e49ff;
                              /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,extraout_r1_02,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
          param_1 = 1;
        }
        else {
          if (gLastUsedAbility == 0xff) goto LAB_0905c11e;
          UNK_02023fdb = bVar2;
          if (gLastUsedAbility == 0xf4) {
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
            gBattleStringLoader = &UNK_090e46b4;
                                /* BattleScriptPushCursorAndCallback or BattleScriptPushCursor or Random2 */ stub(0x9000754,uVar13,&gBattleStringLoader,&BattleScriptPushCursorAndCallback);
            param_1 = 1;
          }
        }
      }
    }
    else {
      if (gLastUsedAbility != 0xff) {
        UNK_02023fdb = bVar2;
        return 0;
      }
LAB_0905c11e:
      UNK_02023fdb = bVar2;
      iVar12 = GetCurrentWeather();
      if (iVar12 - 1U < 0xd) {
                            switch(iVar12 - 1U) {
        case 2:
        case 4:
          if ((gBattleWeather & 0x1007) == 0) {
            gBattleWeather = 5;
LAB_0905c676:
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
            uVar18 = 10;
LAB_0905c67a:
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd5) is written */
            gStatAnimByte = CONCAT11(UNK_02023fd5,uVar18);
            if (((int)(gBattleTypeFlags << 5) < 0) && ((_UNK_0203e044 & 0x1f0) != 0)) {
              gBattleWeather = gBattleWeather | 0x4000;
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
            }
            UNK_02023e87 = GetCurrentWeather();
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
            BattleScriptPushCursorAndCallback(0x9000550);
            param_1 = 1;
          }
          break;
        case 12:
          if ((gBattleWeather & 0x1007) == 0) {
            gBattleWeather = 6;
            goto LAB_0905c676;
          }
          break;
        case 7:
          if ((gBattleWeather & 0x18) == 0) {
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
            gBattleWeather = 0x18;
            uVar18 = 0xc;
            goto LAB_0905c67a;
          }
          break;
        case 0:
        case 11:
          if ((gBattleWeather & 0x860) == 0) {
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
            gBattleWeather = 0x60;
            uVar18 = 0xb;
            goto LAB_0905c67a;
          }
          break;
        case 3:
        case 6:
          if ((gBattleWeather & 0x180) == 0) {
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
            gBattleWeather = 0x180;
            uVar18 = 0xd;
            goto LAB_0905c67a;
          }
        }
      }
    }
sw_5c12a_1:
    if (gLastUsedAbility != 0x24) {
      if (gLastUsedAbility < 0x25) {
        if (gLastUsedAbility != 0) goto LAB_0905d2c0;
      }
      else if ((gLastUsedAbility != 0xcd) && (gLastUsedAbility != 0xff)) {
LAB_0905d2c0:
        gStatuses3[param_2] = gStatuses3[param_2] | 0x80000;
      }
    }
    goto LAB_0905c192;
  case 1:
    uVar13 = (uint)gBattleMons[param_2].hp;
    if (uVar13 == 0) {
      return 0;
    }
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
    if (gLastUsedAbility == 0x62) {
      gActiveBattler = bVar2;
      UNK_02023d6b = bVar2;
      UNK_02023fdb = bVar2;
      iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
      if (iVar12 != 0) {
        return 0;
      }
      iVar12 = GetBankItemEffect(param_2);
      if (iVar12 == 0x88) {
        return 0;
      }
      if (((gBattleWeather & 0x1007) == 0) ||
         (gBattleMons[param_2].hp == gBattleMons[param_2].maxHP)) {
        if ((gBattleWeather & 0x860) == 0) {
          return 0;
        }
        uVar13 = GetBaseMaxHP(param_2);
        gBattleMoveDamage = MathMax(1,uVar13 >> 3 & 0xffff);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
        uVar10 = 0x900085c;
      }
      else {
        uVar13 = GetBaseMaxHP(param_2);
        gBattleMoveDamage = MathMax(1,uVar13 >> 3 & 0xffff);
        gBattleMoveDamage = -gBattleMoveDamage;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
        uVar10 = 0x9000837;
      }
LAB_0905d4cc:
      BattleScriptPushCursorAndCallback(uVar10);
    }
    else {
      if (0x62 < gLastUsedAbility) {
        if (gLastUsedAbility != 0xa0) {
          if (gLastUsedAbility < 0xa1) {
            if (gLastUsedAbility == 0x6b) {
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
              if (iVar12 != 0) {
                return 0;
              }
              if ((gBattleWeather & 0x1007) == 0) {
                return 0;
              }
              iVar12 = GetBankItemEffect(param_2);
              if (iVar12 == 0x88) {
                return 0;
              }
              if ((gBattleMons[param_2].status1 & 0xff) == 0) {
                return 0;
              }
              goto LAB_0905d526;
            }
            if (gLastUsedAbility != 0x91) {
              if (gLastUsedAbility != 0x69) {
                gActiveBattler = bVar2;
                UNK_02023d6b = bVar2;
                UNK_02023fdb = bVar2;
                return 0;
              }
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
              if (iVar12 != 0) {
                return 0;
              }
              if ((gBattleWeather & 0x180) == 0) {
                return 0;
              }
              if (gBattleMons[param_2].hp == gBattleMons[param_2].maxHP) {
                return 0;
              }
              goto LAB_0905d432;
            }
            pcVar21 = (char *)(uVar20 + param_2 + 0x45);
            cVar1 = *pcVar21;
            if (cVar1 == '\0') {
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              return 0;
            }
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            *pcVar21 = cVar1 + -1;
            if (cVar1 != '\x01') {
              return 0;
            }
            uVar10 = 0x9000754;
                    /* WARNING (jumptable): Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
            gBattleStringLoader = &UNK_090e4888;
          }
          else if (gLastUsedAbility == 0xe1) {
            if ((&UNK_093c001a)
                [(uint)*(ushort *)(uVar20 + (gBattlerPartyIndexes[param_2] + 0x7c) * 2 + 6) * 0x2c]
                != '\x05') {
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              return 0;
            }
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
            if (((iVar12 != 0) || ((gBattleWeather & 0x860) == 0)) ||
               (iVar12 = GetBankItemEffect(param_2), iVar12 == 0x88)) {
              uVar10 = Random2();
              __umodsi3(uVar10,100);
              if ((extraout_r1_04 & 0xffff) < 0x32) {
                return 0;
              }
            }
            uVar10 = 0x9000a08;
          }
          else if (gLastUsedAbility == 0xeb) {
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            if (gBattleMons[param_2].maxHP == uVar13) {
              return 0;
            }
LAB_0905d432:
            uVar13 = GetBaseMaxHP(param_2);
            gBattleMoveDamage = MathMax(1,uVar13 >> 4 & 0xffff);
            gBattleMoveDamage = -gBattleMoveDamage;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
            uVar10 = 0x9000837;
          }
          else {
            if (gLastUsedAbility != 0xce) {
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              return 0;
            }
            uVar13 = ~param_2 & 1;
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            if ((gBattleMons[uVar13].status1 & 7) == 0) {
              iVar12 = GetBankAbility(uVar13);
              if (((iVar12 != 0xe7) && ((gBattleMons[uVar13 | 2].status1 & 7) == 0)) &&
                 (iVar12 = GetBankAbility(((param_2 & 1) == 0) + '\x02'), iVar12 != 0xe7)) {
                return 0;
              }
            }
            uVar10 = 0x90008ec;
          }
          goto LAB_0905d4cc;
        }
        uVar17 = (uint)(gBattleMons[param_2].maxHP >> 1);
        if (((gStatuses3[param_2] & 0x11000000) == 0) &&
           (uVar22 = *(uint *)(uVar20 + (param_2 + 0x52) * 4 + 4), 0 < (int)uVar22)) {
          if (uVar17 < uVar13) goto LAB_0905d816;
          gActiveBattler = bVar2;
          UNK_02023d6b = bVar2;
          if ((int)(uVar13 + uVar22) <= (int)uVar17) goto LAB_0905d7f4;
LAB_0905d7d6:
          UNK_02023fdb = bVar2;
          UNK_0203e033 = bVar2;
          BattleScriptPushCursorAndCallback(0x90007c3,&gBattleScripting,uVar22,&BattleScriptPushCursorAndCallback);
        }
        else {
          if (uVar13 <= uVar17) {
LAB_0905d7f4:
            if (((int)((uint)(byte)gDisableStructs[param_2].field_0x18 << 0x1e) < 0) &&
               ((gStatuses3[param_2] & 0x11000000) == 0)) {
              uVar22 = (byte)gDisableStructs[param_2].field_0x18 & 0xfffffffd;
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              gDisableStructs[param_2].field_0x18 = (char)uVar22;
                    /* WARNING (jumptable): Read-only address (ram,0x0203e033) is written */
                    /* WARNING: Read-only address (ram,0x0203e033) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
              goto LAB_0905d7d6;
            }
          }
LAB_0905d816:
          param_1 = 0;
          gActiveBattler = bVar2;
          UNK_02023d6b = bVar2;
          UNK_02023fdb = bVar2;
        }
        *(undefined4 *)(gNewBS + (param_2 + 0x52) * 4 + 4) = 0;
        goto LAB_0905c192;
      }
      if (gLastUsedAbility == 0x35) {
        gActiveBattler = bVar2;
        UNK_02023d6b = bVar2;
        UNK_02023fdb = bVar2;
        iVar12 = func_0x090749a8(param_2);
        if (iVar12 == 0xff) {
          return 0;
        }
        func_0x09074950();
        if (gBattleStruct->usedHeldItems[iVar12] == 0) {
          return 0;
        }
        gBattleMons[param_2].item = gBattleStruct->usedHeldItems[iVar12];
        BtlController_EmitSetMonData(0,2,0,2,param_2 * 0x58 + 0x2023c12);
        MarkBufferBankForExecution(param_2);
        gLastUsedItem = gBattleStruct->usedHeldItems[iVar12];
                    /* WARNING (jumptable): Read-only address (ram,0x02023d68) is written */
                    /* WARNING: Read-only address (ram,0x02023d68) is written */
        gBattleStruct->usedHeldItems[iVar12] = 0;
        uVar10 = GetBankItemEffect(param_2);
        func_0x09073958(param_2,uVar10);
        uVar10 = 0x9000a32;
        goto LAB_0905d4cc;
      }
      if (gLastUsedAbility < 0x36) {
        if (gLastUsedAbility == 3) {
          if (0xb < gBattleMons[param_2].statStages[2]) {
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gDisableStructs[param_2].isFirstTurn == 2) {
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            return 0;
          }
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
          gStatChangeByte = 0x13;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
          gStatAnimByte = 0x11;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
          UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
          gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
          UNK_02022aba = gLastUsedAbility;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
          UNK_02022abb = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
          gBattleTextBuff2 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
          UNK_02022aca = 0xd2;
          gActiveBattler = bVar2;
          UNK_02023d6b = bVar2;
          UNK_02023fdb = bVar2;
          gBattleMons[param_2].statStages[2] = gBattleMons[param_2].statStages[2] + 1;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
          UNK_02022ac9 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
          UNK_02022acb = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
          UNK_02022acc = 0xff;
          uVar10 = 0x900071a;
          goto LAB_0905d4cc;
        }
        if (gLastUsedAbility != 0x2c) {
          gActiveBattler = bVar2;
          UNK_02023d6b = bVar2;
          UNK_02023fdb = bVar2;
          return 0;
        }
        gActiveBattler = bVar2;
        UNK_02023d6b = bVar2;
        UNK_02023fdb = bVar2;
        iVar12 = AbilityBattleEffects(0x13,0,0xd,0,0);
        if (iVar12 != 0) {
          return 0;
        }
        if ((gBattleWeather & 0x1007) == 0) {
          return 0;
        }
        iVar12 = GetBankItemEffect(param_2);
        if (iVar12 == 0x88) {
          return 0;
        }
        if (gBattleMons[param_2].hp == gBattleMons[param_2].maxHP) {
          return 0;
        }
        BattleScriptPushCursorAndCallback(0x9000837,0x58,gBattleMons[param_2].hp,&BattleScriptPushCursorAndCallback);
        uVar13 = GetBaseMaxHP(param_2);
        gBattleMoveDamage = MathMax(1,uVar13 >> 4 & 0xffff);
        gBattleMoveDamage = -gBattleMoveDamage;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
      }
      else {
        if (gLastUsedAbility != 0x3b) {
          if (gLastUsedAbility != 0x3d) {
            if (gLastUsedAbility != 0x36) {
              gActiveBattler = bVar2;
              UNK_02023d6b = bVar2;
              UNK_02023fdb = bVar2;
              return 0;
            }
            bVar16 = gDisableStructs[param_2].field_0x18;
            if ((gBattleMons[param_2].status1 & 7) == 0) {
              bVar16 = bVar16 & 0xfe | bVar16 & 1 ^ 1;
            }
            else {
              bVar16 = bVar16 & 0xfe;
            }
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            gDisableStructs[param_2].field_0x18 = bVar16;
            return 0;
          }
          if ((gBattleMons[param_2].status1 & 0xff) == 0) {
            gActiveBattler = bVar2;
            UNK_02023d6b = bVar2;
            UNK_02023fdb = bVar2;
            return 0;
          }
          gActiveBattler = bVar2;
          UNK_02023d6b = bVar2;
          UNK_02023fdb = bVar2;
          uVar10 = Random2();
          __umodsi3(uVar10,3);
          if ((extraout_r1_03 & 0xffff) != 0) {
            return 0;
          }
LAB_0905d526:
          func_0x09074af4(param_2);
          uVar10 = 0x9000765;
          goto LAB_0905d4cc;
        }
        gActiveBattler = bVar2;
        UNK_02023d6b = bVar2;
        UNK_02023fdb = bVar2;
        param_1 = func_0x090a42a0(param_2);
        if (param_1 == 0) {
          return 0;
        }
        BattleScriptPushCursorAndCallback(0x90012f3);
        gBattleStruct->castformToChangeInto = (char)param_1 - 1;
      }
    }
    goto LAB_0905d386;
  case 2:
    uVar13 = (uint)UNK_02023d6b;
    if (uVar13 == param_2) {
      return 0;
    }
    if (gLastUsedAbility == 0x72) {
      puVar14 = &UNK_0903ffd8;
LAB_0905d872:
      iVar12 = CheckTableForMove(uStack_3c,puVar14);
LAB_0905d880:
      if (iVar12 == 0) {
        return 0;
      }
LAB_0905d888:
      uVar13 = 1;
    }
    else {
      if (gLastUsedAbility < 0x73) {
        if (gLastUsedAbility == 0x2b) {
          iVar12 = sub_9073ba8(uStack_3c);
          goto LAB_0905d880;
        }
        if (gLastUsedAbility != 0x6e) {
          return 0;
        }
        iVar12 = CalcMoveSplit(uVar13,uStack_3c);
        if (iVar12 != 2) {
          return 0;
        }
        if ((gBattleMoves[uStack_3c].target & 0xf7) != 0) {
          return 0;
        }
        goto LAB_0905d888;
      }
      if (gLastUsedAbility != 0xdd) {
        if (gLastUsedAbility != 0xe2) {
          if (gLastUsedAbility != 0x74) {
            return 0;
          }
          puVar14 = &UNK_0903ff64;
          goto LAB_0905d872;
        }
        if (-1 < (int)(gBattleTypeFlags << 0x1f)) {
          return 0;
        }
        if (uVar13 != (param_2 ^ 2)) {
          return 0;
        }
        goto LAB_0905d888;
      }
      iVar12 = PriorityCalc(uVar13,0,uStack_3c);
      uVar13 = param_1;
      if (iVar12 < 1) {
        return 0;
      }
    }
    if ((int)(gBattleMons[UNK_02023d6b].status2 << 0x13) < 0) {
      gHitMarker = gHitMarker | 0x800;
                    /* WARNING (jumptable): Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
    }
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
    UNK_02023fdb = bVar2;
    if (uVar13 == 1) {
LAB_0905d8b0:
      gBattlescriptCurrInstr = (undefined1 *)0x9000ae5;
      goto LAB_0905da9e;
    }
    gBattlescriptCurrInstr = (undefined1 *)0x9000a6d;
    goto LAB_0905d386;
  case 20:
    if ((param_2 ^ 2) == (uint)UNK_02023d6b) {
      return 0;
    }
    if (gLastUsedAbility != 0xdd) {
      return 0;
    }
    iVar12 = PriorityCalc((uint)UNK_02023d6b,0,uStack_3c);
    if (iVar12 < 1) {
      return 0;
    }
    if ((int)(gBattleMons[UNK_02023d6b].status2 << 0x13) < 0) {
      gHitMarker = gHitMarker | 0x800;
                    /* WARNING (jumptable): Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
    }
    gBattlescriptCurrInstr = (undefined1 *)0x9000a6d;
    UNK_02023fdb = bVar2;
    return 1;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
  case 3:
    if (uStack_3c == 0) {
      return 0;
    }
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
    if (gLastUsedAbility != 0x50) {
      if (0x50 < gLastUsedAbility) {
        if (gLastUsedAbility != 0x83) {
          if (0x83 < gLastUsedAbility) {
            if (gLastUsedAbility == 0xdf) {
              if (uVar22 != 5) {
                UNK_02023fdb = bVar2;
                return 0;
              }
            }
            else {
              if (gLastUsedAbility == 0xfe) {
                if (uVar22 != 10) {
                  UNK_02023fdb = bVar2;
                  return 0;
                }
                param_1 = 2;
                UNK_02023fdb = bVar2;
                goto LAB_0905daaa;
              }
              if (gLastUsedAbility != 0xbc) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (uVar22 != 4) {
                UNK_02023fdb = bVar2;
                return 0;
              }
            }
            goto LAB_0905da74;
          }
          if (gLastUsedAbility == 0x62) goto LAB_0905da06;
          if (gLastUsedAbility != 0x71) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (uVar22 != 0xc) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          iVar12 = VarGet(0x5119);
          if (iVar12 == 0x10) {
            return 0;
          }
          goto LAB_0905daec;
        }
        if (uVar22 != 0xb) {
          UNK_02023fdb = bVar2;
          return 0;
        }
LAB_0905da24:
        param_1 = 4;
        UNK_02023fdb = bVar2;
        goto LAB_0905daaa;
      }
      if (gLastUsedAbility == 0x10) {
        UNK_02023fdb = bVar2;
        iVar12 = CheckTableForMove(uStack_3c,&UNK_0903ff9e);
        if (iVar12 == 0) {
          return 0;
        }
LAB_0905daec:
        param_1 = 1;
        goto LAB_0905daaa;
      }
      if (0x10 < gLastUsedAbility) {
        if (gLastUsedAbility == 0x12) {
          if (uVar22 != 10) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((int)(gBattleMons[param_2].status1 << 0x1a) < 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023e87 = (gBattleResources->flags->flags[param_2] & 1) != 0;
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
          if ((int)((uint)(byte)(&UNK_02023e8e)[(uint)UNK_02023d6b * 0x10] << 0x1c) < 0) {
            gBattlescriptCurrInstr = (undefined1 *)0x9000a91;
            UNK_02023fdb = bVar2;
          }
          else {
            gBattlescriptCurrInstr = (undefined1 *)0x9000a90;
            UNK_02023fdb = bVar2;
          }
          goto LAB_0905d392;
        }
        if (gLastUsedAbility != 0x1f) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (uVar22 != 0xd) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        goto LAB_0905da24;
      }
      if (gLastUsedAbility == 10) {
        if (uVar22 != 0xd) {
          UNK_02023fdb = bVar2;
          return 0;
        }
      }
      else {
        if (gLastUsedAbility != 0xb) {
          UNK_02023fdb = bVar2;
          return 0;
        }
LAB_0905da06:
        if (uVar22 != 0xb) {
          UNK_02023fdb = bVar2;
          return 0;
        }
      }
LAB_0905da74:
      UNK_02023fdb = bVar2;
      if (gBattleMons[param_2].hp != gBattleMons[param_2].maxHP) {
        iVar12 = sub_90754f0(param_2);
        if ((iVar12 == 0) && (gLastUsedAbility != 0xdf)) {
          if ((int)((uint)(byte)(&UNK_02023e8e)[(uint)UNK_02023d6b * 0x10] << 0x1c) < 0) {
            gBattlescriptCurrInstr = (undefined1 *)0x9000ab2;
          }
          else {
            gBattlescriptCurrInstr = (undefined1 *)0x9000ab1;
          }
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
          uVar13 = GetBaseMaxHP(param_2);
          gBattleMoveDamage = MathMax(1,uVar13 >> 2 & 0xffff);
          gBattleMoveDamage = -gBattleMoveDamage;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
          goto LAB_0905da9e;
        }
      }
      if ((int)((uint)(byte)(&UNK_02023e8e)[(uint)UNK_02023d6b * 0x10] << 0x1c) < 0) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
        gBattlescriptCurrInstr = (undefined1 *)0x9000ae6;
        goto LAB_0905da9e;
      }
      goto LAB_0905d8b0;
    }
    UNK_02023fdb = bVar2;
    if (uVar22 != 0xd) {
      return 0;
    }
LAB_0905daaa:
    uVar13 = ((byte)(&UNK_02023e8e)[(uint)UNK_02023d6b * 0x10] & 0xf) >> 3;
    if (gBattleMons[param_2].statStages[param_1 - 1] < 0xc) {
      if (uVar13 == 0) {
        gBattlescriptCurrInstr = (undefined1 *)0x9000b05;
      }
      else {
        gBattlescriptCurrInstr = (undefined1 *)0x9000b06;
      }
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
      if (gLastUsedAbility == 0xfe) {
        gStatChangeByte = (byte)param_1 | 0x20;
        param_1 = 2;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
        goto LAB_0905d392;
      }
      gStatChangeByte = (byte)param_1 | 0x10;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
    }
    else if (uVar13 == 0) {
      gBattlescriptCurrInstr = (undefined1 *)0x9000ae5;
    }
    else {
      gBattlescriptCurrInstr = (undefined1 *)0x9000ae6;
    }
    param_1 = 2;
    goto LAB_0905d386;
  case 4:
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
    if (gLastUsedAbility == 0xa3) {
      if ((gMoveResultFlags & 0x29) != 0) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
         (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (UNK_02023d6b == param_2) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      UNK_02023fdb = bVar2;
      iVar12 = CheckContact(uStack_3c);
      if (iVar12 == 0) {
        return 0;
      }
      BattleScriptPushCursor();
      gBattlescriptCurrInstr = &DAT_09001318;
    }
    else if (gLastUsedAbility < 0xa4) {
      if (gLastUsedAbility == 0x6d) {
        UNK_02023fdb = bVar2;
        iVar12 = func_0x09076024();
        if ((iVar12 != 0) && (gLastUsedAbility != 0xe3)) {
          return 0;
        }
        if ((gMoveResultFlags & 0x29) != 0) {
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          return 0;
        }
        uVar13 = (uint)gBattleMons[param_2].hp;
        if (uVar13 == 0) {
          return 0;
        }
        uVar17 = (uint)(gBattleMons[param_2].maxHP >> 1);
        if (uVar17 <= uVar13) {
          return 0;
        }
        if ((int)(uVar13 + gHpDealt) <= (int)uVar17) {
          return 0;
        }
        if (0xb < gBattleMons[param_2].statStages[3]) {
          return 0;
        }
        if (0xb < gBattleMons[param_2].statStages[0]) {
          return 0;
        }
        if (0xb < gBattleMons[param_2].statStages[2]) {
          return 0;
        }
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000d81;
      }
      else if (gLastUsedAbility < 0x6e) {
        if (gLastUsedAbility == 0x23) {
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[UNK_02023d6b].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          uVar10 = GetBankPartyData(param_2);
          sVar4 = GetMonData(uVar10,0x41,0,&GetMonData);
          uVar13 = GetBaseMaxHP(UNK_02023d6b);
          gBattleMoveDamage = MathMax(1,uVar13 >> 2 & 0xffff);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
          if (sVar4 == 0x4a6) {
            UNK_02023e85 = 0x18;
          }
          else {
            if (sVar4 != 0x4a7) {
              return 0;
            }
            UNK_02023e85 = 5;
          }
                    /* WARNING (jumptable): Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
          func_0x09099924(param_2,0x471,1,0,0);
          BattleScriptPushCursor();
          gBattlescriptCurrInstr = (undefined1 *)0x9001444;
        }
        else {
          if (gLastUsedAbility < 0x24) {
            if (gLastUsedAbility == 9) {
              if (-1 < (int)(gBattleTypeFlags << 0x1c)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((gMoveResultFlags & 0x29) != 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[UNK_02023d6b].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (UNK_02023d6b == param_2) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              UNK_02023fdb = bVar2;
              iVar12 = CheckContact(uStack_3c);
              if (iVar12 == 0) {
                return 0;
              }
              iVar12 = CanBeParalyzed(UNK_02023d6b,1);
              if (iVar12 == 0) {
                return 0;
              }
              uVar10 = Random2();
              iVar12 = umodsi(uVar10,3);
              if (iVar12 != 0) {
                return 0;
              }
              UNK_02023e85 = 0x45;
            }
            else {
              if (gLastUsedAbility != 0x1b) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (-1 < (int)(gBattleTypeFlags << 0x1c)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((gMoveResultFlags & 0x29) != 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[UNK_02023d6b].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (UNK_02023d6b == param_2) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              UNK_02023fdb = bVar2;
              iVar12 = CheckContact(uStack_3c);
              if (iVar12 == 0) {
                return 0;
              }
              iVar12 = IsAffectedByPowder(UNK_02023d6b);
              if (iVar12 == 0) {
                return 0;
              }
              uVar10 = Random2(iVar12);
              __umodsi3(uVar10,10);
              if ((extraout_r1_05 & 0xffff) != 0) {
                return 0;
              }
              do {
                bVar2 = Random2();
                UNK_02023e85 = bVar2 & 3;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
              } while (UNK_02023e85 == 0);
              if (UNK_02023e85 == 2) {
                iVar12 = CanBePoisoned(UNK_02023d6b,param_2,1);
              }
              else if (UNK_02023e85 == 3) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
                UNK_02023e85 = 5;
                iVar12 = CanBeParalyzed(UNK_02023d6b,1);
              }
              else {
                iVar12 = sub_90763c6(UNK_02023d6b,1);
              }
              if (iVar12 == 0) {
                UNK_02023e85 = 0;
                return 0;
              }
              UNK_02023e85 = UNK_02023e85 | 0x40;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
            }
          }
          else {
            if (gLastUsedAbility == 0x38) {
              if ((gMoveResultFlags & 0x29) != 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[UNK_02023d6b].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[param_2].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (UNK_02023d6b == param_2) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              UNK_02023fdb = bVar2;
              iVar12 = CheckContact(uStack_3c);
              if (iVar12 == 0) {
                return 0;
              }
              uVar10 = Random2();
              iVar12 = umodsi(uVar10,3);
              if (iVar12 != 0) {
                return 0;
              }
              iVar12 = GetBankAbility(UNK_02023d6b);
              if (iVar12 == 0xc) {
                return 0;
              }
              iVar12 = GetBankAbility(UNK_02023d6b);
              if (iVar12 == 0xc9) {
                return 0;
              }
              if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
                 (iVar12 = GetBankAbility(UNK_02023d6b ^ 2), iVar12 == 0xc9)) {
                return 0;
              }
              iVar11 = GetGenderFromSpeciesAndPersonality(uVar19,uVar13);
              iVar12 = GetGenderFromSpeciesAndPersonality(uVar24,uVar17);
              if (iVar11 == iVar12) {
                return 0;
              }
              if ((gBattleMons[UNK_02023d6b].status2 & 0xf0000) != 0) {
                return 0;
              }
              iVar12 = GetGenderFromSpeciesAndPersonality(uVar19,uVar13);
              if (iVar12 == 0xff) {
                return 0;
              }
              iVar12 = GetGenderFromSpeciesAndPersonality(uVar24,uVar17);
              if (iVar12 == 0xff) {
                return 0;
              }
              gBattleMons[UNK_02023d6b].status2 =
                   *(int *)(&gBitTable + (uint)gBattlerTarget * 4) << 0x10 |
                   gBattleMons[UNK_02023d6b].status2;
              BattleScriptPushCursor();
              gBattlescriptCurrInstr = (undefined1 *)0x9000bf1;
              goto LAB_0905da9e;
            }
            if (gLastUsedAbility == 0x69) {
              if (-1 < (int)(gBattleTypeFlags << 0x1c)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((gMoveResultFlags & 0x29) != 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[UNK_02023d6b].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (UNK_02023d6b == param_2) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              UNK_02023fdb = bVar2;
              iVar12 = CheckContact(uStack_3c);
              if (iVar12 == 0) {
                return 0;
              }
              iVar12 = CanBeFrozen(UNK_02023d6b,1);
              if (iVar12 == 0) {
                return 0;
              }
              uVar10 = Random2();
              iVar12 = umodsi(uVar10,3);
              if (iVar12 != 0) {
                return 0;
              }
              UNK_02023e85 = 0x44;
            }
            else {
              if (gLastUsedAbility != 0x31) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (-1 < (int)(gBattleTypeFlags << 0x1c)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((gMoveResultFlags & 0x29) != 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (gBattleMons[UNK_02023d6b].hp == 0) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              if (UNK_02023d6b == param_2) {
                UNK_02023fdb = bVar2;
                return 0;
              }
              UNK_02023fdb = bVar2;
              iVar12 = CheckContact(uStack_3c);
              if (iVar12 == 0) {
                return 0;
              }
              iVar12 = CanBeBurned(UNK_02023d6b,1);
              if (iVar12 == 0) {
                return 0;
              }
              uVar10 = Random2();
              iVar12 = umodsi(uVar10,3);
              if (iVar12 != 0) {
                return 0;
              }
              UNK_02023e85 = 0x43;
            }
          }
          BattleScriptPushCursor();
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
          gBattlescriptCurrInstr = (undefined1 *)0x9000b44;
          gHitMarker = gHitMarker | 0x2000;
                    /* WARNING (jumptable): Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
        }
      }
      else if (gLastUsedAbility == 0x79) {
        if ((gMoveResultFlags & 0x29) != 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        UNK_02023fdb = bVar2;
        iVar12 = CheckContact(uStack_3c,UNK_02023d6b);
        if (iVar12 == 0) {
          return 0;
        }
        uVar13 = (uint)UNK_02023d6b;
        if (gBattleMons[uVar13].hp == 0) {
          return 0;
        }
        if (uVar13 == param_2) {
          return 0;
        }
        if ((gBattleMons[uVar13].statStages[2] < 1) || (iVar12 = GetBankAbility(), iVar12 == 0xbf))
        {
          iVar12 = GetBankAbility(UNK_02023d6b);
          if (iVar12 != 0xbf) {
            return 0;
          }
          if (0xb < gBattleMons[UNK_02023d6b].statStages[2]) {
            return 0;
          }
        }
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
        gStatChangeByte = 0x93;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000e78;
      }
      else if (gLastUsedAbility < 0x7a) {
        if (gLastUsedAbility == 0x77) {
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[UNK_02023d6b].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          iVar12 = GetBankAbility();
          if (iVar12 == 0x73) {
            return 0;
          }
          iVar12 = CheckContact(uStack_3c,UNK_02023d6b);
          if (iVar12 == 0) {
            return 0;
          }
          if (gBattleMons[param_2].hp != 0) {
            return 0;
          }
          iVar12 = AbilityBattleEffects(0x13,0,6,0,0);
          if (iVar12 != 0) {
            return 0;
          }
          uVar13 = GetBaseMaxHP(UNK_02023d6b);
          uVar13 = uVar13 >> 2;
          goto LAB_0905e23e;
        }
        if (gLastUsedAbility != 0x78) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((gMoveResultFlags & 0x29) != 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (gBattleMons[UNK_02023d6b].hp == 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (UNK_02023d6b == param_2) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        UNK_02023fdb = bVar2;
        iVar12 = GetBankAbility();
        if (iVar12 == 0xc9) {
          return 0;
        }
        if (((int)(gBattleTypeFlags << 0x1f) < 0) &&
           (iVar12 = GetBankAbility(UNK_02023d6b ^ 2), iVar12 == 0xc9)) {
          return 0;
        }
        uVar10 = Random2();
        iVar12 = umodsi(uVar10,3);
        if (iVar12 != 0) {
          return 0;
        }
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000cc8;
      }
      else {
        if (gLastUsedAbility == 0x7b) {
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[UNK_02023d6b].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          iVar12 = GetBankAbility();
          if (iVar12 == 0x73) {
            return 0;
          }
          iVar12 = CheckContact(uStack_3c,UNK_02023d6b);
          if (iVar12 == 0) {
            return 0;
          }
          uVar13 = GetBaseMaxHP(UNK_02023d6b);
          uVar13 = uVar13 >> 3;
LAB_0905e23e:
          uVar13 = uVar13 & 0xffff;
          goto LAB_0905e242;
        }
        if (0x7a < gLastUsedAbility) {
          if (gLastUsedAbility != 0x86) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gTerrainType == '\x02') {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          param_1 = sub_93505ac(2,0x28,param_2);
          goto LAB_0905c192;
        }
        if ((gMoveResultFlags & 0x29) != 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (gBattleMons[UNK_02023d6b].hp == 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (UNK_02023d6b == param_2) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        UNK_02023fdb = bVar2;
        iVar12 = CheckContact(uStack_3c);
        if (iVar12 == 0) {
          return 0;
        }
        uVar13 = GetBankAbility(UNK_02023d6b);
        if (uVar13 == 0xaa) {
          return 0;
        }
        if (uVar13 < 0xab) {
          if (uVar13 == 0x9f) {
            return 0;
          }
          if (uVar13 < 0xa0) {
            if (uVar13 == 0x7a) {
              return 0;
            }
            if (uVar13 == 0x9c) {
              return 0;
            }
          }
          else {
            if (uVar13 == 0xa5) {
              return 0;
            }
            if (uVar13 == 0xa8) {
              return 0;
            }
          }
        }
        else {
          if (uVar13 == 0xd3) {
            return 0;
          }
          if (uVar13 < 0xd4) {
            if (uVar13 == 0xae) {
              return 0;
            }
            if (uVar13 == 0xb4) {
              return 0;
            }
          }
          else {
            if (uVar13 == 0xe7) {
              return 0;
            }
            if (uVar13 == 0xfa) {
              return 0;
            }
          }
        }
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000ce8;
      }
    }
    else if (gLastUsedAbility == 0xc6) {
      if ((gMoveResultFlags & 0x29) != 0) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
         (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (gBattleMons[param_2].hp == 0) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (UNK_02023d6b == param_2) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (uVar22 != 0x11) {
        UNK_02023fdb = bVar2;
        return 0;
      }
LAB_0905e5f4:
      if (0xb < gBattleMons[param_2].statStages[0]) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      gStatChangeByte = 0x11;
      UNK_02023fdb = bVar2;
LAB_0905e604:
                    /* WARNING (jumptable): Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
      BattleScriptPushCursor();
      gBattlescriptCurrInstr = (undefined1 *)0x9000b1a;
    }
    else if (gLastUsedAbility < 199) {
      if (gLastUsedAbility == 0xaf) {
        if ((gMoveResultFlags & 0x29) != 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (gBattleMons[param_2].hp == 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (UNK_02023d6b == param_2) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (uVar22 != 10) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        goto LAB_0905e5f4;
      }
      if (gLastUsedAbility < 0xb0) {
        if (gLastUsedAbility != 0xa4) {
          if (gLastUsedAbility != 0xad) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[param_2].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (0xb < gBattleMons[param_2].statStages[1]) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          gStatChangeByte = 0x12;
          UNK_02023fdb = bVar2;
          goto LAB_0905e604;
        }
        if ((gMoveResultFlags & 0x29) != 0) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if ((gBattleMons[UNK_02023d6b].hp == 0) && (gBattleMons[param_2].hp == 0)) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        if (UNK_02023d6b == param_2) {
          UNK_02023fdb = bVar2;
          return 0;
        }
        UNK_02023fdb = bVar2;
        pbVar15 = (byte *)GetAbilityLocation();
        if (*pbVar15 == gLastUsedAbility) {
          return 0;
        }
        iVar12 = func_0x09075016(uStack_3c,UNK_02023d6b,param_2);
        if (iVar12 == 0) {
          return 0;
        }
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000d2a;
      }
      else {
        if (gLastUsedAbility == 0xbb) {
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d71 < 0xb) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[param_2].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (0xb < gBattleMons[param_2].statStages[0]) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          param_1 = 1;
          UNK_02023fdb = bVar2;
          gBattleMons[param_2].statStages[0] = 0xc;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
          gBattleTextBuff1 = 0xfd;
                    /* WARNING (jumptable): Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
          UNK_02022ab9 = 5;
                    /* WARNING (jumptable): Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
          UNK_02022abb = 0xff;
                    /* WARNING (jumptable): Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
          UNK_02022aba = 1;
          BattleScriptPushCursor();
          gBattlescriptCurrInstr = (undefined1 *)0x9000f0a;
          goto LAB_0905d386;
        }
        if (gLastUsedAbility != 0xc1) {
          if (gLastUsedAbility != 0xb2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (gBattleMons[param_2].hp == 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (UNK_02023d6b == param_2) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (uVar22 != 0xb) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if (0xb < gBattleMons[param_2].statStages[1]) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          gStatChangeByte = 0x22;
          UNK_02023fdb = bVar2;
          goto LAB_0905e604;
        }
        UNK_02023fdb = bVar2;
        iVar12 = func_0x09076024();
        if (iVar12 != 0) {
          return 0;
        }
        if ((gMoveResultFlags & 0x29) != 0) {
          return 0;
        }
        if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
           (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
          return 0;
        }
        iVar12 = CalcMoveSplit(UNK_02023d6b,gCurrentMove);
        if (iVar12 != 0) {
          return 0;
        }
        if (gBattleMons[param_2].hp == 0) {
          return 0;
        }
        if (UNK_02023d6b == param_2) {
          return 0;
        }
        if ((0xb < gBattleMons[param_2].statStages[2]) && (gBattleMons[param_2].statStages[1] < 1))
        {
          return 0;
        }
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = (undefined1 *)0x9000c54;
      }
    }
    else {
      if (gLastUsedAbility != 0xdc) {
        if (gLastUsedAbility < 0xdd) {
          if (gLastUsedAbility == 0xcc) {
            if ((gMoveResultFlags & 0x29) != 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
               (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (gBattleMons[UNK_02023d6b].hp == 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (UNK_02023d6b == param_2) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            UNK_02023fdb = bVar2;
            gStatuses3[param_2] = gStatuses3[param_2] | 0x200;
            gDisableStructs[param_2].field_0x12 = 0x22;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = (undefined1 *)0x9000b90;
          }
          else {
            if (gLastUsedAbility == 0xd8) {
              UNK_02023fdb = bVar2;
              iVar12 = func_0x09076024();
              if ((iVar12 != 0) && (gLastUsedAbility != 0xe3)) {
                return 0;
              }
              if ((gMoveResultFlags & 0x29) != 0) {
                return 0;
              }
              if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
                 (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
                return 0;
              }
              uVar13 = (uint)gBattleMons[param_2].hp;
              if (uVar13 == 0) {
                return 0;
              }
              uVar17 = (uint)(gBattleMons[param_2].maxHP >> 1);
              if (uVar17 <= uVar13) {
                return 0;
              }
              if ((int)(uVar13 + gHpDealt) <= (int)uVar17) {
                return 0;
              }
              if (0xb < gBattleMons[param_2].statStages[3]) {
                return 0;
              }
              gStatChangeByte = 0x14;
              goto LAB_0905e604;
            }
            if (gLastUsedAbility != 0xca) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((gMoveResultFlags & 0x29) != 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
               (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (UNK_02023d6b == param_2) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            UNK_02023fdb = bVar2;
            iVar12 = CalcMoveSplit((uint)UNK_02023d6b,gCurrentMove);
            if (iVar12 != 0) {
              return 0;
            }
            if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[(uint)UNK_02023d6b * 0xb] << 0x1c) < 0
               ) {
              return 0;
            }
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = (undefined1 *)0x9000bba;
          }
        }
        else {
          if (gLastUsedAbility == 0xf5) {
            if ((gMoveResultFlags & 0x29) != 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
               (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (gBattleMons[param_2].hp == 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (UNK_02023d6b == param_2) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (1 < uVar22 - 10) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (0xb < gBattleMons[param_2].statStages[2]) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            gStatChangeByte = 99;
            UNK_02023fdb = bVar2;
            goto LAB_0905e604;
          }
          if (gLastUsedAbility == 0xf7) {
            if ((gMoveResultFlags & 0x29) != 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
               (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if (UNK_02023d6b == param_2) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            if ((gBattleWeather & 0x7818) != 0) {
              UNK_02023fdb = bVar2;
              return 0;
            }
            UNK_02023fdb = bVar2;
            param_1 = sub_9350712(0x18,0x4e,param_2,0xc,1,1);
            goto LAB_0905c192;
          }
          if (gLastUsedAbility != 0xe3) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((gMoveResultFlags & 0x29) != 0) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
             (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          uVar13 = gStatuses3[param_2];
          if (-1 < (int)uVar13) {
            UNK_02023fdb = bVar2;
            return 0;
          }
          UNK_02023fdb = bVar2;
          *(byte *)(uVar20 + 0xc9) =
               (byte)*(undefined4 *)(&gBitTable + param_2 * 4) | *(byte *)(uVar20 + 0xc9);
          gStatuses3[param_2] = uVar13 & 0x7fffffff;
          *(undefined1 *)(uVar20 + param_2 + 0xa5) = 0;
          gActiveBattler = bVar2;
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
          func_0x090a929c(0,gStatuses3 + param_2,4,gStatuses3 + param_2);
          MarkBufferBankForExecution(gActiveBattler);
          BattleScriptPushCursor();
          gBattlescriptCurrInstr = (undefined1 *)0x9000eae;
        }
        goto LAB_0905da9e;
      }
      if ((gMoveResultFlags & 0x29) != 0) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if ((*(int *)(&UNK_02023ed4 + param_2 * 0x14) == 0) &&
         (*(int *)(&UNK_02023ed8 + param_2 * 0x14) == 0)) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (gBattleMons[UNK_02023d6b].hp == 0) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      if (UNK_02023d6b == param_2) {
        UNK_02023fdb = bVar2;
        return 0;
      }
      UNK_02023fdb = bVar2;
      iVar12 = GetBankAbility();
      if (iVar12 == 0x73) {
        return 0;
      }
      if (gBattleMons[param_2].hp != 0) {
        return 0;
      }
      uVar13 = gHpDealt;
LAB_0905e242:
      gBattleMoveDamage = MathMax(1,uVar13);
                    /* WARNING (jumptable): Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
      BattleScriptPushCursor();
      gBattlescriptCurrInstr = (undefined1 *)0x9000b66;
    }
LAB_0905da9e:
    param_1 = 1;
    goto LAB_0905d386;
  case 5:
    uVar13 = 0;
    do {
      if (gBattlersCount <= uVar13) {
        return 0;
      }
      uVar17 = GetBankAbility(uVar13);
      if (uVar17 == 0x11) {
        uVar17 = 0x88;
        if ((gBattleMons[uVar13].status1 & 0x88) != 0) {
          puVar14 = &UNK_08250094;
          goto LAB_0905ed94;
        }
      }
      else if (uVar17 < 0x12) {
        if (uVar17 == 0xc) {
          bVar2 = gDisableStructs[uVar13].field_0x13;
          if ((gBattleMons[uVar13].status2 & 0xf0000) == 0) {
            if ((bVar2 & 0xf) == 0) goto LAB_0905ed1e;
            puVar14 = &LAB_090ff15a;
          }
          else {
            puVar14 = (undefined *)0x90ff153;
            if ((bVar2 & 0xf) == 0) {
              puVar14 = &UNK_082500c4;
            }
          }
          StringCopy(&gBattleTextBuff1,puVar14,bVar2 & 0xf,&StringCopy);
          gDisableStructs[uVar13].field_0x13 = gDisableStructs[uVar13].field_0x13 & 0xf0;
          gBattleMons[uVar13].status2 = gBattleMons[uVar13].status2 & 0xfff0ffff;
          uVar17 = 3;
          goto LAB_0905edd0;
        }
        if (uVar17 == 0xf) {
          if ((gBattleMons[uVar13].status1 & 7) != 0) {
            uVar17 = gBattleMons[uVar13].status2 & 0xf7ffffff;
            gBattleMons[uVar13].status2 = uVar17;
            puVar14 = &UNK_0825009c;
            goto LAB_0905ed94;
          }
        }
        else if ((uVar17 == 7) && (uVar17 = 0x40, (gBattleMons[uVar13].status1 & 0x40) != 0)) {
          puVar14 = &UNK_082500a4;
LAB_0905ed94:
          StringCopy(&gBattleTextBuff1,puVar14,uVar17,&StringCopy);
          uVar17 = 1;
          gBattleMons[uVar13].status1 = 0;
LAB_0905edd0:
          BattleScriptPushCursor();
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
          gBattlescriptCurrInstr = (undefined1 *)0x900076b;
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
          gActiveBattler = (byte)uVar13;
                    /* WARNING (jumptable): Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
          UNK_02023fdb = gActiveBattler;
          BtlController_EmitSetMonData(0,0x28,0,4,uVar13 * 0x58 + 0x2023c30);
          MarkBufferBankForExecution(gActiveBattler);
          return uVar17;
        }
      }
      else if (uVar17 == 0x28) {
        uVar17 = 0x20;
        if ((gBattleMons[uVar13].status1 & 0x20) != 0) {
          puVar14 = &UNK_082500b4;
          goto LAB_0905ed94;
        }
      }
      else if (uVar17 < 0x29) {
        if (uVar17 == 0x14) {
          if ((gBattleMons[uVar13].status2 & 7) != 0) {
            StringCopy(&gBattleTextBuff1,&UNK_082500bc,uVar13 * 0x58,&StringCopy);
            uVar17 = 2;
            gBattleMons[uVar13].status2 = gBattleMons[uVar13].status2 & 0xfffffff8;
            goto LAB_0905edd0;
          }
        }
      }
      else if (((uVar17 == 0x29) || (uVar17 == 0xaf)) &&
              (uVar17 = 0x10, (gBattleMons[uVar13].status1 & 0x10) != 0)) {
        puVar14 = &UNK_082500ac;
        goto LAB_0905ed94;
      }
LAB_0905ed1e:
      uVar13 = uVar13 + 1 & 0xff;
    } while( true );
  case 7:
    if (gLastUsedAbility != 0x1c) {
      return 0;
    }
    pbVar15 = (byte *)(uVar20 + param_2 + 0x89);
    uVar13 = (uint)*pbVar15;
    if (uVar13 == 0) {
      return 0;
    }
    uVar13 = uVar13 - 1;
    if (param_2 != uVar13) {
      gHitMarker = gHitMarker & 0xffffbfff;
                    /* WARNING (jumptable): Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
      UNK_02023e85 = gBattleStruct->synchronizeMoveEffect & 0x3f;
      gBattleStruct->synchronizeMoveEffect = UNK_02023e85;
                    /* WARNING (jumptable): Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
      UNK_02023fdb = bVar2;
      *(byte *)(uVar20 + 0x11a) = UNK_02023d6b;
      *(byte *)(uVar20 + 0x11b) = gBattlerTarget;
      *pbVar15 = 0;
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
      gBattlerTarget = (byte)uVar13;
      UNK_02023d6b = bVar2;
      BattleScriptPushCursor();
                    /* WARNING (jumptable): Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
      gBattlescriptCurrInstr = &LAB_09000f32;
      gHitMarker = gHitMarker | 0x2000;
                    /* WARNING (jumptable): Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
    }
    param_1 = (uint)(param_2 != uVar13);
    *(undefined1 *)(gNewBS + param_2 + 0x89) = 0;
LAB_0905c192:
    if (param_1 == 0) {
      return 0;
    }
LAB_0905d386:
    if (gLastUsedAbility == 0xff) {
      return param_1;
    }
LAB_0905d392:
    func_0x09073930(param_2,gLastUsedAbility);
    return param_1;
  case 12:
    uVar13 = 0;
    iVar12 = GetBattlerSide(param_2);
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      uVar22 = uVar17 & 0xff;
      iVar11 = GetBattlerSide(uVar22);
      if ((iVar11 != iVar12) && (iVar11 = GetBankAbility(uVar22), iVar11 == param_3)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = uVar22 + 1 & 0xff;
      }
    }
    break;
  case 13:
    uVar13 = 0;
    iVar12 = GetBattlerSide(param_2);
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      uVar22 = uVar17 & 0xff;
      iVar11 = GetBattlerSide(uVar22);
      if ((iVar11 == iVar12) && (iVar11 = GetBankAbility(uVar22), iVar11 == param_3)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = uVar22 + 1 & 0xff;
      }
    }
    break;
  case 14:
    if (gLastUsedAbility == 0xfd) {
      uVar13 = sub_9075290();
    }
    else if (gLastUsedAbility == 0xfe) {
      uVar13 = sub_90752bc();
    }
    else {
      uVar13 = 0;
      for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
        iVar12 = GetBankAbility(uVar17 & 0xff);
        if (iVar12 == param_3) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
          gLastUsedAbility = bStack_38;
          uVar13 = (uVar17 & 0xff) + 1 & 0xff;
        }
      }
    }
    break;
  case 19:
    uVar13 = 0;
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      iVar12 = GetBankAbility(uVar17 & 0xff);
      if ((iVar12 == param_3) && (gBattleMons[uVar17].hp != 0)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = (uVar17 & 0xff) + 1 & 0xff;
      }
    }
    break;
  case 15:
    uVar13 = 0;
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      iVar12 = GetBankAbility(uVar17 & 0xff);
      if ((iVar12 == param_3) && (param_2 != uVar17)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = (uVar17 & 0xff) + 1 & 0xff;
      }
    }
    break;
  case 16:
    uVar13 = 0;
    iVar12 = GetBattlerSide(param_2);
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      iVar11 = GetBattlerSide(uVar17 & 0xff);
      if ((iVar11 != iVar12) && (iVar11 = GetBankAbility(uVar17 & 0xff), iVar11 == param_3)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = uVar13 + 1 & 0xff;
      }
    }
    break;
  case 17:
    uVar13 = 0;
    iVar12 = GetBattlerSide(param_2);
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      iVar11 = GetBattlerSide(uVar17 & 0xff);
      if ((iVar11 == iVar12) && (iVar11 = GetBankAbility(uVar17 & 0xff), iVar11 == param_3)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = uVar13 + 1 & 0xff;
      }
    }
    break;
  case 18:
    uVar13 = 0;
    for (uVar17 = 0; (int)uVar17 < (int)(uint)gBattlersCount; uVar17 = uVar17 + 1) {
      iVar12 = GetBankAbility(uVar17 & 0xff);
      if ((iVar12 == param_3) && (param_2 != uVar17)) {
                    /* WARNING (jumptable): Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
        gLastUsedAbility = bStack_38;
        uVar13 = uVar13 + 1 & 0xff;
      }
    }
  }
  if (uVar13 != 0) {
    return uVar13;
  }
sw_5c06c_6:
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abc) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d54) is written */
                    /* WARNING: Read-only address (ram,0x02023d68) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6e) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023dcc) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e02e) is written */
                    /* WARNING: Read-only address (ram,0x0203e033) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
                    /* WARNING: Read-only address (ram,0x02022ab8) is written */
                    /* WARNING: Read-only address (ram,0x02022ab9) is written */
                    /* WARNING: Read-only address (ram,0x02022aba) is written */
                    /* WARNING: Read-only address (ram,0x02022abb) is written */
                    /* WARNING: Read-only address (ram,0x02022abc) is written */
                    /* WARNING: Read-only address (ram,0x02022ac8) is written */
                    /* WARNING: Read-only address (ram,0x02022ac9) is written */
                    /* WARNING: Read-only address (ram,0x02022aca) is written */
                    /* WARNING: Read-only address (ram,0x02022acb) is written */
                    /* WARNING: Read-only address (ram,0x02022acc) is written */
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
                    /* WARNING: Read-only address (ram,0x02023bcc) is written */
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d54) is written */
                    /* WARNING: Read-only address (ram,0x02023d68) is written */
                    /* WARNING: Read-only address (ram,0x02023d6a) is written */
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023d6c) is written */
                    /* WARNING: Read-only address (ram,0x02023d6e) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023d74) is written */
                    /* WARNING: Read-only address (ram,0x02023dcc) is written */
                    /* WARNING: Read-only address (ram,0x02023dd0) is written */
                    /* WARNING: Read-only address (ram,0x02023e85) is written */
                    /* WARNING: Read-only address (ram,0x02023e87) is written */
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x02023f48) is written */
                    /* WARNING: Read-only address (ram,0x02023fd4) is written */
                    /* WARNING: Read-only address (ram,0x02023fdb) is written */
                    /* WARNING: Read-only address (ram,0x02023fde) is written */
                    /* WARNING: Read-only address (ram,0x02023fe8) is written */
                    /* WARNING: Read-only address (ram,0x02023ff4) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e02e) is written */
                    /* WARNING: Read-only address (ram,0x0203e033) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
  return 0;
}

// ---- IsTargetAbilityIgnored  (ROM 0x905f9e4)
bool IsTargetAbilityIgnored(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = sub_9073c04(param_2,param_3);
  bVar2 = false;
  if (iVar1 != 0) {
    iVar1 = CheckTableForAbility(param_1,0x9123906);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- sub_905fa0c  (ROM 0x905fa0c)
bool sub_905fa0c(undefined4 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  if (param_2 == 0x98) {
    iVar1 = CheckTableForAbility(param_1,0x9123906);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- IsClearBodyAbility  (ROM 0x905fa9a)
bool IsClearBodyAbility(int param_1)

{
  return param_1 == 0x1d;
}

// ---- sub_905faa2  (ROM 0x905faa2)
bool sub_905faa2(int param_1)

{
  return param_1 == 0x98;
}

// ---- IsMoxieAbility  (ROM 0x905faaa)
undefined4 IsMoxieAbility(uint param_1)

{
  if (param_1 < 0x9e) {
    if ((param_1 < 0x9c) && (param_1 != 0x76)) {
      return 0;
    }
  }
  else if ((param_1 != 0xac) && (param_1 != 0xcf)) {
    return 0;
  }
  return 1;
}

// ---- sub_905fad6  (ROM 0x905fad6)
undefined4 sub_905fad6(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 10) || ((0xb < param_1 && (param_1 != 0xbc)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

// ---- IsElectricAbsorptionAblity  (ROM 0x905faea)
undefined4 IsElectricAbsorptionAblity(int param_1)

{
  undefined4 uVar1;
  
  if (((param_1 == 0x1f) || (param_1 == 0x50)) || (param_1 == 10)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ---- sub_905fafe  (ROM 0x905fafe)
bool sub_905fafe(char param_1)

{
  return (byte)(param_1 - 0x39U) < 2;
}

// ---- AbilityPreventsLoweringAtk  (ROM 0x905fb74)
bool AbilityPreventsLoweringAtk(int param_1,int param_2)

{
  return param_1 == 0x34 && param_2 == 1;
}

// ---- sub_905fb84  (ROM 0x905fb84)
bool sub_905fb84(char param_1)

{
  return (byte)(param_1 + 0x72U) < 2;
}

// ---- IsAffectedBySturdy  (ROM 0x905fb96)
bool IsAffectedBySturdy(int param_1,int param_2)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 == 5) {
    bVar1 = gBattleMons[param_2].hp == gBattleMons[param_2].maxHP;
  }
  return bVar1;
}

// ---- IsAffectedByDisguse  (ROM 0x905fbb8)
bool IsAffectedByDisguse(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  if (param_1 == 0x9f) {
    bVar1 = param_2 == 0x3e3;
  }
  else {
    bVar1 = false;
    if ((param_1 == 0xfa) && (param_2 == 0x48f)) {
      bVar1 = param_3 == 0;
    }
  }
  return bVar1;
}

// ---- IsTrappedByAbility  (ROM 0x905fc24)
uint IsTrappedByAbility(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = func_0x09074f8c();
  uVar2 = 0;
  if (iVar1 != 0) {
    if (param_2 == 0x2a) {
      uVar2 = IsOfType(param_1,8 /* Steel */);
    }
    else if (param_2 == 0x47) {
      iVar1 = CheckGrounding(param_1);
      uVar2 = (uint)(iVar1 == 1);
    }
    else {
      uVar2 = 0;
      if (param_2 == 0x17) {
        iVar1 = GetBankAbility(param_1);
        uVar2 = (uint)(iVar1 != 0x17);
      }
    }
  }
  return uVar2;
}

// ---- sub_905ff10  (ROM 0x905ff10)
bool sub_905ff10(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  byte bVar6;
  undefined *puVar7;
  uint uVar8;
  bool bVar9;
  
  bVar5 = gBattleMoves[param_1].flags;
  bVar6 = gBattleMoves[param_1].split;
  iVar2 = CheckContact();
  bVar1 = gBattleMoves[param_1].target;
  iVar4 = GetBattlerSide(param_3);
  iVar3 = GetBankAbility(param_2);
  if ((iVar3 == 199) && (iVar2 != 0)) {
    return false;
  }
  iVar3 = func_0x0908de68(param_3,param_1);
  bVar9 = iVar3 != 0;
  if (bVar9) {
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
    UNK_02023e88 = 1;
    *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
  }
  iVar3 = param_3 * 0x10;
  if (((int)((uint)(byte)(&gProtectStructs)[iVar3] << 0x1f) < 0) && ((bVar5 & 2) != 0)) {
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
    UNK_02023e88 = 1;
    *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
    return true;
  }
  puVar7 = &gProtectStructs + iVar3;
  if ((((int)((uint)(byte)(&UNK_02023e8f)[iVar3] << 0x1f) < 0) && ((bVar5 & 2) != 0)) &&
     (bVar6 != 2)) {
    *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
    if (iVar2 == 0) {
      return true;
    }
    if (param_4 == 0) {
      return true;
    }
    bVar6 = 8;
    bVar5 = (&UNK_02023e8f)[iVar3];
  }
  else {
    iVar3 = param_3 * 0x10;
    if (((int)((uint)(byte)(&UNK_02023e8f)[iVar3] << 0x1e) < 0) && ((bVar5 & 2) != 0)) {
      *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
      if (iVar2 == 0) {
        return true;
      }
      if (param_4 == 0) {
        return true;
      }
      (&UNK_02023e8f)[iVar3] = (&UNK_02023e8f)[iVar3] | 0x10;
      UNK_02023e88 = 1;
      return true;
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
    }
    puVar7 = &gProtectStructs + iVar3;
    if (((int)((uint)(byte)(&UNK_02023e8f)[iVar3] << 0x1d) < 0) && ((bVar5 & 2) != 0)) {
      *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
      if (iVar2 == 0) {
        return true;
      }
      if (param_4 == 0) {
        return true;
      }
      bVar5 = (&UNK_02023e8f)[iVar3];
      bVar6 = 0x20;
    }
    else {
      iVar3 = param_3 * 0x10;
      if (((int)((uint)(byte)(&UNK_02023e8e)[iVar3] << 0x1e) < 0) &&
         (((bVar5 & 2) != 0 && (bVar6 != 2)))) {
        *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
        if (iVar2 == 0) {
          return true;
        }
        if (param_4 == 0) {
          return true;
        }
        (&UNK_02023e8e)[iVar3] = (&UNK_02023e8e)[iVar3] | 0x10;
        UNK_02023e88 = 1;
        return true;
      }
      if (((int)((uint)(byte)(&UNK_02023e8e)[iVar3] << 0x19) < 0) && ((bVar5 & 2) != 0)) {
        *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
        if ((iVar2 == 0) || (param_4 == 0)) {
                    /* WARNING: Read-only address (ram,0x02023d6b) is written */
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
          return true;
        }
        (&UNK_02023e8e)[iVar3] = (&UNK_02023e8e)[iVar3] | 0x80;
        UNK_02023e88 = 1;
        return true;
      }
      iVar3 = param_3 * 0x10;
      puVar7 = &gProtectStructs + iVar3;
      if ((-1 < (int)((uint)(byte)(&UNK_02023e8e)[iVar3] << 0x1a)) || ((bVar5 & 2) == 0)) {
        uVar8 = (uint)gSideStatuses[iVar4];
        if (((int)(uVar8 << 0x1c) < 0) && ((bVar1 != 0x10 && (bVar6 == 2)))) {
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = (undefined *)0x90fd70b;
          UNK_02023e88 = 5;
        }
        else if (((int)(uVar8 << 0x18) < 0) && (((bVar5 & 2) != 0 && (bVar6 != 2)))) {
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = (undefined *)0x90fd72b;
          UNK_02023e88 = 6;
        }
        else if (((int)(uVar8 << 0x15) < 0) &&
                (((bVar5 & 2) != 0 && (iVar2 = PriorityCalc(param_2,0,param_1), 0 < iVar2)))) {
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = (undefined *)0x90fd750;
          UNK_02023e88 = 7;
        }
        else {
          if ((-1 < (int)((uint)gSideStatuses[iVar4] << 0x14)) ||
             (((bVar5 & 2) == 0 || ((bVar1 != 8 && (bVar1 != 0x20)))))) {
            iVar2 = IsRaidBattle();
            if (iVar2 == 0) {
              return bVar9;
            }
            if (bVar6 != 2) {
              return bVar9;
            }
            if (UNK_02023d6b == param_3) {
              return bVar9;
            }
            uVar8 = GetBattlerAtPosition(1);
            if (uVar8 != param_3) {
              return bVar9;
            }
            if ((int)((uint)*(byte *)(gNewBS + 0x1b5) << 0x1d) < 0) {
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
              gBattleStringLoader = (undefined *)0x90fe3cf;
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
              UNK_02023e88 = 9;
              *(undefined1 *)(gNewBS + param_3 + 0x164) = 9;
              return true;
            }
            return bVar9;
          }
                    /* WARNING: Read-only address (ram,0x0203e020) is written */
          gBattleStringLoader = &LAB_090fd76e;
          UNK_02023e88 = 8;
        }
                    /* WARNING: Read-only address (ram,0x02023e88) is written */
        *(undefined1 *)(gNewBS + param_3 + 0x164) = UNK_02023e88;
        return true;
      }
      *(undefined1 *)(gNewBS + param_3 + 0x164) = 1;
      if (iVar2 == 0) {
        return true;
      }
      if (param_4 == 0) {
        return true;
      }
      bVar5 = (&UNK_02023e8f)[iVar3];
      bVar6 = 0x80;
    }
  }
  puVar7[3] = bVar6 | bVar5;
  UNK_02023e88 = 1;
  return true;
}

// ---- DoesProtectionMoveBlockMove  (ROM 0x90601e8)
uint DoesProtectionMoveBlockMove(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  
  bVar1 = gBattleMoves[param_3].flags;
  bVar2 = gBattleMoves[param_3].split;
  bVar3 = gBattleMoves[param_3].target;
  bVar6 = bVar1 & 2;
  iVar4 = CheckTableForMove(param_3,&UNK_0904025a);
  if ((iVar4 != 0) && (iVar4 = GetBankAbility(param_1), iVar4 == 199)) {
    return 0;
  }
  if (param_4 == 0x27c) {
    if (gDisableStructs[param_2].isFirstTurn == 0) {
      return 0;
    }
LAB_0906029e:
    if ((bVar1 & 2) == 0) {
      return 0;
    }
    return (uint)(bVar2 != 2);
  }
  if (param_4 < 0x27d) {
    if (param_4 != 0x237) {
      if (param_4 < 0x238) {
        if (param_4 != 0xb6) {
          if (param_4 != 0x20f) {
            return 0;
          }
          goto LAB_0906029e;
        }
      }
      else if (param_4 != 0x244) {
        if (param_4 != 0x27b) {
          return 0;
        }
        if (bVar3 == 0x10) {
          return 0;
        }
        return (uint)(bVar2 == 2);
      }
    }
  }
  else {
    if (param_4 == 0x2c4) goto LAB_0906029e;
    if (param_4 < 0x2c5) {
      if (param_4 == 0x27d) {
        uVar5 = 0;
        if ((bVar1 & 2) != 0) {
          iVar4 = PriorityCalc(param_1,0,param_3);
          uVar5 = (uint)((iVar4 >> 0x1f) - iVar4) >> 0x1f;
        }
        return uVar5;
      }
      if (param_4 != 0x27e) {
        return 0;
      }
      if ((bVar1 & 2) == 0) {
        return 0;
      }
      bVar6 = bVar3 & 0x28;
    }
    else {
      if (param_4 == 0x318) goto LAB_0906029e;
      if (param_4 != 0x334) {
        return 0;
      }
    }
  }
  return (uint)(bVar6 != 0);
}

// ---- AccuracyCalc  (ROM 0x906036c)
void AccuracyCalc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar3 = param_2;
  uVar4 = param_3;
  uVar1 = GetBankAbility(param_3);
  uVar2 = GetBankItemEffect(param_3);
  func_0x0905fc68(param_1,param_2,param_3,uVar1,uVar2,uVar3,uVar4);
  return;
}

// ---- sub_9060cec  (ROM 0x9060cec)
undefined8 sub_9060cec(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  uVar1 = sub_9083c94(gCurrentMove,UNK_02023d6b,param_1,0,0,param_2);
  if ((((uVar1 & 0x29) == 0) &&
      (iVar2 = sub_905ff10(gCurrentMove,UNK_02023d6b,param_1), iVar2 == 0)) &&
     ((gStatuses3[param_1] & 0x130400c0) == 0)) {
    iVar2 = func_0x09060ca0();
    uVar1 = (uint)(iVar2 != 0);
  }
  else {
    uVar1 = 1;
  }
  return CONCAT44(uVar3,uVar1);
}

// ---- sub_906b400  (ROM 0x906b400)
int sub_906b400(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = gBattleMons[param_2].statStages[0] * 2;
  uVar1 = udivsi(gBattleMons[param_2].attack * (ushort)*(byte *)(iVar3 + 0x9124898),
                             *(undefined1 *)(iVar3 + 0x9124899));
  uVar2 = MathMax(1,uVar1);
  iVar3 = GetBankItemEffect(param_1);
  if (iVar3 == 0x68) {
    uVar2 = sub_900042a((uVar2 & 0xffff) * 0xd,10);
  }
  return -(uVar2 & 0xffff);
}

// ---- sub_906cad4  (ROM 0x906cad4)
undefined8 sub_906cad4(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0;
  iVar2 = 0;
  do {
    if (gBattleMons[param_1].moves[iVar2] == 0) {
      if (iVar2 == 1) {
LAB_0906cb1e:
        uVar1 = 0;
      }
      break;
    }
    if (gBattleMons[param_1].moves[iVar2] == 0x2a2) {
      uVar1 = 1;
    }
    else if ((*(uint *)((iVar2 + 0x2097917) * 4) & (uint)*(byte *)(gNewBS + param_1 + 0x6d)) == 0)
    goto LAB_0906cb1e;
    iVar2 = iVar2 + 1;
  } while (iVar2 != 4);
  return CONCAT44(param_1,uVar1);
}

// ---- PriorityCalc  (ROM 0x906efc0)
undefined8 PriorityCalc(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  sbyte sVar3;
  
  iVar1 = 0;
  if (gBattleMons[param_1].hp == 0) goto LAB_0906f042;
  sVar3 = 0;
  if (param_2 == 0) {
    if ((int)((uint)(byte)(&gProtectStructs)[param_1 * 0x10] << 0x1d) < 0) {
      param_3 = 0xa5;
      sVar3 = 0;
LAB_0906eff4:
      if ((gBattleMons[param_1].status2 & 0x300) != 0) {
        sVar3 = 1;
      }
    }
    else {
      sVar3 = gBattleMoves[param_3].priority;
      if (param_3 != 0x75) goto LAB_0906eff4;
    }
    uVar2 = GetBankAbility(param_1);
    if (uVar2 == 0x75) {
      iVar1 = GetMoveTypeSpecial(param_1,param_3);
      if (iVar1 == 2) {
LAB_0906f078:
        if (gBattleMons[param_1].hp == gBattleMons[param_1].maxHP) {
LAB_0906f068:
          sVar3 = sVar3 + 1;
        }
      }
    }
    else if (uVar2 < 0x76) {
      if ((uVar2 == 0x57) && (gBattleMoves[param_3].split == 2)) goto LAB_0906f068;
    }
    else if (uVar2 == 0xb0) {
      if ((int)((uint)gBattleMoves[param_3].flags << 0x19) < 0) {
        sVar3 = sVar3 + 3;
      }
    }
    else if ((uVar2 == 0xfc) && (iVar1 = GetMoveTypeSpecial(param_1,param_3), iVar1 == 10))
    goto LAB_0906f078;
    if ((param_3 == 0x2cf) && (gTerrainType == '\x02')) {
      sVar3 = sVar3 + 1;
    }
  }
  iVar1 = (int)sVar3;
LAB_0906f042:
  return CONCAT44(param_1,iVar1);
}

// ---- sub_906f0b8  (ROM 0x906f0b8)
int sub_906f0b8(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  sbyte sVar4;
  
  sVar4 = gBattleMoves[param_2].priority;
  uVar1 = GetMonAbility();
  if (uVar1 == 0x75) {
    iVar2 = sub_908367c(param_1,param_2);
    if (iVar2 != 2) goto LAB_0906f0d8;
code_r0x09071396:
    iVar3 = GetMonData(param_1,0x39,0);
    iVar2 = GetMonData(param_1,0x3a,0);
    if (iVar3 != iVar2) goto LAB_0906f0d8;
  }
  else {
    if (0x75 < uVar1) {
      if (uVar1 == 0xb0) {
        if ((int)((uint)gBattleMoves[param_2].flags << 0x19) < 0) {
          sVar4 = sVar4 + 3;
        }
        goto LAB_0906f0d8;
      }
      if ((uVar1 != 0xfc) || (iVar2 = sub_908367c(param_1,param_2), iVar2 != 10)) goto LAB_0906f0d8;
      goto code_r0x09071396;
    }
    if ((uVar1 != 0x57) || (gBattleMoves[param_2].split != 2)) goto LAB_0906f0d8;
  }
  sVar4 = sVar4 + 1;
LAB_0906f0d8:
  return (int)sVar4;
}

// ---- sub_906f140  (ROM 0x906f140)
undefined4 sub_906f140(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint extraout_r1;
  uint extraout_r1_00;
  undefined4 *puVar4;
  byte *pbVar5;
  byte bStack_24;
  
  iVar1 = GetBankItemEffect();
  uVar2 = ItemId_GetHoldEffectParam(gBattleMons[param_1].item);
  iVar3 = GetBankAbility(param_1);
  puVar4 = (undefined4 *)(&gBitTable + param_1 * 4);
  pbVar5 = (byte *)(gNewBS + 0xb8);
  bStack_24 = *pbVar5 & ~(byte)*puVar4;
  *pbVar5 = bStack_24;
  if (gBattleMons[param_1].hp == 0) {
    return 0;
  }
  if ((((iVar3 != 0x18) || (UNK_02023be3 != '\0')) || (gBattleMoves[gCurrentMove].split == 2)) ||
     (__umodsi3(gRandomTurnNumber,100), 0x1d < (extraout_r1 & 0xffff))) {
    if (iVar1 == 0x60) {
      iVar1 = AbilityBattleEffects(0xc,param_1,0xc0,0,0);
      if (iVar1 != 0) {
        return 0;
      }
      iVar1 = AbilityBattleEffects(0xc,param_1,0x4d,0,0);
      if (iVar1 != 0) {
        return 0;
      }
      iVar1 = AbilityBattleEffects(0xc,param_1,0x49,0,0);
      if (iVar1 != 0) {
        return 0;
      }
      if (gBattleMons[param_1].maxHP >> 2 < gBattleMons[param_1].hp) {
        iVar1 = GetBankAbility(param_1);
        if (iVar1 != 0xde) {
          return 0;
        }
        if (gBattleMons[param_1].maxHP >> 1 < gBattleMons[param_1].hp) {
          return 0;
        }
      }
      *(byte *)(gNewBS + 0xb8) = (byte)*puVar4 | *(byte *)(gNewBS + 0xb8);
      return 1;
    }
    if (iVar1 == 0x61) {
      return 0xfffffffe;
    }
    if ((iVar1 != 0x1a) ||
       (__umodsi3(gRandomTurnNumber,100), (uVar2 & 0xffff) <= (extraout_r1_00 & 0xffff))) {
                    /* WARNING: Read-only address (ram,0x02023be3) is written */
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
                    /* WARNING: Read-only address (ram,0x02023e80) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x02023be3) is written */
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
                    /* WARNING: Read-only address (ram,0x02023e80) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
      return 0;
    }
  }
  *pbVar5 = bStack_24 | (byte)*puVar4;
  return 1;
                    /* WARNING: Read-only address (ram,0x02023be3) is written */
                    /* WARNING: Read-only address (ram,0x02023d4a) is written */
                    /* WARNING: Read-only address (ram,0x02023e80) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
}

// ---- SpeedCalc  (ROM 0x906f284)
uint SpeedCalc(int param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  if (gBattleMons[param_1].hp == 0) {
    return 0;
  }
  uVar2 = GetBankAbility();
  iVar3 = GetBankItemEffect(param_1);
  uVar4 = ItemId_GetHoldEffectParam(gBattleMons[param_1].item);
  iVar8 = gBattleMons[param_1].statStages[2] * 2;
  uVar5 = sub_900042a((uint)*(byte *)(iVar8 + 0x9124898) * (uint)gBattleMons[param_1].speed,
                      *(undefined1 *)(iVar8 + 0x9124899));
  uVar6 = func_0x0906e320(uVar2,iVar3,uVar5);
  if (uVar2 == 0x91) {
    if (*(char *)(gNewBS + param_1 + 0x45) != '\0') {
      uVar6 = uVar6 >> 1;
    }
    goto LAB_0906f2e8;
  }
  if (uVar2 < 0x92) {
    if (uVar2 != 0x6a) {
      if (((uVar2 != 0x8b) ||
          ((*(uint *)(&gBitTable + param_1 * 4) & (uint)*(byte *)(gNewBS + 0xb3)) == 0)) ||
         (gBattleMons[param_1].item != 0)) goto LAB_0906f2e8;
LAB_0906f37c:
      uVar6 = uVar6 << 1;
      goto LAB_0906f2e8;
    }
    if (gDisableStructs[param_1].isFirstTurn == 0) goto LAB_0906f2e8;
  }
  else {
    if (uVar2 == 0xc3) {
      if (gTerrainType != '\x01') {
LAB_0906f3c6:
        if (-1 < (int)((uint)(byte)gDisableStructs[param_1].field_0x18 << 0x1e)) goto LAB_0906f2e8;
      }
    }
    else {
      if (uVar2 != 0xe5) {
        if ((uVar2 != 0xb9) || (gTerrainType != '\x01')) goto LAB_0906f2e8;
        goto LAB_0906f37c;
      }
      if (((gBattleWeather & 0x860) == 0) || (iVar3 == 0x88)) goto LAB_0906f3c6;
    }
    if (*(char *)(gNewBS + param_1 + 0x19) != '\x03') goto LAB_0906f2e8;
  }
  uVar6 = __udivsi3(uVar6 * 0xf,10);
LAB_0906f2e8:
  uVar1 = gBattleMons[param_1].species;
  uVar5 = IsDynamaxed(param_1);
  uVar7 = func_0x0906e2b4(iVar3,uVar4,uVar1,uVar6,uVar5);
  uVar6 = gNewBS;
  iVar3 = GetBattlerSide(param_1);
  if (*(char *)(uVar6 + iVar3 + 0x13) != '\0') {
    uVar7 = uVar7 << 1;
  }
  iVar3 = func_0x09075480(param_1);
  if (iVar3 != 0) {
    uVar7 = uVar7 >> 2;
  }
  if (((gBattleMons[param_1].status1 & 0xff) == 0) || (uVar2 != 0x70)) {
    if ((int)(gBattleMons[param_1].status1 << 0x19) < 0) {
      uVar7 = uVar7 >> 1;
    }
  }
  else {
    uVar7 = uVar7 << 1;
  }
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return uVar7;
}

// ---- sub_9071268  (ROM 0x9071268)
void sub_9071268(undefined4 param_1,undefined4 param_2)

{
  GetMonData(param_2,0x2d,0);
  return;
}

// ---- GetBankPartyData  (ROM 0x9073980)
Pokemon * GetBankPartyData(int param_1)

{
  ushort uVar1;
  Pokemon *pPVar2;
  int iVar3;
  
  uVar1 = gBattlerPartyIndexes[param_1];
  iVar3 = GetBattlerSide(param_1);
  if (iVar3 == 1) {
    pPVar2 = gEnemyParty;
  }
  else {
    pPVar2 = gPlayerParty;
  }
  return pPVar2 + (byte)uVar1;
}

// ---- sub_90739b4  (ROM 0x90739b4)
ushort sub_90739b4(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = IsDynamaxed();
  if (iVar2 == 0) {
    uVar1 = gBattleMons[param_1].hp;
  }
  else {
    uVar1 = gBattleMons[param_1].hp;
    uVar3 = func_0x0908eab4(param_1);
    iVar2 = sub_900042a(uVar1,uVar3);
    uVar1 = MathMax(1,(gBattleMons[param_1].hp & 1) + iVar2);
  }
  return uVar1;
}

// ---- GetBaseMaxHP  (ROM 0x90739f8)
ushort GetBaseMaxHP(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = IsDynamaxed();
  if (iVar2 == 0) {
    uVar1 = gBattleMons[param_1].maxHP;
  }
  else {
    uVar1 = gBattleMons[param_1].maxHP;
    uVar3 = func_0x0908eab4(param_1);
    iVar2 = sub_900042a(uVar1,uVar3);
    uVar1 = MathMax(1,(gBattleMons[param_1].maxHP & 1) + iVar2);
  }
  return uVar1;
}

// ---- IsDamageHalvedDueToFullHP  (ROM 0x9073ab0)
bool IsDamageHalvedDueToFullHP(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  
  if ((gBattleMons[param_1].hp == gBattleMons[param_1].maxHP) &&
     (iVar1 = func_0x0905fb10(param_2), iVar1 != 0)) {
    if ((param_4 == 0x98) || (iVar1 = CheckTableForMove(param_3,&UNK_09040136), iVar1 != 0)) {
      iVar1 = CheckTableForAbility(param_2,0x9123906);
      bVar2 = iVar1 == 0;
    }
    else {
      bVar2 = true;
    }
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

// ---- sub_9073b08  (ROM 0x9073b08)
bool sub_9073b08(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  
  if ((*(short *)(param_1 + 0x56) == *(short *)(param_1 + 0x58)) &&
     (iVar1 = func_0x0905fb10(param_2), iVar1 != 0)) {
    if ((param_4 == 0x98) || (iVar1 = CheckTableForMove(param_3,&UNK_09040136), iVar1 != 0)) {
      iVar1 = CheckTableForAbility(param_2,0x9123906);
      bVar2 = iVar1 == 0;
    }
    else {
      bVar2 = true;
    }
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

// ---- ViableMonCountFromBank  (ROM 0x9073b6a)
void ViableMonCountFromBank(undefined4 param_1)

{
  Pokemon *pPVar1;
  int iVar2;
  
  iVar2 = GetBattlerSide(param_1);
  if (iVar2 == 0) {
    pPVar1 = gPlayerParty;
  }
  else {
    pPVar1 = gEnemyParty;
  }
  func_0x090c1a64(pPVar1);
  return;
}

// ---- sub_9073b90  (ROM 0x9073b90)
byte sub_9073b90(int param_1)

{
  return gBattleMoves[param_1].flags & 0x40;
}

// ---- sub_9073ba8  (ROM 0x9073ba8)
void sub_9073ba8(undefined4 param_1)

{
  CheckTableForMove(param_1,&UNK_0903ffea);
  return;
}

// ---- CheckRecoil  (ROM 0x9073bb8)
bool CheckRecoil(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if ((((param_1 == 0xa5) || (iVar1 = CheckTableForMove(param_1,&UNK_090401e6), iVar1 != 0)) ||
      (iVar1 = CheckTableForMove(param_1,&UNK_090401f2), iVar1 != 0)) ||
     (iVar1 = CheckTableForMove(param_1,&UNK_09040200), iVar1 != 0)) {
    bVar2 = true;
  }
  else {
    iVar1 = CheckTableForMove(param_1,&UNK_0904027c);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- sub_9073c04  (ROM 0x9073c04)
bool sub_9073c04(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = sub_905faa2();
  bVar2 = true;
  if (iVar1 == 0) {
    iVar1 = CheckTableForMove(param_2,&UNK_09040136);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- IsOfType  (ROM 0x9073c28)
bool IsOfType(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = (uint)gBattleMons[param_1].type1;
  uVar1 = (uint)gBattleMons[param_1].type2;
  uVar2 = (uint)gBattleMons[param_1].type3;
  if ((((uVar3 == 9) || (uVar3 - 0x13 < 2)) || (bVar4 = true, uVar3 != param_2)) &&
     ((((uVar1 == 9 || (uVar1 - 0x13 < 2)) || (bVar4 = true, uVar1 != param_2)) &&
      ((bVar4 = false, uVar2 != 9 && (1 < uVar2 - 0x13)))))) {
    bVar4 = uVar2 == param_2;
  }
  return bVar4;
}

// ---- StatsMaxed  (ROM 0x9073df4)
undefined4 StatsMaxed(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (gBattleMons[param_1].statStages[iVar1] < 0xc) {
      return 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 7);
  return 1;
}

// ---- sub_9073e20  (ROM 0x9073e20)
undefined4 sub_9073e20(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (gBattleMons[param_1].statStages[iVar1] < 0xc) {
      return 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 5);
  return 1;
}

// ---- sub_9073ea4  (ROM 0x9073ea4)
undefined4 sub_9073ea4(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (param_2 < gBattleMons[param_1].statStages[iVar1]) {
      return 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 7);
  return 0;
}

// ---- sub_9073f4c  (ROM 0x9073f4c)
bool sub_9073f4c(uint param_1,int param_2)

{
  return (param_1 & 0xfffffffb) == 0x2a3 || param_2 == 0x65;
}

// ---- LoadPartyRange  (ROM 0x9074010)
undefined8 LoadPartyRange(int param_1,char *param_2,char *param_3)

{
  int iVar1;
  char cVar2;
  Pokemon *pPStack_1c;
  
  iVar1 = GetBattlerSide(param_1);
  pPStack_1c = gEnemyParty;
  if (iVar1 != 1) {
    pPStack_1c = gPlayerParty;
  }
  if (((int)(gBattleTypeFlags << 9) < 0) && (iVar1 = GetBattlerSide(param_1), iVar1 == 0)) {
    *param_2 = '\0';
    iVar1 = GetBattlerPosition(param_1);
    if (iVar1 == 2) {
LAB_0907404a:
      cVar2 = '\x03';
LAB_0907404c:
      *param_2 = cVar2;
    }
  }
  else {
    if ((gBattleTypeFlags & 0x40) == 0) {
      if ((-1 < (int)(gBattleTypeFlags << 10)) || (iVar1 = GetBattlerSide(param_1), iVar1 != 1)) {
        *param_2 = '\0';
        cVar2 = '\x06';
        goto LAB_09074082;
      }
      *param_2 = '\0';
      iVar1 = GetBattlerPosition(param_1);
      if (iVar1 == 3) {
        *param_2 = '\x03';
      }
      goto LAB_0907407e;
    }
    if ((gBattleTypeFlags & 0x800000) != 0) {
      iVar1 = GetBattlerSide(param_1);
      if (iVar1 == 0) {
        *param_2 = '\0';
        goto LAB_0907406c;
      }
      if (param_1 != 1) goto LAB_0907404a;
      cVar2 = '\0';
      goto LAB_0907404c;
    }
    *param_2 = '\0';
LAB_0907406c:
    GetBattlerMultiplayerId(param_1);
    iVar1 = GetLinkTrainerFlankId();
    if (iVar1 == 1) goto LAB_0907404a;
  }
LAB_0907407e:
  cVar2 = *param_2 + '\x03';
LAB_09074082:
  *param_3 = cVar2;
  return CONCAT44(param_3,pPStack_1c);
}

// ---- HasMonToSwitchTo  (ROM 0x90740dc)
bool HasMonToSwitchTo(undefined4 param_1)

{
  undefined1 uVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  byte bStack_1e;
  byte bStack_1d;
  byte bStack_1c;
  byte bStack_1b;
  u8 uStack_1a;
  u8 auStack_19 [5];
  
  iVar3 = LoadPartyRange(param_1,&bStack_1e,&bStack_1d);
  uVar1 = gActiveBattler;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  gActiveBattler = (undefined1)param_1;
  LoadBattlersAndFoes(&bStack_1c,&bStack_1b,&uStack_1a,auStack_19);
  gActiveBattler = uVar1;
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  for (uVar4 = (uint)bStack_1e; uVar5 = (uint)bStack_1d, uVar4 < uVar5; uVar4 = uVar4 + 1 & 0xff) {
    iVar6 = iVar3 + uVar4 * 100;
    sVar2 = GetMonData(iVar6,0x41,0);
    if ((((sVar2 != 0) && (sVar2 != 0x19c)) && (iVar6 = GetMonData(iVar6,0x39,0), iVar6 != 0)) &&
       ((gBattlerPartyIndexes[bStack_1c] != uVar4 && (gBattlerPartyIndexes[bStack_1b] != uVar4))))
    break;
  }
  return uVar5 != uVar4;
}

// ---- ViableMonCountFromBankLoadPartyRange  (ROM 0x9074180)
undefined8 ViableMonCountFromBankLoadPartyRange(undefined4 param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  uStack_1c = param_2;
  uStack_18 = param_3;
  iVar1 = LoadPartyRange(param_1,(int)&uStack_1c + 2,(int)&uStack_1c + 3);
  uVar4 = uStack_1c >> 0x10 & 0xff;
  uVar3 = 0;
  iVar1 = iVar1 + uVar4 * 100;
  for (; (int)uVar4 < (int)(uStack_1c >> 0x18); uVar4 = uVar4 + 1) {
    if (((*(short *)(iVar1 + 0x20) != 0) &&
        (iVar2 = GetMonData(iVar1,0x2d,0), iVar2 == 0)) &&
       (*(short *)(iVar1 + 0x56) != 0)) {
      uVar3 = uVar3 + 1 & 0xff;
    }
    iVar1 = iVar1 + 100;
  }
  return CONCAT44(param_1,uVar3);
}

// ---- GetMonIdAndSideByMon  (ROM 0x907436e)
void GetMonIdAndSideByMon(Pokemon *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if ((param_1 < gPlayerParty) || (gPlayerParty + 5 < param_1)) {
    if ((param_1 < gEnemyParty) || (gEnemyParty + 5 < param_1)) {
      uVar2 = 0xff;
      *param_2 = 0xff;
    }
    else {
      uVar1 = __udivsi3(&param_1[-0x5247c].field_0x44,100);
      uVar2 = 1;
      *param_2 = uVar1;
    }
  }
  else {
    uVar1 = __udivsi3(&param_1[-0x52482].field_0x44,100);
    uVar2 = 0;
    *param_2 = uVar1;
  }
  *param_3 = uVar2;
  return;
}

// ---- sub_90743c0  (ROM 0x90743c0)
bool sub_90743c0(int param_1)

{
  return (uint)gBattleMons[param_1].attack + (uint)gBattleMons[param_1].spAttack <
         (uint)gBattleMons[param_1].defense + (uint)gBattleMons[param_1].spDefense;
}

// ---- sub_90743e8  (ROM 0x90743e8)
undefined8 sub_90743e8(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  if (((&UNK_02023f40)[param_1] != '\0') || (uVar2 = 0, param_2 != 0)) {
    uStack_14 = param_2;
    uStack_10 = param_3;
    iVar1 = LoadPartyRange(param_1,(int)&uStack_14 + 2,(int)&uStack_14 + 3);
    uVar2 = GetMonData(iVar1 + (uint)(byte)(&UNK_02023f44)[param_1] * 100,0x3a,0);
    uVar2 = MathMax(1,uVar2 >> 1);
    uVar2 = uVar2 & 0xffff;
  }
  return CONCAT44(param_1,uVar2);
}

// ---- sub_90744d8  (ROM 0x90744d8)
undefined8 sub_90744d8(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  
  iVar4 = SpeciesToNationalPokedexNum(param_1);
  uVar1 = func_0x090a5244(param_2);
  iVar2 = IsMail(param_2);
  if (iVar2 != 0) {
    uVar3 = 0;
    goto LAB_0907452c;
  }
  uVar3 = 0;
  if (param_2 - 0x1e5 < 2) goto LAB_0907452c;
  iVar2 = param_1 * 0x80;
  psVar5 = (short *)(&UNK_097cd9b0 + iVar2);
  if (uVar1 == 0x57) {
    iVar2 = -0x305;
LAB_09074548:
    iVar4 = iVar4 + iVar2;
LAB_09074526:
    uVar3 = (uint)(iVar4 != 0);
  }
  else {
    if (uVar1 < 0x58) {
      if (uVar1 == 0x49) {
        do {
          if ((*psVar5 == 0xfe) && (((ushort)psVar5[1] == param_2 || ((ushort)psVar5[1] == 0))))
          goto LAB_0907452c;
          psVar5 = psVar5 + 4;
        } while (psVar5 != (short *)(&UNK_097cda30 + iVar2));
      }
      else {
        if (uVar1 == 0x56) {
          iVar2 = -0x289;
          goto LAB_09074548;
        }
        if (uVar1 == 0x48) {
          iVar4 = iVar4 + -0xee;
LAB_09074524:
          iVar4 = iVar4 + -0xff;
          goto LAB_09074526;
        }
      }
    }
    else if (uVar1 == 0x5d) {
      do {
        if (((*psVar5 == 0xfe) && (psVar5[3] == 1)) &&
           (((ushort)psVar5[1] == param_2 || ((ushort)psVar5[1] == 0)))) goto LAB_0907452c;
        psVar5 = psVar5 + 4;
      } while (psVar5 != (short *)(&UNK_097cda30 + iVar2));
    }
    else if (uVar1 < 0x5e) {
      iVar4 = iVar4 + -0xe8;
      if (uVar1 == 0x5a) goto LAB_09074524;
    }
    else {
      if (uVar1 == 0x82) goto LAB_0907452c;
      if (uVar1 == 0x91) {
        iVar2 = -0x3f9;
        goto LAB_09074548;
      }
    }
    uVar3 = 1;
  }
LAB_0907452c:
  return CONCAT44(param_1,uVar3);
}

// ---- sub_90745b4  (ROM 0x90745b4)
bool sub_90745b4(int param_1)

{
  ushort uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = gBattleMons[param_1].item;
  if ((uVar1 == 0) ||
     ((-1 < gBattleTypeFlags << 0x1c && (iVar2 = GetBattlerSide(param_1), iVar2 == 0)))
     ) {
    bVar3 = false;
  }
  else {
    iVar2 = sub_90744d8(gBattleMons[param_1].species,uVar1);
    bVar3 = iVar2 != 0;
  }
  return bVar3;
}

// ---- MoveIgnoresSubstitutes  (ROM 0x907466c)
bool MoveIgnoresSubstitutes(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = sub_9073ba8();
  bVar2 = true;
  if ((iVar1 == 0) && (((param_2 != 0x66 || (param_1 == 0x90)) || (param_1 == 0x2a3)))) {
    iVar1 = CheckTableForMove(param_1,&UNK_0904002c);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- MonMoveBlockedBySubstitute  (ROM 0x90746a4)
bool MonMoveBlockedBySubstitute(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  if ((int)(gBattleMons[param_3].status2 << 7) < 0) {
    uVar1 = GetMonAbility(param_2);
    iVar2 = MoveIgnoresSubstitutes(param_1,uVar1);
    bVar3 = iVar2 == 0;
  }
  return bVar3;
}

// ---- sub_90746d8  (ROM 0x90746d8)
bool sub_90746d8(int param_1)

{
  return param_1 == 0x66;
}

// ---- sub_90746e0  (ROM 0x90746e0)
uint sub_90746e0(void)

{
  return (gBattleTypeFlags & 0x1ffffff) >> 0x18;
}

// ---- IsPlayerInControl  (ROM 0x90746f0)
bool IsPlayerInControl(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  undefined8 uVar3;
  
  iVar1 = GetBattlerSide(param_1);
  bVar2 = false;
  if (iVar1 != 1) {
    iVar1 = sub_90746e0();
    bVar2 = false;
    if (iVar1 == 0) {
      uVar3 = sub_90ad614();
      bVar2 = true;
      if ((int)uVar3 != 0) {
        iVar1 = GetBattlerPosition(param_1,(int)((ulonglong)uVar3 >> 0x20),param_3,&GetBattlerPosition);
        bVar2 = iVar1 != 2;
      }
    }
  }
  return bVar2;
}

// ---- CalcMoveSplit  (ROM 0x90747d8)
undefined8 CalcMoveSplit(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = CheckTableForMove(param_2,&UNK_090401a0);
  uVar3 = (uint)gBattleMoves[param_2].split;
  if ((iVar2 != 0) && (uVar3 != 2)) {
    uVar1 = gBattleMons[param_1].spAttack;
    iVar2 = gBattleMons[param_1].statStages[0] * 2;
    uVar4 = udivsi((uint)*(byte *)(iVar2 + 0x9124898) *
                               (uint)gBattleMons[param_1].attack,*(undefined1 *)(iVar2 + 0x9124899))
    ;
    iVar2 = gBattleMons[param_1].statStages[3] * 2;
    uVar3 = udivsi((uint)*(byte *)(iVar2 + 0x9124898) * (uint)uVar1,
                         *(undefined1 *)(iVar2 + 0x9124899));
    uVar3 = (uint)(uVar4 <= uVar3);
  }
  return CONCAT44(param_1,uVar3);
}

// ---- CalcMoveSplitFromParty  (ROM 0x907485c)
byte CalcMoveSplitFromParty(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = CheckTableForMove(param_2,&UNK_090401a0);
  if (iVar1 == 0) {
    bVar2 = gBattleMoves[param_2].split;
  }
  else {
    bVar2 = *(ushort *)(param_1 + 0x5a) <= *(ushort *)(param_1 + 0x60);
  }
  return bVar2;
}

// ---- FindMovePositionInMoveset  (ROM 0x9074898)
uint FindMovePositionInMoveset(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (gBattleMons[param_2].moves[uVar1] == param_1) break;
    uVar1 = uVar1 + 1;
  } while (uVar1 != 4);
  return uVar1 & 0xff;
}

// ---- MoveInMoveset  (ROM 0x90748c0)
bool MoveInMoveset(void)

{
  uint uVar1;
  
  uVar1 = FindMovePositionInMoveset();
  return uVar1 < 4;
}

// ---- sub_90748d2  (ROM 0x90748d2)
bool sub_90748d2(short param_1)

{
  return (ushort)(param_1 - 0x350U) < 0x35;
}

// ---- sub_9074a2c  (ROM 0x9074a2c)
uint sub_9074a2c(uint param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  if ((gBattleTypeFlags & 1) == 0) {
    uVar2 = ~param_1 & 1;
  }
  else {
    uVar4 = IsRaidBattle();
    if ((int)uVar4 == 0) {
      bVar1 = GetBattlerPosition(param_1,(int)((ulonglong)uVar4 >> 0x20),param_3,&GetBattlerPosition);
      bVar1 = bVar1 ^ 3;
    }
    else {
      iVar3 = GetBattlerSide(param_1);
      if (iVar3 == 0) {
        bVar1 = 1;
      }
      else {
        bVar1 = 0;
      }
    }
    uVar2 = GetBattlerAtPosition(bVar1);
  }
  return uVar2;
}

// ---- sub_9074a88  (ROM 0x9074a88)
undefined8 sub_9074a88(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1;
  iVar4 = param_2;
  iVar1 = sub_9074a2c();
  if ((((gBattleMons[iVar1].hp == 0) || ((gBattleMons[iVar1].status2 & 0x1200000) != 0)) ||
      ((gStatuses3[iVar1] & 0x930400c0) != 0)) ||
     (((param_2 == 0 && ((int)(gBattleMons[param_1].status2 << 10) < 0)) ||
      (iVar1 = sub_908ee64(), iVar1 != 0)))) {
    iVar1 = iVar3;
    uVar2 = 0;
  }
  else {
    iVar3 = AbilityBattleEffects(0x13,0,0x4a,0,0,iVar4,param_3);
    uVar2 = (uint)(iVar3 == 0);
  }
  return CONCAT44(iVar1,uVar2);
}

// ---- sub_9074ba4  (ROM 0x9074ba4)
undefined4 sub_9074ba4(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined1 uStack_1a;
  undefined1 auStack_19 [5];
  
  iVar1 = LoadPartyRange(param_1,&uStack_1a,auStack_19);
  iVar4 = iVar1 + 600;
  while (((iVar2 = GetMonData(iVar1,0x39,0), iVar2 == 0 ||
          (iVar2 = GetMonData(iVar1,0x2d,0), iVar2 != 0)) ||
         (uVar3 = GetMonData(iVar1,0x37), (uVar3 & 7) == 0))) {
    iVar1 = iVar1 + 100;
    if (iVar1 == iVar4) {
      return 0;
    }
  }
  return 1;
}

// ---- CanFlinch  (ROM 0x9074c28)
bool CanFlinch(undefined4 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  if (param_2 != 0x27) {
    iVar1 = IsDynamaxed();
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}

// ---- IsTrickRoomActive  (ROM 0x9074c3c)
bool IsTrickRoomActive(void)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = true;
  if ((*(char *)(gNewBS + 3) == '\0') &&
     ((-1 < gBattleTypeFlags << 5 || (-1 < _UNK_0203e044 << 0x16)))) {
    iVar1 = VarGet(0x5119);
    bVar2 = iVar1 == 0xc;
  }
  return bVar2;
}

// ---- sub_9074c80  (ROM 0x9074c80)
bool sub_9074c80(void)

{
  int iVar1;
  bool bVar2;
  
  if (((gBattleTypeFlags << 5 < 0) && (_UNK_0203e044 << 0x16 < 0)) ||
     (iVar1 = VarGet(0x5119), iVar1 == 0xc)) {
    bVar2 = false;
  }
  else {
    bVar2 = *(char *)(gNewBS + 3) == '\x01';
  }
  return bVar2;
}

// ---- sub_9074cc4  (ROM 0x9074cc4)
uint sub_9074cc4(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 4) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x7ff) >> 10;
  }
  return uVar1;
}

// ---- sub_9074cf0  (ROM 0x9074cf0)
bool sub_9074cf0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,char param_5)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = func_0x090a5244();
  if (((((((param_1 == 0) || (iVar2 = sub_9074cc4(), iVar2 != 0)) || (param_5 != '\0')) ||
        ((iVar2 = sub_90744d8(param_2,param_1), iVar2 == 0 || ((iVar1 - 0x5dU & 0xff) < 2)))) ||
       ((iVar1 == 0x83 ||
        ((iVar1 = sub_90a52de(param_1), iVar1 != 0 &&
         (iVar1 = AbilityBattleEffects(0xc,param_4,0xc0,0,0), iVar1 != 0)))))) ||
      ((iVar1 = sub_90a52de(param_1), iVar1 != 0 &&
       (iVar1 = AbilityBattleEffects(0xc,param_4,0x4d,0,0), iVar1 != 0)))) ||
     ((iVar1 = sub_90a52de(param_1), iVar1 != 0 &&
      (iVar1 = AbilityBattleEffects(0xc,param_4,0x49,0,0), iVar1 != 0)))) {
    bVar3 = false;
  }
  else {
    iVar1 = GetPocketByItemId(param_1);
    bVar3 = iVar1 != 3;
  }
  return bVar3;
}

// ---- sub_9074de4  (ROM 0x9074de4)
undefined4 sub_9074de4(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = sub_9074cc4();
  uVar3 = 0;
  if (iVar2 == 0) {
    uVar1 = GetMonData(param_1,0xc);
    uVar3 = func_0x090a5244(uVar1);
  }
  return uVar3;
}

// ---- sub_9074e56  (ROM 0x9074e56)
bool sub_9074e56(undefined4 param_1)

{
  int iVar1;
  
  GetMonAbility();
  iVar1 = sub_9074de4(param_1);
  return iVar1 == 0x65;
}

// ---- sub_9074eb8  (ROM 0x9074eb8)
bool sub_9074eb8(void)

{
  int iVar1;
  
  iVar1 = sub_9074de4();
  return iVar1 != 0x87;
}

// ---- GetBankItemEffect  (ROM 0x9074ec6)
undefined4 GetBankItemEffect(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if ((*(char *)(gNewBS + param_1 + 0x3d) == '\0') && (iVar1 = sub_9074cc4(), iVar1 == 0)) {
    uVar2 = func_0x090a5244(gBattleMons[param_1].item);
  }
  return uVar2;
}

// ---- sub_9075008  (ROM 0x9075008)
bool sub_9075008(void)

{
  int iVar1;
  
  iVar1 = GetBankItemEffect();
  return iVar1 == 0x65;
}

// ---- CheckContact  (ROM 0x907503c)
bool CheckContact(int param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  
  if (((gBattleMoves[param_1].flags & 1) == 0) ||
     (iVar1 = GetBankItemEffect(param_2), iVar1 == 0x65)) {
    bVar2 = false;
  }
  else {
    iVar1 = GetBankItemEffect(param_2);
    bVar2 = true;
    if (iVar1 == 0x8a) {
      iVar1 = CheckTableForMove(param_1,&UNK_0903fe9a);
      bVar2 = iVar1 == 0;
    }
  }
  return bVar2;
}

// ---- sub_9075096  (ROM 0x9075096)
uint sub_9075096(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 5) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0xfff) >> 0xb;
  }
  return uVar1;
}

// ---- sub_90750c4  (ROM 0x90750c4)
uint sub_90750c4(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 2) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x1fff) >> 0xc;
  }
  return uVar1;
}

// ---- CheckMoveLimitationsFromParty  (ROM 0x90750f0)
uint CheckMoveLimitationsFromParty(undefined4 param_1,uint param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = sub_9074de4();
  iVar4 = 0xd;
  do {
    uVar1 = GetMonData(param_1,iVar4,0);
    if ((((uVar1 == 0) && (param_3 << 0x1f < 0)) ||
        ((iVar3 = GetMonData(param_1,iVar4 + 4,0,&GetMonData), iVar3 == 0 &&
         (param_3 << 0x1e < 0)))) ||
       ((((iVar2 == 0x46 && (gBattleMoves[uVar1].split == 2)) ||
         ((iVar3 = FlagGet(0x901), iVar3 != 0 &&
          (iVar3 = CheckTableForMove(uVar1,&UNK_0903fc58), iVar3 != 0)))) ||
        (((iVar3 = sub_90750c4(), iVar3 != 0 &&
          (iVar3 = CheckTableForMove(uVar1,&UNK_0903f930), iVar3 != 0)) ||
         ((iVar3 = IsRaidBattle(), iVar3 != 0 &&
          (iVar3 = CheckTableForMove(uVar1,&UNK_0903fca8), iVar3 != 0)))))))) {
      param_2 = (param_2 | *(uint *)((iVar4 + 0x209790a) * 4)) & 0xff;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x11);
  return param_2;
}

// ---- sub_90751c8  (ROM 0x90751c8)
bool sub_90751c8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = GetMonData(param_1,0xb,0,param_4,param_4);
  uVar1 = GetMonData(param_1,0xc,0);
  iVar2 = sub_90750c4();
  if ((iVar2 == 0) && (iVar2 = func_0x090a5244(uVar1), iVar2 != 0x62)) {
    iVar2 = GetMonAbility(param_1);
    bVar4 = false;
    if ((iVar2 != 0x1a) && (iVar2 = (uVar3 & 0xffff) * 0x1c, (&UNK_097b98f2)[iVar2] != '\x02')) {
      bVar4 = (&UNK_097b98f3)[iVar2] != '\x02';
    }
  }
  else {
    bVar4 = true;
  }
  return bVar4;
}

// ---- sub_9075238  (ROM 0x9075238)
uint sub_9075238(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 7) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x3fff) >> 0xd;
  }
  return uVar1;
}

// ---- sub_9075264  (ROM 0x9075264)
uint sub_9075264(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 6) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x7fff) >> 0xe;
  }
  return uVar1;
}

// ---- sub_9075290  (ROM 0x9075290)
uint sub_9075290(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)gNewBS == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0xffff) >> 0xf;
  }
  return uVar1;
}

// ---- sub_90752bc  (ROM 0x90752bc)
uint sub_90752bc(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + 1) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x1ffff) >> 0x10;
  }
  return uVar1;
}

// ---- sub_907531c  (ROM 0x907531c)
bool sub_907531c(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = GetBattlerSide(param_1);
  bVar2 = true;
  if ((-1 < (int)((uint)gSideStatuses[iVar1] << 0x1a)) &&
     ((-1 < gBattleTypeFlags << 5 || (-1 < _UNK_0203e044 << 0xb)))) {
    iVar1 = VarGet(0x5119);
    bVar2 = false;
    if (iVar1 == 0x23) {
      iVar1 = GetBattlerSide(param_1);
      bVar2 = iVar1 == 1;
    }
  }
  return bVar2;
}

// ---- sub_9075378  (ROM 0x9075378)
bool sub_9075378(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = GetBattlerSide(param_1);
  bVar2 = true;
  if ((-1 < (int)((uint)gSideStatuses[iVar1] << 0x17)) &&
     ((-1 < gBattleTypeFlags << 5 || (-1 < _UNK_0203e044 << 10)))) {
    iVar1 = VarGet(0x5119);
    bVar2 = false;
    if (iVar1 == 0x23) {
      iVar1 = GetBattlerSide(param_1);
      bVar2 = iVar1 == 1;
    }
  }
  return bVar2;
}

// ---- sub_90753d4  (ROM 0x90753d4)
undefined1 sub_90753d4(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = gNewBS;
  iVar2 = GetBattlerSide(param_1);
  return *(undefined1 *)(uVar1 + iVar2 + 0x13);
}

// ---- sub_9075444  (ROM 0x9075444)
uint sub_9075444(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = gNewBS;
  iVar3 = GetBattlerSide(param_1);
  uVar2 = 1;
  if ((*(char *)(uVar1 + iVar3 + 0xd) == '\0') && (uVar2 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar2 = (_UNK_0203e044 & 0xffffff) >> 0x17;
  }
  return uVar2;
}

// ---- sub_90754f0  (ROM 0x90754f0)
uint sub_90754f0(int param_1)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + param_1 + 0x31) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0xfffffff) >> 0x1b;
  }
  return uVar1;
}

// ---- sub_9075520  (ROM 0x9075520)
uint sub_9075520(int param_1)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + param_1 + 0x39) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x1fffffff) >> 0x1c;
  }
  return uVar1;
}

// ---- sub_9075550  (ROM 0x9075550)
uint sub_9075550(int param_1)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*(char *)(gNewBS + param_1 + 0x35) == '\0') && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = (_UNK_0203e044 & 0x3fffffff) >> 0x1d;
  }
  return uVar1;
}

// ---- IsAbilitySuppressed  (ROM 0x9075580)
uint IsAbilitySuppressed(int param_1)

{
  uint uVar1;
  
  uVar1 = 1;
  if (((gStatuses3[param_1] & 0x8000000) == 0) && (uVar1 = 0, gBattleTypeFlags << 5 < 0)) {
    uVar1 = _UNK_0203e044 >> 0x1f;
  }
  return uVar1;
}

// ---- GetAbilityLocation  (ROM 0x90755ec)
int GetAbilityLocation(int param_1)

{
  int iVar1;
  
  iVar1 = IsAbilitySuppressed();
  if (iVar1 == 0) {
    if (*(char *)(gNewBS + param_1 + 0x79) == '\0') {
      if (*(char *)(gNewBS + param_1 + 0x71) == '\0') {
        return param_1 * 0x58 + 0x2023c04;
      }
      param_1 = param_1 + 0x71;
    }
    else {
      param_1 = param_1 + 0x79;
    }
  }
  else {
    param_1 = param_1 + 0x75;
  }
  return gNewBS + param_1;
}

// ---- GetBankAbility  (ROM 0x90757d0)
byte GetBankAbility(int param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = IsAbilitySuppressed();
  bVar2 = 0;
  if (iVar1 == 0) {
    bVar2 = gBattleMons[param_1].ability;
  }
  return bVar2;
}

// ---- sub_90757f4  (ROM 0x90757f4)
byte sub_90757f4(int param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  
  bVar2 = gDisableStructs[param_1].field_0x13 & 0xf;
  bVar3 = 1;
  if ((((gDisableStructs[param_1].field_0x13 & 0xf) == 0) &&
      (bVar3 = bVar2, gBattleTypeFlags << 5 < 0)) && (_UNK_0203e044 << 6 < 0)) {
    iVar1 = GetBankAbility();
    bVar3 = iVar1 != 0xc;
  }
  return bVar3;
}

// ---- sub_9075a8c  (ROM 0x9075a8c)
bool sub_9075a8c(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  puVar3 = (undefined4 *)GetBankPartyData(param_2);
  puVar4 = (undefined4 *)GetBankPartyData(param_1);
  if (((gBattleMons[param_1].hp != 0) && ((gBattleMons[param_1].status2 & 0xf0000) == 0)) &&
     (iVar5 = GetBankAbility(param_1), iVar5 != 0xc)) {
    uVar1 = *(undefined2 *)(puVar3 + 8);
    uVar2 = *(undefined2 *)(puVar4 + 8);
    uVar8 = *puVar3;
    uVar7 = *puVar4;
    iVar6 = GetGenderFromSpeciesAndPersonality(uVar1,uVar8);
    iVar5 = GetGenderFromSpeciesAndPersonality(uVar2,uVar7);
    if (((iVar6 != iVar5) && (iVar5 = GetGenderFromSpeciesAndPersonality(uVar1,uVar8), iVar5 != 0xff)) &&
       (iVar5 = GetGenderFromSpeciesAndPersonality(uVar2,uVar7), iVar5 != 0xff)) {
      iVar5 = AbilityBattleEffects(0xd,param_1,0xc9,0,0);
      return iVar5 == 0;
    }
  }
  return false;
}

// ---- MoveBlockedBySubstitute  (ROM 0x9075b98)
bool MoveBlockedBySubstitute(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  if ((int)(gBattleMons[param_3].status2 << 7) < 0) {
    uVar1 = GetBankAbility(param_2);
    iVar2 = MoveIgnoresSubstitutes(param_1,uVar1);
    bVar3 = iVar2 == 0;
  }
  return bVar3;
}

// ---- IsAffectedByPowder  (ROM 0x9075bcc)
void IsAffectedByPowder(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  bVar1 = gBattleMons[param_1].type1;
  bVar2 = gBattleMons[param_1].type2;
  bVar3 = gBattleMons[param_1].type3;
  uVar4 = GetBankAbility();
  uVar5 = GetBankItemEffect(param_1);
  func_0x09074648(bVar1,bVar2,bVar3,uVar4,uVar5);
  return;
}

// ---- CheckMoveLimitations  (ROM 0x9075f84)
uint CheckMoveLimitations(int param_1,uint param_2,undefined4 param_3)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar2 = GetBankAbility();
  uVar3 = GetBankItemEffect(param_1);
  uVar1 = gBattleStruct->choicedMove[param_1];
  iVar5 = 0;
                    /* WARNING: Read-only address (ram,0x02023d6f) is written */
  UNK_02023d6f = (undefined1)param_1;
  do {
    uVar6 = (uint)gBattleMons[param_1].moves[iVar5];
    iVar4 = IsDynamaxed(param_1);
    if (iVar4 != 0) {
      uVar6 = GetMaxMoveByMove(param_1,uVar6);
    }
    iVar4 = func_0x09075838(uVar6,param_1,param_3,gBattleMons[param_1].pp[iVar5],uVar2,uVar3,uVar1);
    if (iVar4 != 0) {
      param_2 = (param_2 | *(uint *)((iVar5 + 0x2097917) * 4)) & 0xff;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 4);
  return param_2;
}

// ---- CheckGrounding  (ROM 0x9076054)
bool CheckGrounding(int param_1)

{
  int iVar1;
  
  if ((gStatuses3[param_1] & 0x130400c0) == 0) {
    iVar1 = sub_90750c4();
    if (((iVar1 != 0) || (iVar1 = GetBankItemEffect(param_1), iVar1 == 0x62)) ||
       ((gStatuses3[param_1] & 0x400400) != 0)) {
      return true;
    }
    if ((((gStatuses3[param_1] & 0x20200040) == 0) &&
        (iVar1 = GetBankItemEffect(param_1), iVar1 != 0x67)) &&
       ((iVar1 = GetBankAbility(param_1), iVar1 != 0x1a &&
        ((gBattleMons[param_1].type3 != 2 && (gBattleMons[param_1].type1 != 2)))))) {
      return gBattleMons[param_1].type2 != 2;
    }
  }
  return false;
}

// ---- CanBeConfused  (ROM 0x90760d8)
uint CanBeConfused(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = func_0x09075a44();
  if ((iVar1 == 0) &&
     (((gTerrainType != '\x03' || (iVar1 = CheckGrounding(param_1), iVar1 == 0)) &&
      (iVar1 = GetBankAbility(param_1), iVar1 != 0x14)))) {
    if ((param_2 == 0) ||
       (iVar1 = GetBattlerSide(param_1), -1 < (int)((uint)gSideStatuses[iVar1] << 0x1a))
       ) {
      uVar2 = 1;
    }
    else {
      uVar2 = (gHitMarker & 0x3fff) >> 0xd;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ---- CanBeFrozen  (ROM 0x90762c4)
undefined8 CanBeFrozen(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = param_1;
  iVar1 = func_0x09076204();
  uVar4 = 0;
  if (iVar1 != 0) {
    iVar1 = IsOfType(param_1,0xf /* Ice */);
    if (iVar1 == 0) {
      iVar2 = GetBankAbility(param_1);
      uVar4 = 0;
      if (iVar2 != 0x28) {
        iVar2 = AbilityBattleEffects(0x13,0,0xd,0,0,param_2,param_3);
        uVar4 = 1;
        iVar3 = iVar1;
        if ((iVar2 == 0) && ((gBattleWeather & 0x860) != 0)) {
          iVar3 = GetBankItemEffect(param_1);
          uVar4 = (uint)(iVar3 == 0x88);
          iVar3 = iVar1;
        }
      }
    }
    else {
      uVar4 = 0;
    }
  }
  return CONCAT44(iVar3,uVar4);
}

// ---- CanBeBurned  (ROM 0x9076320)
undefined4 CanBeBurned(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x09076204();
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = IsOfType(param_1,10 /* Fire */);
    if (iVar1 == 0) {
      iVar1 = GetBankAbility(param_1);
      uVar2 = 0;
      if (((iVar1 != 0xaf) && (iVar1 != 0xb1)) && (iVar1 != 0x29)) {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

// ---- CanBeParalyzed  (ROM 0x9076354)
undefined4 CanBeParalyzed(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x09076204();
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = IsOfType(param_1,0xd /* Electric */);
    if (iVar1 == 0) {
      iVar1 = GetBankAbility(param_1);
      uVar2 = 0;
      if (iVar1 != 7) {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

// ---- CanBePoisoned  (ROM 0x9076380)
bool CanBePoisoned(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = func_0x09076204(param_1,param_3);
  bVar2 = false;
  if (iVar1 != 0) {
    iVar1 = GetBankAbility(param_1);
    bVar2 = false;
    if (iVar1 != 0x11) {
      iVar1 = GetBankAbility(param_2);
      if (iVar1 == 0x9e) {
        bVar2 = true;
      }
      else {
        iVar1 = IsOfType(param_1,3 /* Poison */);
        if (iVar1 == 0) {
          iVar1 = IsOfType(param_1,8 /* Steel */);
          bVar2 = iVar1 == 0;
        }
      }
    }
  }
  return bVar2;
}

// ---- sub_90763c6  (ROM 0x90763c6)
bool sub_90763c6(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = func_0x09076204();
  if ((((iVar1 == 0) || (iVar1 = GetBankAbility(param_1), iVar1 == 0xf)) || (iVar1 == 0x4e)) ||
     ((gTerrainType == '\x01' && (iVar1 = CheckGrounding(param_1), iVar1 != 0)))) {
    bVar2 = false;
  }
  else {
    iVar1 = sub_9074ba4(param_1);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}

// ---- CanBePutToSleep  (ROM 0x9076408)
bool CanBePutToSleep(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = func_0x09076204();
  if ((((iVar1 == 0) || (iVar1 = GetBankAbility(param_1), iVar1 == 0xf)) || (iVar1 == 0x4e)) ||
     ((gTerrainType == '\x01' && (iVar1 = CheckGrounding(param_1), iVar1 != 0)))) {
    bVar2 = false;
  }
  else {
    iVar1 = sub_9074ba4(param_1);
    if (iVar1 == 0) {
      bVar2 = true;
    }
    else {
      iVar1 = GetBankAbility(param_3);
      bVar2 = iVar1 == 0xce;
    }
  }
  return bVar2;
}

// ---- GetBaseMoveTarget  (ROM 0x907645c)
byte GetBaseMoveTarget(int param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  
  if ((((param_1 == 0x2c9) && (gBattleTypeFlags << 0x1f < 0)) && (gTerrainType == '\x04')) &&
     (iVar2 = CheckGrounding(param_2), iVar2 != 0)) {
    bVar1 = 8;
  }
  else {
    bVar1 = gBattleMoves[param_1].target;
  }
  return bVar1;
}

// ---- sub_907659c  (ROM 0x907659c)
bool sub_907659c(int param_1)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = true;
  if (param_1 != 0) {
    iVar1 = sub_9074cc4();
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- sub_90765b2  (ROM 0x90765b2)
void sub_90765b2(void)

{
  CheckGrounding();
  return;
}

// ---- sub_9076620  (ROM 0x9076620)
bool sub_9076620(int param_1)

{
  return param_1 == 0x88;
}

// ---- sub_9076636  (ROM 0x9076636)
bool sub_9076636(void)

{
  int iVar1;
  
  iVar1 = func_0x09076628();
  return iVar1 == 0;
}

// ---- sub_9076642  (ROM 0x9076642)
undefined8 sub_9076642(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uStack_18;
  
  uStack_18 = param_1;
  if ((((gBattleMons[param_1].hp == gBattleMons[param_1].maxHP) ||
       ((gTerrainType == '\x01' && (iVar1 = CheckGrounding(), iVar1 != 0)))) ||
      ((gTerrainType == '\x03' && (iVar1 = CheckGrounding(param_1), iVar1 != 0)))) ||
     ((((gBattleMons[param_1].status1 & 7) != 0 || (iVar1 = sub_9074ba4(param_1), iVar1 != 0)) ||
      (iVar1 = func_0x09074238(), iVar1 != 0)))) {
    uVar3 = 0;
  }
  else {
    if (((gBattleTypeFlags & 1) == 0) || (iVar1 = GetBankAbility(param_1 ^ 2), iVar1 != 0x4e)) {
      uVar2 = GetBankAbility(param_1);
      if (uVar2 == 0xaa) {
        iVar1 = GetBankPartyData(param_1);
        uVar3 = (uint)(*(short *)(iVar1 + 0x20) != 0x3df);
        goto LAB_0907665a;
      }
      uVar3 = 0;
      if (uVar2 < 0xab) {
        if ((uVar2 == 0x48) || (uVar2 == 0x4e)) goto LAB_0907665a;
      }
      else if (uVar2 == 0xcb) {
        if ((gBattleWeather & 0x860) != 0) {
          uStack_18 = 0;
          iVar1 = AbilityBattleEffects(0x13,0,0xd,0);
          if (iVar1 == 0) {
            iVar1 = sub_9076636(param_1);
            uVar3 = (uint)(iVar1 == 0);
            goto LAB_0907665a;
          }
        }
      }
      else if (uVar2 == 0xe7) goto LAB_0907665a;
    }
    uVar3 = 1;
  }
LAB_0907665a:
  return CONCAT44(uStack_18,uVar3);
}

// ---- sub_9076728  (ROM 0x9076728)
void sub_9076728(void)

{
  sub_9076636();
  return;
}

// ---- IsChoiceItemEffectOrAbility  (ROM 0x9076730)
bool IsChoiceItemEffectOrAbility(int param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = true;
  if (param_1 != 0x1d) {
    iVar1 = func_0x0905fac6(param_2);
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- CanBeChoiceLocked  (ROM 0x9076748)
void CanBeChoiceLocked(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = GetBankItemEffect();
  uVar2 = GetBankAbility(param_1);
  IsChoiceItemEffectOrAbility(uVar1,uVar2);
  return;
}

// ---- GetMonAbility  (ROM 0x9079808)
void GetMonAbility(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = GetMonData(param_1,0xb,0,param_4,param_4);
  iVar4 = (uVar3 & 0xffff) * 0x1c;
  if (0x7f < *(byte *)(param_1 + 0x4b)) {
    cVar1 = (&UNK_097b9906)[iVar4];
    if (cVar1 != '\0') goto LAB_09079838;
  }
  iVar2 = GetMonData(param_1,0);
  if (iVar2 << 0x1f < 0) {
    cVar1 = (&UNK_097b9903)[iVar4];
    if (cVar1 != '\0') goto LAB_09079838;
  }
  cVar1 = (&UNK_097b9902)[iVar4];
LAB_09079838:
  func_0x090796bc(cVar1,param_1);
  return;
}

// ---- sub_908367c  (ROM 0x908367c)
void sub_908367c(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = GetMonAbility();
  iVar2 = func_0x09083610(param_2,0,param_1);
  if (iVar2 == 0xff) {
    func_0x09083054(param_2,uVar1,0);
  }
  return;
}

// ---- GetMoveTypeSpecial  (ROM 0x90836a2)
void GetMoveTypeSpecial(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = GetBankAbility();
  iVar2 = func_0x09083610(param_2,param_1,0);
  if (iVar2 == 0xff) {
    func_0x09083054(param_2,uVar1,(*(byte *)(gNewBS + 0x19c) & 9) != 0);
  }
  return;
}

// ---- AI_SpecialTypeCalc  (ROM 0x90838a4)
void AI_SpecialTypeCalc(int param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  u8 uVar3;
  u8 uVar4;
  move_t move;
  int iVar5;
  uint uVar6;
  int iVar7;
  u8 bankDef;
  byte bVar8;
  uint uStack_30;
  uint uStack_2c;
  uint uStack_28;
  byte abStack_19 [5];
  
  uVar4 = (u8)param_2;
  bankDef = (u8)param_3;
  uVar3 = GetAIAbility(uVar4,bankDef,(u16)param_1);
  move = IsValidMovePrediction(bankDef,uVar4);
  uVar4 = GetAIAbility(bankDef,uVar4,move);
  iVar5 = GetBankItemEffect(param_3);
  abStack_19[0] = 0;
  if (param_1 == 0xa5) {
    return;
  }
  bVar8 = gBattleMons[param_2].type1;
  bVar1 = gBattleMons[param_2].type2;
  bVar2 = gBattleMons[param_2].type3;
  uVar6 = GetMoveTypeSpecial(param_2,param_1);
  uStack_30 = (uint)bVar8;
  uStack_2c = (uint)bVar1;
  uStack_28 = (uint)bVar2;
  if (uVar3 == 0x96) {
    uStack_30 = uVar6;
    uStack_2c = uVar6;
    uStack_28 = uVar6;
  }
  bVar8 = gBattleMons[param_3].type1;
  bVar1 = gBattleMons[param_3].type2;
  bVar2 = gBattleMons[param_3].type3;
  if (((uStack_30 == uVar6) || (uStack_2c == uVar6)) || (uStack_28 == uVar6)) {
    iVar7 = gBattleMoveDamage << 1;
    if (uVar3 != 0x58) {
      iVar7 = sub_900042a(gBattleMoveDamage * 0x96,100);
    }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
    gBattleMoveDamage = iVar7;
  }
  if (((((uVar6 == 4) && (iVar7 = CheckGrounding(param_3), iVar7 == 0)) &&
       ((((uVar4 == 0x1a &&
          ((uVar3 != 0x98 && (iVar7 = CheckTableForMove(param_1,&UNK_09040136), iVar7 == 0)))) ||
         (iVar5 == 0x67)) || ((gStatuses3[param_3] & 0x20200000) != 0)))) &&
      ((param_1 != 0x23c &&
       ((uVar3 != 0xe9 || (iVar7 = CheckTableForMove(param_1,&UNK_0903ff2a), iVar7 == 0)))))) ||
     ((iVar7 = CheckTableForMove(param_1,&UNK_0903ffd8), iVar7 != 0 &&
      (iVar5 = func_0x09074648(bVar8,bVar1,bVar2,uVar4,iVar5), iVar5 == 0)))) {
    bVar8 = 9;
  }
  else {
    if ((param_1 != 0x2a3) || (((bVar8 != 2 && (bVar1 != 2)) && (bVar2 != 2)))) {
      func_0x09082090(uVar3,param_3,param_1,uVar6,abStack_19,bVar8,bVar1,bVar2);
      goto LAB_090839f6;
    }
    bVar8 = 8;
  }
  abStack_19[0] = bVar8 | abStack_19[0];
LAB_090839f6:
  bVar8 = abStack_19[0];
  if ((uVar4 == 0x19) && (uVar3 != 0x98)) {
    uVar6 = (uint)abStack_19[0];
    iVar5 = CheckTableForMove(param_1,&UNK_09040136);
    if ((((iVar5 == 0) &&
         ((-1 < (int)(uVar6 << 0x1f) && (iVar5 = (*(code *)0x9074f00)(param_2,param_1), iVar5 == 2))
         )) && (((bVar8 & 2) == 0 || ((uVar6 & 6) == 6)))) &&
       ((gBattleMoves[param_1].power != 0 && (gBattleMoves[param_1].split != 2)))) {
      abStack_19[0] = bVar8 | 1;
    }
  }
  if ((abStack_19[0] & 0x29) != 0) {
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
    gBattleMoveDamage = 0;
  }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  return;
}

// ---- AI_TypeCalc  (ROM 0x9083abc)
byte AI_TypeCalc(int param_1,int param_2,undefined4 param_3,Pokemon *param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  u8 uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uStack_44;
  uint uStack_40;
  byte abStack_19 [5];
  
  if (param_1 == 0xa5) {
    return 0;
  }
  abStack_19[0] = 0;
  uVar5 = GetMonAbilityAfterTrace(param_4,(u8)param_2);
  uVar10 = (uint)uVar5;
  uVar6 = ItemId_GetHoldEffectParam(param_4->item);
  uStack_44 = func_0x090c1d94(param_4,0);
  uStack_40 = func_0x090c1d94(param_4,1);
  iVar7 = GetBankAbility(param_2);
  bVar1 = gBattleMons[param_2].type1;
  bVar2 = gBattleMons[param_2].type2;
  bVar3 = gBattleMons[param_2].type3;
  uVar8 = GetMoveTypeSpecial(param_2,param_1);
  bVar4 = 0x14;
  if ((uVar10 == 0xc5) && (iVar9 = sub_9074a88(param_3,1), iVar9 != 0)) {
    iVar9 = sub_9074a2c(param_3);
    uVar10 = GetBankAbility();
    uStack_44 = (uint)gBattleMons[iVar9].type1;
    uStack_40 = (uint)gBattleMons[iVar9].type2;
    bVar4 = gBattleMons[iVar9].type3;
  }
  iVar9 = IsTargetAbilityIgnored(uVar10,iVar7,param_1);
  uVar10 = uVar10 & -(uint)(iVar9 == 0);
  if (((bVar1 == uVar8) || (bVar2 == uVar8)) || (bVar3 == uVar8)) {
    if (iVar7 == 0x58) {
      gBattleMoveDamage = gBattleMoveDamage << 1;
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
      goto LAB_09083bb8;
    }
  }
  else if (iVar7 != 0x96) goto LAB_09083bb8;
  gBattleMoveDamage = udivsi(gBattleMoveDamage * 0xf,10);
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
LAB_09083bb8:
  if ((((uVar8 == 4) && (iVar9 = sub_90751c8(param_4), iVar9 == 0)) &&
      ((uVar10 == 0x1a &&
       ((iVar7 != 0x98 && (iVar9 = CheckTableForMove(param_1,&UNK_09040136), iVar9 == 0)))))) &&
     (param_1 != 0x23c)) {
    abStack_19[0] = 9;
  }
  else {
    iVar9 = CheckTableForMove(param_1,&UNK_0903ffd8);
    if ((iVar9 == 0) || (iVar9 = func_0x09074648(uStack_44,uStack_40,0xff,uVar10,uVar6), iVar9 != 0)
       ) {
      func_0x09082090(iVar7,param_3,param_1,uVar8,abStack_19,uStack_44,uStack_40,bVar4);
      if (uVar10 != 0x19) {
        return abStack_19[0];
      }
      if (((int)((uint)abStack_19[0] << 0x1e) < 0) && ((abStack_19[0] & 6) != 6)) {
        return abStack_19[0];
      }
    }
    else {
      abStack_19[0] = 9;
      if (uVar10 != 0x19) {
        return 9;
      }
    }
    if (gBattleMoves[param_1].power != 0) {
      abStack_19[0] = abStack_19[0] | 8;
    }
  }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  return abStack_19[0];
}

// ---- sub_9083c94  (ROM 0x9083c94)
byte sub_9083c94(int param_1,int param_2,int param_3,undefined4 param_4,char param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uStack_30;
  uint uStack_2c;
  byte abStack_19 [5];
  
  iVar1 = GetBankAbility(param_3);
  iVar2 = GetBankItemEffect(param_3);
  abStack_19[0] = 0;
  if (param_1 == 0xa5) {
    return 0;
  }
  if (param_5 == '\0') {
    iVar3 = GetBankAbility(param_2);
    uStack_30 = (uint)gBattleMons[param_2].type1;
    uStack_2c = (uint)gBattleMons[param_2].type2;
    uVar7 = (uint)gBattleMons[param_2].type3;
    uVar4 = GetMoveTypeSpecial(param_2,param_1);
  }
  else {
    iVar3 = GetMonAbility(param_4);
    uStack_30 = func_0x090c1d94(param_4,0);
    uStack_2c = func_0x090c1d94(param_4,1);
    uVar4 = sub_908367c(param_4,param_1);
    uVar7 = 0x14;
  }
  if (((uVar4 == uStack_30) || (uVar4 == uStack_2c)) || (uVar4 == uVar7)) {
    iVar5 = gBattleMoveDamage << 1;
    if (iVar3 != 0x58) {
      iVar5 = udivsi(gBattleMoveDamage * 0x96,100);
    }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
    gBattleMoveDamage = iVar5;
  }
  if (((((uVar4 == 4) && (iVar5 = CheckGrounding(param_3), iVar5 == 0)) &&
       ((((iVar1 == 0x1a &&
          ((iVar3 != 0x98 && (iVar5 = CheckTableForMove(param_1,&UNK_09040136), iVar5 == 0)))) ||
         (iVar2 == 0x67)) || ((gStatuses3[param_3] & 0x20200000) != 0)))) &&
      ((param_1 != 0x23c &&
       ((iVar3 != 0xe9 || (iVar2 = CheckTableForMove(param_1,&UNK_0903ff2a), iVar2 == 0)))))) ||
     ((iVar2 = CheckTableForMove(param_1,&UNK_0903ffd8), iVar2 != 0 &&
      (iVar2 = IsAffectedByPowder(param_3), iVar2 == 0)))) {
    bVar6 = 9;
  }
  else {
    if ((param_1 != 0x2a3) || (iVar2 = IsOfType(param_3,2 /* Flying */), iVar2 == 0)) {
      func_0x090827ec(iVar3,param_3,param_1,uVar4,abStack_19);
      goto LAB_09083dce;
    }
    bVar6 = 8;
  }
  abStack_19[0] = bVar6 | abStack_19[0];
LAB_09083dce:
  bVar6 = abStack_19[0];
  if ((iVar1 == 0x19) && (iVar3 != 0x98)) {
    uVar4 = (uint)abStack_19[0];
    iVar1 = CheckTableForMove(param_1,&UNK_09040136);
    if ((((iVar1 == 0) &&
         ((-1 < (int)(uVar4 << 0x1f) && (iVar1 = sub_9074f00(param_2,param_1), iVar1 == 2)))) &&
        (((bVar6 & 2) == 0 || ((uVar4 & 6) == 6)))) &&
       ((gBattleMoves[param_1].power != 0 && (gBattleMoves[param_1].split != 2)))) {
      abStack_19[0] = bVar6 | 1;
    }
  }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  return abStack_19[0];
}

// ---- TryAdjustDamageForRaidBoss  (ROM 0x9083eac)
uint TryAdjustDamageForRaidBoss(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = GetBattlerAtPosition(1);
  if (iVar3 == param_1) {
    if ((int)((uint)*(byte *)(gNewBS + 0x1b5) << 0x1d) < 0) {
      if (gBattleMons[iVar3].hp <= param_2) {
        param_2 = gBattleMons[iVar3].hp - 1;
      }
    }
    else {
      iVar1 = IsRaidBattle();
      if (((iVar1 != 0) && (uVar2 = sub_908ef3c(iVar3), uVar2 != 0)) &&
         (gBattleMons[iVar3].hp - param_2 < uVar2)) {
        param_2 = gBattleMons[iVar3].hp - uVar2;
      }
    }
  }
  return param_2;
}

// ---- PopulateDamageCalcStructWithBaseAttackerData  (ROM 0x9083f18)
void PopulateDamageCalcStructWithBaseAttackerData(byte *param_1)

{
  ushort uVar1;
  u8 uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  Pokemon *mon;
  uint uVar7;
  uint uVar8;
  
  uVar8 = (uint)*param_1;
  if (*(int *)(param_1 + 4) != 0) {
    iVar5 = GetBattlerSide(uVar8);
    mon = *(Pokemon **)(param_1 + 4);
    *(ushort *)(param_1 + 0xc) = mon->species;
    if (-1 < (int)((uint)param_1[0x56] << 0x1b)) {
      uVar2 = GetMonAbilityAfterTrace(mon,~(byte)iVar5 & 1);
      param_1[0x10] = uVar2;
      bVar3 = sub_9074de4(mon);
      param_1[0x14] = bVar3;
      *(ushort *)(param_1 + 0x18) = mon->item;
      bVar3 = ItemId_GetHoldEffectParam();
      param_1[0x15] = bVar3;
      if ((param_1[0x10] == 0xc5) && (iVar4 = sub_9074a88(uVar8,1), iVar4 != 0)) {
        param_1[0x54] = 1;
        bVar3 = sub_9074a2c(uVar8);
        param_1[0x52] = bVar3;
        bVar3 = CheckGrounding();
      }
      else {
        bVar3 = sub_90751c8(mon);
      }
      param_1[0x4a] = bVar3;
    }
    param_1[0x12] = 0;
    *(ushort *)(param_1 + 0x1a) = mon->hp;
    uVar1 = mon->maxHP;
    param_1[0x40] = 0;
    param_1[0x41] = 0;
    param_1[0x42] = 0;
    param_1[0x43] = 0;
    *(ushort *)(param_1 + 0x1e) = uVar1;
    if (param_1[0x54] == 0) {
      *(ushort *)(param_1 + 0xc) = mon->species;
      uVar6 = sub_9071268(iVar5,mon);
    }
    else {
      uVar7 = (uint)param_1[0x52];
      bVar3 = GetBankAbility(uVar7);
      param_1[0x10] = bVar3;
      *(ushort *)(param_1 + 0xc) = gBattleMons[uVar7].species;
      uVar6 = SpeedCalc(uVar7);
    }
    uVar7 = mon->condition;
    *(undefined4 *)(param_1 + 0x2c) = uVar6;
    *(uint *)(param_1 + 0x38) = uVar7;
    if (((((uVar7 == 0) && (-1 < (int)((uint)param_1[0x56] << 0x1b))) &&
         (((byte)(&gSideTimers[0].field_0xa)[iVar5 * 0xb] & 0xf) >> 2 != 0)) &&
        ((param_1[0x4a] != 0 && (iVar5 = sub_90c1df8(mon,3), iVar5 == 0)))) &&
       ((iVar5 = func_0x09073b60(mon,param_1[0x14]), iVar5 != 0 &&
        ((iVar5 = sub_907531c(uVar8), iVar5 == 0 && (iVar5 = sub_90c1ed2(mon), iVar5 != 0)))))) {
      param_1[0x38] = 8;
      param_1[0x39] = 0;
      param_1[0x3a] = 0;
      param_1[0x3b] = 0;
    }
    goto LAB_0908403a;
  }
  *(ushort *)(param_1 + 0xc) = gBattleMons[uVar8].species;
  bVar3 = GetBankAbility(uVar8);
  iVar5 = gBattleTypeFlags;
  param_1[0x10] = bVar3;
  if (iVar5 << 0x1f < 0) {
    if (gBattleMons[uVar8 ^ 2].hp == 0) goto LAB_090840d2;
    bVar3 = GetBankAbility();
    param_1[0x12] = bVar3;
  }
  else {
LAB_090840d2:
    param_1[0x12] = 0;
  }
  *(ushort *)(param_1 + 0x18) = gBattleMons[uVar8].item;
  bVar3 = GetBankItemEffect(uVar8);
  param_1[0x14] = bVar3;
  bVar3 = ItemId_GetHoldEffectParam(gBattleMons[uVar8].item);
  param_1[0x15] = bVar3;
  *(ushort *)(param_1 + 0x1a) = gBattleMons[uVar8].hp;
  *(ushort *)(param_1 + 0x1e) = gBattleMons[uVar8].maxHP;
  uVar6 = SpeedCalc(uVar8);
  *(uint *)(param_1 + 0x38) = gBattleMons[uVar8].status1;
  uVar7 = gStatuses3[uVar8];
  *(undefined4 *)(param_1 + 0x2c) = uVar6;
  *(uint *)(param_1 + 0x40) = uVar7;
  bVar3 = CheckGrounding(uVar8);
  param_1[0x4a] = bVar3;
LAB_0908403a:
  param_1[0x57] = 1;
  return;
}

// ---- PopulateDamageCalcStructWithBaseDefenderData  (ROM 0x90840ec)
undefined8 PopulateDamageCalcStructWithBaseDefenderData(int param_1)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined8 uVar9;
  
  uVar8 = (uint)*(byte *)(param_1 + 1);
  iVar7 = *(int *)(param_1 + 8);
  if (iVar7 == 0) {
    *(ushort *)(param_1 + 0xe) = gBattleMons[uVar8].species;
    uVar2 = GetBankAbility(uVar8);
    iVar7 = gBattleTypeFlags;
    *(undefined1 *)(param_1 + 0x11) = uVar2;
    if (iVar7 << 0x1f < 0) {
      if (gBattleMons[uVar8 ^ 2].hp == 0) goto LAB_0908422e;
      uVar2 = GetBankAbility();
      *(undefined1 *)(param_1 + 0x13) = uVar2;
    }
    else {
LAB_0908422e:
      *(undefined1 *)(param_1 + 0x13) = 0;
    }
    uVar2 = GetBankItemEffect(uVar8);
    *(undefined1 *)(param_1 + 0x16) = uVar2;
    uVar2 = ItemId_GetHoldEffectParam(gBattleMons[uVar8].item);
    *(undefined1 *)(param_1 + 0x17) = uVar2;
    *(ushort *)(param_1 + 0x1c) = gBattleMons[uVar8].hp;
    *(ushort *)(param_1 + 0x20) = gBattleMons[uVar8].maxHP;
    uVar9 = SpeedCalc(uVar8);
    *(uint *)(param_1 + 0x3c) = gBattleMons[uVar8].status1;
    uVar6 = gStatuses3[uVar8];
    *(int *)(param_1 + 0x30) = (int)uVar9;
    *(uint *)(param_1 + 0x44) = uVar6;
    iVar7 = sub_2023dfc(uVar8,(int)((ulonglong)uVar9 >> 0x20),uVar8 * 4,&GetBattlerSide);
    *(ushort *)(param_1 + 0x48) = gSideStatuses[iVar7];
    uVar2 = CheckGrounding(uVar8);
    *(undefined1 *)(param_1 + 0x4b) = uVar2;
    *(sbyte *)(param_1 + 0x36) = gBattleMons[uVar8].statStages[1];
    *(sbyte *)(param_1 + 0x37) = gBattleMons[uVar8].statStages[4];
    iVar7 = sub_9075096();
    uVar6 = (uint)gBattleMons[uVar8].spDefense;
    uVar1 = gBattleMons[uVar8].defense;
    if (iVar7 != 0) {
      *(uint *)(param_1 + 0x24) = uVar6;
      *(uint *)(param_1 + 0x28) = (uint)uVar1;
      goto LAB_09084226;
    }
    *(uint *)(param_1 + 0x24) = (uint)uVar1;
  }
  else {
    *(undefined2 *)(param_1 + 0xe) = *(undefined2 *)(iVar7 + 0x20);
    uVar2 = GetMonAbility(iVar7);
    *(undefined1 *)(param_1 + 0x11) = uVar2;
    *(undefined1 *)(param_1 + 0x13) = 0;
    uVar2 = sub_9074de4(iVar7);
    *(undefined1 *)(param_1 + 0x16) = uVar2;
    uVar2 = ItemId_GetHoldEffectParam(*(undefined2 *)(iVar7 + 0x22));
    *(undefined1 *)(param_1 + 0x17) = uVar2;
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(iVar7 + 0x56);
    *(undefined2 *)(param_1 + 0x20) = *(undefined2 *)(iVar7 + 0x58);
    uVar3 = GetBattlerSide(uVar8);
    uVar3 = sub_9071268(uVar3,iVar7);
    uVar5 = *(undefined4 *)(iVar7 + 0x50);
    *(undefined4 *)(param_1 + 0x30) = uVar3;
    *(undefined4 *)(param_1 + 0x3c) = uVar5;
    *(undefined4 *)(param_1 + 0x44) = 0;
    iVar4 = sub_2023dde(uVar8);
    *(ushort *)(param_1 + 0x48) = gSideStatuses[iVar4];
    uVar2 = func_0x09075230(iVar7);
    *(undefined1 *)(param_1 + 0x4b) = uVar2;
    *(undefined2 *)(param_1 + 0x36) = 0;
    iVar4 = sub_9075096();
    if (iVar4 == 0) {
      *(uint *)(param_1 + 0x24) = (uint)*(ushort *)(iVar7 + 0x5c);
      uVar6 = (uint)*(ushort *)(iVar7 + 0x62);
    }
    else {
      *(uint *)(param_1 + 0x24) = (uint)*(ushort *)(iVar7 + 0x62);
      uVar6 = (uint)*(ushort *)(iVar7 + 0x5c);
    }
  }
  *(uint *)(param_1 + 0x28) = uVar6;
LAB_09084226:
  *(undefined1 *)(param_1 + 0x58) = 1;
  return 0x2023dde080751c5;
}

// ---- sub_9084288  (ROM 0x9084288)
undefined8 sub_9084288(undefined4 param_1,int param_2,int param_3,int param_4,char param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = func_0x0908424c(param_1,1);
  if (uVar1 == 0) {
    uVar2 = SpeciesToNationalPokedexNum(param_1);
    uVar1 = GetPokedexHeightWeight(uVar2,1);
  }
  if (param_2 == 0xc2) {
    uVar1 = uVar1 << 1;
  }
  if (param_3 == 0x6b) {
    uVar1 = uVar1 >> 1;
  }
  if (param_5 != '\0') {
    for (iVar3 = 0; iVar3 < (int)(uint)*(byte *)(gNewBS + param_4 + 0x51); iVar3 = iVar3 + 1) {
      if (uVar1 < 0x899) {
        uVar1 = 1;
        break;
      }
      uVar1 = uVar1 - 0x898;
    }
  }
  return CONCAT44(param_1,uVar1);
}

// ---- CountAliveMonsInBattle  (ROM 0x9085196)
undefined8 CountAliveMonsInBattle(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iStack_20;
  
  iStack_20 = param_3;
  if (param_1 == 1) {
    uVar3 = 0;
    for (uVar4 = 0; (int)uVar4 < (int)(uint)gBattlersCount; uVar4 = uVar4 + 1) {
      iStack_20 = GetBattlerSide(uVar4 & 0xff);
      iVar1 = GetBattlerSide(param_2);
      if (((iStack_20 == iVar1) &&
          ((*(uint *)((uVar4 + 0x2097917) * 4) & (uint)gAbsentBattlerFlags) == 0)) &&
         (gBattleMons[uVar4].hp != 0)) {
        uVar3 = uVar3 + 1 & 0xff;
      }
    }
  }
  else if (param_1 == 0) {
    uVar3 = 0;
    for (iVar1 = 0; iVar1 < (int)(uint)gBattlersCount; iVar1 = iVar1 + 1) {
      if (((param_2 != iVar1) &&
          ((*(uint *)((iVar1 + 0x2097917) * 4) & (uint)gAbsentBattlerFlags) == 0)) &&
         (gBattleMons[iVar1].hp != 0)) {
        uVar3 = uVar3 + 1 & 0xff;
      }
    }
  }
  else if (param_1 == 2) {
    uVar3 = 0;
    for (uVar4 = 0; (int)uVar4 < (int)(uint)gBattlersCount; uVar4 = uVar4 + 1) {
      iVar2 = GetBattlerSide(uVar4 & 0xff);
      iVar1 = GetBattlerSide(param_3);
      if (((iVar2 == iVar1) &&
          ((*(uint *)((uVar4 + 0x2097917) * 4) & (uint)gAbsentBattlerFlags) == 0)) &&
         (gBattleMons[uVar4].hp != 0)) {
        uVar3 = uVar3 + 1 & 0xff;
      }
    }
  }
  else {
    uVar3 = 0;
  }
  return CONCAT44(iStack_20,uVar3);
}

// ---- CalcVisualBasePower  (ROM 0x90858f8)
uint CalcVisualBasePower(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined1 uStack_80;
  undefined1 uStack_74;
  undefined1 uStack_73;
  undefined1 auStack_72 [18];
  char cStack_60;
  undefined2 uStack_28;
  undefined1 uStack_26;
  undefined1 uStack_25;
  undefined1 uStack_24;
  byte bStack_23;
  byte bStack_1e;
  
  Memset(auStack_72,0,0x5a);
  uStack_80 = (undefined1)param_2;
  uStack_73 = uStack_80;
  uStack_28 = (undefined2)param_3;
  bStack_1e = 4;
  uStack_74 = (undefined1)param_1;
  PopulateDamageCalcStructWithBaseAttackerData(&uStack_74);
  uStack_25 = CalcMoveSplit(param_1,param_3);
  uStack_26 = GetMoveTypeSpecial(param_1,param_3);
  if (param_4 == 0) {
    PopulateDamageCalcStructWithBaseDefenderData(&uStack_74);
  }
  else {
    bStack_1e = bStack_1e | 1;
  }
  uStack_24 = sub_9083c94(param_3,param_1,param_2,0,0);
  bStack_23 = gBattleMoves[param_3].power;
  uVar1 = func_0x090842fc(&uStack_74);
  uVar2 = func_0x09085304(&uStack_74,uVar1);
  if (param_3 != 0x2a6) {
    if (param_3 < 0x2a7) {
      if ((param_3 != 0x4c) && (param_3 != 0x263)) {
        return uVar2;
      }
      iVar3 = AbilityBattleEffects(0x13,0,0xd,0,0);
      if (iVar3 != 0) {
        return uVar2;
      }
      if (cStack_60 == -0x78) {
        return uVar2;
      }
      if ((gBattleWeather & 0x379f) == 0) {
        return uVar2;
      }
      uVar2 = (uVar2 >> 1) << 0x10;
      goto LAB_090859f4;
    }
    if (1 < param_3 - 0x2b9) {
      return uVar2;
    }
  }
  iVar3 = IsDynamaxed(param_2);
  if (iVar3 == 0) {
    return uVar2;
  }
  uVar2 = uVar2 << 0x11;
LAB_090859f4:
                    /* WARNING: Read-only address (ram,0x02023f1c) is written */
  return uVar2 >> 0x10;
}

// ---- sub_9086b40  (ROM 0x9086b40)
uint sub_9086b40(int param_1,undefined4 param_2,int param_3,int param_4,undefined1 *param_5)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int extraout_r1;
  undefined4 uVar5;
  int iVar6;
  ushort *puVar7;
  undefined1 uStack_84;
  undefined1 auStack_74 [96];
  
  uVar3 = AI_TypeCalc(param_3,param_1,param_2);
  bVar1 = gBattleMoves[param_3].effect;
  if (bVar1 == 0x5b) {
    uVar3 = MathMax(1,(int)((uint)gBattleMons[param_1].hp + (uint)*(ushort *)(param_4 + 0x56)) >> 1)
    ;
    uVar2 = *(ushort *)(param_4 + 0x56);
    uVar3 = uVar3 & 0xffff;
LAB_09086cc6:
    if (uVar3 < uVar2) {
      return uVar2 - uVar3;
    }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
    return 0;
  }
  if (gBattleMoves[param_3].split == 2) {
    return 0;
  }
  if ((uVar3 & 0x29) != 0) {
    return 0;
  }
  if (bVar1 == 0x58) {
    uVar3 = func_0x090a1600(0x32);
    return uVar3;
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  }
  if (bVar1 < 0x59) {
    if (bVar1 == 0x29) {
      return 0x28;
    }
    if (bVar1 == 0x57) {
      return (uint)gBattleMons[param_1].level;
    }
    if (bVar1 == 0x28) {
      return (uint)(*(ushort *)(param_4 + 0x56) >> 1);
    }
  }
  else {
    if (bVar1 == 0xa8) {
      return (uint)gBattleMons[param_1].hp;
    }
    if (bVar1 == 0xbd) {
      uVar2 = *(ushort *)(param_4 + 0x56);
      uVar3 = (uint)gBattleMons[param_1].hp;
      goto LAB_09086cc6;
    }
    if (bVar1 == 0x82) {
      return 0x14;
    }
  }
  Memset(auStack_74,0,0x5c);
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  UNK_02023fd2 = 1;
  iVar4 = func_0x09081c74(param_1,param_2,param_3,0,param_4);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = (byte)iVar4;
  if (iVar4 == 0) {
LAB_09086cf4:
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 10;
  }
  else {
    uVar5 = Random2(iVar4);
    sub_900042e(uVar5,UNK_02023d71);
    if (extraout_r1 != 0) goto LAB_09086cf4;
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 0xf;
  }
  if (param_5 == (undefined1 *)0x0) {
    param_5 = auStack_74;
  }
  uStack_84 = (undefined1)param_1;
  *param_5 = uStack_84;
  param_5[1] = (char)param_2;
  *(short *)(param_5 + 0x4c) = (short)param_3;
  *(int *)(param_5 + 8) = param_4;
  param_5[0x56] = param_5[0x56] | 8;
  gBattleMoveDamage = func_0x09085a10(param_5);
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  AI_TypeCalc(param_3,param_1,param_2,param_4);
  iVar4 = sub_900042a((uint)UNK_02023d71 * gBattleMoveDamage,10);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = 10;
  uVar3 = __udivsi3(iVar4 * 0x60,100);
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if (iVar4 != 0) {
    iVar4 = GetBankAbility(param_1);
    iVar6 = 5;
    if (iVar4 == 0x4f) goto LAB_09086c88;
  }
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if ((iVar4 == 0) && (bVar1 = gBattleMoves[param_3].effect, bVar1 != 0x68)) {
    iVar4 = CheckTableForMove(param_3,&UNK_090401ce);
    if (iVar4 != 0) {
      return uVar3 << 1;
    }
    iVar4 = GetBankAbility(param_1);
    if ((iVar4 == 0x97) && (iVar4 = func_0x09074730(param_3,param_1), iVar4 != 0)) {
      uVar5 = 100;
      iVar4 = uVar3 * 0x7d;
    }
    else {
      iVar4 = GetBankAbility(param_1);
      if ((iVar4 != 0xa7) || (iVar4 = CheckTableForMove(param_3,&UNK_0903fe9a), iVar4 == 0)) {
        puVar7 = (ushort *)(param_4 + 0x56);
        if ((bVar1 != 0x65) &&
           ((((*(ushort *)(param_4 + 0x58) != *puVar7 ||
              (iVar4 = GetMonAbility(param_4), iVar4 != 5)) ||
             (iVar4 = GetBankAbility(param_1), iVar4 == 0x98)) ||
            (iVar4 = CheckTableForMove(param_3,&UNK_09040136), iVar4 != 0)))) {
          if (*puVar7 != *(ushort *)(param_4 + 0x58)) {
            return uVar3;
          }
          iVar4 = func_0x09074fae(param_2);
          if (iVar4 == 0) {
            return uVar3;
          }
        }
        uVar3 = MathMin(uVar3,*puVar7 - 1);
        return uVar3;
      }
      uVar5 = 10;
      iVar4 = uVar3 * 0xf;
    }
    uVar3 = __udivsi3(iVar4,uVar5);
    return uVar3;
  }
  iVar6 = 3;
LAB_09086c88:
  return iVar6 * uVar3;
}

// ---- sub_9086dd8  (ROM 0x9086dd8)
uint sub_9086dd8(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 *param_5)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int extraout_r1;
  undefined4 uVar5;
  int iVar6;
  undefined1 uStack_80;
  undefined1 auStack_74 [96];
  
  uVar3 = sub_9083c94(param_3,param_1,param_2,param_4,1);
  bVar1 = gBattleMoves[param_3].effect;
  if (bVar1 == 0x5b) {
    uVar3 = MathMax(1,(int)((uint)*(ushort *)(param_4 + 0x56) + (uint)gBattleMons[param_2].hp) >> 1)
    ;
    uVar2 = gBattleMons[param_2].hp;
    uVar3 = uVar3 & 0xffff;
LAB_09086f5e:
    if (uVar3 < uVar2) {
      return uVar2 - uVar3;
    }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
    return 0;
  }
  if (gBattleMoves[param_3].split == 2) {
    return 0;
  }
  if ((uVar3 & 0x29) != 0) {
    return 0;
  }
  if (bVar1 == 0x58) {
    uVar3 = func_0x090a1600(0x32);
    return uVar3;
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  }
  if (bVar1 < 0x59) {
    if (bVar1 == 0x29) {
      return 0x28;
    }
    if (bVar1 == 0x57) {
      return (uint)*(byte *)(param_4 + 0x54);
    }
    if (bVar1 == 0x28) {
      uVar3 = sub_90739b4(param_2);
      return uVar3 >> 1 & 0xffff;
    }
  }
  else {
    if (bVar1 == 0xa8) {
      return (uint)*(ushort *)(param_4 + 0x56);
    }
    if (bVar1 == 0xbd) {
      uVar2 = gBattleMons[param_2].hp;
      uVar3 = (uint)*(ushort *)(param_4 + 0x56);
      goto LAB_09086f5e;
    }
    if (bVar1 == 0x82) {
      return 0x14;
    }
  }
  Memset(auStack_74,0,0x5c);
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  UNK_02023fd2 = 1;
  iVar4 = func_0x09081c74(param_1,param_2,param_3,param_4,0);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = (byte)iVar4;
  if (iVar4 == 0) {
LAB_09086f8c:
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 10;
  }
  else {
    uVar5 = Random2(iVar4);
    sub_900042e(uVar5,UNK_02023d71);
    if (extraout_r1 != 0) goto LAB_09086f8c;
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 0xf;
  }
  if (param_5 == (undefined1 *)0x0) {
    param_5 = auStack_74;
  }
  uStack_80 = (undefined1)param_1;
  *param_5 = uStack_80;
  param_5[1] = (char)param_2;
  *(short *)(param_5 + 0x4c) = (short)param_3;
  *(int *)(param_5 + 4) = param_4;
  param_5[0x56] = param_5[0x56] | 8;
  gBattleMoveDamage = func_0x09085a10(param_5);
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  sub_9083c94(param_3,param_1,param_2,param_4,1);
  iVar4 = sub_900042a((uint)UNK_02023d71 * gBattleMoveDamage,10);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = 10;
  uVar3 = __udivsi3(iVar4 * 0x60,100);
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if (iVar4 != 0) {
    iVar4 = GetMonAbility(param_4);
    iVar6 = 5;
    if (iVar4 == 0x4f) goto LAB_09086f2e;
  }
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if ((iVar4 == 0) && (bVar1 = gBattleMoves[param_3].effect, bVar1 != 0x68)) {
    iVar4 = CheckTableForMove(param_3,&UNK_090401ce);
    if (iVar4 != 0) {
      return uVar3 << 1;
    }
    iVar4 = GetMonAbility(param_4);
    if ((iVar4 == 0x97) && (iVar4 = func_0x09074730(param_3,param_1), iVar4 != 0)) {
      uVar5 = 100;
      iVar4 = uVar3 * 0x7d;
    }
    else {
      iVar4 = GetMonAbility(param_4);
      if ((iVar4 != 0xa7) || (iVar4 = CheckTableForMove(param_3,&UNK_0903fe9a), iVar4 == 0)) {
        if ((bVar1 != 0x65) &&
           ((((gBattleMons[param_2].maxHP != gBattleMons[param_2].hp ||
              (iVar4 = GetBankAbility(param_2), iVar4 != 5)) ||
             (iVar4 = GetMonAbility(param_4), iVar4 == 0x98)) ||
            (iVar4 = CheckTableForMove(param_3,&UNK_09040136), iVar4 != 0)))) {
          if (gBattleMons[param_2].hp != gBattleMons[param_2].maxHP) {
            return uVar3;
          }
          iVar4 = func_0x09074fae(param_2);
          if (iVar4 == 0) {
            return uVar3;
          }
        }
        uVar3 = MathMin(uVar3,gBattleMons[param_2].hp - 1);
        return uVar3;
      }
      uVar5 = 10;
      iVar4 = uVar3 * 0xf;
    }
    uVar3 = __udivsi3(iVar4,uVar5);
    return uVar3;
  }
  iVar6 = 3;
LAB_09086f2e:
  return iVar6 * uVar3;
}

// ---- AI_CalcDmg  (ROM 0x9087080)
/* WARNING: Restarted to delay deadcode elimination for space: ram */

uint AI_CalcDmg(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int extraout_r1;
  uint uVar6;
  undefined1 *puStack_80;
  undefined1 auStack_74 [96];
  
  uVar2 = AI_SpecialTypeCalc(param_3,param_1,param_2);
  bVar1 = gBattleMoves[param_3].effect;
  if (bVar1 == 0x5b) {
    iVar4 = sub_90739b4(param_1);
    iVar5 = sub_90739b4(param_2);
    uVar2 = sub_90739b4(param_2);
    uVar6 = iVar4 + iVar5 >> 1;
    if ((uVar6 & 0xffff) < uVar2) {
      iVar4 = sub_90739b4(param_2);
      return iVar4 - uVar6;
    }
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
    return 0;
  }
  if (gBattleMoves[param_3].split == 2) {
    return 0;
  }
  if ((uVar2 & 0x29) != 0) {
    return 0;
  }
  if (bVar1 == 0x58) {
    uVar2 = func_0x090a1600(0x32);
    return uVar2;
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  }
  if (bVar1 < 0x59) {
    if (bVar1 == 0x29) {
      return 0x28;
    }
    if (bVar1 == 0x57) {
      return (uint)gBattleMons[param_1].level;
    }
    if (bVar1 == 0x28) {
      uVar2 = sub_90739b4(param_2);
      return uVar2 >> 1 & 0xffff;
    }
  }
  else {
    if (bVar1 == 0xa8) {
      return (uint)gBattleMons[param_1].hp;
    }
    if (bVar1 == 0xbd) {
      iVar4 = sub_90739b4(param_2);
      iVar5 = sub_90739b4(param_1);
      if (iVar4 - iVar5 < 1) {
        return 0;
      }
      return iVar4 - iVar5;
    }
    if (bVar1 == 0x82) {
      return 0x14;
    }
  }
  Memset(auStack_74,0,0x5c);
                    /* WARNING: Read-only address (ram,0x02023fd2) is written */
  UNK_02023fd2 = 1;
  iVar4 = func_0x09081c74(param_1,param_2,param_3,0,0);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = (byte)iVar4;
  if (iVar4 == 0) {
LAB_0908722c:
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 10;
  }
  else {
    uVar3 = Random2(iVar4);
    sub_900042e(uVar3,UNK_02023d71);
    if (extraout_r1 != 0) goto LAB_0908722c;
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
    UNK_02023d71 = 0xf;
  }
  puStack_80 = param_4;
  if (param_4 == (undefined1 *)0x0) {
    puStack_80 = auStack_74;
  }
  *puStack_80 = (char)param_1;
  puStack_80[1] = (char)param_2;
  *(short *)(puStack_80 + 0x4c) = (short)param_3;
  puStack_80[0x56] = puStack_80[0x56] | 8;
  uVar3 = func_0x09085a10(puStack_80);
  gBattleMoveDamage = MathMin(0x7fffffff,uVar3);
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  AI_SpecialTypeCalc(param_3,param_1,param_2);
  iVar4 = sub_900042a((uint)UNK_02023d71 * gBattleMoveDamage,10);
                    /* WARNING: Read-only address (ram,0x02023d71) is written */
  UNK_02023d71 = 10;
  uVar2 = __udivsi3(iVar4 * 0x5d,100);
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if (iVar4 != 0) {
    iVar4 = GetBankAbility(param_1);
    iVar5 = 5;
    if (iVar4 == 0x4f) goto LAB_09087252;
  }
  iVar4 = CheckTableForMove(param_3,&UNK_090401a8);
  if ((iVar4 != 0) || (iVar4 = CheckTableForMove(param_3,&UNK_090401ce), iVar4 != 0)) {
    return uVar2 << 1;
  }
  bVar1 = gBattleMoves[param_3].effect;
  if (bVar1 != 0x68) {
    iVar4 = GetBankAbility(param_1);
    if ((iVar4 == 0x97) && (iVar4 = func_0x09074730(param_3,param_1), iVar4 != 0)) {
      uVar3 = 100;
      iVar4 = uVar2 * 0x7d;
    }
    else {
      iVar4 = GetBankAbility(param_1);
      if ((iVar4 != 0xa7) || (iVar4 = CheckTableForMove(param_3,&UNK_0903fe9a), iVar4 == 0)) {
        if ((bVar1 != 0x65) &&
           ((((gBattleMons[param_2].maxHP != gBattleMons[param_2].hp ||
              (iVar4 = GetBankAbility(param_2), iVar4 != 5)) ||
             (iVar4 = GetBankAbility(param_1), iVar4 == 0x98)) ||
            (iVar4 = CheckTableForMove(param_3,&UNK_09040136), iVar4 != 0)))) {
          if (gBattleMons[param_2].hp != gBattleMons[param_2].maxHP) {
            return uVar2;
          }
          iVar4 = func_0x09074fae(param_2);
          if (iVar4 == 0) {
            return uVar2;
          }
        }
        uVar2 = MathMin(uVar2,gBattleMons[param_2].hp - 1);
        return uVar2;
      }
      uVar3 = 10;
      iVar4 = uVar2 * 0xf;
    }
    uVar2 = __udivsi3(iVar4,uVar3);
    return uVar2;
  }
  iVar5 = 6;
LAB_09087252:
  return iVar5 * uVar2;
}

// ---- CanDynamax  (ROM 0x908d4ec)
bool CanDynamax(int param_1)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  if ((gBattleTypeFlags << 1 < 0) && (*(char *)(gNewBS + param_1 + 0x1a2) == '\0')) {
    iVar1 = func_0x0908d4ac();
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- IsDynamaxed  (ROM 0x908d7bc)
bool IsDynamaxed(int param_1)

{
  return *(char *)(gNewBS + param_1 + 0x1a6) != '\0';
}

// ---- sub_908d864  (ROM 0x908d864)
undefined8 sub_908d864(BattleMove *param_1,uint param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  BattleMove *pBStack_20;
  
  uVar2 = GetMonData(param_1,0xb,0);
  uVar1 = GetMonData(param_1,0xc,0);
  iVar3 = func_0x0908d454(uVar2);
  pBStack_20 = param_1;
  if ((iVar3 == 0) && (iVar3 = func_0x0908d2e4(uVar1), iVar3 == 0)) {
    iVar3 = 0xd;
    do {
      uVar4 = GetMonData(param_1,iVar3,0);
      if ((uVar4 & 0xffff) == 0) break;
      pBStack_20 = gBattleMoves;
      if (((gBattleMoves[uVar4 & 0xffff].split != 2) &&
          (iVar6 = func_0x0908d73c(param_1), iVar6 != 0)) &&
         (gBattleMoves[iVar6].z_move_effect == param_2)) {
        uVar5 = 1;
        goto LAB_0908d8c6;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x11);
  }
  uVar5 = 0;
LAB_0908d8c6:
  return CONCAT44(pBStack_20,uVar5);
}

// ---- sub_908d8f0  (ROM 0x908d8f0)
bool sub_908d8f0(undefined4 param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  
  if (gBattleTypeFlags << 1 < 0) {
    uVar2 = GetMonData(param_1,0xb,0);
    uVar1 = GetMonData(param_1,0xc,0);
    iVar3 = func_0x0908d454(uVar2);
    if (iVar3 == 0) {
      iVar3 = func_0x0908d2e4(uVar1);
      return iVar3 == 0;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
  return false;
}

// ---- MoveInMonMovesetThatCanChangeByGigantamaxing  (ROM 0x908d93c)
undefined4 MoveInMonMovesetThatCanChangeByGigantamaxing(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  
  if ((int)((uint)*(byte *)(param_1 + 0x47) << 0x1c) < 0) {
    iVar3 = 0xd;
    do {
      uVar2 = GetMonData(param_1,iVar3,0);
      sVar1 = func_0x0908d73c(param_1,uVar2);
      if ((ushort)(sVar1 - 0x3aaU) < 0x42) {
        return 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x11);
  }
  return 0;
}

// ---- IsAnyMaxMove  (ROM 0x908da20)
bool IsAnyMaxMove(short param_1)

{
  return (ushort)(param_1 - 0x385U) < 0x67;
}

// ---- sub_908dd0c  (ROM 0x908dd0c)
bool sub_908dd0c(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 - 0x385U < 0x67) {
    bVar1 = (byte)(gBattleMoves[param_1].z_move_effect - 0xb) < 4;
  }
  return bVar1;
}

// ---- sub_908dd40  (ROM 0x908dd40)
bool sub_908dd40(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 - 0x385U < 0x67) {
    bVar1 = (byte)(gBattleMoves[param_1].z_move_effect - 0xf) < 4;
  }
  return bVar1;
}

// ---- IsMaxMoveWithStatusEffect  (ROM 0x908dd74)
bool IsMaxMoveWithStatusEffect(int param_1)

{
  uint uVar1;
  bool bVar2;
  
  bVar2 = false;
  if ((param_1 - 0x385U < 0x67) &&
     (uVar1 = gBattleMoves[param_1].z_move_effect - 0x16 & 0xff, uVar1 < 0xc)) {
    bVar2 = (1 << uVar1 & 0x903U) != 0;
  }
  return bVar2;
}

// ---- sub_908ddb4  (ROM 0x908ddb4)
undefined4 sub_908ddb4(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((param_1 - 0x385U < 0x67) &&
     ((gBattleMoves[param_1].z_move_effect == 0x18 || (gBattleMoves[param_1].z_move_effect == 0x2a))
     )) {
    uVar1 = 1;
  }
  return uVar1;
}

// ---- IsMaxMoveWithEffect  (ROM 0x908de14)
bool IsMaxMoveWithEffect(int param_1,uint param_2)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 - 0x385U < 0x67) {
    bVar1 = gBattleMoves[param_1].z_move_effect == param_2;
  }
  return bVar1;
}

// ---- IsRaidBattle  (ROM 0x908e0a8)
uint IsRaidBattle(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FlagGet(0x919);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = ~(gBattleTypeFlags >> 3) & 1;
  }
  return uVar2;
}

// ---- GetMaxMoveByMove  (ROM 0x908eca8)
undefined8 GetMaxMoveByMove(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = CalcMoveSplit();
  if (param_2 == 0) {
LAB_0908ecb8:
    uVar3 = 0;
  }
  else {
    iVar4 = IsRaidBattle();
    if ((iVar4 == 0) || (iVar4 = GetBattlerAtPosition(1), iVar4 != param_1)) {
      iVar4 = func_0x0908d454(gBattleMons[param_1].species);
      if ((iVar4 != 0) ||
         ((iVar4 = func_0x0908d2e4(gBattleMons[param_1].item), iVar4 != 0 ||
          (iVar4 = func_0x090bd7c8(param_1), iVar4 != 0)))) goto LAB_0908ecb8;
    }
    if (iVar2 == 2) {
      uVar3 = 0x385;
    }
    else {
      uVar5 = func_0x09083610(param_2,param_1,0);
      if (uVar5 == 0xff) {
        uVar5 = func_0x0908d404(param_2,param_1,0);
      }
      uVar1 = gBattleMons[param_1].species;
      iVar4 = GetBankPartyData(param_1);
      if ((((int)((uint)*(byte *)(iVar4 + 0x47) << 0x1c) < 0) &&
          (iVar4 = func_0x0908d710(uVar1), iVar4 != 0)) && (uVar1 != 0)) {
        iVar4 = 0;
        do {
          iVar6 = iVar4 * 6;
          if ((*(ushort *)(iVar6 + 0x91475ac) == uVar1) && (*(byte *)(iVar6 + 0x91475ae) == uVar5))
          {
            uVar3 = (uint)*(ushort *)(iVar6 + 0x91475b0) + iVar2 & 0xffff;
            if (uVar3 != 0) goto LAB_0908ecba;
            break;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 != 0x12);
      }
      uVar3 = func_0x0908d28c(uVar5,iVar2);
    }
  }
LAB_0908ecba:
  return CONCAT44(param_1,uVar3);
}

// ---- GetMaxMove  (ROM 0x908ed8c)
void GetMaxMove(int param_1,int param_2)

{
  GetMaxMoveByMove(param_1,gBattleMons[param_1].moves[param_2]);
  return;
}

// ---- sub_908edd0  (ROM 0x908edd0)
bool sub_908edd0(void)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = IsRaidBattle();
  if ((iVar1 == 0) || (iVar1 = FlagGet(0x902), iVar1 != 0)) {
    bVar2 = false;
  }
  else {
    iVar1 = FlagGet(0x904);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}

// ---- sub_908ee64  (ROM 0x908ee64)
byte sub_908ee64(undefined4 param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = GetBattlerPosition(param_1);
  bVar2 = 0;
  if (iVar1 == 1) {
    bVar2 = *(byte *)(gNewBS + 0x1b5) >> 2 & 1;
  }
  return bVar2;
}

// ---- sub_908ef3c  (ROM 0x908ef3c)
ushort sub_908ef3c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  byte bVar7;
  byte bVar8;
  ushort uVar9;
  
  iVar4 = sub_908ee64();
  if ((iVar4 == 0) && (uVar1 = gBattleMons[param_1].hp, uVar1 != 0)) {
    bVar8 = gBattleMons[param_1].level;
    if (bVar8 < 0x29) {
      bVar8 = (0x13 < bVar8) + 1;
    }
    else {
      bVar8 = (0x46 < bVar8) + 3;
    }
    uVar2 = gBattleMons[param_1].maxHP;
    uVar3 = sub_900042a(uVar2,bVar8,gBattleMons + param_1,0x58,param_4);
    bVar7 = 1;
    uVar6 = uVar3;
    uVar5 = 0;
    while( true ) {
      uVar9 = uVar6;
      if (bVar8 == bVar7) {
        uVar9 = uVar2;
      }
      if ((uVar5 < uVar1) && (uVar1 <= uVar9)) {
        return uVar5;
      }
      bVar7 = bVar7 + 1;
      uVar6 = uVar3 + uVar6;
      if (bVar8 < bVar7) break;
      uVar5 = uVar9;
    }
  }
  return 0;
}

// ---- IsRaidBossUsingRegularMove  (ROM 0x908f1b0)
bool IsRaidBossUsingRegularMove(int param_1,int param_2)

{
  uint extraout_r1;
  bool bVar1;
  
  bVar1 = true;
  if ((gBattleMoves[param_2].split != 2) && (param_2 != 0xa5)) {
    if (UNK_0203e04e < 4) {
      if ((gRandomTurnNumber & 3) == 0) {
        return true;
      }
    }
    else {
      __umodsi3(gRandomTurnNumber,100);
      if (0x59 < (extraout_r1 & 0xffff)) {
        return true;
      }
    }
    bVar1 = (gBattleMons[param_1].status2 & 0x401000) != 0;
  }
                    /* WARNING: Read-only address (ram,0x02023e80) is written */
                    /* WARNING: Read-only address (ram,0x0203e04e) is written */
  return bVar1;
}

// ---- GetBadDreamsDamage  (ROM 0x9090d00)
undefined4 GetBadDreamsDamage(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  if (((int)(gStatuses3[param_1] << 0x1d) < 0) && (iVar2 = GetBankAbility(), iVar2 != 0x73)) {
    uVar3 = GetBaseMaxHP(param_1);
    uVar1 = MathMax(1,uVar3 >> 3 & 0xffff);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ---- GetPoisonDamage  (ROM 0x9090d34)
int GetPoisonDamage(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = GetBankAbility();
  if (iVar1 == 0x73) {
    return 0;
  }
  if (iVar1 != 0x68) {
    if (iVar1 == 0x92) {
      return 0;
    }
    if ((gBattleMons[param_1].status1 & 8) == 0) {
      if ((int)(gBattleMons[param_1].status1 << 0x18) < 0) {
        uVar2 = GetBaseMaxHP(param_1);
        iVar1 = MathMax(1,uVar2 >> 4 & 0xffff);
        return ((gBattleMons[gActiveBattler].status1 & 0xfff) >> 8) * iVar1;
      }
      return 0;
    }
  }
  uVar2 = GetBaseMaxHP(param_1);
  iVar1 = MathMax(1,uVar2 >> 3 & 0xffff);
                    /* WARNING: Read-only address (ram,0x02023bc4) is written */
  return iVar1;
}

// ---- sub_9090dac  (ROM 0x9090dac)
undefined4 sub_9090dac(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = GetBankAbility();
  uVar2 = 0;
  if (((int)(gBattleMons[param_1].status1 << 0x1b) < 0) && ((iVar1 - 0x73U & 0xdf) != 0)) {
    if (iVar1 == 0x61) {
      uVar3 = GetBaseMaxHP(param_1);
      uVar3 = uVar3 >> 5;
    }
    else {
      uVar3 = GetBaseMaxHP(param_1);
      uVar3 = uVar3 >> 4;
    }
    uVar2 = MathMax(1,uVar3 & 0xffff);
  }
  return uVar2;
}

// ---- sub_9090df8  (ROM 0x9090df8)
undefined2 sub_9090df8(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = GetBankAbility();
  uVar1 = 0;
  if ((iVar2 != 0x73) &&
     ((*(uint *)(&gBitTable + param_1 * 4) & (uint)*(byte *)(gNewBS + 199)) != 0)) {
    uVar3 = GetBaseMaxHP(param_1);
    uVar1 = MathMax(1,uVar3 >> 3 & 0xffff);
    iVar2 = IsOfType(param_1,0xb /* Water */);
    if ((iVar2 != 0) || (iVar2 = IsOfType(param_1,8 /* Steel */), iVar2 != 0)) {
      uVar3 = GetBaseMaxHP(param_1);
      uVar1 = MathMax(1,uVar3 >> 2 & 0xffff);
    }
  }
  return uVar1;
}

// ---- sub_9090e6c  (ROM 0x9090e6c)
undefined4 sub_9090e6c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = GetBankAbility();
  uVar2 = 0;
  if (((int)(gBattleMons[param_1].status1 << 0x1a) < 0) && (iVar1 != 0x73)) {
    if (iVar1 == 0x2f) {
      uVar3 = GetBaseMaxHP(param_1);
      uVar3 = uVar3 >> 5;
    }
    else {
      uVar3 = GetBaseMaxHP(param_1);
      uVar3 = uVar3 >> 4;
    }
    uVar2 = MathMax(1,uVar3 & 0xffff);
  }
  return uVar2;
}

// ---- GetSeaOfFireDamage  (ROM 0x9090f80)
undefined4 GetSeaOfFireDamage(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = func_0x09075408();
  if (((iVar1 == 0) || (iVar1 = IsOfType(param_1,10 /* Fire */), iVar1 != 0)) ||
     (iVar1 = GetBankAbility(param_1), iVar1 == 0x73)) {
    uVar2 = 0;
  }
  else {
    uVar3 = GetBaseMaxHP(param_1);
    uVar2 = MathMax(1,uVar3 >> 3 & 0xffff);
  }
  return uVar2;
}

// ---- sub_9090fba  (ROM 0x9090fba)
undefined8 sub_9090fba(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1;
  if (((gBattleMons[param_1].status1 & 7) == 0) || (iVar3 = GetBankAbility(), iVar3 == 0x73)) {
    iVar3 = 0;
  }
  else {
    uVar1 = GetBaseMaxHP(param_1);
    iVar3 = MathMax(1,uVar1 >> 3 & 0xffff);
    iVar4 = 0;
    iVar2 = AbilityBattleEffects(0x10,param_1,0xce,0,0,param_2,param_3);
    iVar3 = iVar3 * iVar2;
  }
  return CONCAT44(iVar4,iVar3);
}

// ---- GetGMaxVineLashDamage  (ROM 0x9091008)
undefined4 GetGMaxVineLashDamage(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x090754ac();
  if (((iVar1 == 0) || (iVar1 = IsOfType(param_1,0xc /* Grass */), iVar1 != 0)) ||
     (iVar1 = GetBankAbility(param_1), iVar1 == 0x73)) {
    uVar2 = 0;
  }
  else {
    uVar2 = func_0x09090ce8(param_1);
  }
  return uVar2;
}

// ---- GetGMaxWildfireDamage  (ROM 0x9091036)
undefined4 GetGMaxWildfireDamage(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x090754b0();
  if (((iVar1 == 0) || (iVar1 = IsOfType(param_1,10 /* Fire */), iVar1 != 0)) ||
     (iVar1 = GetBankAbility(param_1), iVar1 == 0x73)) {
    uVar2 = 0;
  }
  else {
    uVar2 = func_0x09090ce8(param_1);
  }
  return uVar2;
}

// ---- GetGMaxCannonadeDamage  (ROM 0x9091064)
undefined4 GetGMaxCannonadeDamage(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x090754b4();
  if (((iVar1 == 0) || (iVar1 = IsOfType(param_1,0xb /* Water */), iVar1 != 0)) ||
     (iVar1 = GetBankAbility(param_1), iVar1 == 0x73)) {
    uVar2 = 0;
  }
  else {
    uVar2 = func_0x09090ce8(param_1);
  }
  return uVar2;
}

// ---- sub_9091092  (ROM 0x9091092)
undefined4 sub_9091092(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x090754b8();
  if ((iVar1 == 0) || (iVar1 = GetBankAbility(param_1), iVar1 == 0x73)) {
    uVar2 = 0;
  }
  else {
    uVar2 = func_0x09090ce8(param_1);
  }
  return uVar2;
}

// ---- sub_909a418  (ROM 0x909a418)
bool sub_909a418(int param_1)

{
  return param_1 - 0x395U < 5;
}

// ---- sub_909a830  (ROM 0x909a830)
undefined4 sub_909a830(void)

{
  return 5;
}

// ---- sub_909a9de  (ROM 0x909a9de)
void sub_909a9de(int param_1)

{
  byte bVar1;
  
  bVar1 = gBattleMoves[gBattleMons[param_1].moves[0]].type;
  gBattleMons[param_1].type1 = bVar1;
  if (gBattleMons[param_1].moves[1] != 0) {
    bVar1 = gBattleMoves[gBattleMons[param_1].moves[1]].type;
  }
  gBattleMons[param_1].type2 = bVar1;
  return;
}

// ---- sub_909aa18  (ROM 0x909aa18)
byte sub_909aa18(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = GetMonData(param_1,0xe,0);
    uVar1 = uVar1 & 0xffff;
    if (uVar1 != 0) goto LAB_0909aa50;
  }
  uVar1 = GetMonData(param_1,0xd,0);
LAB_0909aa50:
  return gBattleMoves[uVar1].type;
}

// ---- sub_909ad90  (ROM 0x909ad90)
bool sub_909ad90(undefined4 param_1)

{
  int iVar1;
  
  if (((int)((uint)UNK_03003529 << 0x1e) < 0) && (param_1 = 1, gBattleTypeFlags << 3 < 0)) {
    return true;
  }
  iVar1 = func_0x0909ad58(param_1);
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x03003529) is written */
  return iVar1 != 0;
}

// ---- IsMegaZMoveBannedBattle  (ROM 0x909add4)
uint IsMegaZMoveBannedBattle(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined8 uVar2;
  
  if (gBattleTypeFlags << 0x1c < 0) {
    uVar2 = FlagGet(0x930);
    if ((int)uVar2 != 0) {
      cVar1 = VarGet(0x5018,(int)((ulonglong)uVar2 >> 0x20),param_3,&VarGet);
      if (cVar1 == '\x10') {
        return 1;
      }
      if (gBattleTypeFlags << 5 < 0) {
        return (_UNK_0203e044 & 0x7ffff) >> 0x12;
      }
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x0203e044) is written */
  return 0;
}

// ---- sub_90a0104  (ROM 0x90a0104)
bool sub_90a0104(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  
  uVar1 = gLastUsedMoves[param_1];
  if (((uVar1 != 0xa5) && (uVar1 != 0xe3)) && (uVar1 != 0x2a6)) {
    uVar2 = *(undefined2 *)(&gLastPrintedMoves + param_1 * 2);
    iVar3 = CheckTableForMove(uVar1,&UNK_090400fe);
    if (((iVar3 == 0) && (iVar3 = sub_90748d2(uVar1), iVar3 == 0)) &&
       ((iVar3 = IsAnyMaxMove(uVar1), iVar3 == 0 &&
        ((iVar3 = sub_90748d2(uVar2), iVar3 == 0 && (iVar3 = IsAnyMaxMove(uVar2), iVar3 == 0)))))) {
      iVar3 = IsDynamaxed(param_1);
      return iVar3 != 0;
    }
  }
  return true;
}

// ---- SandstormHurts  (ROM 0x90a0ee0)
bool SandstormHurts(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = GetBankAbility();
  iVar2 = func_0x0909cbac(param_1);
  if ((((iVar2 == 0) || (iVar2 = IsOfType(param_1,5 /* Rock */), iVar2 != 0)) ||
      (iVar2 = IsOfType(param_1,4 /* Ground */), iVar2 != 0)) ||
     (((iVar2 = IsOfType(param_1,8 /* Steel */), iVar2 != 0 || (iVar1 == 8)) || (iVar1 == 0x7c)))) {
    bVar3 = false;
  }
  else {
    bVar3 = iVar1 != 0x5f;
  }
  return bVar3;
}

// ---- sub_90a0f2e  (ROM 0x90a0f2e)
undefined8 sub_90a0f2e(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = AbilityBattleEffects(0x13,0,0xd,0,0,param_2,param_3);
  uVar2 = 0;
  if ((iVar1 == 0) && ((gBattleWeather & 0x18) != 0)) {
    uVar2 = SandstormHurts(param_1);
  }
  return CONCAT44(uVar3,uVar2);
}

// ---- HailHurts  (ROM 0x90a0f60)
bool HailHurts(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = GetBankAbility();
  iVar2 = func_0x0909cbac(param_1);
  if (((iVar2 == 0) || (iVar2 = IsOfType(param_1,0xf /* Ice */), iVar2 != 0)) || (iVar1 == 0x69)) {
    bVar3 = false;
  }
  else {
    bVar3 = iVar1 != 0xab;
  }
  return bVar3;
}

// ---- sub_90a0f92  (ROM 0x90a0f92)
undefined8 sub_90a0f92(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = AbilityBattleEffects(0x13,0,0xd,0,0,param_2,param_3);
  uVar2 = 0;
  if ((iVar1 == 0) && ((gBattleWeather & 0x180) != 0)) {
    uVar2 = HailHurts(param_1);
  }
  return CONCAT44(uVar3,uVar2);
}

// ---- sub_90a0fc8  (ROM 0x90a0fc8)
void sub_90a0fc8(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = sub_90a0f2e();
  if (iVar1 != 0) {
    uVar2 = GetBaseMaxHP(param_1);
    MathMax(1,uVar2 >> 4 & 0xffff);
  }
  return;
}

// ---- sub_90a3700  (ROM 0x90a3700)
undefined2 sub_90a3700(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined *puVar3;
  
  puVar3 = &UNK_09166364;
  if (gTerrainType - 1 < 4) {
                        switch(gTerrainType - 1) {
    case 1:
      uVar1 = 0x175;
      break;
    case 2:
      uVar1 = 0x1d0;
      break;
    case 3:
      uVar1 = 0x5e;
      break;
    case 0:
      goto sw_a370e_0;
    }
  }
  else {
    iVar2 = func_0x09072b68();
    if (iVar2 != 0) {
      return 0xa1;
    }
    puVar3 = &UNK_09166364 + (gBattleTerrain + 4) * 8;
sw_a370e_0:
    uVar1 = *(undefined2 *)(puVar3 + 4);
  }
                    /* WARNING: Read-only address (ram,0x02022b50) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
  return uVar1;
}

// ---- sub_90a404c  (ROM 0x90a404c)
undefined1 sub_90a404c(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined *puVar3;
  
  puVar3 = &UNK_09166364;
  if (gTerrainType - 1 < 4) {
                        switch(gTerrainType - 1) {
    case 1:
      uVar1 = 1;
      break;
    case 2:
      uVar1 = 0x19;
      break;
    case 3:
      uVar1 = 0x18;
      break;
    case 0:
      goto sw_a405a_0;
    }
  }
  else {
    iVar2 = func_0x09072b68();
    if (iVar2 != 0) {
      return 5;
    }
    iVar2 = func_0x090729ac();
    puVar3 = &UNK_09166364 + (iVar2 + 4) * 8;
sw_a405a_0:
    uVar1 = puVar3[1];
  }
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
  return uVar1;
}

// ---- sub_90a46c0  (ROM 0x90a46c0)
undefined1 sub_90a46c0(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined *puVar3;
  
  puVar3 = &UNK_09166364;
  if (gTerrainType - 1 < 4) {
                        switch(gTerrainType - 1) {
    case 1:
      uVar1 = 0xc;
      break;
    case 2:
      uVar1 = 0x17;
      break;
    case 3:
      uVar1 = 0xe;
      break;
    case 0:
      goto sw_a46ce_0;
    }
  }
  else {
    iVar2 = func_0x09072b68();
    if (iVar2 == 0) {
      return (&UNK_09166364)[(gBattleTerrain + 4) * 8];
    }
    puVar3 = &UNK_091663c4;
sw_a46ce_0:
    uVar1 = *puVar3;
  }
                    /* WARNING: Read-only address (ram,0x02022b50) is written */
                    /* WARNING: Read-only address (ram,0x0203e028) is written */
  return uVar1;
}

// ---- ItemId_GetHoldEffectParam  (ROM 0x90a5268)
undefined1 ItemId_GetHoldEffectParam(uint param_1)

{
  if (0x2ed < param_1) {
    param_1 = 0;
  }
  return (&UNK_093c0013)[param_1 * 0x2c];
}

// ---- IsTypeZCrystal  (ROM 0x90a52b6)
bool IsTypeZCrystal(undefined4 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  iVar1 = func_0x090a52a8();
  if ((iVar1 != 0) && (iVar1 = ItemId_GetHoldEffectParam(param_1), iVar1 == param_2)) {
    iVar1 = func_0x090bd730(param_1);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}

// ---- sub_90a52de  (ROM 0x90a52de)
bool sub_90a52de(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = GetPocketByItemId(param_1);
  return iVar1 == 5;
}

// ---- sub_90a52f4  (ROM 0x90a52f4)
undefined4 sub_90a52f4(uint param_1)

{
  if (param_1 != 0x60) {
    if (param_1 < 0x61) {
      if (6 < param_1 - 0xf) {
        return 0;
      }
    }
    else if (param_1 != 0x7f) {
      return 0;
    }
  }
  return 1;
}

// ---- sub_90a9430  (ROM 0x90a9430)
short sub_90a9430(int param_1,uint param_2,ushort *param_3)

{
  short sVar1;
  short *psVar2;
  ushort *puVar3;
  uint uVar4;
  
  psVar2 = (short *)(&UNK_097cd9b0 + param_1 * 0x80);
  do {
    if ((*psVar2 == 0xfe) && (uVar4 = (uint)(ushort)psVar2[1], uVar4 != 0)) {
      sVar1 = psVar2[3];
      if ((sVar1 == 0) || (sVar1 == 3)) {
        if (uVar4 == param_2) {
LAB_090a9458:
          return psVar2[2];
        }
      }
      else if ((sVar1 == 2) && (param_3 != (ushort *)0x0)) {
        puVar3 = param_3;
        do {
          if (*puVar3 == uVar4) goto LAB_090a9458;
          puVar3 = puVar3 + 1;
        } while (param_3 + 4 != puVar3);
      }
    }
    psVar2 = psVar2 + 4;
    if (psVar2 == (short *)(&UNK_097cda30 + param_1 * 0x80)) {
      return 0;
    }
  } while( true );
}

// ---- sub_90a9534  (ROM 0x90a9534)
bool sub_90a9534(void)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = true;
  if (-1 < gBattleTypeFlags << 0x1e) {
    iVar1 = func_0x090a93c4();
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

// ---- sub_90a9554  (ROM 0x90a9554)
undefined8 sub_90a9554(undefined4 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  short *psVar6;
  
  if ((((param_2 != 0) || (iVar2 = sub_90a9534(), iVar2 != 0)) &&
      (iVar2 = IsMegaZMoveBannedBattle(), iVar2 == 0)) &&
     (((int)(gBattleTypeFlags << 0x1c) < 0 ||
      (iVar2 = GetBattlerSide(param_1), iVar2 != 1)))) {
    iVar2 = GetBankPartyData(param_1);
    iVar5 = (uint)*(ushort *)(iVar2 + 0x20) * 0x80;
    psVar6 = (short *)(&UNK_097cd9b0 + iVar5);
    do {
      if ((*psVar6 == 0xfe) && (psVar6[1] != 0)) {
        sVar1 = psVar6[3];
        if (param_2 == 0) {
          if (sVar1 == 0) {
LAB_090a95ee:
            if (*(short *)(iVar2 + 0x22) == psVar6[1]) goto LAB_090a95f4;
          }
          else if (((sVar1 == 2) &&
                   (iVar3 = func_0x090a52a8(*(undefined2 *)(iVar2 + 0x22)), iVar3 == 0)) &&
                  (((gBattleTypeFlags & 0x6000100) == 0 || (iVar3 = func_0x0909ad2c(), iVar3 != 0))
                  )) {
            psVar4 = (short *)(iVar2 + 0x2c);
            do {
              if (*psVar4 == psVar6[1]) goto LAB_090a95f4;
              psVar4 = psVar4 + 1;
            } while (psVar4 != (short *)(iVar2 + 0x34));
          }
        }
        else if (sVar1 == 3) goto LAB_090a95ee;
      }
      psVar6 = psVar6 + 4;
    } while (psVar6 != (short *)(&UNK_097cda30 + iVar5));
  }
  psVar6 = (short *)0x0;
LAB_090a95f4:
  return CONCAT44(param_2,psVar6);
}

// ---- GetBankMegaFormAbility  (ROM 0x90a9704)
uint GetBankMegaFormAbility(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  
  iVar2 = IsAbilitySuppressed();
  if ((iVar2 == 0) &&
     ((iVar2 = sub_90a9554(param_1), iVar2 != 0 || (iVar2 = sub_90a9554(param_1,1), iVar2 != 0)))) {
    uVar3 = func_0x090c2218(*(undefined2 *)(iVar2 + 4));
    if ((uVar3 == 0x24) && (-1 < gBattleTypeFlags << 0x1f)) {
      pbVar4 = (byte *)GetAbilityLocation(param_2);
      bVar1 = *pbVar4;
      iVar2 = CheckTableForAbility(0x24,&UNK_0900a008);
      if (iVar2 == 0) {
        uVar3 = (uint)bVar1;
      }
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ---- sub_90a9764  (ROM 0x90a9764)
bool sub_90a9764(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetBattlerSide(param_1);
  if (iVar1 != 1) {
    iVar1 = GetBattlerSide(param_1);
    if (((iVar1 == 0) && (gBattleTypeFlags << 9 < 0)) ||
       ((iVar1 = GetBattlerSide(param_1), iVar1 == 1 && (gBattleTypeFlags << 10 < 0)))) {
      if (param_2 == 0) {
        iVar1 = gNewBS + param_1 + 0x79;
      }
      else {
        iVar1 = gNewBS + param_1 + 0x8d;
      }
      return *(char *)(iVar1 + 0xff) != '\0';
    }
    if (param_2 == 0) {
      if (*(char *)(gNewBS + param_1 + 0x178) != '\0') {
        return true;
      }
      iVar1 = gNewBS + (param_1 ^ 2) + 0x79;
    }
    else {
      if (*(char *)(gNewBS + param_1 + 0x18c) != '\0') {
        return true;
      }
      iVar1 = gNewBS + (param_1 ^ 2) + 0x8d;
    }
    if (*(char *)(iVar1 + 0xff) != '\0') {
      return true;
    }
  }
                    /* WARNING: Read-only address (ram,0x02022b4c) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
  return false;
}

// ---- sub_90a97fc  (ROM 0x90a97fc)
undefined4 sub_90a97fc(int param_1)

{
  short *psVar1;
  
  psVar1 = (short *)(&UNK_097cd9b0 + param_1 * 0x80);
  while (((*psVar1 != 0xfe || ((psVar1[3] & 0xfffdU) != 0)) || (psVar1[1] != 0))) {
    psVar1 = psVar1 + 4;
    if (psVar1 == (short *)(&UNK_097cda30 + param_1 * 0x80)) {
      return 0;
    }
  }
  return 1;
}

// ---- sub_90a9830  (ROM 0x90a9830)
bool sub_90a9830(int param_1)

{
  return param_1 == 0x38e;
}

// ---- sub_90a9840  (ROM 0x90a9840)
bool sub_90a9840(int param_1)

{
  return param_1 == 0x38d || param_1 == 0x397;
}

// ---- sub_90a985c  (ROM 0x90a985c)
void sub_90a985c(void)

{
  int iVar1;
  
  iVar1 = GetBankPartyData();
  sub_90a97fc(*(undefined2 *)(iVar1 + 0x20));
  return;
}

// ---- sub_90a988e  (ROM 0x90a988e)
undefined4 sub_90a988e(int param_1)

{
  short *psVar1;
  
  psVar1 = (short *)(&UNK_097cd9b0 + param_1 * 0x80);
  while (((*psVar1 != 0xfe || (psVar1[3] != 3)) || (psVar1[1] != 0))) {
    psVar1 = psVar1 + 4;
    if (psVar1 == (short *)(&UNK_097cda30 + param_1 * 0x80)) {
      return 0;
    }
  }
  return 1;
}

// ---- sub_90ad614  (ROM 0x90ad614)
bool sub_90ad614(void)

{
  return (gBattleTypeFlags & 0x400001) == 0x400001;
}

// ---- BankSideHasTwoTrainers  (ROM 0x90ad634)
bool BankSideHasTwoTrainers(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = GetBattlerSide(param_1);
  if (iVar1 == 1) {
    iVar1 = func_0x090ad5f4();
  }
  else {
    if (iVar1 != 0) {
      return false;
    }
    iVar1 = sub_90ad614();
  }
  return iVar1 != 0;
}

// ---- sub_90bd77c  (ROM 0x90bd77c)
bool sub_90bd77c(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = gNewBS;
  bVar3 = false;
  if (*(char *)(gNewBS + param_1 + 0x194) != '\0') {
    iVar2 = GetBattlerSide(param_1);
    bVar3 = (*(uint *)(&gBitTable + (uint)gBattlerPartyIndexes[param_1] * 4) &
            (uint)*(byte *)(uVar1 + iVar2 + 0x198)) != 0;
  }
  return bVar3;
}

// ---- sub_90bd7d0  (ROM 0x90bd7d0)
undefined8 sub_90bd7d0(int param_1,int param_2,uint param_3)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  iVar6 = param_1;
  iVar3 = param_2;
  uVar4 = param_3;
  uVar2 = GetBankPartyData();
  sVar1 = GetMonData(uVar2,0xc,0,&GetMonData,iVar6,iVar3,uVar4);
  if (param_3 == 0) {
    param_3 = (uint)gBattleMons[param_1].moves[param_2];
  }
  iVar3 = IsMegaZMoveBannedBattle();
  if ((((iVar3 == 0) &&
       ((iVar3 = FlagGet(0x82c), iVar3 != 0 ||
        (iVar3 = sub_91521d0(0x1034), iVar3 != 0)))) &&
      ((iVar3 = GetBattlerSide(param_1), iVar3 == 1 || (iVar3 = sub_91521d0(0x1017), iVar3 != 0))))
     && (((iVar3 = sub_90a985c(param_1), iVar3 == 0 &&
          (iVar3 = func_0x090a9880(param_1), iVar3 == 0)) &&
         (iVar3 = func_0x090a986a(param_1), iVar3 == 0)))) {
    iVar3 = func_0x090a52a8(sVar1);
    if ((iVar3 != 0) || (sVar1 == 0x214)) {
      iVar3 = func_0x090bd6d4(param_3,gBattleMons[param_1].species,sVar1);
      if ((iVar3 - 1U & 0xffff) < 0xfffe) goto LAB_090bd808;
      if ((param_3 != 0) && (iVar3 != 0xffff)) {
        uVar5 = (uint)gBattleMoves[param_3].type;
        uVar4 = ItemId_GetHoldEffectParam(sVar1);
        if (uVar5 == uVar4) {
          iVar3 = 0xffff;
          if (gBattleMoves[param_3].split != 2) {
            iVar3 = func_0x090bd668(param_3,param_1);
          }
          goto LAB_090bd808;
        }
      }
    }
  }
  iVar3 = 0;
LAB_090bd808:
  return CONCAT44(iVar6,iVar3);
}

// ---- ReplaceWithZMoveRuntime  (ROM 0x90bd8ec)
int ReplaceWithZMoveRuntime(int param_1,int param_2)

{
  int iVar1;
  
  if (((*(char *)(gNewBS + param_1 + 400) == '\0') || (*(char *)(gNewBS + param_1 + 0x194) != '\0'))
     || (gBattleMoves[param_2].split == 2)) {
    iVar1 = IsDynamaxed(param_1);
    if (iVar1 == 0) {
      if (*(char *)(gNewBS + param_1 + 0x19e) == '\0') {
        return param_2;
      }
      if (*(char *)(gNewBS + param_1 + 0x1a2) != '\0') {
        return param_2;
      }
    }
    iVar1 = IsRaidBattle();
    if (iVar1 != 0) {
      iVar1 = GetBattlerAtPosition(1);
      return iVar1;
    }
    iVar1 = GetMaxMoveByMove(param_1,param_2);
  }
  else {
    iVar1 = sub_90bd7d0(param_1,0xff,param_2);
  }
  if (iVar1 == 0) {
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
                    /* WARNING: Read-only address (ram,0x0203e038) is written */
    return param_2;
  }
  return iVar1;
}

// ---- sub_90becd0  (ROM 0x90becd0)
bool sub_90becd0(void)

{
  int iVar1;
  
  iVar1 = func_0x090bec54();
  return iVar1 == 0;
}

// ---- sub_90bff90  (ROM 0x90bff90)
undefined4 sub_90bff90(undefined4 param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = sub_9074de4();
  uVar3 = 0;
  if (iVar2 != 0x87) {
    bVar1 = (&gSideTimers[0].field_0xa)[param_2 * 0xb];
    uVar3 = GetMonData(param_1,0x3a);
    uVar3 = __udivsi3(uVar3,(5 - (bVar1 & 3)) * 2);
    uVar3 = MathMax(1,uVar3);
  }
  return uVar3;
}

// ---- sub_90c0094  (ROM 0x90c0094)
undefined4 sub_90c0094(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_2 [2];
  
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  gBattleMoveDamage = 0x28;
  iVar1 = sub_9074de4();
  uVar3 = 0;
  if (iVar1 != 0x87) {
    func_0x09082fc8(0,param_1,0x1d4,5,auStack_2 + -0xf,param_2,param_3,param_4);
    uVar3 = func_0x090bece0();
    uVar2 = GetMonData(param_1,0x3a,0);
    uVar3 = __udivsi3(uVar2,uVar3);
    uVar3 = MathMax(1,uVar3);
  }
  return uVar3;
}

// ---- sub_90c0c1e  (ROM 0x90c0c1e)
undefined4 sub_90c0c1e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_2 [2];
  
                    /* WARNING: Read-only address (ram,0x02023d50) is written */
  gBattleMoveDamage = 0x28;
  iVar1 = sub_9074de4();
  uVar3 = 0;
  if (iVar1 != 0x87) {
    func_0x09082fc8(0,param_1,0x17e,8,auStack_2 + -0xf,param_2,param_3,param_4);
    uVar3 = func_0x090bece0();
    uVar2 = GetMonData(param_1,0x3a,0);
    uVar3 = __udivsi3(uVar2,uVar3);
    uVar3 = MathMax(1,uVar3);
  }
  return uVar3;
}

// ---- GetMonEntryHazardDamage  (ROM 0x90c0c78)
int GetMonEntryHazardDamage(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if ((((int)((uint)gSideStatuses[param_2] << 0x1b) < 0) && (iVar2 = GetMonAbility(), iVar2 != 0x73)
      ) && (iVar2 = sub_9074eb8(param_1), iVar2 != 0)) {
    iVar2 = 0;
    if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[param_2 * 0xb] << 0x1b) < 0) {
      iVar2 = func_0x090c0048(param_1);
    }
    if ((int)((uint)(byte)(&gSideTimers[0].field_0xa)[param_2 * 0xb] << 0x19) < 0) {
      iVar1 = sub_90c0c1e(param_1);
      iVar2 = iVar2 + iVar1;
    }
    iVar1 = (uint)(byte)(&gSideTimers[0].field_0xa)[param_2 * 0xb] << 0x1e;
    if (iVar1 != 0) {
      iVar1 = sub_90bff90(param_1,param_2,0xb,iVar1,param_4);
      iVar2 = iVar2 + iVar1;
    }
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

// ---- sub_90c0cf4  (ROM 0x90c0cf4)
void sub_90c0cf4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  GetMonData(param_1,0x39,0,param_4,param_1,param_2,param_3);
  return;
}

// ---- MathMax  (ROM 0x90c1850)
uint MathMax(uint param_1,uint param_2)

{
  if (param_1 < param_2) {
    param_1 = param_2;
  }
  return param_1;
}

// ---- MathMin  (ROM 0x90c1858)
uint MathMin(uint param_1,uint param_2)

{
  if (param_2 < param_1) {
    param_1 = param_2;
  }
  return param_1;
}

// ---- CheckTableForMove  (ROM 0x90c1884)
undefined4 CheckTableForMove(uint param_1,ushort *param_2)

{
  ushort uVar1;
  
  do {
    uVar1 = *param_2;
    if (uVar1 == 0xfefe) {
      return 0;
    }
    param_2 = param_2 + 1;
  } while (uVar1 != param_1);
  return 1;
}

// ---- CheckTableForMovesEffect  (ROM 0x90c1a10)
undefined4 CheckTableForMovesEffect(int param_1,byte *param_2)

{
  byte bVar1;
  
  do {
    bVar1 = *param_2;
    if (bVar1 == 0xff) {
      return 0;
    }
    param_2 = param_2 + 1;
  } while (gBattleMoves[param_1].effect != bVar1);
  return 1;
}

// ---- CheckTableForAbility  (ROM 0x90c1a38)
undefined4 CheckTableForAbility(uint param_1,byte *param_2)

{
  byte bVar1;
  
  do {
    bVar1 = *param_2;
    if (bVar1 == 0xff) {
      return 0;
    }
    param_2 = param_2 + 1;
  } while (bVar1 != param_1);
  return 1;
}

// ---- sub_90c1a54  (ROM 0x90c1a54)
void sub_90c1a54(void)

{
  CheckTableForMove();
  return;
}

// ---- sub_90c1c9c  (ROM 0x90c1c9c)
uint sub_90c1c9c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    iVar1 = GetMonData(param_2,uVar2 + 0xd,0,&GetMonData,param_4);
    if (iVar1 == param_1) {
      return uVar2 & 0xff;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 4);
  return 4;
}

// ---- sub_90c1df8  (ROM 0x90c1df8)
bool sub_90c1df8(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = func_0x090c1d94(param_1,0);
  iVar2 = func_0x090c1d94(param_1,1);
  return iVar1 == param_2 || iVar2 == param_2;
}

// ---- sub_90c1ed2  (ROM 0x90c1ed2)
bool sub_90c1ed2(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = func_0x090c1d94(param_1,0);
  iVar2 = func_0x090c1d94(param_1,1);
  iVar3 = func_0x090c1e78(param_1);
  if (iVar3 != 0) {
    iVar3 = GetMonAbility(param_1);
    if (iVar3 == 0x11) {
      return false;
    }
    if (((iVar1 != 3) && (iVar2 != 3)) && (iVar1 != 8)) {
      return iVar2 != 8;
    }
  }
  return false;
}
