/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "kanagawa2040.h"

#ifdef RGB_MATRIX_ENABLE

#define NA NO_LED

/* RGB Positioning */
led_config_t g_led_config = {  {
    // Key Matrix to LED Index
    { 12,  11, 10,  9,  8,      7,  6,  5,  4,  3,  2,      1,      0, NO_LED, NO_LED },
    { 26,  25, 24, 23, 22,     21, 20, 19, 18, 17, 16,     15,     14,     13,     66 },
    { 40,  39, 38, 37, 36,     35, 34, 33, 32, 31, 30,     29,     28,     27,     67 },
    { 53,  52, 51, 50, 49,     48, 47, 46, 45, 44, 43,     42,     41, NO_LED,     68 },
    { 65,  64, 63, 62, 61,     60, 59, 58, 57, 56, 55,     54, NO_LED,     70, NO_LED },
    { 82,  81, 80, 79, 78, NO_LED, 77, 76, 75, 74, 73, NO_LED,     72,     71,     69 }
}, {
    // LED Index to Physical Position
    { 0,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 112,  0 }, { 224,  0},
    { 0, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 112, 21 }, { 224, 21},
    { 0, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 224, 42},
    { 0, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 224, 42},
    { 0, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 112, 42 }, { 224, 42},
    { 0, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 112, 64 }, { 224, 64}
}, {
    // LED Index to Flag
    4, 4, 4,
    4, 4, 4,
    4, 4, 4,
    4, 4, 4
} };

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif
