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
        { 0,  0    },                   { 26,  0    }, { 39,  0    }, { 52,  0    }, { 65,  0    }, { 79,  0    }, { 92,  0    }, { 105,  0    }, { 118,  0    }, { 131,  0    }, { 144,  0    }, { 158,  0    }, { 171,  0    },           { 197,  0    }, { 210,  0    }, { 224,  0    },

        { 0, 21 }, { 13, 21 }, { 26, 21 }, { 39, 21 }, { 52, 21 }, { 65, 21 }, { 79, 21 }, { 92, 21 }, { 105, 21 }, { 118, 21 }, { 131, 21 }, { 144, 21 }, { 158, 21 }, { 171, 21 },           { 197, 21 }, { 210, 21 }, { 224, 21 },
        { 0, 32    }, { 13, 32    }, { 26, 32    }, { 39, 32    }, { 52, 32    }, { 65, 32    }, { 79, 32    }, { 92, 32    }, { 105, 32    }, { 118, 32    }, { 131, 32    }, { 144, 32    }, { 158, 32    }, { 171, 32    },           { 197, 32    }, { 210, 32    }, { 224, 32    },
        { 0, 42 }, { 13, 42 }, { 26, 42 }, { 39, 42 }, { 52, 42 }, { 65, 42 }, { 79, 42 }, { 92, 42 }, { 105, 42 }, { 118, 42 }, { 131, 42 }, { 144, 42 },                    { 171, 42 },
        { 0, 53 },                   { 26, 53 }, { 39, 53 }, { 52, 53 }, { 65, 53 }, { 79, 53 }, { 92, 53 }, { 105, 53 }, { 118, 53 }, { 131, 53 }, { 144, 53 },                    { 171, 53 },                              { 210, 53 },
        { 0, 64    }, { 13, 64    }, { 26, 64    },                                                       { 79, 64    },                                                         { 131, 64    }, { 144, 64    }, { 158, 64    }, { 171, 64    },           { 197, 64    }, { 210, 64    }, { 224, 64    },

        // Underglow LED
        { 224, 64 }, { 206, 64 }, { 189, 64 }, { 172, 64 }, { 155, 64 }, { 137, 64 }, { 120, 64 }, { 103, 64 }, { 86, 64 }, { 68, 64 }, { 51, 64 }, { 34, 64 }, { 17, 64 }, { 0, 64 },
        { 0, 42 }, { 0, 21 },
        { 0, 0 }, { 17, 0 }, { 34, 0 }, { 51, 0 }, { 68, 0 }, { 86, 0 }, { 103, 0 }, { 120, 0 }, { 137, 0 }, { 155, 0 }, { 172, 0 }, { 189, 0 }, { 206, 0 }, { 224, 0 },
        { 224, 21 }, { 224, 42 }
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
