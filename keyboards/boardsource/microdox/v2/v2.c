// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "v2.h"

#ifdef RGB_MATRIX_ENABLE
#define xxx NO_LED
led_config_t g_led_config = { {
  //led electrical order
  { 13, 14, 15, 16, 17 },
  { 12, 11, 10, 9,  8},
  { 3,  4,  5,  6,  7 },
  {xxx, xxx, xxx, 2, 1, 0},
  //18-21 left underglow
  { 35, 36, 37, 38, 39 },
  { 34, 33, 32, 31, 30 },
  { 25, 26, 27, 28, 29 },
  { xxx, xxx, xxx, 24, 23, 22}
  //40-44 right underglow
  }, {
  //led idx -> physical position  
  }, {
  //led idx -> flag 
  }
};
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
  return encoder_update_user(index, clockwise);
  if (index == 0) {
    if (clockwise) {
      tap_code_delay(KC_VOLU, 10);
    } else {
      tap_code_delay(KC_VOLD, 10);  
    }
  } else {
    if (clockwise) {
      tap_code(KC_MNXT);
    } else {
      tap_code(KC_MPRV);
    }
  }
}
#endif
