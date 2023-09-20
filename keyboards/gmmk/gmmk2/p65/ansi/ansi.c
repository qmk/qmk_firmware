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

const aw20216s_led_t g_aw20216s_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1  },  //  0  Esc
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2  },  //  1  1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3  },  //  2  2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4  },  //  3  3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5  },  //  4  4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6  },  //  5  5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7  },  //  6  6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8  },  //  7  7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9  },  //  8  8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10 },  //  9  9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11 },  //  10 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12 },  //  11 -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5  },  //  12 =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7  },  //  13 Backspace
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4  },  //  14 Del

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1  },  //  15 Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2  },  //  16 Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3  },  //  17 W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4  },  //  18 E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5  },  //  19 R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6  },  //  20 T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7  },  //  21 Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8  },  //  22 U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9  },  //  23 I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10 },  //  24 O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11 },  //  25 P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12 },  //  26 [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8  },  //  27 ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9  },  //  28 \|
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7  },  //  29 PgUp

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1 },  //  30 Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2 },  //  31 A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3 },  //  32 S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4 },  //  33 D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5 },  //  34 F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6 },  //  35 G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7 },  //  36 H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8 },  //  37 J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9 },  //  38 K
    {0, CS10_SW10, CS11_SW10, CS12_SW10},  //  39 L
    {0, CS10_SW11, CS11_SW11, CS12_SW11},  //  40 ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12},  //  41 '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11 },  //  42 Enter
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5  },  //  43 PgDn

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1 },  //  44 Shift_L
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3 },  //  45 Z
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4 },  //  46 X
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5 },  //  47 C
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6 },  //  48 V
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7 },  //  49 B
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8 },  //  50 N
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9 },  //  51 M
    {0, CS13_SW10, CS14_SW10, CS15_SW10},  //  52 ,
    {0, CS13_SW11, CS14_SW11, CS15_SW11},  //  53 .
    {0, CS13_SW12, CS14_SW12, CS15_SW12},  //  54 /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8  },  //  55 Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9  },  //  56 Up
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6  },  //  57 END

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1 },  //  58 Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2 },  //  59 Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3 },  //  60 Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6 },  //  61 Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9 },  //  62 Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10},  //  63 FN
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10 },  //  64 Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11 },  //  65 Down
    {1, CS4_SW12,  CS5_SW12,  CS6_SW12 },  //  66 Right

    {1, CS13_SW1,  CS14_SW1,  CS15_SW1 },  //  69 LED 1
    {1, CS13_SW2,  CS14_SW2,  CS15_SW2 },  //  70 LED 2
    {1, CS13_SW3,  CS14_SW3,  CS15_SW3 },  //  71 LED 3
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4 },  //  72 LED 4
    {1, CS13_SW5,  CS14_SW5,  CS15_SW5 },  //  73 LED 5
    {1, CS13_SW6,  CS14_SW6,  CS15_SW6 },  //  74 LED 6
    {1, CS13_SW7,  CS14_SW7,  CS15_SW7 },  //  75 LED 7
    {1, CS13_SW8,  CS14_SW8,  CS15_SW8 },  //  76 LED 8
    {1, CS13_SW9,  CS14_SW9,  CS15_SW9 },  //  77 LED 9
    {1, CS13_SW10, CS14_SW10, CS15_SW10},  //  78 LED 10
    {1, CS16_SW1,  CS17_SW1,  CS18_SW1 },  //  79 LED 11
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2 },  //  80 LED 12
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3 },  //  81 LED 13
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4 },  //  82 LED 14
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5 },  //  83 LED 15
    {1, CS16_SW6,  CS17_SW6,  CS18_SW6 },  //  84 LED 16
    {1, CS16_SW7,  CS17_SW7,  CS18_SW7 },  //  85 LED 17
    {1, CS16_SW8,  CS17_SW8,  CS18_SW8 },  //  86 LED 18
    {1, CS16_SW9,  CS17_SW9,  CS18_SW9 },  //  87 LED 19
    {1, CS16_SW10, CS17_SW10, CS18_SW10}   //  88 LED 20
};

#define __ NO_LED

