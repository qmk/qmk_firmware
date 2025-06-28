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

#define QMK_POLISH_KEYCODES_VERSION "0.0.1"
#define QMK_POLISH_KEYCODES_VERSION_BCD 0x00000001
#define QMK_POLISH_KEYCODES_VERSION_MAJOR 0
#define QMK_POLISH_KEYCODES_VERSION_MINOR 0
#define QMK_POLISH_KEYCODES_VERSION_PATCH 1

// Aliases
#define PL_GRV  KC_GRV  // `
#define PL_1    KC_1    // 1
#define PL_2    KC_2    // 2
#define PL_3    KC_3    // 3
#define PL_4    KC_4    // 4
#define PL_5    KC_5    // 5
#define PL_6    KC_6    // 6
#define PL_7    KC_7    // 7
#define PL_8    KC_8    // 8
#define PL_9    KC_9    // 9
#define PL_0    KC_0    // 0
#define PL_MINS KC_MINS // -
#define PL_EQL  KC_EQL  // =
#define PL_Q    KC_Q    // Q
#define PL_W    KC_W    // W
#define PL_E    KC_E    // E
#define PL_R    KC_R    // R
#define PL_T    KC_T    // T
#define PL_Y    KC_Y    // Y
#define PL_U    KC_U    // U
#define PL_I    KC_I    // I
#define PL_O    KC_O    // O
#define PL_P    KC_P    // P
#define PL_LBRC KC_LBRC // [
#define PL_RBRC KC_RBRC // ]
#define PL_BSLS KC_BSLS // (backslash)
#define PL_A    KC_A    // A
#define PL_S    KC_S    // S
#define PL_D    KC_D    // D
#define PL_F    KC_F    // F
#define PL_G    KC_G    // G
#define PL_H    KC_H    // H
#define PL_J    KC_J    // J
#define PL_K    KC_K    // K
#define PL_L    KC_L    // L
#define PL_SCLN KC_SCLN // ;
#define PL_QUOT KC_QUOT // '
#define PL_Z    KC_Z    // Z
#define PL_X    KC_X    // X
#define PL_C    KC_C    // C
#define PL_V    KC_V    // V
#define PL_B    KC_B    // B
#define PL_N    KC_N    // N
#define PL_M    KC_M    // M
#define PL_COMM KC_COMM // ,
#define PL_DOT  KC_DOT  // .
#define PL_SLSH KC_SLSH // /
#define PL_TILD S(PL_GRV)  // ~
#define PL_EXLM S(PL_1)    // !
#define PL_AT   S(PL_2)    // @
#define PL_HASH S(PL_3)    // #
#define PL_DLR  S(PL_4)    // $
#define PL_PERC S(PL_5)    // %
#define PL_CIRC S(PL_6)    // ^
#define PL_AMPR S(PL_7)    // &
#define PL_ASTR S(PL_8)    // *
#define PL_LPRN S(PL_9)    // (
#define PL_RPRN S(PL_0)    // )
#define PL_UNDS S(PL_MINS) // _
#define PL_PLUS S(PL_EQL)  // +
#define PL_LCBR S(PL_LBRC) // {
#define PL_RCBR S(PL_RBRC) // }
#define PL_PIPE S(PL_BSLS) // |
#define PL_COLN S(PL_SCLN) // :
#define PL_DQUO S(PL_QUOT) // "
#define PL_LABK S(PL_COMM) // <
#define PL_RABK S(PL_DOT)  // >
#define PL_QUES S(PL_SLSH) // ?
#define PL_EOGO ALGR(PL_E)    // Ę
#define PL_EURO ALGR(PL_U)    // €
#define PL_OACU ALGR(PL_O)    // Ó
#define PL_AOGO ALGR(PL_A)    // Ą
#define PL_SACU ALGR(PL_S)    // Ś
#define PL_LSTR ALGR(PL_L)    // Ł
#define PL_ZDOT ALGR(PL_Z)    // Ż
#define PL_ZACU ALGR(PL_X)    // Ź
#define PL_CACU ALGR(PL_C)    // Ć
#define PL_NACU ALGR(PL_N)    // Ń

