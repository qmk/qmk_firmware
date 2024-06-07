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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, SW1_CS4,  SW1_CS5,  SW1_CS6  },  //  0  NUM
    {0, SW2_CS4,  SW2_CS5,  SW2_CS6  },  //  1  /
    {0, SW1_CS7,  SW1_CS8,  SW1_CS9  },  //  2  *
    {0, SW2_CS7,  SW2_CS8,  SW2_CS9  },  //  3  -
    {0, SW3_CS4,  SW3_CS5,  SW3_CS6  },  //  4  7
    {0, SW4_CS4,  SW4_CS5,  SW4_CS6  },  //  5  8
    {0, SW3_CS7,  SW3_CS8,  SW3_CS9  },  //  6  9
    {0, SW4_CS7,  SW4_CS8,  SW4_CS9  },  //  7  +
    {0, SW5_CS4,  SW5_CS5,  SW5_CS6  },  //  8  4
    {0, SW6_CS4,  SW6_CS5,  SW6_CS6  },  //  9  5
    {0, SW5_CS7,  SW5_CS8,  SW5_CS9  },  //  10 6
    {0, SW7_CS4,  SW7_CS5,  SW7_CS6  },  //  11 1
    {0, SW8_CS4,  SW8_CS5,  SW8_CS6  },  //  12 2
    {0, SW7_CS7,  SW7_CS8,  SW7_CS9  },  //  13 3
    {0, SW8_CS7,  SW8_CS8,  SW8_CS9  },  //  14 ENTER
    {0, SW9_CS4,  SW9_CS5,  SW9_CS6  },  //  15 0
    {0, SW9_CS7,  SW9_CS8,  SW9_CS9  },  //  16 .
    {0, SW1_CS1,  SW1_CS2,  SW1_CS3  },  //  17 LED18
    {0, SW2_CS1,  SW2_CS2,  SW2_CS3  },  //  18 LED19
    {0, SW3_CS1,  SW3_CS2,  SW3_CS3  },  //  19 LED20
    {0, SW4_CS1,  SW4_CS2,  SW4_CS3  },  //  20 LED21
    {0, SW5_CS1,  SW5_CS2,  SW5_CS3  },  //  21 LED22
    {0, SW6_CS1,  SW6_CS2,  SW6_CS3  },  //  22 LED23
    {0, SW7_CS1,  SW7_CS2,  SW7_CS3  },  //  23 LED24
    {0, SW1_CS10, SW1_CS11, SW1_CS12 },  //  24 LED27
    {0, SW2_CS10, SW2_CS11, SW2_CS12 },  //  25 LED28
    {0, SW3_CS10, SW3_CS11, SW3_CS12 },  //  26 LED29
    {0, SW4_CS10, SW4_CS11, SW4_CS12 },  //  27 LED30
    {0, SW5_CS10, SW5_CS11, SW5_CS12 },  //  28 LED31
    {0, SW6_CS10, SW6_CS11, SW6_CS12 },  //  29 LED32
    {0, SW7_CS10, SW7_CS11, SW7_CS12 },  //  30 LED33
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
    gpio_set_pin_output(AW20216S_PW_EN_PIN);
    gpio_write_pin_high(AW20216S_PW_EN_PIN);
}
#    endif

#endif
