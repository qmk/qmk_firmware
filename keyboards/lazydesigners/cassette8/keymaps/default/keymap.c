/* Copyright 2021 LAZYDESIGNERS
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

#define LT1_SPC LT(1, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,      KC_2,    KC_3,     KC_4,    
        KC_5,      KC_6,    KC_7,     LT1_SPC
        ),
    [1] = LAYOUT(
        RESET,     KC_NO,   KC_NO,   KC_NO,
        KC_NO,     KC_NO,   KC_NO,   KC_NO
        ),
    [2] = LAYOUT(
        KC_NO,     KC_NO,   KC_NO,   KC_NO,
        KC_NO,     KC_NO,   KC_NO,   KC_NO
        ),
};
