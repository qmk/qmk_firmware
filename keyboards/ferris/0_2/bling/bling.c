/*
Copyright 2021 Pierre Chevalier <pierrechevalier83@gmail.com>

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

#include "drivers/led/issi/is31fl3731.h"

/*
|      Left        ||    Right       |
|    | 3  |   | 0  || 0 |   | 3  |   |
| 5  |    |   |    ||   |   |    | 6 |
|    |    |   |    ||   |   |    |   |
|    |    |   | 1  || 1 |   |    |   |
|    | 4  |   |    ||   |   | 4  |   |
| 6  |    |   | 2  || 2 |   |    | 5 |
*/
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |      G location
     *   |  |      |      B location
     *   |  |      |      | */
    {0, C9_10, C8_10, C7_10},  // Left  RGB 5
    {0, C9_12, C8_12, C7_12},  // Left  RGB 3
    {0, C9_15, C8_15, C6_14},  // Left  RGB 0
    {1, C1_2, C2_2, C4_3},     // Right RGB 0
    {1, C1_5, C2_5, C3_5},     // Right RGB 3
    {1, C1_8, C2_8, C3_8},     // Right RGB 6
    {1, C1_7, C2_7, C3_7},     // Right RGB 5
    {1, C1_6, C2_6, C3_6},     // Right RGB 4
    {1, C1_3, C2_3, C3_3},     // Right RGB 1
    {1, C1_4, C2_4, C3_4},     // Right RGB 2
    {0, C9_13, C8_13, C7_13},  // Left  RGB 2
    {0, C9_14, C8_14, C7_14},  // Left  RGB 1
    {0, C9_11, C8_11, C7_11},  // Left  RGB 4
    {0, C9_9, C8_9, C7_9},     // Left  RGB 6
};
// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    }, {
        // LED Index to Physical Position. The unit is roughly milimiters in the real world
        //    |      Left      ||    Right        |
        // x->| 10  | 32  | 64 || 160 | 192 | 214 |
        // y  |_____|_____|____||_____|_____|_____|
        // 0  |     | 1   | 2  || 3   |   4 |     |
        // 16 | 0   |     |    ||     |     | 5   |
        // 35 |     |     | 11 || 8   |     |     |
        // 45 |     | 12  |    ||     |   7 |     |
        // 50 | 13  |     | 10 || 9   |     | 6   |
        // 0         1        2         3         4         5
        {10, 16}, {32, 0}, {64, 0}, {160, 0}, {192, 0}, {214, 16},
        //  6          7          8          9
        {214, 50}, {192, 45}, {160, 35}, {160, 50},
        //  10       11        12       13
        {64, 50}, {64, 35}, {32, 45}, {10, 50},
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
