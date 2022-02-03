/*
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

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer
   * .-----------------------------------------------------------------------------------------------------------------------------------------'
   * |  =        | 1      | 2      | 3      | 4      | 5      | [      | ]      | `      | 6      | 7      | 8      | 9      | 0      | -      |
   * |-----------+--------+--------+------- +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | TAB       | Q      | W      | E      | R      | T      | 7      | 8      | 9      | Y      | U      | I      | O      | P      | BCKSPC |
   * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * | ESC(CTRL) | A      | S      | D      | F      | G      | 4      | 5      |  6     | H      | J      | K      | L      | ;      | '      |
   * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------- +--------+--------+--------|
   * | LSHIFT    | Z      | X      | C      | V      | B      | 1      | 2      | 3      | N      | M      | ,      | .      | /      | ENTER  |
   * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   *            |  LCTRL  |  LGUI  |  LALT   |                        SPACE                            | RALT  |  MO (FN)  | APP    |
   *'------------------------------------------------------------------------------------------------------------------------------------------'
   */
    [0] = LAYOUT_7u(
      KC_EQL,        KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_LBRC,   KC_RBRC,   KC_GRV,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TAB,        KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_P7,     KC_P8,     KC_P9,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_P4,     KC_P5,     KC_P6,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,       KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_P1,     KC_P2,     KC_P3,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
           KC_LCTL,  KC_LGUI,  KC_LALT,                                      KC_SPC,                                    KC_RALT,     MO(1),    KC_MENU
    ),

    /* Function Layer
    * .-------------------------------------------------------------------------------------------------------------------------------------'
    * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | F13   | DEL    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------|
    * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |       |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+----------------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET   |      |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+----------------|
    * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |       |
    * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+----------------|
    *          |        |       |        |                                                              |         |        |        |
    *'--------------------------------------------------------------------------------------------------------------------------------------'
    */
    [1] = LAYOUT_7u(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13, KC_DEL,
      _______, _______, KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, _______, _______,
        _______, _______, _______,                                 _______,                                        _______, _______, _______
    )
};
