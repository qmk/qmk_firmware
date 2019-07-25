/* Copyright 2019 imchipwood
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

#ifndef _DUMBPAD_TEST
#define _DUMBPAD_TEST
#endif

#include <print.h>

#define BASE 0
#define SUB 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( /* Base */
             KC_W,
    TG(SUB), KC_S, KC_D
  ),
  [SUB] = LAYOUT( /* Sub layer */
             KC_S,
    KC_TRNS, KC_X, KC_C
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 

  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable = true;
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


bool encoder_update_user(uint8_t index, bool clockwise) {
  // put your custom code here
  // change "return false;" to "return true;" if you do anything 
  // returning false will cause it to use the default encoder actions
  uprintf("layer: %d, SUB on: %d\n", layer_state, IS_LAYER_ON(SUB));
  return false;
}
