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
#define SE_SECT KC_GRV  // §
#define SE_1    KC_1    // 1
#define SE_2    KC_2    // 2
#define SE_3    KC_3    // 3
#define SE_4    KC_4    // 4
#define SE_5    KC_5    // 5
#define SE_6    KC_6    // 6
#define SE_7    KC_7    // 7
#define SE_8    KC_8    // 8
#define SE_9    KC_9    // 9
#define SE_0    KC_0    // 0
#define SE_PLUS KC_MINS // +
#define SE_ACUT KC_EQL  // ´ (dead)
#define SE_Q    KC_Q    // Q
#define SE_W    KC_W    // W
#define SE_E    KC_E    // E
#define SE_R    KC_R    // R
#define SE_T    KC_T    // T
#define SE_Y    KC_Y    // Y
#define SE_U    KC_U    // U
#define SE_I    KC_I    // I
#define SE_O    KC_O    // O
#define SE_P    KC_P    // P
#define SE_ARNG KC_LBRC // Å
#define SE_DIAE KC_RBRC // ¨ (dead)
#define SE_A    KC_A    // A
#define SE_S    KC_S    // S
#define SE_D    KC_D    // D
#define SE_F    KC_F    // F
#define SE_G    KC_G    // G
#define SE_H    KC_H    // H
#define SE_J    KC_J    // J
#define SE_K    KC_K    // K
#define SE_L    KC_L    // L
#define SE_ODIA KC_SCLN // Ö
#define SE_ADIA KC_QUOT // Ä
#define SE_QUOT KC_NUHS // '
#define SE_LABK KC_NUBS // <
#define SE_Z    KC_Z    // Z
#define SE_X    KC_X    // X
#define SE_C    KC_C    // C
#define SE_V    KC_V    // V
#define SE_B    KC_B    // B
#define SE_N    KC_N    // N
#define SE_M    KC_M    // M
#define SE_COMM KC_COMM // ,
#define SE_DOT  KC_DOT  // .
#define SE_MINS KC_SLSH // -
#define SE_HALF S(SE_SECT) // ½
#define SE_EXLM S(SE_1)    // !
#define SE_DQUO S(SE_2)    // "
#define SE_HASH S(SE_3)    // #
#define SE_CURR S(SE_4)    // ¤
#define SE_PERC S(SE_5)    // %
#define SE_AMPR S(SE_6)    // &
#define SE_SLSH S(SE_7)    // /
#define SE_LPRN S(SE_8)    // (
#define SE_RPRN S(SE_9)    // )
#define SE_EQL  S(SE_0)    // =
#define SE_QUES S(SE_PLUS) // ?
#define SE_GRV  S(SE_ACUT) // ` (dead)
#define SE_CIRC S(SE_DIAE) // ^ (dead)
#define SE_ASTR S(SE_QUOT) // *
#define SE_RABK S(SE_LABK) // >
#define SE_SCLN S(SE_COMM) // ;
#define SE_COLN S(SE_DOT)  // :
#define SE_UNDS S(SE_MINS) // _
#define SE_AT   ALGR(SE_2)    // @
#define SE_PND  ALGR(SE_3)    // £
#define SE_DLR  ALGR(SE_4)    // $
#define SE_EURO ALGR(SE_5)    // €
#define SE_LCBR ALGR(SE_7)    // {
#define SE_LBRC ALGR(SE_8)    // [
#define SE_RBRC ALGR(SE_9)    // ]
#define SE_RCBR ALGR(SE_0)    // }
#define SE_BSLS ALGR(SE_PLUS) // (backslash)
#define SE_TILD ALGR(SE_DIAE) // ~ (dead)
#define SE_PIPE ALGR(SE_LABK) // |
#define SE_MICR ALGR(SE_M)    // µ
