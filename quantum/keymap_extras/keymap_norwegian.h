// Copyright 2024 QMK
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
#define NO_PIPE KC_GRV  // |
#define NO_1    KC_1    // 1
#define NO_2    KC_2    // 2
#define NO_3    KC_3    // 3
#define NO_4    KC_4    // 4
#define NO_5    KC_5    // 5
#define NO_6    KC_6    // 6
#define NO_7    KC_7    // 7
#define NO_8    KC_8    // 8
#define NO_9    KC_9    // 9
#define NO_0    KC_0    // 0
#define NO_PLUS KC_MINS // +
#define NO_BSLS KC_EQL  // (backslash)
#define NO_Q    KC_Q    // Q
#define NO_W    KC_W    // W
#define NO_E    KC_E    // E
#define NO_R    KC_R    // R
#define NO_T    KC_T    // T
#define NO_Y    KC_Y    // Y
#define NO_U    KC_U    // U
#define NO_I    KC_I    // I
#define NO_O    KC_O    // O
#define NO_P    KC_P    // P
#define NO_ARNG KC_LBRC // Å
#define NO_DIAE KC_RBRC // ¨ (dead)
#define NO_A    KC_A    // A
#define NO_S    KC_S    // S
#define NO_D    KC_D    // D
#define NO_F    KC_F    // F
#define NO_G    KC_G    // G
#define NO_H    KC_H    // H
#define NO_J    KC_J    // J
#define NO_K    KC_K    // K
#define NO_L    KC_L    // L
#define NO_OSTR KC_SCLN // Ø
#define NO_AE   KC_QUOT // Æ
#define NO_QUOT KC_NUHS // '
#define NO_LABK KC_NUBS // <
#define NO_Z    KC_Z    // Z
#define NO_X    KC_X    // X
#define NO_C    KC_C    // C
#define NO_V    KC_V    // V
#define NO_B    KC_B    // B
#define NO_N    KC_N    // N
#define NO_M    KC_M    // M
#define NO_COMM KC_COMM // ,
#define NO_DOT  KC_DOT  // .
#define NO_MINS KC_SLSH // -
#define NO_SECT S(NO_PIPE) // §
#define NO_EXLM S(NO_1)    // !
#define NO_DQUO S(NO_2)    // "
#define NO_HASH S(NO_3)    // #
#define NO_CURR S(NO_4)    // ¤
#define NO_PERC S(NO_5)    // %
#define NO_AMPR S(NO_6)    // &
#define NO_SLSH S(NO_7)    // /
#define NO_LPRN S(NO_8)    // (
#define NO_RPRN S(NO_9)    // )
#define NO_EQL  S(NO_0)    // =
#define NO_QUES S(NO_PLUS) // ?
#define NO_GRV  S(NO_BSLS) // ` (dead)
#define NO_CIRC S(NO_DIAE) // ^ (dead)
#define NO_ASTR S(NO_QUOT) // *
#define NO_RABK S(NO_LABK) // >
#define NO_SCLN S(NO_COMM) // ;
#define NO_COLN S(NO_DOT)  // :
#define NO_UNDS S(NO_MINS) // _
#define NO_AT   ALGR(NO_2)    // @
#define NO_PND  ALGR(NO_3)    // £
#define NO_DLR  ALGR(NO_4)    // $
#define NO_EURO ALGR(NO_5)    // €
#define NO_LCBR ALGR(NO_7)    // {
#define NO_LBRC ALGR(NO_8)    // [
#define NO_RBRC ALGR(NO_9)    // ]
#define NO_RCBR ALGR(NO_0)    // }
#define NO_ACUT ALGR(NO_BSLS) // ´ (dead)
#define NO_TILD ALGR(NO_DIAE) // ~ (dead)
#define NO_MICR ALGR(NO_M)    // µ

