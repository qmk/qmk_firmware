/* Copyright 2023 Mechlovin'
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

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
}

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_8  },                { 0, C3_8 },  { 0, C4_8  },  { 0, C5_8 },  { 0, C6_8  },  { 0, C7_8 },  { 0, C8_8  },  { 0, C9_8 },  { 0, C1_9  },  { 0, C2_9  },  { 0, C3_9   },  { 0, C4_9  },  { 0, C5_9   },  { 0, C6_9  },  { 0, C7_9   },  { 0, C8_9  },  { 0, C9_9  },  { 0, C1_16 },
    { 0, C1_7  },  { 0, C2_7 },  { 0, C3_7 },  { 0, C4_7  },  { 0, C5_7 },  { 0, C6_7  },  { 0, C7_7 },  { 0, C8_7  },  { 0, C9_7 },  { 0, C1_10 },  { 0, C2_10 },  { 0, C3_10  },  { 0, C4_10 },  { 0, C5_10  },  { 0, C6_10 },  { 0, C7_10  },  { 0, C8_10 },  { 0, C9_10 },  { 0, C2_16 },
    { 0, C1_6  },  { 0, C2_6 },  { 0, C3_6 },  { 0, C4_6  },  { 0, C5_6 },  { 0, C6_6  },  { 0, C7_6 },  { 0, C8_6  },  { 0, C9_6 },  { 0, C1_11 },  { 0, C2_11 },  { 0, C3_11  },  { 0, C4_11 },  { 0, C5_11  },  { 0, C6_11 },  { 0, C7_11  },  { 0, C8_11 },  { 0, C9_11 },  { 0, C3_16 },
    { 0, C1_5  },  { 0, C2_5 },  { 0, C3_5 },  { 0, C4_5  },  { 0, C5_5 },  { 0, C6_5  },  { 0, C7_5 },  { 0, C8_5  },  { 0, C9_5 },  { 0, C1_12 },  { 0, C2_12 },  { 0, C3_12  },  { 0, C4_12 },  { 0, C5_12  },                 { 0, C7_12  },  { 0, C8_12 },  { 0, C9_12 },  { 0, C4_16 },
    { 0, C1_4  },  { 0, C2_4 },  { 0, C3_4 },  { 0, C4_4  },  { 0, C5_4 },  { 0, C6_4  },  { 0, C7_4 },  { 0, C8_4  },  { 0, C9_4 },  { 0, C1_13 },  { 0, C2_13 },  { 0, C3_13  },  { 0, C4_13 },  { 0, C5_13  },  { 0, C6_13 },  { 0, C7_13  },  { 0, C8_13 },  { 0, C9_13 },  { 0, C5_16 },
    { 0, C1_3  },  { 0, C2_3 },                { 0, C4_3  },                               { 0, C7_3 },                                              { 0, C2_14 },  { 0, C3_14  },  { 0, C4_14 },  { 0, C5_14  },  { 0, C6_14 },  { 0, C7_14  },  { 0, C8_15 },  { 0, C9_15 },  { 0, C7_16 },
    { 0, C2_1  },  { 0, C1_1 },  { 0, C9_1 },  // Lock LED Indicator
    { 0, C7_15 },  { 0, C6_15 }, { 0, C9_16 }, { 0, C8_16 }, { 0, C1_15 }, // Layer LED Indicator
};



bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) { return false; }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(106, 0xFF);
        led_matrix_set_value(56, 0xFF);
    } else {
        led_matrix_set_value(106, 0x00);
    }
    if (host_keyboard_led_state().num_lock) {
        led_matrix_set_value(107, 0xFF);
        led_matrix_set_value(33, 0xFF);
    } else {
        led_matrix_set_value(107, 0x00);
    }
    if (host_keyboard_led_state().scroll_lock) {
        led_matrix_set_value(108, 0xFF);
    } else {
        led_matrix_set_value(108, 0x00);
    }
  // if on layer 0, turn on L1 LED, otherwise off.
    if (layer_state_is(0)) {
        led_matrix_set_value(109, 0xFF);
    } else {
        led_matrix_set_value(109, 0x00);
    }
  // if on layer 1, turn on L2 LED, otherwise off.
    if (layer_state_is(1)) {
        led_matrix_set_value(110, 0xFF);
    } else {
        led_matrix_set_value(110, 0x00);
    }

  // if on layer 2, turn on L3 LED, otherwise off.
    if (layer_state_is(2)) {
        led_matrix_set_value(111, 0xFF);
    } else {
        led_matrix_set_value(111, 0x00);
    }

  // if on layer 3, turn on L4 LED, otherwise off.
    if (layer_state_is(3)) {
        led_matrix_set_value(112, 0xFF);
    } else {
        led_matrix_set_value(112, 0x00);
    }
  // if on layer 4, turn on L5 LED, otherwise off.
    if (layer_state_is(4)) {
        led_matrix_set_value(113, 0xFF);
    } else {
        led_matrix_set_value(114, 0x00);
    }

    return true;
}
