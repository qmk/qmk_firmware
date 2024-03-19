// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

// clang-format off

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3   },  //  0  Esc
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3   },  //  1  1
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3   },  //  2  2
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3   },  //  3  3
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3   },  //  4  4
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3   },  //  5  5
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3   },  //  6  6
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3   },  //  7  7
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3   },  //  8  8
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3  },  //  9  9
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3  },  //  10 0
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3  },  //  11 -
    {0, SW1_CS16,  SW1_CS17,  SW1_CS18  },  //  12 =
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18  },  //  13 Backspace

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6   },  //  14 Tab
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6   },  //  15 Q
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6   },  //  16 W
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6   },  //  17 E
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6   },  //  18 R
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6   },  //  19 T
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6   },  //  20 Y
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6   },  //  21 U
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6   },  //  22 I
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6  },  //  23 O
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6  },  //  24 P
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6  },  //  25 [
    {0, SW4_CS16,  SW4_CS17,  SW4_CS18  },  //  26 ]
    {0, SW5_CS16,  SW5_CS17,  SW5_CS18  },  //  27 \|
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18  },  //  28 Del

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9   },  //  29 Caps Lock
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9   },  //  30 A
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9   },  //  31 S
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9   },  //  32 D
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9   },  //  33 F
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9   },  //  34 G
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9   },  //  35 H
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9   },  //  36 J
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9   },  //  37 K
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9  },  //  38 L
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9  },  //  39 ;
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9  },  //  40 '
    {0, SW7_CS16,  SW7_CS17,  SW7_CS18  },  //  41 Enter
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18  },  //  42 Home

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12  },  //  43 Shift_L
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12  },  //  44 Z
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12  },  //  45 X
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12  },  //  46 C
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12  },  //  47 V
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12  },  //  48 B
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12  },  //  49 N
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12  },  //  50 M
    {0, SW10_CS10, SW10_CS11, SW10_CS12 },  //  51 ,
    {0, SW11_CS10, SW11_CS11, SW11_CS12 },  //  52 .
    {0, SW12_CS10, SW12_CS11, SW12_CS12 },  //  53 /
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18  },  //  54 Shift_R
    {0, SW10_CS16, SW10_CS17, SW10_CS18 },  //  55 Up
    {0, SW8_CS16,  SW8_CS17,  SW8_CS18  },  //  56 END

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15  },  //  57 Ctrl_L
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15  },  //  58 Win_L
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15  },  //  59 Alt_L
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15  },  //  60 Space
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15  },  //  61 Alt_R
    {0, SW10_CS13, SW10_CS14, SW10_CS15 },  //  62 Ctrl_R
    {0, SW11_CS13, SW11_CS14, SW11_CS15 },  //  63 FN
    {0, SW12_CS13, SW12_CS14, SW12_CS15 },  //  64 Left
    {0, SW12_CS16, SW12_CS17, SW12_CS18 },  //  65 Down
    {0, SW11_CS16, SW11_CS17, SW11_CS18 },  //  66 Right
};

// clang-format on

#endif  // #ifdef RGB_MATRIX_ENABLE
