glabel func_80080728
/* AF78C8 80080728 8C820790 */  lw    $v0, 0x790($a0)
/* AF78CC 8008072C 2406002B */  li    $a2, 43
/* AF78D0 80080730 8443014E */  lh    $v1, 0x14e($v0)
/* AF78D4 80080734 10600011 */  beqz  $v1, .L8008077C
/* AF78D8 80080738 00037080 */   sll   $t6, $v1, 2
.L8008073C:
/* AF78DC 8008073C 008E7821 */  addu  $t7, $a0, $t6
/* AF78E0 80080740 8DE20790 */  lw    $v0, 0x790($t7)
/* AF78E4 80080744 5040000E */  beql  $v0, $zero, .L80080780
/* AF78E8 80080748 00001025 */   move  $v0, $zero
/* AF78EC 8008074C 84580142 */  lh    $t8, 0x142($v0)
/* AF78F0 80080750 54D8000B */  bnel  $a2, $t8, .L80080780
/* AF78F4 80080754 00001025 */   move  $v0, $zero
/* AF78F8 80080758 8C5900A8 */  lw    $t9, 0xa8($v0)
/* AF78FC 8008075C 93280002 */  lbu   $t0, 2($t9)
/* AF7900 80080760 54A80004 */  bnel  $a1, $t0, .L80080774
/* AF7904 80080764 8443014E */   lh    $v1, 0x14e($v0)
/* AF7908 80080768 03E00008 */  jr    $ra
/* AF790C 8008076C 24020001 */   li    $v0, 1
/* AF7910 80080770 8443014E */  lh    $v1, 0x14e($v0)
.L80080774:
/* AF7914 80080774 5460FFF1 */  bnezl $v1, .L8008073C
/* AF7918 80080778 00037080 */   sll   $t6, $v1, 2
.L8008077C:
/* AF791C 8008077C 00001025 */  move  $v0, $zero
.L80080780:
/* AF7920 80080780 03E00008 */  jr    $ra
/* AF7924 80080784 00000000 */   nop   
