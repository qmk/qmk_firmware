/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, SW3_CS1,    SW1_CS1,    SW2_CS1},
    {0, SW3_CS3,    SW1_CS3,    SW2_CS3},
    {0, SW3_CS4,    SW1_CS4,    SW2_CS4},
    {0, SW3_CS5,    SW1_CS5,    SW2_CS5},
    {0, SW3_CS6,    SW1_CS6,    SW2_CS6},
    {0, SW3_CS7,    SW1_CS7,    SW2_CS7},
    {0, SW3_CS8,    SW1_CS8,    SW2_CS8},
    {0, SW3_CS9,    SW1_CS9,    SW2_CS9},
    {0, SW3_CS10,   SW1_CS10,   SW2_CS10},
    {0, SW3_CS11,   SW1_CS11,   SW2_CS11},
    {0, SW3_CS12,   SW1_CS12,   SW2_CS12},
    {0, SW3_CS13,   SW1_CS13,   SW2_CS13},
    {0, SW3_CS14,   SW1_CS14,   SW2_CS14},
    {0, SW3_CS15,   SW1_CS15,   SW2_CS15},
    {0, SW3_CS16,   SW1_CS16,   SW2_CS16},

    {0, SW6_CS1,    SW4_CS1,    SW5_CS1},
    {0, SW6_CS2,    SW4_CS2,    SW5_CS2},
    {0, SW6_CS3,    SW4_CS3,    SW5_CS3},
    {0, SW6_CS4,    SW4_CS4,    SW5_CS4},
    {0, SW6_CS5,    SW4_CS5,    SW5_CS5},
    {0, SW6_CS6,    SW4_CS6,    SW5_CS6},
    {0, SW6_CS7,    SW4_CS7,    SW5_CS7},
    {0, SW6_CS8,    SW4_CS8,    SW5_CS8},
    {0, SW6_CS9,    SW4_CS9,    SW5_CS9},
    {0, SW6_CS10,   SW4_CS10,   SW5_CS10},
    {0, SW6_CS11,   SW4_CS11,   SW5_CS11},
    {0, SW6_CS12,   SW4_CS12,   SW5_CS12},
    {0, SW6_CS13,   SW4_CS13,   SW5_CS13},
    {0, SW6_CS14,   SW4_CS14,   SW5_CS14},
    {0, SW6_CS16,   SW4_CS16,   SW5_CS16},

    {0, SW9_CS1,    SW7_CS1,    SW8_CS1},
    {0, SW9_CS2,    SW7_CS2,    SW8_CS2},
    {0, SW9_CS3,    SW7_CS3,    SW8_CS3},
    {0, SW9_CS4,    SW7_CS4,    SW8_CS4},
    {0, SW9_CS5,    SW7_CS5,    SW8_CS5},
    {0, SW9_CS6,    SW7_CS6,    SW8_CS6},
    {0, SW9_CS7,    SW7_CS7,    SW8_CS7},
    {0, SW9_CS8,    SW7_CS8,    SW8_CS8},
    {0, SW9_CS9,    SW7_CS9,    SW8_CS9},
    {0, SW9_CS10,   SW7_CS10,   SW8_CS10},
    {0, SW9_CS11,   SW7_CS11,   SW8_CS11},
    {0, SW9_CS12,   SW7_CS12,   SW8_CS12},
    {0, SW9_CS13,   SW7_CS13,   SW8_CS13},
    {0, SW9_CS16,   SW7_CS16,   SW8_CS16},

    {0, SW12_CS1,    SW10_CS1,    SW11_CS1},
    {0, SW12_CS2,    SW10_CS2,    SW11_CS2},
    {0, SW12_CS3,    SW10_CS3,    SW11_CS3},
    {0, SW12_CS4,    SW10_CS4,    SW11_CS4},
    {0, SW12_CS5,    SW10_CS5,    SW11_CS5},
    {0, SW12_CS6,    SW10_CS6,    SW11_CS6},
    {0, SW12_CS7,    SW10_CS7,    SW11_CS7},
    {0, SW12_CS8,    SW10_CS8,    SW11_CS8},
    {0, SW12_CS9,    SW10_CS9,    SW11_CS9},
    {0, SW12_CS10,   SW10_CS10,   SW11_CS10},
    {0, SW12_CS11,   SW10_CS11,   SW11_CS11},
    {0, SW12_CS12,   SW10_CS12,   SW11_CS12},
	{0, SW12_CS14,   SW10_CS14,   SW11_CS14},
	{0, SW9_CS14,   SW7_CS14,   SW8_CS14},
    {0, SW12_CS16,   SW10_CS16,   SW11_CS16},

    {1, SW3_CS1,    SW1_CS1,    SW2_CS1},
    {1, SW3_CS2,    SW1_CS2,    SW2_CS2},
    {1, SW3_CS3,    SW1_CS3,    SW2_CS3},
    {1, SW3_CS4,    SW1_CS4,    SW2_CS4},
    {1, SW3_CS5,    SW1_CS5,    SW2_CS5},
    {1, SW3_CS6,    SW1_CS6,    SW2_CS6},
    {1, SW3_CS7,    SW1_CS7,    SW2_CS7},
    {1, SW3_CS8,    SW1_CS8,    SW2_CS8},
    {1, SW3_CS9,    SW1_CS9,    SW2_CS9},
    {1, SW3_CS10,   SW1_CS10,   SW2_CS10},
    {1, SW3_CS11,   SW1_CS11,   SW2_CS11},
    {1, SW3_CS12,   SW1_CS12,   SW2_CS12},
    {1, SW3_CS14,   SW1_CS14,   SW2_CS14},
    {1, SW3_CS15,   SW1_CS15,   SW2_CS15},

    {1, SW6_CS1,    SW4_CS1,    SW5_CS1},
    {1, SW6_CS2,    SW4_CS2,    SW5_CS2},
    {1, SW6_CS3,    SW4_CS3,    SW5_CS3},
    {1, SW6_CS7,    SW4_CS7,    SW5_CS7},
    {1, SW6_CS11,   SW4_CS11,   SW5_CS11},
    {1, SW6_CS12,   SW4_CS12,   SW5_CS12},
    {1, SW6_CS13,   SW4_CS13,   SW5_CS13},
    {1, SW6_CS14,   SW4_CS14,   SW5_CS14},
    {1, SW6_CS15,   SW4_CS15,   SW5_CS15},
    {1, SW6_CS16,   SW4_CS16,   SW5_CS16}
};

