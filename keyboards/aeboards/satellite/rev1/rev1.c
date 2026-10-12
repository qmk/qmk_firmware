/* Copyright 2022 Harrison Chan (Xelus)
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
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3731.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_1,   C3_1,   C4_1}, //A0
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C1_5,   C2_5,   C3_5}, //A5
    {0, C1_6,   C2_6,   C3_6}, //A6
    {0, C1_7,   C2_7,   C3_7}, //A7
    {0, C1_8,   C2_8,   C3_8}, //A8
    {0, C9_1,   C8_1,   C7_1}, //A9
    {0, C9_2,   C8_2,   C7_2}, //A10
    {0, C9_3,   C8_3,   C7_3}, //A11
    {0, C9_4,   C8_4,   C7_4}, //A12
    {0, C9_5,   C8_5,   C7_5}, //A13
    {0, C9_6,   C8_6,   C7_6}, //A14
    {0, C9_7,   C8_7,   C6_6}, //A15
    {0, C9_8,   C7_7,   C6_7}, //A16
    {0, C8_8,   C7_8,   C6_8}, //A17

    {0, C2_9,   C3_9,   C4_9},  //B0
    {0, C1_9,   C3_10,  C4_10}, //B1
    {0, C1_10,  C2_10,  C4_11}, //B2
    {0, C1_11,  C2_11,  C3_11}, //B3
    {0, C1_12,  C2_12,  C3_12}, //B4
    {0, C1_13,  C2_13,  C3_13}, //B5
    {0, C1_14,  C2_14,  C3_14}, //B6
    {0, C1_15,  C2_15,  C3_15}, //B7
    {0, C1_16,  C2_16,  C3_16}, //B8
    {0, C9_9,   C8_9,   C7_9},  //B9
    {0, C9_10,  C8_10,  C7_10}, //B10
    {0, C9_11,  C8_11,  C7_11}, //B11
    {0, C9_12,  C8_12,  C7_12}, //B12
    {0, C9_13,  C8_13,  C7_13}, //B13
    {0, C9_14,  C8_14,  C7_14}, //B14
    {0, C9_15,  C8_15,  C6_14}, //B15
    {0, C9_16,  C7_15,  C6_15}, //B16
    {0, C8_16,  C7_16,  C6_16}, //B17

    {1, C2_1,   C3_1,   C4_1}, //C0
    {1, C1_1,   C3_2,   C4_2}, //C1
    {1, C1_2,   C2_2,   C4_3}, //C2
    {1, C1_3,   C2_3,   C3_3}, //C3
    {1, C1_4,   C2_4,   C3_4}, //C4
    {1, C1_5,   C2_5,   C3_5}, //C5
    {1, C1_6,   C2_6,   C3_6}, //C6
    {1, C1_7,   C2_7,   C3_7}, //C7
    {1, C1_8,   C2_8,   C3_8}, //C8
    {1, C9_1,   C8_1,   C7_1}, //C9
    {1, C9_2,   C8_2,   C7_2}, //C10
    {1, C9_3,   C8_3,   C7_3}, //C11
    {1, C9_4,   C8_4,   C7_4}, //C12
    {1, C9_5,   C8_5,   C7_5}, //C13
    {1, C9_6,   C8_6,   C7_6}, //C14
    {1, C9_7,   C8_7,   C6_6}, //C15
    {1, C9_8,   C7_7,   C6_7}, //C16
    {1, C8_8,   C7_8,   C6_8}, //C17

    {1, C2_9,   C3_9,   C4_9},  //D0
    {1, C1_9,   C3_10,  C4_10}, //D1
    {1, C1_10,  C2_10,  C4_11}, //D2
    {1, C1_11,  C2_11,  C3_11}, //D3
    {1, C1_12,  C2_12,  C3_12}, //D4
    {1, C1_13,  C2_13,  C3_13}, //D5
    {1, C1_14,  C2_14,  C3_14}, //D6
    {1, C1_15,  C2_15,  C3_15}, //D7
    {1, C1_16,  C2_16,  C3_16}, //D8
    {1, C9_9,    C8_9,   C7_9}, //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}, //D16
    {1, C8_16,  C7_16,  C6_16}  //D17
};

// Custom Driver
static void init(void) {
    i2c_init();

    is31fl3731_init(0);
    is31fl3731_init(1);

    for (int index = 0; index < IS31FL3731_LED_COUNT; index++) {
        bool enabled = !(   ( index == 18+5) || //B5
                            ( index == 36+17) || //C17
                            ( index == 54+13) //D13
                        );
        is31fl3731_set_led_control_register(index, enabled, enabled, enabled);
    }

    is31fl3731_update_led_control_registers(0);
    is31fl3731_update_led_control_registers(1);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3731_flush,
    .set_color = is31fl3731_set_color,
    .set_color_all = is31fl3731_set_color_all
};

#endif
