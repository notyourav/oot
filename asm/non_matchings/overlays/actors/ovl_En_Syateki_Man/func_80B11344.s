glabel func_80B11344
/* 00AD4 80B11344 27BDFFE8 */  addiu   $sp, $sp, 0xFFE8           ## $sp = FFFFFFE8
/* 00AD8 80B11348 AFBF0014 */  sw      $ra, 0x0014($sp)           
/* 00ADC 80B1134C 8482020E */  lh      $v0, 0x020E($a0)           ## 0000020E
/* 00AE0 80B11350 2442FFFF */  addiu   $v0, $v0, 0xFFFF           ## $v0 = FFFFFFFF
/* 00AE4 80B11354 00021400 */  sll     $v0, $v0, 16               
/* 00AE8 80B11358 00021403 */  sra     $v0, $v0, 16               
/* 00AEC 80B1135C 50400004 */  beql    $v0, $zero, .L80B11370     
/* 00AF0 80B11360 8482020C */  lh      $v0, 0x020C($a0)           ## 0000020C
/* 00AF4 80B11364 1000001B */  beq     $zero, $zero, .L80B113D4   
/* 00AF8 80B11368 A482020E */  sh      $v0, 0x020E($a0)           ## 0000020E
/* 00AFC 80B1136C 8482020C */  lh      $v0, 0x020C($a0)           ## 0000020C
.L80B11370:
/* 00B00 80B11370 24080001 */  addiu   $t0, $zero, 0x0001         ## $t0 = 00000001
/* 00B04 80B11374 24420001 */  addiu   $v0, $v0, 0x0001           ## $v0 = 00000000
/* 00B08 80B11378 00021400 */  sll     $v0, $v0, 16               
/* 00B0C 80B1137C 00021403 */  sra     $v0, $v0, 16               
/* 00B10 80B11380 28410003 */  slti    $at, $v0, 0x0003           
/* 00B14 80B11384 54200012 */  bnel    $at, $zero, .L80B113D0     
/* 00B18 80B11388 A482020C */  sh      $v0, 0x020C($a0)           ## 0000020C
/* 00B1C 80B1138C A480020C */  sh      $zero, 0x020C($a0)         ## 0000020C
/* 00B20 80B11390 0C03F66B */  jal     Math_Rand_ZeroOne
              ## Rand.Next() float
/* 00B24 80B11394 AFA40018 */  sw      $a0, 0x0018($sp)           
/* 00B28 80B11398 3C014270 */  lui     $at, 0x4270                ## $at = 42700000
/* 00B2C 80B1139C 44812000 */  mtc1    $at, $f4                   ## $f4 = 60.00
/* 00B30 80B113A0 8FA40018 */  lw      $a0, 0x0018($sp)           
/* 00B34 80B113A4 3C1980B1 */  lui     $t9, %hi(func_80B11310)    ## $t9 = 80B10000
/* 00B38 80B113A8 46040182 */  mul.s   $f6, $f0, $f4              
/* 00B3C 80B113AC 27391310 */  addiu   $t9, $t9, %lo(func_80B11310) ## $t9 = 80B11310
/* 00B40 80B113B0 AC990224 */  sw      $t9, 0x0224($a0)           ## 00000224
/* 00B44 80B113B4 4600320D */  trunc.w.s $f8, $f6                   
/* 00B48 80B113B8 440F4000 */  mfc1    $t7, $f8                   
/* 00B4C 80B113BC 00000000 */  nop
/* 00B50 80B113C0 25F80014 */  addiu   $t8, $t7, 0x0014           ## $t8 = 00000014
/* 00B54 80B113C4 10000003 */  beq     $zero, $zero, .L80B113D4   
/* 00B58 80B113C8 A498020E */  sh      $t8, 0x020E($a0)           ## 0000020E
/* 00B5C 80B113CC A482020C */  sh      $v0, 0x020C($a0)           ## 0000020C
.L80B113D0:
/* 00B60 80B113D0 A488020E */  sh      $t0, 0x020E($a0)           ## 0000020E
.L80B113D4:
/* 00B64 80B113D4 8FBF0014 */  lw      $ra, 0x0014($sp)           
/* 00B68 80B113D8 27BD0018 */  addiu   $sp, $sp, 0x0018           ## $sp = 00000000
/* 00B6C 80B113DC 03E00008 */  jr      $ra                        
/* 00B70 80B113E0 00000000 */  nop

