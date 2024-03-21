/* Copyright 2022 Feker
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  G location
 *   |  |     B location
 *   |  |     |     R location
 *   |  |     |     | */
    {0, SW1_CS1,  SW3_CS1,  SW2_CS1},  // 0,   `~,              K10
    {0, SW1_CS2,  SW3_CS2,  SW2_CS2},  // 1,   1!,              K11
    {0, SW1_CS3,  SW3_CS3,  SW2_CS3},  // 2,   2@,              K12
    {0, SW1_CS4,  SW3_CS4,  SW2_CS4},  // 3,   3#,              K13
    {0, SW1_CS5,  SW3_CS5,  SW2_CS5},  // 4,   4$,              K14
    {0, SW1_CS6,  SW3_CS6,  SW2_CS6},  // 5,   5%,              K15
    {0, SW1_CS7,  SW3_CS7,  SW2_CS7},  // 6,   6^,              K16
    {0, SW1_CS8,  SW3_CS8,  SW2_CS8},  // 7,   7&,              K17
    {0, SW1_CS9,  SW3_CS9,  SW2_CS9},  // 8,   8*,              K18
    {0, SW1_CS10, SW3_CS10, SW2_CS10}, // 9,   9(,              K19
    {0, SW1_CS11, SW3_CS11, SW2_CS11}, // 10,  0),              K1A
    {0, SW1_CS12, SW3_CS12, SW2_CS12}, // 11,  -_,              K1B
    {0, SW1_CS13, SW3_CS13, SW2_CS13}, // 12,  =+,              K1C
    {0, SW1_CS14, SW3_CS14, SW2_CS14}, // 13,  Backspace,       K1D
    {0, SW1_CS15, SW3_CS15, SW2_CS15}, // 14,  Left Alt,        K52
    {0, SW1_CS16, SW3_CS16, SW2_CS16}, // 15,  Space,           K56

    {0, SW4_CS1,  SW6_CS1,  SW5_CS1},  // 16,  Tab,             K20
    {0, SW4_CS2,  SW6_CS2,  SW5_CS2},  // 17,  Q,               K21
    {0, SW4_CS3,  SW6_CS3,  SW5_CS3},  // 18,  W,               K22
    {0, SW4_CS4,  SW6_CS4,  SW5_CS4},  // 19,  E,               K23
    {0, SW4_CS5,  SW6_CS5,  SW5_CS5},  // 20,  R,               K24
    {0, SW4_CS6,  SW6_CS6,  SW5_CS6},  // 21,  T,               K25
    {0, SW4_CS7,  SW6_CS7,  SW5_CS7},  // 22,  Y,               K26
    {0, SW4_CS8,  SW6_CS8,  SW5_CS8},  // 23,  U,               K27
    {0, SW4_CS9,  SW6_CS9,  SW5_CS9},  // 24,  I,               K28
    {0, SW4_CS10, SW6_CS10, SW5_CS10}, // 25,  O,               K29
    {0, SW4_CS11, SW6_CS11, SW5_CS11}, // 26,  P,               K2A
    {0, SW4_CS12, SW6_CS12, SW5_CS12}, // 27,  [{,              K2B
    {0, SW4_CS13, SW6_CS13, SW5_CS13}, // 28,  ]},              K2C
    {0, SW4_CS14, SW6_CS14, SW5_CS14}, // 29,  \|,              K2D
    {0, SW4_CS15, SW6_CS15, SW5_CS15}, // 30,  Right Ctrl,      K5C
    {0, SW4_CS16, SW6_CS16, SW5_CS16}, // 31,  Function,        K5A

    {0, SW7_CS1,  SW9_CS1,  SW8_CS1},  // 32,  Caps Lock,       K30
    {0, SW7_CS2,  SW9_CS2,  SW8_CS2},  // 33,  A,               K31
    {0, SW7_CS3,  SW9_CS3,  SW8_CS3},  // 34,  S,               K32
    {0, SW7_CS4,  SW9_CS4,  SW8_CS4},  // 35,  D,               K33
    {0, SW7_CS5,  SW9_CS5,  SW8_CS5},  // 36,  F,               K34
    {0, SW7_CS6,  SW9_CS6,  SW8_CS6},  // 37,  G,               K35
    {0, SW7_CS7,  SW9_CS7,  SW8_CS7},  // 38,  H,               K36
    {0, SW7_CS8,  SW9_CS8,  SW8_CS8},  // 39,  J,               K37
    {0, SW7_CS9,  SW9_CS9,  SW8_CS9},  // 40,  K,               K38
    {0, SW7_CS10, SW9_CS10, SW8_CS10}, // 41,  L,               K39
    {0, SW7_CS11, SW9_CS11, SW8_CS11}, // 42,  ;:,              K3A
    {0, SW7_CS12, SW9_CS12, SW8_CS12}, // 43,  '",              K3B
    {0, SW7_CS13, SW9_CS13, SW8_CS13}, // 44,  Enter,           K3D
    {0, SW7_CS14, SW9_CS14, SW8_CS14}, // 45,  Up,              K4E
    {0, SW7_CS15, SW9_CS15, SW8_CS15}, // 46,  Num Lock LED
    {0, SW7_CS16, SW9_CS16, SW8_CS16}, // 47,  Right Alt,       K59

    {0, SW10_CS1,  SW12_CS1,  SW11_CS1},  // 48,  Left Shift,      K40