#define __ NO_LED

led_config_t g_led_config = {
	{
        // Key Matrix to LED Index
		{  0, __,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 14 },
		{ 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
		{ 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 57, 43 },
		{ 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 72, 56, 58 },
		{ 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 81, 71, 13 },
		{ 73, 74, 75, __, __, __, 76, __, __, __, 77, 78, 79, 80, 82 }
	},
	{
        // LED Index to Physical Position
        {0,0},           {18,0},  {33,0},  {48,0},  {62,0},  {81,0},  {95,0},   {110,0},  {125,0},  {143,0},  {158,0},  {173,0},  {187,0},  {206,0},  {224,0},
        {0,15}, {15,15}, {29,15}, {44,15}, {59,15}, {73,15}, {88,15}, {103,15}, {118,15}, {132,15}, {147,15}, {162,15}, {176,15}, {198,15},           {224,15},
        {4,26}, {22,26}, {37,26}, {51,26}, {66,26}, {81,26}, {95,26}, {110,26}, {125,26}, {140,26}, {154,26}, {169,26}, {184,26},                     {224,26},
        {6,38}, {26,38}, {40,38}, {55,38}, {70,38}, {84,38}, {99,38}, {114,38}, {129,38}, {143,38}, {158,38}, {173,38}, {187,38}, {203,32},           {224,38},
        {2,49}, {18,49}, {33,49}, {48,49}, {62,49}, {77,49}, {92,49}, {106,49}, {121,49}, {136,49}, {151,49}, {165,49},           {185,49}, {209,52},
        {2,61}, {20,61}, {39,61}, {94,61},                            {147,61},                               {162,61}, {176,61}, {195,64}, {209,64}, {224,64}
    },
	{
        // RGB LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        1, 1, 1,           4,         1, 1, 1, 1, 1, 1
	}
};

#endif // RGB_MATRIX_ENABLE
