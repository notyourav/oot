.include "macro.inc"

 # assembler directives
 .set noat      # allow manual use of $at
 .set noreorder # don't insert nops after branches
 .set gp=64     # allow use of 64-bit general purposee registers

.section .data

glabel D_80B4A090
 .word 0x455E8000, 0x42C80000, 0xC4BDA000, 0x45462000, 0x42C80000, 0xC4DCE000, 0x4545D000, 0x42C80000, 0xC50A9000, 0x455EB000, 0x42C80000, 0xC5185000, 0x4576A000, 0x42C80000, 0xC50A9000, 0x45766000, 0x42C80000, 0xC4DCA000, 0x4532D000, 0x42C80000, 0xC515A000, 0x452D8000, 0x42C80000, 0xC4F86000, 0x458D7800, 0x4404C000, 0xC48F4000, 0x458AD000, 0x4404C000, 0xC4AFA000, 0x45825000, 0x4404C000, 0xC4AE6000, 0x457BE000, 0x4404C000, 0xC4914000, 0x457AA000, 0x4404C000, 0xC45CC000, 0x45857000, 0x4404C000, 0xC44A8000, 0x458D4000, 0x4404C000, 0xC45C0000, 0x45852000, 0x4404C000, 0xC4816000, 0x4594A800, 0x4404C000, 0xC48F4000, 0x4570A000, 0x4404C000, 0xC45CC000, 0x4588E000, 0x4404C000, 0xC42C8000, 0x45832800, 0x4404C000, 0xC4218000, 0x457E6000, 0x4404C000, 0xC4C4E000, 0x4575A000, 0x4404C000, 0xC4D52000, 0x456C4000, 0x4404C000, 0xC4E56000, 0x455E8000, 0x4404C000, 0xC4F82000
glabel D_80B4A1B0
 .word 0x00000000
glabel D_80B4A1B4
 .word 0x00010000
glabel En_Zf_InitVars
 .word 0x00250500, 0x00000015, 0x001B0000, 0x00000568
.word EnZf_Init
.word EnZf_Destroy
.word EnZf_Update
.word EnZf_Draw
glabel D_80B4A1D8
 .word 0x00000909, 0x10010000, 0x01000000, 0x00000000, 0x00000000, 0xFFCFFFFF, 0x00000000, 0x00010100, 0x00140046, 0x00000000, 0x00000000
glabel D_80B4A204
 .word 0x0A110D00, 0x00030000, 0x00000000, 0xFFCFFFFF, 0x00080000, 0x00000000, 0x00000000, 0x81010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
glabel D_80B4A254
 .word 0x1002D102, 0x10020210, 0x010204D2, 0xF4D2D2D2, 0xD260F360, 0x00000104, 0x02020804, 0x00000400
glabel D_80B4A274
 .word 0xB04C07D0, 0xC850000F, 0x386CF254
glabel D_80B4A280
 .word 0x0601081C, 0x06010CAC, 0x06011070, 0x44898000, 0xC42F0000, 0x00000000
glabel D_80B4A298
 .word 0x43960000, 0x00000000, 0x00000000
glabel D_80B4A2A4
 .word 0x43960000, 0xC4D48000, 0x00000000
glabel D_80B4A2B0
 .word 0xC4160000, 0x43960000, 0x00000000
glabel D_80B4A2BC
 .word 0x00000000, 0x44BB8000, 0x00000000
glabel D_80B4A2C8
 .word 0xC4160000, 0xC53B8000, 0x447A0000
glabel D_80B4A2D4
 .word 0xC4160000, 0xC53B8000, 0xC47A0000
glabel D_80B4A2E0
 .word 0x44BB8000, 0xC53B8000, 0x00000000
glabel D_80B4A2EC
 .word 0x00000000, 0x00000000, 0x00000000
glabel D_80B4A2F8
 .word 0xD7000002, 0x0A000A00, 0xDF000000, 0x00000000, 0x00000000, 0x00000000
