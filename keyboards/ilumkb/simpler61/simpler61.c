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
    {0, SW5_CS27, SW5_CS26, SW5_CS25},

    {0, SW1_CS15, SW1_CS14, SW1_CS13},
    {0, SW2_CS15, SW2_CS14, SW2_CS13},
    {0, SW3_CS15, SW3_CS14, SW3_CS13},
    {0, SW6_CS15, SW6_CS14, SW6_CS13},
    {0, SW8_CS30, SW8_CS29, SW8_CS28},
    {0, SW7_CS30, SW7_CS29, SW7_CS28},
    {0, SW5_CS30, SW5_CS29, SW5_CS28},
};

led_config_t g_led_config = {
	{
		{  0,       1,       2,       3,       4,       5,       6,       7,       8,       9,      10,      11,      12,      13},
		{ 14,      15,      16,      17,      18,      19,      20,      21,      22,      23,      24,      25,      26,      27},
		{ 28,      29,      30,      31,      32,      33,      34,      35,      36,      37,      38,      39,  NO_LED,      40},
		{ 41,      42,      43,      44,      45,      46,      47,      48,      49,      50,      51,      52,  NO_LED,      53},
		{ 54,      55,      56,  NO_LED,  NO_LED,      57,  NO_LED,  NO_LED,  NO_LED,  NO_LED,      58,      59,  NO_LED,      60},
    }, {
		{0,  0}, {16,  0}, {32,  0},  {48, 0},  {64, 0},   {80, 0},   {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {216, 0},
		{4, 16}, {24, 16}, {40, 16}, {56, 16}, {72, 16},  {88, 16}, {104, 16}, {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16},
		{2, 32}, {28, 32}, {44, 32}, {60, 32}, {76, 32},  {92, 32}, {108, 32}, {114, 32}, {130, 32}, {146, 32}, {162, 32}, {178, 32},            {204, 32},
		{9, 48}, {36, 48}, {52, 48}, {68, 48}, {84, 48}, {100, 48}, {116, 48}, {132, 48}, {148, 48}, {164, 48}, {180, 48}, {202, 48},            {224, 48},
		{4, 64}, {24, 64}, {44, 64},                     {112, 64},                                             {180, 64}, {200, 64},            {220, 64},
	}, {
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,                4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,                4,
		4,       4,       4,                         4,                                           4,       4,                4,
	}
};

#endif
