/* 
Copyright 2023 NEO

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ansi.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS2_SW1,  CS3_SW1,  CS1_SW1},  /* RGB0-ESC ROW1*/
    {0, CS5_SW1,  CS6_SW1,  CS4_SW1},  /* RGB1-1 */
    {0, CS8_SW1,  CS9_SW1,  CS7_SW1},  /* RGB2-2 */
    {0, CS11_SW1,  CS12_SW1,  CS10_SW1},  /* RGB3-3 */
    {0, CS14_SW1,  CS15_SW1,  CS13_SW1},  /* RGB4-4 */
    {0, CS17_SW1,  CS18_SW1,  CS16_SW1},  /* RGB5-5 */
    {0, CS20_SW1,  CS21_SW1,  CS19_SW1},  /* RGB6-6 */
    {0, CS23_SW1,  CS24_SW1,  CS22_SW1},  /* RGB7-7 */
    {0, CS26_SW1,  CS27_SW1,  CS25_SW1},  /* RGB8-8 */
    {0, CS29_SW1,  CS30_SW1,  CS28_SW1},  /* RGB9-9 */
    {0, CS32_SW1,  CS33_SW1,  CS31_SW1},  /* RGB10-0 */
    {0, CS35_SW1,  CS36_SW1,  CS34_SW1},  /* RGB11--- */
    {0, CS38_SW1,  CS39_SW1,  CS37_SW1},  /* RGB12-+= */
    {0, CS38_SW3,  CS39_SW3,  CS37_SW3},  /* RGB13-|\ */
    {0, CS38_SW6,  CS39_SW6,  CS37_SW6},   /* RGB14-BS */ 
    {0, CS35_SW6,  CS36_SW6,  CS34_SW6},  /* RGB15-Delete */

    {0, CS2_SW2,  CS3_SW2,  CS1_SW2},  /* RGB16-TAB ----ROW2*/
    {0, CS5_SW2,  CS6_SW2,  CS4_SW2},  /* RGB17-Q */
    {0, CS8_SW2,  CS9_SW2,  CS7_SW2},  /* RGB18-W */
    {0, CS11_SW2,  CS12_SW2,  CS10_SW2},  /* RGB19-E */
    {0, CS14_SW2,  CS15_SW2,  CS13_SW2},  /* RGB20-R */
    {0, CS17_SW2,  CS18_SW2,  CS16_SW2},  /* RGB21-T */
    {0, CS20_SW2,  CS21_SW2,  CS19_SW2},  /* RGB22-Y */
    {0, CS23_SW2,  CS24_SW2,  CS22_SW2},  /* RGB23-U */
    {0, CS26_SW2,  CS27_SW2,  CS25_SW2},  /* RGB24-I */
    {0, CS29_SW2,  CS30_SW2,  CS28_SW2},  /* RGB25-O */
    {0, CS32_SW2,  CS33_SW2,  CS31_SW2},  /* RGB26-P */
    {0, CS35_SW2,  CS36_SW2,  CS34_SW2},  /* RGB27-[ */
    {0, CS38_SW2,  CS39_SW2,  CS37_SW2},  /* RGB28-] */
    {0, CS38_SW7,  CS39_SW7,  CS37_SW7},  /* RGB29-\ */
    {0, CS35_SW7,  CS36_SW7,  CS34_SW7},  /* RGB30-PgUp */

    {0, CS2_SW3,  CS3_SW3,  CS1_SW3},  /* RGB31-CAPS---ROW3*/
    {0, CS5_SW3,  CS6_SW3,  CS4_SW3},  /* RGB32-A-- */
    {0, CS8_SW3,  CS9_SW3,  CS7_SW3},  /* RGB33-S-- */
    {0, CS11_SW3,  CS12_SW3,  CS10_SW3}, /* RGB34-D */
    {0, CS14_SW3,  CS15_SW3,  CS13_SW3}, /* RGB35-F */
    {0, CS17_SW3,  CS18_SW3,  CS16_SW3}, /* RGB36-G */
    {0, CS20_SW3,  CS21_SW3,  CS19_SW3}, /* RGB37-H */
    {0, CS23_SW3,  CS24_SW3,  CS22_SW3}, /* RGB38-J */
    {0, CS26_SW3,  CS27_SW3,  CS25_SW3}, /* RGB39-K */
    {0, CS29_SW3,  CS30_SW3,  CS28_SW3}, /* RGB40-L */
    {0, CS32_SW3,  CS33_SW3,  CS31_SW3}, /* RGB41-;: */
    {0, CS35_SW3,  CS36_SW3,  CS34_SW3}, /* RGB42-'" */
    {0, CS38_SW8,  CS39_SW8,  CS37_SW8}, /* RGB43-ENTER */
    {0, CS35_SW8,  CS36_SW8,  CS34_SW8}, /* RGB44-Page Down */
    

    {0, CS2_SW4,  CS3_SW4,  CS1_SW4},    /* RGB45-LSF --ROW4*/
    {0, CS5_SW4,  CS6_SW4,  CS4_SW4},    /* RGB46-Z */
    {0, CS8_SW4,  CS9_SW4,  CS7_SW4},    /* RGB47-X */
    {0, CS11_SW4,  CS12_SW4,  CS10_SW4}, /* RGB48-C */ 
    {0, CS14_SW4,  CS15_SW4,  CS13_SW4},  /* RGB49-V */
    {0, CS17_SW4,  CS18_SW4,  CS16_SW4},  /* RGB50-B */
    {0, CS20_SW4,  CS21_SW4,  CS19_SW4},  /* RGB51-N */
    {0, CS23_SW4,  CS24_SW4,  CS22_SW4},  /* RGB52-M */
    {0, CS26_SW4,  CS27_SW4,  CS25_SW4},  /* RGB53-,< */
    {0, CS29_SW4,  CS30_SW4,  CS28_SW4},  /* RGB54->. */
    {0, CS32_SW4,  CS33_SW4,  CS31_SW4},  /* RGB55-?/ */
    {0, CS35_SW4,  CS36_SW4,  CS34_SW4},  /* RGB56-RSF */
    {0, CS38_SW9,  CS39_SW9,  CS37_SW9},  /* RGB57-UP */
    {0, CS35_SW9,  CS36_SW9,  CS34_SW9},  /* RGB58-End */

    {0, CS2_SW5,  CS3_SW5,  CS1_SW5},  /* RGB59-lct-- ROW5*/
    {0, CS5_SW5,  CS6_SW5,  CS4_SW5},  /* RGB60-lwin */
    {0, CS8_SW5,  CS9_SW5,  CS7_SW5},  /* RGB61-lalt */
    {0, CS17_SW5,  CS18_SW5,  CS16_SW5},  /* RGB62-sp */
    {0, CS29_SW5,  CS30_SW5,  CS28_SW5},  /* RGB63-ralt */
    {0, CS32_SW5,  CS33_SW5,  CS31_SW5},  /* RGB64- fn */
    {0, CS38_SW4,  CS39_SW4,  CS37_SW4},  /* RGB65-left */
    {0, CS38_SW5,  CS39_SW5,  CS37_SW5},  /* RGB66-down */
    {0, CS35_SW5,  CS36_SW5,  CS34_SW5}  /* RGB67-right */
};

