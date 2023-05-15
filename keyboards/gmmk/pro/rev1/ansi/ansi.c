/* Copyright 2021 Gigahawk
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

#include "ansi.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = {{
    { 4,      NO_LED, NO_LED, 95,     65,     79, 5,      28 },
    { 8,      2,      9,      0,      10,     75, 1,      7  },
    { 14,     3,      15,     NO_LED, 16,     86, 6,      13 },
    { 20,     18,     21,     23,     22,     94, 12,     19 },
    { 25,     30,     26,     31,     27,     32, 29,     24 },
    { 41,     36,     42,     37,     43,     38, 35,     40 },
    { 46,     89,     47,     34,     48,     72, 78,     45 },
    { 52,     39,     53,     97,     54,     82, 44,     51 },
    { 58,     63,     59,     64,     NO_LED, 60, 62,     57 },
    { 11,     90,     55,     17,     33,     49, NO_LED, 69 },
    { NO_LED, 85,     93,     61,     96,     66, 50,     56 }
}, {
    {0, 0},     // 0, ESC, k13
    {0, 15},    // 1, ~, k16
    {4, 26},    // 2, Tab, k11
    {5, 38},    // 3, Caps, k21
    {9, 49},    // 4, Sh_L, k00
    {2, 61},    // 5, Ct_L, k06
    {18, 0},    // 6, F1, k26
    {14, 15},   // 7, 1, k17
    {22, 26},   // 8, Q, k10
    {25, 38},   // 9, A, k12
    {33, 49},   // 10, Z, k14
    {20, 61},   // 11, Win_L, k90
    {33, 0},    // 12, F2, k36
    {29, 15},   // 13, 2, k27
    {36, 26},   // 14, W, k20
    {40, 38},   // 15, S, k22
    {47, 49},   // 16, X, k24
    {38, 61},   // 17, Alt_L, k93
    {47, 0},    // 18, F3, k31
    {43, 15},   // 19, 3, k37
    {51, 26},   // 20, E, k30
    {54, 38},   // 21, D, k32
    {61, 49},   // 22, C, k34
    {61, 0},    // 23, F4, k33
    {58, 15},   // 24, 4, k47
    {65, 26},   // 25, R, k40
    {69, 38},   // 26, F, k42
    {76, 49},   // 27, V, k44
    {79, 0},    // 28, F5, k07
    {72, 15},   // 29, 5, k46
    {79, 26},   // 30, T, k41
    {83, 38},   // 31, G, k43
    {90, 49},   // 32, B, k45
    {92, 61},   // 33, SPACE, k94
    {94, 0},    // 34, F6, k63
    {87, 15},   // 35, 6, k56
    {94, 26},   // 36, Y, k51
    {98, 38},   // 37, H, k53
    {105, 49},  // 38, N, k55
    {108, 0},   // 39, F7, k71
    {101, 15},  // 40, 7, k57
    {108, 26},  // 41, U, k50
    {112, 38},  // 42, J, k52
    {119, 49},  // 43, M, k54
    {123, 0},   // 44, F8, k76
    {116, 15},  // 45, 8, k67
    {123, 26},  // 46, I, k60
    {126, 38},  // 47, K, k62
    {134, 49},  // 48, ,, k64
    {145, 61},  // 49, Alt_R, k95
    {141, 0},   // 50, F9, ka6
    {130, 15},  // 51, 9, k77
    {137, 26},  // 52, O, k70
    {141, 38},  // 53, L, k72
    {148, 49},  // 54, ., k74
    {159, 61},  // 55, FN, k92
    {155, 0},   // 56, F10, ka7
    {145, 15},  // 57, 0, k87
    {152, 26},  // 58, P, k80
    {155, 38},  // 59, ;, k82
    {163, 49},  // 60, ?, k85
    {170, 0},   // 61, F11, ka3
    {159, 15},  // 62, -, k86
    {166, 26},  // 63, [, k81
    {170, 38},  // 64, ", k83
    {173, 61},  // 65, Ct_R, k04
    {184, 0},   // 66, F12, ka5
    {0, 8},     // 67, LED, l01
    {224, 8},   // 68, LED, l11
    {202, 0},   // 69, Prt, k97
    {0, 15},    // 70, LED, l02
    {224, 15},  // 71, LED, l12
    {224, 15},  // 72, Del, k65
    {0, 21},    // 73, LED, l03
    {224, 21},  // 74, LED, l13
    {224, 26},  // 75, PgUp, k15
    {0, 28},    // 76, LED, l04
    {224, 28},  // 77, LED, l14
    {173, 15},  // 78, =, k66
    {220, 64},  // 79, Right, k05
    {0, 35},    // 80, LED, l05
    {224, 35},  // 81, LED, l15
    {224, 49},  // 82, End, k75
    {0, 42},    // 83, LED, l06
    {224, 42},  // 84, LED, l16
    {195, 15},  // 85, BSpc, ka1
    {224, 38},  // 86, PgDn, k25
    {0, 48},    // 87, LED, l07
    {224, 48},  // 88, LED, l17
    {181, 26},  // 89, ], k61
    {182, 49},  // 90, Sh_R, k91
    {0, 55},    // 91, LED, l08
    {224, 55},  // 92, LED, l18
    {199, 26},  // 93, \, ka2
    {206, 52},  // 94, Up, k35
    {191, 64},  // 95, Left, k03
    {193, 38},  // 96, Enter, ka4
    {206, 64}   // 97, Down, k73
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 4, 2, 2, 4, 2, 2,
    4, 2, 2, 4, 4, 2, 2, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 4, 4, 4
}};

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS1_SW1, CS2_SW1, CS3_SW1},        //  0, ESC, k13
    {0, CS4_SW1, CS5_SW1, CS6_SW1},        //  1, ~, k16
    {0, CS7_SW1, CS8_SW1, CS9_SW1},        //  2, Tab, k11
    {0, CS10_SW1, CS11_SW1, CS12_SW1},     //  3, Caps, k21
    {0, CS13_SW1, CS14_SW1, CS15_SW1},     //  4, Sh_L, k00
    {0, CS16_SW1, CS17_SW1, CS18_SW1},     //  5, Ct_L, k06
    {0, CS1_SW2, CS2_SW2, CS3_SW2},        //  6, F1, k26
    {0, CS4_SW2, CS5_SW2, CS6_SW2},        //  7, 1, k17
    {0, CS7_SW2, CS8_SW2, CS9_SW2},        //  8, Q, k10
    {0, CS10_SW2, CS11_SW2, CS12_SW2},     //  9, A, k12
    {0, CS13_SW2, CS14_SW2, CS15_SW2},     //  10, Z, k14
    {0, CS16_SW2, CS17_SW2, CS18_SW2},     //  11, Win_L, k90
    {0, CS1_SW3, CS2_SW3, CS3_SW3},        //  12, F2, k36
    {0, CS4_SW3, CS5_SW3, CS6_SW3},        //  13, 2, k27
    {0, CS7_SW3, CS8_SW3, CS9_SW3},        //  14, W, k20
    {0, CS10_SW3, CS11_SW3, CS12_SW3},     //  15, S, k22
    {0, CS13_SW3, CS14_SW3, CS15_SW3},     //  16, X, k24
    {0, CS16_SW3, CS17_SW3, CS18_SW3},     //  17, Alt_L, k93
    {0, CS1_SW4, CS2_SW4, CS3_SW4},        //  18, F3, k31
    {0, CS4_SW4, CS5_SW4, CS6_SW4},        //  19, 3, k37
    {0, CS7_SW4, CS8_SW4, CS9_SW4},        //  20, E, k30
    {0, CS10_SW4, CS11_SW4, CS12_SW4},     //  21, D, k32
    {0, CS13_SW4, CS14_SW4, CS15_SW4},     //  22, C, k34
    {0, CS1_SW5, CS2_SW5, CS3_SW5},        //  23, F4, k33
    {0, CS4_SW5, CS5_SW5, CS6_SW5},        //  24, 4, k47
    {0, CS7_SW5, CS8_SW5, CS9_SW5},        //  25, R, k40
    {0, CS10_SW5, CS11_SW5, CS12_SW5},     //  26, F, k42
    {0, CS13_SW5, CS14_SW5, CS15_SW5},     //  27, V, k44
    {0, CS1_SW6, CS2_SW6, CS3_SW6},        //  28, F5, k07
    {0, CS4_SW6, CS5_SW6, CS6_SW6},        //  29, 5, k46
    {0, CS7_SW6, CS8_SW6, CS9_SW6},        //  30, T, k41
    {0, CS10_SW6, CS11_SW6, CS12_SW6},     //  31, G, k43
    {0, CS13_SW6, CS14_SW6, CS15_SW6},     //  32, B, k45
    {0, CS16_SW6, CS17_SW6, CS18_SW6},     //  33, SPACE, k94
    {0, CS1_SW7, CS2_SW7, CS3_SW7},        //  34, F6, k63
    {0, CS4_SW7, CS5_SW7, CS6_SW7},        //  35, 6, k56
    {0, CS7_SW7, CS8_SW7, CS9_SW7},        //  36, Y, k51
    {0, CS10_SW7, CS11_SW7, CS12_SW7},     //  37, H, k53
    {0, CS13_SW7, CS14_SW7, CS15_SW7},     //  38, N, k55
    {0, CS1_SW8, CS2_SW8, CS3_SW8},        //  39, F7, k71
    {0, CS4_SW8, CS5_SW8, CS6_SW8},        //  40, 7, k57
    {0, CS7_SW8, CS8_SW8, CS9_SW8},        //  41, U, k50
    {0, CS10_SW8, CS11_SW8, CS12_SW8},     //  42, J, k52
    {0, CS13_SW8, CS14_SW8, CS15_SW8},     //  43, M, k54
    {0, CS1_SW9, CS2_SW9, CS3_SW9},        //  44, F8, k76
    {0, CS4_SW9, CS5_SW9, CS6_SW9},        //  45, 8, k67
    {0, CS7_SW9, CS8_SW9, CS9_SW9},        //  46, I, k60
    {0, CS10_SW9, CS11_SW9, CS12_SW9},     //  47, K, k62
    {0, CS13_SW9, CS14_SW9, CS15_SW9},     //  48, ,, k64
    {0, CS16_SW9, CS17_SW9, CS18_SW9},     //  49, Alt_R, k95
    {0, CS1_SW10, CS2_SW10, CS3_SW10},     //  50, F9, ka6
    {0, CS4_SW10, CS5_SW10, CS6_SW10},     //  51, 9, k77
    {0, CS7_SW10, CS8_SW10, CS9_SW10},     //  52, O, k70
    {0, CS10_SW10, CS11_SW10, CS12_SW10},  //  53, L, k72
    {0, CS13_SW10, CS14_SW10, CS15_SW10},  //  54, ., k74
    {0, CS16_SW10, CS17_SW10, CS18_SW10},  //  55, FN, k92
    {0, CS1_SW11, CS2_SW11, CS3_SW11},     //  56, F10, ka7
    {0, CS4_SW11, CS5_SW11, CS6_SW11},     //  57, 0, k87
    {0, CS7_SW11, CS8_SW11, CS9_SW11},     //  58, P, k80
    {0, CS10_SW11, CS11_SW11, CS12_SW11},  //  59, ;, k82
    {0, CS13_SW11, CS14_SW11, CS15_SW11},  //  60, ?, k85
    {0, CS1_SW12, CS2_SW12, CS3_SW12},     //  61, F11, ka3
    {0, CS4_SW12, CS5_SW12, CS6_SW12},     //  62, -, k86
    {0, CS7_SW12, CS8_SW12, CS9_SW12},     //  63, [, k81
    {0, CS10_SW12, CS11_SW12, CS12_SW12},  //  64, ", k83
    {0, CS16_SW12, CS17_SW12, CS18_SW12},  //  65, Ct_R, k04

    {1, CS1_SW1, CS2_SW1, CS3_SW1},     //  66, F12, ka5
    {1, CS13_SW1, CS14_SW1, CS15_SW1},  //  67, LED, l01
    {1, CS16_SW1, CS17_SW1, CS18_SW1},  //  68, LED, l11
    {1, CS4_SW2, CS5_SW2, CS6_SW2},     //  69, Prt, k97
    {1, CS13_SW2, CS14_SW2, CS15_SW2},  //  70, LED, l02
    {1, CS16_SW2, CS17_SW2, CS18_SW2},  //  71, LED, l12
    {1, CS4_SW3, CS5_SW3, CS6_SW3},     //  72, Del, k65
    {1, CS13_SW3, CS14_SW3, CS15_SW3},  //  73, LED, l03
    {1, CS16_SW3, CS17_SW3, CS18_SW3},  //  74, LED, l13
    {1, CS4_SW4, CS5_SW4, CS6_SW4},     //  75, PgUp, k15
    {1, CS13_SW4, CS14_SW4, CS15_SW4},  //  76, LED, l04
    {1, CS16_SW4, CS17_SW4, CS18_SW4},  //  77, LED, l14
    {1, CS1_SW5, CS2_SW5, CS3_SW5},     //  78, =, k66
    {1, CS10_SW5, CS11_SW5, CS12_SW5},  //  79, Right, k05
    {1, CS13_SW5, CS14_SW5, CS15_SW5},  //  80, LED, l05
    {1, CS16_SW5, CS17_SW5, CS18_SW5},  //  81, LED, l15
    {1, CS4_SW6, CS5_SW6, CS6_SW6},     //  82, End, k75
    {1, CS13_SW6, CS14_SW6, CS15_SW6},  //  83, LED, l06
    {1, CS16_SW6, CS17_SW6, CS18_SW6},  //  84, LED, l16
    {1, CS1_SW7, CS2_SW7, CS3_SW7},     //  85, BSpc, ka1
    {1, CS4_SW7, CS5_SW7, CS6_SW7},     //  86, PgDn, k25
    {1, CS13_SW7, CS14_SW7, CS15_SW7},  //  87, LED, l07
    {1, CS16_SW7, CS17_SW7, CS18_SW7},  //  88, LED, l17
    {1, CS1_SW8, CS2_SW8, CS3_SW8},     //  89, ], k61
    {1, CS4_SW8, CS5_SW8, CS6_SW8},     //  90, Sh_R, k91
    {1, CS13_SW8, CS14_SW8, CS15_SW8},  //  91, LED, l08
    {1, CS16_SW8, CS17_SW8, CS18_SW8},  //  92, LED, l18
    {1, CS1_SW9, CS2_SW9, CS3_SW9},     //  93, \, ka2
    {1, CS4_SW9, CS5_SW9, CS6_SW9},     //  94, Up, k35
    {1, CS4_SW10, CS5_SW10, CS6_SW10},  //  95, Left, k03
    {1, CS1_SW11, CS2_SW11, CS3_SW11},  //  96, Enter, ka4
    {1, CS4_SW11, CS5_SW11, CS6_SW11},  //  97, Down, k73
};
// clang-format on
#endif
