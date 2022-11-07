/* Copyright 2022 XCStore
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "cc67.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14 },
    { 29,     28,     27,     26,     25,     24,     23,     22,     21,     20,     19,     18,     17,     16,     15 },
    { 30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43 },
    { 57,     56,     55,     54,     53,     52,     51,     50,     49,     48,     47, NO_LED,     46,     45,     44 },
    { 58,     59,     60, NO_LED, NO_LED, NO_LED,     61, NO_LED,     62,     63, NO_LED, NO_LED,     64,     65,     66 }
}, {
    // Key matrix (0 -> 66)
    {0  ,  0}, {15 ,  0}, {30 ,  0}, {45 ,  0}, {60 ,  0}, {75 ,  0}, {90 ,  0}, {105,  0}, {119,  0}, {134,  0}, {149,  0}, {164,  0}, {179,  0}, {202,  0}, {224,  0},
    {224, 16}, {205, 16}, {187, 16}, {172, 16}, {157, 16}, {142, 16}, {127, 16}, {112, 16}, {97 , 16}, {82 , 16}, {67 , 16}, {52 , 16}, {37 , 16}, {22 , 16}, {4  , 16},
    {6  , 32}, {26 , 32}, {41 , 32}, {56 , 32}, {71 , 32}, {86 , 32}, {101, 32}, {116, 32}, {131, 32}, {146, 32}, {161, 32}, {175, 32}, {200, 32},            {224, 32},
    {224, 48}, {209, 48}, {189, 48}, {168, 48}, {153, 48}, {138, 48}, {123, 48}, {108, 48}, {93 , 48}, {78 , 48}, {63 , 48},            {49 , 48}, {34 , 48}, {9  , 48},
    {2  , 64}, {21 , 64}, {39 , 64},                                  {95 , 64},            {151, 64}, {170, 64},                       {194, 64}, {209, 64}, {224, 64},

    // Underglow (67 -> 80)
    {217, 28}, {198, 48}, {161, 48}, {131, 48}, {101, 48}, {71 , 48}, {41 , 48}, {19 , 24}, {37 ,  0}, {67 ,  0}, {97 ,  0}, {127,  0}, {157,  0}, {187,  0},
}, {
    // Key matrix (0 -> 66)
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    4,
    4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 1,
    1, 1, 1,          4,    1, 1,       4, 4, 4,

    // Underglow (67 -> 80)
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif
