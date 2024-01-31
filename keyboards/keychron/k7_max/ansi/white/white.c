/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
    {0, E_1},
    {0, E_2},
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
    {0, E_13},
    {0, E_14},
    {0, E_16},

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
    {0, D_13},
    {0, D_14},
    {0, D_16},

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
    {0, C_14},
    {0, C_16},

    {0, B_1},
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

    {0, A_1},
    {0, A_2},
    {0, A_3},
    {0, A_7},
    {0, A_11},
    {0, A_12},
    {0, A_13},
    {0, A_14},
    {0, A_15},
    {0, A_16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, __, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, __, 29 },
        { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, __, 42, __, 43 },
        { 44, __, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, __, 55, 56, 57 },
        { 58, 59, 60, __, __, __, 61, __, __, __, 62, 63, 64, 65, 66, 67 },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {15, 0}, {30, 0}, {45, 0}, {60, 0}, {75, 0}, { 90, 0}, {105, 0}, {119, 0}, {134, 0}, {149, 0}, {164, 0}, {179, 0}, {202, 0},           {224, 0}, 
        {4,16}, {22,16}, {37,16}, {52,16}, {67,16}, {82,16}, { 97,16}, {112,16}, {127,16}, {142,16}, {157,16}, {172,16}, {187,16}, {205,16},           {224,16}, 
        {6,32}, {26,32}, {41,32}, {56,32}, {71,32}, {86,32}, {101,32}, {116,32}, {131,32}, {146,32}, {161,32}, {175,32},           {200,32},           {224,32}, 
        {9,48},          {34,48}, {49,48}, {64,48}, {78,48}, { 93,48}, {108,48}, {123,48}, {138,48}, {153,48}, {168,48},           {189,48}, {209,48}, {224,48}, 
        {2,64}, {21,64}, {39,64},                            { 95,64},                               {149,64}, {164,64}, {179,64}, {194,64}, {209,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1, 
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 
        1, 1, 1,          1,          1, 1, 1, 1, 1, 1  
    }
};
#endif
