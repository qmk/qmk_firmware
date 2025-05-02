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

#define QMK_NORMAN_KEYCODES_VERSION "0.0.1"
#define QMK_NORMAN_KEYCODES_VERSION_BCD 0x00000001
#define QMK_NORMAN_KEYCODES_VERSION_MAJOR 0
#define QMK_NORMAN_KEYCODES_VERSION_MINOR 0
#define QMK_NORMAN_KEYCODES_VERSION_PATCH 1

// Aliases
#define NM_GRV  KC_GRV  // `
#define NM_1    KC_1    // 1
#define NM_2    KC_2    // 2
#define NM_3    KC_3    // 3
#define NM_4    KC_4    // 4
#define NM_5    KC_5    // 5
#define NM_6    KC_6    // 6
#define NM_7    KC_7    // 7
#define NM_8    KC_8    // 8
#define NM_9    KC_9    // 9
#define NM_0    KC_0    // 0
#define NM_MINS KC_MINS // -
#define NM_EQL  KC_EQL  // =
#define NM_Q    KC_Q    // Q
#define NM_W    KC_W    // W
#define NM_D    KC_E    // D
#define NM_F    KC_R    // F
#define NM_K    KC_T    // K
#define NM_J    KC_Y    // J
#define NM_U    KC_U    // U
#define NM_R    KC_I    // R
#define NM_L    KC_O    // L
#define NM_SCLN KC_P    // ;
#define NM_LBRC KC_LBRC // [
#define NM_RBRC KC_RBRC // ]
#define NM_BSLS KC_BSLS // (backslash)
#define NM_A    KC_A    // A
#define NM_S    KC_S    // S
#define NM_E    KC_D    // E
#define NM_T    KC_F    // T
#define NM_G    KC_G    // G
#define NM_Y    KC_H    // Y
#define NM_N    KC_J    // N
#define NM_I    KC_K    // I
#define NM_O    KC_L    // O
#define NM_H    KC_SCLN // H
#define NM_QUOT KC_QUOT // '
#define NM_Z    KC_Z    // Z
#define NM_X    KC_X    // X
#define NM_C    KC_C    // C
#define NM_V    KC_V    // V
#define NM_B    KC_B    // B
#define NM_P    KC_N    // P
#define NM_M    KC_M    // M
#define NM_COMM KC_COMM // ,
#define NM_DOT  KC_DOT  // .
#define NM_SLSH KC_SLSH // /
#define NM_TILD S(NM_GRV)  // ~
#define NM_EXLM S(NM_1)    // !
#define NM_AT   S(NM_2)    // @
#define NM_HASH S(NM_3)    // #
#define NM_DLR  S(NM_4)    // $
#define NM_PERC S(NM_5)    // %
#define NM_CIRC S(NM_6)    // ^
#define NM_AMPR S(NM_7)    // &
#define NM_ASTR S(NM_8)    // *
#define NM_LPRN S(NM_9)    // (
#define NM_RPRN S(NM_0)    // )
#define NM_UNDS S(NM_MINS) // _
#define NM_PLUS S(NM_EQL)  // +
#define NM_COLN S(NM_SCLN) // :
#define NM_LCBR S(NM_LBRC) // {
#define NM_RCBR S(NM_RBRC) // }
#define NM_PIPE S(NM_BSLS) // |
#define NM_DQUO S(NM_QUOT) // "
#define NM_LABK S(NM_COMM) // <
#define NM_RABK S(NM_DOT)  // >
#define NM_QUES S(NM_SLSH) // ?

