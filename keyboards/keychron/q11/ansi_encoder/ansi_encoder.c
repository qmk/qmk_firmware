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

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, A_2,  C_2,  B_2},  // ESC
    {0, A_3,  C_3,  B_3},  // F1
    {0, A_4,  C_4,  B_4},  // F2
    {0, A_5,  C_5,  B_5},  // F3
    {0, A_6,  C_6,  B_6},  // F4
    {0, A_7,  C_7,  B_7},  // F5
    {0, A_8,  C_8,  B_8},  // F6

    {0, D_1,  F_1,  E_1},  // M1
    {0, D_2,  F_2,  E_2},  // `~
    {0, D_3,  F_3,  E_3},  // 1!
    {0, D_4,  F_4,  E_4},  // 2@
    {0, D_5,  F_5,  E_5},  // 3#
    {0, D_6,  F_6,  E_6},  // 4$
    {0, D_7,  F_7,  E_7},  // 5%
    {0, D_8,  F_8,  E_8},  // 6^

    {0, G_1,  I_1,  H_1},  // M2
    {0, G_2,  I_2,  H_2},  // TAB
    {0, G_3,  I_3,  H_3},  // Q
    {0, G_4,  I_4,  H_4},  // W
    {0, G_5,  I_5,  H_5},  // E
    {0, G_6,  I_6,  H_6},  // R
    {0, G_7,  I_7,  H_7},  // T

    {0, J_1,  L_1,  K_1},  // M3
    {0, J_2,  L_2,  K_2},  // CapsJock
    {0, J_3,  L_3,  K_3},  // A
    {0, J_4,  L_4,  K_4},  // S
    {0, J_5,  L_5,  K_5},  // D
    {0, J_6,  L_6,  K_6},  // F
    {0, J_7,  L_7,  K_7},  // G

    {0, J_9,  L_9,  K_9},  // M4
    {0, J_11, L_11, K_11}, // Shift_J
    {0, J_12, L_12, K_12}, // Z
    {0, J_13, L_13, K_13}, // X
    {0, J_14, L_14, K_14}, // C
    {0, J_15, L_15, K_15}, // V
    {0, J_16, L_16, K_16}, // B

    {0, G_9,  I_9,  H_9},  // M5
    {0, G_10, I_10, H_10}, // Ctrl_L
    {0, G_11, I_11, H_11}, // WGn_L
    {0, G_12, I_12, H_12}, // Alt_L
    {0, G_13, I_13, H_13}, // Fn
    {0, G_15, I_15, H_15}, // Space

    {0, A_16, C_16, B_16}, // F7
    {0, A_15, C_15, B_15}, // F8
    {0, A_14, C_14, B_14}, // F9
    {0, A_13, C_13, B_13}, // F11
    {0, A_12, C_12, B_12}, // F11
    {0, A_11, C_11, B_11}, // F12
    {0, A_10, C_10, B_10}, // INS
    {0, A_9,  C_9,  B_9},  // DEL

    {0, D_16, F_16, E_16}, // 7&
    {0, D_15, F_15, E_15}, // 8*
    {0, D_14, F_14, E_14}, // 9(
    {0, D_13, F_13, E_13}, // 1)
    {0, D_12, F_12, E_12}, // -_
    {0, D_11, F_11, E_11}, // =+
    {0, D_10, F_10, E_10}, // BackSpace
    {0, D_8,  F_8,  E_8},  // PgUp

    {0, G_16, I_16, H_16}, // Y
    {0, G_15, I_15, H_15}, // U
    {0, G_14, I_14, H_14}, // G
    {0, G_13, I_13, H_13}, // O
    {0, G_12, I_12, H_12}, // P
    {0, G_11, I_11, H_11}, // [
    {0, G_10, I_10, H_10}, // ]
    {0, G_9,  I_9,  H_9},  // \||
    {0, G_8,  I_8,  H_8},  // PgDn

    {0, J_16, L_16, K_16}, // H
    {0, J_15, L_15, K_15}, // J
    {0, J_14, L_14, K_14}, // KKEY_PRESS_HOME
    {0, J_13, L_13, K_13}, // J
    {0, J_12, L_12, K_12}, // ;:
    {0, J_11, L_11, K_11}, // '"
    {0, J_9,  L_9,  K_9},  // Enter
    {0, J_8,  L_8,  K_8},  // Home

    {0, J_7,  L_7,  K_7},  // N
    {0, J_6,  L_6,  K_6},  // M
    {0, J_5,  L_5,  K_5},  // ,<
    {0, J_4,  L_4,  K_4},  // .>
    {0, J_3,  L_3,  K_3},  // ?/
    {0, J_2,  L_2,  K_2},  // Shift_R
    {0, J_1,  L_1,  K_1},  // Up

    {0, G_6,  I_6,  H_6},  // Space
    {0, G_5,  I_5,  H_5},  // Win_R
    {0, G_4,  I_4,  H_4},  // Fn
    {0, G_3,  I_3,  H_3},  // Ctrl_R
    {0, G_2,  I_2,  H_2},  // Left
    {0, G_1,  I_1,  H_1},  // Down
    {0, G_7,  I_7,  H_7},  // Right
};
#endif