//  {0, SW10_CS2,  SW12_CS2,  SW11_CS2},  //      Unused LED
    {0, SW10_CS3,  SW12_CS3,  SW11_CS3},  // 49,  Z,               K42
    {0, SW10_CS4,  SW12_CS4,  SW11_CS4},  // 50,  X,               K43
    {0, SW10_CS5,  SW12_CS5,  SW11_CS5},  // 51,  C,               K44
    {0, SW10_CS6,  SW12_CS6,  SW11_CS6},  // 52,  V,               K45
    {0, SW10_CS7,  SW12_CS7,  SW11_CS7},  // 53,  B,               K46
    {0, SW10_CS8,  SW12_CS8,  SW11_CS8},  // 54,  N,               K47
    {0, SW10_CS9,  SW12_CS9,  SW11_CS9},  // 55,  M,               K48
    {0, SW10_CS10, SW12_CS10, SW11_CS10}, // 56,  ,<,              K49
    {0, SW10_CS11, SW12_CS11, SW11_CS11}, // 57,  .>,              K4A
    {0, SW10_CS12, SW12_CS12, SW11_CS12}, // 58,  /?,              K4B
    {0, SW10_CS13, SW12_CS13, SW11_CS13}, // 59,  Right Shift,     K4D
    {0, SW10_CS14, SW12_CS14, SW11_CS14}, // 60,  Left,            K5D
    {0, SW10_CS15, SW12_CS15, SW11_CS15}, // 61,  Down,            K5E
    {0, SW10_CS16, SW12_CS16, SW11_CS16}, // 62,  Right,           K5F

    {1, SW1_CS1,  SW3_CS1,  SW2_CS1},  // 63,  Underglow 20
    {1, SW1_CS2,  SW3_CS2,  SW2_CS2},  // 64,  Underglow 19
    {1, SW1_CS3,  SW3_CS3,  SW2_CS3},  // 65,  Underglow 18
    {1, SW1_CS4,  SW3_CS4,  SW2_CS4},  // 66,  Underglow 17
    {1, SW1_CS5,  SW3_CS5,  SW2_CS5},  // 67,  Underglow 16
    {1, SW1_CS6,  SW3_CS6,  SW2_CS6},  // 68,  Underglow 15
    {1, SW1_CS7,  SW3_CS7,  SW2_CS7},  // 69,  Underglow 14
    {1, SW1_CS8,  SW3_CS8,  SW2_CS8},  // 70,  Underglow 13
    {1, SW1_CS9,  SW3_CS9,  SW2_CS9},  // 71,  Underglow 12
    {1, SW1_CS10, SW3_CS10, SW2_CS10}, // 72,  Underglow 11
    {1, SW1_CS11, SW3_CS11, SW2_CS11}, // 73,  Underglow 10
    {1, SW1_CS12, SW3_CS12, SW2_CS12}, // 74,  Underglow 9
    {1, SW1_CS13, SW3_CS13, SW2_CS13}, // 75,  Underglow 8
    {1, SW1_CS14, SW3_CS14, SW2_CS14}, // 76,  Underglow 7
    {1, SW1_CS15, SW3_CS15, SW2_CS15}, // 77,  Underglow 6
    {1, SW1_CS16, SW3_CS16, SW2_CS16}, // 78,  Underglow 5

    {1, SW4_CS1,  SW6_CS1,  SW5_CS1},  // 79,  Esc,             K00
    {1, SW4_CS2,  SW6_CS2,  SW5_CS2},  // 80,  F1,              K01
    {1, SW4_CS3,  SW6_CS3,  SW5_CS3},  // 81,  F2,              K02
    {1, SW4_CS4,  SW6_CS4,  SW5_CS4},  // 82,  F3,              K03
    {1, SW4_CS5,  SW6_CS5,  SW5_CS5},  // 83,  F4,              K04
    {1, SW4_CS6,  SW6_CS6,  SW5_CS6},  // 84,  F5,              K05
    {1, SW4_CS7,  SW6_CS7,  SW5_CS7},  // 85,  F6,              K06
    {1, SW4_CS8,  SW6_CS8,  SW5_CS8},  // 86,  F7,              K07
    {1, SW4_CS9,  SW6_CS9,  SW5_CS9},  // 87,  F8,              K08
    {1, SW4_CS10, SW6_CS10, SW5_CS10}, // 88,  F9,              K09
    {1, SW4_CS11, SW6_CS11, SW5_CS11}, // 89,  F10,             K0A
    {1, SW4_CS12, SW6_CS12, SW5_CS12}, // 90,  F11,             K0B
    {1, SW4_CS13, SW6_CS13, SW5_CS13}, // 91,  F12,             K0C
    {1, SW4_CS14, SW6_CS14, SW5_CS14}, // 92,  Delete,          K0D
    {1, SW4_CS15, SW6_CS15, SW5_CS15}, // 93,  Left Ctrl,       K50
    {1, SW4_CS16, SW6_CS16, SW5_CS16}, // 94,  Left Windows,    K51

    {1, SW7_CS1,  SW9_CS1,  SW8_CS1},  // 95,  Underglow 21
    {1, SW7_CS2,  SW9_CS2,  SW8_CS2},  // 96,  Underglow 22
    {1, SW7_CS3,  SW9_CS3,  SW8_CS3},  // 97,  Underglow 23
    {1, SW7_CS4,  SW9_CS4,  SW8_CS4},  // 98,  Underglow 24
    {1, SW7_CS5,  SW9_CS5,  SW8_CS5},  // 99,  Knob LED 3,      K53
    {1, SW7_CS6,  SW9_CS6,  SW8_CS6},  // 100, Knob LED 2,      K54
    {1, SW7_CS7,  SW9_CS7,  SW8_CS7},  // 101, Knob LED 1,      K4F
    {1, SW7_CS8,  SW9_CS8,  SW8_CS8},  // 102, Insert,          K1F
    {1, SW7_CS9,  SW9_CS9,  SW8_CS9},  // 103, Page Up,         K3E
    {1, SW7_CS10, SW9_CS10, SW8_CS10}, // 104, Caps/Win/Scr LED
    {1, SW7_CS11, SW9_CS11, SW8_CS11}, // 105, End,             K2F
    {1, SW7_CS12, SW9_CS12, SW8_CS12}, // 106, Page Down,       K3F
    {1, SW7_CS13, SW9_CS13, SW8_CS13}, // 107, Underglow 1
    {1, SW7_CS14, SW9_CS14, SW8_CS14}, // 108, Underglow 2
    {1, SW7_CS15, SW9_CS15, SW8_CS15}, // 109, Underglow 3
    {1, SW7_CS16, SW9_CS16, SW8_CS16}, // 110, Underglow 4

    {1, SW10_CS1,  SW12_CS1,  SW11_CS1},  // 111, Underglow 25
    {1, SW10_CS2,  SW12_CS2,  SW11_CS2},  // 112, Underglow 26
    {1, SW10_CS3,  SW12_CS3,  SW11_CS3},  // 113, Underglow 27
    {1, SW10_CS4,  SW12_CS4,  SW11_CS4},  // 114, Underglow 28
    {1, SW10_CS5,  SW12_CS5,  SW11_CS5},  // 115, Underglow 29
    {1, SW10_CS6,  SW12_CS6,  SW11_CS6},  // 116, Underglow 30
    {1, SW10_CS7,  SW12_CS7,  SW11_CS7},  // 117, Underglow 31
    {1, SW10_CS8,  SW12_CS8,  SW11_CS8},  // 118, Underglow 32
    {1, SW10_CS9,  SW12_CS9,  SW11_CS9},  // 119, Underglow 33
    {1, SW10_CS10, SW12_CS10, SW11_CS10}, // 120, Underglow 34
    {1, SW10_CS11, SW12_CS11, SW11_CS11}, // 121, Underglow 35
    {1, SW10_CS12, SW12_CS12, SW11_CS12}, // 122, Underglow 36
    {1, SW10_CS13, SW12_CS13, SW11_CS13}, // 123, Underglow 37
    {1, SW10_CS14, SW12_CS14, SW11_CS14}, // 124, Underglow 38
    {1, SW10_CS15, SW12_CS15, SW11_CS15}, // 125, Underglow 39
    {1, SW10_CS16, SW12_CS16, SW11_CS16}, // 126, Underglow 40
};

