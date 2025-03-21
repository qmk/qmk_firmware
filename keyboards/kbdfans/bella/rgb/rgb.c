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
#include "quantum.h"
#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS18, SW1_CS17, SW1_CS16},    /* RGB6 */
    {0, SW3_CS18, SW3_CS17, SW3_CS16},    /* RGB32 */
    {0, SW4_CS18, SW4_CS17, SW4_CS16},    /* RGB45 */
    {0, SW5_CS18, SW5_CS17, SW5_CS16},    /* RGB58 */
    {0, SW6_CS18, SW6_CS17, SW6_CS16},    /* RGB71 */
    {0, SW7_CS18, SW7_CS17, SW7_CS16},    /* RGB84 */
    {0, SW8_CS18, SW8_CS17, SW8_CS16},    /* RGB97 */
    {0, SW1_CS21, SW1_CS20, SW1_CS19},    /* RGB7 */
    {0, SW2_CS21, SW2_CS20, SW2_CS19},    /* RGB20 */
    {0, SW3_CS21, SW3_CS20, SW3_CS19},    /* RGB33 */
    {0, SW4_CS21, SW4_CS20, SW4_CS19},    /* RGB46 */
    {0, SW5_CS21, SW5_CS20, SW5_CS19},    /* RGB59 */
    {0, SW6_CS21, SW6_CS20, SW6_CS19},    /* RGB72 */
    {0, SW7_CS21, SW7_CS20, SW7_CS19},    /* RGB85 */

    {0, SW1_CS15, SW1_CS14, SW1_CS13},    /* RGB5 */
    {0, SW2_CS15, SW2_CS14, SW2_CS13},    /* RGB18 */
    {0, SW3_CS15, SW3_CS14, SW3_CS13},    /* RGB31 */
    {0, SW4_CS15, SW4_CS14, SW4_CS13},    /* RGB44 */
    {0, SW5_CS15, SW5_CS14, SW5_CS13},    /* RGB57 */
    {0, SW6_CS15, SW6_CS14, SW6_CS13},    /* RGB70 */
    {0, SW7_CS15, SW7_CS14, SW7_CS13},    /* RGB83 */
    {0, SW8_CS15, SW8_CS14, SW8_CS13},    /* RGB96 */
    {0, SW1_CS24, SW1_CS23, SW1_CS22},    /* RGB8 */
    {0, SW2_CS24, SW2_CS23, SW2_CS22},    /* RGB21 */
    {0, SW3_CS24, SW3_CS23, SW3_CS22},    /* RGB34 */
    {0, SW4_CS24, SW4_CS23, SW4_CS22},    /* RGB47 */
    {0, SW5_CS24, SW5_CS23, SW5_CS22},    /* RGB60 */
    {0, SW6_CS24, SW6_CS23, SW6_CS22},    /* RGB73 */
    {0, SW7_CS24, SW7_CS23, SW7_CS22},    /* RGB86 */

    {0, SW1_CS12, SW1_CS11, SW1_CS10},    /* RGB4 */
    {0, SW2_CS12, SW2_CS11, SW2_CS10},    /* RGB17 */
    {0, SW3_CS12, SW3_CS11, SW3_CS10},    /* RGB30 */
    {0, SW4_CS12, SW4_CS11, SW4_CS10},    /* RGB43 */
    {0, SW5_CS12, SW5_CS11, SW5_CS10},    /* RGB56 */
    {0, SW6_CS12, SW6_CS11, SW6_CS10},    /* RGB69 */
    {0, SW7_CS12, SW7_CS11, SW7_CS10},    /* RGB82 */
    {0, SW8_CS12, SW8_CS11, SW8_CS10},    /* RGB95 */
    {0, SW1_CS27, SW1_CS26, SW1_CS25},    /* RGB9 */
    {0, SW2_CS27, SW2_CS26, SW2_CS25},    /* RGB22 */
    {0, SW3_CS27, SW3_CS26, SW3_CS25},    /* RGB35 */
    {0, SW4_CS27, SW4_CS26, SW4_CS25},    /* RGB48 */
    {0, SW5_CS27, SW5_CS26, SW5_CS25},    /* RGB61 */
    {0, SW6_CS27, SW6_CS26, SW6_CS25},    /* RGB74 */
    {0, SW7_CS27, SW7_CS26, SW7_CS25},    /* RGB87 */

    {0, SW1_CS9, SW1_CS8, SW1_CS7},    /* RGB3 */
    {0, SW2_CS9, SW2_CS8, SW2_CS7},    /* RGB16 */
    {0, SW3_CS9, SW3_CS8, SW3_CS7},    /* RGB29*/
    {0, SW4_CS9, SW4_CS8, SW4_CS7},    /* RGB42 */
    {0, SW5_CS9, SW5_CS8, SW5_CS7},    /* RGB55 */
    {0, SW6_CS9, SW6_CS8, SW6_CS7},    /* RGB68 */
    {0, SW7_CS9, SW7_CS8, SW7_CS7},    /* RGB81 */
    {0, SW8_CS9, SW8_CS8, SW8_CS7},    /* RGB94 */
    {0, SW1_CS30, SW1_CS29, SW1_CS28},    /* RGB10 */
    {0, SW2_CS30, SW2_CS29, SW2_CS28},    /* RGB23 */
    {0, SW3_CS30, SW3_CS29, SW3_CS28},    /* RGB36 */
    {0, SW4_CS30, SW4_CS29, SW4_CS28},    /* RGB49 */
    {0, SW5_CS30, SW5_CS29, SW5_CS28},    /* RGB62 */
    {0, SW7_CS30, SW7_CS29, SW7_CS28},    /* RGB88 */

    {0, SW1_CS6, SW1_CS5, SW1_CS4},    /* RGB2 */
    {0, SW3_CS6, SW3_CS5, SW3_CS4},    /* RGB28 */
    {0, SW4_CS6, SW4_CS5, SW4_CS4},    /* RGB41 */
    {0, SW5_CS6, SW5_CS5, SW5_CS4},    /* RGB54 */
    {0, SW6_CS6, SW6_CS5, SW6_CS4},    /* RGB67 */
    {0, SW7_CS6, SW7_CS5, SW7_CS4},    /* RGB80 */
    {0, SW8_CS6, SW8_CS5, SW8_CS4},    /* RGB93 */
    {0, SW1_CS33, SW1_CS32, SW1_CS31},    /* RGB11 */
    {0, SW2_CS33, SW2_CS32, SW2_CS31},    /* RGB24 */
    {0, SW3_CS33, SW3_CS32, SW3_CS31},    /* RGB37 */
    {0, SW4_CS33, SW4_CS32, SW4_CS31},    /* RGB50 */
    {0, SW5_CS33, SW5_CS32, SW5_CS31},    /* RGB63 */
    {0, SW6_CS33, SW6_CS32, SW6_CS31},    /* RGB76 */

    {0, SW1_CS3, SW1_CS2, SW1_CS1},    /* RGB1 */
    {0, SW2_CS3, SW2_CS2, SW2_CS1},    /* RGB14 */
    {0, SW3_CS3, SW3_CS2, SW3_CS1},    /* RGB27 */
    {0, SW8_CS36, SW8_CS35, SW8_CS34},    /* RGB103 */
    {0, SW3_CS36, SW3_CS35, SW3_CS34},    /* RGB38 */
    {0, SW4_CS36, SW4_CS35, SW4_CS34},    /* RGB51 */
    {0, SW5_CS36, SW5_CS35, SW5_CS34},    /* RGB64 */
    {0, SW6_CS36, SW6_CS35, SW6_CS34},    /* RGB77 */
    {0, SW7_CS36, SW7_CS35, SW7_CS34},    /* RGB90 */

    {0, SW9_CS18, SW9_CS17, SW9_CS16},    /* RGB110 */
    {0, SW2_CS18, SW2_CS17, SW2_CS16},    /* RGB19 */
    {0, SW9_CS12, SW9_CS11, SW9_CS10},    /* RGB108 */
    {0, SW8_CS21, SW8_CS20, SW8_CS19},    /* RGB98 */
    {0, SW9_CS24, SW9_CS23, SW9_CS22},    /* RGB112 */
    {0, SW8_CS24, SW8_CS23, SW8_CS22},    /* RGB99 */
    {0, SW9_CS9, SW9_CS8, SW9_CS7},    /* RGB107 */
    {0, SW8_CS27, SW8_CS26, SW8_CS25},    /* RGB100 */
    {0, SW7_CS33, SW7_CS32, SW7_CS31},    /* RGB89 */
    {0, SW9_CS33, SW9_CS32, SW9_CS31},    /* RGB115 */
    {0, SW9_CS36, SW9_CS35, SW9_CS34},    /* RGB116 */
    {0, SW2_CS36, SW2_CS35, SW2_CS34},    /* RGB25 */
    {0, SW9_CS3, SW9_CS2, SW9_CS1},    /* RGB105 */
    {0, SW4_CS3, SW4_CS2, SW4_CS1},    /* RGB40 */
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
