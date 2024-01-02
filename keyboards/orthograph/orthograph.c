/* Copyright 2023 vladkvit
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
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
{0, A_6, B_6, C_6},
{0, A_5, B_5, C_5},
{0, A_4, B_4, C_4},
{0, A_3, B_3, C_3},
{0, A_2, B_2, C_2},
{0, A_1, B_1, C_1},

{0, D_6, E_6, F_6},
{0, D_5, E_5, F_5},
{0, D_4, E_4, F_4},
{0, D_3, E_3, F_3},
{0, D_2, E_2, F_2},
{0, D_1, E_1, F_1},

{0, G_6, H_6, I_6},
{0, G_5, H_5, I_5},
{0, G_4, H_4, I_4},
{0, G_3, H_3, I_3},
{0, G_2, H_2, I_2},
{0, G_1, H_1, I_1},

{0, A_14, B_14, C_14},
{0, A_13, B_13, C_13},
{0, A_12, B_12, C_12},
{0, A_11, B_11, C_11},
{0, A_10, B_10, C_10},
{0, A_9, B_9, C_9},

{0, D_14, E_14, F_14},
{0, D_13, E_13, F_13},
{0, D_12, E_12, F_12},
{0, D_11, E_11, F_11},
{0, D_10, E_10, F_10},
{0, D_9, E_9, F_9},

{0, G_14, H_14, I_14},
{0, G_13, H_13, I_13},
{0, G_12, H_12, I_12},
{0, G_11, H_11, I_11},
{0, G_10, H_10, I_10},
{0, G_9, H_9, I_9},

//----------------


{0, A_6, B_6, C_6},
{0, A_5, B_5, C_5},
{0, A_4, B_4, C_4},
{0, A_3, B_3, C_3},
{0, A_2, B_2, C_2},
{0, A_1, B_1, C_1},
{0, A_16, B_16, C_16},
// {0, A_15, B_15, C_15},


{0, D_6, E_6, F_6},
{0, D_5, E_5, F_5},
{0, D_4, E_4, F_4},
{0, D_3, E_3, F_3},
{0, D_2, E_2, F_2},
{0, D_1, E_1, F_1},
{0, D_16, E_16, F_16},
{0, D_15, E_15, F_15},

{0, G_6, H_6, I_6},
{0, G_5, H_5, I_5},
{0, G_4, H_4, I_4},
{0, G_3, H_3, I_3},
{0, G_2, H_2, I_2},
{0, G_1, H_1, I_1},
{0, G_16, H_16, I_16},
{0, G_15, H_15, I_15},

{0, A_14, B_14, C_14},
{0, A_13, B_13, C_13},
{0, A_12, B_12, C_12},
{0, A_11, B_11, C_11},
{0, A_10, B_10, C_10},
{0, A_9,  B_9,  C_9},
{0, A_8,  B_8, C_8},
// {0, A_7,  B_7, C_7},

{0, D_14, E_14, F_14},
{0, D_13, E_13, F_13},
{0, D_12, E_12, F_12},
{0, D_11, E_11, F_11},
{0, D_10, E_10, F_10},
{0, D_9,  E_9,  F_9},
{0, D_8, E_8, F_8},
{0, D_7, E_7, F_7},

{0, G_14, H_14, I_14},
{0, G_13, H_13, I_13},
{0, G_12, H_12, I_12},
{0, G_11, H_11, I_11},
{0, G_10, H_10, I_10},
{0, G_9, H_9, I_9},
{0, G_8, H_8, I_8},
{0, G_7, H_7, I_7}
};

#endif
