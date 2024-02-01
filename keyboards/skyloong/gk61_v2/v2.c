/* Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
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

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    {0, CS1_SW1, CS2_SW1, CS3_SW1},
    {0, CS1_SW2, CS2_SW2, CS3_SW2},
    {0, CS1_SW3, CS2_SW3, CS3_SW3},
    {0, CS1_SW4, CS2_SW4, CS3_SW4},
    {0, CS1_SW5, CS2_SW5, CS3_SW5},
    {0, CS1_SW6, CS2_SW6, CS3_SW6},
    {0, CS1_SW7, CS2_SW7, CS3_SW7},
    {0, CS1_SW8, CS2_SW8, CS3_SW8},
    {0, CS1_SW9, CS2_SW9, CS3_SW9},
    {0, CS1_SW10, CS2_SW10, CS3_SW10},
    {0, CS1_SW11, CS2_SW11, CS3_SW11},
    {0, CS16_SW1, CS17_SW1, CS18_SW1},
    {0, CS16_SW2, CS17_SW2, CS18_SW2},
    {0, CS16_SW3, CS17_SW3, CS18_SW3},

    {0, CS4_SW1, CS5_SW1, CS6_SW1},
    {0, CS4_SW2, CS5_SW2, CS6_SW2},
    {0, CS4_SW3, CS5_SW3, CS6_SW3},
    {0, CS4_SW4, CS5_SW4, CS6_SW4},
    {0, CS4_SW5, CS5_SW5, CS6_SW5},
    {0, CS4_SW6, CS5_SW6, CS6_SW6},
    {0, CS4_SW7, CS5_SW7, CS6_SW7},
    {0, CS4_SW8, CS5_SW8, CS6_SW8},
    {0, CS4_SW9, CS5_SW9, CS6_SW9},
    {0, CS4_SW10, CS5_SW10, CS6_SW10},
    {0, CS4_SW11, CS5_SW11, CS6_SW11},
    {0, CS16_SW4, CS17_SW4, CS18_SW4},
    {0, CS16_SW5, CS17_SW5, CS18_SW5},
    {0, CS16_SW6, CS17_SW6, CS18_SW6},

    {0, CS7_SW1, CS8_SW1, CS9_SW1},
    {0, CS7_SW2, CS8_SW2, CS9_SW2},
    {0, CS7_SW3, CS8_SW3, CS9_SW3},
    {0, CS7_SW4, CS8_SW4, CS9_SW4},
    {0, CS7_SW5, CS8_SW5, CS9_SW5},
    {0, CS7_SW6, CS8_SW6, CS9_SW6},
    {0, CS7_SW7, CS8_SW7, CS9_SW7},
    {0, CS7_SW8, CS8_SW8, CS9_SW8},
    {0, CS7_SW9, CS8_SW9, CS9_SW9},
    {0, CS7_SW10, CS8_SW10, CS9_SW10},
    {0, CS7_SW11, CS8_SW11, CS9_SW11},
    {0, CS16_SW7, CS17_SW7, CS18_SW7},
    {0, CS16_SW8, CS17_SW8, CS18_SW8},

    {0, CS10_SW1, CS11_SW1, CS12_SW1},
    {0, CS10_SW2, CS11_SW2, CS12_SW2},
    {0, CS10_SW3, CS11_SW3, CS12_SW3},
    {0, CS10_SW4, CS11_SW4, CS12_SW4},
    {0, CS10_SW5, CS11_SW5, CS12_SW5},
    {0, CS10_SW6, CS11_SW6, CS12_SW6},
    {0, CS10_SW7, CS11_SW7, CS12_SW7},
    {0, CS10_SW8, CS11_SW8, CS12_SW8},
    {0, CS10_SW9, CS11_SW9, CS12_SW9},
    {0, CS10_SW10, CS11_SW10, CS12_SW10},
    {0, CS10_SW11, CS11_SW11, CS12_SW11},
    {0, CS16_SW9, CS17_SW9, CS18_SW9},

    {0, CS13_SW1, CS14_SW1, CS15_SW1},
    {0, CS13_SW2, CS14_SW2, CS15_SW2},
    {0, CS13_SW3, CS14_SW3, CS15_SW3},
    {0, CS13_SW4, CS14_SW4, CS15_SW4},
    {0, CS13_SW5, CS14_SW5, CS15_SW5},
    {0, CS13_SW6, CS14_SW6, CS15_SW6},
    {0, CS13_SW7, CS14_SW7, CS15_SW7},
    {0, CS13_SW8, CS14_SW8, CS15_SW8},
    {0, CS13_SW9, CS14_SW9, CS15_SW9},
    {0, CS13_SW10, CS14_SW10, CS15_SW10},
};

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;

};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 255, 255, 255); // assuming caps lock is at led #28
    }
    return false;
}
