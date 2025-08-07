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
    {0, SW1_CS28, SW1_CS30, SW1_CS29}, /* RGB10 */
    {0, SW2_CS28, SW2_CS30, SW2_CS29}, /* RGB11 */
    {0, SW3_CS28, SW3_CS30, SW3_CS29}, /* RGB12 */
    {0, SW4_CS28, SW4_CS30, SW4_CS29}, /* RGB13 */
    {0, SW5_CS28, SW5_CS30, SW5_CS29}, /* RGB14 */
    {0, SW6_CS28, SW6_CS30, SW6_CS29}, /* RGB15 */
    {0, SW7_CS28, SW7_CS30, SW7_CS29}, /* RGB16 */
    {0, SW8_CS28, SW8_CS30, SW8_CS29}, /* RGB17 */
    {0, SW9_CS28, SW9_CS30, SW9_CS29}, /* RGB18 */
    {0, SW1_CS31, SW1_CS33, SW1_CS32}, /* RGB28 */
    {0, SW2_CS31, SW2_CS33, SW2_CS32}, /* RGB29 */
    {0, SW3_CS31, SW3_CS33, SW3_CS32}, /* RGB30 */
    {0, SW4_CS31, SW4_CS33, SW4_CS32}, /* RGB31 */
    {0, SW5_CS31, SW5_CS33, SW5_CS32}, /* RGB32 */
    {0, SW6_CS31, SW6_CS33, SW6_CS32}, /* RGB33 */
    {0, SW1_CS25, SW1_CS27, SW1_CS26}, /* RGB1 */
    {0, SW2_CS25, SW2_CS27, SW2_CS26}, /* RGB2 */
    {0, SW3_CS25, SW3_CS27, SW3_CS26}, /* RGB3 */
    {0, SW4_CS25, SW4_CS27, SW4_CS26}, /* RGB4 */
    {0, SW5_CS25, SW5_CS27, SW5_CS26}, /* RGB5 */
    {0, SW6_CS25, SW6_CS27, SW6_CS26}, /* RGB6 */
    {0, SW7_CS25, SW7_CS27, SW7_CS26}, /* RGB7 */
    {0, SW8_CS25, SW8_CS27, SW8_CS26}, /* RGB8 */
    {0, SW9_CS25, SW9_CS27, SW9_CS26}, /* RGB9 */
    {0, SW1_CS34, SW1_CS36, SW1_CS35}, /* RGB46 */
    {0, SW2_CS34, SW2_CS36, SW2_CS35}, /* RGB47 */
    {0, SW3_CS34, SW3_CS36, SW3_CS35}, /* RGB48 */
    {0, SW4_CS34, SW4_CS36, SW4_CS35}, /* RGB49 */
    {0, SW5_CS34, SW5_CS36, SW5_CS35}, /* RGB50 */
    {0, SW7_CS31, SW7_CS33, SW7_CS32}, /* RGB34 */
    {0, SW1_CS22, SW1_CS24, SW1_CS23}, /* RGB37 */
    {0, SW2_CS22, SW2_CS24, SW2_CS23}, /* RGB38 */
    {0, SW3_CS22, SW3_CS24, SW3_CS23}, /* RGB39 */
    {0, SW4_CS22, SW4_CS24, SW4_CS23}, /* RGB40 */
    {0, SW5_CS22, SW5_CS24, SW5_CS23}, /* RGB41 */
    {0, SW6_CS22, SW6_CS24, SW6_CS23}, /* RGB42 */
    {0, SW7_CS22, SW7_CS24, SW7_CS23}, /* RGB43 */
    {0, SW8_CS22, SW8_CS24, SW8_CS23}, /* RGB44 */
    {0, SW9_CS22, SW9_CS24, SW9_CS23}, /* RGB45 */
    {0, SW9_CS34, SW9_CS36, SW9_CS35}, /* RGB54 */
    {0, SW8_CS34, SW8_CS36, SW8_CS35}, /* RGB53 */
    {0, SW7_CS34, SW7_CS36, SW7_CS35}, /* RGB52 */
    {0, SW6_CS34, SW6_CS36, SW6_CS35}, /* RGB51 */
    {0, SW8_CS31, SW8_CS33, SW8_CS32}, /* RGB35 */
    {0, SW2_CS19, SW2_CS21, SW2_CS20}, /* RGB56 */
    {0, SW4_CS19, SW4_CS21, SW4_CS20}, /* RGB60 */
    {0, SW5_CS19, SW5_CS21, SW5_CS20}, /* RGB59 */
    {0, SW6_CS19, SW6_CS21, SW6_CS20}, /* RGB60 */
    {0, SW7_CS19, SW7_CS21, SW7_CS20}, /* RGB61 */
    {0, SW8_CS19, SW8_CS21, SW8_CS20}, /* RGB62 */
    {0, SW9_CS19, SW9_CS21, SW9_CS20}, /* RGB63 */
    {0, SW3_CS19, SW3_CS21, SW3_CS20}, /* RGB57 */
    {0, SW1_CS19, SW1_CS21, SW1_CS20}, /* RGB55 */
    {0, SW5_CS37, SW5_CS39, SW5_CS38}, /* RGB23 */
    {0, SW6_CS37, SW6_CS39, SW6_CS38}, /* RGB24 */
    {0, SW7_CS37, SW7_CS39, SW7_CS38}, /* RGB25 */
    {0, SW8_CS37, SW8_CS39, SW8_CS38}, /* RGB26 */
    {0, SW9_CS31, SW9_CS33, SW9_CS32}, /* RGB36 */

    {0, SW1_CS6, SW1_CS8, SW1_CS7},    /* RGB64 */
    {0, SW3_CS6, SW3_CS8, SW3_CS7},    /* RGB66 */
    {0, SW4_CS6, SW4_CS8, SW4_CS7},    /* RGB67 */
    {0, SW5_CS6, SW5_CS8, SW5_CS7},    /* RGB69 */
    {0, SW6_CS6, SW6_CS8, SW6_CS7},    /* RGB70 */
    {0, SW2_CS6, SW2_CS8, SW2_CS7},    /* RGB65 */

    {0, SW1_CS37, SW1_CS39, SW1_CS38}, /* RGB19 */
    {0, SW2_CS37, SW2_CS39, SW2_CS38}, /* RGB20 */
    {0, SW3_CS37, SW3_CS39, SW3_CS38}, /* RGB21 */
    {0, SW4_CS37, SW4_CS39, SW4_CS38}, /* RGB22 */
    {0, SW9_CS37, SW9_CS39, SW9_CS38}, /* RGB27 */
};
led_config_t g_led_config = {
	{
		/* C0     C1      C2      C3      C4      C5      C6      C7      C8      C9       C10      C11     C12     C13      */
		{  0,      1,      2,      3,     4,       5,      6,      7,      8,      9,       10,      11,     12,     13,     }, /* R0 */
		{ 15,     16,     17,     18,     19,     20,     21,     22,     23,     24,       25,      26,     27,     28,     }, /* R1 */
		{ 30,     31,     32,     33,     34,     35,     36,     37,     38,     39,       40,      41,     NO_LED, 42,     }, /* R2 */
		{ 44,     NO_LED, 45,     46,     47,     48,     49,     50,     51,     52,       53,      54,     55,     NO_LED, }, /* R3 */
		{ 58,     59,     60,     NO_LED, 61,     62,     63,     NO_LED, NO_LED, 64,       65,      NO_LED, NO_LED, NO_LED, }, /* R4 */
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 14,     29,     56,     43,       57,      66,     67,     68,     }, /* R5 */
    }, {
        {0,  0},  {16,  0},  {32,  0}, {48,  0}, {64,  0}, {80,  0}, {96,  0}, {112,  0}, {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {208,  0}, 
		{0, 16},  {16, 16},  {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16}, 
		{0, 32},  {16, 32},  {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32},            {192, 32}, 
		{0, 48},             {16, 48}, {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48},  {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48},
		{0, 64},  {16, 64},  {32, 64},           {48, 64}, {64, 64}, {80, 64},                        {96, 64}, {112, 64}, 
		                                                             {0, 80},  {16, 80},  {32, 80},   {48, 80}, {64, 80}, {80, 80},   {96, 80}, {112, 80}, 
	}, {
	       4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,         4,
		   4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,         4,
		   4,       4,         4,        4,        4,        4,        4,        4,          4,         4,         4,          4,                   4,
		   4,                  4,        4,        4,        4,        4,        4,          4,         4,         4,          4,        4,
		   4,       4,         4,                  4,        4,        4,                               4,         4,
		                                                               4,        4,          4,         4,         4,          4,        4,         4,
	}
};

