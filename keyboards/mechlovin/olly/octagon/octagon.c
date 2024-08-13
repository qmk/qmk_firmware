/* Copyright 2022 Team Mechlovin
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

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_1  },  { 0, C1_2 },  { 0, C1_3  },  { 0, C1_4 },  { 0, C1_5  },  { 0, C1_6 },  { 0, C1_7  },  { 0, C1_8 },  { 0, C1_9  },  { 0, C1_10 },  { 0, C1_11  },  { 0, C1_12 },  { 0, C1_13  },  { 0, C1_14 },  { 0, C1_15  },  { 0, C1_16 },
    { 0, C2_1  },  { 0, C2_2 },  { 0, C2_3  },  { 0, C2_4 },  { 0, C2_5  },  { 0, C2_6 },  { 0, C2_7  },  { 0, C2_8 },  { 0, C2_9  },  { 0, C2_10 },  { 0, C2_11  },  { 0, C2_12 },  { 0, C2_13  },  { 0, C2_14 },  { 0, C2_15  },  { 0, C2_16 },
    { 0, C3_1  },  { 0, C3_2 },  { 0, C3_3  },  { 0, C3_4 },  { 0, C3_5  },  { 0, C3_6 },  { 0, C3_7  },  { 0, C3_8 },  { 0, C3_9  },  { 0, C3_10 },  { 0, C3_11  },  { 0, C3_12 },  { 0, C3_13  },  { 0, C3_14 },                  { 0, C3_16 },
    { 0, C4_1  },  { 0, C4_2 },  { 0, C4_3  },  { 0, C4_4 },  { 0, C4_5  },  { 0, C4_6 },  { 0, C4_7  },  { 0, C4_8 },  { 0, C4_9  },  { 0, C4_10 },  { 0, C4_11  },  { 0, C4_12 },  { 0, C4_13  },  { 0, C4_14 },                  { 0, C4_16 },
    { 0, C5_1  },  { 0, C5_2 },  { 0, C5_3  },  { 0, C5_4 },  { 0, C5_5  },  { 0, C5_6 },  { 0, C5_7  },  { 0, C5_8 },  { 0, C5_9  },  { 0, C5_10 },  { 0, C5_11  },  { 0, C5_12 },  { 0, C5_13  },  { 0, C5_14 },                  { 0, C5_16 },
    { 0, C6_1  },  { 0, C6_2 },  { 0, C6_3  },                                             { 0, C6_7  },                                              { 0, C6_11  },  { 0, C6_12 },  { 0, C6_13  },  { 0, C6_14 },  { 0, C6_15  },  { 0, C6_16 },
    { 0, C3_15 },  { 0, C4_15 }, { 0, C5_15 },  // Lock Indicator
    { 0, C7_13 },  { 0, C7_14 }, { 0, C7_15 }, { 0, C7_16 }, // Layer Indicator
};

bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(87, 0xFF);
        led_matrix_set_value(47, 0xFF);
    } else {
        led_matrix_set_value(87, 0x00);
    }
    if (host_keyboard_led_state().num_lock) {
        led_matrix_set_value(88, 0xFF);
    } else {
        led_matrix_set_value(88, 0x00);
    }
    if (host_keyboard_led_state().scroll_lock) {
        led_matrix_set_value(89, 0xFF);
    } else {
        led_matrix_set_value(89, 0x00);
    }
    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            led_matrix_set_value(90, 0xFF);
            break;
        case 1:
            led_matrix_set_value(91, 0xFF);
            break;
        case 2:
            led_matrix_set_value(92, 0xFF);
            break;
        case 3:
            led_matrix_set_value(93, 0xFF);
            break;
        default:
            led_matrix_set_value(90, 0x00);
            led_matrix_set_value(91, 0x00);
            led_matrix_set_value(92, 0x00);
            led_matrix_set_value(93, 0x00);
    }
    return layer_state_set_user(state);
}
