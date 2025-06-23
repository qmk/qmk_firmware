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
#define RU_YO   KC_GRV  // Ё
#define RU_1    KC_1    // 1
#define RU_2    KC_2    // 2
#define RU_3    KC_3    // 3
#define RU_4    KC_4    // 4
#define RU_5    KC_5    // 5
#define RU_6    KC_6    // 6
#define RU_7    KC_7    // 7
#define RU_8    KC_8    // 8
#define RU_9    KC_9    // 9
#define RU_0    KC_0    // 0
#define RU_MINS KC_MINS // -
#define RU_EQL  KC_EQL  // =
#define RU_SHTI KC_Q    // Й
#define RU_TSE  KC_W    // Ц
#define RU_U    KC_E    // У
#define RU_KA   KC_R    // К
#define RU_IE   KC_T    // Е
#define RU_EN   KC_Y    // Н
#define RU_GHE  KC_U    // Г
#define RU_SHA  KC_I    // Ш
#define RU_SHCH KC_O    // Щ
#define RU_ZE   KC_P    // З
#define RU_HA   KC_LBRC // Х
#define RU_HARD KC_RBRC // Ъ
#define RU_BSLS KC_BSLS // (backslash)
#define RU_EF   KC_A    // Ф
#define RU_YERU KC_S    // Ы
#define RU_VE   KC_D    // В
#define RU_A    KC_F    // А
#define RU_PE   KC_G    // П
#define RU_ER   KC_H    // Р
#define RU_O    KC_J    // О
#define RU_EL   KC_K    // Л
#define RU_DE   KC_L    // Д
#define RU_ZHE  KC_SCLN // Ж
#define RU_E    KC_QUOT // Э
#define RU_YA   KC_Z    // Я
#define RU_CHE  KC_X    // Ч
#define RU_ES   KC_C    // С
#define RU_EM   KC_V    // М
#define RU_I    KC_B    // И
#define RU_TE   KC_N    // Т
#define RU_SOFT KC_M    // Ь
#define RU_BE   KC_COMM // Б
#define RU_YU   KC_DOT  // Ю
#define RU_DOT  KC_SLSH // .
#define RU_EXLM S(RU_1)    // !
#define RU_DQUO S(RU_2)    // "
#define RU_NUM  S(RU_3)    // №
#define RU_SCLN S(RU_4)    // ;
#define RU_PERC S(RU_5)    // %
#define RU_COLN S(RU_6)    // :
#define RU_QUES S(RU_7)    // ?
#define RU_ASTR S(RU_8)    // *
#define RU_LPRN S(RU_9)    // (
#define RU_RPRN S(RU_0)    // )
#define RU_UNDS S(RU_MINS) // _
#define RU_PLUS S(RU_EQL)  // +
#define RU_SLSH S(RU_BSLS) // /
#define RU_COMM S(RU_DOT)  // ,
#define RU_RUBL ALGR(RU_8)    // ₽