led_config_t g_led_config = {{
    { 44, 57, __, 64, __, 66, 58, 55},
    { 16, 15, 31,  0, 45, 59, __,  1},
    { 17, 30, 32, 60, 46, 14, 29,  2},
    { 18, 61, 33, 63, 47, 56, 62,  3},
    { 19, 20, 34, 35, 48, 49,  5,  4},
    { 22, 21, 37, 36, 51, 50,  6,  7},
    { 23, 27, 38, __, 52, 43, 12,  8},
    { 24, 13, 39, 65, 53, __, 28,  9},
    { 25, 26, 40, 41, 42, 54, 11, 10}
}, {
    {14,  0 }, //  0  Esc
    {28,  0 }, //  1  1
    {42,  0 }, //  2  2
    {56,  0 }, //  3  3
    {70,  0 }, //  4  4
    {84,  0 }, //  5  5
    {98,  0 }, //  6  6
    {112, 0 }, //  7  7
    {126, 0 }, //  8  8
    {140, 0 }, //  9  9
    {154, 0 }, //  10 0
    {168, 0 }, //  11 -
    {182, 0 }, //  12 =
    {196, 0 }, //  13 Backspace
    {210, 0 }, //  14 Del

    {14,  16}, //  15 Tab
    {28,  16}, //  16 Q
    {42,  16}, //  17 W
    {56,  16}, //  18 E
    {70,  16}, //  19 R
    {84,  16}, //  20 T
    {98,  16}, //  21 Y
    {112, 16}, //  22 U
    {126, 16}, //  23 I
    {140, 16}, //  24 O
    {154, 16}, //  25 P
    {168, 16}, //  26 [
    {182, 16}, //  27 ]
    {196, 16}, //  28 \|
    {210, 16}, //  29 PgUp

    {14,  32}, //  30 Caps Lock
    {28,  32}, //  31 A
    {42,  32}, //  32 S
    {56,  32}, //  33 D
    {70,  32}, //  34 F
    {84,  32}, //  35 G
    {98,  32}, //  36 H
    {112, 32}, //  37 J
    {126, 32}, //  38 K
    {140, 32}, //  39 L
    {154, 32}, //  40 ;
    {168, 32}, //  41 '
    {196, 32}, //  42 Enter
    {210, 32}, //  43 PgDn

    {14,  48}, //  44 Shift_L
    {42,  48}, //  45 Z
    {56,  48}, //  46 X
    {70,  48}, //  47 C
    {84,  48}, //  48 V
    {98,  48}, //  49 B
    {112, 48}, //  50 N
    {126, 48}, //  51 M
    {140, 48}, //  52 ,
    {154, 48}, //  53 .
    {168, 48}, //  54 /
    {182, 48}, //  55 Shift_R
    {196, 48}, //  56 Up
    {210, 48}, //  57 END

    {14,  64}, //  58 Ctrl_L
    {28,  64}, //  59 Win_L
    {42,  64}, //  60 Alt_L
    {84,  64}, //  61 Space
    {126, 64}, //  62 Alt_R
    {140, 64}, //  63 FN
    {182, 64}, //  64 Left
    {196, 64}, //  65 Down
    {210, 64}, //  66 Right

    {0,   0},  //  69 LED 1
    {0,   7},  //  70 LED 2
    {0,   14}, //  71 LED 3
    {0,   21}, //  72 LED 4
    {0,   28}, //  73 LED 5
    {0,   35}, //  74 LED 6
    {0,   42}, //  75 LED 7
    {0,   49}, //  76 LED 8
    {0,   56}, //  77 LED 9
    {0,   64}, //  78 LED 10
    {224, 0 }, //  79 LED 11
    {224, 7 }, //  80 LED 12
    {224, 14}, //  81 LED 13
    {224, 21}, //  82 LED 14
    {224, 28}, //  83 LED 15
    {224, 35}, //  84 LED 16
    {224, 42}, //  85 LED 17
    {224, 49}, //  86 LED 18
    {224, 56}, //  87 LED 19
    {224, 64}, //  88 LED 20
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif
