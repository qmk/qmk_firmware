/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// clang-format off

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, J_2,	L_2,   K_2},
    {0, J_3,	L_3,   K_3},
    {0, J_4,	L_4,   K_4},
    {0, J_5,	L_5,   K_5},

    {0, J_6,	L_6,   K_6},
    {0, J_7,	L_7,   K_7},
    {0, J_8,	L_8,   K_8},
    {0, J_9,	L_9,   K_9},
    {0, J_10,	L_10,  K_10},
	
    {0, G_1,	I_1,   H_1},
    {0, G_2,	I_2,   H_2},
    {0, G_3,	I_3,   H_3},
    {0, G_4,	I_4,   H_4},
    {0, G_5,	I_5,   H_5},

    {0, G_6,	I_6,   H_6},
    {0, G_7,	I_7,   H_7},
    {0, G_8,	I_8,   H_8},
    {0, G_9,	I_9,   H_9},

    {0, A_1,    C_1,   B_1},
    {0, A_2,    C_2,   B_2},
    {0, A_3,    C_3,   B_3},
    {0, A_4,    C_4,   B_4},
    {0, A_5,    C_5,   B_5},

    {0, A_6,    C_6,   B_6},
    {0, A_7,    C_7,   B_7},
    {0, A_9,    C_9,   B_9},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3 },
        {  4,  5,  6,  7,  8 }, 
        {  9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, __ },
        { 18, 19, 20, 21, 22 },
        { 23, 24, __, 25, __ }

    },
    {
        //  LED Index to Physical Position
                 {102, 0},{117, 0}, {132, 0}, {147, 0}, 
        {87,15}, {102,15},{117,15}, {132,15}, {147,15}, 
        {87,26}, {102,26},{117,26}, {132,26}, {147,32}, 
        {87,38}, {102,38},{117,38}, {132,38}, 
        {87,49}, {102,49},{117,49}, {132,49}, {147,55}, 
        {87,61}, {110,61},          {132,61},                 
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 
        1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 
        1, 1, 1, 1, 
        1, 1, 1, 1, 1, 
        1, 1,    1,         
    }
};
#endif
