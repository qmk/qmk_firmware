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

#define QMK_FINNISH_KEYCODES_VERSION "0.0.1"
#define QMK_FINNISH_KEYCODES_VERSION_BCD 0x00000001
#define QMK_FINNISH_KEYCODES_VERSION_MAJOR 0
#define QMK_FINNISH_KEYCODES_VERSION_MINOR 0
#define QMK_FINNISH_KEYCODES_VERSION_PATCH 1

// Aliases
#define FI_SECT KC_GRV  // §
#define FI_1    KC_1    // 1
#define FI_2    KC_2    // 2
#define FI_3    KC_3    // 3
#define FI_4    KC_4    // 4
#define FI_5    KC_5    // 5
#define FI_6    KC_6    // 6
#define FI_7    KC_7    // 7
#define FI_8    KC_8    // 8
#define FI_9    KC_9    // 9
#define FI_0    KC_0    // 0
#define FI_PLUS KC_MINS // +
#define FI_ACUT KC_EQL  // ´ (dead)
#define FI_Q    KC_Q    // Q
#define FI_W    KC_W    // W
#define FI_E    KC_E    // E
#define FI_R    KC_R    // R
#define FI_T    KC_T    // T
#define FI_Y    KC_Y    // Y
#define FI_U    KC_U    // U
#define FI_I    KC_I    // I
#define FI_O    KC_O    // O
#define FI_P    KC_P    // P
#define FI_ARNG KC_LBRC // Å
#define FI_DIAE KC_RBRC // ¨ (dead)
#define FI_A    KC_A    // A
#define FI_S    KC_S    // S
#define FI_D    KC_D    // D
#define FI_F    KC_F    // F
#define FI_G    KC_G    // G
#define FI_H    KC_H    // H
#define FI_J    KC_J    // J
#define FI_K    KC_K    // K
#define FI_L    KC_L    // L
#define FI_ODIA KC_SCLN // Ö
#define FI_ADIA KC_QUOT // Ä
#define FI_QUOT KC_NUHS // '
#define FI_LABK KC_NUBS // <
#define FI_Z    KC_Z    // Z
#define FI_X    KC_X    // X
#define FI_C    KC_C    // C
#define FI_V    KC_V    // V
#define FI_B    KC_B    // B
#define FI_N    KC_N    // N
#define FI_M    KC_M    // M
#define FI_COMM KC_COMM // ,
#define FI_DOT  KC_DOT  // .
#define FI_MINS KC_SLSH // -
#define FI_HALF S(FI_SECT) // ½
#define FI_EXLM S(FI_1)    // !
#define FI_DQUO S(FI_2)    // "
#define FI_HASH S(FI_3)    // #
#define FI_CURR S(FI_4)    // ¤
#define FI_PERC S(FI_5)    // %
#define FI_AMPR S(FI_6)    // &
#define FI_SLSH S(FI_7)    // /
#define FI_LPRN S(FI_8)    // (
#define FI_RPRN S(FI_9)    // )
#define FI_EQL  S(FI_0)    // =
#define FI_QUES S(FI_PLUS) // ?
#define FI_GRV  S(FI_ACUT) // ` (dead)
#define FI_CIRC S(FI_DIAE) // ^ (dead)
#define FI_ASTR S(FI_QUOT) // *
#define FI_RABK S(FI_LABK) // >
#define FI_SCLN S(FI_COMM) // ;
#define FI_COLN S(FI_DOT)  // :
#define FI_UNDS S(FI_MINS) // _
#define FI_AT   ALGR(FI_2)    // @
#define FI_PND  ALGR(FI_3)    // £
#define FI_DLR  ALGR(FI_4)    // $
#define FI_EURO ALGR(FI_5)    // €
#define FI_LCBR ALGR(FI_7)    // {
#define FI_LBRC ALGR(FI_8)    // [
#define FI_RBRC ALGR(FI_9)    // ]
#define FI_RCBR ALGR(FI_0)    // }
#define FI_BSLS ALGR(FI_PLUS) // (backslash)
#define FI_TILD ALGR(FI_DIAE) // ~ (dead)
#define FI_PIPE ALGR(FI_LABK) // |
#define FI_MICR ALGR(FI_M)    // µ

