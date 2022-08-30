/* Copyright 2021 Mss Studio
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

#include "m63_rgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13 },
    { 14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27 },
    { 28,     29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39, NO_LED,     40 },
    { 41,     42,     43,     44,     45,     46,     47,     48,     49,     50,     51, NO_LED,     52,     53 },
    { 54,     55,     56, NO_LED, NO_LED,     57, NO_LED, NO_LED, NO_LED,     58,     59,     60,     61,     62 }
}, {
    // Key matrix (0 -> 62)
    {0  ,  0}, {16 ,  0}, {32 ,  0}, {48 ,  0}, {64 ,  0}, {80 ,  0}, {96 ,  0}, {112,  0}, {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {216,  0},
    {4  , 16}, {24 , 16}, {40 , 16}, {56 , 16}, {72 , 16}, {88 , 16}, {104, 16}, {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16},
    {6  , 32}, {28 , 32}, {44 , 32}, {60 , 32}, {76 , 32}, {92 , 32}, {108, 32}, {124, 32}, {140, 32}, {156, 32}, {172, 32}, {188, 32},            {214, 32},
    {10 , 48}, {36 , 48}, {52 , 48}, {68 , 48}, {84 , 48}, {100, 48}, {116, 48}, {132, 48}, {148, 48}, {164, 48}, {186, 48},            {208, 48}, {224, 48},
    {2  , 64}, {22 , 64}, {42 , 64},                       {102, 64},                                  {160, 64}, {176, 64}, {192, 64}, {208, 64}, {224, 64},

    // Underglow (63 -> 74)
    {216, 56}, {181, 57}, {138, 59}, {105, 58}, {52 , 60}, {10 , 60},
    {20 , 12}, {54 , 12}, {102, 10}, {145, 13}, {182,  9}, {211, 10},
}, {
    // Key matrix (0 -> 62)
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    4, 4,
    1, 1, 1,       4,          1, 1, 4, 4, 4,

    // Underglow (63 -> 74)
    2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2
} };
#endif