const is31fl3741_led_t g_is31_indicator_leds[6] = {
    {0, SW1_CS5, SW1_CS3, SW1_CS4}, /* RGB71 */
    {0, SW2_CS5, SW2_CS3, SW2_CS4}, /* RGB72 */
    {0, SW3_CS5, SW3_CS3, SW3_CS4}, /* RGB73 */
    {0, SW4_CS5, SW4_CS3, SW4_CS4}, /* RGB74 */
    {0, SW5_CS5, SW5_CS3, SW5_CS4}, /* RGB75 */
    {0, SW6_CS5, SW6_CS3, SW6_CS4}, /* RGB76 */
};

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        if (led_state.caps_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0xff, 0x00, 0x00);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[3], 0xff, 0x00, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[2], 0x00, 0x00, 0x00);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[3], 0x00, 0x00, 0x00);
        }

        if (led_state.num_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0x00, 0xff, 0x00);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[4], 0x00, 0xff, 0x00);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[1], 0x00, 0x00, 0x00);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[4], 0x00, 0x00, 0x00);
        }

        if (led_state.scroll_lock) {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0x00, 0xff);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[5], 0x00, 0x00, 0xff);
        } else {
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[0], 0x00, 0x00, 0x00);
            is31fl3741_set_pwm_buffer(&g_is31_indicator_leds[5], 0x00, 0x00, 0x00);
        }
    }
    return true;
}

void matrix_init_kb(void) {
    for (int i = 0; i < DRIVER_INDICATOR_LED_TOTAL; ++i) {
        is31fl3741_led_t led = g_is31_indicator_leds[i];
        is31fl3741_set_scaling_registers(&led, 0xFF, 0xFF, 0xFF);
    }

    is31fl3741_update_led_control_registers(0);

    matrix_init_user();
}
#endif
