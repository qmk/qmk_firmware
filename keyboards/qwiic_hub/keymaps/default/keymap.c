/* Copyright 2018 Jack Humbert
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

#include "qwiic_hub.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_ortho_2x2(
  KC_TAB, KC_SPACE,
  KC_LSFT, KC_ENT
)

};

void encoder_update_user(int8_t index, bool clockwise) {
  switch(index) {
    case 0:
      if (clockwise) {
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      } else {
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      }
      break;
    case 1:
      if (clockwise) {
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      } else {
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      }
      break;
    case 2:
      break;
    case 3:
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_scan_user(void) {
}
