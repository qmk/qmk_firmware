/*
Copyright 2021 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stick.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }
}, {
    // LED Index to Physical Position
    { 0, 0 }, { 20, 0 }, { 40, 0 }, { 60, 0 },
    { 80, 0 }, { 100, 0 }, { 120, 0 }, { 140, 0 },
    { 160, 0 }, { 180, 0 }, { 200, 0 }, { 220, 0 },
}, {
    // LED Index to Flag
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();             // Enable RGB by default
    rgblight_sethsv(0, 255, 255);  // Set default HSV - red hue, full saturation, full brightness
#    ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);  // set to RGB_RAINBOW_SWIRL by default
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();  // Enable RGB by default
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return false;
}
