/* Copyright 2021 dztech
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
#include "rgb.h"
#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS18_SW1, CS17_SW1, CS16_SW1},    /* RGB6 */
    {0, CS18_SW3, CS17_SW3, CS16_SW3},    /* RGB32 */
    {0, CS18_SW4, CS17_SW4, CS16_SW4},    /* RGB45 */
    {0, CS18_SW5, CS17_SW5, CS16_SW5},    /* RGB58 */
    {0, CS18_SW6, CS17_SW6, CS16_SW6},    /* RGB71 */
    {0, CS18_SW7, CS17_SW7, CS16_SW7},    /* RGB84 */
    {0, CS18_SW8, CS17_SW8, CS16_SW8},    /* RGB97 */
    {0, CS21_SW1, CS20_SW1, CS19_SW1},    /* RGB7 */
    {0, CS21_SW2, CS20_SW2, CS19_SW2},    /* RGB20 */
    {0, CS21_SW3, CS20_SW3, CS19_SW3},    /* RGB33 */
    {0, CS21_SW4, CS20_SW4, CS19_SW4},    /* RGB46 */
    {0, CS21_SW5, CS20_SW5, CS19_SW5},    /* RGB59 */
    {0, CS21_SW6, CS20_SW6, CS19_SW6},    /* RGB72 */
    {0, CS21_SW7, CS20_SW7, CS19_SW7},    /* RGB85 */

    {0, CS15_SW1, CS14_SW1, CS13_SW1},    /* RGB5 */
    {0, CS15_SW2, CS14_SW2, CS13_SW2},    /* RGB18 */
    {0, CS15_SW3, CS14_SW3, CS13_SW3},    /* RGB31 */
    {0, CS15_SW4, CS14_SW4, CS13_SW4},    /* RGB44 */
    {0, CS15_SW5, CS14_SW5, CS13_SW5},    /* RGB57 */
    {0, CS15_SW6, CS14_SW6, CS13_SW6},    /* RGB70 */
    {0, CS15_SW7, CS14_SW7, CS13_SW7},    /* RGB83 */
    {0, CS15_SW8, CS14_SW8, CS13_SW8},    /* RGB96 */
    {0, CS24_SW1, CS23_SW1, CS22_SW1},    /* RGB8 */
    {0, CS24_SW2, CS23_SW2, CS22_SW2},    /* RGB21 */
    {0, CS24_SW3, CS23_SW3, CS22_SW3},    /* RGB34 */
    {0, CS24_SW4, CS23_SW4, CS22_SW4},    /* RGB47 */
    {0, CS24_SW5, CS23_SW5, CS22_SW5},    /* RGB60 */
    {0, CS24_SW6, CS23_SW6, CS22_SW6},    /* RGB73 */
    {0, CS24_SW7, CS23_SW7, CS22_SW7},    /* RGB86 */

    {0, CS12_SW1, CS11_SW1, CS10_SW1},    /* RGB4 */
    {0, CS12_SW2, CS11_SW2, CS10_SW2},    /* RGB17 */
    {0, CS12_SW3, CS11_SW3, CS10_SW3},    /* RGB30 */
    {0, CS12_SW4, CS11_SW4, CS10_SW4},    /* RGB43 */
    {0, CS12_SW5, CS11_SW5, CS10_SW5},    /* RGB56 */
    {0, CS12_SW6, CS11_SW6, CS10_SW6},    /* RGB69 */
    {0, CS12_SW7, CS11_SW7, CS10_SW7},    /* RGB82 */
    {0, CS12_SW8, CS11_SW8, CS10_SW8},    /* RGB95 */
    {0, CS27_SW1, CS26_SW1, CS25_SW1},    /* RGB9 */
    {0, CS27_SW2, CS26_SW2, CS25_SW2},    /* RGB22 */
    {0, CS27_SW3, CS26_SW3, CS25_SW3},    /* RGB35 */
    {0, CS27_SW4, CS26_SW4, CS25_SW4},    /* RGB48 */
    {0, CS27_SW5, CS26_SW5, CS25_SW5},    /* RGB61 */
    {0, CS27_SW6, CS26_SW6, CS25_SW6},    /* RGB74 */
    {0, CS27_SW7, CS26_SW7, CS25_SW7},    /* RGB87 */

    {0, CS9_SW1, CS8_SW1, CS7_SW1},    /* RGB3 */
    {0, CS9_SW2, CS8_SW2, CS7_SW2},    /* RGB16 */
    {0, CS9_SW3, CS8_SW3, CS7_SW3},    /* RGB29*/
    {0, CS9_SW4, CS8_SW4, CS7_SW4},    /* RGB42 */
    {0, CS9_SW5, CS8_SW5, CS7_SW5},    /* RGB55 */
    {0, CS9_SW6, CS8_SW6, CS7_SW6},    /* RGB68 */
    {0, CS9_SW7, CS8_SW7, CS7_SW7},    /* RGB81 */
    {0, CS9_SW8, CS8_SW8, CS7_SW8},    /* RGB94 */
    {0, CS30_SW1, CS29_SW1, CS28_SW1},    /* RGB10 */
    {0, CS30_SW2, CS29_SW2, CS28_SW2},    /* RGB23 */
    {0, CS30_SW3, CS29_SW3, CS28_SW3},    /* RGB36 */
    {0, CS30_SW4, CS29_SW4, CS28_SW4},    /* RGB49 */
    {0, CS30_SW5, CS29_SW5, CS28_SW5},    /* RGB62 */
    {0, CS30_SW7, CS29_SW7, CS28_SW7},    /* RGB88 */

    {0, CS6_SW1, CS5_SW1, CS4_SW1},    /* RGB2 */
    {0, CS6_SW3, CS5_SW3, CS4_SW3},    /* RGB28 */
    {0, CS6_SW4, CS5_SW4, CS4_SW4},    /* RGB41 */
    {0, CS6_SW5, CS5_SW5, CS4_SW5},    /* RGB54 */
    {0, CS6_SW6, CS5_SW6, CS4_SW6},    /* RGB67 */
    {0, CS6_SW7, CS5_SW7, CS4_SW7},    /* RGB80 */
    {0, CS6_SW8, CS5_SW8, CS4_SW8},    /* RGB93 */
    {0, CS33_SW1, CS32_SW1, CS31_SW1},    /* RGB11 */
    {0, CS33_SW2, CS32_SW2, CS31_SW2},    /* RGB24 */
    {0, CS33_SW3, CS32_SW3, CS31_SW3},    /* RGB37 */
    {0, CS33_SW4, CS32_SW4, CS31_SW4},    /* RGB50 */
    {0, CS33_SW5, CS32_SW5, CS31_SW5},    /* RGB63 */
    {0, CS33_SW6, CS32_SW6, CS31_SW6},    /* RGB76 */

    {0, CS3_SW1, CS2_SW1, CS1_SW1},    /* RGB1 */
    {0, CS3_SW2, CS2_SW2, CS1_SW2},    /* RGB14 */
    {0, CS3_SW3, CS2_SW3, CS1_SW3},    /* RGB27 */
    {0, CS36_SW8, CS35_SW8, CS34_SW8},    /* RGB103 */
    {0, CS36_SW3, CS35_SW3, CS34_SW3},    /* RGB38 */
    {0, CS36_SW4, CS35_SW4, CS34_SW4},    /* RGB51 */
    {0, CS36_SW5, CS35_SW5, CS34_SW5},    /* RGB64 */
    {0, CS36_SW6, CS35_SW6, CS34_SW6},    /* RGB77 */
    {0, CS36_SW7, CS35_SW7, CS34_SW7},    /* RGB90 */

    {0, CS18_SW9, CS17_SW9, CS16_SW9},    /* RGB110 */
    {0, CS18_SW2, CS17_SW2, CS16_SW2},    /* RGB19 */
    {0, CS12_SW9, CS11_SW9, CS10_SW9},    /* RGB108 */
    {0, CS21_SW8, CS20_SW8, CS19_SW8},    /* RGB98 */
    {0, CS24_SW9, CS23_SW9, CS22_SW9},    /* RGB112 */
    {0, CS24_SW8, CS23_SW8, CS22_SW8},    /* RGB99 */
    {0, CS9_SW9, CS8_SW9, CS7_SW9},    /* RGB107 */
    {0, CS27_SW8, CS26_SW8, CS25_SW8},    /* RGB100 */
    {0, CS33_SW7, CS32_SW7, CS31_SW7},    /* RGB89 */
    {0, CS33_SW9, CS32_SW9, CS31_SW9},    /* RGB115 */
    {0, CS36_SW9, CS35_SW9, CS34_SW9},    /* RGB116 */
    {0, CS36_SW2, CS35_SW2, CS34_SW2},    /* RGB25 */
    {0, CS3_SW9, CS2_SW9, CS1_SW9},    /* RGB105 */
    {0, CS3_SW4, CS2_SW4, CS1_SW4},    /* RGB40 */
};

