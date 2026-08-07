// Copyright 2026 QMK
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
#include "keycodes.h"
// clang-format off

#define QMK_PORTUGUESE_MAC_ISO_KEYCODES_VERSION "0.0.1"
#define QMK_PORTUGUESE_MAC_ISO_KEYCODES_VERSION_BCD 0x00000001
#define QMK_PORTUGUESE_MAC_ISO_KEYCODES_VERSION_MAJOR 0
#define QMK_PORTUGUESE_MAC_ISO_KEYCODES_VERSION_MINOR 0
#define QMK_PORTUGUESE_MAC_ISO_KEYCODES_VERSION_PATCH 1

// Aliases
#define PT_SECT KC_GRV  // §
#define PT_1    KC_1    // 1
#define PT_2    KC_2    // 2
#define PT_3    KC_3    // 3
#define PT_4    KC_4    // 4
#define PT_5    KC_5    // 5
#define PT_6    KC_6    // 6
#define PT_7    KC_7    // 7
#define PT_8    KC_8    // 8
#define PT_9    KC_9    // 9
#define PT_0    KC_0    // 0
#define PT_QUOT KC_MINS // '
#define PT_PLUS KC_EQL  // +
#define PT_Q    KC_Q    // Q
#define PT_W    KC_W    // W
#define PT_E    KC_E    // E
#define PT_R    KC_R    // R
#define PT_T    KC_T    // T
#define PT_Y    KC_Y    // Y
#define PT_U    KC_U    // U
#define PT_I    KC_I    // I
#define PT_O    KC_O    // O
#define PT_P    KC_P    // P
#define PT_MORD KC_LBRC // º
#define PT_ACUT KC_RBRC // ´ (dead)
#define PT_A    KC_A    // A
#define PT_S    KC_S    // S
#define PT_D    KC_D    // D
#define PT_F    KC_F    // F
#define PT_G    KC_G    // G
#define PT_H    KC_H    // H
#define PT_J    KC_J    // J
#define PT_K    KC_K    // K
#define PT_L    KC_L    // L
#define PT_CCED KC_SCLN // Ç
#define PT_TILD KC_QUOT // ~ (dead)
#define PT_BSLS KC_NUHS // (backslash)
#define PT_LABK KC_NUBS // <
#define PT_Z    KC_Z    // Z
#define PT_X    KC_X    // X
#define PT_C    KC_C    // C
#define PT_V    KC_V    // V
#define PT_B    KC_B    // B
#define PT_N    KC_N    // N
#define PT_M    KC_M    // M
#define PT_COMM KC_COMM // ,
#define PT_DOT  KC_DOT  // .
#define PT_MINS KC_SLSH // -
#define PT_PLMN S(PT_SECT) // ±
#define PT_EXLM S(PT_1)    // !
#define PT_DQUO S(PT_2)    // "
#define PT_HASH S(PT_3)    // #
#define PT_DLR  S(PT_4)    // $
#define PT_PERC S(PT_5)    // %
#define PT_AMPR S(PT_6)    // &
#define PT_SLSH S(PT_7)    // /
#define PT_LPRN S(PT_8)    // (
#define PT_RPRN S(PT_9)    // )
#define PT_EQL  S(PT_0)    // =
#define PT_QUES S(PT_QUOT) // ?
#define PT_ASTR S(PT_PLUS) // *
#define PT_FORD S(PT_MORD) // ª
#define PT_GRV  S(PT_ACUT) // ` (dead)
#define PT_CIRC S(PT_TILD) // ^ (dead)
#define PT_PIPE S(PT_BSLS) // |
#define PT_RABK S(PT_LABK) // >
#define PT_SCLN S(PT_COMM) // ;
#define PT_COLN S(PT_DOT)  // :
#define PT_UNDS S(PT_MINS) // _
#define PT_APPL A(PT_1)    //  (Apple logo)
#define PT_AT   A(PT_2)    // @
#define PT_EURO A(PT_3)    // €
#define PT_PND  A(PT_4)    // £
#define PT_PERM A(PT_5)    // ‰
#define PT_PILC A(PT_6)    // ¶
#define PT_DIV  A(PT_7)    // ÷
#define PT_LBRC A(PT_8)    // [
#define PT_RBRC A(PT_9)    // ]
#define PT_NEQL A(PT_0)    // ≠
#define PT_OE   A(PT_Q)    // Œ
#define PT_NARS A(PT_W)    // ∑
#define PT_AE   A(PT_E)    // Æ
#define PT_REGD A(PT_R)    // ®
#define PT_TM   A(PT_T)    // ™
#define PT_YEN  A(PT_Y)    // ¥
#define PT_DAGG A(PT_U)    // †
#define PT_DLSI A(PT_I)    // ı
#define PT_OSTR A(PT_O)    // Ø
#define PT_PI   A(PT_P)    // π
#define PT_DEG  A(PT_MORD) // °
#define PT_DIAE A(PT_ACUT) // ¨ (dead)
#define PT_ARNG A(PT_A)    // å
#define PT_SS   A(PT_S)    // ß
#define PT_PDIF A(PT_D)    // ∂
#define PT_FHK  A(PT_F)    // ƒ
#define PT_DOTA A(PT_G)    // ˙
#define PT_CARN A(PT_H)    // ˇ
#define PT_MACR A(PT_J)    // ¯
#define PT_DLQU A(PT_K)    // „
#define PT_LSQU A(PT_L)    // ‘
#define PT_CEDL A(PT_CCED) // ¸
#define PT_STIL A(PT_TILD) // ˜ (dead)
#define PT_LSAQ A(PT_BSLS) // ‹
#define PT_LTEQ A(PT_LABK) // ≤
#define PT_OMEG A(PT_Z)    // Ω
#define PT_LDAQ A(PT_X)    // «
#define PT_COPY A(PT_C)    // ©
#define PT_SQRT A(PT_V)    // √
#define PT_INTG A(PT_B)    // ∫
#define PT_NOT  A(PT_N)    // ¬
#define PT_MICR A(PT_M)    // µ
#define PT_LDQU A(PT_COMM) // “
#define PT_ELLP A(PT_DOT)  // …
#define PT_MDSH A(PT_MINS) // —
#define PT_IEXL S(A(PT_1))    // ¡
#define PT_FI   S(A(PT_2))    // ﬁ
#define PT_FL   S(A(PT_3))    // ﬂ
#define PT_CENT S(A(PT_4))    // ¢
#define PT_INFN S(A(PT_5))    // ∞
#define PT_BULT S(A(PT_6))    // •
#define PT_FRSL S(A(PT_7))    // ⁄
#define PT_LCBR S(A(PT_8))    // {
#define PT_RCBR S(A(PT_9))    // }
#define PT_AEQL S(A(PT_0))    // ≈
#define PT_IQUE S(A(PT_QUOT)) // ¿
#define PT_LOZN S(A(PT_PLUS)) // ◊
#define PT_DDAG S(A(PT_U))    // ‡
#define PT_RNGA S(A(PT_I))    // ˚
#define PT_NARP S(A(PT_P))    // ∏
#define PT_DACU S(A(PT_ACUT)) // ˝
#define PT_INCR S(A(PT_D))    // ∆
#define PT_SLQU S(A(PT_K))    // ‚
#define PT_RSQU S(A(PT_L))    // ’
#define PT_OGON S(A(PT_CCED)) // ˛
#define PT_DCIR S(A(PT_TILD)) // ˆ (dead)
#define PT_RSAQ S(A(PT_BSLS)) // ›
#define PT_GTEQ S(A(PT_LABK)) // ≥
#define PT_RDAQ S(A(PT_X))    // »
#define PT_RDQU S(A(PT_COMM)) // ”
#define PT_MDDT S(A(PT_DOT))  // ·
#define PT_NDSH S(A(PT_MINS)) // –

