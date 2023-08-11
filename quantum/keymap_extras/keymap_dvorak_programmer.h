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
#define DP_DLR  KC_GRV  // $
#define DP_AMPR KC_1    // &
#define DP_LBRC KC_2    // [
#define DP_LCBR KC_3    // {
#define DP_RCBR KC_4    // }
#define DP_LPRN KC_5    // (
#define DP_EQL  KC_6    // =
#define DP_ASTR KC_7    // *
#define DP_RPRN KC_8    // )
#define DP_PLUS KC_9    // +
#define DP_RBRC KC_0    // ]
#define DP_EXLM KC_MINS // !
#define DP_HASH KC_EQL  // #
#define DP_SCLN KC_Q    // ;
#define DP_COMM KC_W    // ,
#define DP_DOT  KC_E    // .
#define DP_P    KC_R    // P
#define DP_Y    KC_T    // Y
#define DP_F    KC_Y    // F
#define DP_G    KC_U    // G
#define DP_C    KC_I    // C
#define DP_R    KC_O    // R
#define DP_L    KC_P    // L
#define DP_SLSH KC_LBRC // /
#define DP_AT   KC_RBRC // @
#define DP_BSLS KC_BSLS // (backslash)
#define DP_A    KC_A    // A
#define DP_O    KC_S    // O
#define DP_E    KC_D    // E
#define DP_U    KC_F    // U
#define DP_I    KC_G    // I
#define DP_D    KC_H    // D
#define DP_H    KC_J    // H
#define DP_T    KC_K    // T
#define DP_N    KC_L    // N
#define DP_S    KC_SCLN // S
#define DP_MINS KC_QUOT // -
#define DP_QUOT KC_Z    // '
#define DP_Q    KC_X    // Q
#define DP_J    KC_C    // J
#define DP_K    KC_V    // K
#define DP_X    KC_B    // X
#define DP_B    KC_N    // B
#define DP_M    KC_M    // M
#define DP_W    KC_COMM // W
#define DP_V    KC_DOT  // V
#define DP_Z    KC_SLSH // Z
#define DP_TILD S(DP_DLR)  // ~
#define DP_PERC S(DP_AMPR) // %
#define DP_7    S(DP_LBRC) // 7
#define DP_5    S(DP_LCBR) // 5
#define DP_3    S(DP_RCBR) // 3
#define DP_1    S(DP_LPRN) // 1
#define DP_9    S(DP_EQL)  // 9
#define DP_0    S(DP_ASTR) // 0
#define DP_2    S(DP_RPRN) // 2
#define DP_4    S(DP_PLUS) // 4
#define DP_6    S(DP_RBRC) // 6
#define DP_8    S(DP_EXLM) // 8
#define DP_GRV  S(DP_HASH) // `
#define DP_COLN S(DP_SCLN) // :
#define DP_LABK S(DP_COMM) // <
#define DP_RABK S(DP_DOT)  // >
#define DP_QUES S(DP_SLSH) // ?
#define DP_CIRC S(DP_AT)   // ^
#define DP_PIPE S(DP_BSLS) // |
#define DP_UNDS S(DP_MINS) // _
#define DP_DQUO S(DP_QUOT) // "

