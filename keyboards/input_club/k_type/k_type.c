/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#    include "is31fl3733-dual.h"

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    { 0, SW2_CS1,  SW1_CS1,  SW3_CS1  },
    { 0, SW2_CS2,  SW1_CS2,  SW3_CS2  },
    { 0, SW2_CS3,  SW1_CS3,  SW3_CS3  },
    { 0, SW2_CS4,  SW1_CS4,  SW3_CS4  },
    { 0, SW2_CS5,  SW1_CS5,  SW3_CS5  },
    { 0, SW2_CS6,  SW1_CS6,  SW3_CS6  },
    { 0, SW2_CS7,  SW1_CS7,  SW3_CS7  },
    { 0, SW2_CS8,  SW1_CS8,  SW3_CS8  },
    { 0, SW2_CS9,  SW1_CS9,  SW3_CS9  },
    { 0, SW2_CS10, SW1_CS10, SW3_CS10 },
    { 0, SW2_CS11, SW1_CS11, SW3_CS11 },
    { 0, SW2_CS12, SW1_CS12, SW3_CS12 },
    { 0, SW2_CS13, SW1_CS13, SW3_CS13 },
    { 0, SW2_CS14, SW1_CS14, SW3_CS14 },
    { 0, SW2_CS15, SW1_CS15, SW3_CS15 },
    { 0, SW2_CS16, SW1_CS16, SW3_CS16 },

    { 0, SW5_CS1,  SW4_CS1,  SW6_CS1  },
    { 0, SW5_CS2,  SW4_CS2,  SW6_CS2  },
    { 0, SW5_CS3,  SW4_CS3,  SW6_CS3  },
    { 0, SW5_CS4,  SW4_CS4,  SW6_CS4  },
    { 0, SW5_CS5,  SW4_CS5,  SW6_CS5  },
    { 0, SW5_CS6,  SW4_CS6,  SW6_CS6  },
    { 0, SW5_CS7,  SW4_CS7,  SW6_CS7  },
    { 0, SW5_CS8,  SW4_CS8,  SW6_CS8  },
    { 0, SW5_CS9,  SW4_CS9,  SW6_CS9  },
    { 0, SW5_CS10, SW4_CS10, SW6_CS10 },
    { 0, SW5_CS11, SW4_CS11, SW6_CS11 },
    { 0, SW5_CS12, SW4_CS12, SW6_CS12 },
    { 0, SW5_CS13, SW4_CS13, SW6_CS13 },
    { 0, SW5_CS14, SW4_CS14, SW6_CS14 },
    { 0, SW5_CS15, SW4_CS15, SW6_CS15 },
    { 0, SW5_CS16, SW4_CS16, SW6_CS16 },

    { 0, SW8_CS1,  SW7_CS1,  SW9_CS1  },
    { 0, SW8_CS2,  SW7_CS2,  SW9_CS2  },
    { 0, SW8_CS3,  SW7_CS3,  SW9_CS3  },
    { 0, SW8_CS4,  SW7_CS4,  SW9_CS4  },
    { 0, SW8_CS5,  SW7_CS5,  SW9_CS5  },
    { 0, SW8_CS6,  SW7_CS6,  SW9_CS6  },
    { 0, SW8_CS7,  SW7_CS7,  SW9_CS7  },
    { 0, SW8_CS8,  SW7_CS8,  SW9_CS8  },
    { 0, SW8_CS9,  SW7_CS9,  SW9_CS9  },
    { 0, SW8_CS10, SW7_CS10, SW9_CS10 },
    { 0, SW8_CS11, SW7_CS11, SW9_CS11 },
    { 0, SW8_CS12, SW7_CS12, SW9_CS12 },
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 },
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 },
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 },
    { 0, SW8_CS16, SW7_CS16, SW9_CS16 },

    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1  },
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2  },
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3  },
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4  },
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5  },
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6  },
    { 0, SW11_CS7,  SW10_CS7,  SW12_CS7  },
    { 0, SW11_CS8,  SW10_CS8,  SW12_CS8  },
    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9  },
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 },
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 },
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 },
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 },
    { 0, SW11_CS14, SW10_CS14, SW12_CS14 },
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 },
    { 0, SW11_CS16, SW10_CS16, SW12_CS16 },

    // Driver 2 is on I2C2
    { 1, SW2_CS1,  SW1_CS1,  SW3_CS1  },
    { 1, SW2_CS2,  SW1_CS2,  SW3_CS2  },
    { 1, SW2_CS3,  SW1_CS3,  SW3_CS3  },
    { 1, SW2_CS4,  SW1_CS4,  SW3_CS4  },
    { 1, SW2_CS5,  SW1_CS5,  SW3_CS5  },
    { 1, SW2_CS6,  SW1_CS6,  SW3_CS6  },
    { 1, SW2_CS7,  SW1_CS7,  SW3_CS7  },
    { 1, SW2_CS8,  SW1_CS8,  SW3_CS8  },
    { 1, SW2_CS9,  SW1_CS9,  SW3_CS9  },
    { 1, SW2_CS10, SW1_CS10, SW3_CS10 },
    { 1, SW2_CS11, SW1_CS11, SW3_CS11 },
    { 1, SW2_CS12, SW1_CS12, SW3_CS12 },
    { 1, SW2_CS13, SW1_CS13, SW3_CS13 },
    { 1, SW2_CS14, SW1_CS14, SW3_CS14 },
    { 1, SW2_CS15, SW1_CS15, SW3_CS15 },
    { 1, SW2_CS16, SW1_CS16, SW3_CS16 },

    { 1, SW5_CS1,  SW4_CS1,  SW6_CS1  },
    { 1, SW5_CS2,  SW4_CS2,  SW6_CS2  },
    { 1, SW5_CS3,  SW4_CS3,  SW6_CS3  },
    { 1, SW5_CS4,  SW4_CS4,  SW6_CS4  },
    { 1, SW5_CS5,  SW4_CS5,  SW6_CS5  },
    { 1, SW5_CS6,  SW4_CS6,  SW6_CS6  },
    { 1, SW5_CS7,  SW4_CS7,  SW6_CS7  },
    { 1, SW5_CS8,  SW4_CS8,  SW6_CS8  },
    { 1, SW5_CS9,  SW4_CS9,  SW6_CS9  },
    { 1, SW5_CS10, SW4_CS10, SW6_CS10 },
    { 1, SW5_CS11, SW4_CS11, SW6_CS11 },
    { 1, SW5_CS12, SW4_CS12, SW6_CS12 },
    { 1, SW5_CS13, SW4_CS13, SW6_CS13 },
    { 1, SW5_CS14, SW4_CS14, SW6_CS14 },
    { 1, SW5_CS15, SW4_CS15, SW6_CS15 },
    { 1, SW5_CS16, SW4_CS16, SW6_CS16 },

    { 1, SW8_CS1,  SW7_CS1,  SW9_CS1  },
    { 1, SW8_CS2,  SW7_CS2,  SW9_CS2  },
    { 1, SW8_CS3,  SW7_CS3,  SW9_CS3  },
    { 1, SW8_CS4,  SW7_CS4,  SW9_CS4  },
    { 1, SW8_CS5,  SW7_CS5,  SW9_CS5  },
    { 1, SW8_CS6,  SW7_CS6,  SW9_CS6  },
    { 1, SW8_CS7,  SW7_CS7,  SW9_CS7  },
    { 1, SW8_CS8,  SW7_CS8,  SW9_CS8  },
    { 1, SW8_CS9,  SW7_CS9,  SW9_CS9  },
    { 1, SW8_CS10, SW7_CS10, SW9_CS10 },
    { 1, SW8_CS11, SW7_CS11, SW9_CS11 },
    { 1, SW8_CS12, SW7_CS12, SW9_CS12 },
    { 1, SW8_CS13, SW7_CS13, SW9_CS13 },
    { 1, SW8_CS14, SW7_CS14, SW9_CS14 },
    { 1, SW8_CS15, SW7_CS15, SW9_CS15 },
    { 1, SW8_CS16, SW7_CS16, SW9_CS16 },

    { 1, SW11_CS1,  SW10_CS1,  SW12_CS1  },
    { 1, SW11_CS2,  SW10_CS2,  SW12_CS2  },
    { 1, SW11_CS3,  SW10_CS3,  SW12_CS3  },
    { 1, SW11_CS4,  SW10_CS4,  SW12_CS4  },
    { 1, SW11_CS5,  SW10_CS5,  SW12_CS5  },
    { 1, SW11_CS6,  SW10_CS6,  SW12_CS6  },
    { 1, SW11_CS7,  SW10_CS7,  SW12_CS7  }
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {      0,      1,      2,      3,      4,      5,      6,      7,      8,      9 },
        {     10,     11,     12,     13,     14,     15,     16,     17,     18,     19 },
        {     20,     21,     22,     23,     24,     25,     26,     27,     28, NO_LED },
        {     29, NO_LED,     30,     31,     32,     33,     34,     35,     36,     37 },
        {     38,     39,     40,     41,     42,     43,     44,     45,     46, NO_LED },
        {     47,     48,     49,     50,     51,     52,     53,     54,     55,     56 },
        {     57,     58,     59,     60,     61, NO_LED,     62, NO_LED,     63, NO_LED },
        {     64,     65,     66,     67,     68,     69,     70,     71,     72,     73 },
        { NO_LED,     74, NO_LED,     75,     76,     77,     78,     79,     80,     81 },
        {     82,     83,     84,     85,     86, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    }, {
        // LED Index to Physical Position
        // Key LED
        { 0,  0    },                   { 26.35,  0    }, { 39.53,  0    }, { 52.71,  0    }, { 65.88,  0    }, { 79.06,  0    }, { 92.24,  0    }, { 105.41,  0    }, { 118.59,  0    }, { 131.77,  0    }, { 144.94,  0    }, { 158.12,  0    }, { 171.29,  0    },           { 197.65,  0    }, { 210.82,  0    }, { 224,  0    },

        { 0, 21.33 }, { 13.18, 21.33 }, { 26.35, 21.33 }, { 39.53, 21.33 }, { 52.71, 21.33 }, { 65.88, 21.33 }, { 79.06, 21.33 }, { 92.24, 21.33 }, { 105.41, 21.33 }, { 118.59, 21.33 }, { 131.77, 21.33 }, { 144.94, 21.33 }, { 158.12, 21.33 }, { 171.29, 21.33 },           { 197.65, 21.33 }, { 210.82, 21.33 }, { 224, 21.33 },
        { 0, 32    }, { 13.18, 32    }, { 26.35, 32    }, { 39.53, 32    }, { 52.71, 32    }, { 65.88, 32    }, { 79.06, 32    }, { 92.24, 32    }, { 105.41, 32    }, { 118.59, 32    }, { 131.77, 32    }, { 144.94, 32    }, { 158.12, 32    }, { 171.29, 32    },           { 197.65, 32    }, { 210.82, 32    }, { 224, 32    },
        { 0, 42.67 }, { 13.18, 42.67 }, { 26.35, 42.67 }, { 39.53, 42.67 }, { 52.71, 42.67 }, { 65.88, 42.67 }, { 79.06, 42.67 }, { 92.24, 42.67 }, { 105.41, 42.67 }, { 118.59, 42.67 }, { 131.77, 42.67 }, { 144.94, 42.67 },                    { 171.29, 42.67 },
        { 0, 53.33 },                   { 26.35, 53.33 }, { 39.53, 53.33 }, { 52.71, 53.33 }, { 65.88, 53.33 }, { 79.06, 53.33 }, { 92.24, 53.33 }, { 105.41, 53.33 }, { 118.59, 53.33 }, { 131.77, 53.33 }, { 144.94, 53.33 },                    { 171.29, 53.33 },                              { 210.82, 53.33 },
        { 0, 64    }, { 13.18, 64    }, { 26.35, 64    },                                                       { 79.06, 64    },                                                         { 131.77, 64    }, { 144.94, 64    }, { 158.12, 64    }, { 171.29, 64    },           { 197.65, 64    }, { 210.82, 64    }, { 224, 64    },

        // Underglow LED
        { 224, 64 }, { 206.77, 64 }, { 189.54, 64 }, { 172.31, 64 }, { 155.08, 64 }, { 137.85, 64 }, { 120.61, 64 }, { 103.38, 64 }, { 86.15, 64 }, { 68.92, 64 }, { 51.69, 64 }, { 34.46, 64 }, { 17.23, 64 }, { 0, 64 },
        { 0, 42.67 }, { 0, 21.33 },
        { 0, 0 }, { 17.23, 0 }, { 34.46, 0 }, { 51.69, 0 }, { 68.92, 0 }, { 86.15, 0 }, { 103.38, 0 }, { 120.61, 0 }, { 137.85, 0 }, { 155.08, 0 }, { 172.31, 0 }, { 189.54, 0 }, { 206.77, 0 }, { 224, 0 },
        { 224, 21.33 }, { 224, 42.67 }
    }, {
        // LED Index to Flag
        //Key LED
        1,  4, 4, 4, 4,  1, 1, 1, 1,  4, 4, 4, 4,    1, 1, 1,

        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,       1,
        1, 1, 1,          4,          1, 1, 1, 1,    1, 1, 1,

        // Underglow LED
        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,

        2,                                                  2,

        2,                                                  2,

        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    }
};

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    /*
     * Since K20x is stuck with a 32 byte EEPROM (see tmk_core/common/chibios/eeprom_teensy.c),
     * and neither led_matrix_eeconfig.speed or .flags fit in this boundary, just force their values to default on boot.
     */
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD),
    rgb_matrix_set_flags(LED_FLAG_ALL);

    matrix_init_user();
}
#endif
