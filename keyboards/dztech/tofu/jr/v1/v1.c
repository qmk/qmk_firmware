/* Copyright 2022 DZTECH <moyi4681@live.cn>
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

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    { 1, K_12, J_12, L_12 },
    { 1, K_11, J_11, L_11 },
    { 1, K_10, J_10, L_10 },
    { 1, K_9,  J_9,  L_9 },
    { 1, K_8,  J_8,  L_8 },
    { 1, K_7,  J_7,  L_7 },
    { 1, K_6,  J_6,  L_6 },
    { 1, K_5,  J_5,  L_5 },
    { 1, K_4,  J_4,  L_4 },
    { 1, K_3,  J_3,  L_3 },
    { 1, K_2,  J_2,  L_2 },
    { 1, K_1,  J_1,  L_1 },
    { 1, H_1,  G_1,  I_1 },
    { 1, H_2,  G_2,  I_2 },
    { 1, H_3,  G_3,  I_3 },

    { 0, B_12, A_12, C_12 },
    { 0, B_11, A_11, C_11 },
    { 0, B_10, A_10, C_10 },
    { 0, B_9,  A_9,  C_9 },
    { 0, B_8,  A_8,  C_8 },
    { 0, B_7,  A_7,  C_7 },
    { 0, B_6,  A_6,  C_6 },
    { 0, B_5,  A_5,  C_5 },
    { 0, B_4,  A_4,  C_4 },
    { 0, B_3,  A_3,  C_3 },
    { 0, B_2,  A_2,  C_2 },
    { 0, B_1,  A_1,  C_1 },
    { 1, H_6,  G_6,  I_6 },
    { 1, H_5,  G_5,  I_5 },
    { 1, H_4,  G_4,  I_4 },

    { 0, E_12, D_12, F_12 },
    { 0, E_11, D_11, F_11 },
    { 0, E_10, D_10, F_10 },
    { 0, E_9,  D_9,  F_9 },
    { 0, E_8,  D_8,  F_8 },
    { 0, E_7,  D_7,  F_7 },
    { 0, E_6,  D_6,  F_6 },
    { 0, E_5,  D_5,  F_5 },
    { 0, E_4,  D_4,  F_4 },
    { 0, E_3,  D_3,  F_3 },
    { 0, E_2,  D_2,  F_2 },
    { 0, E_1,  D_1,  F_1 },
    { 1, H_7,  G_7,  I_7 },
    { 1, H_8,  G_8,  I_8 },

    { 0, H_12, G_12, I_12 },
    { 0, H_11, G_11, I_11 },
    { 0, H_10, G_10, I_10 },
    { 0, H_9,  G_9,  I_9 },
    { 0, H_8,  G_8,  I_8 },
    { 0, H_7,  G_7,  I_7 },
    { 0, H_6,  G_6,  I_6 },
    { 0, H_5,  G_5,  I_5 },
    { 0, H_4,  G_4,  I_4 },
    { 0, H_3,  G_3,  I_3 },
    { 0, H_2,  G_2,  I_2 },
    { 0, H_1,  G_1,  I_1 },
    { 0, K_9,  J_9,  L_9 },
    { 0, K_8,  J_8,  L_8 },

    { 0, K_12, J_12, L_12 },
    { 0, K_11, J_11, L_11 },
    { 0, K_10, J_10, L_10 },
    { 0, K_7,  J_7,  L_7 },
    { 0, K_4,  J_4,  L_4 },
    { 0, K_3,  J_3,  L_3 },
    { 0, K_2,  J_2,  L_2 },
    { 0, K_1,  J_1,  L_1 },
    { 0, K_6,  J_6,  L_6 },
    { 0, K_5,  J_5,  L_5 },
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
    return true;
}

#endif
