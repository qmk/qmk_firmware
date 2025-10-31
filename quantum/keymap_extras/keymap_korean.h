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

#define QMK_KOREAN_KEYCODES_VERSION "0.0.1"
#define QMK_KOREAN_KEYCODES_VERSION_BCD 0x00000001
#define QMK_KOREAN_KEYCODES_VERSION_MAJOR 0
#define QMK_KOREAN_KEYCODES_VERSION_MINOR 0
#define QMK_KOREAN_KEYCODES_VERSION_PATCH 1

// Aliases
#define KR_GRV  KC_GRV  // `
#define KR_1    KC_1    // 1
#define KR_2    KC_2    // 2
#define KR_3    KC_3    // 3
#define KR_4    KC_4    // 4
#define KR_5    KC_5    // 5
#define KR_6    KC_6    // 6
#define KR_7    KC_7    // 7
#define KR_8    KC_8    // 8
#define KR_9    KC_9    // 9
#define KR_0    KC_0    // 0
#define KR_MINS KC_MINS // -
#define KR_EQL  KC_EQL  // =
#define KR_Q    KC_Q    // Q
#define KR_W    KC_W    // W
#define KR_E    KC_E    // E
#define KR_R    KC_R    // R
#define KR_T    KC_T    // T
#define KR_Y    KC_Y    // Y
#define KR_U    KC_U    // U
#define KR_I    KC_I    // I
#define KR_O    KC_O    // O
#define KR_P    KC_P    // P
#define KR_LBRC KC_LBRC // [
#define KR_RBRC KC_RBRC // ]
#define KR_WON  KC_BSLS // ₩
#define KR_A    KC_A    // A
#define KR_S    KC_S    // S
#define KR_D    KC_D    // D
#define KR_F    KC_F    // F
#define KR_G    KC_G    // G
#define KR_H    KC_H    // H
#define KR_J    KC_J    // J
#define KR_K    KC_K    // K
#define KR_L    KC_L    // L
#define KR_SCLN KC_SCLN // ;
#define KR_QUOT KC_QUOT // '
#define KR_Z    KC_Z    // Z
#define KR_X    KC_X    // X
#define KR_C    KC_C    // C
#define KR_V    KC_V    // V
#define KR_B    KC_B    // B
#define KR_N    KC_N    // N
#define KR_M    KC_M    // M
#define KR_COMM KC_COMM // ,
#define KR_DOT  KC_DOT  // .
#define KR_SLSH KC_SLSH // /
#define KR_HANJ KC_LNG2 // Hanja (한자)
#define KR_HAEN KC_LNG1 // Han ↔ Yeong (한 ↔ 영)
#define KR_TILD S(KR_GRV)  // ~
#define KR_EXLM S(KR_1)    // !
#define KR_AT   S(KR_2)    // @
#define KR_HASH S(KR_3)    // #
#define KR_DLR  S(KR_4)    // $
#define KR_PERC S(KR_5)    // %
#define KR_CIRC S(KR_6)    // ^
#define KR_AMPR S(KR_7)    // &
#define KR_ASTR S(KR_8)    // *
#define KR_LPRN S(KR_9)    // (
#define KR_RPRN S(KR_0)    // )
#define KR_UNDS S(KR_MINS) // _
#define KR_PLUS S(KR_EQL)  // +
#define KR_LCBR S(KR_LBRC) // {
#define KR_RCBR S(KR_RBRC) // }
#define KR_PIPE S(KR_WON)  // |
#define KR_COLN S(KR_SCLN) // :
#define KR_DQUO S(KR_QUOT) // "
#define KR_LABK S(KR_COMM) // <
#define KR_RABK S(KR_DOT)  // >
#define KR_QUES S(KR_SLSH) // ?

