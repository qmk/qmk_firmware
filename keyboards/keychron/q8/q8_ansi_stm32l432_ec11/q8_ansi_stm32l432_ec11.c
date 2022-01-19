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
const ckled2001_led PROGMEM g_ckled2001_leds[DRIVER_LED_TOTAL] = {
/* Refer to CKLED manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, L_16,   J_16,   K_16},
    {0, L_15,   J_15,   K_15},
    {0, L_14,   J_14,   K_14},
    {0, L_13,   J_13,   K_13},
    {0, L_12,   J_12,   K_12},
    {0, L_11,   J_11,   K_11},
    {0, L_10,   J_10,   K_10},
    {0, L_9,    J_9,    K_9},
    {0, L_8,    J_8,    K_8},
    {0, L_7,    J_7,    K_7},
    {0, L_6,    J_6,    K_6},
    {0, L_5,    J_5,    K_5},
    {0, L_4,    J_4,    K_4},
    {0, L_3,    J_3,    K_3},
    {0, L_2,    J_2,    K_2},

    {0, C_16,   A_16,   B_16},
    {0, C_15,   A_15,   B_15},
    {0, C_14,   A_14,   B_14},
    {0, C_13,   A_13,   B_13},
    {0, C_12,   A_12,   B_12},
    {0, C_11,   A_11,   B_11},
    {0, C_10,   A_10,   B_10},
    {0, C_9,    A_9,    B_9},
    {0, C_8,    A_8,    B_8},
    {0, C_7,    A_7,    B_7},
    {0, C_6,    A_6,    B_6},
    {0, C_5,    A_5,    B_5},
    {0, C_3,    A_3,    B_3},
    {0, C_2,    A_2,    B_2},

    {0, I_16,   G_16,   H_16},
    {0, I_14,   G_14,   H_14},
    {0, I_13,   G_13,   H_13},
    {0, I_12,   G_12,   H_12},
    {0, I_11,   G_11,   H_11},
    {0, I_10,   G_10,   H_10},
    {0, I_9,    G_9,    H_9},
    {0, I_8,    G_8,    H_8},
    {0, I_7,    G_7,    H_7},
    {0, I_6,    G_6,    H_6},
    {0, I_5,    G_5,    H_5},
    {0, I_3,    G_3,    H_3},
    {0, I_2,    G_2,    H_2},

    {0, F_16,   D_16,   E_16},
    {0, F_15,   D_15,   E_15},
    {0, F_14,   D_14,   E_14},
    {0, F_10,   D_10,   E_10},
    {0, F_6,    D_6,    E_6},
    {0, F_5,    D_5,    E_5},
    {0, F_3,    D_3,    E_3},
    {0, F_2,    D_2,    E_2},
    {0, C_4,    A_4,    B_4}
};

led_config_t g_led_config = {
     {
        {   0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14  },
        {  15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     51,     27,     28  },
        {  29, NO_LED,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39, NO_LED,     40,     41  },
        {  42,     43,     43, NO_LED, NO_LED, NO_LED,     45, NO_LED, NO_LED, NO_LED,     46,     47,     48,     49,     50  }
    },
    {
        {0, 0}, {15, 0}, {30, 0}, {45, 0}, {60, 0}, {75, 0}, {90, 0}, {105, 0}, {120, 0}, {135, 0}, {150, 0}, {165, 0}, {180, 0}, {195, 0},           {224, 0},
        {0,21}, {15,21}, {30,21}, {45,21}, {60,21}, {75,21}, {90,21}, {105,21}, {120,21}, {135,21}, {150,21}, {165,21},           {195,21},           {224,21},
        {0,42},          {30,42}, {45,42}, {60,42}, {75,42}, {90,42}, {105,42}, {120,42}, {135,42}, {150,42}, {165,42},           {180,42},           {224,42},
        {0,64}, {15,42}, {30,64},                            {90,64},                               {150,64}, {165,64}, {180,64}, {195,64}, {210,64}, {224,64}
    },
    {
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,          4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,          4,          4,
        4,          4,    4,    4,    4,    4,    4,    4,    4,    4,    4,          4,    4,
        4,    4,    4,                      4,                      4,    4,    4,    4,    4,    4
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
