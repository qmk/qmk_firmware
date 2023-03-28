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
#include "keymap.h"
// clang-format off

// Aliases
#define RS_SLQU KC_GRV  // ‚ (dead)
#define RS_1    KC_1    // 1
#define RS_2    KC_2    // 2
#define RS_3    KC_3    // 3
#define RS_4    KC_4    // 4
#define RS_5    KC_5    // 5
#define RS_6    KC_6    // 6
#define RS_7    KC_7    // 7
#define RS_8    KC_8    // 8
#define RS_9    KC_9    // 9
#define RS_0    KC_0    // 0
#define RS_QUOT KC_MINS // '
#define RS_PLUS KC_EQL  // +
#define RS_Q    KC_Q    // Q
#define RS_W    KC_W    // W
#define RS_E    KC_E    // E
#define RS_R    KC_R    // R
#define RS_T    KC_T    // T
#define RS_Z    KC_Y    // Z
#define RS_U    KC_U    // U
#define RS_I    KC_I    // I
#define RS_O    KC_O    // O
#define RS_P    KC_P    // P
#define RS_SCAR KC_LBRC // Š
#define RS_DSTR KC_RBRC // Đ
#define RS_A    KC_A    // A
#define RS_S    KC_S    // S
#define RS_D    KC_D    // D
#define RS_F    KC_F    // F
#define RS_G    KC_G    // G
#define RS_H    KC_H    // H
#define RS_J    KC_J    // J
#define RS_K    KC_K    // K
#define RS_L    KC_L    // L
#define RS_CCAR KC_SCLN // Č
#define RS_CACU KC_QUOT // Ć
#define RS_ZCAR KC_NUHS // Ž
#define RS_LABK KC_NUBS // <
#define RS_Y    KC_Z    // Y
#define RS_X    KC_X    // X
#define RS_C    KC_C    // C
#define RS_V    KC_V    // V
#define RS_B    KC_B    // B
#define RS_N    KC_N    // N
#define RS_M    KC_M    // M
#define RS_COMM KC_COMM // ,
#define RS_DOT  KC_DOT  // .
#define RS_MINS KC_SLSH // -
#define RS_TILD S(RS_SLQU) // ~
#define RS_EXLM S(RS_1)    // !
#define RS_DQUO S(RS_2)    // "
#define RS_HASH S(RS_3)    // #
#define RS_DLR  S(RS_4)    // $
#define RS_PERC S(RS_5)    // %
#define RS_AMPR S(RS_6)    // &
#define RS_SLSH S(RS_7)    // /
#define RS_LPRN S(RS_8)    // (
#define RS_RPRN S(RS_9)    // )
#define RS_EQL  S(RS_0)    // =
#define RS_QUES S(RS_QUOT) // ?
#define RS_ASTR S(RS_PLUS) // *
#define RS_RABK S(RS_LABK) // >
#define RS_SCLN S(RS_COMM) // ;
#define RS_COLN S(RS_DOT)  // :
#define RS_UNDS S(RS_MINS) // _
#define RS_CARN ALGR(RS_2)    // ˇ (dead)
#define RS_CIRC ALGR(RS_3)    // ^ (dead)
#define RS_BREV ALGR(RS_4)    // ˘ (dead)
#define RS_RNGA ALGR(RS_5)    // ° (dead)
#define RS_OGON ALGR(RS_6)    // ˛ (dead)
#define RS_GRV  ALGR(RS_7)    // `
#define RS_DOTA ALGR(RS_8)    // ˙ (dead)
#define RS_ACUT ALGR(RS_9)    // ´ (dead)
#define RS_DACU ALGR(RS_0)    // ˝ (dead)
#define RS_DIAE ALGR(RS_QUOT) // ¨ (dead)
#define RS_CEDL ALGR(RS_PLUS) // ¸ (dead)
#define RS_BSLS ALGR(RS_Q)    // (backslash)
#define RS_PIPE ALGR(RS_W)    // |
#define RS_EURO ALGR(RS_E)    // €
#define RS_DIV  ALGR(RS_SCAR) // ÷
#define RS_MUL  ALGR(RS_DSTR) // ×
#define RS_LBRC ALGR(RS_F)    // [
#define RS_RBRC ALGR(RS_G)    // ]
#define RS_LLST ALGR(RS_K)    // ł
#define RS_CLST ALGR(RS_L)    // Ł
#define RS_SS   ALGR(RS_CACU) // ß
#define RS_CURR ALGR(RS_ZCAR) // ¤
#define RS_AT   ALGR(RS_V)    // @
#define RS_LCBR ALGR(RS_B)    // {
#define RS_RCBR ALGR(RS_N)    // }
#define RS_SECT ALGR(RS_M)    // §

