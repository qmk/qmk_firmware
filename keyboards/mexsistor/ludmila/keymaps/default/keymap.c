/* Copyright 2020 Kevin M.
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

// Keyboard Layers
enum keyboard_layers{
    _BASE = 0,
    _CONTROL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base */
    KC_A, KC_B, KC_C,
    KC_D, KC_E

  );

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_F);
        } else {
            tap_code(KC_G);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Example of "pressing" CONTROL+SHIFT+V instead of "A" on keyboard
    // More info: https://docs.qmk.fm/#/feature_macros
    // case KC_A:
    //   if (record->event.pressed) {
    //     SEND_STRING(SS_LCTL(SS_LSFT("v")));
    //   } else {
    //   }
    //   break;
  }
  return true;
};
