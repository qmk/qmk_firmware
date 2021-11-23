/* Copyright 2021 TW59420 <https://github.com/TW59420>
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

#include "mw65_rgb.h"

led_config_t g_led_config = { {
    { 82,     81,     80,     79,     78,     77,     76,     75,     74,     73,     72,     71,     70,     69,     68 },
    { 53,     54,     55,     56,     57,     58,     59,     60,     61,     62,     63,     64,     65,     66,     67 },
    { 52,     51,     50,     49,     48,     47,     46,     45,     44,     43,     42,     41, NO_LED,     40,     39 },
    { 25, NO_LED,     26,     27,     28,     29,     30,     31,     32,     33,     34,     35,     36,     37,     38 },
    { 24,     23,     22, NO_LED, NO_LED, NO_LED,     21, NO_LED, NO_LED, NO_LED,     20,     19,     18,     17,     16 }
}, {
    //Underglow (0 -> 15)
    {180, 52}, {146, 52}, {86 , 52}, {45 , 52}, {7  , 52}, {7  , 36}, {7  , 20}, {7  ,  4}, {45 ,  4}, {86 ,  4}, {146,  4}, {180,  4}, {217,  4}, {217, 20}, {217, 36}, {217, 52},

    //Key matrix (16 -> 83)
    {224, 64}, {209, 64}, {194, 64}, {173, 64}, {156, 64},                                  {96 , 64},                                  {36 , 64}, {19 , 64}, {2  , 64},
    {8  , 48}, {31 , 48}, {46 , 48}, {61 , 48}, {76 , 48}, {91 , 48}, {106, 48}, {121, 48}, {136, 48}, {151, 48}, {166, 48}, {188, 48}, {210, 48},            {224, 48},
    {224, 32}, {200, 32},            {175, 32}, {160, 32}, {145, 32}, {130, 32}, {115, 32}, {100, 32}, {85 , 32}, {70 , 32}, {55 , 32}, {40 , 32}, {25 , 32}, {5  , 32},
    {3  , 16}, {21 , 16}, {36 , 16}, {51 , 16}, {66 , 16}, {81 , 16}, {96 , 16}, {111, 16}, {126, 16}, {141, 16}, {156, 16}, {171, 16}, {186, 16}, {205, 16}, {224, 16},
    {224,  0}, {202,  0}, {180,  0}, {165,  0}, {150,  0}, {135,  0}, {120,  0}, {105,  0}, {90 ,  0}, {75 ,  0}, {60 ,  0}, {45 ,  0}, {30 ,  0}, {15 ,  0}, {0  ,  0},
}, {
    //Underglow (0 -> 15)
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

    //Key matrix (16 -> 82)
    4, 4, 4, 1, 1,          4,          1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,    4,
    4, 1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
} };
