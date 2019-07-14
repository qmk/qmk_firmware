/* Copyright 2019 Chip
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include <print.h>

#define BASE 0
#define SUB  1

#define ___ KC_TRNS

#define TAPPING_TOGGLE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
        BASE LAYER
   /-----------------------------------------------------`
   |             |    7    |    8    |    9    |  Bkspc  |
   |             |---------|---------|---------|---------|
   |             |    4    |    5    |    6    |   Esc   |
   |             |---------|---------|---------|---------|
   |             |    1    |    2    |    3    |   Tab   |
   |-------------|---------|---------|---------|---------|
   | Left mouse  | TapTog  |    0    |    .    |  Enter  |
   \-----------------------------------------------------'
  */
  [BASE] = LAYOUT( /* Base */
                   KC_7,      KC_8,    KC_9,     KC_BSPC, 
                   KC_4,      KC_5,    KC_6,     KC_ESC, 
                   KC_1,      KC_2,    KC_3,     KC_TAB, 
    TT(SUB),       TT(SUB),   KC_0,    KC_DOT,   KC_ENT
  ),
  /*
        SUB LAYER
   /-----------------------------------------------------`
   |             |         |         |         |  Reset  |
   |             |---------|---------|---------|---------|
   |             |         |   Up    |         |  Debug  |
   |             |---------|---------|---------|---------|
   |             |  Left   |  Down   |  Right  |         |
   |-------------|---------|---------|---------|---------|
   | Right mouse |         |         |         |         |
   \-----------------------------------------------------'
  */
  [SUB] = LAYOUT(
                   ___,       ___,     ___,      RESET, 
                   ___,       KC_UP,   ___,      DEBUG, 
                   KC_LEFT,   KC_DOWN, KC_RIGHT, ___, 
    TT(BASE),      ___,       ___,     ___,      ___
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
*/
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}


void encoder_update_kb(uint8_t index, bool clockwise) {
  if (index == 0) {
    //uprintf("layer: %u\n", layer_state);
    if (layer_state | 0x1) {
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    } else {
      if (clockwise) {
        tap_code(KC_MS_R);
      } else {
        tap_code(KC_MS_L);
      }
    }
  }
}
