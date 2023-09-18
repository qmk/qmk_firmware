// Copyright 2023 QMK
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
#define HR_CEDL KC_GRV  // ¸ (dead)
#define HR_1    KC_1    // 1
#define HR_2    KC_2    // 2
#define HR_3    KC_3    // 3
#define HR_4    KC_4    // 4
#define HR_5    KC_5    // 5
#define HR_6    KC_6    // 6
#define HR_7    KC_7    // 7
#define HR_8    KC_8    // 8
#define HR_9    KC_9    // 9
#define HR_0    KC_0    // 0
#define HR_QUOT KC_MINS // '
#define HR_PLUS KC_EQL  // +
#define HR_Q    KC_Q    // Q
#define HR_W    KC_W    // W
#define HR_E    KC_E    // E
#define HR_R    KC_R    // R
#define HR_T    KC_T    // T
#define HR_Z    KC_Y    // Z
#define HR_U    KC_U    // U
#define HR_I    KC_I    // I
#define HR_O    KC_O    // O
#define HR_P    KC_P    // P
#define HR_SCAR KC_LBRC // Š
#define HR_DSTR KC_RBRC // Đ
#define HR_A    KC_A    // A
#define HR_S    KC_S    // S
#define HR_D    KC_D    // D
#define HR_F    KC_F    // F
#define HR_G    KC_G    // G
#define HR_H    KC_H    // H
#define HR_J    KC_J    // J
#define HR_K    KC_K    // K
#define HR_L    KC_L    // L
#define HR_CCAR KC_SCLN // Č
#define HR_CACU KC_QUOT // Ć
#define HR_ZCAR KC_NUHS // Ž
#define HR_LABK KC_NUBS // <
#define HR_Y    KC_Z    // Y
#define HR_X    KC_X    // X
#define HR_C    KC_C    // C
#define HR_V    KC_V    // V
#define HR_B    KC_B    // B
#define HR_N    KC_N    // N
#define HR_M    KC_M    // M
#define HR_COMM KC_COMM // ,
#define HR_DOT  KC_DOT  // .
#define HR_MINS KC_SLSH // -
#define HR_DIAE S(HR_CEDL) // ¨ (dead)
#define HR_EXLM S(HR_1)    // !
#define HR_DQUO S(HR_2)    // "
#define HR_HASH S(HR_3)    // #
#define HR_DLR  S(HR_4)    // $
#define HR_PERC S(HR_5)    // %
#define HR_AMPR S(HR_6)    // &
#define HR_SLSH S(HR_7)    // /
#define HR_LPRN S(HR_8)    // (
#define HR_RPRN S(HR_9)    // )
#define HR_EQL  S(HR_0)    // =
#define HR_QUES S(HR_QUOT) // ?
#define HR_ASTR S(HR_PLUS) // *
#define HR_RABK S(HR_LABK) // >
#define HR_SCLN S(HR_COMM) // ;
#define HR_COLN S(HR_DOT)  // :
#define HR_UNDS S(HR_MINS) // _
#define HR_TILD ALGR(HR_1)    // ~
#define HR_CARN ALGR(HR_2)    // ˇ (dead)
#define HR_CIRC ALGR(HR_3)    // ^ (dead)
#define HR_BREV ALGR(HR_4)    // ˘ (dead)
#define HR_RNGA ALGR(HR_5)    // ° (dead)
#define HR_OGON ALGR(HR_6)    // ˛ (dead)
#define HR_GRV  ALGR(HR_7)    // `
#define HR_DOTA ALGR(HR_8)    // ˙ (dead)
#define HR_ACUT ALGR(HR_9)    // ´ (dead)
#define HR_DACU ALGR(HR_0)    // ˝ (dead)
#define HR_BSLS ALGR(HR_Q)    // (backslash)
#define HR_PIPE ALGR(HR_W)    // |
#define HR_EURO ALGR(HR_E)    // €
#define HR_DIV  ALGR(HR_SCAR) // ÷
#define HR_MUL  ALGR(HR_DSTR) // ×
#define HR_LBRC ALGR(HR_F)    // [
#define HR_RBRC ALGR(HR_G)    // ]
#define HR_LLST ALGR(HR_K)    // ł
#define HR_CLST ALGR(HR_L)    // Ł
#define HR_SS   ALGR(HR_CACU) // ß
#define HR_CURR ALGR(HR_ZCAR) // ¤
#define HR_AT   ALGR(HR_V)    // @
#define HR_LCBR ALGR(HR_B)    // {
#define HR_RCBR ALGR(HR_N)    // }
#define HR_SECT ALGR(HR_M)    // §

