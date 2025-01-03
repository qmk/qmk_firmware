// Copyright 2025 QMK
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

// Aliases
#define CZ_PLUS KC_1    // +
#define CZ_ECAR KC_2    // ě
#define CZ_SCAR KC_3    // š
#define CZ_CCAR KC_4    // č
#define CZ_RCAR KC_5    // ř
#define CZ_ZCAR KC_6    // ž
#define CZ_YACU KC_7    // ý
#define CZ_AACU KC_8    // á
#define CZ_IACU KC_9    // í
#define CZ_EACU KC_0    // é
#define CZ_EQL  KC_MINS // =
#define CZ_ACUT KC_EQL  // ' (dead)
#define CZ_Q    KC_Q    // Q
#define CZ_W    KC_W    // W
#define CZ_E    KC_E    // E
#define CZ_R    KC_R    // R
#define CZ_T    KC_T    // T
#define CZ_Z    KC_Y    // Z
#define CZ_U    KC_U    // U
#define CZ_I    KC_I    // I
#define CZ_O    KC_O    // O
#define CZ_P    KC_P    // P
#define CZ_UACU KC_LBRC // ú
#define CZ_RPRN KC_RBRC // )
#define CZ_A    KC_A    // A
#define CZ_S    KC_S    // S
#define CZ_D    KC_D    // D
#define CZ_F    KC_F    // F
#define CZ_G    KC_G    // G
#define CZ_H    KC_H    // H
#define CZ_J    KC_J    // J
#define CZ_K    KC_K    // K
#define CZ_L    KC_L    // L
#define CZ_URNG KC_SCLN // ů
#define CZ_SECT KC_QUOT // §
#define CZ_DIAE KC_NUHS // ¨ (dead)
#define CZ_BSLS KC_NUBS // (backslash)
#define CZ_Y    KC_Z    // Y
#define CZ_X    KC_X    // X
#define CZ_C    KC_C    // C
#define CZ_V    KC_V    // V
#define CZ_B    KC_B    // B
#define CZ_N    KC_N    // N
#define CZ_M    KC_M    // M
#define CZ_COMM KC_COMM // ,
#define CZ_DOT  KC_DOT  // .
#define CZ_MINS KC_SLSH // -
#define CZ_1    S(CZ_PLUS) // 1
#define CZ_2    S(CZ_ECAR) // 2
#define CZ_3    S(CZ_SCAR) // 3
#define CZ_4    S(CZ_CCAR) // 4
#define CZ_5    S(CZ_RCAR) // 5
#define CZ_6    S(CZ_ZCAR) // 6
#define CZ_7    S(CZ_YACU) // 7
#define CZ_8    S(CZ_AACU) // 8
#define CZ_9    S(CZ_IACU) // 9
#define CZ_0    S(CZ_EACU) // 0
#define CZ_PERC S(CZ_EQL)  // %
#define CZ_CARN S(CZ_ACUT) // ˇ (dead)
#define CZ_SLSH S(CZ_UACU) // /
#define CZ_LPRN S(CZ_RPRN) // (
#define CZ_DQUO S(CZ_URNG) // "
#define CZ_EXLM S(CZ_SECT) // !
#define CZ_GRV  S(CZ_DIAE) // `
#define CZ_PIPE S(CZ_BSLS) // |
#define CZ_QUES S(CZ_COMM) // ?
#define CZ_COLN S(CZ_DOT)  // :
#define CZ_UNDS S(CZ_MINS) // _
#define CZ_AT   A(CZ_ECAR) // @
#define CZ_HASH A(CZ_SCAR) // #
#define CZ_DLR  A(CZ_CCAR) // $
#define CZ_TILD A(CZ_RCAR) // ~
#define CZ_CIRC A(CZ_ZCAR) // ^
#define CZ_AMPR A(CZ_YACU) // &
#define CZ_ASTR A(CZ_AACU) // *
#define CZ_LCBR A(CZ_IACU) // {
#define CZ_RCBR A(CZ_EACU) // }
#define CZ_RNGA A(CZ_EQL)  // ° (dead)
#define CZ_DCIR A(CZ_ACUT) // ^ (dead)
#define CZ_LEDT A(CZ_W)    // ė
#define CZ_LEOG A(CZ_E)    // ę
#define CZ_EURO A(CZ_R)    // €
#define CZ_LZDT A(CZ_Z)    // ż
#define CZ_LBRC A(CZ_UACU) // [
#define CZ_RBRC A(CZ_RPRN) // ]
#define CZ_LAOG A(CZ_A)    // ą
#define CZ_SS   A(CZ_S)    // ß
#define CZ_PDIF A(CZ_D)    // ∂
#define CZ_LSQU A(CZ_H)    // ‘
#define CZ_RSQU A(CZ_J)    // ’
#define CZ_LLST A(CZ_L)    // ł
#define CZ_SCLN A(CZ_URNG) // ;
#define CZ_QUOT A(CZ_SECT) // '
#define CZ_SLQU A(CZ_N)    // ‚
#define CZ_LABK A(CZ_COMM) // <
#define CZ_RABK A(CZ_DOT)  // >
#define CZ_NDSH A(CZ_MINS) // –
#define CZ_NOT  S(A(CZ_1))    // ¬
#define CZ_BULT S(A(CZ_2))    // •
#define CZ_NEQL S(A(CZ_3))    // ≠
#define CZ_PND  S(A(CZ_4))    // £
#define CZ_LOZN S(A(CZ_5))    // ◊
#define CZ_DAGG S(A(CZ_6))    // †
#define CZ_PARA S(A(CZ_7))    // ¶
#define CZ_DIV  S(A(CZ_8))    // ÷
#define CZ_LDAQ S(A(CZ_9))    // «
#define CZ_RDAQ S(A(CZ_0))    // »
#define CZ_DCOM S(A(CZ_EQL))  // , (dead)
#define CZ_DHPN S(A(CZ_ACUT)) // - (dead)
#define CZ_CEDT S(A(CZ_W))    // Ė
#define CZ_CEOG S(A(CZ_E))    // Ę
#define CZ_REGD S(A(CZ_R))    // ®
#define CZ_TM   S(A(CZ_T))    // ™
#define CZ_CZDT S(A(CZ_Z))    // Ż
#define CZ_LSAQ S(A(CZ_UACU)) // ‹
#define CZ_RSAQ S(A(CZ_RPRN)) // ›
#define CZ_CAOG S(A(CZ_A))    // Ą
#define CZ_NARS S(A(CZ_S))    // ∑
#define CZ_INCR S(A(CZ_D))    // ∆
#define CZ_LDQU S(A(CZ_H))    // “
#define CZ_RDQU S(A(CZ_J))    // ”
#define CZ_CLST S(A(CZ_L))    // Ł
#define CZ_ELLP S(A(CZ_URNG)) // …
#define CZ_DTIL S(A(CZ_SECT)) // ~ (dead)
#define CZ_DDQT S(A(CZ_DIAE)) // " (dead)
#define CZ_COPY S(A(CZ_C))    // ©
#define CZ_SQRT S(A(CZ_V))    // √
#define CZ_DLQU S(A(CZ_N))    // „
#define CZ_LEQL S(A(CZ_COMM)) // ≤
#define CZ_GEQL S(A(CZ_DOT))  // ≥
#define CZ_MDSH S(A(CZ_MINS)) // —

