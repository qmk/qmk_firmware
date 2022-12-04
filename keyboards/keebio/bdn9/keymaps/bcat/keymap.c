/* Copyright 2021 Jonathan Rascher
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

#include "bcat.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [LAYER_DEFAULT] = LAYOUT(
        KC_MUTE,  LY_FN1,   BL_BRTG,
        KC_F4,    KC_F5,    KC_F6,
        KC_F1,    KC_F2,    KC_F3
    ),
    [LAYER_FUNCTION_1] = LAYOUT(
        EE_CLR,   _______,  QK_BOOT,
        KC_F10,   KC_F11,   KC_F12,
        KC_F7,    KC_F8,    KC_F9
    ),
    // clang-format on
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        /* Top-left encoder (volume) */
        case 0:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            return false;
        /* Top-right encoder (backlight brightness) */
        case 1:
#if defined(BACKLIGHT_ENABLE)
            if (clockwise) {
                backlight_increase();
            } else {
                backlight_decrease();
            }
#endif
            return false;
    }
    return true;
}