led_config_t g_led_config = {
	{
		/* C0     C1      C2      C3      C4      C5      C6      C7      C8      C9       C10      C11     C12     C13      C14     C15*/
		{  0,     NO_LED,  1,      2,      3,     4,       5,      6,      7,      8,      NO_LED,  9,      10,      11,     12,     13,     }, /* R0 */
		{ 14,     15,     16,     17,     18,     19,     20,     21,     22,      23,     24,      25,     26,      NO_LED, 27,     28,     }, /* R1 */
		{ 29,     30,     31,     32,     33,     34,     35,     36,     37,      38,     39,      40,     41,      42,     NO_LED, 43,     }, /* R2 */
		{ 44,     45,     46,     47,     48,     49,     50,     51,     52,      53,     54,      55,     NO_LED,  56,     NO_LED, 57,     }, /* R3 */
		{ 58,     NO_LED, 59,     60,     61,     62,     63,     64,     65,      66,     67,      68,     69,      NO_LED, 70,     NO_LED, }, /* R4 */
		{ 71,     72,     73,     NO_LED, NO_LED, NO_LED, 74,     NO_LED, NO_LED, NO_LED,  75,      76,     77,      NO_LED, 78,     79,     }, /* R5 */
    }, {
        {0,  0},  {29,  0},  {44,  0}, {59,  0}, {73,  0}, {95,  0}, {110,  0}, {125,  0}, {140,  0}, {161,  0}, {176,  0}, {191,  0}, {206,  0}, {224,  0},
	{0, 17},  {15, 17},  {29, 17}, {44, 17}, {59, 17}, {73, 17}, {88, 17}, {102, 17}, {117, 17}, {132, 17}, {147, 17}, {161, 17}, {176, 17}, {198, 17}, {224, 17},
	{4, 29},  {22, 29},  {37, 29}, {51, 29}, {66, 29}, {81, 29}, {95, 29}, {110, 29}, {125, 29}, {140, 29}, {154, 29}, {169, 29}, {184, 29}, {202, 29}, {224, 29},
	{5, 41},  {26, 41},  {40, 41}, {55, 41}, {70, 41}, {84, 41}, {99, 41}, {114, 41}, {129, 41}, {143, 41}, {158, 41}, {172, 41}, {196, 41}, {224, 41},
	{9, 52},  {33, 52},  {48, 52}, {62, 52}, {77, 52}, {92, 52}, {106, 52}, {121, 52}, {136, 52}, {150, 52}, {165, 52}, {185, 52}, {209, 52},
	{2, 64},  {20, 64},  {38, 64}, {94, 64}, {150, 64}, {172, 64}, {195, 64}, {209, 64}, {224, 64},
	{0, 0},  {45, 0},  {90, 0}, {134, 0}, {179, 0}, {224, 0},
	{0, 32}, {224,32},
	{0, 64},  {45, 64},  {90, 64}, {134, 64}, {179, 64}, {224, 64},
	}, {
    4,1,1,1,1,1,1,1,1,1,1,1,1,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,1,
	4,4,4,4,4,4,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	}
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(44, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
