glabel func_8081009C
/* 0C35C 8081009C 3C050001 */  lui     $a1, 0x0001                ## $a1 = 00010000
/* 0C360 808100A0 34A58000 */  ori     $a1, $a1, 0x8000           ## $a1 = 00018000
/* 0C364 808100A4 00851021 */  addu    $v0, $a0, $a1              
/* 0C368 808100A8 844E4A38 */  lh      $t6, 0x4A38($v0)           ## 00004A38
/* 0C36C 808100AC 000E7840 */  sll     $t7, $t6,  1               
/* 0C370 808100B0 008FC021 */  addu    $t8, $a0, $t7              
/* 0C374 808100B4 03051821 */  addu    $v1, $t8, $a1              
/* 0C378 808100B8 84794A8C */  lh      $t9, 0x4A8C($v1)           ## 00004A8C
/* 0C37C 808100BC 27280019 */  addiu   $t0, $t9, 0x0019           ## $t0 = 00000019
/* 0C380 808100C0 A4684A8C */  sh      $t0, 0x4A8C($v1)           ## 00004A8C
/* 0C384 808100C4 84494A38 */  lh      $t1, 0x4A38($v0)           ## 00004A38
/* 0C388 808100C8 00095040 */  sll     $t2, $t1,  1               
/* 0C38C 808100CC 008A5821 */  addu    $t3, $a0, $t2              
/* 0C390 808100D0 01651821 */  addu    $v1, $t3, $a1              
/* 0C394 808100D4 846C4A7A */  lh      $t4, 0x4A7A($v1)           ## 00004A7A
/* 0C398 808100D8 240B00C8 */  addiu   $t3, $zero, 0x00C8         ## $t3 = 000000C8
/* 0C39C 808100DC 258DFFCE */  addiu   $t5, $t4, 0xFFCE           ## $t5 = FFFFFFCE
/* 0C3A0 808100E0 A46D4A7A */  sh      $t5, 0x4A7A($v1)           ## 00004A7A
/* 0C3A4 808100E4 844E4A38 */  lh      $t6, 0x4A38($v0)           ## 00004A38
/* 0C3A8 808100E8 000E7840 */  sll     $t7, $t6,  1               
/* 0C3AC 808100EC 008FC021 */  addu    $t8, $a0, $t7              
/* 0C3B0 808100F0 03051821 */  addu    $v1, $t8, $a1              
/* 0C3B4 808100F4 84794A7A */  lh      $t9, 0x4A7A($v1)           ## 00004A7A
/* 0C3B8 808100F8 24180008 */  addiu   $t8, $zero, 0x0008         ## $t8 = 00000008
/* 0C3BC 808100FC 5F200003 */  bgtzl   $t9, .L8081010C            
/* 0C3C0 80810100 84484A50 */  lh      $t0, 0x4A50($v0)           ## 00004A50
/* 0C3C4 80810104 A4604A7A */  sh      $zero, 0x4A7A($v1)         ## 00004A7A
/* 0C3C8 80810108 84484A50 */  lh      $t0, 0x4A50($v0)           ## 00004A50
.L8081010C:
/* 0C3CC 8081010C 3C010002 */  lui     $at, 0x0002                ## $at = 00020000
/* 0C3D0 80810110 00240821 */  addu    $at, $at, $a0              
/* 0C3D4 80810114 2509FFFF */  addiu   $t1, $t0, 0xFFFF           ## $t1 = 00000018
/* 0C3D8 80810118 A429CA50 */  sh      $t1, -0x35B0($at)          ## 0001CA50
/* 0C3DC 8081011C 844A4A50 */  lh      $t2, 0x4A50($v0)           ## 00004A50
/* 0C3E0 80810120 5540000F */  bnel    $t2, $zero, .L80810160     
/* 0C3E4 80810124 84494A38 */  lh      $t1, 0x4A38($v0)           ## 00004A38
/* 0C3E8 80810128 844C4A38 */  lh      $t4, 0x4A38($v0)           ## 00004A38
/* 0C3EC 8081012C 3C010002 */  lui     $at, 0x0002                ## $at = 00020000
/* 0C3F0 80810130 00240821 */  addu    $at, $at, $a0              
/* 0C3F4 80810134 000C6840 */  sll     $t5, $t4,  1               
/* 0C3F8 80810138 008D7021 */  addu    $t6, $a0, $t5              
/* 0C3FC 8081013C 01C57821 */  addu    $t7, $t6, $a1              
/* 0C400 80810140 A5EB4A8C */  sh      $t3, 0x4A8C($t7)           ## 00004A8C
/* 0C404 80810144 A438CA50 */  sh      $t8, -0x35B0($at)          ## 0001CA50
/* 0C408 80810148 84594A44 */  lh      $t9, 0x4A44($v0)           ## 00004A44
/* 0C40C 8081014C 3C010002 */  lui     $at, 0x0002                ## $at = 00020000
/* 0C410 80810150 00240821 */  addu    $at, $at, $a0              
/* 0C414 80810154 27280001 */  addiu   $t0, $t9, 0x0001           ## $t0 = 00000001
/* 0C418 80810158 A428CA44 */  sh      $t0, -0x35BC($at)          ## 0001CA44
/* 0C41C 8081015C 84494A38 */  lh      $t1, 0x4A38($v0)           ## 00004A38
.L80810160:
/* 0C420 80810160 00095040 */  sll     $t2, $t1,  1               
/* 0C424 80810164 008A6021 */  addu    $t4, $a0, $t2              
/* 0C428 80810168 01856821 */  addu    $t5, $t4, $a1              
/* 0C42C 8081016C 85A34A8C */  lh      $v1, 0x4A8C($t5)           ## 00004A5A
/* 0C430 80810170 A4434A98 */  sh      $v1, 0x4A98($v0)           ## 00004A98
/* 0C434 80810174 03E00008 */  jr      $ra                        
/* 0C438 80810178 A4434A96 */  sh      $v1, 0x4A96($v0)           ## 00004A96

