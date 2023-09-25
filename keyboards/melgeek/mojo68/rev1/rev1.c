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

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS9_SW1, CS8_SW1, CS7_SW1},    /* RGB1 */
    {0, CS9_SW2, CS8_SW2, CS7_SW2},    /* RGB2 */
    {0, CS9_SW3, CS8_SW3, CS7_SW3},    /* RGB3 */
    {0, CS9_SW4, CS8_SW4, CS7_SW4},    /* RGB4 */
    {0, CS9_SW5, CS8_SW5, CS7_SW5},    /* RGB5 */
    {0, CS9_SW6, CS8_SW6, CS7_SW6},    /* RGB6 */
    {0, CS9_SW7, CS8_SW7, CS7_SW7},    /* RGB7 */
    {0, CS9_SW8, CS8_SW8, CS7_SW8},    /* RGB8 */
    {0, CS9_SW9, CS8_SW9, CS7_SW9},    /* RGB9 */
    {0, CS24_SW1, CS23_SW1, CS22_SW1}, /* RGB46 */
    {0, CS24_SW2, CS23_SW2, CS22_SW2}, /* RGB47 */
    {0, CS24_SW3, CS23_SW3, CS22_SW3}, /* RGB48 */
    {0, CS24_SW4, CS23_SW4, CS22_SW4}, /* RGB49 */
    {0, CS24_SW5, CS23_SW5, CS22_SW5}, /* RGB50 */
    {0, CS24_SW6, CS23_SW6, CS22_SW6}, /* RGB51 */
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, /* RGB10 */
    {0, CS12_SW2, CS11_SW2, CS10_SW2}, /* RGB11 */
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, /* RGB12 */
    {0, CS12_SW4, CS11_SW4, CS10_SW4}, /* RGB13 */
    {0, CS12_SW5, CS11_SW5, CS10_SW5}, /* RGB14 */
    {0, CS12_SW6, CS11_SW6, CS10_SW6}, /* RGB15 */
    {0, CS12_SW7, CS11_SW7, CS10_SW7}, /* RGB16 */
    {0, CS12_SW8, CS11_SW8, CS10_SW8}, /* RGB17 */
    {0, CS12_SW9, CS11_SW9, CS10_SW9}, /* RGB18 */
    {0, CS24_SW7, CS23_SW7, CS22_SW7}, /* RGB52 */
    {0, CS24_SW8, CS23_SW8, CS22_SW8}, /* RGB53 */
    {0, CS24_SW9, CS23_SW9, CS22_SW9}, /* RGB54 */
    {0, CS27_SW1, CS26_SW1, CS25_SW1}, /* RGB55 */
    {0, CS27_SW2, CS26_SW2, CS25_SW2}, /* RGB56 */
    {0, CS27_SW3, CS26_SW3, CS25_SW3}, /* RGB57 */
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, /* RGB19 */
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, /* RGB20 */
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, /* RGB21 */
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, /* RGB22 */
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, /* RGB23 */
    {0, CS15_SW6, CS14_SW6, CS13_SW6}, /* RGB24 */
    {0, CS15_SW7, CS14_SW7, CS13_SW7}, /* RGB25 */
    {0, CS15_SW8, CS14_SW8, CS13_SW8}, /* RGB26 */
    {0, CS15_SW9, CS14_SW9, CS13_SW9}, /* RGB27 */
    {0, CS27_SW4, CS26_SW4, CS25_SW4}, /* RGB58 */
    {0, CS27_SW5, CS26_SW5, CS25_SW5}, /* RGB59 */
    {0, CS27_SW6, CS26_SW6, CS25_SW6}, /* RGB60 */
    {0, CS27_SW7, CS26_SW7, CS25_SW7}, /* RGB61 */
    {0, CS27_SW8, CS26_SW8, CS25_SW8}, /* RGB62 */
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, /* RGB28 */
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, /* RGB29 */
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, /* RGB30 */
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, /* RGB31 */
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, /* RGB32 */
    {0, CS18_SW6, CS17_SW6, CS16_SW6}, /* RGB33 */
    {0, CS18_SW7, CS17_SW7, CS16_SW7}, /* RGB34 */
    {0, CS18_SW8, CS17_SW8, CS16_SW8}, /* RGB35 */
    {0, CS18_SW9, CS17_SW9, CS16_SW9}, /* RGB36 */
    {0, CS27_SW9, CS26_SW9, CS25_SW9}, /* RGB63 */
    {0, CS30_SW1, CS29_SW1, CS28_SW1}, /* RGB64 */
    {0, CS30_SW2, CS29_SW2, CS28_SW2}, /* RGB65 */
    {0, CS30_SW3, CS29_SW3, CS28_SW3}, /* RGB66 */
    {0, CS30_SW4, CS29_SW4, CS28_SW4}, /* RGB67 */
    {0, CS21_SW1, CS20_SW1, CS19_SW1}, /* RGB37 */
    {0, CS21_SW2, CS20_SW2, CS19_SW2}, /* RGB38 */
    {0, CS21_SW3, CS20_SW3, CS19_SW3}, /* RGB39 */
    {0, CS21_SW4, CS20_SW4, CS19_SW4}, /* RGB40 */
    {0, CS21_SW5, CS20_SW5, CS19_SW5}, /* RGB41 */
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, /* RGB42 */
    {0, CS21_SW7, CS20_SW7, CS19_SW7}, /* RGB43 */
    {0, CS21_SW8, CS20_SW8, CS19_SW8}, /* RGB44 */
    {0, CS21_SW9, CS20_SW9, CS19_SW9}, /* RGB45 */
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, /* RGB68 */
};

