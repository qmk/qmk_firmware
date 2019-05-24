/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "ez.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_12,  A_12,  C_12},
    {0, B_11,  A_11,  C_11},
    {0, B_10,  A_10,  C_10},
    {0, B_9,   A_9,   C_9},
    {0, B_8,   A_8,   C_8},
    {0, B_7,   A_7,   C_7},

    {0, H_12,  G_12,  I_12},
    {0, H_11,  G_11,  I_11},
    {0, H_10,  G_10,  I_10},
    {0, H_9,   G_9,   I_9},
    {0, H_8,   G_8,   I_8},
    {0, H_7,   G_7,   I_7},

    {0, B_6,   A_6,   C_6},
    {0, B_5,   A_5,   C_5},
    {0, B_4,   A_4,   C_4},
    {0, B_3,   A_3,   C_3},
    {0, B_2,   A_2,   C_2},
    {0, B_1,   A_1,   C_1},

    {0, H_6,   G_6,   I_6},
    {0, H_5,   G_5,   I_5},
    {0, H_4,   G_4,   I_4},
    {0, H_3,   G_3,   I_3},
    {0, H_2,   G_2,   I_2},
    {0, H_1,   G_1,   I_1},

    {0, E_12,  D_12,  F_12},
    {0, E_11,  D_11,  F_11},
    {0, E_10,  D_10,  F_10},
    {0, E_9,   D_9,   F_9},
    {0, E_8,   D_8,   F_8},
    {0, E_7,   D_7,   F_7},

    {0, K_12,  J_12,  L_12},
    {0, K_11,  J_11,  L_11},
    {0, K_10,  J_10,  L_10},
    {0, K_9,   J_9,   L_9},
    {0, K_8,   J_8,   L_8},
    {0, K_7,   J_7,   L_7},

    {0, E_6,   D_6,   F_6},
    {0, E_5,   D_5,   F_5},
    {0, E_4,   D_4,   F_4},
    {0, E_3,   D_3,   F_3},
    {0, E_2,   D_2,   F_2},
    {0, E_1,   D_1,   F_1},

    {0, K_6,   J_6,   L_6},
    {0, K_5,   J_5,   L_5},
    {0, K_4,   J_4,   L_4},
    {0, K_3,   J_3,   L_3},
    {0, K_2,   J_2,   L_2},

};

led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5 },
    {  12,  13,  14,  15,  16,  17 },
    {  24,  25,  26,  27,  28,  29 },
    {  36,  37,  38,  45,  46, NO_LED },
    {   6,   7,   8,   9,  10,  11 },
    {  18,  19,  20,  21,  22,  23 },
    {  30,  31,  32,  33,  34,  35 },
    {  42,  43,  44,  39,  40,  41 }
}, {
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 }, { 122,   0 }, { 142,   0 }, { 162,   0 }, { 183,   0 }, { 203,   0 }, { 223,   0 },
    {   0,  21 }, {  20,  21 }, {  40,  21 }, {  61,  21 }, {  81,  21 }, { 101,  21 }, { 122,  21 }, { 142,  21 }, { 162,  21 }, { 183,  21 }, { 203,  21 }, { 223,  21 },
    {   0,  42 }, {  20,  42 }, {  40,  42 }, {  61,  42 }, {  81,  42 }, { 101,  42 }, { 122,  42 }, { 142,  42 }, { 162,  42 }, { 183,  42 }, { 203,  42 }, { 223,  42 },
    {   0,  63 }, {  20,  63 }, {  40,  63 }, {  61,  63 }, {  81,  63 }, { 111,  63 }, { 142,  63 }, { 162,  63 }, { 183,  63 }, { 203,  63 }, { 223,  63 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1
} };


void matrix_init_kb(void) {
  matrix_init_user();

  palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, 9, PAL_MODE_OUTPUT_PUSHPULL);

  palClearPad(GPIOB, 8);
  palClearPad(GPIOB, 9);
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

uint32_t layer_state_set_kb(uint32_t state) {

  palClearPad(GPIOB, 8);
  palClearPad(GPIOB, 9);
  state = layer_state_set_user(state);
  uint8_t layer = biton32(state);
  switch (layer) {
      case 3:
        palSetPad(GPIOB, 9);
        break;
      case 4:
        palSetPad(GPIOB, 8);
        break;
      case 6:
        palSetPad(GPIOB, 9);
        palSetPad(GPIOB, 8);
        break;
      default:
        break;
    }
    return state;
}
