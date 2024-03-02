 /* Copyright 2020 t-miyajima
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
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------------------------------------------.
   * | Tab |  /|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  -| Bspc|
   * |-------------------------------------------------------|
   * | Ctrl  |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S| Return|
   * |-------------------------------------------------------|
   * | Shift  |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|   Z| Del|
   * `----.---------------------------------------------.---'
   *      | Alt |Win | Layer |   Space   |Win |Alt |Esc |
   *      `---------------------------------------------'
   */
    LAYOUT_44key( /* Base */
        KC_TAB, KC_SLASH, KC_COMMA, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_MINUS, KC_BSPC,
        KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_ENTER,
        KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_DELETE,
        KC_LALT, KC_LGUI, MO(1), KC_SPACE, KC_RGUI, KC_RALT, KC_ESCAPE),
    LAYOUT_44key( /* layer 1 */
        KC_GRAVE, KC_EXCLAIM, KC_AT, KC_HASH, KC_QUOTE, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRC, KC_RBRC,
        KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
        KC_TRNS, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_EQUAL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
