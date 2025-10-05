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

#define QMK_SERBIAN_KEYCODES_VERSION "0.0.1"
#define QMK_SERBIAN_KEYCODES_VERSION_BCD 0x00000001
#define QMK_SERBIAN_KEYCODES_VERSION_MAJOR 0
#define QMK_SERBIAN_KEYCODES_VERSION_MINOR 0
#define QMK_SERBIAN_KEYCODES_VERSION_PATCH 1

// Aliases
#define RS_GRV  KC_GRV  // `
#define RS_1    KC_1    // 1
#define RS_2    KC_2    // 2
#define RS_3    KC_3    // 3
#define RS_4    KC_4    // 4
#define RS_5    KC_5    // 5
#define RS_6    KC_6    // 6
#define RS_7    KC_7    // 7
#define RS_8    KC_8    // 8
#define RS_9    KC_9    // 9
#define RS_0    KC_0    // 0
#define RS_QUOT KC_MINS // ' (dead)
#define RS_PLUS KC_EQL  // +
#define RS_LJE  KC_Q    // Љ
#define RS_NJE  KC_W    // Њ
#define RS_IE   KC_E    // Е
#define RS_ER   KC_R    // Р
#define RS_TE   KC_T    // Т
#define RS_ZE   KC_Y    // З
#define RS_U    KC_U    // У
#define RS_I    KC_I    // И
#define RS_O    KC_O    // О
#define RS_PE   KC_P    // П
#define RS_SHA  KC_LBRC // Ш
#define RS_DJE  KC_RBRC // Ђ
#define RS_A    KC_A    // А
#define RS_ES   KC_S    // С
#define RS_DE   KC_D    // Д
#define RS_EF   KC_F    // Ф
#define RS_GHE  KC_G    // Г
#define RS_HA   KC_H    // Х
#define RS_JE   KC_J    // Ј
#define RS_KA   KC_K    // К
#define RS_EL   KC_L    // Л
#define RS_CHE  KC_SCLN // Ч
#define RS_TSHE KC_QUOT // Ћ
#define RS_ZHE  KC_NUHS // Ж
#define RS_LABK KC_NUBS // <
#define RS_DZE  KC_Z    // Ѕ
#define RS_DZHE KC_X    // Џ
#define RS_TSE  KC_C    // Ц
#define RS_VE   KC_V    // В
#define RS_BE   KC_B    // Б
#define RS_EN   KC_N    // Н
#define RS_EM   KC_M    // М
#define RS_COMM KC_COMM // ,
#define RS_DOT  KC_DOT  // .
#define RS_MINS KC_SLSH // -
#define RS_TILD S(RS_GRV)  // ~
#define RS_EXLM S(RS_1)    // !
#define RS_DQUO S(RS_2)    // "
#define RS_HASH S(RS_3)    // #
#define RS_DLR  S(RS_4)    // $
#define RS_PERC S(RS_5)    // %
#define RS_AMPR S(RS_6)    // &
#define RS_SLSH S(RS_7)    // /
#define RS_LPRN S(RS_8)    // (
#define RS_RPRN S(RS_9)    // )
#define RS_EQL  S(RS_0)    // =
#define RS_QUES S(RS_QUOT) // ?
#define RS_ASTR S(RS_PLUS) // *
#define RS_RABK S(RS_LABK) // >
#define RS_SCLN S(RS_COMM) // ;
#define RS_COLN S(RS_DOT)  // :
#define RS_UNDS S(RS_MINS) // _
#define RS_EURO ALGR(RS_IE)   // €

