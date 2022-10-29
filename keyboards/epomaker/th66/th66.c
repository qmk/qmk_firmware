/* Copyright 2022 Epomaker
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "th66.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  B location
 *   |  |     G location
 *   |  |     |     R location
 *   |  |     |     | */
//  {0, A_1,  B_1,  C_1},  //      Unused LED
    {0, A_2,  B_2,  C_2},  // 0,   1!,              K11
    {0, A_3,  B_3,  C_3},  // 1,   2@,              K12
    {0, A_4,  B_4,  C_4},  // 2,   3#,              K13
    {0, A_5,  B_5,  C_5},  // 3,   4$,              K14
    {0, A_6,  B_6,  C_6},  // 4,   5%,              K15
    {0, A_7,  B_7,  C_7},  // 5,   6^,              K16
    {0, A_8,  B_8,  C_8},  // 6,   7&,              K17
    {0, A_9,  B_9,  C_9},  // 7,   8*,              K18
    {0, A_10, B_10, C_10}, // 8,   9(,              K19
    {0, A_11, B_11, C_11}, // 9,   0),              K1A
    {0, A_12, B_12, C_12}, // 10,  -_,              K1B
    {0, A_13, B_13, C_13}, // 11,  =+,              K1C
    {0, A_14, B_14, C_14}, // 12,  Backspace,       K1D
    {0, A_15, B_15, C_15}, // 13,  Left Alt,        K52
    {0, A_16, B_16, C_16}, // 14,  Space,           K56

    {0, D_1,  E_1,  F_1},  // 15,  Tab,             K20
    {0, D_2,  E_2,  F_2},  // 16,  Q,               K21
    {0, D_3,  E_3,  F_3},  // 17,  W,               K22
    {0, D_4,  E_4,  F_4},  // 18,  E,               K23
    {0, D_5,  E_5,  F_5},  // 19,  R,               K24
    {0, D_6,  E_6,  F_6},  // 20,  T,               K25
    {0, D_7,  E_7,  F_7},  // 21,  Y,               K26
    {0, D_8,  E_8,  F_8},  // 22,  U,               K27
    {0, D_9,  E_9,  F_9},  // 23,  I,               K28
    {0, D_10, E_10, F_10}, // 24,  O,               K29
    {0, D_11, E_11, F_11}, // 25,  P,               K2A
    {0, D_12, E_12, F_12}, // 26,  [{,              K2B
    {0, D_13, E_13, F_13}, // 27,  ]},              K2C
    {0, D_14, E_14, F_14}, // 28,  \|,              K2D
    {0, D_15, E_15, F_15}, // 29,  Right Alt,       K59
    {0, D_16, E_16, F_16}, // 30,  Function,        K5A

    {0, G_1,  H_1,  I_1},  // 31,  Caps Lock,       K30
    {0, G_2,  H_2,  I_2},  // 32,  A,               K31
    {0, G_3,  H_3,  I_3},  // 33,  S,               K32
    {0, G_4,  H_4,  I_4},  // 34,  D,               K33
    {0, G_5,  H_5,  I_5},  // 35,  F,               K34
    {0, G_6,  H_6,  I_6},  // 36,  G,               K35
    {0, G_7,  H_7,  I_7},  // 37,  H,               K36
    {0, G_8,  H_8,  I_8},  // 38,  J,               K37
    {0, G_9,  H_9,  I_9},  // 39,  K,               K38
    {0, G_10, H_10, I_10}, // 40,  L,               K39
    {0, G_11, H_11, I_11}, // 41,  ;:,              K3A
    {0, G_12, H_12, I_12}, // 42,  '",              K3B
    {0, G_13, H_13, I_13}, // 43,  Enter,           K3D
    {0, G_14, H_14, I_14}, // 44,  Up,              K4E
//  {0, G_15, H_15, I_15}, //      Unused LED
    {0, G_16, H_16, I_16}, // 45,  Right Ctrl,      K5C

    {0, J_1,  K_1,  L_1},  // 46,  Left Shift,      K40
