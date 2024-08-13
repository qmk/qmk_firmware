/* Copyright 2024 Sandy Macdonald (https://github.com/sandyjmacdonald)
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |       G location
     *   |  |       |       B location
     *   |  |       |       | */
        {0, C8_9, C6_9, C7_9},
        {0, C9_9, C3_9, C5_9},
        {0, C8_1, C6_1, C7_1},
        {0, C9_1, C3_1, C5_1},
        {0, C8_10, C6_10, C7_10},
        {0, C9_10, C3_10, C5_10},
        {0, C8_2, C6_2, C7_2},
        {0, C9_2, C3_2, C5_2},
        {0, C8_11, C6_11, C7_11},
        {0, C9_11, C2_10, C5_11},
        {0, C8_3, C6_3, C7_3},
        {0, C9_3, C2_2, C5_3},
        {0, C8_12, C6_12, C7_12},
        {0, C9_12, C2_11, C5_12},
        {0, C8_4, C6_4, C7_4},
        {0, C9_4, C2_3, C5_4}
};

led_config_t g_led_config = { {
// Key Matrix to LED Index
  { 0, 1, 2, 3 },
  { 4, 5, 6, 7 },
  { 8, 9, 10, 11 },
  { 12, 13, 14, 15 }
}, {
// LED Index to Physical Position
  { 0, 0 }, { 0, 21 }, { 0, 42 }, { 0, 64 },
  { 74, 0 }, { 74, 21 }, { 74, 42 }, { 74, 64 },
  { 149, 0 }, { 149, 21 }, { 149, 42 }, { 149, 64 },
  { 224, 0 }, { 224, 21 }, { 224, 42 }, { 224, 64 },
}, {
// LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
