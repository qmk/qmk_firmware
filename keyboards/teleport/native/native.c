/* Copyright 2021 Moritz Plattner
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

/* This board has !SDB of the is31 wired to D2. Set high to enable */
void keyboard_post_init_kb(void) {
    setPinOutput(B9);
    writePinHigh(B9);
    
    keyboard_post_init_user();
}

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |     G location
 *   |  |     |     B location
 *   |  |     |     | */
    {0, L_1,  K_1,  J_1},               // Row 1
    {0, L_2,  K_2,  J_2},
    {0, L_3,  K_3,  J_3},
    {0, L_4,  K_4,  J_4},
    {0, L_5,  K_5,  J_5},
    {0, L_6,  K_6,  J_6},
    {0, L_7,  K_7,  J_7},
    {0, L_8,  K_8,  J_8},
    {0, L_9,  K_9,  J_9},
    {0, L_10, K_10, J_10},
    {0, L_11, K_11, J_11},
    {0, L_12, K_12, J_12},
    {0, L_13, K_13, J_13},
    {0, L_14, K_14, J_14},
    {0, L_15, K_15, J_15},
    {0, L_16, K_16, J_16},

    {0, I_1,  H_1,  G_1},               // Row 2
    {0, I_2,  H_2,  G_2},
    {0, I_3,  H_3,  G_3},
    {0, I_4,  H_4,  G_4},
    {0, I_5,  H_5,  G_5},
    {0, I_6,  H_6,  G_6},
    {0, I_7,  H_7,  G_7},
    {0, I_8,  H_8,  G_8},
    {0, I_9,  H_9,  G_9},
    {0, I_10, H_10, G_10},
    {0, I_11, H_11, G_11},
    {0, I_12, H_12, G_12},
    {0, I_13, H_13, G_13},
    {0, I_15, H_15, G_15},
    {0, I_16, H_16, G_16},

    {0, F_1,  E_1,  D_1},               // Row 3
    {0, F_3,  E_3,  D_3},
    {0, F_4,  E_4,  D_4},
    {0, F_5,  E_5,  D_5},
    {0, F_6,  E_6,  D_6},
    {0, F_7,  E_7,  D_7},
    {0, F_8,  E_8,  D_8},
    {0, F_9,  E_9,  D_9},
    {0, F_10, E_10, D_10},
    {0, F_11, E_11, D_11},
    {0, F_12, E_12, D_12},
    {0, F_13, E_13, D_13},
    {0, F_14, E_14, D_14},
    {0, F_15, E_15, D_15},
    {0, F_16, E_16, D_16},

    {1, L_1,  K_1,  J_1},               // Row 4
    {1, L_3,  K_3,  J_3},
    {1, L_4,  K_4,  J_4},
    {1, L_5,  K_5,  J_5},
    {1, L_6,  K_6,  J_6},
    {1, L_7,  K_7,  J_7},
    {1, L_8,  K_8,  J_8},
    {1, L_9,  K_9,  J_9},
    {1, L_10, K_10, J_10},
    {1, L_11, K_11, J_11},
    {1, L_12, K_12, J_12},
    {1, L_13, K_13, J_13},
    {1, L_14, K_14, J_14},
    {1, L_16, K_16, J_16},

    {1, I_1,  H_1,  G_1},               // Row 5
    {1, I_2,  H_2,  G_2},
    {1, I_3,  H_3,  G_3},
    {1, I_4,  H_4,  G_4},
    {1, I_5,  H_5,  G_5},
    {1, I_6,  H_6,  G_6},
    {1, I_7,  H_7,  G_7},
    {1, I_8,  H_8,  G_8},
    {1, I_9,  H_9,  G_9},
    {1, I_10, H_10, G_10},
    {1, I_11, H_11, G_11},
    {1, I_12, H_12, G_12},
    {1, I_14, H_14, G_14},
    {1, I_15, H_15, G_15},
    {1, I_16, H_16, G_16},

    {1, F_1,  E_1,  D_1},               // Row 6
    {1, F_2,  E_2,  D_2},
    {1, F_3,  E_3,  D_3},
    {1, F_7,  E_7,  D_7},
    {1, F_11, E_11, D_11},
    {1, F_12, E_12, D_12},
    {1, F_13, E_13, D_13},
    {1, F_14, E_14, D_14},
    {1, F_15, E_15, D_15},
    {1, F_16, E_16, D_16}
};
#endif