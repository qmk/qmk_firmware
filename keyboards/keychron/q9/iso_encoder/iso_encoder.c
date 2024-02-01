/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, L_16, J_16, K_16}, // Tab
    {0, L_15, J_15, K_15}, // Q
    {0, L_14, J_14, K_14}, // W
    {0, L_13, J_13, K_13}, // E
    {0, L_12, J_12, K_12}, // R
    {0, L_11, J_11, K_11}, // T
    {0, L_10, J_10, K_10}, // Y
    {0, L_9,  J_9,  K_9},  // U
    {0, L_8,  J_8,  K_8},  // I
    {0, L_7,  J_7,  K_7},  // O
    {0, L_6,  J_6,  K_6},  // P
    {0, L_5,  J_5,  K_5},  // [
    {0, L_4,  J_4,  K_4},  // ]
    // {0, L_2,  J_2,  K_2},  // Mute

    {0, C_16, A_16, B_16}, // CapsLock
    {0, C_15, A_15, B_15}, // A
    {0, C_14, A_14, B_14}, // S
    {0, C_13, A_13, B_13}, // D
    {0, C_12, A_12, B_12}, // F
    {0, C_11, A_11, B_11}, // G
    {0, C_10, A_10, B_10}, // H
    {0, C_9,  A_9,  B_9},  // J
    {0, C_8,  A_8,  B_8},  // K
    {0, C_7,  A_7,  B_7},  // L
    {0, C_6,  A_6,  B_6},  // ;
    {0, C_5,  A_5,  B_5},  // '
    {0, C_3,  A_3,  B_3},  // #
    {0, L_3,  J_3,  K_3},  // Enter
    {0, C_2,  A_2,  B_2},  // Home

    {0, I_16, G_16, H_16}, // LeftShift
    {0, I_15, G_15, H_15}, // |
    {0, I_14, G_14, H_14}, // Z
    {0, I_13, G_13, H_13}, // X
    {0, I_12, G_12, H_12}, // C
    {0, I_11, G_11, H_11}, // V
    {0, I_10, G_10, H_10}, // B
    {0, I_9,  G_9,  H_9},  // N
    {0, I_8,  G_8,  H_8},  // M
    {0, I_7,  G_7,  H_7},  // ,
    {0, I_6,  G_6,  H_6},  // .
    {0, I_5,  G_5,  H_5},  // ?
    {0, I_3,  G_3,  H_3},  // RightShift
    {0, I_2,  G_2,  H_2},  // Up

    {0, F_16, D_16, E_16}, // LeftCtrl
    {0, F_15, D_15, E_15}, // LeftWin
    {0, F_14, D_14, E_14}, // LeftAlt
    {0, F_10, D_10, E_10}, // Space
    {0, F_6,  D_6,  E_6},  // RightAlt
    {0, F_5,  D_5,  E_5},  // Fn1
    {0, F_4,  D_4,  E_4},  // Fn2
    {0, F_3,  D_3,  E_3},  // Left
    {0, F_2,  D_2,  E_2},  // Down
    {0, C_4,  A_4,  B_4}   // Right
};

#endif // RGB_MATRIX_ENABLE
