/* Copyright 2025 @mawaeg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
    // clang-format off
    /*
     *             ┌────────────┐
     *             │ RGB_MOD    │
     * ┌───┬───┬───┼────────────┤
     * │ 7 │ 8 │ 9 │ RGB_TOGGLE │
     * ├───┼───┼───┼────────────┤
     * │ 4 │ 5 │ 6 │ NUM        │
     * ├───┼───┼───┼────────────┤
     * │ 1 │ 2 │ 3 │ 0          │
     * └───┴───┴───┴────────────┘
     */
        [0] = LAYOUT(
                             RM_NEXT,
        KC_P7, KC_P8, KC_P9, RM_TOGG,
        KC_P4, KC_P5, KC_P6, KC_NUM,
        KC_P1, KC_P2, KC_P3, KC_P0
    )
    // clang-format on
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(RM_SPDD, RM_SPDU)},
};
#endif
