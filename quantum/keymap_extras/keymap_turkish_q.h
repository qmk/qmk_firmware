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
#define TR_DQUO KC_GRV  // "
#define TR_1    KC_1    // 1
#define TR_2    KC_2    // 2
#define TR_3    KC_3    // 3
#define TR_4    KC_4    // 4
#define TR_5    KC_5    // 5
#define TR_6    KC_6    // 6
#define TR_7    KC_7    // 7
#define TR_8    KC_8    // 8
#define TR_9    KC_9    // 9
#define TR_0    KC_0    // 0
#define TR_ASTR KC_MINS // *
#define TR_MINS KC_EQL  // -
#define TR_Q    KC_Q    // Q
#define TR_W    KC_W    // W
#define TR_E    KC_E    // E
#define TR_R    KC_R    // R
#define TR_T    KC_T    // T
#define TR_Y    KC_Y    // Y
#define TR_U    KC_U    // U
#define TR_I    KC_I    // I
#define TR_O    KC_O    // O
#define TR_P    KC_P    // P
#define TR_GBRV KC_LBRC // Ğ
#define TR_UDIA KC_RBRC // Ü
#define TR_A    KC_A    // A
#define TR_S    KC_S    // S
#define TR_D    KC_D    // D
#define TR_F    KC_F    // F
#define TR_G    KC_G    // G
#define TR_H    KC_H    // H
#define TR_J    KC_J    // J
#define TR_K    KC_K    // K
#define TR_L    KC_L    // L
#define TR_SCED KC_SCLN // Ş
#define TR_IDOT KC_QUOT // İ
#define TR_COMM KC_NUHS // ,
#define TR_LABK KC_NUBS // <
#define TR_Z    KC_Z    // Z
#define TR_X    KC_X    // X
#define TR_C    KC_C    // C
#define TR_V    KC_V    // V
#define TR_B    KC_B    // B
#define TR_N    KC_N    // N
#define TR_M    KC_M    // M
#define TR_ODIA KC_COMM // Ö
#define TR_CCED KC_DOT  // Ç
#define TR_DOT  KC_SLSH // .
#define TR_EACU S(TR_DQUO) // é
#define TR_EXLM S(TR_1)    // !
#define TR_QUOT S(TR_2)    // '
#define TR_CIRC S(TR_3)    // ^ (dead)
#define TR_PLUS S(TR_4)    // +
#define TR_PERC S(TR_5)    // %
#define TR_AMPR S(TR_6)    // &
#define TR_SLSH S(TR_7)    // /
#define TR_LPRN S(TR_8)    // (
#define TR_RPRN S(TR_9)    // )
#define TR_EQL  S(TR_0)    // =
#define TR_QUES S(TR_ASTR) // ?
#define TR_UNDS S(TR_MINS) // _
#define TR_SCLN S(TR_COMM) // ;
#define TR_RABK S(TR_LABK) // >
#define TR_COLN S(TR_DOT)  // :
#define TR_PND  ALGR(TR_2)    // £
#define TR_HASH ALGR(TR_3)    // #
#define TR_DLR  ALGR(TR_4)    // $
#define TR_HALF ALGR(TR_5)    // ½
#define TR_LCBR ALGR(TR_7)    // {
#define TR_LBRC ALGR(TR_8)    // [
#define TR_RBRC ALGR(TR_9)    // ]
#define TR_RCBR ALGR(TR_0)    // }
#define TR_BSLS ALGR(TR_ASTR) // (backslash)
#define TR_PIPE ALGR(TR_MINS) // |
#define TR_AT   ALGR(TR_Q)    // @
#define TR_EURO ALGR(TR_E)    // €
#define TR_LIRA ALGR(TR_T)    // ₺
#define TR_DIAE ALGR(TR_GBRV) // ¨ (dead)
#define TR_TILD ALGR(TR_UDIA) // ~ (dead)
#define TR_AE   ALGR(TR_A)    // Æ
#define TR_SS   ALGR(TR_S)    // ß
#define TR_ACUT ALGR(TR_SCED) // ´ (dead)
#define TR_GRV  ALGR(TR_COMM) // ` (dead)

