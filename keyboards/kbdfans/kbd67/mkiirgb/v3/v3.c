/* Copyright 2021 DZTECH <moyi4681@live.cn>
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

#include "v3.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    {0, CS21_SW1, CS20_SW1, CS19_SW1},
    {0, CS21_SW2, CS20_SW2, CS19_SW2},
    {0, CS21_SW3, CS20_SW3, CS19_SW3},
    {0, CS21_SW4, CS20_SW4, CS19_SW4},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},
    {0, CS21_SW6, CS20_SW6, CS19_SW6},
    {0, CS21_SW7, CS20_SW7, CS19_SW7},
    {0, CS21_SW8, CS20_SW8, CS19_SW8},
    {0, CS24_SW1, CS23_SW1, CS22_SW1},
    {0, CS24_SW2, CS23_SW2, CS22_SW2},
    {0, CS24_SW3, CS23_SW3, CS22_SW3},
    {0, CS24_SW4, CS23_SW4, CS22_SW4},
    {0, CS24_SW5, CS23_SW5, CS22_SW5},
    {0, CS24_SW6, CS23_SW6, CS22_SW6},
    {0, CS24_SW7, CS23_SW7, CS22_SW7},

    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW2, CS14_SW2, CS13_SW2},
    {0, CS15_SW3, CS14_SW3, CS13_SW3},
    {0, CS15_SW4, CS14_SW4, CS13_SW4},
    {0, CS15_SW5, CS14_SW5, CS13_SW5},
    {0, CS15_SW6, CS14_SW6, CS13_SW6},
    {0, CS15_SW7, CS14_SW7, CS13_SW7},
    {0, CS15_SW8, CS14_SW8, CS13_SW8},
    {0, CS30_SW1, CS29_SW1, CS28_SW1},
    {0, CS30_SW2, CS29_SW2, CS28_SW2},
    {0, CS30_SW3, CS29_SW3, CS28_SW3},
    {0, CS30_SW4, CS29_SW4, CS28_SW4},
    {0, CS30_SW5, CS29_SW5, CS28_SW5},
    {0, CS30_SW6, CS29_SW6, CS28_SW6},
    {0, CS30_SW7, CS29_SW7, CS28_SW7},

    {0, CS12_SW1, CS11_SW1, CS10_SW1},
    {0, CS12_SW2, CS11_SW2, CS10_SW2},
    {0, CS12_SW3, CS11_SW3, CS10_SW3},
    {0, CS12_SW4, CS11_SW4, CS10_SW4},
    {0, CS12_SW5, CS11_SW5, CS10_SW5},
    {0, CS12_SW6, CS11_SW6, CS10_SW6},
    {0, CS12_SW7, CS11_SW7, CS10_SW7},
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS33_SW1, CS32_SW1, CS31_SW1},
    {0, CS33_SW2, CS32_SW2, CS31_SW2},
    {0, CS33_SW3, CS32_SW3, CS31_SW3},
    {0, CS33_SW4, CS32_SW4, CS31_SW4},
    {0, CS33_SW5, CS32_SW5, CS31_SW5},
    {0, CS33_SW7, CS32_SW7, CS31_SW7},

    {0, CS9_SW1, CS8_SW1, CS7_SW1},
    {0, CS9_SW2, CS8_SW2, CS7_SW2},
    {0, CS9_SW3, CS8_SW3, CS7_SW3},
    {0, CS9_SW4, CS8_SW4, CS7_SW4},
    {0, CS9_SW5, CS8_SW5, CS7_SW5},
    {0, CS9_SW6, CS8_SW6, CS7_SW6},
    {0, CS9_SW7, CS8_SW7, CS7_SW7},
    {0, CS9_SW8, CS8_SW8, CS7_SW8},
    {0, CS36_SW1, CS35_SW1, CS34_SW1},
    {0, CS36_SW2, CS35_SW2, CS34_SW2},
    {0, CS36_SW3, CS35_SW3, CS34_SW3},
    {0, CS36_SW4, CS35_SW4, CS34_SW4},
    {0, CS36_SW5, CS35_SW5, CS34_SW5},
    {0, CS36_SW7, CS35_SW7, CS34_SW7},

    {0, CS3_SW1, CS2_SW1, CS1_SW1},
    {0, CS3_SW2, CS2_SW2, CS1_SW2},
    {0, CS3_SW3, CS2_SW3, CS1_SW3},
    {0, CS3_SW6, CS2_SW6, CS1_SW6},
//    {0, CS39_SW1, CS38_SW1, CS37_SW1},
    {0, CS39_SW2, CS38_SW2, CS37_SW2},
    {0, CS39_SW3, CS38_SW3, CS37_SW3},
    {0, CS39_SW4, CS38_SW4, CS37_SW4},
    {0, CS39_SW5, CS38_SW5, CS37_SW5},
    {0, CS39_SW7, CS38_SW7, CS37_SW7}

};
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14 },
    {  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
    {  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, NO_LED, 42, 43 },
    {  44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, NO_LED, 56, 57 },
    {  58, 59, 60, NO_LED, NO_LED, 61, NO_LED, NO_LED, 62, NO_LED, 63, 64, NO_LED, 65, 66 }
}, {
    // LED Index to Physical Position
    {6,10},{20,10},{34,10},{48,10},{62,10},{76,10},{90,10},{104,10},{118,10},{132,10},{146,10},{160,10},{174,10}, {196,10},{217,10},
	{9,23}, {27,23},{41,23},{55,23},{69,23},{83,23},{97,23},{111,23},{125,23},{139,23},{153,23},{167,23},{181,23}, {199,23},{217,23},
	{11,36},{30,36},{44,36},{58,36},{72,36},{86,36},{101,36},{115,36},{129,36},{143,36},{157,36},{171,36}, {194,36},{217,36},
	{15,49}, {38,49},{52,49},{66,49},{80,49},{94,49},{108,49},{122,49},{136,49},{150,49},{164,49}, {184,49},{203,49},{217,49},
    {8,62},{25,62},{43,62}, {95,62}, {149,62},{166,62}, {189,62},{203,62},{217,62}

}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1
} };


__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock)     {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
}
#endif
