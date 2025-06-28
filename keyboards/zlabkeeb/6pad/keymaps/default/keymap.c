/*
Copyright 2024 zlabkeeb (zlabkeeb@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────────┌─────────┌─────────┐
     * │    1    │ layer 1 │    3    │
     * ├─────────┼─────────┼─────────|
     * │    4    │    5    │    6    |
     * ├─────────┼─────────┼─────────┘
     */
    [0] = LAYOUT(
        KC_1, TO(1), KC_2,
        KC_3, KC_4, KC_5
        ),
    /*
     * ┌─────────┌─────────┌─────────┐
     * │    A    │ layer O │    B    │
     * ├─────────┼─────────┼─────────|
     * │    C    │    D    │    E    |
     * ├─────────┼─────────┼─────────┘
     */
    [1] = LAYOUT(
        KC_A, TO(0), KC_B,
        KC_C, KC_D, KC_E
        )
};

#if defined (ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP)}
};
#endif
