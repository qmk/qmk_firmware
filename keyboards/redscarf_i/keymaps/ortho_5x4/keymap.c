/* Copyright 2019 Ben Weakley
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

enum custom_keycodes {
  KC_P00 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_5x4( // Base
    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,   KC_PEQL,
    KC_P1,   KC_P2,   KC_P3,   KC_ENT,
    KC_P0,   KC_P00,  KC_PDOT, MO(1)
  ),
  [1] = LAYOUT_ortho_5x4( // Function 1
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    BL_TOGG, BL_STEP, BL_BRTG, _______,
    KC_MUTE, KC_VOLD, KC_VOLU, _______,
    KC_MPRV, KC_MPLY, KC_MNXT, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_P00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      break;
  }
  return true;
}
