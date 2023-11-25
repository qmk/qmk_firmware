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
#define LA_PIPE KC_GRV  // |
#define LA_1    KC_1    // 1
#define LA_2    KC_2    // 2
#define LA_3    KC_3    // 3
#define LA_4    KC_4    // 4
#define LA_5    KC_5    // 5
#define LA_6    KC_6    // 6
#define LA_7    KC_7    // 7
#define LA_8    KC_8    // 8
#define LA_9    KC_9    // 9
#define LA_0    KC_0    // 0
#define LA_QUOT KC_MINS // '
#define LA_IQUE KC_EQL  // ¿
#define LA_Q    KC_Q    // Q
#define LA_W    KC_W    // W
#define LA_E    KC_E    // E
#define LA_R    KC_R    // R
#define LA_T    KC_T    // T
#define LA_Y    KC_Y    // Y
#define LA_U    KC_U    // U
#define LA_I    KC_I    // I
#define LA_O    KC_O    // O
#define LA_P    KC_P    // P
#define LA_ACUT KC_LBRC // ´ (dead)
#define LA_PLUS KC_RBRC // +
#define LA_A    KC_A    // A
#define LA_S    KC_S    // S
#define LA_D    KC_D    // D
#define LA_F    KC_F    // F
#define LA_G    KC_G    // G
#define LA_H    KC_H    // H
#define LA_J    KC_J    // J
#define LA_K    KC_K    // K
#define LA_L    KC_L    // L
#define LA_NTIL KC_SCLN // Ñ
#define LA_LCBR KC_QUOT // {
#define LA_RCBR KC_NUHS // }
#define LA_LABK KC_NUBS // <
#define LA_Z    KC_Z    // Z
#define LA_X    KC_X    // X
#define LA_C    KC_C    // C
#define LA_V    KC_V    // V
#define LA_B    KC_B    // B
#define LA_N    KC_N    // N
#define LA_M    KC_M    // M
#define LA_COMM KC_COMM // ,
#define LA_DOT  KC_DOT  // .
#define LA_MINS KC_SLSH // -
#define LA_MORD S(LA_PIPE) // °
#define LA_EXLM S(LA_1)    // !
#define LA_DQUO S(LA_2)    // "
#define LA_NUMB S(LA_3)    // #
#define LA_DLR  S(LA_4)    // $
#define LA_PERC S(LA_5)    // %
#define LA_AMPR S(LA_6)    // &
#define LA_SLSH S(LA_7)    // /
#define LA_LPRN S(LA_8)    // (
#define LA_RPRN S(LA_9)    // )
#define LA_EQL  S(LA_0)    // =
#define LA_QUES S(LA_QUOT) // ?
#define LA_IEXL S(LA_IQUE) // ¡
#define LA_DIAE S(LA_ACUT) // ¨ (dead)
#define LA_ASTR S(LA_PLUS) // *
#define LA_LBRC S(LA_LCBR) // [
#define LA_RBRC S(LA_RCBR) // ]
#define LA_RABK S(LA_LABK) // >
#define LA_SCLN S(LA_COMM) // ;
#define LA_COLN S(LA_DOT)  // :
#define LA_UNDS S(LA_MINS) // _
#define LA_NOT  ALGR(LA_PIPE) // ¬
#define LA_BSLS ALGR(LA_QUOT) // (backslash)
#define LQ_AT   ALGR(LA_Q)    // @
#define LA_EUR  ALGR(LA_E)    // #
#define LA_TILD ALGR(LA_PLUS) // ~
#define LA_CIRC ALGR(LA_LCBR) // ^

