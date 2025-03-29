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
#define EG_GRV  KC_GRV  // $
#define EG_1    KC_1    // 1
#define EG_2    KC_2    // 2
#define EG_3    KC_3    // 3
#define EG_4    KC_4    // 4
#define EG_5    KC_5    // 5
#define EG_6    KC_6    // 6
#define EG_7    KC_7    // 7
#define EG_8    KC_8    // 8
#define EG_9    KC_9    // 9
#define EG_0    KC_0    // 0
#define EG_SLSH KC_MINS // /
#define EG_EQL  KC_EQL  // =
#define EG_Q    KC_Q    // Q
#define EG_C    KC_W    // C
#define EG_O    KC_E    // O
#define EG_P    KC_R    // P
#define EG_W    KC_T    // W
#define EG_J    KC_Y    // J
#define EG_M    KC_U    // M
#define EG_D    KC_I    // D
#define EG_1DK  KC_O    // One Dead Key
#define EG_Y    KC_P    // Y
#define EG_LBRC KC_LBRC // [
#define EG_RBRC KC_RBRC // ]
#define EG_A    KC_A    // A
#define EG_S    KC_S    // S
#define EG_E    KC_D    // E
#define EG_N    KC_F    // N
#define EG_F    KC_G    // F
#define EG_L    KC_H    // L
#define EG_R    KC_J    // R
#define EG_T    KC_K    // T
#define EG_I    KC_L    // I
#define EG_U    KC_SCLN // U
#define EG_QUOT KC_QUOT // '
#define EG_BSLS KC_BSLS // (backslash)
#define EG_LABK KC_NUBS // <
#define EG_Z    KC_Z    // Z
#define EG_X    KC_X    // X
#define EG_MINS KC_C    // -
#define EG_V    KC_V    // V
#define EG_B    KC_B    // B
#define EG_DOT  KC_N    // .
#define EG_H    KC_M    // H
#define EG_G    KC_COMM // G
#define EG_COMM KC_DOT  // ,
#define EG_K    KC_SLSH // K
#define EG_TILD S(EG_GRV)  // ~
#define EG_EURO S(EG_1)    // €
#define EG_LDAQ S(EG_2)    // «
#define EG_RDAQ S(EG_3)    // »
#define EG_DLR  S(EG_4)    // $
#define EG_PERC S(EG_5)    // %
#define EG_CIRC S(EG_6)    // ^
#define EG_AMPR S(EG_7)    // &
#define EG_ASTR S(EG_8)    // *
#define EG_HASH S(EG_9)    // #
#define EG_AT   S(EG_0)    // @
#define EG_UNDS S(EG_SLSH) // _
#define EG_PLUS S(EG_EQL)  // +
#define EG_EXLM S(EG_1DK)  // !
#define EG_LCBR S(EG_LBRC) // {
#define EG_RCBR S(EG_RBRC) // }
#define EG_DQUO S(EG_QUOT) // "
#define EG_PIPE S(EG_BSLS) // |
#define EG_RABK S(EG_LABK) // >
#define EG_COLN S(EG_DOT)  // :
#define EG_SCLN S(EG_COMM) // ;
#define EG_NNBS S(KC_SPC)  // (narrow non-breaking space)
#define EG_SUB_1 ALGR(EG_1)    // ₁
#define EG_SUB_2 ALGR(EG_2)    // ₂
#define EG_SUB_3 ALGR(EG_3)    // ₃
#define EG_SUB_4 ALGR(EG_4)    // ₄
#define EG_SUB_5 ALGR(EG_5)    // ₅
#define EG_SUB_6 ALGR(EG_6)    // ₆
#define EG_SUB_7 ALGR(EG_7)    // ₇
#define EG_SUB_8 ALGR(EG_8)    // ₈
#define EG_SUB_9 ALGR(EG_9)    // ₉
#define EG_SUB_0 ALGR(EG_0)    // ₀
#define EG_LPRN ALGR(EG_S)    // (
#define EG_RPRN ALGR(EG_E)    // )
#define EG_SUP_1 S(ALGR(EG_1))    // ¹
#define EG_SUP_2 S(ALGR(EG_2))    // ²
#define EG_SUP_3 S(ALGR(EG_3))    // ³
#define EG_SUP_4 S(ALGR(EG_4))    // ⁴
#define EG_SUP_5 S(ALGR(EG_5))    // ⁵
#define EG_SUP_6 S(ALGR(EG_6))    // ⁶
#define EG_SUP_7 S(ALGR(EG_7))    // ⁷
#define EG_SUP_8 S(ALGR(EG_8))    // ⁸
#define EG_SUP_9 S(ALGR(EG_9))    // ⁹
#define EG_SUP_0 S(ALGR(EG_0))    // ⁰
#define EG_DCIR S(ALGR(EG_Q))    // ^ (dead)
#define EG_LEQL S(ALGR(EG_C))    // ≤
#define EG_GEQL S(ALGR(EG_O))    // ≥
#define EG_CURR S(ALGR(EG_P))    // ¤ (dead)
#define EG_PERM S(ALGR(EG_W))    // ‰
#define EG_RNGA S(ALGR(EG_J))    // ° (dead)
#define EG_MUL  S(ALGR(EG_D))    // ×
#define EG_ACUT S(ALGR(EG_1DK))  // ´ (dead)
#define EG_DGRV S(ALGR(EG_Y))    // ` (dead)
#define EG_CARN S(ALGR(EG_A))    // ˇ (dead)
#define EG_DOTA S(ALGR(EG_N))    // ˙ (dead)
#define EG_NEQL S(ALGR(EG_F))    // ≠
#define EG_DSLS S(ALGR(EG_L))    // / (dead)
#define EG_PLMN S(ALGR(EG_R))    // ±
#define EG_MACR S(ALGR(EG_T))    // ¯ (dead)
#define EG_DIV  S(ALGR(EG_I))    // ÷
#define EG_DACU S(ALGR(EG_U))    // ˝ (dead)
#define EG_DTIL S(ALGR(EG_Z))    // ~ (dead)
#define EG_DCMM S(ALGR(EG_X))    // , (dead)
#define EG_OGON S(ALGR(EG_MINS)) // ˛ (dead)
#define EG_NDSH S(ALGR(EG_V))    // – (en-dash)
#define EG_BRKP S(ALGR(EG_DOT))  // ¦
#define EG_NOT  S(ALGR(EG_H))    // ¬
#define EG_CEDL S(ALGR(EG_G))    // ¸ (dead)
#define EG_BREV S(ALGR(EG_K))    // ˘ (dead)
#define EG_NBSP S(ALGR(KC_SPC))  // (non-breaking space)

