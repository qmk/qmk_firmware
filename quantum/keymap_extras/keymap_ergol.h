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

#define QMK_ERGOL_KEYCODES_VERSION "0.0.1"
#define QMK_ERGOL_KEYCODES_VERSION_BCD 0x00000001
#define QMK_ERGOL_KEYCODES_VERSION_MAJOR 0
#define QMK_ERGOL_KEYCODES_VERSION_MINOR 0
#define QMK_ERGOL_KEYCODES_VERSION_PATCH 1

// Aliases
#define EL_GRV  KC_GRV  // `
#define EL_1    KC_1    // 1
#define EL_2    KC_2    // 2
#define EL_3    KC_3    // 3
#define EL_4    KC_4    // 4
#define EL_5    KC_5    // 5
#define EL_6    KC_6    // 6
#define EL_7    KC_7    // 7
#define EL_8    KC_8    // 8
#define EL_9    KC_9    // 9
#define EL_0    KC_0    // 0
#define EL_SLSH KC_MINS // /
#define EL_EQL  KC_EQL  // =
#define EL_Q    KC_Q    // Q
#define EL_C    KC_W    // C
#define EL_O    KC_E    // O
#define EL_P    KC_R    // P
#define EL_W    KC_T    // W
#define EL_J    KC_Y    // J
#define EL_M    KC_U    // M
#define EL_D    KC_I    // D
#define EL_1DK  KC_O    // ★ (one dead key)
#define EL_Y    KC_P    // Y
#define EL_LBRC KC_LBRC // [
#define EL_RBRC KC_RBRC // ]
#define EL_A    KC_A    // A
#define EL_S    KC_S    // S
#define EL_E    KC_D    // E
#define EL_N    KC_F    // N
#define EL_F    KC_G    // F
#define EL_L    KC_H    // L
#define EL_R    KC_J    // R
#define EL_T    KC_K    // T
#define EL_I    KC_L    // I
#define EL_U    KC_SCLN // U
#define EL_QUOT KC_QUOT // '
#define EL_BSLS KC_BSLS // (backslash)
#define EL_LABK KC_NUBS // <
#define EL_Z    KC_Z    // Z
#define EL_X    KC_X    // X
#define EL_MINS KC_C    // -
#define EL_V    KC_V    // V
#define EL_B    KC_B    // B
#define EL_DOT  KC_N    // .
#define EL_H    KC_M    // H
#define EL_G    KC_COMM // G
#define EL_COMM KC_DOT  // ,
#define EL_K    KC_SLSH // K
#define EL_TILD S(EL_GRV)  // ~
#define EL_EURO S(EL_1)    // €
#define EL_LDAQ S(EL_2)    // «
#define EL_RDAQ S(EL_3)    // »
#define EL_DLR  S(EL_4)    // $
#define EL_PERC S(EL_5)    // %
#define EL_CIRC S(EL_6)    // ^
#define EL_AMPR S(EL_7)    // &
#define EL_ASTR S(EL_8)    // *
#define EL_HASH S(EL_9)    // #
#define EL_AT   S(EL_0)    // @
#define EL_UNDS S(EL_SLSH) // _
#define EL_PLUS S(EL_EQL)  // +
#define EL_EXLM S(EL_1DK)  // !
#define EL_LCBR S(EL_LBRC) // {
#define EL_RCBR S(EL_RBRC) // }
#define EL_DQUO S(EL_QUOT) // "
#define EL_PIPE S(EL_BSLS) // |
#define EL_RABK S(EL_LABK) // >
#define EL_QUES S(EL_MINS) // ?
#define EL_COLN S(EL_DOT)  // :
#define EL_SCLN S(EL_COMM) // ;
#define EL_NNBS S(KC_SPC)  // (narrow non-breaking space)
#define EL_SUB1 ALGR(EL_1)    // ₁
#define EL_SUB2 ALGR(EL_2)    // ₂
#define EL_SUB3 ALGR(EL_3)    // ₃
#define EL_SUB4 ALGR(EL_4)    // ₄
#define EL_SUB5 ALGR(EL_5)    // ₅
#define EL_SUB6 ALGR(EL_6)    // ₆
#define EL_SUB7 ALGR(EL_7)    // ₇
#define EL_SUB8 ALGR(EL_8)    // ₈
#define EL_SUB9 ALGR(EL_9)    // ₉
#define EL_SUB0 ALGR(EL_0)    // ₀
#define EL_LPRN ALGR(EL_S)    // (
#define EL_RPRN ALGR(EL_E)    // )
#define EL_SUP1 S(ALGR(EL_1))    // ¹
#define EL_SUP2 S(ALGR(EL_2))    // ²
#define EL_SUP3 S(ALGR(EL_3))    // ³
#define EL_SUP4 S(ALGR(EL_4))    // ⁴
#define EL_SUP5 S(ALGR(EL_5))    // ⁵
#define EL_SUP6 S(ALGR(EL_6))    // ⁶
#define EL_SUP7 S(ALGR(EL_7))    // ⁷
#define EL_SUP8 S(ALGR(EL_8))    // ⁸
#define EL_SUP9 S(ALGR(EL_9))    // ⁹
#define EL_SUP0 S(ALGR(EL_0))    // ⁰
#define EL_DCIR S(ALGR(EL_Q))    // ^ (dead)
#define EL_LEQL S(ALGR(EL_C))    // ≤
#define EL_GEQL S(ALGR(EL_O))    // ≥
#define EL_CURR S(ALGR(EL_P))    // ¤ (dead)
#define EL_PERM S(ALGR(EL_W))    // ‰
#define EL_RNGA S(ALGR(EL_J))    // ° (dead)
#define EL_MUL  S(ALGR(EL_D))    // ×
#define EL_ACUT S(ALGR(EL_1DK))  // ´ (dead)
#define EL_DGRV S(ALGR(EL_Y))    // ` (dead)
#define EL_CARN S(ALGR(EL_A))    // ˇ (dead)
#define EL_DOTA S(ALGR(EL_N))    // ˙ (dead)
#define EL_NEQL S(ALGR(EL_F))    // ≠
#define EL_DSLS S(ALGR(EL_L))    // / (dead)
#define EL_PLMN S(ALGR(EL_R))    // ±
#define EL_MACR S(ALGR(EL_T))    // ¯ (dead)
#define EL_DIV  S(ALGR(EL_I))    // ÷
#define EL_DACU S(ALGR(EL_U))    // ” (dead)
#define EL_DTIL S(ALGR(EL_Z))    // ~ (dead)
#define EL_DCMM S(ALGR(EL_X))    // , (dead)
#define EL_OGON S(ALGR(EL_MINS)) // ˛ (dead)
#define EL_NOT  S(ALGR(EL_H))    // ¬
#define EL_CEDL S(ALGR(EL_G))    // ¸ (dead)
#define EL_BREV S(ALGR(EL_K))    // ˘ (dead)
#define EL_NBSP S(ALGR(KC_SPC))  // (non-breaking space)

