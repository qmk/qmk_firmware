/* Copyright 2021 yynmt
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
  /* Base
   * ,-----------------------------------------.
   * |  Cut | Copy |Paste |  Up  |Delete| Bksp |
   * |      |      |      |      |      |Raise |
   * |------+------+------+------+------+------|
   * | Ctrl |Shift | Left | Down |Right |Enter |
   * |      |      |      |      |      |Lower |
   * `-----------------------------------------'
   */
  [0] = LAYOUT(
    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_UP, KC_DEL, LT(2,KC_BSPC),
    KC_LCTL, KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, LT(1,KC_ENT)
  ),
  /* Lower */
  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  /* Raise */
  [2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  /* Adjust */
  [3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};
