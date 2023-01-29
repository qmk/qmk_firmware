/* Copyright 2023 a_marmot
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┼───┤
     * │Tab│ q │ w │ e │ r │
     * ├───┼───┼───┼───┼───┤
     * │Ctl│ a │ s │ d │ f │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ z │ x │ c │ v │
     * ├───┼───┼───┼───┼───┤
     * │Alt│ ↑ │ ↓ │ → │ ← │
     * ├───┴───┴───┴───┴───┤
     * │Spa                │
     * └───────────────────┘
     */
    [0] = LAYOUT_keypad(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
        KC_LALT, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ),

    /*
     * ┌───┌───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┼───┤
     * │Tab│ q │ w │ e │ r │
     * ├───┼───┼───┼───┼───┤
     * │Ctl│ a │ s │ d │ f │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ z │ x │ c │ v │
     * ├───┼───┼───┼───┼───┤
     * │Alt│ ↑ │ ↓ │ → │ ← │
     * ├───┴───┴───┴───┴───┤
     * │Spa                │
     * └───────────────────┘
     */
  /*   [1] = LAYOUT_keypad(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
        KC_LALT, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE
    ) */
};
