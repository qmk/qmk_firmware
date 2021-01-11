/* Copyright 2018 MechMerlin
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
[0] = LAYOUT( /* Base */
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC, \
  KC_D,  KC_O,  KC_N, KC_U, KC_T, KC_C, KC_A, KC_T, KC_SPC, KC_R, KC_U, KC_L, KC_E, KC_S, KC_SPC \
),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
