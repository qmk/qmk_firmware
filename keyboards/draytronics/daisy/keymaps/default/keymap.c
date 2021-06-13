/*Copyright 2021 Blake Drayson / Draytronics

Contact info@draytronics.co.uk

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
#define _BASE 0  // Base layer
#define _CODE 1  // Code layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_daisy(
      KC_MUTE,                     KC_HOME,
      MO(_CODE), KC_MPRV, KC_MNXT, KC_MPLY,
      C(KC_LEFT), C(KC_UP), C(KC_DOWN), C(KC_RIGHT)
    ),
    [_CODE] = LAYOUT_daisy(
      KC_MUTE,                     KC_END,
      _______, RGB_MOD, RGB_VAI, RGB_TOG,
      G(S(KC_5)), G(A(KC_ESC)), G(KC_F), RESET
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
}
