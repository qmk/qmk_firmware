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

// Layer shorthand
enum layer {
  _BASE,
  _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * | Gesc  |   1   |   2   |   3   |   4   |   5   |   -   |  Num  |   =   |   6   |   7   |   8   |   9   |   0   | Bksp  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  |   Q   |   W   |   E   |   R   |   T   |   7   |   8   |   9   |   Y   |   U   |   I   |   O   |   P   |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  |   A   |   S   |   D   |   F   |   G   |   4   |   5   |   6   |   H   |   J   |   K   |   L   |   ;   |   '   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |   Z   |   X   |   C   |   V   |   B   |   1   |   2   |   3   |   N   |   M   |   ,   |   .   |   /   | Enter |
 * |-------+-------+---------------------------------------------------------------------------------------+-------+-------|
 * | Ctrl  |  Fn   |  Alt  |  Cmd  |                         Space                         | Left  | Down  |  Up   | Right |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
 [_BASE] = LAYOUT_ortho_7u(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_NLCK, KC_EQL,  KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_P7,   KC_P8,   KC_P9,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_P4,   KC_P5,   KC_P6,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, MO(_FN), KC_LALT, KC_LGUI,                            KC_SPC,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
 ),

 [_FN] = LAYOUT_ortho_7u(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F13,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,                            _______,                            _______, _______, _______, _______
 )
};
