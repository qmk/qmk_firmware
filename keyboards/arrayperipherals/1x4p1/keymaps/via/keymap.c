/*
Copyright 2020 David Doan

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

#include QMK_KEYBOARD_H

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_MS_WH_UP);
    } else {
      tap_code(KC_MS_WH_DOWN);
    }
  }
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //button closest to usb is first
  [0] = LAYOUT_ortho_1x5(
     KC_ESC, KC_TAB, KC_LSHIFT, KC_LCTRL, TG(1)
   ),

  [1] = LAYOUT_ortho_1x5(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(2)
  ),
  [2] = LAYOUT_ortho_1x5(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(3)
  ),
  [3] = LAYOUT_ortho_1x5(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(0)
  )
};
