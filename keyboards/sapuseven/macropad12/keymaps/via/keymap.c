/* Copyright 2023 SapuSeven
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
    [0] = LAYOUT_ortho_3x4(
        KC_1, KC_2, KC_3, KC_PLUS,
        KC_4, KC_5, KC_6, KC_MINUS,
        KC_7, KC_8, KC_9, KC_0
    ),
    [1] = LAYOUT_ortho_3x4(
        KC_F1, KC_F2, KC_F3, KC_F4,
        KC_F5, KC_F6, KC_F7, KC_F8,
        KC_F9, KC_F10, KC_F11, KC_F12
    ),
    [2] = LAYOUT_ortho_3x4(
        KC_F13, KC_F14, KC_F15, KC_F16,
        KC_F17, KC_F18, KC_F19, KC_F20,
        KC_F21, KC_F22, KC_F23, KC_F24
    ),
    [3] = LAYOUT_ortho_3x4(
        KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO
    )
};
