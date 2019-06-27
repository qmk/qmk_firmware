/* Copyright 2019 Ryota Goto
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

/*
 *  K702,       K503, K504, K604, K704,    K706, K708, K609, K509,    K506, K406, K411, K412,    K415, K315, K114, \
 *  K502, K402, K403, K404, K405, K505, K507, K407, K408, K409, K410, K510, K508,       K606,    K512, K514, K513, \
 *  K602, K302, K303, K304, K305, K605, K607, K307, K308, K309, K310, K610, K608,       K206,    K511, K414, K413, \
 *  K603, K202, K203, K204, K205, K705, K707, K207, K208, K209, K210, K710,             K106,                      \
 *  K601,       K102, K103, K104, K105, K005, K007, K107, K108, K109, K010,             K101,          K714,       \
 *  K500,       K715,                         K006,                         K015,       K100,    K014, K011, K012  \
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_A,  KC_1,  KC_H, \
      KC_TAB,  KC_SPC   \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
