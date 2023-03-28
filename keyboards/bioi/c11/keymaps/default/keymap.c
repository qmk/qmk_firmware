/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#include "print.h"
#include "../../../ble.h"
#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    // 0: Base Layer
    [0] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6, 
        KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11),
    // 1: Function Layer
    [1] = LAYOUT(
        KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______,  _______,
        _______,  _______,  _______,  _______, _______),

    [2] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______),

    [3] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______),
    // clang-format on
};

void keyboard_pre_init_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_F13:
            if (record->event.pressed) {
                rgb_matrix_toggle();
            }
            break;
        case KC_F14:
            if (record->event.pressed) {
                rgb_matrix_step();
            }
            break;
        case KC_F15:
            if (record->event.pressed) {
                rgb_matrix_step_reverse();
            }
            break;
        case KC_F16:
            if (record->event.pressed) {
                rgb_matrix_increase_hue();
            }
            break;
        case KC_F21:
            if (record->event.pressed) {
                module_reset();
            } else {
            }
            break;
        case KC_F19:
            if (record->event.pressed) {
                reset_ble_batt();

            } else {
            }
            break;
        case KC_F20:
            if (record->event.pressed) {
                update_ble_batt();
                wait_ms(100);

            } else {
            }
            break;
        default:
            return true;
    }
    return true;
}
