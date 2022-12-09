// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
#include "keymap.h"
// clang-format off

// Aliases
#define DE_CIRC KC_GRV  // ^ (dead)
#define DE_1    KC_1    // 1
#define DE_2    KC_2    // 2
#define DE_3    KC_3    // 3
#define DE_4    KC_4    // 4
#define DE_5    KC_5    // 5
#define DE_6    KC_6    // 6
#define DE_7    KC_7    // 7
#define DE_8    KC_8    // 8
#define DE_9    KC_9    // 9
#define DE_0    KC_0    // 0
#define DE_SS   KC_MINS // ß
#define DE_ACUT KC_EQL  // ´ (dead)
#define DE_Q    KC_Q    // Q
#define DE_W    KC_W    // W
#define DE_E    KC_E    // E
#define DE_R    KC_R    // R
#define DE_T    KC_T    // T
#define DE_Z    KC_Y    // Z
#define DE_U    KC_U    // U
#define DE_I    KC_I    // I
#define DE_O    KC_O    // O
#define DE_P    KC_P    // P
#define DE_UDIA KC_LBRC // Ü
#define DE_PLUS KC_RBRC // +
#define DE_A    KC_A    // A
#define DE_S    KC_S    // S
#define DE_D    KC_D    // D
#define DE_F    KC_F    // F
#define DE_G    KC_G    // G
#define DE_H    KC_H    // H
#define DE_J    KC_J    // J
#define DE_K    KC_K    // K
#define DE_L    KC_L    // L
#define DE_ODIA KC_SCLN // Ö
#define DE_ADIA KC_QUOT // Ä
#define DE_HASH KC_NUHS // #
#define DE_LABK KC_NUBS // <
#define DE_Y    KC_Z    // Y
#define DE_X    KC_X    // X
#define DE_C    KC_C    // C
#define DE_V    KC_V    // V
#define DE_B    KC_B    // B
#define DE_N    KC_N    // N
#define DE_M    KC_M    // M
#define DE_COMM KC_COMM // ,
#define DE_DOT  KC_DOT  // .
#define DE_MINS KC_SLSH // -
#define DE_DEG  S(DE_CIRC) // °
#define DE_EXLM S(DE_1)    // !
#define DE_DQUO S(DE_2)    // "
#define DE_SECT S(DE_3)    // §
#define DE_DLR  S(DE_4)    // $
#define DE_PERC S(DE_5)    // %
#define DE_AMPR S(DE_6)    // &
#define DE_SLSH S(DE_7)    // /
#define DE_LPRN S(DE_8)    // (
#define DE_RPRN S(DE_9)    // )
#define DE_EQL  S(DE_0)    // =
#define DE_QUES S(DE_SS)   // ?
#define DE_GRV  S(DE_ACUT) // ` (dead)
#define DE_ASTR S(DE_PLUS) // *
#define DE_QUOT S(DE_HASH) // '
#define DE_RABK S(DE_LABK) // >
#define DE_SCLN S(DE_COMM) // ;
#define DE_COLN S(DE_DOT)  // :
#define DE_UNDS S(DE_MINS) // _
#define DE_DLQU A(DE_CIRC) // „
#define DE_IEXL A(DE_1)    // ¡
#define DE_LDQU A(DE_2)    // “
#define DE_PILC A(DE_3)    // ¶
#define DE_CENT A(DE_4)    // ¢
#define DE_LBRC A(DE_5)    // [
#define DE_RBRC A(DE_6)    // ]
#define DE_PIPE A(DE_7)    // |
#define DE_LCBR A(DE_8)    // {
#define DE_RCBR A(DE_9)    // }
#define DE_NEQL A(DE_0)    // ≠
#define DE_IQUE A(DE_SS)   // ¿
#define DE_LDAQ A(DE_Q)    // «
#define DE_NARS A(DE_W)    // ∑
#define DE_EURO A(DE_E)    // €
#define DE_REGD A(DE_R)    // ®
#define DE_DAGG A(DE_T)    // †
#define DE_OMEG A(DE_Z)    // Ω
#define DE_DIAE A(DE_U)    // ¨ (dead)
#define DE_FRSL A(DE_I)    // ⁄
#define DE_OSTR A(DE_O)    // Ø
#define DE_PI   A(DE_P)    // π
#define DE_BULT A(DE_UDIA) // •
#define DE_PLMN A(DE_PLUS) // ±
#define DE_ARNG A(DE_A)    // Å
#define DE_SLQU A(DE_S)    // ‚
#define DE_PDIF A(DE_D)    // ∂
#define DE_FHK  A(DE_F)    // ƒ
#define DE_COPY A(DE_G)    // ©
#define DE_FORD A(DE_H)    // ª
#define DE_MORD A(DE_J)    // º
#define DE_INCR A(DE_K)    // ∆
#define DE_AT   A(DE_L)    // @
#define DE_OE   A(DE_ODIA) // Œ
#define DE_AE   A(DE_ADIA) // Æ
#define DE_LSQU A(DE_HASH) // ‘
#define DE_LTEQ A(DE_LABK) // ≤
#define DE_YEN  A(DE_Y)    // ¥
#define DE_AEQL A(DE_X)    // ≈
#define DE_CCCE A(DE_C)    // Ç
#define DE_SQRT A(DE_V)    // √
#define DE_INTG A(DE_B)    // ∫
#define DE_TILD A(DE_N)    // ~ (dead)
#define DE_MICR A(DE_M)    // µ
#define DE_INFN A(DE_COMM) // ∞
#define DE_ELLP A(DE_DOT)  // …
#define DE_NDSH A(DE_MINS) // –
#define DE_NOT  S(A(DE_1))    // ¬
#define DE_RDQU S(A(DE_2))    // ”
#define DE_PND  S(A(DE_4))    // £
#define DE_FI   S(A(DE_5))    // ﬁ
#define DE_BSLS S(A(DE_7))    // (backslash)
#define DE_STIL S(A(DE_8))    // ˜
#define DE_MDDT S(A(DE_9))    // ·
#define DE_MACR S(A(DE_0))    // ¯
#define DE_DOTA S(A(DE_SS))   // ˙
#define DE_RNGA S(A(DE_ACUT)) // ˚
#define DE_RDAQ S(A(DE_Q))    // »
#define DE_PERM S(A(DE_E))    // ‰
#define DE_CEDL S(A(DE_R))    // ¸
#define DE_DACU S(A(DE_T))    // ˝
#define DE_CARN S(A(DE_Z))    // ˇ
#define DE_AACU S(A(DE_U))    // Á
#define DE_UCIR S(A(DE_I))    // Û
#define DE_NARP S(A(DE_P))    // ∏
#define DE_APPL S(A(DE_PLUS)) //  (Apple logo)
#define DE_IACU S(A(DE_S))    // Í
#define DE_TM   S(A(DE_D))    // ™
#define DE_IDIA S(A(DE_F))    // Ï
#define DE_IGRV S(A(DE_G))    // Ì
#define DE_OACU S(A(DE_H))    // Ó
#define DE_DLSI S(A(DE_J))    // ı
#define DE_FL   S(A(DE_L))    // ﬂ
#define DE_GTEQ S(A(DE_LABK)) // ≥
#define DE_DDAG S(A(DE_Y))    // ‡
#define DE_UGRV S(A(DE_X))    // Ù
#define DE_LOZN S(A(DE_V))    // ◊
#define DE_LSAQ S(A(DE_B))    // ‹
#define DE_RSAQ S(A(DE_N))    // ›
#define DE_BREV S(A(DE_M))    // ˘
#define DE_OGON S(A(DE_COMM)) // ˛
#define DE_DIV  S(A(DE_DOT))  // ÷
#define DE_MDSH S(A(DE_MINS)) // —
