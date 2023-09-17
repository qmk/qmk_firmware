/* Copyright 2021 Carlos Martins
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

led_config_t g_led_config = {
    {
        {  4,  5,  14,  15,  24,  25 },
        {  3,  6,  13,  16,  23,  26 },
        {  2,   7,  12,  17,  21,  27},
        {  1,   8,  11,  18,  21,  28},
        {  0,   9,  10,  19,  20,  NO_LED },
        {  40,  41,  50,  51,  60,  61},
        {  39,  42,  49,  52,  59,  62},
        {  38,  43,  48,  53,  58,  63},
        {  37,  44,  47,  54,  57,  64},
        {  36,  45,  46,  55,  56,  NO_LED }
    },
    {
       // I dont think any of this actuall matters, as its pixel cocodinates on the board...
       //https://gist.github.com/vinorodrigues/75b376e937f9e875244dff77fef2f8d7
       // {0,0} = top left
       // {224, 64} = bottom right
       // Left side underglow
        //{96, 40}, {16, 20}, {48, 10}, {80, 18}, {88, 60}, {56, 57}, {24,60},
        // // Left side Matrix
        // {32, 57}, { 0, 48}, { 0, 36}, { 0, 24}, { 0, 12},
        // {16, 12}, {16, 24}, {16, 36}, {16, 48}, {48, 55},
        // {64, 57}, {32, 45}, {32, 33}, {32, 21}, {32,  9},
        // {48,  7}, {48, 19}, {48, 31}, {48, 43}, {80, 59},
        // {96, 64}, {64, 45}, {64, 33}, {64, 21}, {64,  9},
        // {80, 10}, {80, 22}, {80, 34}, {80, 47},


        // // Right side underglow
        // //{128, 40}, {208, 20}, {176, 10}, {144, 18}, {136, 60}, {168, 57}, {200,60},
        // // Right side Matrix
        // {192, 57}, {224, 48}, {224, 36}, {224, 24}, {224, 12},
        // {208, 12}, {208, 24}, {208, 36}, {208, 48}, {176, 55},
        // {160, 57}, {192, 45}, {192, 33}, {192, 21}, {192,  9},
        // {176,  7}, {176, 19}, {176, 31}, {176, 43}, {144, 59},
        // {128, 64}, {160, 45}, {160, 33}, {160, 21}, {160,  9},
        // {144, 10}, {144, 22}, {144, 34}, {144, 47},
        {16, 13}, {32, 13}, {48, 13}, {64, 13}, {80, 13}, {128, 13}, {144, 13}, {160, 13}, {176, 13}, {192, 13}, {208, 13}, {224, 13},
        {16, 26}, {32, 26}, {48, 26}, {64, 26}, {80, 26}, {128, 26}, {144, 26}, {160, 26}, {176, 26}, {192, 26}, {208, 26}, {224, 26},
        {16, 38}, {32, 38}, {48, 38}, {64, 38}, {80, 38}, {128, 38}, {144, 38}, {160, 38}, {176, 38}, {192, 38}, {208, 38}, {224, 38},
        {16, 51}, {32, 51}, {48, 51}, {64, 51}, {80, 51}, {128, 51}, {144, 51}, {160, 51}, {176, 51}, {192, 51}, {208, 51}, {224, 51},
        {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64}, {160, 64}, {176, 64}, {192, 64},
    },
    {
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif
