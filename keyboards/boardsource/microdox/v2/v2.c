// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "v2.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { 
  {
    { 13, 14, 15, 16, 17 },
    { 12, 11, 10, 9,  8  },
    { 3,  4,  5,  6,  7  },
    { NO_LED, NO_LED, 2, 1, 0 },
    //18-21 left underglow
    { 35, 36, 37, 38, 39 },
    { 34, 33, 32, 31, 30 },
    { 25, 26, 27, 28, 29 },
    { NO_LED, NO_LED, 24, 23, 22 }
    //40-44 right underglow
  }, {
    {99,64}, {74,64}, {49,64}, //0-2
    {0,42},  {24,42}, {49,42}, {74,42}, {99,42}, //3-7
    {99,21}, {74,21}, {49,21}, {24,21}, {0,21}, //8-12
    {0,0},   {24,0},  {49,0},  {74,0},  {99,0}, //13-17
    {12,11}, {86,11}, {86,53}, {0,64}, //18-21
    {124,64}, {149,64}, {174,64}, //22-24
    {224,42}, {199,42}, {174,42}, {149,42}, {124,42}, //25-29
    {124,21}, {149,21}, {174,21}, {199,21}, {224,21}, //30-34
    {224,0},  {199,0},  {174,0},  {149,0},  {124,0}, //35-39
    {211,11}, {136,11}, {136,53}, {224,64} //40-44
  }, {
    1, 1, 1,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    2, 2, 2, 2,
    1, 1, 1,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    2, 2, 2, 2
  }
};
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
  if (!encoder_update_user(index, clockwise)) { return false; }
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
  return false;
}
#endif
