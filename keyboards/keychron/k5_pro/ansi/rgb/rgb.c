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
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to snled27351manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, G_1,    I_1,    H_1},
    {0, G_2,    I_2,    H_2},
    {0, G_3,    I_3,    H_3},
    {0, G_4,    I_4,    H_4},
    {0, G_5,    I_5,    H_5},
    {0, G_6,    I_6,    H_6},
    {0, G_7,    I_7,    H_7},
    {0, G_8,    I_8,    H_8},
    {0, G_9,    I_9,    H_9},
    {0, G_10,   I_10,   H_10},
    {0, G_11,   I_11,   H_11},
    {0, G_12,   I_12,   H_12},
    {0, G_13,   I_13,   H_13},
    {0, G_15,   I_15,   H_15},
    {0, G_16,   I_16,   H_16},
    {0, G_14,   I_14,   H_14},
    {1, G_13,   I_13,   H_13},
    {1, G_15,   I_15,   H_15},
    {1, G_16,   I_16,   H_16},
    {1, A_15,   C_15,   B_15},

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
    {0, D_14,   F_14,   E_14},
    {0, D_15,   F_15,   E_15},
    {0, D_16,   F_16,   E_16},
    {0, J_7,    L_7,    K_7},
    {0, J_8,    L_8,    K_8},
    {0, J_9,    L_9,    K_9},
    {0, J_10,   L_10,   K_10},
    {0, J_11,   L_11,   K_11},

    {0, C_1,    A_1,    B_1},
    {0, C_2,    A_2,    B_2},
    {0, C_3,    A_3,    B_3},
    {0, C_4,    A_4,    B_4},
    {0, C_5,    A_5,    B_5},
    {0, C_6,    A_6,    B_6},
    {0, C_7,    A_7,    B_7},
    {0, C_8,    A_8,    B_8},
    {0, C_9,    A_9,    B_9},
    {0, C_10,   A_10,   B_10},
    {0, C_11,   A_11,   B_11},
    {0, C_12,   A_12,   B_12},
    {0, C_13,   A_13,   B_13},
    {0, C_14,   A_14,   B_14},
    {0, C_15,   A_15,   B_15},
    {0, C_16,   A_16,   B_16},
    {0, J_12,   L_12,   K_12},
    {0, J_13,   L_13,   K_13},
    {0, J_14,   L_14,   K_14},
    {0, J_15,   L_15,   K_15},
    {0, J_16,   L_16,   K_16},

    {1, G_1,    I_1,    H_1},
    {1, G_2,    I_2,    H_2},
    {1, G_3,    I_3,    H_3},
    {1, G_4,    I_4,    H_4},
    {1, G_5,    I_5,    H_5},
    {1, G_6,    I_6,    H_6},
    {1, G_7,    I_7,    H_7},
    {1, G_8,    I_8,    H_8},
    {1, G_9,    I_9,    H_9},
    {1, G_10,   I_10,   H_10},
    {1, G_11,   I_11,   H_11},
    {1, G_12,   I_12,   H_12},
    {1, G_14,   I_14,   H_14},
    {1, J_7,    L_7,    K_7},
    {1, J_8,    L_8,    K_8},
    {1, J_9,    L_9,    K_9},

    {1, A_1,    C_1,    B_1},
    {1, A_3,    C_3,    B_3},
    {1, A_4,    C_4,    B_4},
    {1, A_5,    C_5,    B_5},
    {1, A_6,    C_6,    B_6},
    {1, A_7,    C_7,    B_7},
    {1, A_8,    C_8,    B_8},
    {1, A_9,    C_9,    B_9},
    {1, A_10,   C_10,   B_10},
    {1, A_11,   C_11,   B_11},
    {1, A_12,   C_12,   B_12},
    {1, A_14,   C_14,   B_14},
    {1, A_16,   C_16,   B_16},
    {1, J_10,   L_10,   K_10},
    {1, J_11,   L_11,   K_11},
    {1, J_12,   L_12,   K_12},
    {1, J_13,   L_13,   K_13},

    {1, D_1,    F_1,    E_1},
    {1, D_2,    F_2,    E_2},
    {1, D_3,    F_3,    E_3},
    {1, D_7,    F_7,    E_7},
    {1, D_11,   F_11,   E_11},
    {1, D_12,   F_12,   E_12},
    {1, D_13,   F_13,   E_13},
    {1, D_14,   F_14,   E_14},
    {1, D_15,   F_15,   E_15},
    {1, D_16,   F_16,   E_16},
    {1, J_14,   L_14,   K_14},
    {1, J_15,   L_15,   K_15},
    {1, J_16,   L_16,   K_16},
};
#endif
