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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3  },  //  0  Esc
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6  },  //  1  1
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6  },  //  2  2
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6  },  //  3  3
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6  },  //  4  4
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6  },  //  5  5
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6  },  //  6  6
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6  },  //  7  7
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6  },  //  8  8
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6 },  //  9  9
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6 },  //  10 0
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6 },  //  11 -
    {1, SW5_CS1,   SW5_CS2,   SW5_CS3  },  //  12 =
    {1, SW7_CS1,   SW7_CS2,   SW7_CS3  },  //  13 Backspace
    {1, SW4_CS4,   SW4_CS5,   SW4_CS6  },  //  14 Del

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9  },  //  15 Tab
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9  },  //  16 Q
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9  },  //  17 W
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9  },  //  18 E
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9  },  //  19 R
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9  },  //  20 T
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9  },  //  21 Y
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9  },  //  22 U
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9  },  //  23 I
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9 },  //  24 O
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9 },  //  25 P
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9 },  //  26 [
    {1, SW8_CS1,   SW8_CS2,   SW8_CS3  },  //  27 ]
    {1, SW9_CS1,   SW9_CS2,   SW9_CS3  },  //  28 \|
    {1, SW7_CS4,   SW7_CS5,   SW7_CS6  },  //  29 PgUp

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12 },  //  30 Caps Lock
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12 },  //  31 A
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12 },  //  32 S
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12 },  //  33 D
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12 },  //  34 F
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12 },  //  35 G
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12 },  //  36 H
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12 },  //  37 J
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12 },  //  38 K
    {0, SW10_CS10, SW10_CS11, SW10_CS12},  //  39 L
    {0, SW11_CS10, SW11_CS11, SW11_CS12},  //  40 ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12},  //  41 '
    {1, SW11_CS1,  SW11_CS2,  SW11_CS3 },  //  42 Enter
    {1, SW5_CS4,   SW5_CS5,   SW5_CS6  },  //  43 PgDn

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15 },  //  44 Shift_L
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15 },  //  45 Z
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15 },  //  46 X
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15 },  //  47 C
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15 },  //  48 V
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15 },  //  49 B
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15 },  //  50 N
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15 },  //  51 M
    {0, SW10_CS13, SW10_CS14, SW10_CS15},  //  52 ,
    {0, SW11_CS13, SW11_CS14, SW11_CS15},  //  53 .
    {0, SW12_CS13, SW12_CS14, SW12_CS15},  //  54 /
    {1, SW8_CS4,   SW8_CS5,   SW8_CS6  },  //  55 Shift_R
    {1, SW9_CS4,   SW9_CS5,   SW9_CS6  },  //  56 Up
    {1, SW6_CS4,   SW6_CS5,   SW6_CS6  },  //  57 END

    {0, SW1_CS16,  SW1_CS17,  SW1_CS18 },  //  58 Ctrl_L
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18 },  //  59 Win_L
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18 },  //  60 Alt_L
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18 },  //  61 Space
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18 },  //  62 Alt_R
    {0, SW10_CS16, SW10_CS17, SW10_CS18},  //  63 FN
    {1, SW10_CS4,  SW10_CS5,  SW10_CS6 },  //  64 Left
    {1, SW11_CS4,  SW11_CS5,  SW11_CS6 },  //  65 Down
    {1, SW12_CS4,  SW12_CS5,  SW12_CS6 },  //  66 Right

    {1, SW1_CS13,  SW1_CS14,  SW1_CS15 },  //  69 LED 1
    {1, SW2_CS13,  SW2_CS14,  SW2_CS15 },  //  70 LED 2
    {1, SW3_CS13,  SW3_CS14,  SW3_CS15 },  //  71 LED 3
    {1, SW4_CS13,  SW4_CS14,  SW4_CS15 },  //  72 LED 4
    {1, SW5_CS13,  SW5_CS14,  SW5_CS15 },  //  73 LED 5
    {1, SW6_CS13,  SW6_CS14,  SW6_CS15 },  //  74 LED 6
    {1, SW7_CS13,  SW7_CS14,  SW7_CS15 },  //  75 LED 7
    {1, SW8_CS13,  SW8_CS14,  SW8_CS15 },  //  76 LED 8
    {1, SW9_CS13,  SW9_CS14,  SW9_CS15 },  //  77 LED 9
    {1, SW10_CS13, SW10_CS14, SW10_CS15},  //  78 LED 10
    {1, SW1_CS16,  SW1_CS17,  SW1_CS18 },  //  79 LED 11
    {1, SW2_CS16,  SW2_CS17,  SW2_CS18 },  //  80 LED 12
    {1, SW3_CS16,  SW3_CS17,  SW3_CS18 },  //  81 LED 13
    {1, SW4_CS16,  SW4_CS17,  SW4_CS18 },  //  82 LED 14
    {1, SW5_CS16,  SW5_CS17,  SW5_CS18 },  //  83 LED 15
    {1, SW6_CS16,  SW6_CS17,  SW6_CS18 },  //  84 LED 16
    {1, SW7_CS16,  SW7_CS17,  SW7_CS18 },  //  85 LED 17
    {1, SW8_CS16,  SW8_CS17,  SW8_CS18 },  //  86 LED 18
    {1, SW9_CS16,  SW9_CS17,  SW9_CS18 },  //  87 LED 19
    {1, SW10_CS16, SW10_CS17, SW10_CS18}   //  88 LED 20
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
