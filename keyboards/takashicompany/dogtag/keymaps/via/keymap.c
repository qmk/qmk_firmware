/* Copyright 2021 takashicompany
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
    LAYOUT(
        LT(1, KC_ESC), KC_Q, KC_W, KC_E,                 KC_Y, KC_U, KC_I, KC_O,
        KC_LSFT,       KC_A, KC_S, KC_D, KC_SPC, KC_TAB, KC_H, KC_J, KC_K, KC_L,
        KC_WH_U, KC_WH_D, KC_WH_U, KC_WH_D
    ),

    LAYOUT(
        KC_TRNS, RGB_MOD, RGB_HUI, RGB_SAI,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_M_P, RGB_M_K, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_WH_L, KC_WH_R, KC_WH_L, KC_WH_R
    )
};
