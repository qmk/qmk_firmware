/* Copyright 2015-2017 Jack Humbert
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


enum layers {
  _BASE,
  _FUNC
};

enum custom_keycodes {
  FUNC = SAFE_RANGE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   *         ,------.
   *         |   1  |
   *     ,------+------.
   *     |   2  |   3  |
   * ,------+------+------.
   * |   4  | FUNC |   6  |
   * `--------------------'
   */
  [_BASE] = LAYOUT(
            KC_1,
         KC_2, KC_3,
    KC_4, MO(_FUNC), KC_6
  ),

  /* Func
   *         ,------.
   *         |BCKLIT|
   *     ,------+------.
   *     |   8  |   9  |
   * ,------+------+------.
   * |   0  | FUNC | QK_BOOT|
   * `--------------------'
   */
  [_FUNC] = LAYOUT(
            BACKLIT,
         KC_8, KC_9,
    KC_0, _______, QK_BOOT
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
		  register_code(KC_LSFT);
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
		unregister_code(KC_LSFT);
      }
      return false;
      break;
  }
  return true;
}
