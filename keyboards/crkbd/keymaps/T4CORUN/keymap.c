/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "T4CORUN.h"

#define LAYOUT_split_3x6_3_wrapper(...)      LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_split_3x6_3_base(                            \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A,       \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A,       \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A        \
  ) \
  LAYOUT_split_3x6_3_wrapper( \
    ___x___, K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     K0A,     ___x___,   \
    ___x___, K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A,     ___x___,   \
    ___x___, K21,     K22,     K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A,     ___x___,   \
                               _________BASE_L4_________, _________BASE_R4_________                               \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_split_3x6_3_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Review $qmkroot\users\T4CORUN\wrappers.h for definitions
  [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
    ________________COLEMAKDH_L1_______________, ________________COLEMAKDH_R1_______________,
    ________________COLEMAKDH_L2_______________, ________________COLEMAKDH_R2_______________,
    ________________COLEMAKDH_L3_______________, ________________COLEMAKDH_R3_______________
  ),

  [_NUMBER] = LAYOUT_split_3x6_3_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________NUMPAD_L1_________________, _________________NUMPAD_R1_________________, ___x___,
    ___x___, _________________NUMPAD_L2_________________, _________________NUMPAD_R2_________________, ___x___,
    ___x___, _________________NUMPAD_L3_________________, _________________NUMPAD_R3_________________, ___x___,
                               ________NUMPAD_L4________, ________NUMPAD_R4________
  ),

  [_NAVIGATION] = LAYOUT_split_3x6_3_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, ___________________NAV_L1__________________, ___________________NAV_R1__________________, ___x___,
    ___x___, ___________________NAV_L2__________________, ___________________NAV_R2__________________, ___x___,
    ___x___, ___________________NAV_L3__________________, ___________________NAV_R3__________________, ___x___,
                               __________NAV_L4_________, __________NAV_R4_________
  ),

  [_FUNCTION] = LAYOUT_split_3x6_3_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________FUNCPAD_L1________________, _________________FUNCPAD_R1________________, ___x___,
    ___x___, _________________FUNCPAD_L2________________, _________________FUNCPAD_R2________________, ___x___,
    ___x___, _________________FUNCPAD_L3________________, _________________FUNCPAD_R3________________, ___x___,
                               ________FUNCPAD_L4_______, ________FUNCPAD_R4_______
  ),

  [_MOUSE] = LAYOUT_split_3x6_3_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, ________________MOUSEKEY_L1________________, ________________MOUSEKEY_R1________________, ___x___,
    ___x___, ________________MOUSEKEY_L2________________, ________________MOUSEKEY_R2________________, ___x___,
    ___x___, ________________MOUSEKEY_L3________________, ________________MOUSEKEY_R3________________, ___x___,
                               _______MOUSEKEY_L4_______, _______MOUSEKEY_R4_______ 
  ),

  [_ADJUST] = LAYOUT_split_3x6_3_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, ___x___,
    ___x___, _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, ___x___,
    ___x___, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, ___x___,
                               ________ADJUST_L4________, ________ADJUST_R4________
  )
};

void suspend_wakeup_init_user(void) {
  #ifdef OLED_ENABLE
    oled_on();
  #endif
  
  #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
  #endif
}

void suspend_power_down_user(void) {
  #ifdef OLED_ENABLE
    oled_off();
  #endif

  #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef KEYLOG_ENABLE
  if (record->event.pressed) {
    add_keylog(keycode);
  }
  #endif //KEYLOG_ENABLE
  
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {  
          default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case CLMAKDH:
      if (record->event.pressed) {
          default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;
  }
  return true;
}