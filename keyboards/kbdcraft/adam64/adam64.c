/* 
 * Copyright 2023 KBDCraft
 * Copyright 2023 Adophoxia <andyao1528@gmail.com>
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
 *   |  |     G location
 *   |  |     |     B location
 *   |  |     |     | */
    {0, SW1_CS14, SW1_CS13, SW1_CS15},
    {0, SW2_CS14, SW2_CS13, SW2_CS15},
    {0, SW3_CS14, SW3_CS13, SW3_CS15},
    {0, SW4_CS14, SW4_CS13, SW4_CS15},
    {0, SW5_CS14, SW5_CS13, SW5_CS15},
    {0, SW6_CS14, SW6_CS13, SW6_CS15},
    {0, SW7_CS14, SW7_CS13, SW7_CS15},
    {0, SW1_CS32, SW1_CS31, SW1_CS33},
    {0, SW2_CS32, SW2_CS31, SW2_CS33},
    {0, SW3_CS32, SW3_CS31, SW3_CS33},
    {0, SW4_CS32, SW4_CS31, SW4_CS33},
    {0, SW5_CS32, SW5_CS31, SW5_CS33},
    {0, SW6_CS32, SW6_CS31, SW6_CS33},
    {0, SW7_CS32, SW7_CS31, SW7_CS33},

    {0, SW1_CS23, SW1_CS24, SW1_CS22},
    {0, SW2_CS23, SW2_CS24, SW2_CS22},
    {0, SW3_CS23, SW3_CS24, SW3_CS22},
    {0, SW4_CS23, SW4_CS24, SW4_CS22},
    {0, SW5_CS23, SW5_CS24, SW5_CS22},
    {0, SW6_CS23, SW6_CS24, SW6_CS22},
    {0, SW7_CS23, SW7_CS24, SW7_CS22},
    {0, SW1_CS35, SW1_CS34, SW1_CS36},
    {0, SW2_CS35, SW2_CS34, SW2_CS36},
    {0, SW3_CS35, SW3_CS34, SW3_CS36},
    {0, SW4_CS35, SW4_CS34, SW4_CS36},
    {0, SW5_CS35, SW5_CS34, SW5_CS36},
    {0, SW6_CS35, SW6_CS34, SW6_CS36},
    {0, SW7_CS35, SW7_CS34, SW7_CS36},

    {0, SW1_CS17, SW1_CS16, SW1_CS18},
    {0, SW2_CS17, SW2_CS16, SW2_CS18},
    {0, SW3_CS17, SW3_CS16, SW3_CS18},
    {0, SW4_CS17, SW4_CS16, SW4_CS18},
    {0, SW5_CS17, SW5_CS16, SW5_CS18},
    {0, SW6_CS17, SW6_CS16, SW6_CS18},
    {0, SW7_CS17, SW7_CS16, SW7_CS18},
    {0, SW1_CS26, SW1_CS25, SW1_CS27},
    {0, SW2_CS26, SW2_CS25, SW2_CS27},
    {0, SW3_CS26, SW3_CS25, SW3_CS27},
    {0, SW4_CS26, SW4_CS25, SW4_CS27},
    {0, SW5_CS26, SW5_CS25, SW5_CS27},
    {0, SW7_CS26, SW7_CS25, SW7_CS27},

    {0, SW1_CS20, SW1_CS19, SW1_CS21},
    {0, SW2_CS20, SW2_CS19, SW2_CS21},
    {0, SW3_CS20, SW3_CS19, SW3_CS21},
    {0, SW4_CS20, SW4_CS19, SW4_CS21},
    {0, SW5_CS20, SW5_CS19, SW5_CS21},
    {0, SW6_CS20, SW6_CS19, SW6_CS21},
    {0, SW7_CS20, SW7_CS19, SW7_CS21},
    {0, SW1_CS29, SW1_CS28, SW1_CS30},
    {0, SW2_CS29, SW2_CS28, SW2_CS30},
    {0, SW3_CS29, SW3_CS28, SW3_CS30},
    {0, SW4_CS29, SW4_CS28, SW4_CS30},
    {0, SW5_CS29, SW5_CS28, SW5_CS30},
    {0, SW6_CS29, SW6_CS28, SW6_CS30},
    {0, SW7_CS29, SW7_CS28, SW7_CS30},

    {0, SW1_CS9, SW1_CS10, SW1_CS8},
    {0, SW2_CS9, SW2_CS10, SW2_CS8},
    {0, SW3_CS9, SW3_CS10, SW3_CS8},
    {0, SW6_CS9, SW6_CS10, SW6_CS8},
    {0, SW3_CS2, SW3_CS1, SW3_CS3},
    {0, SW4_CS2, SW4_CS1, SW4_CS3},
    {0, SW5_CS2, SW5_CS1, SW5_CS3},
    {0, SW6_CS2, SW6_CS1, SW6_CS3},
    {0, SW7_CS2, SW7_CS1, SW7_CS3}
};
#endif
