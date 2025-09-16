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
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // Left Half
    { 0, 1, 2, 3, 4, 5 },
    { 11, 10, 9, 8, 7, 6 },
    { 12, 13, 14, 15, 16, 17 },
    { 23, 22, 21, 20, 19, 18 },
    { NO_LED, NO_LED, 24, 25, 26, 27 },
    // Right Half
    { 34, 35, 36, 37, 38, 39 },
    { 45, 44, 43, 42, 41, 40 },
    { 46, 47, 48, 49, 50, 51 },
    { 57, 56, 55, 54, 53, 52 },
    { NO_LED, NO_LED, 58, 59, 60, 61 }
}, {
    // LED Index to Physical Position
    // Left Half
    { 0, 5 }, { 16, 5 }, { 32, 2 }, { 48, 0 }, { 64, 2 }, { 80, 3 },
    { 80, 17 }, { 64, 15 }, { 48, 13 }, { 32, 15 }, { 16, 18 }, { 0, 18 },
    { 0, 32 }, { 16, 32 }, { 32, 28 }, { 48, 27 }, { 64, 28 }, { 80, 30 },
    { 80, 43 }, { 64, 42 }, { 48, 40 }, { 32, 42 }, { 16, 45 }, { 0, 45 },
    { 56, 47 }, { 72, 58 }, { 90, 64 }, { 98, 52 },
    { 80, 58 }, { 40, 50 }, { 8, 43 }, { 8, 5 }, { 40, 1 }, { 72, 3 },
    // Right Half
    { 224, 5 }, { 208, 5 }, { 192, 2 }, { 176, 0 }, { 160, 2 }, { 144, 3 },
    { 144, 18 }, { 160, 18 }, { 176, 15 }, { 192, 13 }, { 208, 15 }, { 224, 17 },
    { 224, 32 }, { 208, 32 }, { 192, 28 }, { 176, 27 }, { 160, 28 }, { 144, 30 },
    { 144, 45 }, { 160, 45 }, { 176, 42 }, { 192, 40 }, { 208, 42 }, { 224, 43 },
    { 168, 47 }, { 152, 58 }, { 134, 64 }, { 126, 52 },
    { 144, 58 }, { 184, 50 }, { 216, 43 }, { 216, 5 }, { 184, 1 }, { 152, 3 }
}, {
    // LED Index to Flag
    // Left Half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
          4, 4, 4, 4,
    2, 2, 2, 2, 2, 2,
    // Right Half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4,
    2, 2, 2, 2, 2, 2

} };


#endif

#ifdef ENCODER_ENABLE
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
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 2) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 3) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
