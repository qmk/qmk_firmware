/*
Copyright 2021 Evelien Dekkers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rev5.h"

const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   C_1,   A_1},
    {0, B_2,   C_2,   A_2},
    {0, B_3,   C_3,   A_3},
    {0, B_4,   C_4,   A_4},
    {0, B_5,   C_5,   A_5},
    {0, B_6,   C_6,   A_6},
    {0, B_7,   C_7,   A_7},
    {0, B_8,   C_8,   A_8},
    {0, B_9,   C_9,   A_9},
    {0, B_10,  C_10,  A_10},
    {0, B_11,  C_11,  A_11},
    {0, B_12,  C_12,  A_12},
    {0, B_13,  C_13,  A_13},

    {0, E_1,   F_1,   D_1},
    {0, E_2,   F_2,   D_2},
    {0, E_3,   F_3,   D_3},
    {0, E_4,   F_4,   D_4},
    {0, E_5,   F_5,   D_5},
    {0, E_6,   F_6,   D_6},
    {0, E_7,   F_7,   D_7},
    {0, E_8,   F_8,   D_8},
    {0, E_9,   F_9,   D_9},
    {0, E_10,  F_10,  D_10},
    {0, E_11,  F_11,  D_11},
    {0, E_13,  F_13,  D_13},

    {0, H_1,   I_1,   G_1},
    {0, H_2,   I_2,   G_2},
    {0, H_3,   I_3,   G_3},
    {0, H_4,   I_4,   G_4},
    {0, H_5,   I_5,   G_5},
    {0, H_6,   I_6,   G_6},
    {0, H_7,   I_7,   G_7},
    {0, H_8,   I_8,   G_8},
    {0, H_9,   I_9,   G_9},
    {0, H_10,  I_10,  G_10},
    {0, H_11,  I_11,  G_11},
    {0, H_12,  I_12,  G_12},
    {0, H_13,  I_13,  G_13},

    {0, K_1,   L_1,   J_1},
    {0, K_2,   L_2,   J_2},
    {0, K_3,   L_3,   J_3},
    {0, K_4,   L_4,   J_4},
    {0, K_6,   L_6,   J_6},
    {0, K_8,   L_8,   J_8},
    {0, K_10,  L_10,  J_10},
    {0, K_11,  L_11,  J_11},
    {0, K_12,  L_12,  J_12},
    {0, K_13,  L_13,  J_13}
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12   },
  {   13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, NO_LED, 24   },
  {   25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37   },
  {   38, 39, 40, 41, NO_LED, 42, NO_LED, 43, NO_LED, 44, 45, 46, 47   }
}, {
  // LED Index to Physical Position
  { 9,     8 },
  { 26,    8 },
  { 43,    8 },
  { 60,    8 },
  { 78,    8 },
  { 95,    8 },
  { 112,   8 },
  { 129,   8 },
  { 146,   8 },
  { 164,   8 },
  { 181,   8 },
  { 198,   8 },
  { 215,   8 },

  { 11,   24 },
  { 30,   24 },
  { 47,   24 },
  { 64,   24 },
  { 82,   24 },
  { 99,   24 },
  { 116,  24 },
  { 134,  24 },
  { 151,  24 },
  { 168,  24 },
  { 185,  24 },
  { 209,  24 },

  { 15,   40 },
  { 20,   22 },
  { 39,   40 },
  { 56,   40 },
  { 73,   40 },
  { 90,   40 },
  { 108,  40 },
  { 125,  40 },
  { 142,  40 },
  { 159,  40 },
  { 177,  40 },
  { 196,  40 },
  { 215,  40 },

  { 11,   56 },
  { 30,   56 },
  { 47,   56 },
  { 64,   56 },
  { 88,   56 },
  { 127,  56 },
  { 159,  56 },
  { 177,  56 },
  { 194,  56 },
  { 213,  56 },
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };

void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 255, 255);
    } else {
        rgb_matrix_set_color(26, 0, 0, 0);
    }
}
