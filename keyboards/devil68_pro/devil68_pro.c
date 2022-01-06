/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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

#include "devil68_pro.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {       0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12, NO_LED,     13,     14 },
    {      15, NO_LED,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29 },
    {      30, NO_LED,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43 },
    {  NO_LED,     44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54, NO_LED,     55,     56,     57 },
    {      58,     59, NO_LED,     60, NO_LED, NO_LED,     61, NO_LED, NO_LED, NO_LED,     64,     62,     63,     65,     66,     67 }
}, {
    // Key matrix (0 -> 67)
    {0  ,  0}, {15 ,  0}, {30 ,  0}, {45 ,  0}, {60 ,  0}, {75 ,  0}, {90 ,  0}, {105,  0}, {120,  0}, {135,  0}, {150,  0}, {165,  0}, {180,  0},            {202,  0}, {224,  0},
    {3  , 16},            {21 , 16}, {36 , 16}, {51 , 16}, {66 , 16}, {81 , 16}, {96 , 16}, {111, 16}, {126, 16}, {141, 16}, {156, 16}, {171, 16}, {186, 16}, {205, 16}, {224, 16},
    {5  , 32},            {25 , 32}, {40 , 32}, {55 , 32}, {70 , 32}, {85 , 32}, {100, 32}, {115, 32}, {130, 32}, {145, 32}, {160, 32}, {175, 32}, {200, 32},            {224, 32},
               {8  , 48}, {31 , 48}, {46 , 48}, {61 , 48}, {76 , 48}, {91 , 48}, {106, 48}, {121, 48}, {136, 48}, {151, 48}, {166, 48},            {188, 48}, {210, 48}, {224, 48},
    {2  , 64}, {19 , 64},            {36 , 64},                       {96 , 64},                                  {149, 64}, {164, 64}, {179, 64}, {194, 64}, {209, 64}, {224, 64},

    // Underglow (68 -> 85)
    {210, 60}, {186, 12}, {158, 12}, {130, 12}, {101, 12}, {71 , 12}, {39 , 12}, {13 , 12}, {13 , 35},
    {13 , 12}, {39 , 12}, {71 , 12}, {101, 12}, {130, 12}, {158, 12}, {186, 12}, {210, 12}, {210, 35},
}, {
    // Key matrix (0 -> 67)
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    8,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    4,
       1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4, 4,
    1, 1,    1,       4,          1, 1, 1, 4, 4, 4,

    // Underglow (68 -> 85)
    2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif
