/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 * Modified 2022 by rustedaperture for qmk_firmware
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

const aw20216s_led_t g_aw20216s_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, CS4_SW1,  CS5_SW1,  CS6_SW1  },  //  0  NUM
    {0, CS4_SW2,  CS5_SW2,  CS6_SW2  },  //  1  /
    {0, CS7_SW1,  CS8_SW1,  CS9_SW1  },  //  2  *
    {0, CS7_SW2,  CS8_SW2,  CS9_SW2  },  //  3  -
    {0, CS4_SW3,  CS5_SW3,  CS6_SW3  },  //  4  7
    {0, CS4_SW4,  CS5_SW4,  CS6_SW4  },  //  5  8
    {0, CS7_SW3,  CS8_SW3,  CS9_SW3  },  //  6  9
    {0, CS7_SW4,  CS8_SW4,  CS9_SW4  },  //  7  +
    {0, CS4_SW5,  CS5_SW5,  CS6_SW5  },  //  8  4
    {0, CS4_SW6,  CS5_SW6,  CS6_SW6  },  //  9  5
    {0, CS7_SW5,  CS8_SW5,  CS9_SW5  },  //  10 6
    {0, CS4_SW7,  CS5_SW7,  CS6_SW7  },  //  11 1
    {0, CS4_SW8,  CS5_SW8,  CS6_SW8  },  //  12 2
    {0, CS7_SW7,  CS8_SW7,  CS9_SW7  },  //  13 3
    {0, CS7_SW8,  CS8_SW8,  CS9_SW8  },  //  14 ENTER
    {0, CS4_SW9,  CS5_SW9,  CS6_SW9  },  //  15 0
    {0, CS7_SW9,  CS8_SW9,  CS9_SW9  },  //  16 .
    {0, CS1_SW1,  CS2_SW1,  CS3_SW1  },  //  17 LED18
    {0, CS1_SW2,  CS2_SW2,  CS3_SW2  },  //  18 LED19
    {0, CS1_SW3,  CS2_SW3,  CS3_SW3  },  //  19 LED20
    {0, CS1_SW4,  CS2_SW4,  CS3_SW4  },  //  20 LED21
    {0, CS1_SW5,  CS2_SW5,  CS3_SW5  },  //  21 LED22
    {0, CS1_SW6,  CS2_SW6,  CS3_SW6  },  //  22 LED23
    {0, CS1_SW7,  CS2_SW7,  CS3_SW7  },  //  23 LED24
    {0, CS10_SW1, CS11_SW1, CS12_SW1 },  //  24 LED27
    {0, CS10_SW2, CS11_SW2, CS12_SW2 },  //  25 LED28
    {0, CS10_SW3, CS11_SW3, CS12_SW3 },  //  26 LED29
    {0, CS10_SW4, CS11_SW4, CS12_SW4 },  //  27 LED30
    {0, CS10_SW5, CS11_SW5, CS12_SW5 },  //  28 LED31
    {0, CS10_SW6, CS11_SW6, CS12_SW6 },  //  29 LED32
    {0, CS10_SW7, CS11_SW7, CS12_SW7 },  //  30 LED33
};

led_config_t g_led_config = {{
    { 0,   1,   2,   3  },
    { 4,   5,   6,   7  },
    { 8,   9,   10,  NO_LED},
    { 11,  12,  13,  14 },
    { 15,  NO_LED, NO_LED, 16 }
}, {
    {45,  0  },  //  0  NUM
    {90,  0  },  //  1  /
    {134, 0  },  //  2  *
    {179, 0  },  //  3  -
    {45,  16 },  //  4  7
    {90,  16 },  //  5  8
    {134, 16 },  //  6  9
    {179, 24 },  //  7  +
    {45,  32 },  //  8  4
    {90,  32 },  //  9  5
    {134, 32 },  //  10 6
    {45,  48 },  //  11 1
    {90,  48 },  //  12 2
    {134, 48 },  //  13 3
    {179, 56 },  //  14 ENTER
    {67,  64 },  //  15 0
    {134, 64 },  //  16 .
    {0,   0  },  //  17 LED18
    {0,   11 },  //  18 LED19
    {0,   21 },  //  19 LED20
    {0,   32 },  //  20 LED21
    {0,   43 },  //  21 LED22
    {0,   53 },  //  22 LED23
    {0,   64 },  //  23 LED24
    {224, 0  },  //  24 LED27
    {224, 11 },  //  25 LED28
    {224, 21 },  //  26 LED29
    {224, 32 },  //  27 LED30
    {224, 43 },  //  28 LED31
    {224, 53 },  //  29 LED32
    {224, 64 }   //  30 LED33
}, {
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4,
    4, 4, 4, 4,
    4,       4,
    2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2
} };

#    ifdef AW20216S_PW_EN_PIN_1

void keyboard_pre_init_user(void) {
    wait_ms(2000);
    setPinOutput(AW20216S_PW_EN_PIN_1);
    writePinHigh(AW20216S_PW_EN_PIN_1);
}
#    endif

#endif