led_config_t g_led_config = { {
    { 0,   1,   2,   3,      4,      5,   6,      7,      8,      9,   10,  11,     12,   14,   15 },    
	{ 16,  17,  18,  19,     20,     21,  22,     23,     24,     25,  26,  27,     28,   29,   30 },    
	{ 31,  32,  33,  34,     35,     36,  37,     38,     39,     40,  41,  42,     43,   13,   44 }, 
	{ 45,  46,  47,  48,     49,     50,  51,     52,     53,     54,  55,  NO_LED, 56,   57,   58 },    
	{ 59,  60,  61,  NO_LED, NO_LED, 62,  NO_LED, NO_LED, NO_LED, 63,  64,  NO_LED, 65,   66,   67 }
}, {
    // LED Index to Physical Position
    { 0, 0 },  { 15, 0 },  { 30, 0 },  { 45, 0 },  { 60, 0 },  { 75, 0 },  { 90, 0 },  { 105, 0 },  { 120, 0 }, { 135, 0 },  { 150, 0 },  { 165, 0 },  { 180, 0 },  { 195, 0 },  { 210, 0 },  { 224, 0 }, 
    { 4, 16},  { 22, 16},  { 37, 16},  { 52, 16},  { 67, 16},  { 82, 16},  { 97, 16},  { 112, 16 }, { 127, 16}, {142, 16},   {157, 16 },  { 172, 16},  { 187, 16},  { 206, 16},               { 224, 16}, 
    { 6, 32},  { 26, 32},  { 41, 32},  { 56, 32},  { 71, 32},  { 86, 32},  {101, 32},  { 116, 32},  { 131, 32}, {146, 32},   { 161, 32},  { 176, 32},  { 201, 32},                            { 224, 32},
    { 8, 48},              { 31, 48},  { 46, 48},  { 61, 48},  { 76, 48},  { 91, 48},  { 106, 48},  { 121, 48}, { 136, 48},  { 151, 48},  { 166, 48},  { 183, 48},  { 210, 48},               { 224, 48}, 
    { 2, 64},  { 21, 64},  { 39, 64},                                      { 91, 64},                                                     { 145, 64},  {163, 64},   { 195, 64},  { 210, 64 }, { 224, 64}
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,       1, 
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
    1, 1, 1,       4,          1, 1,       1, 1, 1
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


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF);
    }

    return true;
}

#endif