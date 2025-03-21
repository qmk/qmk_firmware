/* Copyright 2022 bdtc123 *
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

const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS6, SW1_CS5, SW1_CS4},
    {0, SW3_CS6, SW3_CS5, SW3_CS4},
    {0, SW4_CS6, SW4_CS5, SW4_CS4},
    {0, SW5_CS6, SW5_CS5, SW5_CS4},
    {0, SW6_CS6, SW6_CS5, SW6_CS4},
    {0, SW7_CS6, SW7_CS5, SW7_CS4},
    {0, SW8_CS6, SW8_CS5, SW8_CS4},
    {0, SW9_CS6, SW9_CS5, SW9_CS4},
    {0, SW1_CS21, SW1_CS20, SW1_CS19},
    {0, SW2_CS21, SW2_CS20, SW2_CS19},
    {0, SW3_CS21, SW3_CS20, SW3_CS19},
    {0, SW4_CS21, SW4_CS20, SW4_CS19},
    {0, SW5_CS21, SW5_CS20, SW5_CS19},
    {0, SW6_CS21, SW6_CS20, SW6_CS19},
    {0, SW7_CS21, SW7_CS20, SW7_CS19},
    {0, SW8_CS21, SW8_CS20, SW8_CS19},


    {0, SW1_CS9, SW1_CS8, SW1_CS7},
    {0, SW2_CS9, SW2_CS8, SW2_CS7},
    {0, SW3_CS9, SW3_CS8, SW3_CS7},
    {0, SW4_CS9, SW4_CS8, SW4_CS7},
    {0, SW5_CS9, SW5_CS8, SW5_CS7},
    {0, SW6_CS9, SW6_CS8, SW6_CS7},
    {0, SW7_CS9, SW7_CS8, SW7_CS7},
    {0, SW8_CS9, SW8_CS8, SW8_CS7},
    {0, SW9_CS9, SW9_CS8, SW9_CS7},
    {0,SW1_CS24, SW1_CS23, SW1_CS22},
    {0,SW2_CS24, SW2_CS23, SW2_CS22},
    {0,SW3_CS24, SW3_CS23, SW3_CS22},
    {0,SW4_CS24, SW4_CS23, SW4_CS22},
    {0,SW5_CS24, SW5_CS23, SW5_CS22},
    {0,SW6_CS24, SW6_CS23, SW6_CS22},
    {0,SW7_CS24, SW7_CS23, SW7_CS22},
    {0,SW8_CS24, SW8_CS23, SW8_CS22},

    {0, SW1_CS12, SW1_CS11, SW1_CS10},
    {0, SW2_CS12, SW2_CS11, SW2_CS10},
    {0, SW3_CS12, SW3_CS11, SW3_CS10},
    {0, SW4_CS12, SW4_CS11, SW4_CS10},
    {0, SW5_CS12, SW5_CS11, SW5_CS10},
    {0, SW6_CS12, SW6_CS11, SW6_CS10},
    {0, SW7_CS12, SW7_CS11, SW7_CS10},
    {0, SW8_CS12, SW8_CS11, SW8_CS10},
    {0, SW9_CS12, SW9_CS11, SW9_CS10},
    {0, SW1_CS27, SW1_CS26, SW1_CS25},
    {0, SW2_CS27, SW2_CS26, SW2_CS25},
    {0, SW3_CS27, SW3_CS26, SW3_CS25},
    {0, SW4_CS27, SW4_CS26, SW4_CS25},
    {0, SW5_CS27, SW5_CS26, SW5_CS25},
    {0, SW6_CS27, SW6_CS26, SW6_CS25},
    {0, SW7_CS27, SW7_CS26, SW7_CS25},
    {0, SW8_CS27, SW8_CS26, SW8_CS25},

    {0, SW1_CS15, SW1_CS14, SW1_CS13},
    {0, SW2_CS15, SW2_CS14, SW2_CS13},
    {0, SW3_CS15, SW3_CS14, SW3_CS13},
    {0, SW4_CS15, SW4_CS14, SW4_CS13},
    {0, SW5_CS15, SW5_CS14, SW5_CS13},
    {0, SW6_CS15, SW6_CS14, SW6_CS13},
    {0, SW7_CS15, SW7_CS14, SW7_CS13},
    {0, SW8_CS15, SW8_CS14, SW8_CS13},
    {0, SW9_CS15, SW9_CS14, SW9_CS13},
    {0, SW1_CS30, SW1_CS29, SW1_CS28},
    {0, SW2_CS30, SW2_CS29, SW2_CS28},
    {0, SW3_CS30, SW3_CS29, SW3_CS28},
    {0, SW4_CS30, SW4_CS29, SW4_CS28},

    {0, SW1_CS18, SW1_CS17, SW1_CS16},
    {0, SW3_CS18, SW3_CS17, SW3_CS16},
    {0, SW4_CS18, SW4_CS17, SW4_CS16},
    {0, SW5_CS18, SW5_CS17, SW5_CS16},
    {0, SW6_CS18, SW6_CS17, SW6_CS16},
    {0, SW7_CS18, SW7_CS17, SW7_CS16},
    {0, SW8_CS18, SW8_CS17, SW8_CS16},
    {0, SW9_CS18, SW9_CS17, SW9_CS16},
    {0, SW1_CS33, SW1_CS32, SW1_CS31},
    {0, SW2_CS33, SW2_CS32, SW2_CS31},
    {0, SW3_CS33, SW3_CS32, SW3_CS31},
    {0, SW4_CS33, SW4_CS32, SW4_CS31},
    {0, SW7_CS33, SW7_CS32, SW7_CS31},

    {0, SW1_CS3, SW1_CS2, SW1_CS1},
    {0, SW2_CS3, SW2_CS2, SW2_CS1},
    {0, SW3_CS3, SW3_CS2, SW3_CS1},
    {0, SW6_CS3, SW6_CS2, SW6_CS1},
    {0, SW2_CS36, SW2_CS35, SW2_CS34},
    {0, SW3_CS36, SW3_CS35, SW3_CS34},
    {0, SW4_CS36, SW4_CS35, SW4_CS34},
    {0, SW5_CS36, SW5_CS35, SW5_CS34},
    {0, SW6_CS36, SW6_CS35, SW6_CS34},
    {0, SW7_CS36, SW7_CS35, SW7_CS34},
    {0, SW8_CS36, SW8_CS35, SW8_CS34}

};
led_config_t g_led_config = { {
    {  0,  NO_LED,      1,     2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15 },
    {  16,     17,     18,     19,    20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31,     32 },
    {  33,     34,     35,     36,    37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48,     49 },
    {  50,     51,     52,     53,    54,     55,     56,     57,     58,     59,     60,     61,     62, NO_LED, NO_LED, NO_LED, NO_LED },
    {  63, NO_LED,     64,     65,    66,     67,     68,     69,     70,     71,     72,     73,     74, NO_LED, NO_LED,     75, NO_LED },
    {  76,     77,     78, NO_LED,NO_LED,     79, NO_LED, NO_LED, NO_LED, NO_LED,     80,     81,     82,     83,     84,     85,     86 }
},
{
    {   7,   5 }, {  31,   5 }, {  43,   5 }, {  55,   5 }, {  67,   5 }, {  85,   5 }, {  97,   5 }, { 109,   5 }, { 121,   5 }, { 139,   5 }, { 151,   5 }, { 163,   5 }, { 175,   5 }, { 193,   5 }, { 205,   5 }, { 217,   5 },
    {   7,  20 }, {  19,  20 }, {  31,  20 }, {  43,  20 }, {  55,  20 }, {  67,  20 }, {  79,  20 }, {  91,  20 }, { 103,  20 }, { 115,  20 }, { 127,  20 }, { 139,  20 }, { 151,  20 }, { 169,  20 }, { 193,  20 }, { 205,  20 }, { 217,  20 },
    {  10,  30 }, {  25,  30 }, {  37,  30 }, {  49,  30 }, {  61,  30 }, {  73,  30 }, {  85,  30 }, {  97,  30 }, { 109,  30 }, { 121,  30 }, { 133,  30 }, { 145,  30 }, { 157,  30 }, { 172,  30 }, { 193,  30 }, { 205,  30 }, { 217,  30 },
    {  11,  39 }, {  28,  39 }, {  40,  39 }, {  52,  39 }, {  64,  39 }, {  76,  39 }, {  88,  39 }, { 100,  39 }, { 112,  39 }, { 124,  39 }, { 136,  39 }, { 148,  39 }, { 168,  39 },
    {  17,  49 },  {  34,  49 }, {  46,  49 }, {  58,  49 }, {  70,  49 }, {  82,  49 }, {  94,  49 }, { 106,  49 }, { 118,  49 }, { 130,  49 }, { 142,  49 }, { 165,  49 }, { 205,  49 },
    {  8,  59 }, {  23,  59 }, {  38,  59 }, {  83,  59 }, { 129,  59 }, { 144,  59 }, { 159,  59 }, { 174,  59 }, { 193,  59 }, { 205,  59 }, { 217,  59 }
},
{   1,    4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,       1,
    1, 1, 1,       4,     1, 1, 1, 1,         1, 1, 1
} };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(50, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
