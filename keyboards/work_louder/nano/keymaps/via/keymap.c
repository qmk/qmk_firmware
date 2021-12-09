/* Copyright 2021 Drashna Jael're
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


#define LAYOUT_via( \
    k00, k01, k02, \
    k00_a, k00_b \
) { \
    { k00, k01,   k02, k00_a, k00_b } \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_via(
        KC_PSCR, MACRO00, MO(1),
        KC_PGDN, KC_PGUP
    ),
    [1] = LAYOUT_via(
        RESET,   MACRO01, _______,
        _______, _______
    ),
    [2] = LAYOUT_via(
        _______, _______, _______,
        _______, _______
    ),
    [3] = LAYOUT_via(
        _______, _______, _______,
        _______, _______
    )
};
