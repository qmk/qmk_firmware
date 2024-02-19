/* Copyright 2021 CANARYTEAM <tuananhnguyen204@gmail.com>
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
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[RGB_MATRIX_LED_COUNT] = {
    { 0, J_14, K_14,  L_14 },
    { 0, J_13, K_13,  L_13 },
    { 0, J_12, K_12,  L_12 },
    { 0, J_11, K_11,  L_11 },
    { 0, J_10, K_10,  L_10 },
    { 0, J_9,  K_9,   L_9 },
    { 0, J_8,  K_8,   L_8 },
    { 0, J_7,  K_7,   L_7 },
    { 0, J_6,  K_6,   L_6 },
    { 0, J_5,  K_5,   L_5 },
    { 0, J_4,  K_4,   L_4 },
    { 0, J_3,  K_3,   L_3 },
    { 0, J_2,  K_2,   L_2 },
    { 0, J_1,  K_1,   L_1 },

    { 0, G_14, H_14,  I_14 },
    { 0, G_13, H_13,  I_13 },
    { 0, G_12, H_12,  I_12 },
    { 0, G_11, H_11,  I_11 },
    { 0, G_10, H_10,  I_10 },
    { 0, G_9,  H_9,   I_9 },
    { 0, G_8,  H_8,   I_8 },
    { 0, G_7,  H_7,   I_7 },
    { 0, G_6,  H_6,   I_6 },
    { 0, G_5,  H_5,   I_5 },
    { 0, G_4,  H_4,   I_4 },
    { 0, G_3,  H_3,   I_3 },
    { 0, G_2,  H_2,   I_2 },
    { 0, G_1,  H_1,   I_1 },

    { 0, D_14, E_14,  F_14 },
    { 0, D_12, E_12,  F_12 },
    { 0, D_11, E_11,  F_11 },
    { 0, D_10, E_10,  F_10 },
    { 0, D_9,  E_9,   F_9 },
    { 0, D_8,  E_8,   F_8 },
    { 0, D_7,  E_7,   F_7 },
    { 0, D_6,  E_6,   F_6 },
    { 0, D_5,  E_5,   F_5 },
    { 0, D_4,  E_4,   F_4 },
    { 0, D_3,  E_3,   F_3 },
    { 0, D_2,  E_2,   F_2 },
    { 0, D_1,  E_1,   F_1 },

    { 0, A_14, B_14,  C_14 },
    { 0, A_13, B_13,  C_13 },
    { 0, A_11, B_11,  C_11 },
    { 0, A_10, B_10,  C_10 },
    { 0, A_9,  B_9,   C_9 },
    { 0, A_8,  B_8,   C_8 },
    { 0, A_7,  B_7,   C_7 },
    { 0, A_6,  B_6,   C_6 },
    { 0, A_5,  B_5,   C_5 },
    { 0, A_4,  B_4,   C_4 },
    { 0, A_3,  B_3,   C_3 },
    { 0, A_2,  B_2,   C_2 },
    { 0, A_1,  B_1,   C_1 },

    { 0, A_15, B_15,  C_15 },
    { 0, D_13, E_13,  F_13 },
    { 0, A_12, B_12,  C_12 },
    { 0, D_15, E_15,  F_15 },
    { 0, G_15, H_15,  I_15 },
    { 0, A_16, B_16,  C_16 },
    { 0, D_16, E_16,  F_16 },
    { 0, G_16, H_16,  I_16 },
    { 0, J_16, K_16,  L_16 }
};

led_config_t g_led_config = {
    {
        { 13, 12, 11,     10,      9,  8,      7,      6,  5,  4,  3,  2,      1,  0 },
        { 27, 26, 25,     24,     23, 22,     21,     20, 19, 18, 17, 16,     15, 14 },
        { 40, 39, 38,     37,     36, 35,     34,     33, 32, 31, 30, 29, NO_LED, 28 },
        { 53, 52, 51,     50,     49, 48,     47,     46, 45, 44, 43, 42, NO_LED, 41 },
        { 62, 61, 60, NO_LED, NO_LED, 59, NO_LED, NO_LED, 58, 57, 56, 55, NO_LED, 54 }
    }, {
        { 216,   0 }, { 192,   0 }, { 176,   0 }, { 160,   0 }, { 144,   0 }, { 128,   0 }, { 112,   0 }, {  96,   0 }, {  80,   0 }, {  64,   0 }, {  48,   0 }, {  32,   0 }, {  16,   0 }, {   0,   0 },
        { 220,  16 }, { 200,  16 }, { 184,  16 }, { 168,  16 }, { 152,  16 }, { 136,  16 }, { 120,  16 }, { 104,  16 }, {  88,  16 }, {  72,  16 }, {  56,  16 }, {  40,  16 }, {  24,  16 }, {   4,  16 },
        { 214,  32 }, { 188,  32 }, { 172,  32 }, { 156,  32 }, { 140,  32 }, { 124,  32 }, { 108,  32 }, {  92,  32 }, {  76,  32 }, {  60,  32 }, {  44,  32 }, {  28,  32 },               {   6,  32 },
        { 224,  48 },               { 208,  48 }, { 186,  48 }, { 164,  48 }, { 148,  48 }, { 132,  48 }, { 116,  48 }, { 100,  48 }, {  84,  48 }, {  68,  48 }, {  52,  48 }, {  36,  48 }, {   9,  48 },
        { 224,  64 }, { 208,  64 }, { 192,  64 },                                           { 176,  64 },                             { 160,  64 }, { 102,  64 }, {  42,  64 }, {  22,  64 }, {   2,  64 }
    }, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1,          1,       1, 4, 1, 1, 1
    }
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
