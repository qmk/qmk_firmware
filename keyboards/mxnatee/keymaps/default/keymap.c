/* Copyright 2021 juan
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
              RESET, KC_R, 			          KC_F3, KC_F4,            \
              KC_Q,  KC_D, KC_W, KC_B,		KC_J, KC_F,  KC_U, KC_P,       \
              KC_S,  KC_H, KC_T, KC_G,		KC_Y, KC_N,  KC_E, KC_O,       \
        KC_A,        KC_Z, KC_X, KC_M,		KC_V, KC_K,  KC_L,       KC_I, \
                     KC_1, KC_2, KC_C,      KC_6, KC_7, KC_8,              \
                           KC_4, KC_5,      KC_9, KC_0
    )
};