//  {0, J_2,  K_2,  L_2},  //      Unused LED
    {0, J_3,  K_3,  L_3},  // 47,  Z,               K42
    {0, J_4,  K_4,  L_4},  // 48,  X,               K43
    {0, J_5,  K_5,  L_5},  // 49,  C,               K44
    {0, J_6,  K_6,  L_6},  // 50,  V,               K45
    {0, J_7,  K_7,  L_7},  // 51,  B,               K46
    {0, J_8,  K_8,  L_8},  // 52,  N,               K47
    {0, J_9,  K_9,  L_9},  // 53,  M,               K48
    {0, J_10, K_10, L_10}, // 54,  ,<,              K49
    {0, J_11, K_11, L_11}, // 55,  .>,              K4A
    {0, J_12, K_12, L_12}, // 56,  /?,              K4B
    {0, J_13, K_13, L_13}, // 57,  Right Shift,     K4D
    {0, J_14, K_14, L_14}, // 58,  Left,            K5D
    {0, J_15, K_15, L_15}, // 59,  Down,            K5E
    {0, J_16, K_16, L_16}, // 60,  Right,           K5F

    {1, C_1,  B_1,  A_1},  // 61,  Underglow 20
    {1, C_2,  B_2,  A_2},  // 62,  Underglow 19
    {1, C_3,  B_3,  A_3},  // 63,  Underglow 18
    {1, C_4,  B_4,  A_4},  // 64,  Underglow 17
    {1, C_5,  B_5,  A_5},  // 65,  Underglow 16
    {1, C_6,  B_6,  A_6},  // 66,  Underglow 15
    {1, C_7,  B_7,  A_7},  // 67,  Underglow 14
    {1, C_8,  B_8,  A_8},  // 68,  Underglow 13
    {1, C_9,  B_9,  A_9},  // 69,  Underglow 12
    {1, C_10, B_10, A_10}, // 70,  Underglow 11
    {1, C_11, B_11, A_11}, // 71,  Underglow 10
    {1, C_12, B_12, A_12}, // 72,  Underglow 9
    {1, C_13, B_13, A_13}, // 73,  Underglow 8
    {1, C_14, B_14, A_14}, // 74,  Underglow 7
    {1, C_15, B_15, A_15}, // 75,  Underglow 6
    {1, C_16, B_16, A_16}, // 76,  Underglow 5

    {1, D_1,  E_1,  F_1},  // 77,  Esc,             K00
//  {1, D_2,  E_2,  F_2},  //      Unused LED
//  {1, D_3,  E_3,  F_3},  //      Unused LED
//  {1, D_4,  E_4,  F_4},  //      Unused LED
//  {1, D_5,  F_5,  F_5},  //      Unused LED
//  {1, D_6,  E_5,  F_6},  //      Unused LED
//  {1, D_7,  E_7,  F_7},  //      Unused LED
//  {1, D_8,  E_8,  F_8},  //      Unused LED
//  {1, D_9,  E_9,  F_9},  //      Unused LED
//  {1, D_10, E_10, F_10}, //      Unused LED
//  {1, D_11, E_11, F_11}, //      Unused LED
//  {1, D_12, E_12, F_12}, //      Unused LED
//  {1, D_13, E_13, F_13}, //      Unused LED
//  {1, D_14, E_14, F_14}, //      Unused LED
    {1, D_15, E_15, F_15}, // 78,  Left Ctrl,       K50
    {1, D_16, E_16, F_16}, // 79,  Left Windows,    K51

//  {1, I_1,  H_1,  G_1},  //      Unused LED
//  {1, I_2,  H_2,  G_2},  //      Unused LED
//  {1, I_3,  H_3,  G_3},  //      Unused LED
//  {1, I_4,  H_4,  G_4},  //      Unused LED
//  {1, G_5,  H_5,  I_5},  //      Unused LED
//  {1, G_6,  H_6,  I_6},  //      Unused LED
//  {1, G_7,  H_7,  I_7},  //      Unused LED
//  {1, G_8,  H_8,  I_8},  //      Unused LED
    {1, G_9,  H_9,  I_9},  // 80, Page Up,         K3E
