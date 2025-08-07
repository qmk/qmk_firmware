/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"

#ifndef CAPS_LOCK_ENABLE
#    define CAPS_LOCK_ENABLE true
#endif

#ifndef CAPS_LOCK_COLOR
#    define CAPS_LOCK_COLOR RGB_RED
#endif

#ifndef CAPS_LED_GROUP
// change what leds to target, for example LED_FLAG_KEYLIGHT for alpas or LED_FLAG_MODIFIER for modifiers
#    define CAPS_LED_GROUP LED_FLAG_INDICATOR
#endif

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2 }, //D402
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3 }, //D403
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4 }, //D404
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5 }, //D405
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6 }, //D406
    { 0, SW11_CS7,  SW10_CS7,  SW12_CS7 }, //D407
    { 0, SW11_CS8,  SW10_CS8,  SW12_CS8 }, //D408
    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9 }, //D409
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 }, //D410
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 }, //D411
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 }, //D412
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 }, //D413
    { 0, SW11_CS14, SW10_CS14, SW12_CS14 }, //D414
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 }, //D415
    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1 }, //D401
    { 0, SW8_CS4,  SW7_CS4,  SW9_CS4 }, //D420
    { 0, SW8_CS5,  SW7_CS5,  SW9_CS5 }, //D421
    { 0, SW8_CS6,  SW7_CS6,  SW9_CS6 }, //D422
    { 0, SW8_CS7,  SW7_CS7,  SW9_CS7 }, //D423
    { 0, SW8_CS8,  SW7_CS8,  SW9_CS8 }, //D424
    { 0, SW8_CS9,  SW7_CS9,  SW9_CS9 }, //D425
    { 0, SW8_CS10, SW7_CS10, SW9_CS10 }, //D426
    { 0, SW8_CS11, SW7_CS11, SW9_CS11 }, //D427
    { 0, SW8_CS12, SW7_CS12, SW9_CS12 }, //D428
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 }, //D429
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 }, //D430
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 }, //D431
    { 0, SW11_CS16, SW10_CS16, SW12_CS16 }, //D416
    { 0, SW8_CS2,  SW7_CS2,  SW9_CS2 }, //D418
    { 0, SW8_CS3,  SW7_CS3,  SW9_CS3 }, //D419
    { 0, SW5_CS5,  SW4_CS5,  SW6_CS5 }, //D437
    { 0, SW5_CS6,  SW4_CS6,  SW6_CS6 }, //D438
    { 0, SW5_CS7,  SW4_CS7,  SW6_CS7 }, //D439
    { 0, SW5_CS8,  SW4_CS8,  SW6_CS8 }, //D440
    { 0, SW5_CS9,  SW4_CS9,  SW6_CS9 }, //D441
    { 0, SW5_CS10, SW4_CS10, SW6_CS10 }, //D442
    { 0, SW5_CS11, SW4_CS11, SW6_CS11 }, //D443
    { 0, SW5_CS12, SW4_CS12, SW6_CS12 }, //D444
    { 0, SW5_CS13, SW4_CS13, SW6_CS13 }, //D445
    { 0, SW5_CS14, SW4_CS14, SW6_CS14 }, //D446
    { 0, SW8_CS16, SW7_CS16, SW9_CS16 }, //D432
    { 0, SW8_CS1,  SW7_CS1,  SW9_CS1 }, //D417
    { 0, SW5_CS3,  SW4_CS3,  SW6_CS3 }, //D435
    { 0, SW5_CS4,  SW4_CS4,  SW6_CS4 }, //D436
    { 0, SW2_CS2,  SW1_CS2,  SW3_CS2 }, //D450
    { 0, SW2_CS3,  SW1_CS3,  SW3_CS3 }, //D451
    { 0, SW2_CS4,  SW1_CS4,  SW3_CS4 }, //D452
    { 0, SW2_CS6,  SW1_CS6,  SW3_CS6 }, //D454
    { 0, SW2_CS8,  SW1_CS8,  SW3_CS8 }, //D456
    { 0, SW2_CS9,  SW1_CS9,  SW3_CS9 }, //D457
    { 0, SW2_CS10, SW1_CS10, SW3_CS10 }, //D458
    { 0, SW2_CS12, SW1_CS12, SW3_CS12 }, //D460
    { 0, SW2_CS13, SW1_CS13, SW3_CS13 }, //D461
    { 0, SW5_CS15, SW4_CS15, SW6_CS15 }, //D447
    { 0, SW5_CS1,  SW4_CS1,  SW6_CS1 }, //D433
    { 0, SW5_CS2,  SW4_CS2,  SW6_CS2 }, //D434
    { 0, SW2_CS1,  SW1_CS1,  SW3_CS1 }, //D449
    { 0, SW2_CS7,  SW1_CS7,  SW3_CS7 }, //D455
    { 0, SW2_CS11, SW1_CS11, SW3_CS11 }, //D459
    { 0, SW2_CS14, SW1_CS14, SW3_CS14 }, //D462
    { 0, SW2_CS15,  SW1_CS15,  SW3_CS15 }, //D463
    { 0, SW2_CS16,  SW1_CS16,  SW3_CS16 } //D464
};

#define XXX NO_LED
led_config_t g_led_config = {
    {
    {   0,   2,   4,   6,   8,  10,  12 },
    {   1,   3,   5,   7,   9,  11, XXX },
    {  14,  16,  18,  20,  22,  24,  26 },
    {  15,  17,  19,  21,  23,  25,  13 },
    {  28,  30,  32,  34,  36,  38,  40 },
    {  29,  31,  33,  35,  37,  39, XXX },
    {  41,  43,  45,  47,  49,  51, XXX },
    {  42,  44,  46,  48,  50,  52,  27 },
    {  54,  55, XXX,  57, XXX,  60,  53 },
    {  56, XXX, XXX,  58,  59,  61, XXX },

    }, {
    {  0,0  }, { 16,0  }, { 32,0  }, { 48,0  }, { 65,0  }, { 81,0  }, { 97,0  }, {113,0  }, {129,0  }, {145,0  },
    {161,0  }, {178,0  }, {194,0  }, {218,0  }, {  4,16 }, { 24,16 }, { 40,16 }, { 57,16 }, { 73,16 }, { 89,16 },
    {105,16 }, {121,16 }, {137,16 }, {153,16 }, {170,16 }, {186,16 }, {202,16 }, {224,24 }, {  6,32 }, { 28,32 },
    { 44,32 }, { 61,32 }, { 77,32 }, { 93,32 }, {109,32 }, {125,32 }, {141,32 }, {157,32 }, {174,32 }, {190,32 },
    {206,32 }, {  2,48 }, { 20,48 }, { 36,48 }, { 52,48 }, { 69,48 }, { 85,48 }, {101,48 }, {117,48 }, {133,48 },
    {149,48 }, {165,48 }, {182,48 }, {212,48 }, {  2,64 }, { 22,64 }, { 42,64 }, {103,64 }, {163,64 }, {184,64 },
    {204,64 }, {224,64 },
    }, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 4, 1, 1, 1, 1
    }
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock && CAPS_LOCK_ENABLE) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & CAPS_LED_GROUP) {
                rgb_matrix_set_color(i, CAPS_LOCK_COLOR);
            }
        }
    }

    return true;
}
#endif
