/*
Copyright 2021 Evelien Dekkers

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

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, SW2_CS1,   SW3_CS1,   SW1_CS1},
    {0, SW2_CS2,   SW3_CS2,   SW1_CS2},
    {0, SW2_CS3,   SW3_CS3,   SW1_CS3},
    {0, SW2_CS4,   SW3_CS4,   SW1_CS4},
    {0, SW2_CS5,   SW3_CS5,   SW1_CS5},
    {0, SW2_CS6,   SW3_CS6,   SW1_CS6},
    {0, SW2_CS7,   SW3_CS7,   SW1_CS7},
    {0, SW2_CS8,   SW3_CS8,   SW1_CS8},
    {0, SW2_CS9,   SW3_CS9,   SW1_CS9},
    {0, SW2_CS10,  SW3_CS10,  SW1_CS10},
    {0, SW2_CS11,  SW3_CS11,  SW1_CS11},
    {0, SW2_CS12,  SW3_CS12,  SW1_CS12},
    {0, SW2_CS13,  SW3_CS13,  SW1_CS13},

    {0, SW5_CS1,   SW6_CS1,   SW4_CS1},
    {0, SW5_CS2,   SW6_CS2,   SW4_CS2},
    {0, SW5_CS3,   SW6_CS3,   SW4_CS3},
    {0, SW5_CS4,   SW6_CS4,   SW4_CS4},
    {0, SW5_CS5,   SW6_CS5,   SW4_CS5},
    {0, SW5_CS6,   SW6_CS6,   SW4_CS6},
    {0, SW5_CS7,   SW6_CS7,   SW4_CS7},
    {0, SW5_CS8,   SW6_CS8,   SW4_CS8},
    {0, SW5_CS9,   SW6_CS9,   SW4_CS9},
    {0, SW5_CS10,  SW6_CS10,  SW4_CS10},
    {0, SW5_CS11,  SW6_CS11,  SW4_CS11},
    {0, SW5_CS13,  SW6_CS13,  SW4_CS13},

    {0, SW8_CS1,   SW9_CS1,   SW7_CS1},
    {0, SW8_CS2,   SW9_CS2,   SW7_CS2},
    {0, SW8_CS3,   SW9_CS3,   SW7_CS3},
    {0, SW8_CS4,   SW9_CS4,   SW7_CS4},
    {0, SW8_CS5,   SW9_CS5,   SW7_CS5},
    {0, SW8_CS6,   SW9_CS6,   SW7_CS6},
    {0, SW8_CS7,   SW9_CS7,   SW7_CS7},
    {0, SW8_CS8,   SW9_CS8,   SW7_CS8},
    {0, SW8_CS9,   SW9_CS9,   SW7_CS9},
    {0, SW8_CS10,  SW9_CS10,  SW7_CS10},
    {0, SW8_CS11,  SW9_CS11,  SW7_CS11},
    {0, SW8_CS12,  SW9_CS12,  SW7_CS12},
    {0, SW8_CS13,  SW9_CS13,  SW7_CS13},

    {0, SW11_CS1,   SW12_CS1,   SW10_CS1},
    {0, SW11_CS2,   SW12_CS2,   SW10_CS2},
    {0, SW11_CS3,   SW12_CS3,   SW10_CS3},
    {0, SW11_CS4,   SW12_CS4,   SW10_CS4},
    {0, SW11_CS6,   SW12_CS6,   SW10_CS6},
    {0, SW11_CS8,   SW12_CS8,   SW10_CS8},
    {0, SW11_CS10,  SW12_CS10,  SW10_CS10},
    {0, SW11_CS11,  SW12_CS11,  SW10_CS11},
    {0, SW11_CS12,  SW12_CS12,  SW10_CS12},
    {0, SW11_CS13,  SW12_CS13,  SW10_CS13}
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12   },
  {   13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, NO_LED, 24   },
  {   25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37   },
  {   38, 39, 40, 41, NO_LED, 42, NO_LED, 43, NO_LED, 44, 45, 46, 47   }
}, {
  // LED Index to Physical Position
  { 9,     8 },
  { 26,    8 },
  { 43,    8 },
  { 60,    8 },
  { 78,    8 },
  { 95,    8 },
  { 112,   8 },
  { 129,   8 },
  { 146,   8 },
  { 164,   8 },
  { 181,   8 },
  { 198,   8 },
  { 215,   8 },

  { 11,   24 },
  { 30,   24 },
  { 47,   24 },
  { 64,   24 },
  { 82,   24 },
  { 99,   24 },
  { 116,  24 },
  { 134,  24 },
  { 151,  24 },
  { 168,  24 },
  { 185,  24 },
  { 209,  24 },

  { 15,   40 },
  { 20,   22 },
  { 39,   40 },
  { 56,   40 },
  { 73,   40 },
  { 90,   40 },
  { 108,  40 },
  { 125,  40 },
  { 142,  40 },
  { 159,  40 },
  { 177,  40 },
  { 196,  40 },
  { 215,  40 },

  { 11,   56 },
  { 30,   56 },
  { 47,   56 },
  { 64,   56 },
  { 88,   56 },
  { 127,  56 },
  { 159,  56 },
  { 177,  56 },
  { 194,  56 },
  { 213,  56 },
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 255, 255);
    } else {
        rgb_matrix_set_color(26, 0, 0, 0);
    }
    return true;
}
