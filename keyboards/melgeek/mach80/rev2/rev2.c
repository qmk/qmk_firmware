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
    {0, CS9_SW1,  CS8_SW1,  CS7_SW1},  /* RGB1 */
    {0, CS9_SW2,  CS8_SW2,  CS7_SW2},  /* RGB2 */
    {0, CS9_SW3,  CS8_SW3,  CS7_SW3},  /* RGB3 */
    {0, CS9_SW4,  CS8_SW4,  CS7_SW4},  /* RGB4 */
    {0, CS9_SW5,  CS8_SW5,  CS7_SW5},  /* RGB5 */
    {0, CS9_SW6,  CS8_SW6,  CS7_SW6},  /* RGB6 */
    {0, CS9_SW7,  CS8_SW7,  CS7_SW7},  /* RGB7 */
    {0, CS9_SW8,  CS8_SW8,  CS7_SW8},  /* RGB8 */
    {0, CS9_SW9,  CS8_SW9,  CS7_SW9},  /* RGB9 */
    {0, CS27_SW1, CS26_SW1, CS25_SW1}, /* RGB65 */
    {0, CS27_SW2, CS26_SW2, CS25_SW2}, /* RGB56 */
    {0, CS27_SW3, CS26_SW3, CS25_SW3}, /* RGB57 */
    {0, CS27_SW4, CS26_SW4, CS25_SW4}, /* RGB58 */
    {0, CS27_SW5, CS26_SW5, CS25_SW5}, /* RGB59 */
    {0, CS27_SW6, CS26_SW6, CS25_SW6}, /* RGB67 */
    {0, CS27_SW7, CS26_SW7, CS25_SW7}, /* RGB68 */
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, /* RGB10 */
	{0, CS12_SW2, CS11_SW2, CS10_SW2}, /* RGB11 */
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, /* RGB12 */
	{0, CS12_SW4, CS11_SW4, CS10_SW4}, /* RGB13 */
	{0, CS12_SW5, CS11_SW5, CS10_SW5}, /* RGB14 */
    {0, CS12_SW6, CS11_SW6, CS10_SW6}, /* RGB15 */
    {0, CS12_SW7, CS11_SW7, CS10_SW7}, /* RGB16 */
    {0, CS12_SW8, CS11_SW8, CS10_SW8}, /* RGB17 */
    {0, CS12_SW9, CS11_SW9, CS10_SW9}, /* RGB18 */
    {0, CS27_SW8, CS26_SW8, CS25_SW8}, /* RGB69 */
    {0, CS27_SW9, CS26_SW9, CS25_SW9}, /* RGB70 */
    {0, CS30_SW1, CS29_SW1, CS28_SW1}, /* RGB64 */
    {0, CS30_SW2, CS29_SW2, CS28_SW2}, /* RGB55 */
    {0, CS30_SW3, CS29_SW3, CS28_SW3}, /* RGB71 */
    {0, CS30_SW4, CS29_SW4, CS28_SW4}, /* RGB72 */
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, /* RGB66 */
    {0, CS30_SW6, CS29_SW6, CS28_SW6}, /* RGB60 */
    {0, CS30_SW7, CS29_SW7, CS28_SW7}, /* RGB61 */
    {0, CS30_SW8, CS29_SW8, CS28_SW8}, /* RGB73 */
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, /* RGB19 */
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, /* RGB20 */
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, /* RGB21 */
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, /* RGB22 */
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, /* RGB23 */
    {0, CS15_SW6, CS14_SW6, CS13_SW6}, /* RGB24 */
    {0, CS15_SW7, CS14_SW7, CS13_SW7}, /* RGB25 */
    {0, CS15_SW8, CS14_SW8, CS13_SW8}, /* RGB26 */
    {0, CS15_SW9, CS14_SW9, CS13_SW9}, /* RGB27 */
    {0, CS30_SW9, CS29_SW9, CS28_SW9}, /* RGB74 */
	{0, CS33_SW1, CS32_SW1, CS31_SW1}, /* RGB75 */
    {0, CS33_SW2, CS32_SW2, CS31_SW2}, /* RGB76 */
    {0, CS33_SW3, CS32_SW3, CS31_SW3}, /* RGB77 */
    {0, CS33_SW4, CS32_SW4, CS31_SW4}, /* RGB78 */
    {0, CS33_SW5, CS32_SW5, CS31_SW5}, /* RGB79 */
    {0, CS33_SW6, CS32_SW6, CS31_SW6}, /* RGB80 */
    {0, CS33_SW7, CS32_SW7, CS31_SW7}, /* RGB83 */
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, /* RGB28 */
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, /* RGB29 */
	{0, CS18_SW3, CS17_SW3, CS16_SW3}, /* RGB30 */
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, /* RGB31 */
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, /* RGB32 */
    {0, CS18_SW6, CS17_SW6, CS16_SW6}, /* RGB33 */
    {0, CS18_SW7, CS17_SW7, CS16_SW7}, /* RGB34 */
    {0, CS18_SW8, CS17_SW8, CS16_SW8}, /* RGB35 */
    {0, CS18_SW9, CS17_SW9, CS16_SW9}, /* RGB36 */
    {0, CS33_SW8, CS32_SW8, CS31_SW8}, /* RGB81 */
    {0, CS33_SW9, CS32_SW9, CS31_SW9}, /* RGB82 */
    {0, CS36_SW1, CS35_SW1, CS34_SW1}, /* RGB89 */
    {0, CS36_SW2, CS35_SW2, CS34_SW2}, /* RGB90 */
    {0, CS36_SW3, CS35_SW3, CS34_SW3}, /* RGB91 */
    {0, CS36_SW4, CS35_SW4, CS34_SW4}, /* RGB92 */
    {0, CS21_SW1, CS20_SW1, CS19_SW1}, /* RGB37 */
    {0, CS21_SW2, CS20_SW2, CS19_SW2}, /* RGB38 */
    {0, CS21_SW3, CS20_SW3, CS19_SW3}, /* RGB39 */
    {0, CS21_SW4, CS20_SW4, CS19_SW4}, /* RGB40 */
    {0, CS21_SW5, CS20_SW5, CS19_SW5}, /* RGB41 */
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, /* RGB42 */
    {0, CS21_SW7, CS20_SW7, CS19_SW7}, /* RGB43 */
    {0, CS21_SW8, CS20_SW8, CS19_SW8}, /* RGB44 */
    {0, CS21_SW9, CS20_SW9, CS19_SW9}, /* RGB45 */
    {0, CS36_SW5, CS35_SW5, CS34_SW5}, /* RGB84 */
    {0, CS36_SW6, CS35_SW6, CS34_SW6}, /* RGB85 */
    {0, CS36_SW7, CS35_SW7, CS34_SW7}, /* RGB88 */
    {0, CS36_SW8, CS35_SW8, CS34_SW8}, /* RGB86 */
    {0, CS36_SW9, CS35_SW9, CS34_SW9}, /* RGB87 */
    {0, CS39_SW1, CS38_SW1, CS37_SW1}, /* RGB98 */
    {0, CS39_SW2, CS38_SW2, CS37_SW2}, /* RGB99 */
    {0, CS39_SW3, CS38_SW3, CS37_SW3}, /* RGB100 */
    {0, CS24_SW1, CS23_SW1, CS22_SW1}, /* RGB46 */
    {0, CS24_SW2, CS23_SW2, CS22_SW2}, /* RGB47 */
    {0, CS24_SW3, CS23_SW3, CS22_SW3}, /* RGB48 */
    {0, CS24_SW4, CS23_SW4, CS22_SW4}, /* RGB49 */
    {0, CS24_SW5, CS23_SW5, CS22_SW5}, /* RGB50 */
    {0, CS24_SW6, CS23_SW6, CS22_SW6}, /* RGB51 */
    {0, CS24_SW7, CS23_SW7, CS22_SW7}, /* RGB52 */
    {0, CS24_SW8, CS23_SW8, CS22_SW8}, /* RGB53 */
    {0, CS24_SW9, CS23_SW9, CS22_SW9}, /* RGB54 */
    {0, CS39_SW4, CS38_SW4, CS37_SW4}, /* RGB101 */
};
led_config_t g_led_config = {
	{
		/* C0       C1       C2       C3       C4       C5       C6       C7       C8       C9       C10       C11       C12       C13       C14       C15 */
		{  0,  NO_LED,       1,       2,       3,       4,       5,       6,       7,       8,        9,       10,       11,       12,       13,       14 }, /* R0 */
		{ 16,      17,      18,      19,      20,      21,      22,      23,      24,      25,       26,       27,       28,       30,       32,       33 }, /* R1 */
		{ 35,      36,      37,      38,      39,      40,      41,      42,      43,      44,       45,       46,       47,       48,       49,       50 }, /* R2 */
		{ 52,      53,      54,      55,      56,      57,      58,      59,      60,      61,       62,       63,       65,       15,       34,       51 }, /* R3 */
		{ 68,      70,      71,      72,      73,      74,      75,      76,      77,      78,       79,       81,   NO_LED,   NO_LED,       83,   NO_LED }, /* R4 */
		{ 84,  NO_LED,      85,  NO_LED,  NO_LED,      87,  NO_LED,  NO_LED,  NO_LED,      89,   NO_LED,   NO_LED,       90,       91,       92,       93 }  /* R5 */
    }, {
        {0, 0},   {12, 0},   {24, 0},  {36, 0},  {48, 0},  {60, 0},  {72, 0},  {84, 0},  {96, 0},  {108, 0},  {120, 0},  {132, 0},  {144, 0},  {156, 0},  {168, 0},  {180, 0},                                   //16
		{0, 12},  {12, 12},  {24, 12}, {36, 12}, {48, 12}, {60, 12}, {72, 12}, {84, 12}, {96, 12}, {108, 12}, {120, 12}, {132, 12}, {144, 12}, {156, 12}, {168, 12}, {180, 12}, {192, 12}, {204, 12}, {216, 12}, //19
		{0, 24},  {12, 24},  {24, 24}, {36, 24}, {48, 24}, {60, 24}, {72, 24}, {84, 24}, {96, 24}, {108, 24}, {120, 24}, {132, 24}, {144, 24}, {156, 24}, {168, 24}, {180, 24}, {192, 24},                       //17
		{0, 36},  {12, 36},  {24, 36}, {36, 36}, {48, 36}, {60, 36}, {72, 36}, {84, 36}, {96, 36}, {108, 36}, {120, 36}, {132, 36}, {144, 36}, {156, 36}, {168, 36},                                             //15
		{0, 48},  {12, 48},  {24, 48}, {36, 48}, {48, 48}, {60, 48}, {72, 48}, {84, 48}, {96, 48}, {108, 48}, {120, 48}, {132, 48}, {144, 48}, {156, 48}, {168, 48}, {180, 48}, {192, 48},                       //17
		{0, 60},  {12, 60},  {24, 60}, {36, 60}, {48, 60}, {60, 60}, {72, 60}, {84, 60}, {96, 60}, {108, 60}
		//10
	}, {          
	       4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,         4,         4,         4,       
		   4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,         4,         4,         4,         4,         4,         4,
		   4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,         4,         4,         4,         4,
		   4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,         4,         4,         
		   4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         4,         4,         4,         4,         4,         4,         4,
		   4,         4,         4,        4,        4,        4,        4,         4,         4,         4,         
	}
};

const is31fl3741_led_t g_is31_indicator_leds[3] = {
    {0, CS6_SW1, CS5_SW1, CS4_SW1}, /* RGB107 */
    {0, CS6_SW2, CS5_SW2, CS4_SW2}, /* RGB108 */
    {0, CS6_SW3, CS5_SW3, CS4_SW3}, /* RGB109 */
};

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        if (led_state.caps_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0x00, 0x00, 0xff);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0x00, 0x00, 0x00);
        }

        if (led_state.num_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0xff, 0x00, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0x00, 0x00, 0x00);
        }

        if (led_state.scroll_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0xff, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0x00, 0x00);
        }
    }
    return true;
}

void matrix_init_kb(void) {
    for (int i = 0; i < DRIVER_INDICATOR_LED_TOTAL; ++i) {
        is31fl3741_led_t led = g_is31_indicator_leds[i];
        is31fl3741_set_scaling_registers(&led, 0xFF, 0xFF, 0xFF);
    }

    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_1, 0);

    matrix_init_user();
}


void keyboard_pre_init_kb(void) {
    setPinOutput(B7);
    writePinHigh(B7);
    keyboard_pre_init_user();
}
#endif
