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

#include "macropad.h"

#ifdef RGB_MATRIX_ENABLE

#define NA NO_LED

/* RGB Positioning */
led_config_t g_led_config = { {
    { NA,  NA, NA },
    {  0,   1,  2 },
    {  3,   4,  5 },
    {  6,   7,  8 },
    {  9,  10, 11 }
}, {
    { 0,  0 }, { 112,  0 }, { 224,  0},
    { 0, 21 }, { 112, 21 }, { 224, 21},
    { 0, 42 }, { 112, 42 }, { 224, 42},
    { 0, 64 }, { 112, 64 }, { 224, 64}
}, {
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
