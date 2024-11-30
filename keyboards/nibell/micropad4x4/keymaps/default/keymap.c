/*
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
    /*
     * ┌───────┬─────┬────────┬───────┐
     * │  F1   │ F2  │   F3   │  F4   │
     * ├───────┼─────┼────────┼───────┤
     * │  F5   │ F6  │   F7   │  F8   │
     * ├───────┼─────┼────────┼───────┤
     * │   1   │  2  │   3    │   4   │
     * ├───────┼─────┼────────┼───────┤
     * │ PRTSC │ INS │ RSHIFT │ RCTRL │
     * └───────┴─────┴────────┴───────┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_F1,              KC_F2,      KC_F3,          KC_F4,
        KC_F5,              KC_F6,      KC_F7,          KC_F8,
        KC_1,               KC_2,       KC_3,           KC_4,
        KC_PRINT_SCREEN,    KC_INSERT,  KC_RIGHT_SHIFT, KC_RIGHT_CTRL
    )
};
