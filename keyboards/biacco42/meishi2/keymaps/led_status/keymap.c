/* Copyright 2019 Biacco42
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

#define PRO_MICRO_LED_TX D5
#define PRO_MICRO_LED_RX B0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V)
  )
};

void matrix_init_user(void) {
  setPinOutput(PRO_MICRO_LED_TX);
  setPinOutput(PRO_MICRO_LED_RX);
}

bool led_update_user(led_t led_state) {
  writePin(PRO_MICRO_LED_TX, !led_state.num_lock);
  writePin(PRO_MICRO_LED_RX, !led_state.caps_lock);
  return true;
}
