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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.g
 */

#include "quantum.h"

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to snled27351manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, J_1},
    {0, J_2},
    {0, J_3},
    {0, J_4},
    {0, J_5},
    {0, J_6},
    {0, J_7},
    {0, J_8},
    {0, J_9},
    {0, J_10},
    {0, J_11},
    {0, J_12},
    {0, J_13},
    {0, J_14},

    {0, G_1},
    {0, G_2},
    {0, G_3},
    {0, G_4},
    {0, G_5},
    {0, G_6},
    {0, G_7},
    {0, G_8},
    {0, G_9},
    {0, G_10},
    {0, G_11},
    {0, G_12},
    {0, G_13},
    {0, G_14},

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

    {0, A_1},
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
    {0, A_14},

    {0, A_15},
    {0, A_16},
    {0, D_15},
    {0, D_16},
    {0, G_15},
    {0, G_16},
    {0, J_15},
    {0, J_16},
};
#endif
