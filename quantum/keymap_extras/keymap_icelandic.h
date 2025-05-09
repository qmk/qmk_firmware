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
#define IS_RNGA KC_GRV  // ° (dead)
#define IS_1    KC_1    // 1
#define IS_2    KC_2    // 2
#define IS_3    KC_3    // 3
#define IS_4    KC_4    // 4
#define IS_5    KC_5    // 5
#define IS_6    KC_6    // 6
#define IS_7    KC_7    // 7
#define IS_8    KC_8    // 8
#define IS_9    KC_9    // 9
#define IS_0    KC_0    // 0
#define IS_ODIA KC_MINS // Ö
#define IS_MINS KC_EQL  // -
#define IS_Q    KC_Q    // Q
#define IS_W    KC_W    // W
#define IS_E    KC_E    // E
#define IS_R    KC_R    // R
#define IS_T    KC_T    // T
#define IS_Y    KC_Y    // Y
#define IS_U    KC_U    // U
#define IS_I    KC_I    // I
#define IS_O    KC_O    // O
#define IS_P    KC_P    // P
#define IS_ETH  KC_LBRC // Ð
#define IS_QUOT KC_RBRC // '
#define IS_A    KC_A    // A
#define IS_S    KC_S    // S
#define IS_D    KC_D    // D
#define IS_F    KC_F    // F
#define IS_G    KC_G    // G
#define IS_H    KC_H    // H
#define IS_J    KC_J    // J
#define IS_K    KC_K    // K
#define IS_L    KC_L    // L
#define IS_AE   KC_SCLN // Æ
#define IS_ACUT KC_QUOT // ´ (dead)
#define IS_PLUS KC_NUHS // +
#define IS_LABK KC_NUBS // <
#define IS_Z    KC_Z    // Z
#define IS_X    KC_X    // X
#define IS_C    KC_C    // C
#define IS_V    KC_V    // V
#define IS_B    KC_B    // B
#define IS_N    KC_N    // N
#define IS_M    KC_M    // M
#define IS_COMM KC_COMM // ,
#define IS_DOT  KC_DOT  // .
#define IS_THRN KC_SLSH // Þ
#define IS_DIAE S(IS_RNGA) // ¨ (dead)
#define IS_EXLM S(IS_1)    // !
#define IS_DQUO S(IS_2)    // "
#define IS_HASH S(IS_3)    // #
#define IS_DLR  S(IS_4)    // $
#define IS_PERC S(IS_5)    // %
#define IS_AMPR S(IS_6)    // &
#define IS_SLSH S(IS_7)    // /
#define IS_LPRN S(IS_8)    // (
#define IS_RPRN S(IS_9)    // )
#define IS_EQL  S(IS_0)    // =
#define IS_UNDS S(IS_MINS) // _
#define IS_QUES S(IS_QUOT) // ?
#define IS_ASTR S(IS_PLUS) // *
#define IS_RABK S(IS_LABK) // >
#define IS_SCLN S(IS_COMM) // ;
#define IS_COLN S(IS_DOT)  // :
#define IS_DEG  ALGR(IS_RNGA) // °
#define IS_LCBR ALGR(IS_7)    // {
#define IS_LBRC ALGR(IS_8)    // [
#define IS_RBRC ALGR(IS_9)    // ]
#define IS_RCBR ALGR(IS_0)    // }
#define IS_BSLS ALGR(IS_ODIA) // (backslash)
#define IS_AT   ALGR(IS_Q)    // @
#define IS_EURO ALGR(IS_E)    // €
#define IS_TILD ALGR(IS_QUOT) // ~
#define IS_CIRC ALGR(IS_ACUT) // ^ (dead)
#define IS_GRV  ALGR(IS_PLUS) // ` (dead)
#define IS_PIPE ALGR(IS_LABK) // |
#define IS_MICR ALGR(IS_M)    // µ

