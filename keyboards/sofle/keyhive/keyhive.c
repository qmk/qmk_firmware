/* Copyright
 *   2021 solartempest
 *   2021 QMK
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

#include "keyhive.h"
#ifdef RGB_MATRIX_ENABLE
// Physical Layout
// Columns
// 0  1  2  3  4  5  6  7  8  9  10 11 12 13
//                                           ROWS
// 12 13 22 23 32 33       33 32 23 22 13 12  0
//    02    03    04       04    03    02
// 11 14 21 24 31 34       34 31 24 21 14 11  1
//                01       01
// 10 15 20 25 30 35       35 30 25 20 15 10  2
//
// 09 16 19 26 29 36       36 29 26 19 16 09  3
//
//     08 17 18 27 28     28 27 18 17 08      4
//    07    06    05       05    06    07

// clang-format off

led_config_t g_led_config = {
    {
        {  11,  12,  21,  22,  31,  32 },
        {  10,  13,  20,  23,  30,  33 },
        {  9,   14,  19,  24,  29,  34},
        {  8,   15,  18,  25,  28,  35},
        {  7,   16,  17,  26,  27,  NO_LED },
        {  47,  48,  57,  58,  67,  68},
        {  46,  49,  56,  59,  66,  69},
        {  45,  50,  55,  60,  65,  70},
        {  44,  51,  54,  61,  64,  71},
        {  43,  52,  53,  62,  63,  NO_LED }
    },
    {
       // Left side underglow
        {96, 40}, {16, 20}, {48, 10}, {80, 18}, {88, 60}, {56, 57}, {24,60},
        // Left side Matrix
        {32, 57}, { 0, 48}, { 0, 36}, { 0, 24}, { 0, 12},
        {16, 12}, {16, 24}, {16, 36}, {16, 48}, {48, 55},
        {64, 57}, {32, 45}, {32, 33}, {32, 21}, {32,  9},
        {48,  7}, {48, 19}, {48, 31}, {48, 43}, {80, 59},
        {96, 64}, {64, 45}, {64, 33}, {64, 21}, {64,  9},
        {80, 10}, {80, 22}, {80, 34}, {80, 47},


        // Right side underglow
        {128, 40}, {208, 20}, {176, 10}, {144, 18}, {136, 60}, {168, 57}, {200,60},
        // Right side Matrix
        {192, 57}, {224, 48}, {224, 36}, {224, 24}, {224, 12},
        {208, 12}, {208, 24}, {208, 36}, {208, 48}, {176, 55},
        {160, 57}, {192, 45}, {192, 33}, {192, 21}, {192,  9},
        {176,  7}, {176, 19}, {176, 31}, {176, 43}, {144, 59},
        {128, 64}, {160, 45}, {160, 33}, {160, 21}, {160,  9},
        {144, 10}, {144, 22}, {144, 34}, {144, 47},
    },
    {
        LED_FLAG_NONE, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_NONE, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif
