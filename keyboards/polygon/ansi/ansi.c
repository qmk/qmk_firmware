/* Copyright 2024 Your Name (@rotwitt)
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
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |           G location
     *   |  |           |           B location
     *   |  |           |           |
     * ROW 1*/
    {0, SW9_CS1, SW9_CS2, SW9_CS3},    // RGB 1
    {0, SW9_CS4, SW9_CS5, SW9_CS6},    // RGB 2
    {0, SW9_CS7, SW9_CS8, SW9_CS9},    // RGB 3
    {0, SW8_CS10, SW8_CS11, SW8_CS12}, // RGB 4
    {0, SW9_CS10, SW9_CS11, SW9_CS12}, // RGB 5
    {0, SW8_CS13, SW8_CS14, SW8_CS15}, // RGB 6
    {0, SW9_CS13, SW9_CS14, SW9_CS15}, // RGB 7
    {0, SW8_CS16, SW8_CS17, SW8_CS18}, // RGB 8
    {0, SW9_CS16, SW9_CS17, SW9_CS18}, // RGB 9
    {0, SW9_CS19, SW9_CS20, SW9_CS21}, // RGB 10
    {0, SW9_CS22, SW9_CS23, SW9_CS24}, // RGB 11
    {0, SW9_CS25, SW9_CS26, SW9_CS27}, // RGB 12
    {0, SW9_CS28, SW9_CS29, SW9_CS30}, // RGB 13
    {0, SW9_CS36, SW9_CS35, SW9_CS34}, // RGB 14

    // ROW 2
    {0, SW7_CS1, SW7_CS2, SW7_CS3},    // RGB 15
    {0, SW7_CS4, SW7_CS5, SW7_CS6},    // RGB 16
    {0, SW7_CS7, SW7_CS8, SW7_CS9},    // RGB 17
    {0, SW6_CS10, SW6_CS11, SW6_CS12}, // RGB 18
    {0, SW7_CS10, SW7_CS11, SW7_CS12}, // RGB 19
    {0, SW6_CS13, SW6_CS14, SW6_CS15}, // RGB 20
    {0, SW7_CS13, SW7_CS14, SW7_CS15}, // RGB 21
    {0, SW6_CS16, SW6_CS17, SW6_CS18}, // RGB 22
    {0, SW7_CS16, SW7_CS17, SW7_CS18}, // RGB 23
    {0, SW7_CS19, SW7_CS20, SW7_CS21}, // RGB 24
    {0, SW7_CS22, SW7_CS23, SW7_CS24}, // RGB 25
    {0, SW7_CS25, SW7_CS26, SW7_CS27}, // RGB 26
    {0, SW7_CS28, SW7_CS29, SW7_CS30}, // RGB 27
    {0, SW7_CS31, SW7_CS32, SW7_CS33}, // RGB 28
    {0, SW7_CS39, SW7_CS38, SW7_CS37}, // RGB 29

    // ROW 3
    {0, SW5_CS1, SW5_CS2, SW5_CS3},    // RGB 30
    {0, SW5_CS4, SW5_CS5, SW5_CS6},    // RGB 31
    {0, SW5_CS7, SW5_CS8, SW5_CS9},    // RGB 32
    {0, SW4_CS10, SW4_CS11, SW4_CS12}, // RGB 33
    {0, SW5_CS10, SW5_CS11, SW5_CS12}, // RGB 34
    {0, SW4_CS13, SW4_CS14, SW4_CS15}, // RGB 35
    {0, SW5_CS13, SW5_CS14, SW5_CS15}, // RGB 36
    {0, SW4_CS16, SW4_CS17, SW4_CS18}, // RGB 37
    {0, SW5_CS16, SW5_CS17, SW5_CS18}, // RGB 38
    {0, SW5_CS19, SW5_CS20, SW5_CS21}, // RGB 39
    {0, SW5_CS22, SW5_CS23, SW5_CS24}, // RGB 40
    {0, SW5_CS25, SW5_CS26, SW5_CS27}, // RGB 41
    {0, SW5_CS36, SW5_CS35, SW5_CS34}, // RGB 42
    {0, SW5_CS39, SW5_CS38, SW5_CS37}, // RGB 43

    // ROW 4
    {0, SW3_CS1, SW3_CS2, SW3_CS3},    // RGB 44
    {0, SW3_CS7, SW3_CS8, SW3_CS9},    // RGB 46 (NOT A MISCOUNT)
    {0, SW2_CS10, SW2_CS11, SW2_CS12}, // RGB 47
    {0, SW3_CS10, SW3_CS11, SW3_CS12}, // RGB 48
    {0, SW2_CS13, SW2_CS14, SW2_CS15}, // RGB 49
    {0, SW3_CS13, SW3_CS14, SW3_CS15}, // RGB 50
    {0, SW2_CS16, SW2_CS17, SW2_CS18}, // RGB 51
    {0, SW3_CS16, SW3_CS17, SW3_CS18}, // RGB 52
    {0, SW3_CS19, SW3_CS20, SW3_CS21}, // RGB 53
    {0, SW3_CS22, SW3_CS23, SW3_CS24}, // RGB 54
    {0, SW3_CS25, SW3_CS26, SW3_CS27}, // RGB 55
    {0, SW3_CS28, SW3_CS29, SW3_CS30}, // RGB 56
    {0, SW3_CS36, SW3_CS35, SW3_CS34}, // RGB 57
    {0, SW3_CS39, SW3_CS38, SW3_CS37}, // RGB 58

    // ROW 5
    {0, SW1_CS1, SW1_CS2, SW1_CS3},    // RGB 59
    {0, SW1_CS4, SW1_CS5, SW1_CS6},    // RGB 60
    {0, SW1_CS7, SW1_CS8, SW1_CS9},    // RGB 61
    {0, SW1_CS13, SW1_CS14, SW1_CS15}, // RGB 63 (NOT A MISCOUNT)
    {0, SW1_CS22, SW1_CS23, SW1_CS24}, // RGB 66 (NOT A MISCOUNT)
    {0, SW1_CS25, SW1_CS26, SW1_CS27}, // RGB 67
    {0, SW1_CS31, SW1_CS32, SW1_CS33}, // RGB 68
    {0, SW1_CS36, SW1_CS35, SW1_CS34}, // RGB 69
    {0, SW1_CS39, SW1_CS38, SW1_CS37}  // RGB 70
};
#endif
