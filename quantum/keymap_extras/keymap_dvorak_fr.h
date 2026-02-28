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

#define QMK_DVORAK_FR_KEYCODES_VERSION "0.0.1"
#define QMK_DVORAK_FR_KEYCODES_VERSION_BCD 0x00000001
#define QMK_DVORAK_FR_KEYCODES_VERSION_MAJOR 0
#define QMK_DVORAK_FR_KEYCODES_VERSION_MINOR 0
#define QMK_DVORAK_FR_KEYCODES_VERSION_PATCH 1

// Aliases
#define DV_LDAQ KC_GRV  // «
#define DV_RDAQ KC_1    // »
#define DV_SLSH KC_2    // /
#define DV_MINS KC_3    // -
#define DV_EGRV KC_4    // è
#define DV_BSLS KC_5    // (backslash)
#define DV_CIRC KC_6    // ^ (dead)
#define DV_LPRN KC_7    // (
#define DV_GRV  KC_8    // ` (dead)
#define DV_RPRN KC_9    // )
#define DV_UNDS KC_0    // _
#define DV_LBRC KC_MINS // [
#define DV_RBRC KC_EQL  // ]
#define DV_COLN KC_Q    // :
#define DV_QUOT KC_W    // '
#define DV_EACU KC_E    // é
#define DV_G    KC_R    // G
#define DV_DOT  KC_T    // .
#define DV_H    KC_Y    // H
#define DV_V    KC_U    // V
#define DV_C    KC_I    // C
#define DV_M    KC_O    // M
#define DV_K    KC_P    // K
#define DV_Z    KC_LBRC // Z
#define DV_DIAE KC_RBRC // ¨ (dead)
#define DV_O    KC_A    // O
#define DV_A    KC_S    // A
#define DV_U    KC_D    // U
#define DV_E    KC_F    // E
#define DV_B    KC_G    // B
#define DV_F    KC_H    // F
#define DV_S    KC_J    // S
#define DV_T    KC_K    // T
#define DV_N    KC_L    // N
#define DV_D    KC_SCLN // D
#define DV_W    KC_QUOT // W
#define DV_TILD KC_NUHS // ~ (dead)
#define DV_AGRV KC_NUBS // à
#define DV_SCLN KC_Z    // ;
#define DV_Q    KC_X    // Q
#define DV_COMM KC_C    // ,
#define DV_I    KC_V    // I
#define DV_Y    KC_B    // Y
#define DV_X    KC_N    // X
#define DV_R    KC_M    // R
#define DV_L    KC_COMM // L
#define DV_P    KC_DOT  // P
#define DV_J    KC_SLSH // J
#define DV_ASTR S(DV_LDAQ) // *
#define DV_1    S(DV_RDAQ) // 1
#define DV_2    S(DV_SLSH) // 2
#define DV_3    S(DV_MINS) // 3
#define DV_4    S(DV_EGRV) // 4
#define DV_5    S(DV_BSLS) // 5
#define DV_6    S(DV_CIRC) // 6
#define DV_7    S(DV_LPRN) // 7
#define DV_8    S(DV_GRV)  // 8
#define DV_9    S(DV_RPRN) // 9
#define DV_0    S(DV_UNDS) // 0
#define DV_PLUS S(DV_LBRC) // +
#define DV_PERC S(DV_RBRC) // %
#define DV_QUES S(DV_COLN) // ?
#define DV_LABK S(DV_QUOT) // <
#define DV_RABK S(DV_EACU) // >
#define DV_EXLM S(DV_DOT)  // !
#define DV_EQL  S(DV_DIAE) // =
#define DV_HASH S(DV_TILD) // #
#define DV_CCED S(DV_AGRV) // ç
#define DV_PIPE S(DV_SCLN) // |
#define DV_AT   S(DV_COMM) // @

