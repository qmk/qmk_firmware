// Copyright 2023 a_marmot
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
//
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// Dummy IS31FL3731 config for testing - enables all possible LED locations

#include "config.h"
#include "orbweaver.h"

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,  C2_1,  C3_1},
    {0, C1_2,  C2_2,  C3_2},
    {0, C1_3,  C2_3,  C3_3},
    {0, C1_4,  C2_4,  C3_4},
    {0, C1_5,  C2_5,  C3_5},
    {0, C1_6,  C2_6,  C3_6},
    {0, C1_7,  C2_7,  C3_7},
    {0, C1_8,  C2_8,  C3_8},  
    {0, C1_9,  C2_9,  C3_9},
    {0, C1_10,  C2_10,  C3_10},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},
    {0, C4_1,  C5_1,  C6_1},
    {0, C4_2,  C5_2,  C6_2},
    {0, C4_3,  C5_3,  C6_3},
    {0, C4_4,  C5_4,  C6_4},
    {0, C4_5,  C5_5,  C6_5},
    {0, C4_6,  C5_6,  C6_6},
    {0, C4_7,  C5_7,  C6_7},
    {0, C4_8,  C5_8,  C6_8},
    {0, C4_9,  C5_9,  C6_9},
    {0, C4_10,  C5_10,  C6_10},
    {0, C4_11,  C5_11,  C6_11},
    {0, C4_12,  C5_12,  C6_12},
    {0, C4_13,  C5_13,  C6_13},
    {0, C4_14,  C5_14,  C6_14},
    {0, C4_15,  C5_15,  C6_15},
    {0, C4_16,  C5_16,  C6_16}, 
    {0, C7_1,  C8_1,  C9_1},
    {0, C7_2,  C8_2,  C9_2},
    {0, C7_3,  C8_3,  C9_3},
    {0, C7_4,  C8_4,  C9_4},
    {0, C7_5,  C8_5,  C9_5},
    {0, C7_6,  C8_6,  C9_6},
    {0, C7_7,  C8_7,  C9_7},
    {0, C7_8,  C8_8,  C9_8}, 
    {0, C7_9,  C8_9,  C9_9},
    {0, C7_10,  C8_10,  C9_10},
    {0, C7_11,  C8_11,  C9_11},
    {0, C7_12,  C8_12,  C9_12},
    {0, C7_13,  C8_13,  C9_13},
    {0, C7_14,  C8_14,  C9_14},
    {0, C7_15,  C8_15,  C9_15},
    {0, C7_16,  C8_16,  C9_16}
};

// Dummy RGB Matrix config for testing
led_config_t g_led_config = {
    // Matrix location to LED index
    {
        [0 ... MATRIX_ROWS-1] = {
            [0 ... MATRIX_COLS-1] = NO_LED
        }
    },

    // LED index to physical location
    {
        [0 ... RGB_MATRIX_LED_COUNT-1] = {0, 0}
    },

    // LED index to flags
    {
        [0 ... RGB_MATRIX_LED_COUNT-1] = 4
    }
};



