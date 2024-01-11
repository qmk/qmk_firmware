/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, A_1},
    {0, A_2},
    {0, A_3},
    {0, A_4},
    {0, A_5},
    {0, A_6},
    {0, A_7},
    {0, A_8},
    {0, A_9},
    {0, A_10},
    {0, A_11},
    {0, A_12},
    {0, A_13},
    {0, A_14},
    {0, A_15},
    {0, A_16},

    {0, B_1},
    {0, B_2},
    {0, B_3},
    {0, B_4},
    {0, B_5},
    {0, B_6},
    {0, B_7},
    {0, B_8},
    {0, B_9},
    {0, B_10},
    {0, B_11},
    {0, B_12},
    {0, B_13},
    {0, B_14},
    {0, B_16},

    {0, C_1},
    {0, C_2},
    {0, C_3},
    {0, C_4},
    {0, C_5},
    {0, C_6},
    {0, C_7},
    {0, C_8},
    {0, C_9},
    {0, C_10},
    {0, C_11},
    {0, C_12},
    {0, C_13},
    {0, C_14},
    {0, C_16},

    {0, D_1},
    {0, D_2},
    {0, D_3},
    {0, D_4},
    {0, D_5},
    {0, D_6},
    {0, D_7},
    {0, D_8},
    {0, D_9},
    {0, D_10},
    {0, D_11},
    {0, D_12},
    {0, D_14},
    {0, D_16},

    {0, E_1},
    {0, E_3},
    {0, E_4},
    {0, E_5},
    {0, E_6},
    {0, E_7},
    {0, E_8},
    {0, E_9},
    {0, E_10},
    {0, E_11},
    {0, E_12},
    {0, E_14},
    {0, E_15},
    {0, E_16},

    {0, F_1},
    {0, F_2},
    {0, F_3},
    {0, F_7},
    {0, F_11},
    {0, F_12},
    {0, F_13},
    {0, F_14},
    {0, F_15},
    {0, F_16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14,     15 },
        { 16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     __,     30 },
        { 31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     44,     __,     45 },
        { 46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57,     __,     58,     __,     59 },
        { 60,     __,     61,     62,     63,     64,     65,     66,     67,     68,     69,     70,     __,     71,     72,     73 },
        { 74,     75,     76,     __,     __,     __,     77,     __,     __,     __,     78,     79,     80,     81,     82,     83 }
    },
     {
        // LED Index to Physical Position
        {0, 0}, {14, 0}, {29, 0}, {44, 0}, {59, 0}, {74, 0}, { 89,  0}, {104,  0}, {119,  0}, {134,  0}, {149,  0}, {164,  0}, {179,  0}, {194,  0}, {209,  0}, {223,  0},
        {0,12}, {14,12}, {29,12}, {44,12}, {59,12}, {74,12}, { 89, 12}, {104, 12}, {119, 12}, {134, 12}, {149, 12}, {164, 12}, {179, 12}, {201, 12},            {223, 12},
        {3,25}, {22,25}, {37,25}, {52,25}, {67,25}, {82,25}, { 97, 25}, {112, 25}, {126, 25}, {141, 25}, {156, 25}, {171, 25}, {186, 25}, {205, 25},            {223, 25},
        {5,38}, {26,38}, {41,38}, {55,38}, {70,38}, {85,38}, {100, 38}, {115, 38}, {130, 38}, {145, 38}, {160, 38}, {175, 38},            {199, 38},            {223, 38},
        {9,51},          {33,51}, {48,51}, {63,51}, {78,51}, { 93, 51}, {108, 51}, {123, 51}, {138, 51}, {153, 51}, {168, 51},            {188, 51}, {209, 51}, {223, 51},
        {1,64}, {20,64}, {39,64},                            { 95, 64},                                  {149, 64}, {164, 64}, {179, 64}, {194, 64}, {209, 64}, {223, 64}
    },
    {
        // RGB LED Index to Flag
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,
        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,        4,
        4,        4,   4,   4,   4,   4,   4,   4,   4,   4,   4,        4,   4,   4,
        4,   4,   4,                  4,                  4,   4,   4,   4,   4,   4
    }
};
#endif
