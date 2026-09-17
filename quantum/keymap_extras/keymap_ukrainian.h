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

#define QMK_UKRAINIAN_KEYCODES_VERSION "0.0.1"
#define QMK_UKRAINIAN_KEYCODES_VERSION_BCD 0x00000001
#define QMK_UKRAINIAN_KEYCODES_VERSION_MAJOR 0
#define QMK_UKRAINIAN_KEYCODES_VERSION_MINOR 0
#define QMK_UKRAINIAN_KEYCODES_VERSION_PATCH 1

// Aliases
#define UA_QUOT KC_GRV  // '
#define UA_1    KC_1    // 1
#define UA_2    KC_2    // 2
#define UA_3    KC_3    // 3
#define UA_4    KC_4    // 4
#define UA_5    KC_5    // 5
#define UA_6    KC_6    // 6
#define UA_7    KC_7    // 7
#define UA_8    KC_8    // 8
#define UA_9    KC_9    // 9
#define UA_0    KC_0    // 0
#define UA_MINS KC_MINS // -
#define UA_EQL  KC_EQL  // =
#define UA_YOT  KC_Q    // Й
#define UA_TSE  KC_W    // Ц
#define UA_U    KC_E    // У
#define UA_KA   KC_R    // К
#define UA_E    KC_T    // Е
#define UA_EN   KC_Y    // Н
#define UA_HE   KC_U    // Г
#define UA_SHA  KC_I    // Ш
#define UA_SHCH KC_O    // Щ
#define UA_ZE   KC_P    // З
#define UA_KHA  KC_LBRC // Х
#define UA_YI   KC_RBRC // Ї
#define UA_BSLS KC_BSLS // (backslash)
#define UA_EF   KC_A    // Ф
#define UA_I    KC_S    // І
#define UA_VE   KC_D    // В
#define UA_A    KC_F    // А
#define UA_PE   KC_G    // П
#define UA_ER   KC_H    // Р
#define UA_O    KC_J    // О
#define UA_EL   KC_K    // Л
#define UA_DE   KC_L    // Д
#define UA_ZHE  KC_SCLN // Ж
#define UA_YE   KC_QUOT // Є
#define UA_YA   KC_Z    // Я
#define UA_CHE  KC_X    // Ч
#define UA_ES   KC_C    // С
#define UA_EM   KC_V    // М
#define UA_Y    KC_B    // И
#define UA_TE   KC_N    // Т
#define UA_SOFT KC_M    // Ь
#define UA_BE   KC_COMM // Б
#define UA_YU   KC_DOT  // Ю
#define UA_DOT  KC_SLSH // .
#define UA_HRYV S(UA_QUOT) // ₴
#define UA_EXLM S(UA_1)    // !
#define UA_DQUO S(UA_2)    // "
#define UA_NUM  S(UA_3)    // №
#define UA_SCLN S(UA_4)    // ;
#define UA_PERC S(UA_5)    // %
#define UA_COLN S(UA_6)    // :
#define UA_QUES S(UA_7)    // ?
#define UA_ASTR S(UA_8)    // *
#define UA_LPRN S(UA_9)    // (
#define UA_RPRN S(UA_0)    // )
#define UA_UNDS S(UA_MINS) // _
#define UA_PLUS S(UA_EQL)  // +
#define UA_SLSH S(UA_BSLS) // /
#define UA_COMM S(UA_DOT)  // ,
#define UA_GE   ALGR(UA_HE)   // ґ

