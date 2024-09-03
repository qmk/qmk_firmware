/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

// Mask out handedness diode to prevent it
// from keeping the keyboard awake
// - just mirroring `KC_NO` in the `LAYOUT`
//   macro to keep it simple
const matrix_row_t matrix_mask[] = {
    0b11111100,
    0b11111100,
    0b11111111,
    0b00101111,
    0b11111100,
    0b11111100,
    0b11111111,
    0b00101111,
};

#ifdef SWAP_HANDS_ENABLE
// clang-format off
__attribute__ ((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}}
};
// clang-format on
#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
/* Map physical under glow LEDs for RGB matrix support
 *  09, 02, xx, xx, 01, xx,                   xx, 11, xx, xx, 12, 19,
 *  xx, xx, xx, xx, xx, 00,                   10, xx, xx, xx, xx, xx,
 *  08, 03, 04, xx, xx, xx, 07, xx,   xx, 17, xx, xx, xx, 14, 13, 18,
 *                  xx, 05, 06, xx,   xx, xx, xx, 16, 15, xx
 */
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { NO_LED, NO_LED, NO_LED, 1,      NO_LED, NO_LED, 2,      9     },
    { NO_LED, NO_LED, 0,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 7,      NO_LED, NO_LED, NO_LED, 4,      3,      8      },
    { NO_LED, NO_LED, 6,      5,      NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, 11,     NO_LED, NO_LED, 12,     19     },
    { NO_LED, NO_LED, 10,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 17,     NO_LED, NO_LED, NO_LED, 14,     13,     18     },
    { NO_LED, NO_LED, 16,     15,     NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
    {77,24}, {63,8}, {21,8}, {21,40}, {35,40}, {63,56}, {77,56}, {91,40}, {7,40}, {7,8},
    {147,24}, {161,8}, {203,8}, {203,40}, {189,40}, {161,56}, {147,56}, {133,40}, {217,40}, {217,8}
}, {
    // LED Index to Flag
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif
