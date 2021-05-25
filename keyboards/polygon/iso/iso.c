/* Copyright 2020 Adam Naldal
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

#include "polygon.h"

// POSITIONS FOR ISO BOARD
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           |
 * ROW 1*/
    {0, CS1_SW9,    CS2_SW9,    CS3_SW9}, //RGB 1
    {0, CS4_SW9,    CS5_SW9,    CS6_SW9}, //RGB 2
    {0, CS7_SW9,    CS8_SW9,    CS9_SW9}, //RGB 3
    {0, CS10_SW8,   CS11_SW8,   CS12_SW8}, //RGB 4
    {0, CS10_SW9,   CS11_SW9,   CS12_SW9}, //RGB 5
    {0, CS13_SW8,   CS14_SW8,   CS15_SW8}, //RGB 6
    {0, CS13_SW9,   CS14_SW9,   CS15_SW9}, //RGB 7
    {0, CS16_SW8,   CS17_SW8,   CS18_SW8}, //RGB 8
    {0, CS16_SW9,   CS17_SW9,   CS18_SW9}, //RGB 9
    {0, CS19_SW9,   CS20_SW9,   CS21_SW9}, //RGB 10
    {0, CS22_SW9,   CS23_SW9,   CS24_SW9}, //RGB 11
    {0, CS25_SW9,   CS26_SW9,   CS27_SW9}, //RGB 12
    {0, CS28_SW9,   CS29_SW9,   CS30_SW9}, //RGB 13
    {0, CS36_SW9,   CS35_SW9,   CS34_SW9}, //RGB 14

    // ROW 2
    {0, CS1_SW7,    CS2_SW7,    CS3_SW7}, //RGB 15
    {0, CS4_SW7,    CS5_SW7,    CS6_SW7}, //RGB 16
    {0, CS7_SW7,    CS8_SW7,    CS9_SW7}, //RGB 17
    {0, CS10_SW6,   CS11_SW6,   CS12_SW6}, //RGB 18
    {0, CS10_SW7,   CS11_SW7,   CS12_SW7}, //RGB 19
    {0, CS13_SW6,   CS14_SW6,   CS15_SW6}, //RGB 20
    {0, CS13_SW7,   CS14_SW7,   CS15_SW7}, //RGB 21
    {0, CS16_SW6,   CS17_SW6,   CS18_SW6}, //RGB 22
    {0, CS16_SW7,   CS17_SW7,   CS18_SW7}, //RGB 23
    {0, CS19_SW7,   CS20_SW7,   CS21_SW7}, //RGB 24
    {0, CS22_SW7,   CS23_SW7,   CS24_SW7}, //RGB 25
    {0, CS25_SW7,   CS26_SW7,   CS27_SW7}, //RGB 26
    {0, CS28_SW7,   CS29_SW7,   CS30_SW7}, //RGB 27
    {0, CS31_SW7,   CS32_SW7,   CS33_SW7}, //RGB 28
    {0, CS39_SW7,   CS38_SW7,   CS37_SW7}, //RGB 29

    // ROW 3
    {0, CS1_SW5,    CS2_SW5,    CS3_SW5}, //RGB 30
    {0, CS4_SW5,    CS5_SW5,    CS6_SW5}, //RGB 31
    {0, CS7_SW5,    CS8_SW5,    CS9_SW5}, //RGB 32
    {0, CS10_SW4,   CS11_SW4,   CS12_SW4}, //RGB 33
    {0, CS10_SW5,   CS11_SW5,   CS12_SW5}, //RGB 34
    {0, CS13_SW4,   CS14_SW4,   CS15_SW4}, //RGB 35
    {0, CS13_SW5,   CS14_SW5,   CS15_SW5}, //RGB 36
    {0, CS16_SW4,   CS17_SW4,   CS18_SW4}, //RGB 37
    {0, CS16_SW5,   CS17_SW5,   CS18_SW5}, //RGB 38
    {0, CS19_SW5,   CS20_SW5,   CS21_SW5}, //RGB 39
    {0, CS22_SW5,   CS23_SW5,   CS24_SW5}, //RGB 40
    {0, CS25_SW5,   CS26_SW5,   CS27_SW5}, //RGB 41
    {0, CS36_SW5,   CS35_SW5,   CS34_SW5}, //RGB 42
    {0, CS39_SW5,   CS38_SW5,   CS37_SW5}, //RGB 43

    // ROW 4
    {0, CS1_SW3,    CS2_SW3,    CS3_SW3}, //RGB 44
    {0, CS4_SW3,    CS5_SW3,    CS6_SW3}, //RGB 45
    {0, CS7_SW3,    CS8_SW3,    CS9_SW3}, //RGB 46
    {0, CS10_SW2,   CS11_SW2,   CS12_SW2}, //RGB 47
    {0, CS10_SW3,   CS11_SW3,   CS12_SW3}, //RGB 48
    {0, CS13_SW2,   CS14_SW2,   CS15_SW2}, //RGB 49
    {0, CS13_SW3,   CS14_SW3,   CS15_SW3}, //RGB 50
    {0, CS16_SW2,   CS17_SW2,   CS18_SW2}, //RGB 51
    {0, CS16_SW3,   CS17_SW3,   CS18_SW3}, //RGB 52
    {0, CS19_SW3,   CS20_SW3,   CS21_SW3}, //RGB 53
    {0, CS22_SW3,   CS23_SW3,   CS24_SW3}, //RGB 54
    {0, CS25_SW3,   CS26_SW3,   CS27_SW3}, //RGB 55
    {0, CS28_SW3,   CS29_SW3,   CS30_SW3}, //RGB 56
    {0, CS36_SW3,   CS35_SW3,   CS34_SW3}, //RGB 57
    {0, CS39_SW3,   CS38_SW3,   CS37_SW3}, //RGB 58

    // ROW 5
    {0, CS1_SW1,    CS2_SW1,    CS3_SW1}, //RGB 59
    {0, CS4_SW1,    CS5_SW1,    CS6_SW1}, //RGB 60
    {0, CS7_SW1,    CS8_SW1,    CS9_SW1}, //RGB 61
    {0, CS13_SW1,   CS14_SW1,   CS15_SW1}, //RGB 63 (NOT A MISCOUNT)
    {0, CS22_SW1,   CS23_SW1,   CS24_SW1}, //RGB 66 (NOT A MISCOUNT)
    {0, CS25_SW1,   CS26_SW1,   CS27_SW1}, //RGB 67
    {0, CS31_SW1,   CS32_SW1,   CS33_SW1}, //RGB 68
    {0, CS36_SW1,   CS35_SW1,   CS34_SW1}, //RGB 69
    {0, CS39_SW1,   CS38_SW1,   CS37_SW1} //RGB 70
};
led_config_t g_led_config = {
	{
		/* C0     C1      C2      C3      C4      C5      C6      C7      C8      C9       C10      C11     C12     C13      C14     C15*/
		{  0,      1,      2,      3,     4,       5,      6,      7,      8,      9,       10,      11,     12,     NO_LED, 13,     NO_LED, }, /* R0 */
		{ 14,     15,     16,     17,     18,     19,     20,     21,     22,     23,       24,      25,     26,     27,     NO_LED, 28,     }, /* R1 */
		{ 29,     30,     31,     32,     33,     34,     35,     36,     37,     38,       39,      40,     NO_LED, NO_LED, 41,     42,     }, /* R2 */
		{ 43,     44,     45,     46,     47,     48,     49,     50,     51,     52,       53,      54,     55,     NO_LED, 56,     57,     }, /* R3 */
		{ 58,     59,     60,     NO_LED, NO_LED, NO_LED, 61,     NO_LED, NO_LED, NO_LED,   62,      63,     NO_LED, 64,     65,     66,     }, /* R4 */
    }, {
        {0,  0},  {14,  0},  {29,  0}, {43,  0}, {58,  0}, {72,  0}, {87,  0}, {101,  0}, {116,  0}, {130,  0}, {145,  0}, {159,  0}, {173,  0},   {195,  0},
		    {11,15},  {22, 15},  {36, 15}, {51, 15}, {65, 15}, {79, 15}, {94, 15}, {108, 15}, {123, 15}, {137, 15}, {152, 15}, {166, 15}, {181, 15}, {208, 23},       {224, 15},
		    {13, 30},  {25, 30},  {40, 30}, {54, 30}, {69, 30}, {83, 30}, {98, 30}, {112, 30}, {126, 30}, {141, 30}, {155, 30}, {170, 30}, {184, 30},                 {224, 30},
		    {9, 45}, {18, 45}, {33, 45}, {47, 45}, {61, 45}, {76, 45}, {90, 45},  {105, 45}, {119, 45}, {134, 45}, {148, 45}, {163, 45}, {181, 45},    {206, 49},      {224, 45},
		    {9, 60},    {27, 60},   {45, 60},                             {98, 60},                                  {155, 60},   {177, 60},  {191, 64}, {206, 64}, {220, 64},
	}, {
	       4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,         4,
		   4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,         4,        4,
		   4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,                   4,        4,
		   4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,         4,        4,
		   4,       4,         4,                                      4,                                          4,          4,        4,         4,        4,
	}
};