led_config_t g_led_config = {
	{
		/* C0     C1         C2        C3        C4        C5        C6        C7        C8          C9        C10         C11        C12        C13       C14*/
		{  0,      1,         2,        3,        4,        5,        6,        7,        8,          9,        10,         11,       12,        13,       14 }, /* R0 */
		{ 15,     16,        17,       18,       19,       20,       21,       22,       23,         24,        25,         26,       27,        28,       29 }, /* R1 */
		{ 30,     31,        32,       33,       34,       35,       36,       37,       38,         39,        40,         41,       42,        NO_LED,   43 }, /* R2 */
		{ 44,     45,        46,       47,       48,       49,       50,       51,       52,         53,        54,         55,       56,        NO_LED,   57 }, /* R3 */
		{ 58,     59,        60,       NO_LED,   NO_LED,   61,       NO_LED,   NO_LED,   NO_LED,     62,        63,         64,       65,        66,       67 }, /* R4 */
    }, {
        {0, 0},   {16, 0},   {32, 0},  {48, 0},  {64, 0},  {80, 0},  {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},  {224, 0},
		{0, 16},  {16, 16},  {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16}, {224, 16},
		{0, 32},  {16, 32},  {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32}, {208, 32},
		{0, 48},  {16, 48},  {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48},
		{0, 64},  {16, 64},  {32, 64}, {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64},
	}, {
	       4,      4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,         4,
		   4,      4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,         4,
		   4,      4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,
		   4,      4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,
		   4,      4,         4,        4,        4,        4,        4,        4,         4,         4,
	}
};

const is31_led g_is31_indicator_leds[3] = {
    {0, CS6_SW1, CS5_SW1, CS4_SW1}, /* RGB124 */
    {0, CS6_SW2, CS5_SW2, CS4_SW2}, /* RGB125 */
    {0, CS6_SW3, CS5_SW3, CS4_SW3}, /* RGB126 */
};

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        if (led_state.caps_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0xff, 0x00, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0x00, 0x00, 0x00);
        }

        if (led_state.num_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0x00, 0xff, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0x00, 0x00, 0x00);
        }

        if (led_state.scroll_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0x00, 0xff);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0x00, 0x00);
        }
    }
    return true;
}

void matrix_init_kb(void) {
    for (int i = 0; i < DRIVER_INDICATOR_LED_TOTAL; ++i) {
        is31_led led = g_is31_indicator_leds[i];
        is31fl3741_set_scaling_registers(&led, 0xFF, 0xFF, 0xFF);
    }

    is31fl3741_update_led_control_registers(DRIVER_ADDR_1, 0);

    matrix_init_user();
}


void keyboard_pre_init_kb(void) {
    setPinOutput(B7);
    writePinHigh(B7);
    keyboard_pre_init_user();
}
#endif
