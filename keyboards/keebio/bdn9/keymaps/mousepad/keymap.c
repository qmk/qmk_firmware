/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
    [0] = LAYOUT(
        KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, \
        KC_WH_UP, KC_WH_UP, KC_WH_L, \
        KC_WH_DN, TT(1), KC_WH_R \
    ),
    [1] = LAYOUT(
        RESET,   KC_ACL0, KC_ACL1, \
        KC_VOLU, KC_ACL2, KC_BRIU, \
        KC_VOLD, TO(1),  KC_BRID \
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_LEFT);
        } else {
            tap_code(KC_MS_RIGHT;
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_UP);
        } else {
            tap_code(KC_MS_DN);
        }
    }
}
