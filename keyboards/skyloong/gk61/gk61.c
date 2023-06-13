/* Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
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

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C_1,    B_1,    A_1},
    {0, C_2,    B_2,    A_2},
    {0, C_3,    B_3,    A_3},
    {0, C_4,    B_4,    A_4},
    {0, C_5,    B_5,    A_5},
    {0, C_6,    B_6,    A_6},
    {0, C_7,    B_7,    A_7},
    {0, C_8,    B_8,    A_8},
    {0, C_9,    B_9,    A_9},
    {0, C_10,   B_10,   A_10},
    {0, C_11,   B_11,   A_11},
    {0, C_12,   B_12,   A_12},
    {0, C_13,   B_13,   A_13},
    {0, C_14,   B_14,   A_14},
    {0, C_15,   B_15,   A_15},
    {0, C_16,   B_16,   A_16},

    {0, F_1,    E_1,    D_1},
    {0, F_2,    E_2,    D_2},
    {0, F_3,    E_3,    D_3},
    {0, F_4,    E_4,    D_4},
    {0, F_5,    E_5,    D_5},
    {0, F_6,    E_6,    D_6},
    {0, F_7,    E_7,    D_7},
    {0, F_8,    E_8,    D_8},
    {0, F_9,    E_9,    D_9},
    {0, F_10,   E_10,   D_10},
    {0, F_11,   E_11,   D_11},
    {0, F_12,   E_12,   D_12},
    {0, F_13,   E_13,   D_13},
    {0, F_14,   E_14,   D_14},
    {0, F_15,   E_15,   D_15},
    {0, F_16,   E_16,   D_16},

    {0, I_1,    H_1,    G_1},
    {0, I_2,    H_2,    G_2},
    {0, I_3,    H_3,    G_3},
    {0, I_4,    H_4,    G_4},
    {0, I_5,    H_5,    G_5},
    {0, I_6,    H_6,    G_6},
    {0, I_7,    H_7,    G_7},
    {0, I_8,    H_8,    G_8},
    {0, I_9,    H_9,    G_9},
    {0, I_10,   H_10,   G_10},
    {0, I_11,   H_11,   G_11},
    {0, I_12,   H_12,   G_12},
    {0, I_13,   H_13,   G_13},
    {0, I_14,   H_14,   G_14},
    {0, I_15,   H_15,   G_15},
    {0, I_16,   H_16,   G_16},

    {0, L_1,    K_1,    J_1},
    {0, L_2,    K_2,    J_2},
    {0, L_3,    K_3,    J_3},
    {0, L_4,    K_4,    J_4},
    {0, L_5,    K_5,    J_5},
    {0, L_6,    K_6,    J_6},
    {0, L_7,    K_7,    J_7},
    {0, L_8,    K_8,    J_8},
    {0, L_9,    K_9,    J_9},
    {0, L_10,   K_10,   J_10},
    {0, L_11,   K_11,   J_11},
    {0, L_12,   K_12,   J_12},
    {0, L_13,   K_13,   J_13},
    {0, L_14,   K_14,   J_14},
    {0, L_15,   K_15,   J_15},
    {0, L_16,   K_16,   J_16},

};
/*
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,    1,    2,        3,        4,    5,    6,        7,    8,    9,   10,       11,        12,       13 },
  { 16,   17,   18,       19,       20,   21,   22,       23,   24,   25,   26,       27,        28,       29 },
  { 32,   33,   34,       36,       37,   35,   38,       39,   40,   41,   42,       43,    NO_LED,       44 },
  { 48,   49,   50,       51,       52,   53,   54,       55,   56,   57,   58,   NO_LED,        60,   NO_LED },
  { 62,   63,   46,   NO_LED,       47,   30,   31,   NO_LED,   14,   15,   45,       59,    NO_LED,       61 }

}, {
  // LED Index to Physical Position

  {   0,     0 }, {   10,   0 }, {   20,   0 }, {   30,   0 }, {   40,   0 }, {   50,   0 }, {   60,   0 }, {  70,   0 }, {   80,   0 }, {   90,   0 },{  100,   0 },{   110,   0 }, {  120,   0 },{  135,   0 },
  { 2.5,    10 }, {   15,  10 }, {   25,  10 }, {   35,  10 }, {   45,  10 }, {   55,  10 }, {   65,  10 }, {  75,  10 }, {   85,  10 }, {   95,  10 },{  105,  10 },{   115,  10 }, {  125,  10 },{  138,  10 },
  {   4,    20 }, { 17.5,  20 }, { 27.5,  20 }, { 37.5,  20 }, { 47.5,  20 }, { 57.5,  20 }, { 67.5,  20 }, {77.5,  20 }, { 87.5,  20 }, { 97.5,  20 },{107.5,  20 },{ 117.5,  20 },               {  134,  20 },
  {   6,    30 }, { 22.5,  30 }, { 32.5,  30 }, { 42.5,  30 }, { 52.5,  30 }, { 62.5,  30 }, { 72.5,  30 }, {82.5,  30 }, { 92.5,  30 }, {102.5,  30 },{112.5,  30 },                {  130,  30 },
  {   1,    40 }, {   14,  40 }, {   26,  40 },                {   46,  40 }, { 63.5,  40 }, { 71.5,  40 },               { 88.5,  40 }, {101.5,  40 },{113.5,  40 },{   127,  10 },               {140.5,  10 },

}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
  4, 4, 4,    4, 4, 4,    4, 4, 4, 4,    4,
} };
#endif
*/
void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;

}
