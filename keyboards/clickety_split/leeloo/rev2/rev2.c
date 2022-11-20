/* Copyright 2022 Clickety Split Ltd.
 *                https://clicketysplit.ca
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

#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 34 33 26 25 16 15   0
  // 04   03   0    01
  // 35 32 27 24 17 14   1
  //
  // 36 31 28 23 18 13   2
  // 05   06   07   08
  // 37 30 29 22 19 12   3
  //
  //    21 20 11 10 09   4

  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 15 16 25 26 33 34   5
  // 01   02   03   04
  // 14 17 24 27 32 35   6
  //
  // 13 18 23 28 31 36   7
  // 08   07   06   05
  // 12 19 22 29 30 37   8
  //
  // 09 10 11 20 21      9
  
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 34 33 26 25 16 15       15 16 25 26 33 34  0
  //   03   02   01             01   02   03
  // 35 32 27 24 17 14       14 17 24 27 32 35  1
  // 04                                     04
  // 36 31 28 23 18 13       13 18 23 28 31 36  2
  // 05                                     05
  // 37 30 29 22 19 12       12 19 22 29 30 37  3
  //   06   07   08             08   07   06
  //       21 20 11 10 09 09 10 11 20 21      4

led_config_t g_led_config = {
    {
        {     33,     32,     25,     24,     15,     14 },
        {     34,     31,     26,     23,     16,     13 },
        {     35,     30,     27,     22,     17,     12 },
        {     36,     29,     28,     21,     18,     11 },
        { NO_LED,     20,     19,     10,      9,      8 },
        {     70,     69,     62,     61,     52,     51 },
        {     71,     68,     63,     60,     53,     50 },
        {     72,     67,     64,     59,     54,     49 },
        {     73,     66,     65,     58,     55,     48 },
        { NO_LED,     57,     56,     47,     46,     45 }
    }, 
    {
        {86,8},{52,8},{17,8},{0,24},{0,40},{17,56},{52,56},{86,56},
        {103,48},{103,64},
        {86,64},{86,48},{86,32},{86,16},{86,0},
        {69,0},{69,16},{69,32},{69,48},{69,64},
        {52,64},{52,48},{52,32},{52,16},{52,0},
        {34,0},{34,16},{34,32},{34,48},
        {17,48},{17,32},{17,16},{17,0},
        {0,0},{0,16},{0,32},{0,48},

        {137,8},{172,8},{206,8},{224,24},{224,40},{206,56},{172,56},{137,56},
        {120,48},{120,64},
        {137,64},{137,48},{137,32},{137,16},{137,0},
        {155,0},{155,16},{155,32},{155,48},{155,64},
        {172,64},{172,48},{172,32},{172,16},{172,0},
        {189,0},{189,16},{189,32},{189,48},
        {206,48},{206,32},{206,16},{206,0},
        {224,0},{224,16},{224,32},{224,48}
    }, 
    {
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,

        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};

#endif