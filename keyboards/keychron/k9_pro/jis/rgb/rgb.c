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
#ifdef RGB_MATRIX_ENABLE
const ckled2001_led g_ckled2001_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to CKLED2001 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, A_1,    C_1,    B_1},
    {0, A_2,    C_2,    B_2},
    {0, A_3,    C_3,    B_3},
    {0, A_4,    C_4,    B_4},
    {0, A_5,    C_5,    B_5},
    {0, A_6,    C_6,    B_6},
    {0, A_7,    C_7,    B_7},
    {0, A_8,    C_8,    B_8},
    {0, A_9,    C_9,    B_9},
    {0, A_10,   C_10,   B_10},
    {0, A_11,   C_11,   B_11},
    {0, A_12,   C_12,   B_12},
    {0, A_13,   C_13,   B_13},
    {0, A_14,   C_14,   B_14},
    {0, A_15,   C_15,   B_15},

    {0, D_1,    F_1,    E_1},
    {0, D_2,    F_2,    E_2},
    {0, D_3,    F_3,    E_3},
    {0, D_4,    F_4,    E_4},
    {0, D_5,    F_5,    E_5},
    {0, D_6,    F_6,    E_6},
    {0, D_7,    F_7,    E_7},
    {0, D_8,    F_8,    E_8},
    {0, D_9,    F_9,    E_9},
    {0, D_10,   F_10,   E_10},
    {0, D_11,   F_11,   E_11},
    {0, D_12,   F_12,   E_12},
    {0, D_13,   F_13,   E_13},

    {1, F_1,    D_1,    E_1},
    {1, F_2,    D_2,    E_2},
    {1, F_3,    D_3,    E_3},
    {1, F_4,    D_4,    E_4},
    {1, F_5,    D_5,    E_5},
    {1, F_6,    D_6,    E_6},
    {1, F_7,    D_7,    E_7},
    {1, F_8,    D_8,    E_8},
    {1, F_9,    D_9,    E_9},
    {1, F_10,   D_10,   E_10},
    {1, F_11,   D_11,   E_11},
    {1, F_12,   D_12,   E_12},
    {1, F_14,   D_14,   E_14},
    {0, D_14,   F_14,   E_14},

    {1, C_1,    A_1,    B_1},
    {1, C_3,    A_3,    B_3},
    {1, C_4,    A_4,    B_4},
    {1, C_5,    A_5,    B_5},
    {1, C_6,    A_6,    B_6},
    {1, C_7,    A_7,    B_7},
    {1, C_8,    A_8,    B_8},
    {1, C_9,    A_9,    B_9},
    {1, C_10,   A_10,   B_10},
    {1, C_11,   A_11,   B_11},
    {1, C_12,   A_12,   B_12},
    {1, C_13,   A_13,   B_13},
    {1, C_14,   A_14,   B_14},

    {1, I_1,    G_1,    H_1},
    {1, I_2,    G_2,    H_2},
    {1, I_3,    G_3,    H_3},
    {1, I_4,    G_4,    H_4},
    {1, I_7,    G_7,    H_7},
    {1, I_10,   G_10,   H_10},
    {1, I_11,   G_11,   H_11},
    {1, I_12,   G_12,   H_12},
    {1, I_13,   G_13,   H_13},
    {1, I_14,   G_14,   H_14},
};
#endif
