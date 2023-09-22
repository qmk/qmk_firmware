// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

// clang-format off

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1   },  //  0  Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2   },  //  1  1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3   },  //  2  2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4   },  //  3  3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5   },  //  4  4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6   },  //  5  5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7   },  //  6  6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8   },  //  7  7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9   },  //  8  8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10  },  //  9  9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11  },  //  10 0
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12  },  //  11 -
    {0, CS16_SW1,  CS17_SW1,  CS18_SW1  },  //  12 =
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2  },  //  13 Backspace

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1   },  //  14 Tab
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2   },  //  15 Q
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3   },  //  16 W
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4   },  //  17 E
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5   },  //  18 R
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6   },  //  19 T
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7   },  //  20 Y
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8   },  //  21 U
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9   },  //  22 I
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10  },  //  23 O
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11  },  //  24 P
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12  },  //  25 [
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4  },  //  26 ]
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5  },  //  27 \|
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3  },  //  28 Del

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1   },  //  29 Caps Lock
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2   },  //  30 A
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3   },  //  31 S
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4   },  //  32 D
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5   },  //  33 F
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6   },  //  34 G
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7   },  //  35 H
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8   },  //  36 J
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9   },  //  37 K
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10  },  //  38 L
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11  },  //  39 ;
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12  },  //  40 '
    {0, CS16_SW7,  CS17_SW7,  CS18_SW7  },  //  41 Enter
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6  },  //  42 Home

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1  },  //  43 Shift_L
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3  },  //  44 Z
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4  },  //  45 X
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5  },  //  46 C
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6  },  //  47 V
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7  },  //  48 B
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8  },  //  49 N
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9  },  //  50 M
    {0, CS10_SW10, CS11_SW10, CS12_SW10 },  //  51 ,
    {0, CS10_SW11, CS11_SW11, CS12_SW11 },  //  52 .
    {0, CS10_SW12, CS11_SW12, CS12_SW12 },  //  53 /
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9  },  //  54 Shift_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10 },  //  55 Up
    {0, CS16_SW8,  CS17_SW8,  CS18_SW8  },  //  56 END

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1  },  //  57 Ctrl_L
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2  },  //  58 Win_L
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3  },  //  59 Alt_L
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6  },  //  60 Space
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9  },  //  61 Alt_R
    {0, CS13_SW10, CS14_SW10, CS15_SW10 },  //  62 Ctrl_R
    {0, CS13_SW11, CS14_SW11, CS15_SW11 },  //  63 FN
    {0, CS13_SW12, CS14_SW12, CS15_SW12 },  //  64 Left
    {0, CS16_SW12, CS17_SW12, CS18_SW12 },  //  65 Down
    {0, CS16_SW11, CS17_SW11, CS18_SW11 },  //  66 Right
};

// clang-format on

#endif  // #ifdef RGB_MATRIX_ENABLE
