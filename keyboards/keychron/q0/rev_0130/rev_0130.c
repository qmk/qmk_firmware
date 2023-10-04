/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

// clang-format off

const snled27351_led_t PROGMEM g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, F_5,    D_5,    E_5}, // 0
    {0, I_5,    G_5,    H_5}, // 1
    {0, L_5,    J_5,    K_5}, // 2
    {0, C_5,    A_5,    B_5}, // 3

    {0, F_4,    D_4,    E_4}, // 4
    {0, I_4,    G_4,    H_4}, // 5
    {0, L_4,    J_4,    K_4}, // 6
    {0, C_4,    A_4,    B_4}, // 7

    {0, F_6,    D_6,    E_6}, // 8
    {0, I_6,    G_6,    H_6}, // 9
    {0, L_6,    J_6,    K_6}, // 10

    {0, F_3,    D_3,    E_3}, // 11
    {0, I_3,    G_3,    H_3}, // 12
    {0, L_3,    J_3,    K_3}, // 13
    {0, C_6,    A_6,    B_6}, // 14

    {0, F_2,    D_2,    E_2}, // 15
    {0, I_2,    G_2,    H_2}, // 16
    {0, L_2,    J_2,    K_2}, // 17

    {0, F_1,    D_1,    E_1}, // 18
    {0, L_1,    J_1,    K_1}, // 19
    {0, C_2,    A_2,    B_2}, // 20
};
#endif // RGB_MATRIX_ENABLE
