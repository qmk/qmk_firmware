// Copyright 2026 QMK
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

#define QMK_SPANISH_DVORAK_KEYCODES_VERSION "0.0.1"
#define QMK_SPANISH_DVORAK_KEYCODES_VERSION_BCD 0x00000001
#define QMK_SPANISH_DVORAK_KEYCODES_VERSION_MAJOR 0
#define QMK_SPANISH_DVORAK_KEYCODES_VERSION_MINOR 0
#define QMK_SPANISH_DVORAK_KEYCODES_VERSION_PATCH 1

// Aliases
#define DV_MORD KC_GRV  // º
#define DV_1    KC_1    // 1
#define DV_2    KC_2    // 2
#define DV_3    KC_3    // 3
#define DV_4    KC_4    // 4
#define DV_5    KC_5    // 5
#define DV_6    KC_6    // 6
#define DV_7    KC_7    // 7
#define DV_8    KC_8    // 8
#define DV_9    KC_9    // 9
#define DV_0    KC_0    // 0
#define DV_QUOT KC_MINS // '
#define DV_IEXL KC_EQL  // ¡
#define DV_DOT  KC_Q    // .
#define DV_COMM KC_W    // ,
#define DV_NTIL KC_E    // Ñ
#define DV_P    KC_R    // P
#define DV_Y    KC_T    // Y
#define DV_F    KC_Y    // F
#define DV_G    KC_U    // G
#define DV_C    KC_I    // C
#define DV_H    KC_O    // H
#define DV_L    KC_P    // L
#define DV_GRV  KC_LBRC // ` (dead)
#define DV_PLUS KC_RBRC // +
#define DV_A    KC_A    // A
#define DV_O    KC_S    // O
#define DV_E    KC_D    // E
#define DV_U    KC_F    // U
#define DV_I    KC_G    // I
#define DV_D    KC_H    // D
#define DV_R    KC_J    // R
#define DV_T    KC_K    // T
#define DV_N    KC_L    // N
#define DV_S    KC_SCLN // S
#define DV_ACUT KC_QUOT // ´ (dead)
#define DV_CCED KC_NUHS // Ç
#define DV_LABK KC_NUBS // <
#define DV_MINS KC_Z    // -
#define DV_Q    KC_X    // Q
#define DV_J    KC_C    // J
#define DV_K    KC_V    // K
#define DV_X    KC_B    // X
#define DV_B    KC_N    // B
#define DV_M    KC_M    // M
#define DV_W    KC_COMM // W
#define DV_V    KC_DOT  // V
#define DV_Z    KC_SLSH // Z
#define DV_FORD S(DV_MORD) // ª
#define DV_EXLM S(DV_1)    // !
#define DV_DQUO S(DV_2)    // "
#define DV_BULT S(DV_3)    // ·
#define DV_DLR  S(DV_4)    // $
#define DV_PERC S(DV_5)    // %
#define DV_AMPR S(DV_6)    // &
#define DV_SLSH S(DV_7)    // /
#define DV_LPRN S(DV_8)    // (
#define DV_RPRN S(DV_9)    // )
#define DV_EQL  S(DV_0)    // =
#define DV_QUES S(DV_QUOT) // ?
#define DV_IQUE S(DV_IEXL) // ¿
#define DV_COLN S(DV_DOT)  // :
#define DV_SCLN S(DV_COMM) // ;
#define DV_CIRC S(DV_GRV)  // ^ (dead)
#define DV_ASTR S(DV_PLUS) // *
#define DV_DIAE S(DV_ACUT) // ¨ (dead)
#define DV_RABK S(DV_LABK) // >
#define DV_UNDS S(DV_MINS) // _
#define DV_BSLS ALGR(DV_MORD) // (backslash)
#define DV_PIPE ALGR(DV_1)    // |
#define DV_AT   ALGR(DV_2)    // @
#define DV_HASH ALGR(DV_3)    // #
#define DV_TILD ALGR(DV_4)    // ~
#define DV_EURO ALGR(DV_5)    // €
#define DV_NOT  ALGR(DV_6)    // ¬
#define DV_LBRC ALGR(DV_GRV)  // [
#define DV_RBRC ALGR(DV_PLUS) // ]
#define DV_LCBR ALGR(DV_ACUT) // {
#define DV_RCBR ALGR(DV_CCED) // }

