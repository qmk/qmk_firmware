 /* Copyright 2022 bdtc123
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
#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS6_SW1, CS5_SW1, CS4_SW1},
    {0, CS6_SW2, CS5_SW2, CS4_SW2},
    {0, CS6_SW3, CS5_SW3, CS4_SW3},
    {0, CS6_SW4, CS5_SW4, CS4_SW4},
    {0, CS6_SW5, CS5_SW5, CS4_SW5},
    {0, CS6_SW6, CS5_SW6, CS4_SW6},
    {0, CS6_SW7, CS5_SW7, CS4_SW7},
    {0, CS6_SW8, CS5_SW8, CS4_SW8},
    {0, CS18_SW1, CS17_SW1, CS16_SW1},
    {0, CS18_SW2, CS17_SW2, CS16_SW2},
    {0, CS18_SW3, CS17_SW3, CS16_SW3},
    {0, CS18_SW4, CS17_SW4, CS16_SW4},
    {0, CS18_SW5, CS17_SW5, CS16_SW5},
    {0, CS18_SW6, CS17_SW6, CS16_SW6},
    {0, CS18_SW7, CS17_SW7, CS16_SW7},

    {0, CS9_SW1, CS8_SW1, CS7_SW1},
    {0, CS9_SW2, CS8_SW2, CS7_SW2},
    {0, CS9_SW3, CS8_SW3, CS7_SW3},
    {0, CS9_SW4, CS8_SW4, CS7_SW4},
    {0, CS9_SW5, CS8_SW5, CS7_SW5},
    {0, CS9_SW6, CS8_SW6, CS7_SW6},
    {0, CS9_SW7, CS8_SW7, CS7_SW7},
    {0, CS9_SW8, CS8_SW8, CS7_SW8},
    {0, CS21_SW1, CS20_SW1, CS19_SW1},
    {0, CS21_SW2, CS20_SW2, CS19_SW2},
    {0, CS21_SW3, CS20_SW3, CS19_SW3},
    {0, CS21_SW4, CS20_SW4, CS19_SW4},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},
    {0, CS21_SW6, CS20_SW6, CS19_SW6},
    {0, CS21_SW7, CS20_SW7, CS19_SW7},

    {0, CS12_SW1, CS11_SW1, CS10_SW1},
    {0, CS12_SW2, CS11_SW2, CS10_SW2},
    {0, CS12_SW3, CS11_SW3, CS10_SW3},
    {0, CS12_SW4, CS11_SW4, CS10_SW4},
    {0, CS12_SW5, CS11_SW5, CS10_SW5},
    {0, CS12_SW6, CS11_SW6, CS10_SW6},
    {0, CS12_SW7, CS11_SW7, CS10_SW7},
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS24_SW1, CS23_SW1, CS22_SW1},
    {0, CS24_SW2, CS23_SW2, CS22_SW2},
    {0, CS24_SW3, CS23_SW3, CS22_SW3},
    {0, CS24_SW4, CS23_SW4, CS22_SW4},
    {0, CS24_SW6, CS23_SW6, CS22_SW6},
    {0, CS24_SW7, CS23_SW7, CS22_SW7},

    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW3, CS14_SW3, CS13_SW3},
    {0, CS15_SW4, CS14_SW4, CS13_SW4},
    {0, CS15_SW5, CS14_SW5, CS13_SW5},
    {0, CS15_SW6, CS14_SW6, CS13_SW6},
    {0, CS15_SW7, CS14_SW7, CS13_SW7},
    {0, CS15_SW8, CS14_SW8, CS13_SW8},
    {0, CS27_SW1, CS26_SW1, CS25_SW1},
    {0, CS27_SW2, CS26_SW2, CS25_SW2},
    {0, CS27_SW3, CS26_SW3, CS25_SW3},
    {0, CS27_SW4, CS26_SW4, CS25_SW4},
    {0, CS27_SW5, CS26_SW5, CS25_SW5},
    {0, CS27_SW6, CS26_SW6, CS25_SW6},
    {0, CS27_SW7, CS26_SW7, CS25_SW7},

    {0, CS3_SW1, CS2_SW1, CS1_SW1},
    {0, CS3_SW2, CS2_SW2, CS1_SW2},
    {0, CS3_SW3, CS2_SW3, CS1_SW3},
    {0, CS3_SW7, CS2_SW7, CS1_SW7},
    {0, CS30_SW2, CS29_SW2, CS28_SW2},
    {0, CS30_SW3, CS29_SW3, CS28_SW3},
    {0, CS30_SW4, CS29_SW4, CS28_SW4},
    {0, CS30_SW5, CS29_SW5, CS28_SW5},
    {0, CS30_SW6, CS29_SW6, CS28_SW6},
    {0, CS30_SW7, CS29_SW7, CS28_SW7}

};
led_config_t g_led_config = { {
    {  0,      1,  2,      3,      4,     5,   6,       7,       8,  9,  10,  11,     12,    13,  14 },
    {  15,    16, 17,     18,     19,    20,  21,      22,      23, 24,  25,  26,     27,    28,  29 },
    {  30,    31, 32,     33,     34,    35,  36,      37,      38, 39,  40,  41, NO_LED,    42,  43 },
    {  44,NO_LED, 45,     46,     47,    48,  49,      50,      51, 52,  53,  54,     55,    56,  57 },
    {  58,    59, 60, NO_LED, NO_LED,NO_LED,  61,  NO_LED,  NO_LED, 62,  63,  64,     65,    66,  67 }
}, {
    {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{120,0},{135,0},{150,0},{165,0},{180,0},{203,0},{224,0},
	{4,16},{23,16},{38,16},{53,16},{68,16},{83,16},{98,16},{113,16},{128,16},{143,16},{158,16},{173,16},{188,16},{206,16},{224,16},
	{6,32},{26,32},{41,32},{56,32},{71,32},{86,32},{101,32},{116,32},{131,32},{146,32},{161,32},{176,32},{201,32},{224,32},
	{9,48},{34,48},{49,48},{64,48},{79,48},{94,48},{109,48},{124,48},{139,48},{154,48},{169,48},{189,48},{210,48},{224,48},
        {   2,  64 }, {  21,  64 }, {  39,  64 },                                           {  96,  64 },                             { 150,  64 }, { 165,  64 }, { 180,  64 }, { 195,  64 }, { 210,  64 }, { 224,  64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1, 1
} };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
