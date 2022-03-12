/* Copyright 2022
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

#include "kuro_pad_eval.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |        G location
 *   |     |        |        B location
 *   |     |        |        | */
    {0, CS1_SW3, CS5_SW3, CS3_SW3},    // idx 0
    {0, CS1_SW5, CS5_SW5, CS3_SW5},    // idx 1
    {0, CS1_SW7, CS5_SW7, CS3_SW7},    // idx 2
    {0, CS1_SW9, CS5_SW9, CS3_SW9},    // idx 3

    {0, CS6_SW3, CS10_SW3, CS8_SW3},   // idx 4
    {0, CS6_SW5, CS10_SW5, CS8_SW5},   // idx 5
    {0, CS6_SW7, CS10_SW7, CS8_SW7},   // idx 6
    {0, CS6_SW9, CS10_SW9, CS8_SW9},   // idx 7

    {0, CS11_SW3, CS15_SW3, CS13_SW3}, // idx 8
    {0, CS11_SW5, CS15_SW5, CS13_SW5}, // idx 9
    {0, CS11_SW7, CS15_SW7, CS13_SW7}, // idx 10

    {0, CS17_SW3, CS20_SW3, CS19_SW3}, // idx 11
    {0, CS17_SW5, CS20_SW5, CS19_SW5}, // idx 12
    {0, CS17_SW7, CS20_SW7, CS19_SW7}, // idx 13
    {0, CS17_SW9, CS20_SW9, CS19_SW9}, // idx 14

    {0, CS22_SW5, CS26_SW5, CS24_SW5}, // idx 15
    {0, CS22_SW7, CS26_SW7, CS24_SW7}  // idx 16

};

led_config_t g_led_config = { {
    // Key Matrix (5x5) to LED Index
    { NO_LED,      0,      1,      2,      3 },
    { NO_LED,      4,      5,      6,      7 },
    { NO_LED,      8,      9,     10, NO_LED },
    { NO_LED,     11,     12,     13,     14 },
    { NO_LED, NO_LED,     15,     16, NO_LED }
}, {
    // LED Index to Physical Position
    {  0,  0},{ 75,  0},{149,  0},{224,  0},
    {  0, 16},{ 75, 16},{149, 16},{224, 24},
    {  0, 32},{ 75, 32},{149, 32},
    {  0, 48},{ 75, 48},{149, 48},{224, 56},
              { 37, 64},{149, 64}
}, {
    // LED Index to Flag
    1, 1, 1, 1,
    4, 4, 4, 1,
    4, 4, 4,
    4, 4, 4, 1,
       4, 1
} };


__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
}
#endif
