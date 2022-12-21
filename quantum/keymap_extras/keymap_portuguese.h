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
#define PT_BSLS KC_GRV  // (backslash)
#define PT_1    KC_1    // 1
#define PT_2    KC_2    // 2
#define PT_3    KC_3    // 3
#define PT_4    KC_4    // 4
#define PT_5    KC_5    // 5
#define PT_6    KC_6    // 6
#define PT_7    KC_7    // 7
#define PT_8    KC_8    // 8
#define PT_9    KC_9    // 9
#define PT_0    KC_0    // 0
#define PT_QUOT KC_MINS // '
#define PT_LDAQ KC_EQL  // «
#define PT_Q    KC_Q    // Q
#define PT_W    KC_W    // W
#define PT_E    KC_E    // E
#define PT_R    KC_R    // R
#define PT_T    KC_T    // T
#define PT_Y    KC_Y    // Y
#define PT_U    KC_U    // U
#define PT_I    KC_I    // I
#define PT_O    KC_O    // O
#define PT_P    KC_P    // P
#define PT_PLUS KC_LBRC // +
#define PT_ACUT KC_RBRC // ´ (dead)
#define PT_A    KC_A    // A
#define PT_S    KC_S    // S
#define PT_D    KC_D    // D
#define PT_F    KC_F    // F
#define PT_G    KC_G    // G
#define PT_H    KC_H    // H
#define PT_J    KC_J    // J
#define PT_K    KC_K    // K
#define PT_L    KC_L    // L
#define PT_CCED KC_SCLN // Ç
#define PT_MORD KC_QUOT // º
#define PT_TILD KC_NUHS // ~ (dead)
#define PT_LABK KC_NUBS // <
#define PT_Z    KC_Z    // Z
#define PT_X    KC_X    // X
#define PT_C    KC_C    // C
#define PT_V    KC_V    // V
#define PT_B    KC_B    // B
#define PT_N    KC_N    // N
#define PT_M    KC_M    // M
#define PT_COMM KC_COMM // ,
#define PT_DOT  KC_DOT  // .
#define PT_MINS KC_SLSH // -
#define PT_PIPE S(PT_BSLS) // |
#define PT_EXLM S(PT_1)    // !
#define PT_DQUO S(PT_2)    // "
#define PT_HASH S(PT_3)    // #
#define PT_DLR  S(PT_4)    // $
#define PT_PERC S(PT_5)    // %
#define PT_AMPR S(PT_6)    // &
#define PT_SLSH S(PT_7)    // /
#define PT_LPRN S(PT_8)    // (
#define PT_RPRN S(PT_9)    // )
#define PT_EQL  S(PT_0)    // =
#define PT_QUES S(PT_QUOT) // ?
#define PT_RDAQ S(PT_LDAQ) // »
#define PT_ASTR S(PT_PLUS) // *
#define PT_GRV  S(PT_ACUT) // ` (dead)
#define PT_FORD S(PT_MORD) // ª
#define PT_CIRC S(PT_TILD) // ^ (dead)
#define PT_RABK S(PT_LABK) // >
#define PT_SCLN S(PT_COMM) // ;
#define PT_COLN S(PT_DOT)  // :
#define PT_UNDS S(PT_MINS) // _
#define PT_AT   ALGR(PT_2)    // @
#define PT_PND  ALGR(PT_3)    // £
#define PT_SECT ALGR(PT_4)    // §
#define PT_LCBR ALGR(PT_7)    // {
#define PT_LBRC ALGR(PT_8)    // [
#define PT_RBRC ALGR(PT_9)    // ]
#define PT_RCBR ALGR(PT_0)    // }
#define PT_DIAE ALGR(PT_PLUS) // ¨ (dead)
#define PT_EURO ALGR(PT_E)    // €
