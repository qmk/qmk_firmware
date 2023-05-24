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
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C_1,    A_1,    B_1},
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

    {0, F_1,    D_1,    E_1},
    {0, F_2,    D_2,    E_2},
    {0, F_3,    D_3,    E_3},
    {0, F_4,    D_4,    E_4},
    {0, F_5,    D_5,    E_5},
    {0, F_6,    D_6,    E_6},
    {0, F_7,    D_7,    E_7},
    {0, F_8,    D_8,    E_8},
    {0, F_9,    D_9,    E_9},
    {0, F_10,   D_10,   E_10},
    {0, F_11,   D_11,   E_11},
    {0, F_12,   D_12,   E_12},
    {0, F_13,   D_13,   E_13},
    {0, F_14,   D_14,   E_14},
    {0, F_16,   D_16,   E_16},

    {0, I_1,    G_1,    H_1},
    {0, I_2,    G_2,    H_2},
    {0, I_3,    G_3,    H_3},
    {0, I_4,    G_4,    H_4},
    {0, I_5,    G_5,    H_5},
    {0, I_6,    G_6,    H_6},
    {0, I_7,    G_7,    H_7},
    {0, I_8,    G_8,    H_8},
    {0, I_9,    G_9,    H_9},
    {0, I_10,   G_10,   H_10},
    {0, I_11,   G_11,   H_11},
    {0, I_12,   G_12,   H_12},
    {0, I_13,   G_13,   H_13},
    {0, I_14,   G_14,   H_14},
    {0, I_16,   G_16,   H_16},

    {0, L_1,    J_1,    K_1},
    {0, L_2,    J_2,    K_2},
    {0, L_3,    J_3,    K_3},
    {0, L_4,    J_4,    K_4},
    {0, L_5,    J_5,    K_5},
    {0, L_6,    J_6,    K_6},
    {0, L_7,    J_7,    K_7},
    {0, L_8,    J_8,    K_8},
    {0, L_9,    J_9,    K_9},
    {0, L_10,   J_10,   K_10},
    {0, L_11,   J_11,   K_11},
    {0, L_12,   J_12,   K_12},
    {0, L_14,   J_14,   K_14},
    {0, L_16,   J_16,   K_16},

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
    {1, C_14,   A_14,   B_14},
    {1, C_15,   A_15,   B_15},

    {1, F_1,    D_1,    E_1},
    {1, F_2,    D_2,    E_2},
    {1, F_3,    D_3,    E_3},
    {1, F_7,    D_7,    E_7},
    {1, F_11,   D_11,   E_11},
    {1, F_12,   D_12,   E_12},
    {1, F_13,   D_13,   E_13},
    {1, F_14,   D_14,   E_14},
    {1, F_15,   D_15,   E_15},
    {1, F_16,   D_16,   E_16}
};

led_config_t g_led_config = {
    {
        {   0,     NO_LED,  1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,      12,     14   },
        {  15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,      28,     29   },
        {  30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,      43,     44   },
        {  45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     71,      57,     58   },
        {  59,     NO_LED, 60,     61,     62,     63,     64,     65,     66,     67,     68,     69,     80,      70,     13   },
        {  72,     73,     74,     NO_LED, NO_LED, NO_LED, 75,     NO_LED, NO_LED, NO_LED, 76,     77,     78,      79,     81   }
    },
    {
        {0, 0},          {30, 0}, {45, 0}, {60, 0}, {75, 0}, {90, 0}, {105, 0}, {120, 0}, {135, 0}, {150, 0}, {165, 0}, {180, 0}, {195, 0}, {210, 0}, {224, 0},
        {0,13}, {15,13}, {30,13}, {45,13}, {60,13}, {75,13}, {90,13}, {105,13}, {120,13}, {135,13}, {150,13}, {165,13}, {180,13}, {195,13},           {224,13},
        {0,26}, {15,26}, {30,26}, {45,26}, {60,26}, {75,26}, {90,26}, {105,26}, {120,26}, {135,26}, {150,26}, {165,26}, {180,26}, {195,26},           {224,26},
        {0,39}, {15,39}, {30,39}, {45,39}, {60,39}, {75,39}, {90,39}, {105,39}, {120,39}, {135,39}, {150,39}, {165,39},           {195,39},           {224,39},
        {0,52},          {30,52}, {45,52}, {60,52}, {75,52}, {90,52}, {105,52}, {120,52}, {135,52}, {150,52}, {165,52},           {195,52}, {210,52},
        {0,64}, {15,64}, {30,64},                            {90,64},                               {150,64}, {165,64}, {180,64}, {195,64}, {210,64}, {224,64}
    },
    {
        4,              4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,
        4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,              4,
        4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,              4,
        4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,              4,              4,
        4,              4,      4,      4,      4,      4,      4,      4,      4,      4,      4,              4,      4,
        4,      4,      4,                              4,                              4,      4,      4,      4,      4,      4
    }
};
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif
