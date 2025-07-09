/*
Copyright 2022 Mechlovin'

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



const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C2_1  },  { 0, C2_2 },  { 0, C2_3  },  { 0, C2_4 },  { 0, C2_5  },  { 0, C2_6 },  { 0, C2_7  },  { 0, C2_8 },  { 0, C2_9  },  { 0, C2_10 },  { 0, C2_11  },  { 0, C2_12 },  { 0, C2_13  },  { 0, C2_14 },  { 0, C2_15  },  { 0, C2_16 },
    { 0, C3_1  },  { 0, C3_2 },  { 0, C3_3  },  { 0, C3_4 },  { 0, C3_5  },  { 0, C3_6 },  { 0, C3_7  },  { 0, C3_8 },  { 0, C3_9  },  { 0, C3_10 },  { 0, C3_11  },  { 0, C3_12 },  { 0, C3_13  },  { 0, C3_14 },                  { 0, C3_16 },
    { 0, C4_1  },  { 0, C4_2 },  { 0, C4_3  },  { 0, C4_4 },  { 0, C4_5  },  { 0, C4_6 },  { 0, C4_7  },  { 0, C4_8 },  { 0, C4_9  },  { 0, C4_10 },  { 0, C4_11  },  { 0, C4_12 },  { 0, C4_13  },  { 0, C4_14 },                  { 0, C4_16 },
    { 0, C5_1  },  { 0, C5_2 },  { 0, C5_3  },  { 0, C5_4 },  { 0, C5_5  },  { 0, C5_6 },  { 0, C5_7  },  { 0, C5_8 },  { 0, C5_9  },  { 0, C5_10 },  { 0, C5_11  },  { 0, C5_12 },  { 0, C5_13  },  { 0, C5_14 },                  { 0, C5_16 },
    { 0, C6_1  },  { 0, C6_2 },  { 0, C6_3  },                                             { 0, C6_7  },                                              { 0, C6_11  },  { 0, C6_12 },                  { 0, C6_14 },  { 0, C6_15  },  { 0, C6_16 },
};

bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
    	return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(31, 0xFF);
    }
    return true;
}
