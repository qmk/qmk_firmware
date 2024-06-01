/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
    {0, SW1_CS1, SW1_CS2, SW1_CS3},        //  0, ESC, k13
    {0, SW1_CS4, SW1_CS5, SW1_CS6},        //  1, ~, k16
    {0, SW1_CS7, SW1_CS8, SW1_CS9},        //  2, Tab, k11
    {0, SW1_CS10, SW1_CS11, SW1_CS12},     //  3, Caps, k21
    {0, SW1_CS13, SW1_CS14, SW1_CS15},     //  4, Sh_L, k00
    {0, SW1_CS16, SW1_CS17, SW1_CS18},     //  5, Ct_L, k06
    {0, SW2_CS1, SW2_CS2, SW2_CS3},        //  6, F1, k26
    {0, SW2_CS4, SW2_CS5, SW2_CS6},        //  7, 1, k17
    {0, SW2_CS7, SW2_CS8, SW2_CS9},        //  8, Q, k10
    {0, SW2_CS10, SW2_CS11, SW2_CS12},     //  9, A, k12
    {0, SW2_CS13, SW2_CS14, SW2_CS15},     //  10, Z, k14
    {0, SW2_CS16, SW2_CS17, SW2_CS18},     //  11, Win_L, k90
    {0, SW3_CS1, SW3_CS2, SW3_CS3},        //  12, F2, k36
    {0, SW3_CS4, SW3_CS5, SW3_CS6},        //  13, 2, k27
    {0, SW3_CS7, SW3_CS8, SW3_CS9},        //  14, W, k20
    {0, SW3_CS10, SW3_CS11, SW3_CS12},     //  15, S, k22
    {0, SW3_CS13, SW3_CS14, SW3_CS15},     //  16, X, k24
    {0, SW3_CS16, SW3_CS17, SW3_CS18},     //  17, Alt_L, k93
    {0, SW4_CS1, SW4_CS2, SW4_CS3},        //  18, F3, k31
    {0, SW4_CS4, SW4_CS5, SW4_CS6},        //  19, 3, k37
    {0, SW4_CS7, SW4_CS8, SW4_CS9},        //  20, E, k30
    {0, SW4_CS10, SW4_CS11, SW4_CS12},     //  21, D, k32
    {0, SW4_CS13, SW4_CS14, SW4_CS15},     //  22, C, k34
    {0, SW5_CS1, SW5_CS2, SW5_CS3},        //  23, F4, k33
    {0, SW5_CS4, SW5_CS5, SW5_CS6},        //  24, 4, k47
    {0, SW5_CS7, SW5_CS8, SW5_CS9},        //  25, R, k40
    {0, SW5_CS10, SW5_CS11, SW5_CS12},     //  26, F, k42
    {0, SW5_CS13, SW5_CS14, SW5_CS15},     //  27, V, k44
    {0, SW6_CS1, SW6_CS2, SW6_CS3},        //  28, F5, k07
    {0, SW6_CS4, SW6_CS5, SW6_CS6},        //  29, 5, k46
    {0, SW6_CS7, SW6_CS8, SW6_CS9},        //  30, T, k41
    {0, SW6_CS10, SW6_CS11, SW6_CS12},     //  31, G, k43
    {0, SW6_CS13, SW6_CS14, SW6_CS15},     //  32, B, k45
    {0, SW6_CS16, SW6_CS17, SW6_CS18},     //  33, SPACE, k94
    {0, SW7_CS1, SW7_CS2, SW7_CS3},        //  34, F6, k63
    {0, SW7_CS4, SW7_CS5, SW7_CS6},        //  35, 6, k56
    {0, SW7_CS7, SW7_CS8, SW7_CS9},        //  36, Y, k51
    {0, SW7_CS10, SW7_CS11, SW7_CS12},     //  37, H, k53
    {0, SW7_CS13, SW7_CS14, SW7_CS15},     //  38, N, k55
    {0, SW8_CS1, SW8_CS2, SW8_CS3},        //  39, F7, k71
    {0, SW8_CS4, SW8_CS5, SW8_CS6},        //  40, 7, k57
    {0, SW8_CS7, SW8_CS8, SW8_CS9},        //  41, U, k50
    {0, SW8_CS10, SW8_CS11, SW8_CS12},     //  42, J, k52
    {0, SW8_CS13, SW8_CS14, SW8_CS15},     //  43, M, k54
    {0, SW9_CS1, SW9_CS2, SW9_CS3},        //  44, F8, k76
    {0, SW9_CS4, SW9_CS5, SW9_CS6},        //  45, 8, k67
    {0, SW9_CS7, SW9_CS8, SW9_CS9},        //  46, I, k60
    {0, SW9_CS10, SW9_CS11, SW9_CS12},     //  47, K, k62
    {0, SW9_CS13, SW9_CS14, SW9_CS15},     //  48, ,, k64
    {0, SW9_CS16, SW9_CS17, SW9_CS18},     //  49, Alt_R, k95
    {0, SW10_CS1, SW10_CS2, SW10_CS3},     //  50, F9, ka6
    {0, SW10_CS4, SW10_CS5, SW10_CS6},     //  51, 9, k77
    {0, SW10_CS7, SW10_CS8, SW10_CS9},     //  52, O, k70
    {0, SW10_CS10, SW10_CS11, SW10_CS12},  //  53, L, k72
    {0, SW10_CS13, SW10_CS14, SW10_CS15},  //  54, ., k74
    {0, SW10_CS16, SW10_CS17, SW10_CS18},  //  55, FN, k92
    {0, SW11_CS1, SW11_CS2, SW11_CS3},     //  56, F10, ka7
    {0, SW11_CS4, SW11_CS5, SW11_CS6},     //  57, 0, k87
    {0, SW11_CS7, SW11_CS8, SW11_CS9},     //  58, P, k80
    {0, SW11_CS10, SW11_CS11, SW11_CS12},  //  59, ;, k82
    {0, SW11_CS13, SW11_CS14, SW11_CS15},  //  60, ?, k85
    {0, SW12_CS1, SW12_CS2, SW12_CS3},     //  61, F11, ka3
    {0, SW12_CS4, SW12_CS5, SW12_CS6},     //  62, -, k86
    {0, SW12_CS7, SW12_CS8, SW12_CS9},     //  63, [, k81
    {0, SW12_CS10, SW12_CS11, SW12_CS12},  //  64, ", k83
    {0, SW12_CS16, SW12_CS17, SW12_CS18},  //  65, Ct_R, k04

    {1, SW1_CS1, SW1_CS2, SW1_CS3},     //  66, F12, ka5
    {1, SW1_CS13, SW1_CS14, SW1_CS15},  //  67, LED, l01
    {1, SW1_CS16, SW1_CS17, SW1_CS18},  //  68, LED, l11
    {1, SW2_CS4, SW2_CS5, SW2_CS6},     //  69, Prt, k97
    {1, SW2_CS13, SW2_CS14, SW2_CS15},  //  70, LED, l02
    {1, SW2_CS16, SW2_CS17, SW2_CS18},  //  71, LED, l12
    {1, SW3_CS4, SW3_CS5, SW3_CS6},     //  72, Del, k65
    {1, SW3_CS13, SW3_CS14, SW3_CS15},  //  73, LED, l03
    {1, SW3_CS16, SW3_CS17, SW3_CS18},  //  74, LED, l13
    {1, SW4_CS4, SW4_CS5, SW4_CS6},     //  75, PgUp, k15
    {1, SW4_CS13, SW4_CS14, SW4_CS15},  //  76, LED, l04
    {1, SW4_CS16, SW4_CS17, SW4_CS18},  //  77, LED, l14
    {1, SW5_CS1, SW5_CS2, SW5_CS3},     //  78, =, k66
    {1, SW5_CS10, SW5_CS11, SW5_CS12},  //  79, Right, k05
    {1, SW5_CS13, SW5_CS14, SW5_CS15},  //  80, LED, l05
    {1, SW5_CS16, SW5_CS17, SW5_CS18},  //  81, LED, l15
    {1, SW6_CS4, SW6_CS5, SW6_CS6},     //  82, End, k75
    {1, SW6_CS13, SW6_CS14, SW6_CS15},  //  83, LED, l06
    {1, SW6_CS16, SW6_CS17, SW6_CS18},  //  84, LED, l16
    {1, SW7_CS1, SW7_CS2, SW7_CS3},     //  85, BSpc, ka1
    {1, SW7_CS4, SW7_CS5, SW7_CS6},     //  86, PgDn, k25
    {1, SW7_CS13, SW7_CS14, SW7_CS15},  //  87, LED, l07
    {1, SW7_CS16, SW7_CS17, SW7_CS18},  //  88, LED, l17
    {1, SW8_CS1, SW8_CS2, SW8_CS3},     //  89, ], k61
    {1, SW8_CS4, SW8_CS5, SW8_CS6},     //  90, Sh_R, k91
    {1, SW8_CS13, SW8_CS14, SW8_CS15},  //  91, LED, l08
    {1, SW8_CS16, SW8_CS17, SW8_CS18},  //  92, LED, l18
    {1, SW9_CS1, SW9_CS2, SW9_CS3},     //  93, \, ka2
    {1, SW9_CS4, SW9_CS5, SW9_CS6},     //  94, Up, k35
    {1, SW10_CS4, SW10_CS5, SW10_CS6},  //  95, Left, k03
    {1, SW11_CS1, SW11_CS2, SW11_CS3},  //  96, Enter, ka4
    {1, SW11_CS4, SW11_CS5, SW11_CS6},  //  97, Down, k73
};
// clang-format on
#endif
