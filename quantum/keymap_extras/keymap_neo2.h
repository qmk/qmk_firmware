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

#define QMK_NEO2_KEYCODES_VERSION "0.0.1"
#define QMK_NEO2_KEYCODES_VERSION_BCD 0x00000001
#define QMK_NEO2_KEYCODES_VERSION_MAJOR 0
#define QMK_NEO2_KEYCODES_VERSION_MINOR 0
#define QMK_NEO2_KEYCODES_VERSION_PATCH 1

// Aliases
#define NE_CIRC KC_GRV  // ^ (dead)
#define NE_1    KC_1    // 1
#define NE_2    KC_2    // 2
#define NE_3    KC_3    // 3
#define NE_4    KC_4    // 4
#define NE_5    KC_5    // 5
#define NE_6    KC_6    // 6
#define NE_7    KC_7    // 7
#define NE_8    KC_8    // 8
#define NE_9    KC_9    // 9
#define NE_0    KC_0    // 0
#define NE_MINS KC_MINS // -
#define NE_GRV  KC_EQL  // ` (dead)
#define NE_X    KC_Q    // X
#define NE_V    KC_W    // V
#define NE_L    KC_E    // L
#define NE_C    KC_R    // C
#define NE_W    KC_T    // W
#define NE_K    KC_Y    // K
#define NE_H    KC_U    // H
#define NE_G    KC_I    // G
#define NE_F    KC_O    // F
#define NE_Q    KC_P    // Q
#define NE_SS   KC_LBRC // ß
#define NE_ACUT KC_RBRC // ´ (dead)
#define NE_L3L  KC_CAPS // (layer 3)
#define NE_U    KC_A    // U
#define NE_I    KC_S    // I
#define NE_A    KC_D    // A
#define NE_E    KC_F    // E
#define NE_O    KC_G    // O
#define NE_S    KC_H    // S
#define NE_N    KC_J    // N
#define NE_R    KC_K    // R
#define NE_T    KC_L    // T
#define NE_D    KC_SCLN // D
#define NE_Y    KC_QUOT // Y
#define NE_L3R  KC_NUHS // (layer 3)
#define NE_L4L  KC_NUBS // (layer 4)
#define NE_UDIA KC_Z    // Ü
#define NE_ODIA KC_X    // Ö
#define NE_ADIA KC_C    // Ä
#define NE_P    KC_V    // P
#define NE_Z    KC_B    // Z
#define NE_B    KC_N    // B
#define NE_M    KC_M    // M
#define NE_COMM KC_COMM // ,
#define NE_DOT  KC_DOT  // .
#define NE_J    KC_SLSH // J
#define NE_L4R  KC_ALGR // (layer 4)

