// Copyright 2020 MaiKong<704340378@qq.com>
// SPDX-License-Identifier: GPL-2.0+

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3737_led_t PROGMEM g_is31fl3737_leds[IS31FL3737_LED_COUNT] = {
 /* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */

   {0, SW1_CS11,   SW2_CS11,   SW3_CS11},
   {0, SW4_CS11,   SW5_CS11,   SW6_CS11},
   {0, SW7_CS11,   SW8_CS11,   SW9_CS11},
   {0, SW10_CS11,   SW11_CS11,   SW12_CS11},
   {0, SW1_CS12,   SW2_CS12,   SW3_CS12},
   {0, SW4_CS12,   SW5_CS12,   SW6_CS12},
   {0, SW7_CS12,   SW8_CS12,   SW9_CS12},
   {0, SW10_CS12,   SW11_CS12,   SW12_CS12},
   {1, SW1_CS11,   SW2_CS11,   SW3_CS11},
   {1, SW4_CS11,   SW5_CS11,   SW6_CS11},
   {1, SW7_CS11,   SW8_CS11,   SW9_CS11},
   {1, SW10_CS11,   SW11_CS11,   SW12_CS11},
   {1, SW1_CS12,   SW2_CS12,   SW3_CS12},
   {1, SW4_CS12,   SW5_CS12,   SW6_CS12},
   {1, SW7_CS12,   SW8_CS12,   SW9_CS12},
   {1, SW10_CS12,   SW11_CS12,   SW12_CS12},

   {0, SW1_CS1,   SW2_CS1,   SW3_CS1},
   {0, SW4_CS1,   SW5_CS1,   SW6_CS1},
   {0, SW7_CS1,   SW8_CS1,   SW9_CS1},
   {0, SW10_CS1,   SW11_CS1,   SW12_CS1},
   {0, SW1_CS6,   SW2_CS6,   SW3_CS6},
   {0, SW4_CS6,   SW5_CS6,   SW6_CS6},
   {0, SW7_CS6,   SW8_CS6,   SW9_CS6},
   {0, SW10_CS6,   SW11_CS6,   SW12_CS6},
   {1, SW1_CS1,   SW2_CS1,   SW3_CS1},
   {1, SW4_CS1,   SW5_CS1,   SW6_CS1},
   {1, SW7_CS1,   SW8_CS1,   SW9_CS1},
   {1, SW10_CS1,   SW11_CS1,   SW12_CS1},
   {1, SW1_CS6,   SW2_CS6,   SW3_CS6},
   {1, SW4_CS6,   SW5_CS6,   SW6_CS6},
   {1, SW7_CS6,   SW8_CS6,   SW9_CS6},

   {0, SW1_CS2,   SW2_CS2,   SW3_CS2},
   {0, SW4_CS2,   SW5_CS2,   SW6_CS2},
   {0, SW7_CS2,   SW8_CS2,   SW9_CS2},
   {0, SW10_CS2,   SW11_CS2,   SW12_CS2},
   {0, SW1_CS7,   SW2_CS7,   SW3_CS7},
   {0, SW4_CS7,   SW5_CS7,   SW6_CS7},
   {0, SW7_CS7,   SW8_CS7,   SW9_CS7},
   {0, SW10_CS7,   SW11_CS7,   SW12_CS7},
   {1, SW1_CS2,   SW2_CS2,   SW3_CS2},
   {1, SW4_CS2,   SW5_CS2,   SW6_CS2},
   {1, SW7_CS2,   SW8_CS2,   SW9_CS2},
   {1, SW10_CS2,   SW11_CS2,   SW12_CS2},
   {1, SW1_CS7,   SW2_CS7,   SW3_CS7},
   {1, SW4_CS7,   SW5_CS7,   SW6_CS7},
   {1, SW7_CS7,   SW8_CS7,   SW9_CS7},

   {0, SW1_CS3,   SW2_CS3,   SW3_CS3},
   {0, SW4_CS3,   SW5_CS3,   SW6_CS3},
   {0, SW7_CS3,   SW8_CS3,   SW9_CS3},
   {0, SW10_CS3,   SW11_CS3,   SW12_CS3},
   {0, SW1_CS8,   SW2_CS8,   SW3_CS8},
   {0, SW4_CS8,   SW5_CS8,   SW6_CS8},
   {0, SW7_CS8,   SW8_CS8,   SW9_CS8},
   {0, SW10_CS8,   SW11_CS8,   SW12_CS8},
   {1, SW1_CS3,   SW2_CS3,   SW3_CS3},
   {1, SW4_CS3,   SW5_CS3,   SW6_CS3},
   {1, SW7_CS3,   SW8_CS3,   SW9_CS3},
   {1, SW10_CS3,   SW11_CS3,   SW12_CS3},
   {1, SW1_CS8,   SW2_CS8,   SW3_CS8},
   {1, SW7_CS8,   SW8_CS8,   SW9_CS8},

   {0, SW1_CS4,   SW2_CS4,   SW3_CS4},
   {0, SW4_CS4,   SW5_CS4,   SW6_CS4},
   {0, SW7_CS4,   SW8_CS4,   SW9_CS4},
   {0, SW10_CS4,   SW11_CS4,   SW12_CS4},
   {0, SW1_CS9,   SW2_CS9,   SW3_CS9},
   {0, SW4_CS9,   SW5_CS9,   SW6_CS9},
   {0, SW7_CS9,   SW8_CS9,   SW9_CS9},
   {0, SW10_CS9,   SW11_CS9,   SW12_CS9},
   {1, SW1_CS4,   SW2_CS4,   SW3_CS4},
   {1, SW4_CS4,   SW5_CS4,   SW6_CS4},
   {1, SW7_CS4,   SW8_CS4,   SW9_CS4},
   {1, SW10_CS4,   SW11_CS4,   SW12_CS4},
   {1, SW1_CS9,   SW2_CS9,   SW3_CS9},
   {1, SW7_CS9,   SW8_CS9,   SW9_CS9},

   {0, SW1_CS5,   SW2_CS5,   SW3_CS5},
   {0, SW4_CS5,   SW5_CS5,   SW6_CS5},
   {0, SW7_CS5,   SW8_CS5,   SW9_CS5},
   {0, SW4_CS10,  SW5_CS10,  SW6_CS10},
   {1, SW4_CS5,   SW5_CS5,   SW6_CS5},
   {1, SW7_CS5,   SW8_CS5,   SW9_CS5},
   {1, SW10_CS5,   SW11_CS5,   SW12_CS5},
   {1, SW1_CS10,  SW2_CS10,  SW3_CS10},
   {1, SW4_CS10,  SW5_CS10,  SW6_CS10},
   {1, SW7_CS10,   SW8_CS10,   SW9_CS10}
};
#endif
