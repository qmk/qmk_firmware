/* Copyright 2020 MelGeek <melgeek001365@gmail.com>
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
    {0,  SW1_CS6,  SW1_CS5,  SW1_CS4}, /* RGB1 */
    {0,  SW2_CS6,  SW2_CS5,  SW2_CS4}, /* RGB2 */
    {0,  SW3_CS6,  SW3_CS5,  SW3_CS4}, /* RGB3 */
    {0,  SW4_CS6,  SW4_CS5,  SW4_CS4}, /* RGB4 */
    {0,  SW5_CS6,  SW5_CS5,  SW5_CS4}, /* RGB5 */
    {0,  SW6_CS6,  SW6_CS5,  SW6_CS4}, /* RGB6 */
    {0,  SW7_CS6,  SW7_CS5,  SW7_CS4}, /* RGB7 */
    {0,  SW8_CS6,  SW8_CS5,  SW8_CS4}, /* RGB8 */
    {0,  SW9_CS6,  SW9_CS5,  SW9_CS4}, /* RGB9 */
    {0, SW1_CS24, SW1_CS23, SW1_CS22}, /* RGB55 */
    {0, SW2_CS24, SW2_CS23, SW2_CS22}, /* RGB56 */
	{0, SW3_CS24, SW3_CS23, SW3_CS22}, /* RGB57 */
    {0, SW4_CS24, SW4_CS23, SW4_CS22}, /* RGB58 */
    {0, SW5_CS24, SW5_CS23, SW5_CS22}, /* RGB59 */
    {0, SW6_CS24, SW6_CS23, SW6_CS22}, /* RGB60 */
    {0, SW7_CS24, SW7_CS23, SW7_CS22}, /* RGB61 */
    {0,  SW1_CS9,  SW1_CS8,  SW1_CS7}, /* RGB10 */
    {0,  SW2_CS9,  SW2_CS8,  SW2_CS7}, /* RGB11 */
    {0,  SW3_CS9,  SW3_CS8,  SW3_CS7}, /* RGB12 */
    {0,  SW4_CS9,  SW4_CS8,  SW4_CS7}, /* RGB13 */
    {0,  SW5_CS9,  SW5_CS8,  SW5_CS7}, /* RGB14 */
    {0,  SW6_CS9,  SW6_CS8,  SW6_CS7}, /* RGB15 */
    {0,  SW7_CS9,  SW7_CS8,  SW7_CS7}, /* RGB16 */
    {0,  SW8_CS9,  SW8_CS8,  SW8_CS7}, /* RGB17 */
    {0,  SW9_CS9,  SW9_CS8,  SW9_CS7}, /* RGB18 */
    {0, SW8_CS24, SW8_CS23, SW8_CS22}, /* RGB62 */
    {0, SW9_CS24, SW9_CS23, SW9_CS22}, /* RGB63 */
    {0, SW1_CS27, SW1_CS26, SW1_CS25}, /* RGB64 */
    {0, SW2_CS27, SW2_CS26, SW2_CS25}, /* RGB65 */
	{0, SW3_CS27, SW3_CS26, SW3_CS25}, /* RGB66 */
    {0, SW4_CS27, SW4_CS26, SW4_CS25}, /* RGB67 */
    {0, SW5_CS27, SW5_CS26, SW5_CS25}, /* RGB68 */
    {0, SW6_CS27, SW6_CS26, SW6_CS25}, /* RGB69 */
    {0, SW1_CS12, SW1_CS11, SW1_CS10}, /* RGB19 */
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, /* RGB20 */
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, /* RGB21 */
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, /* RGB22 */
    {0, SW5_CS12, SW5_CS11, SW5_CS10}, /* RGB23 */
    {0, SW6_CS12, SW6_CS11, SW6_CS10}, /* RGB24 */
    {0, SW7_CS12, SW7_CS11, SW7_CS10}, /* RGB25 */
    {0, SW8_CS12, SW8_CS11, SW8_CS10}, /* RGB26 */
    {0, SW9_CS12, SW9_CS11, SW9_CS10}, /* RGB27 */
    {0, SW7_CS27, SW7_CS26, SW7_CS25}, /* RGB70 */
    {0, SW8_CS27, SW8_CS26, SW8_CS25}, /* RGB71 */
    {0, SW9_CS27, SW9_CS26, SW9_CS25}, /* RGB72 */
    {0, SW1_CS30, SW1_CS29, SW1_CS28}, /* RGB86 */
    {0, SW2_CS30, SW2_CS29, SW2_CS28}, /* RGB73 */
    {0, SW3_CS30, SW3_CS29, SW3_CS28}, /* RGB74 */
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, /* RGB28 */
    {0, SW2_CS15, SW2_CS14, SW2_CS13}, /* RGB29 */
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, /* RGB30 */
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, /* RGB31 */
    {0, SW5_CS15, SW5_CS14, SW5_CS13}, /* RGB32 */
    {0, SW6_CS15, SW6_CS14, SW6_CS13}, /* RGB33 */
    {0, SW7_CS15, SW7_CS14, SW7_CS13}, /* RGB34 */
    {0, SW8_CS15, SW8_CS14, SW8_CS13}, /* RGB35 */
    {0, SW9_CS15, SW9_CS14, SW9_CS13}, /* RGB36 */
    {0, SW4_CS30, SW4_CS29, SW4_CS28}, /* RGB75 */
    {0, SW5_CS30, SW5_CS29, SW5_CS28}, /* RGB76 */
    {0, SW6_CS30, SW6_CS29, SW6_CS28}, /* RGB77 */
    {0, SW7_CS30, SW7_CS29, SW7_CS28}, /* RGB78 */
    {0, SW8_CS30, SW8_CS29, SW8_CS28}, /* RGB79 */
    {0, SW9_CS30, SW9_CS29, SW9_CS28}, /* RGB80 */
    {0, SW1_CS39, SW1_CS38, SW1_CS37}, /* RGB91 */
    {0, SW1_CS18, SW1_CS17, SW1_CS16}, /* RGB37 */
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, /* RGB38 */
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, /* RGB39 */
    {0, SW4_CS18, SW4_CS17, SW4_CS16}, /* RGB40 */
    {0, SW5_CS18, SW5_CS17, SW5_CS16}, /* RGB41 */
    {0, SW6_CS18, SW6_CS17, SW6_CS16}, /* RGB42 */
    {0, SW7_CS18, SW7_CS17, SW7_CS16}, /* RGB43 */
    {0, SW8_CS18, SW8_CS17, SW8_CS16}, /* RGB44 */
    {0, SW9_CS18, SW9_CS17, SW9_CS16}, /* RGB45 */
    {0, SW3_CS36, SW3_CS35, SW3_CS34}, /* RGB84 */
    {0, SW4_CS36, SW4_CS35, SW4_CS34}, /* RGB83 */
    {0, SW2_CS36, SW2_CS35, SW2_CS34}, /* RGB82 */
    {0, SW6_CS36, SW6_CS35, SW6_CS34}, /* RGB85 */
    {0, SW1_CS36, SW1_CS35, SW1_CS34}, /* RGB81 */
    {0, SW2_CS39, SW2_CS38, SW2_CS37}, /* RGB87 */
    {0, SW3_CS39, SW3_CS38, SW3_CS37}, /* RGB89 */
    {0, SW1_CS21, SW1_CS20, SW1_CS19}, /* RGB46 */
	{0, SW2_CS21, SW2_CS20, SW2_CS19}, /* RGB47 */
    {0, SW3_CS21, SW3_CS20, SW3_CS19}, /* RGB48 */
	{0, SW4_CS21, SW4_CS20, SW4_CS19}, /* RGB49 */
	{0, SW5_CS21, SW5_CS20, SW5_CS19}, /* RGB50 */
    {0, SW6_CS21, SW6_CS20, SW6_CS19}, /* RGB51 */
    {0, SW7_CS21, SW7_CS20, SW7_CS19}, /* RGB52 */
    {0, SW8_CS21, SW8_CS20, SW8_CS19}, /* RGB53 */
    {0, SW9_CS21, SW9_CS20, SW9_CS19}, /* RGB54 */
    {0, SW4_CS39, SW4_CS38, SW4_CS37}, /* RGB88 */
    {0, SW5_CS39, SW5_CS38, SW5_CS37}, /* RGB92 */
    {0, SW6_CS39, SW6_CS38, SW6_CS37}, /* RGB90 */
};

