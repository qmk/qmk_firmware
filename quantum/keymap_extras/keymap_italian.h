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
#define IT_BSLS KC_GRV  // (backslash)
#define IT_1    KC_1    // 1
#define IT_2    KC_2    // 2
#define IT_3    KC_3    // 3
#define IT_4    KC_4    // 4
#define IT_5    KC_5    // 5
#define IT_6    KC_6    // 6
#define IT_7    KC_7    // 7
#define IT_8    KC_8    // 8
#define IT_9    KC_9    // 9
#define IT_0    KC_0    // 0
#define IT_QUOT KC_MINS // '
#define IT_IGRV KC_EQL  // ì
#define IT_Q    KC_Q    // Q
#define IT_W    KC_W    // W
#define IT_E    KC_E    // E
#define IT_R    KC_R    // R
#define IT_T    KC_T    // T
#define IT_Y    KC_Y    // Y
#define IT_U    KC_U    // U
#define IT_I    KC_I    // I
#define IT_O    KC_O    // O
#define IT_P    KC_P    // P
#define IT_EGRV KC_LBRC // è
#define IT_PLUS KC_RBRC // +
#define IT_A    KC_A    // A
#define IT_S    KC_S    // S
#define IT_D    KC_D    // D
#define IT_F    KC_F    // F
#define IT_G    KC_G    // G
#define IT_H    KC_H    // H
#define IT_J    KC_J    // J
#define IT_K    KC_K    // K
#define IT_L    KC_L    // L
#define IT_OGRV KC_SCLN // ò
#define IT_AGRV KC_QUOT // à
#define IT_UGRV KC_NUHS // ù
#define IT_LABK KC_NUBS // <
#define IT_Z    KC_Z    // Z
#define IT_X    KC_X    // X
#define IT_C    KC_C    // C
#define IT_B    KC_B    // B
#define IT_V    KC_V    // V
#define IT_N    KC_N    // N
#define IT_M    KC_M    // M
#define IT_COMM KC_COMM // ,
#define IT_DOT  KC_DOT  // .
#define IT_MINS KC_SLSH // -
#define IT_PIPE S(IT_BSLS) // |
#define IT_EXLM S(IT_1)    // !
#define IT_DQUO S(IT_2)    // "
#define IT_PND  S(IT_3)    // £
#define IT_DLR  S(IT_4)    // $
#define IT_PERC S(IT_5)    // %
#define IT_AMPR S(IT_6)    // &
#define IT_SLSH S(IT_7)    // /
#define IT_LPRN S(IT_8)    // (
#define IT_RPRN S(IT_9)    // )
#define IT_EQL  S(IT_0)    // =
#define IT_QUES S(IT_QUOT) // ?
#define IT_CIRC S(IT_IGRV) // ^
#define IT_EACU S(IT_EGRV) // é
#define IT_ASTR S(IT_PLUS) // *
#define IT_CCED S(IT_OGRV) // ç
#define IT_DEG  S(IT_AGRV) // °
#define IT_SECT S(IT_UGRV) // §
#define IT_RABK S(IT_LABK) // >
#define IT_COLN S(IT_DOT)  // :
#define IT_SCLN S(IT_COMM) // ;
#define IT_UNDS S(IT_MINS) // _
#define IT_EURO ALGR(IT_E)    // €
#define IT_LBRC ALGR(IT_EGRV) // [
#define IT_RBRC ALGR(IT_PLUS) // ]
#define IT_AT   ALGR(IT_OGRV) // @
#define IT_HASH ALGR(IT_AGRV) // #
#define IT_LCBR S(ALGR(IT_EGRV)) // {
#define IT_RCBR S(ALGR(IT_PLUS)) // }

