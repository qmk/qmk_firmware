/*
Copyright 2023 Matt F

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


#define _FN      MO(3)
#define FN_BACK  LT(3, KC_BSPC)
#define ZOOMIN   C(KC_EQL)
#define ZOOMOUT  C(KC_MINS)
#define NTAB     C(KC_TAB)
#define BTAB     C(S(KC_TAB))



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(

    /* Base Layer


*  --------- .-----------------------------------. .-----------------------------------. .-----------------------------------. --------.   .--------------------------.
 * | ESC   | | F1     | F2     | F3     | F4     | | F5     | F6     | F7     | F8     | | F9     | F10    | F11    | F12    | | F13   |   | PrintSC| ScrlLk | Pause  |
 * |       | |        |        |        |        | |        |        |        |        | |        |        |        |        | |       |   |        |        |        |
 * '-------+ '--------+--------+--------+--------' '--------+--------+--------+--------' '--------+--------+--------+--------' '-------+   '--------+--------+--------'

 * .-----------------------------------------------------------------------------------------------------------------------------------.  .--------------------------.
 * | Grave     | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | Backspace |  | Ins    | Home   | PageUp |
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |  |        |        |        |
 * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------|  |--------+--------+--------|
 * | Tab       | Q      | W      | E      | R      | T      |        |        | Y      | U      | I      | O      | P      | Del       |  | Del    | End    |PageDown|
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |  |        |        |        |
 * |-----------+--------+--------+--------+--------+--------| [      | ]      |--------+--------+--------+-----------------+-----------|  '--------+--------+--------'
 * | FN_BACK   | A      | S      | D      | F      | G      |--------+--------| H      | J      | K      | L      | "      | Enter     |
 * |           |        |        |        |        |        |        |        |        |        |        |        | '      |           |
 * |-----------+--------+--------+--------+--------+--------| Prev   | Next   |--------+--------+--------------------------+-----------|           .--------.
 * | LShift    | Z      | X      | C      | V      | B      | Tab    | Tab    | N      | M      | <      | >      | ?      | RShift    |           | Up     |
 * |           |        |        |        |        |        |        |        |        |        | ,      | .      | /      |           |           |        |
 * |-----------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+-----------|  .--------+--------+--------.
 * | LCtrl     | LGUI   | LALT   | FN     | Space  | Space  |      Space      | Space  | Space  | Space  | RALT  | RGUI    | RCTRL     |  | Left   | Down   | Right  |
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |  |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------------'  '--------+--------+--------'
 */

  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,           KC_PSCR, KC_SCRL, KC_PAUS,

  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,          KC_INS,  KC_HOME, KC_PGUP,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,           KC_DEL,  KC_END,  KC_PGDN,
  FN_BACK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    BTAB,    NTAB,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,                   KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,       KC_SPC,      KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, _FN,     KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT( /* Layer One */

  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,           KC_PSCR, KC_SCRL, KC_PAUS,

  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,          KC_INS,  KC_HOME, KC_PGUP,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,           KC_DEL,  KC_END,  KC_PGDN,
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PGUP, KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,       KC_SPC,      KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, _FN,     KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),


  [2] = LAYOUT( /* Layer Two */

  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,           KC_PSCR, KC_SCRL, KC_PAUS,

  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,          KC_INS,  KC_HOME, KC_PGUP,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    ZOOMIN,  KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,           KC_DEL,  KC_END,  KC_PGDN,
  FN_BACK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    ZOOMOUT, KC_LBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,       KC_SPC,      KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, _FN,     KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [3] = LAYOUT( /* Layer Three */

  KC_ESC,  DF(0),   DF(1),   DF(2),   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,           KC_PSCR, KC_SCRL, QK_BOOT,

  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, DF(0),   RGB_MOD,
  KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, DF(1),   RGB_RMOD,
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_VOLD, KC_BSLS, KC_CAPS,                   KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_ENT,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
  )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
};
#endif