led_config_t g_led_config = {
	{
		/* C0     C1         C2        C3        C4        C5        C6        C7        C8          C9        C10         C11        C12        C13        C14        C15   */
		{  0,      1,         2,        3,        4,        5,        6,        7,        8,          9,        10,         11,       12,        13,        14,        15 }, /* R0 */
		{ 16,     17,        18,       19,       20,       21,       22,       23,       24,         25,        26,         27,       28,        30,        NO_LED,    32 }, /* R1 */
		{ 33,     34,        35,       36,       37,       38,       39,       40,       41,         42,        43,         44,       45,        46,        NO_LED,    47 }, /* R2 */
		{ 48,     49,        50,       51,       52,       53,       54,       55,       56,         57,        58,         59,       NO_LED,    61,        NO_LED,    63 }, /* R3 */
		{ 65,     67,        68,       69,       70,       71,       72,       73,       74,         75,        76,         NO_LED,   77,        NO_LED,    78,        79 }, /* R4 */
		{ 80,     81,        82,       NO_LED,   NO_LED,   84,       NO_LED,   NO_LED,   NO_LED,     86,        87,         NO_LED,   88,        89,        90,        91 }, /* R5 */
    }, {
        {0,  0},  {16, 0},   {32, 0},  {48, 0},  {64, 0},  {80, 0},  {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},   {224, 0},  {240, 0},
		{0, 16},  {16, 16},  {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16},  {224, 16}, {240, 16}, {255, 16},
		{0, 32},  {16, 32},  {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32}, {208, 32},  {224, 32},
		{0, 48},  {16, 48},  {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48},  {224, 48}, {240, 48},
		{0, 64},  {16, 64},  {32, 64}, {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64}, {160, 64}, {176, 64}, {192, 64}, {208, 64},  {224, 64}, {240, 64},
		{0, 80},  {16, 80},  {32, 80}, {48, 80}, {64, 80}, {80, 80}, {96, 80}, {112, 80}, {128, 80}, {144, 80}, {160, 80}, {176, 80},
	}, {
	     4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,          4,         4,
	     4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,          4,         4,        4,
	     4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,          4,
	     4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,          4,         4,
		 4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,          4,         4,
		 4,        4,         4,        4,        4,        4,        4,        4,         4,         4,         4,         4,
	}
};


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
