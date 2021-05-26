/* Copyright 2020 codecoffeecode
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
    [0] = LAYOUT(
      KC_HOME,              KC_UP,   KC_END,   /*|*/ KC_TRNS,
      KC_LEFT,              KC_DOWN, KC_RIGHT, /*|*/ KC_TRNS,
      KC_MPRV,              KC_MPLY, KC_MNXT,  /*|*/ KC_TRNS,
      LCTL(LSFT(KC_ESC)),   RGB_TOG, LGUI(KC_L)
      ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(index) {
      case 0:
        if (clockwise) {
          tap_code(KC_VOLU); // Volume
        } else {
          tap_code(KC_VOLD);
        }
        break;
      case 1:
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);  // Scroll
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;
      case 2:
        if (clockwise) {
          rgblight_increase_hue(); // RGB Hue
        } else {
          rgblight_decrease_hue();
        }
        break;
    }
    return true;
}