led_config_t g_led_config = { {
    { 79,     80,     81,     82,     83,     84,     85,     86,     87,     88,     89,     90,     91,     92, NO_LED, NO_LED },
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13, NO_LED,    102 },
    { 16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29, NO_LED,    105 },
    { 32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43, NO_LED,     44,    103,    106 },
    { 48, NO_LED,     49,     50,     51,     52,     53,     54,     55,     56,     57,     58, NO_LED,     59,     45,    101 },
    { 93,     94,     14, NO_LED, NO_LED, NO_LED,     15, NO_LED, NO_LED,     30,     31, NO_LED,     47,     60,     61,     62 }
}, {
    {0  , 15}, {14 , 15}, {29 , 15}, {43 , 15}, {58 , 15}, {72 , 15}, {87 , 15}, {101, 15}, {116, 15}, {130, 15}, {145, 15}, {159, 15}, {173, 15}, {195, 15}, {38 , 61}, {92 , 61},
    {4  , 26}, {22 , 26}, {36 , 26}, {51 , 26}, {65 , 26}, {79 , 26}, {94 , 26}, {108, 26}, {123, 26}, {137, 26}, {152, 26}, {166, 26}, {181, 26}, {199, 26}, {173, 61}, {159, 61},
    {5  , 38}, {25 , 38}, {40 , 38}, {54 , 38}, {69 , 38}, {83 , 38}, {98 , 38}, {112, 38}, {126, 38}, {141, 38}, {155, 38}, {170, 38}, {193, 38}, {206, 52}, {210, 12}, {145, 61},
    {9  , 49},            {33 , 49}, {47 , 49}, {61 , 49}, {76 , 49}, {90 , 49}, {105, 49}, {119, 49}, {134, 49}, {148, 49}, {163, 49}, {182, 49}, {191, 64}, {206, 64}, {220, 64},
    {14 ,  0}, {28 ,  0}, {53 ,  0}, {63 ,  0}, {74 ,  0}, {88 ,  0}, {102,  0}, {116,  0}, {130,  0}, {144,  0}, {158,  0}, {172,  0}, {189,  0}, {210,  0}, {224,  0}, {224, 11},
    {0  ,  0}, {18 ,  0}, {33 ,  0}, {47 ,  0}, {61 ,  0}, {79 ,  0}, {94 ,  0}, {108,  0}, {123,  0}, {141,  0}, {155,  0}, {170,  0}, {184,  0}, {202,  0}, {2  , 61}, {20 , 61},
    {0  ,  0}, {0  , 11}, {0  , 27}, {0  , 37}, {224,  5}, {210,  5}, {217,  0}, {224, 15}, {224, 38}, {210, 18}, {224, 26}, {224, 49}, {224, 56}, {224, 45}, {224, 35}, {224, 24},
    {0  , 48}, {0  , 56}, {0  , 64}, {14 , 64}, {28 , 64}, {49 , 64}, {67 , 64}, {84 , 64}, {98 , 64}, {112, 64}, {126, 64}, {140, 64}, {158, 64}, {172, 64}, {196, 64}, {224, 64},
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 8, 1,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    2, 2, 2, 2, 1, 1, 4, 4, 4, 8, 4, 4, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif
