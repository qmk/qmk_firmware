/* Copyright 2021 Equalz
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
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0,  SW1_CS3,  SW1_CS2,  SW1_CS1},
    {0,  SW2_CS3,  SW2_CS2,  SW2_CS1},
    {0,  SW3_CS3,  SW3_CS2,  SW3_CS1},
    {0,  SW4_CS3,  SW4_CS2,  SW4_CS1},
    {0,  SW5_CS3,  SW5_CS2,  SW5_CS1},
    {0,  SW6_CS3,  SW6_CS2,  SW6_CS1},
    {0,  SW7_CS3,  SW7_CS2,  SW7_CS1},
    {0,  SW8_CS3,  SW8_CS2,  SW8_CS1},
    {0,  SW9_CS3,  SW9_CS2,  SW9_CS1},
    {0, SW9_CS18, SW9_CS17, SW9_CS16},
    {0, SW8_CS18, SW8_CS17, SW8_CS16},
    {0, SW7_CS18, SW7_CS17, SW7_CS16},
    {0, SW6_CS18, SW6_CS17, SW6_CS16},
    {0, SW5_CS18, SW5_CS17, SW5_CS16},

    {0,  SW1_CS6,  SW1_CS5,  SW1_CS4},
    {0,  SW2_CS6,  SW2_CS5,  SW2_CS4},
    {0,  SW3_CS6,  SW3_CS5,  SW3_CS4},
    {0,  SW4_CS6,  SW4_CS5,  SW4_CS4},
    {0,  SW5_CS6,  SW5_CS5,  SW5_CS4},
    {0,  SW6_CS6,  SW6_CS5,  SW6_CS4},
    {0,  SW7_CS6,  SW7_CS5,  SW7_CS4},
    {0,  SW8_CS6,  SW8_CS5,  SW8_CS4},
    {0,  SW9_CS6,  SW9_CS5,  SW9_CS4},
	{0, SW9_CS21, SW9_CS20, SW9_CS19},
    {0, SW8_CS21, SW8_CS20, SW8_CS19},
    {0, SW7_CS21, SW7_CS20, SW7_CS19},
    {0, SW6_CS21, SW6_CS20, SW6_CS19},
    {0, SW5_CS21, SW5_CS20, SW5_CS19},

    {0,  SW1_CS9,  SW1_CS8,  SW1_CS7},
    {0,  SW2_CS9,  SW2_CS8,  SW2_CS7},
    {0,  SW3_CS9,  SW3_CS8,  SW3_CS7},
    {0,  SW4_CS9,  SW4_CS8,  SW4_CS7},
    {0,  SW5_CS9,  SW5_CS8,  SW5_CS7},
    {0,  SW6_CS9,  SW6_CS8,  SW6_CS7},
    {0,  SW7_CS9,  SW7_CS8,  SW7_CS7},
    {0,  SW8_CS9,  SW8_CS8,  SW8_CS7},
    {0,  SW9_CS9,  SW9_CS8,  SW9_CS7},
    {0, SW9_CS24, SW9_CS23, SW9_CS22},
	{0, SW8_CS24, SW8_CS23, SW8_CS22},
    {0, SW7_CS24, SW7_CS23, SW7_CS22},
	{0, SW5_CS24, SW5_CS23, SW5_CS22},

    {0, SW1_CS12, SW1_CS11, SW1_CS10},
    {0, SW2_CS12, SW2_CS11, SW2_CS10},
    {0, SW3_CS12, SW3_CS11, SW3_CS10},
    {0, SW4_CS12, SW4_CS11, SW4_CS10},
    {0, SW5_CS12, SW5_CS11, SW5_CS10},
    {0, SW6_CS12, SW6_CS11, SW6_CS10},
    {0, SW7_CS12, SW7_CS11, SW7_CS10},
    {0, SW8_CS12, SW8_CS11, SW8_CS10},
    {0, SW9_CS12, SW9_CS11, SW9_CS10},
    {0, SW9_CS27, SW9_CS26, SW9_CS25},
    {0, SW8_CS27, SW8_CS26, SW8_CS25},
	{0, SW7_CS27, SW7_CS26, SW7_CS25},
    {0, SW6_CS27, SW6_CS26, SW6_CS25},
    {0, SW5_CS27, SW5_CS26, SW5_CS25},

    {0, SW1_CS15, SW1_CS14, SW1_CS13},
    {0, SW2_CS15, SW2_CS14, SW2_CS13},
    {0, SW3_CS15, SW3_CS14, SW3_CS13},
    {0, SW6_CS15, SW6_CS14, SW6_CS13},
    {0, SW9_CS30, SW9_CS29, SW9_CS28},
    {0, SW8_CS30, SW8_CS29, SW8_CS28},
    {0, SW7_CS30, SW7_CS29, SW7_CS28},
    {0, SW6_CS30, SW6_CS29, SW6_CS28},
    {0, SW5_CS30, SW5_CS29, SW5_CS28},
};
#endif