//  {1, G_10, H_10, I_10}, //      Unused LED
//  {1, G_11, H_11, I_11}, //      Unused LED
    {1, G_12, H_12, I_12}, // 81, Page Down,       K3F
//  {1, I_13, H_13, G_13}, //      Unused LED
//  {1, I_14, H_14, G_14}, //      Unused LED
//  {1, I_15, H_15, G_15}, //      Unused LED
//  {1, I_16, H_16, G_16}, //      Unused LED

//  {1, L_1,  K_1,  J_1},  //      Unused LED
//  {1, L_2,  K_2,  J_2},  //      Unused LED
//  {1, L_3,  K_3,  J_3},  //      Unused LED
//  {1, L_4,  K_4,  J_4},  //      Unused LED
//  {1, L_5,  K_5,  J_5},  //      Unused LED
//  {1, L_6,  K_6,  J_6},  //      Unused LED
//  {1, L_7,  K_7,  J_7},  //      Unused LED
//  {1, L_8,  K_8,  J_8},  //      Unused LED
//  {1, L_9,  K_9,  J_9},  //      Unused LED
//  {1, L_10, K_10, J_10}, //      Unused LED
//  {1, L_11, K_11, J_11}, //      Unused LED
//  {1, L_12, K_12, J_12}, //      Unused LED
//  {1, L_13, K_13, J_13}, //      Unused LED
//  {1, L_14, K_14, J_14}, //      Unused LED
//  {1, L_15, K_15, J_15}, //      Unused LED
//  {1, L_16, K_16, J_16}, //      Unused LED
};

led_config_t g_led_config = { {
    {     77, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED,      0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12, NO_LED, NO_LED },
    {     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28, NO_LED, NO_LED },
    {     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43,     80,     81 },
    {     46, NO_LED,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56, NO_LED,     57,     44, NO_LED },
    {     78,     79,     13, NO_LED, NO_LED, NO_LED,     14, NO_LED, NO_LED,     29,     30, NO_LED,     45,     58,     59,     60 }
}, {
               {15 ,  0}, {29 ,  0}, {44 ,  0}, {59 ,  0}, {73 ,  0}, {88 ,  0}, {103,  0}, {118,  0}, {132,  0}, {147,  0}, {162,  0}, {176,  0}, {198,  0}, {39 , 64}, {94 , 64},
    {4  , 16}, {22 , 16}, {37 , 16}, {51 , 16}, {66 , 16}, {81 , 16}, {95 , 16}, {110, 16}, {125, 16}, {140, 16}, {154, 16}, {169, 16}, {184, 16}, {202, 16}, {147, 64}, {162, 64},
    {6  , 32}, {26 , 32}, {40 , 32}, {55 , 32}, {70 , 32}, {84 , 32}, {99 , 32}, {114, 32}, {129, 32}, {143, 32}, {158, 32}, {173, 32}, {196, 32}, {206, 48},            {176, 64},
    {9  , 48},            {33 , 48}, {48 , 48}, {62 , 48}, {77 , 48}, {92 , 48}, {106, 48}, {121, 48}, {136, 48}, {151, 48}, {165, 48}, {185, 48}, {191, 64}, {206, 64}, {220, 64},
    {92 ,  8}, {62 ,  8}, {33 ,  8}, {11 , 16}, {13 , 32}, {17 , 52}, {51 , 56}, {84 , 56}, {110, 56}, {147, 52}, {173, 52}, {198, 52}, {202, 28}, {206,  8}, {165,  8}, {136,  8},
    {0  ,  0},                                                                                                                                                {2  , 64}, {20 , 64},
                                                                                            {224, 20},                       {224, 36},
}, {
       4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,    1,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    4,                                        1, 1,
                            4,       4
} };
#endif
