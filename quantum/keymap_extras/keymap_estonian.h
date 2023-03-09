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
#define EE_CARN KC_GRV  // ˇ (dead)
#define EE_1    KC_1    // 1
#define EE_2    KC_2    // 2
#define EE_3    KC_3    // 3
#define EE_4    KC_4    // 4
#define EE_5    KC_5    // 5
#define EE_6    KC_6    // 6
#define EE_7    KC_7    // 7
#define EE_8    KC_8    // 8
#define EE_9    KC_9    // 9
#define EE_0    KC_0    // 0
#define EE_PLUS KC_MINS // +
#define EE_ACUT KC_EQL  // ´ (dead)
#define EE_Q    KC_Q    // Q
#define EE_W    KC_W    // W
#define EE_E    KC_E    // E
#define EE_R    KC_R    // R
#define EE_T    KC_T    // T
#define EE_Y    KC_Y    // Y
#define EE_U    KC_U    // U
#define EE_I    KC_I    // I
#define EE_O    KC_O    // O
#define EE_P    KC_P    // P
#define EE_UDIA KC_LBRC // Ü
#define EE_OTIL KC_RBRC // Õ
#define EE_A    KC_A    // A
#define EE_S    KC_S    // S
#define EE_D    KC_D    // D
#define EE_F    KC_F    // F
#define EE_G    KC_G    // G
#define EE_H    KC_H    // H
#define EE_J    KC_J    // J
#define EE_K    KC_K    // K
#define EE_L    KC_L    // L
#define EE_ODIA KC_SCLN // Ö
#define EE_ADIA KC_QUOT // Ä
#define EE_QUOT KC_NUHS // '
#define EE_LABK KC_NUBS // <
#define EE_Z    KC_Z    // Z
#define EE_X    KC_X    // X
#define EE_C    KC_C    // C
#define EE_V    KC_V    // V
#define EE_B    KC_B    // B
#define EE_N    KC_N    // N
#define EE_M    KC_M    // M
#define EE_COMM KC_COMM // ,
#define EE_DOT  KC_DOT  // .
#define EE_MINS KC_SLSH // -
#define EE_TILD S(EE_CARN) // ~ (dead)
#define EE_EXLM S(EE_1)    // !
#define EE_DQUO S(EE_2)    // "
#define EE_HASH S(EE_3)    // #
#define EE_CURR S(EE_4)    // ¤
#define EE_PERC S(EE_5)    // %
#define EE_AMPR S(EE_6)    // &
#define EE_SLSH S(EE_7)    // /
#define EE_LPRN S(EE_8)    // (
#define EE_RPRN S(EE_9)    // )
#define EE_EQL  S(EE_0)    // =
#define EE_QUES S(EE_PLUS) // ?
#define EE_GRV  S(EE_ACUT) // ` (dead)
#define EE_ASTR S(EE_QUOT) // *
#define EE_RABK S(EE_LABK) // >
#define EE_SCLN S(EE_COMM) // ;
#define EE_COLN S(EE_DOT)  // :
#define EE_UNDS S(EE_MINS) // _
#define EE_AT   ALGR(EE_2)    // @
#define EE_PND  ALGR(EE_3)    // £
#define EE_DLR  ALGR(EE_4)    // $
#define EE_EURO ALGR(EE_5)    // €
#define EE_LCBR ALGR(EE_7)    // {
#define EE_LBRC ALGR(EE_8)    // [
#define EE_RBRC ALGR(EE_9)    // ]
#define EE_RCBR ALGR(EE_0)    // }
#define EE_BSLS ALGR(EE_PLUS) // (backslash)
#define EE_SECT ALGR(EE_OTIL) // §
#define EE_SCAR ALGR(EE_S)    // š
#define EE_CIRC ALGR(EE_ADIA) // ^ (dead)
#define EE_HALF ALGR(EE_QUOT) // ½
#define EE_PIPE ALGR(EE_LABK) // |
#define EE_ZCAR ALGR(EE_Z)    // ž

