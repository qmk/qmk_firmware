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

#define QMK_UK_KEYCODES_VERSION "0.0.1"
#define QMK_UK_KEYCODES_VERSION_BCD 0x00000001
#define QMK_UK_KEYCODES_VERSION_MAJOR 0
#define QMK_UK_KEYCODES_VERSION_MINOR 0
#define QMK_UK_KEYCODES_VERSION_PATCH 1

// Aliases
#define UK_GRV  KC_GRV  // `
#define UK_1    KC_1    // 1
#define UK_2    KC_2    // 2
#define UK_3    KC_3    // 3
#define UK_4    KC_4    // 4
#define UK_5    KC_5    // 5
#define UK_6    KC_6    // 6
#define UK_7    KC_7    // 7
#define UK_8    KC_8    // 8
#define UK_9    KC_9    // 9
#define UK_0    KC_0    // 0
#define UK_MINS KC_MINS // -
#define UK_EQL  KC_EQL  // =
#define UK_Q    KC_Q    // Q
#define UK_W    KC_W    // W
#define UK_E    KC_E    // E
#define UK_R    KC_R    // R
#define UK_T    KC_T    // T
#define UK_Y    KC_Y    // Y
#define UK_U    KC_U    // U
#define UK_I    KC_I    // I
#define UK_O    KC_O    // O
#define UK_P    KC_P    // P
#define UK_LBRC KC_LBRC // [
#define UK_RBRC KC_RBRC // ]
#define UK_A    KC_A    // A
#define UK_S    KC_S    // S
#define UK_D    KC_D    // D
#define UK_F    KC_F    // F
#define UK_G    KC_G    // G
#define UK_H    KC_H    // H
#define UK_J    KC_J    // J
#define UK_K    KC_K    // K
#define UK_L    KC_L    // L
#define UK_SCLN KC_SCLN // ;
#define UK_QUOT KC_QUOT // '
#define UK_HASH KC_NUHS // #
#define UK_BSLS KC_NUBS // (backslash)
#define UK_Z    KC_Z    // Z
#define UK_X    KC_X    // X
#define UK_C    KC_C    // C
#define UK_V    KC_V    // V
#define UK_B    KC_B    // B
#define UK_N    KC_N    // N
#define UK_M    KC_M    // M
#define UK_COMM KC_COMM // ,
#define UK_DOT  KC_DOT  // .
#define UK_SLSH KC_SLSH // /
#define UK_NOT  S(UK_GRV)  // ¬
#define UK_EXLM S(UK_1)    // !
#define UK_DQUO S(UK_2)    // "
#define UK_PND  S(UK_3)    // £
#define UK_DLR  S(UK_4)    // $
#define UK_PERC S(UK_5)    // %
#define UK_CIRC S(UK_6)    // ^
#define UK_AMPR S(UK_7)    // &
#define UK_ASTR S(UK_8)    // *
#define UK_LPRN S(UK_9)    // (
#define UK_RPRN S(UK_0)    // )
#define UK_UNDS S(UK_MINS) // _
#define UK_PLUS S(UK_EQL)  // +
#define UK_LCBR S(UK_LBRC) // {
#define UK_RCBR S(UK_RBRC) // }
#define UK_COLN S(UK_SCLN) // :
#define UK_AT   S(UK_QUOT) // @
#define UK_TILD S(UK_HASH) // ~
#define UK_PIPE S(UK_BSLS) // |
#define UK_LABK S(UK_COMM) // <
#define UK_RABK S(UK_DOT)  // >
#define UK_QUES S(UK_SLSH) // ?
#define UK_BRKP ALGR(UK_GRV)  // ¦
#define UK_EURO ALGR(UK_4)    // €
#define UK_EACU ALGR(KC_E)    // É
#define UK_UACU ALGR(KC_U)    // Ú
#define UK_IACU ALGR(KC_I)    // Í
#define UK_OACU ALGR(KC_O)    // Ó
#define UK_AACU ALGR(KC_A)    // Á

