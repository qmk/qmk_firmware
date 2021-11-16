/* Copyright 2021 Jay Greco
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

bool numlock_set = false;

enum layers {
    _BASE = 0,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
                             KC_PSLS, KC_PAST, KC_PMNS, 
  KC_VOLD, KC_VOLU, KC_MUTE, KC_P7,   KC_P8,   KC_P9, 
  KC_MPRV, KC_MNXT, KC_MPLY, KC_P4,   KC_P5,   KC_P6,
  KC_LEFT, KC_RGHT, KC_F1,   KC_P1,   KC_P2,   KC_P3, 
  KC_WH_D, KC_WH_U, KC_F2,   KC_P0,   KC_PDOT, KC_PENT  
  ),

  [_FUNC] = LAYOUT(
                 ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, ___  
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_remote_kb(keycode, record);

  // Get the current NLCK status & set if not set.
  // Only do this once, in case user has a NLCK key
  // and wants to disable it later on.
  if (!numlock_set && record->event.pressed) {
    led_t led_state = host_keyboard_led_state();
    if (!led_state.num_lock) {
      register_code(KC_NLCK);
    }
    numlock_set = true;
  }

  return true;
}

void matrix_init_user(void) {
  matrix_init_remote_kb();
  set_bitc_LED(LED_OFF);
}

void matrix_scan_user(void) {
  matrix_scan_remote_kb();
}
