glabel func_80B407A8
/* 045C8 80B407A8 27BDFFD8 */  addiu   $sp, $sp, 0xFFD8           ## $sp = FFFFFFD8
/* 045CC 80B407AC AFA40028 */  sw      $a0, 0x0028($sp)
/* 045D0 80B407B0 AFBF0024 */  sw      $ra, 0x0024($sp)
/* 045D4 80B407B4 3C040602 */  lui     $a0, %hi(D_06018B00)                ## $a0 = 06020000
/* 045D8 80B407B8 0C028800 */  jal     SkelAnime_GetFrameCount

/* 045DC 80B407BC 24848B00 */  addiu   $a0, $a0, %lo(D_06018B00)           ## $a0 = 06018B00
/* 045E0 80B407C0 44822000 */  mtc1    $v0, $f4                   ## $f4 = 0.00
/* 045E4 80B407C4 3C01C100 */  lui     $at, 0xC100                ## $at = C1000000
/* 045E8 80B407C8 44814000 */  mtc1    $at, $f8                   ## $f8 = -8.00
/* 045EC 80B407CC 468021A0 */  cvt.s.w $f6, $f4
/* 045F0 80B407D0 8FA40028 */  lw      $a0, 0x0028($sp)
/* 045F4 80B407D4 3C050602 */  lui     $a1, %hi(D_06018B00)                ## $a1 = 06020000
/* 045F8 80B407D8 240E0002 */  addiu   $t6, $zero, 0x0002         ## $t6 = 00000002
/* 045FC 80B407DC AFAE0014 */  sw      $t6, 0x0014($sp)
/* 04600 80B407E0 24A58B00 */  addiu   $a1, $a1, %lo(D_06018B00)           ## $a1 = 06018B00
/* 04604 80B407E4 E7A60010 */  swc1    $f6, 0x0010($sp)
/* 04608 80B407E8 3C063F80 */  lui     $a2, 0x3F80                ## $a2 = 3F800000
/* 0460C 80B407EC 24070000 */  addiu   $a3, $zero, 0x0000         ## $a3 = 00000000
/* 04610 80B407F0 E7A80018 */  swc1    $f8, 0x0018($sp)
/* 04614 80B407F4 0C029468 */  jal     SkelAnime_ChangeAnim

/* 04618 80B407F8 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 0461C 80B407FC 8FA20028 */  lw      $v0, 0x0028($sp)
/* 04620 80B40800 240F003B */  addiu   $t7, $zero, 0x003B         ## $t7 = 0000003B
/* 04624 80B40804 24180001 */  addiu   $t8, $zero, 0x0001         ## $t8 = 00000001
/* 04628 80B40808 AC4F0260 */  sw      $t7, 0x0260($v0)           ## 00000260
/* 0462C 80B4080C AC580264 */  sw      $t8, 0x0264($v0)           ## 00000264
/* 04630 80B40810 8FBF0024 */  lw      $ra, 0x0024($sp)
/* 04634 80B40814 27BD0028 */  addiu   $sp, $sp, 0x0028           ## $sp = 00000000
/* 04638 80B40818 03E00008 */  jr      $ra
/* 0463C 80B4081C 00000000 */  nop
