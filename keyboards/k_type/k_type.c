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

#include "k_type.h"


#ifdef RGB_MATRIX_ENABLE

#include "is31fl3733-dual.h"


const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    { 0, B_1,  A_1,  C_1  },
    { 0, B_2,  A_2,  C_2  },
    { 0, B_3,  A_3,  C_3  },
    { 0, B_4,  A_4,  C_4  },
    { 0, B_5,  A_5,  C_5  },
    { 0, B_6,  A_6,  C_6  },
    { 0, B_7,  A_7,  C_7  },
    { 0, B_8,  A_8,  C_8  },
    { 0, B_9,  A_9,  C_9  },
    { 0, B_10, A_10, C_10 },
    { 0, B_11, A_11, C_11 },
    { 0, B_12, A_12, C_12 },
    { 0, B_13, A_13, C_13 },
    { 0, B_14, A_14, C_14 },
    { 0, B_15, A_15, C_15 },
    { 0, B_16, A_16, C_16 },

    { 0, E_1,  D_1,  F_1  },
    { 0, E_2,  D_2,  F_2  },
    { 0, E_3,  D_3,  F_3  },
    { 0, E_4,  D_4,  F_4  },
    { 0, E_5,  D_5,  F_5  },
    { 0, E_6,  D_6,  F_6  },
    { 0, E_7,  D_7,  F_7  },
    { 0, E_8,  D_8,  F_8  },
    { 0, E_9,  D_9,  F_9  },
    { 0, E_10, D_10, F_10 },
    { 0, E_11, D_11, F_11 },
    { 0, E_12, D_12, F_12 },
    { 0, E_13, D_13, F_13 },
    { 0, E_14, D_14, F_14 },
    { 0, E_15, D_15, F_15 },
    { 0, E_16, D_16, F_16 },

    { 0, H_1,  G_1,  I_1  },
    { 0, H_2,  G_2,  I_2  },
    { 0, H_3,  G_3,  I_3  },
    { 0, H_4,  G_4,  I_4  },
    { 0, H_5,  G_5,  I_5  },
    { 0, H_6,  G_6,  I_6  },
    { 0, H_7,  G_7,  I_7  },
    { 0, H_8,  G_8,  I_8  },
    { 0, H_9,  G_9,  I_9  },
    { 0, H_10, G_10, I_10 },
    { 0, H_11, G_11, I_11 },
    { 0, H_12, G_12, I_12 },
    { 0, H_13, G_13, I_13 },
    { 0, H_14, G_14, I_14 },
    { 0, H_15, G_15, I_15 },
    { 0, H_16, G_16, I_16 },

    { 0, K_1,  J_1,  L_1  },
    { 0, K_2,  J_2,  L_2  },
    { 0, K_3,  J_3,  L_3  },
    { 0, K_4,  J_4,  L_4  },
    { 0, K_5,  J_5,  L_5  },
    { 0, K_6,  J_6,  L_6  },
    { 0, K_7,  J_7,  L_7  },
    { 0, K_8,  J_8,  L_8  },
    { 0, K_9,  J_9,  L_9  },
    { 0, K_10, J_10, L_10 },
    { 0, K_11, J_11, L_11 },
    { 0, K_12, J_12, L_12 },
    { 0, K_13, J_13, L_13 },
    { 0, K_14, J_14, L_14 },
    { 0, K_15, J_15, L_15 },
    { 0, K_16, J_16, L_16 },

    // Driver 2 is on I2C2
    { 1, B_1,  A_1,  C_1  },
    { 1, B_2,  A_2,  C_2  },
    { 1, B_3,  A_3,  C_3  },
    { 1, B_4,  A_4,  C_4  },
    { 1, B_5,  A_5,  C_5  },
    { 1, B_6,  A_6,  C_6  },
    { 1, B_7,  A_7,  C_7  },
    { 1, B_8,  A_8,  C_8  },
    { 1, B_9,  A_9,  C_9  },
    { 1, B_10, A_10, C_10 },
    { 1, B_11, A_11, C_11 },
    { 1, B_12, A_12, C_12 },
    { 1, B_13, A_13, C_13 },
    { 1, B_14, A_14, C_14 },
    { 1, B_15, A_15, C_15 },
    { 1, B_16, A_16, C_16 },

    { 1, E_1,  D_1,  F_1  },
    { 1, E_2,  D_2,  F_2  },
    { 1, E_3,  D_3,  F_3  },
    { 1, E_4,  D_4,  F_4  },
    { 1, E_5,  D_5,  F_5  },
    { 1, E_6,  D_6,  F_6  },
    { 1, E_7,  D_7,  F_7  },
    { 1, E_8,  D_8,  F_8  },
    { 1, E_9,  D_9,  F_9  },
    { 1, E_10, D_10, F_10 },
    { 1, E_11, D_11, F_11 },
    { 1, E_12, D_12, F_12 },
    { 1, E_13, D_13, F_13 },
    { 1, E_14, D_14, F_14 },
    { 1, E_15, D_15, F_15 },
    { 1, E_16, D_16, F_16 },

    { 1, H_1,  G_1,  I_1  },
    { 1, H_2,  G_2,  I_2  },
    { 1, H_3,  G_3,  I_3  },
    { 1, H_4,  G_4,  I_4  },
    { 1, H_5,  G_5,  I_5  },
    { 1, H_6,  G_6,  I_6  },
    { 1, H_7,  G_7,  I_7  },
    { 1, H_8,  G_8,  I_8  },
    { 1, H_9,  G_9,  I_9  },
    { 1, H_10, G_10, I_10 },
    { 1, H_11, G_11, I_11 },
    { 1, H_12, G_12, I_12 },
    { 1, H_13, G_13, I_13 },
    { 1, H_14, G_14, I_14 },
    { 1, H_15, G_15, I_15 },
    { 1, H_16, G_16, I_16 },

    { 1, K_1,  J_1,  L_1  },
    { 1, K_2,  J_2,  L_2  },
    { 1, K_3,  J_3,  L_3  },
    { 1, K_4,  J_4,  L_4  },
    { 1, K_5,  J_5,  L_5  },
    { 1, K_6,  J_6,  L_6  },
    { 1, K_7,  J_7,  L_7  }
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
#endif


void keyboard_pre_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    // Turn on LED controller
    setPinOutput(B16);
    writePinHigh(B16);
#endif
    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

#ifdef RGB_MATRIX_ENABLE
    /*
     * Since K20x is stuck with a 32 byte EEPROM (see tmk_core/common/chibios/eeprom_teensy.c),
     * and neither led_matrix_eeconfig.speed or .flags fit in this boundary, just force their values to default on boot.
     */
#    if !defined(RGB_MATRIX_STARTUP_SPD)
#        define RGB_MATRIX_STARTUP_SPD UINT8_MAX / 2
#    endif
    rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD),
    rgb_matrix_set_flags(LED_FLAG_ALL);
#endif

    matrix_init_user();
}
