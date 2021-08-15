/* Copyright 2021 Ananya Kirti
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x3(
        KC_CAPSLOCK,  MO(1), KC_PGUP,
        KC_DEL,  KC_END,  KC_PGDN
    ),
    [1] = LAYOUT_ortho_2x3(
        KC_CAPSLOCK,  MO(1), KC_PGUP,
        KC_DEL,  KC_END,  KC_PGDN
    ),

};



void matrix_scan_user(void) {
    writePin(D0, layer_state_is(1));
}

bool led_update_user(led_t led_state) {
    writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
    return false;
};



bool encoder_update_user(uint8_t index, bool clockwise) {
    if(IS_LAYER_ON(1)) { // on Raise layer
      if (clockwise) {
          tap_code(KC_A);
      } else {
          tap_code(KC_B);
      }
    }
    // default layer
    else {
      if (clockwise) {
          tap_code(KC_C);
      } else {
          tap_code(KC_D);
      }
    }
    return true;
}
