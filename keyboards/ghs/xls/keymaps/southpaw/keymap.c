/* Copyright 2022 Ramon Imbao
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
    /*
     * ┌───┬───┬───┬───┐
     * │F13│F14│F15│F16│
     * ├───┼───┼───┼───┤
     * │ - │ * │ / │Num│
     * ├───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │
     * │ + ├───┼───┤───│
     * │   │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼───┤
     * │   │ 1 │ 2 │ 3 │
     * │Ent├───┼───┴───│
     * │   │ . │   0   │
     * └───┴───┴───────┘
     */
    [0] = LAYOUT_numpad_6x4_southpaw(
        KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_PMNS, KC_PAST, KC_PSLS, KC_NUM,
        KC_PPLS, KC_P7,   KC_P8,   KC_P9,
                 KC_P4,   KC_P5,   KC_P6,
        KC_PENT, KC_P1,   KC_P2,   KC_P3,
                 KC_PDOT, KC_P0
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_BRIU, 10);
        } else {
            tap_code_delay(KC_BRID, 10);
        }
    } else if (index == 2) {
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }

    return false;
}
