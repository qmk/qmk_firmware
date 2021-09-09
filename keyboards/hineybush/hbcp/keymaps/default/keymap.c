/* Copyright 2019 hineybush
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all( /* Base */

  /*#define LAYOUT_all( \
    K000,    K001, K002, K003, K004,    K005, K006, K007, K008,    K009, K010, K011, K012,           K014, K015, K016, K017, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K013,        K114, K115, K116, K117, \
    K200,   K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,    K213,         K214, K215, K216, K217, \
    K300,    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,   K313,         K314, K315, K316, K317, \
    K400,     K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,      K413,     K414, K415, K416, K417, \
    K500, K501, K502,             K505,                   K509, K510, K511,          K512, K513, K514,     K515, K516, K517 \
)*/
    KC_ESC,   KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,                                KC_DEL,  KC_INS,  KC_PGUP, KC_PGDN,
    KC_GRV,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_GRV, KC_BSPC,              KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS,
    KC_TAB,   KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,                      KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_CAPS,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT, KC_NUHS, KC_ENT,                       KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,  KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_LSFT,                KC_UP,         KC_P1,   KC_P2,   KC_P3,   KC_TRNS,
    KC_LCTL,  KC_LGUI, KC_LALT,                KC_SPC,                         KC_LALT, MO(1),    KC_RGUI,                KC_LEFT, KC_DOWN, KC_RGHT,       KC_P0,   KC_PDOT, KC_PENT

    ),

  [1] = LAYOUT_all(
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                               KC_PSCR, KC_SLCK,KC_HOME, KC_END,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             RGB_HUD, RGB_HUI,KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS, RESET ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                      RGB_SAD, RGB_SAI,KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                      RGB_VAD, RGB_VAI,KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                KC_VOLU,       RGB_TOG, RGB_MOD,KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,                       KC_MPLY,                          KC_TRNS, KC_TRNS,  KC_TRNS,       KC_MPRV, KC_VOLD,  KC_MNXT,      KC_TRNS,KC_TRNS, KC_TRNS

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
