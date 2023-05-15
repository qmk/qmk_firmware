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

#include "simpler64.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0,  CS3_SW1,  CS2_SW1,  CS1_SW1},
    {0,  CS3_SW2,  CS2_SW2,  CS1_SW2},
    {0,  CS3_SW3,  CS2_SW3,  CS1_SW3},
    {0,  CS3_SW4,  CS2_SW4,  CS1_SW4},
    {0,  CS3_SW5,  CS2_SW5,  CS1_SW5},
    {0,  CS3_SW6,  CS2_SW6,  CS1_SW6},
    {0,  CS3_SW7,  CS2_SW7,  CS1_SW7},
    {0,  CS3_SW8,  CS2_SW8,  CS1_SW8},
    {0,  CS3_SW9,  CS2_SW9,  CS1_SW9},
    {0, CS18_SW9, CS17_SW9, CS16_SW9},
    {0, CS18_SW8, CS17_SW8, CS16_SW8},
    {0, CS18_SW7, CS17_SW7, CS16_SW7},
    {0, CS18_SW6, CS17_SW6, CS16_SW6},
    {0, CS18_SW5, CS17_SW5, CS16_SW5},

    {0,  CS6_SW1,  CS5_SW1,  CS4_SW1},
    {0,  CS6_SW2,  CS5_SW2,  CS4_SW2},
    {0,  CS6_SW3,  CS5_SW3,  CS4_SW3},
    {0,  CS6_SW4,  CS5_SW4,  CS4_SW4},
    {0,  CS6_SW5,  CS5_SW5,  CS4_SW5},
    {0,  CS6_SW6,  CS5_SW6,  CS4_SW6},
    {0,  CS6_SW7,  CS5_SW7,  CS4_SW7},
    {0,  CS6_SW8,  CS5_SW8,  CS4_SW8},
    {0,  CS6_SW9,  CS5_SW9,  CS4_SW9},
	{0, CS21_SW9, CS20_SW9, CS19_SW9},
    {0, CS21_SW8, CS20_SW8, CS19_SW8},
    {0, CS21_SW7, CS20_SW7, CS19_SW7},
    {0, CS21_SW6, CS20_SW6, CS19_SW6},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},

    {0,  CS9_SW1,  CS8_SW1,  CS7_SW1},
    {0,  CS9_SW2,  CS8_SW2,  CS7_SW2},
    {0,  CS9_SW3,  CS8_SW3,  CS7_SW3},
    {0,  CS9_SW4,  CS8_SW4,  CS7_SW4},
    {0,  CS9_SW5,  CS8_SW5,  CS7_SW5},
    {0,  CS9_SW6,  CS8_SW6,  CS7_SW6},
    {0,  CS9_SW7,  CS8_SW7,  CS7_SW7},
    {0,  CS9_SW8,  CS8_SW8,  CS7_SW8},
    {0,  CS9_SW9,  CS8_SW9,  CS7_SW9},
    {0, CS24_SW9, CS23_SW9, CS22_SW9},
	{0, CS24_SW8, CS23_SW8, CS22_SW8},
    {0, CS24_SW7, CS23_SW7, CS22_SW7},
	{0, CS24_SW5, CS23_SW5, CS22_SW5},

    {0, CS12_SW1, CS11_SW1, CS10_SW1},
    {0, CS12_SW2, CS11_SW2, CS10_SW2},
    {0, CS12_SW3, CS11_SW3, CS10_SW3},
    {0, CS12_SW4, CS11_SW4, CS10_SW4},
    {0, CS12_SW5, CS11_SW5, CS10_SW5},
    {0, CS12_SW6, CS11_SW6, CS10_SW6},
    {0, CS12_SW7, CS11_SW7, CS10_SW7},
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS12_SW9, CS11_SW9, CS10_SW9},
    {0, CS27_SW9, CS26_SW9, CS25_SW9},
    {0, CS27_SW8, CS26_SW8, CS25_SW8},
	{0, CS27_SW7, CS26_SW7, CS25_SW7},
    {0, CS27_SW6, CS26_SW6, CS25_SW6},
    {0, CS27_SW5, CS26_SW5, CS25_SW5},

    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW2, CS14_SW2, CS13_SW2},
    {0, CS15_SW3, CS14_SW3, CS13_SW3},
    {0, CS15_SW6, CS14_SW6, CS13_SW6},
    {0, CS30_SW9, CS29_SW9, CS28_SW9},
    {0, CS30_SW8, CS29_SW8, CS28_SW8},
    {0, CS30_SW7, CS29_SW7, CS28_SW7},
    {0, CS30_SW6, CS29_SW6, CS28_SW6},
    {0, CS30_SW5, CS29_SW5, CS28_SW5},
};

led_config_t g_led_config = {
	{
		{  0,       1,       2,       3,       4,       5,       6,       7,       8,       9,      10,      11,      12,      13},
		{ 14,      15,      16,      17,      18,      19,      20,      21,      22,      23,      24,      25,      26,      27},
		{ 28,      29,      30,      31,      32,      33,      34,      35,      36,      37,      38,      39,  NO_LED,      40},
		{ 41,      42,      43,      44,      45,      46,      47,      48,      49,      50,      51,      52,      53,      54},
		{ 55,      56,      57,  NO_LED,  NO_LED,      58,  NO_LED,  NO_LED,  NO_LED,      59,      60,      61,      62,      63},
    }, {
		{0,  0}, {16,  0}, {32,  0},  {48, 0},  {64, 0},  {80, 0},   {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {216, 0},
		{4, 16}, {24, 16}, {40, 16}, {56, 16}, {72, 16}, {88, 16}, {104, 16}, {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16},
		{6, 32}, {28, 32}, {44, 32}, {60, 32}, {76, 32}, {92, 32}, {108, 32}, {114, 32}, {130, 32}, {146, 32}, {162, 32}, {178, 32},            {204, 32},
		{8, 48}, {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {138, 48}, {154, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48}, {224, 48},
		{2, 64}, {22, 64}, {42, 64},                    {102, 64},                                  {160, 64}, {176, 64}, {192, 64}, {208, 64}, {224, 64},
	}, {
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,                4,
		4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,       4,
		4,       4,       4,                         4,                                  4,       4,       4,       4,       4,
	}
};

#endif
