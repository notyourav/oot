glabel func_809EE408
/* 00B98 809EE408 27BDFFE0 */  addiu   $sp, $sp, 0xFFE0           ## $sp = FFFFFFE0
/* 00B9C 809EE40C AFB00018 */  sw      $s0, 0x0018($sp)           
/* 00BA0 809EE410 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00BA4 809EE414 AFBF001C */  sw      $ra, 0x001C($sp)           
/* 00BA8 809EE418 AFA50024 */  sw      $a1, 0x0024($sp)           
/* 00BAC 809EE41C 0C02927F */  jal     SkelAnime_FrameUpdateMatrix
              
/* 00BB0 809EE420 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 00BB4 809EE424 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 00BB8 809EE428 0C03036D */  jal     func_800C0DB4              
/* 00BBC 809EE42C 260500E4 */  addiu   $a1, $s0, 0x00E4           ## $a1 = 000000E4
/* 00BC0 809EE430 50400004 */  beql    $v0, $zero, .L809EE444     
/* 00BC4 809EE434 860502A0 */  lh      $a1, 0x02A0($s0)           ## 000002A0
/* 00BC8 809EE438 0C03DA0A */  jal     func_800F6828              
/* 00BCC 809EE43C 00002025 */  or      $a0, $zero, $zero          ## $a0 = 00000000
/* 00BD0 809EE440 860502A0 */  lh      $a1, 0x02A0($s0)           ## 000002A0
.L809EE444:
/* 00BD4 809EE444 50A00038 */  beql    $a1, $zero, .L809EE528     
/* 00BD8 809EE448 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 00BDC 809EE44C C60402E8 */  lwc1    $f4, 0x02E8($s0)           ## 000002E8
/* 00BE0 809EE450 C6060318 */  lwc1    $f6, 0x0318($s0)           ## 00000318
/* 00BE4 809EE454 260402C4 */  addiu   $a0, $s0, 0x02C4           ## $a0 = 000002C4
/* 00BE8 809EE458 8E0502D0 */  lw      $a1, 0x02D0($s0)           ## 000002D0
/* 00BEC 809EE45C 46062202 */  mul.s   $f8, $f4, $f6              
/* 00BF0 809EE460 8E0602DC */  lw      $a2, 0x02DC($s0)           ## 000002DC
/* 00BF4 809EE464 44074000 */  mfc1    $a3, $f8                   
/* 00BF8 809EE468 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00BFC 809EE46C 00000000 */  nop
/* 00C00 809EE470 C60A02F0 */  lwc1    $f10, 0x02F0($s0)          ## 000002F0
/* 00C04 809EE474 C6100318 */  lwc1    $f16, 0x0318($s0)          ## 00000318
/* 00C08 809EE478 260402CC */  addiu   $a0, $s0, 0x02CC           ## $a0 = 000002CC
/* 00C0C 809EE47C 8E0502D8 */  lw      $a1, 0x02D8($s0)           ## 000002D8
/* 00C10 809EE480 46105482 */  mul.s   $f18, $f10, $f16           
/* 00C14 809EE484 8E0602E4 */  lw      $a2, 0x02E4($s0)           ## 000002E4
/* 00C18 809EE488 44079000 */  mfc1    $a3, $f18                  
/* 00C1C 809EE48C 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00C20 809EE490 00000000 */  nop
/* 00C24 809EE494 C604030C */  lwc1    $f4, 0x030C($s0)           ## 0000030C
/* 00C28 809EE498 C6060318 */  lwc1    $f6, 0x0318($s0)           ## 00000318
/* 00C2C 809EE49C 260402B8 */  addiu   $a0, $s0, 0x02B8           ## $a0 = 000002B8
/* 00C30 809EE4A0 8E0502F4 */  lw      $a1, 0x02F4($s0)           ## 000002F4
/* 00C34 809EE4A4 46062202 */  mul.s   $f8, $f4, $f6              
/* 00C38 809EE4A8 8E060300 */  lw      $a2, 0x0300($s0)           ## 00000300
/* 00C3C 809EE4AC 44074000 */  mfc1    $a3, $f8                   
/* 00C40 809EE4B0 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00C44 809EE4B4 00000000 */  nop
/* 00C48 809EE4B8 C60A0310 */  lwc1    $f10, 0x0310($s0)          ## 00000310
/* 00C4C 809EE4BC C6100318 */  lwc1    $f16, 0x0318($s0)          ## 00000318
/* 00C50 809EE4C0 260402BC */  addiu   $a0, $s0, 0x02BC           ## $a0 = 000002BC
/* 00C54 809EE4C4 8E0502F8 */  lw      $a1, 0x02F8($s0)           ## 000002F8
/* 00C58 809EE4C8 46105482 */  mul.s   $f18, $f10, $f16           
/* 00C5C 809EE4CC 8E060304 */  lw      $a2, 0x0304($s0)           ## 00000304
/* 00C60 809EE4D0 44079000 */  mfc1    $a3, $f18                  
/* 00C64 809EE4D4 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00C68 809EE4D8 00000000 */  nop
/* 00C6C 809EE4DC C6040314 */  lwc1    $f4, 0x0314($s0)           ## 00000314
/* 00C70 809EE4E0 C6060318 */  lwc1    $f6, 0x0318($s0)           ## 00000318
/* 00C74 809EE4E4 260402C0 */  addiu   $a0, $s0, 0x02C0           ## $a0 = 000002C0
/* 00C78 809EE4E8 8E0502FC */  lw      $a1, 0x02FC($s0)           ## 000002FC
/* 00C7C 809EE4EC 46062202 */  mul.s   $f8, $f4, $f6              
/* 00C80 809EE4F0 8E060308 */  lw      $a2, 0x0308($s0)           ## 00000308
/* 00C84 809EE4F4 44074000 */  mfc1    $a3, $f8                   
/* 00C88 809EE4F8 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00C8C 809EE4FC 00000000 */  nop
/* 00C90 809EE500 3C013F80 */  lui     $at, 0x3F80                ## $at = 3F800000
/* 00C94 809EE504 44810000 */  mtc1    $at, $f0                   ## $f0 = 1.00
/* 00C98 809EE508 3C073CA3 */  lui     $a3, 0x3CA3                ## $a3 = 3CA30000
/* 00C9C 809EE50C 34E7D70A */  ori     $a3, $a3, 0xD70A           ## $a3 = 3CA3D70A
/* 00CA0 809EE510 44050000 */  mfc1    $a1, $f0                   
/* 00CA4 809EE514 44060000 */  mfc1    $a2, $f0                   
/* 00CA8 809EE518 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00CAC 809EE51C 26040318 */  addiu   $a0, $s0, 0x0318           ## $a0 = 00000318
/* 00CB0 809EE520 860502A0 */  lh      $a1, 0x02A0($s0)           ## 000002A0
/* 00CB4 809EE524 8FA40024 */  lw      $a0, 0x0024($sp)           
.L809EE528:
/* 00CB8 809EE528 260602B8 */  addiu   $a2, $s0, 0x02B8           ## $a2 = 000002B8
/* 00CBC 809EE52C 0C030136 */  jal     Gameplay_CameraSetAtEye              
/* 00CC0 809EE530 260702C4 */  addiu   $a3, $s0, 0x02C4           ## $a3 = 000002C4
/* 00CC4 809EE534 920E031E */  lbu     $t6, 0x031E($s0)           ## 0000031E
/* 00CC8 809EE538 55C0001D */  bnel    $t6, $zero, .L809EE5B0     
/* 00CCC 809EE53C 860F0294 */  lh      $t7, 0x0294($s0)           ## 00000294
/* 00CD0 809EE540 860F029A */  lh      $t7, 0x029A($s0)           ## 0000029A
/* 00CD4 809EE544 24180005 */  addiu   $t8, $zero, 0x0005         ## $t8 = 00000005
/* 00CD8 809EE548 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 00CDC 809EE54C 55E00018 */  bnel    $t7, $zero, .L809EE5B0     
/* 00CE0 809EE550 860F0294 */  lh      $t7, 0x0294($s0)           ## 00000294
/* 00CE4 809EE554 A618029A */  sh      $t8, 0x029A($s0)           ## 0000029A
/* 00CE8 809EE558 0C27B678 */  jal     func_809ED9E0              
/* 00CEC 809EE55C 8FA50024 */  lw      $a1, 0x0024($sp)           
/* 00CF0 809EE560 861902A6 */  lh      $t9, 0x02A6($s0)           ## 000002A6
/* 00CF4 809EE564 3C098016 */  lui     $t1, %hi(gSaveContext+0xeda)
/* 00CF8 809EE568 240B001E */  addiu   $t3, $zero, 0x001E         ## $t3 = 0000001E
/* 00CFC 809EE56C 2728FFFF */  addiu   $t0, $t9, 0xFFFF           ## $t0 = FFFFFFFF
/* 00D00 809EE570 A60802A6 */  sh      $t0, 0x02A6($s0)           ## 000002A6
/* 00D04 809EE574 9529F53A */  lhu     $t1, %lo(gSaveContext+0xeda)($t1)
/* 00D08 809EE578 240C0005 */  addiu   $t4, $zero, 0x0005         ## $t4 = 00000005
/* 00D0C 809EE57C 240E0001 */  addiu   $t6, $zero, 0x0001         ## $t6 = 00000001
/* 00D10 809EE580 312A0100 */  andi    $t2, $t1, 0x0100           ## $t2 = 00000000
/* 00D14 809EE584 55400004 */  bnel    $t2, $zero, .L809EE598     
/* 00D18 809EE588 A60C0296 */  sh      $t4, 0x0296($s0)           ## 00000296
/* 00D1C 809EE58C 10000002 */  beq     $zero, $zero, .L809EE598   
/* 00D20 809EE590 A60B0296 */  sh      $t3, 0x0296($s0)           ## 00000296
/* 00D24 809EE594 A60C0296 */  sh      $t4, 0x0296($s0)           ## 00000296
.L809EE598:
/* 00D28 809EE598 860D02A6 */  lh      $t5, 0x02A6($s0)           ## 000002A6
/* 00D2C 809EE59C 5DA00004 */  bgtzl   $t5, .L809EE5B0            
/* 00D30 809EE5A0 860F0294 */  lh      $t7, 0x0294($s0)           ## 00000294
/* 00D34 809EE5A4 A60002A6 */  sh      $zero, 0x02A6($s0)         ## 000002A6
/* 00D38 809EE5A8 A20E031E */  sb      $t6, 0x031E($s0)           ## 0000031E
/* 00D3C 809EE5AC 860F0294 */  lh      $t7, 0x0294($s0)           ## 00000294
.L809EE5B0:
/* 00D40 809EE5B0 51E00034 */  beql    $t7, $zero, .L809EE684     
/* 00D44 809EE5B4 861802A2 */  lh      $t8, 0x02A2($s0)           ## 000002A2
/* 00D48 809EE5B8 C60A02C4 */  lwc1    $f10, 0x02C4($s0)          ## 000002C4
/* 00D4C 809EE5BC C61002D0 */  lwc1    $f16, 0x02D0($s0)          ## 000002D0
/* 00D50 809EE5C0 3C014000 */  lui     $at, 0x4000                ## $at = 40000000
/* 00D54 809EE5C4 44811000 */  mtc1    $at, $f2                   ## $f2 = 2.00
/* 00D58 809EE5C8 46105001 */  sub.s   $f0, $f10, $f16            
/* 00D5C 809EE5CC 46000005 */  abs.s   $f0, $f0                   
/* 00D60 809EE5D0 4602003C */  c.lt.s  $f0, $f2                   
/* 00D64 809EE5D4 00000000 */  nop
/* 00D68 809EE5D8 45020037 */  bc1fl   .L809EE6B8                 
/* 00D6C 809EE5DC 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00D70 809EE5E0 C61202C8 */  lwc1    $f18, 0x02C8($s0)          ## 000002C8
/* 00D74 809EE5E4 C60402D4 */  lwc1    $f4, 0x02D4($s0)           ## 000002D4
/* 00D78 809EE5E8 46049001 */  sub.s   $f0, $f18, $f4             
/* 00D7C 809EE5EC 46000005 */  abs.s   $f0, $f0                   
/* 00D80 809EE5F0 4602003C */  c.lt.s  $f0, $f2                   
/* 00D84 809EE5F4 00000000 */  nop
/* 00D88 809EE5F8 4502002F */  bc1fl   .L809EE6B8                 
/* 00D8C 809EE5FC 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00D90 809EE600 C60602CC */  lwc1    $f6, 0x02CC($s0)           ## 000002CC
/* 00D94 809EE604 C60802D8 */  lwc1    $f8, 0x02D8($s0)           ## 000002D8
/* 00D98 809EE608 46083001 */  sub.s   $f0, $f6, $f8              
/* 00D9C 809EE60C 46000005 */  abs.s   $f0, $f0                   
/* 00DA0 809EE610 4602003C */  c.lt.s  $f0, $f2                   
/* 00DA4 809EE614 00000000 */  nop
/* 00DA8 809EE618 45020027 */  bc1fl   .L809EE6B8                 
/* 00DAC 809EE61C 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00DB0 809EE620 C60A02B8 */  lwc1    $f10, 0x02B8($s0)          ## 000002B8
/* 00DB4 809EE624 C61002F4 */  lwc1    $f16, 0x02F4($s0)          ## 000002F4
/* 00DB8 809EE628 46105001 */  sub.s   $f0, $f10, $f16            
/* 00DBC 809EE62C 46000005 */  abs.s   $f0, $f0                   
/* 00DC0 809EE630 4602003C */  c.lt.s  $f0, $f2                   
/* 00DC4 809EE634 00000000 */  nop
/* 00DC8 809EE638 4502001F */  bc1fl   .L809EE6B8                 
/* 00DCC 809EE63C 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00DD0 809EE640 C61202BC */  lwc1    $f18, 0x02BC($s0)          ## 000002BC
/* 00DD4 809EE644 C60402F8 */  lwc1    $f4, 0x02F8($s0)           ## 000002F8
/* 00DD8 809EE648 46049001 */  sub.s   $f0, $f18, $f4             
/* 00DDC 809EE64C 46000005 */  abs.s   $f0, $f0                   
/* 00DE0 809EE650 4602003C */  c.lt.s  $f0, $f2                   
/* 00DE4 809EE654 00000000 */  nop
/* 00DE8 809EE658 45020017 */  bc1fl   .L809EE6B8                 
/* 00DEC 809EE65C 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00DF0 809EE660 C60602C0 */  lwc1    $f6, 0x02C0($s0)           ## 000002C0
/* 00DF4 809EE664 C60802FC */  lwc1    $f8, 0x02FC($s0)           ## 000002FC
/* 00DF8 809EE668 46083001 */  sub.s   $f0, $f6, $f8              
/* 00DFC 809EE66C 46000005 */  abs.s   $f0, $f0                   
/* 00E00 809EE670 4602003C */  c.lt.s  $f0, $f2                   
/* 00E04 809EE674 00000000 */  nop
/* 00E08 809EE678 4502000F */  bc1fl   .L809EE6B8                 
/* 00E0C 809EE67C 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00E10 809EE680 861802A2 */  lh      $t8, 0x02A2($s0)           ## 000002A2
.L809EE684:
/* 00E14 809EE684 3C0A809F */  lui     $t2, %hi(func_809EE6C8)    ## $t2 = 809F0000
/* 00E18 809EE688 24190046 */  addiu   $t9, $zero, 0x0046         ## $t9 = 00000046
/* 00E1C 809EE68C 13000008 */  beq     $t8, $zero, .L809EE6B0     
/* 00E20 809EE690 254AE6C8 */  addiu   $t2, $t2, %lo(func_809EE6C8) ## $t2 = 809EE6C8
/* 00E24 809EE694 3C09809F */  lui     $t1, %hi(func_809EE780)    ## $t1 = 809F0000
/* 00E28 809EE698 24080002 */  addiu   $t0, $zero, 0x0002         ## $t0 = 00000002
/* 00E2C 809EE69C 2529E780 */  addiu   $t1, $t1, %lo(func_809EE780) ## $t1 = 809EE780
/* 00E30 809EE6A0 A6190294 */  sh      $t9, 0x0294($s0)           ## 00000294
/* 00E34 809EE6A4 A60802A2 */  sh      $t0, 0x02A2($s0)           ## 000002A2
/* 00E38 809EE6A8 10000002 */  beq     $zero, $zero, .L809EE6B4   
/* 00E3C 809EE6AC AE090280 */  sw      $t1, 0x0280($s0)           ## 00000280
.L809EE6B0:
/* 00E40 809EE6B0 AE0A0280 */  sw      $t2, 0x0280($s0)           ## 00000280
.L809EE6B4:
/* 00E44 809EE6B4 8FBF001C */  lw      $ra, 0x001C($sp)           
.L809EE6B8:
/* 00E48 809EE6B8 8FB00018 */  lw      $s0, 0x0018($sp)           
/* 00E4C 809EE6BC 27BD0020 */  addiu   $sp, $sp, 0x0020           ## $sp = 00000000
/* 00E50 809EE6C0 03E00008 */  jr      $ra                        
/* 00E54 809EE6C4 00000000 */  nop
