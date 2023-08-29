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
 *
 *  09, 05, xx, xx, 04, xx,                   xx, 14, xx, xx, 15, 19,
 *  xx, xx, xx, xx, xx, 03,                   13, xx, xx, xx, xx, xx,
 *  08, 06, 07, xx, xx, xx, 00, xx,   xx, 10, xx, xx, xx, 17, 16, 18,
 *                  xx, 02, 01, xx,   xx, xx, xx, 11, 12, xx
 */
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { NO_LED, NO_LED, NO_LED, 4,      NO_LED, NO_LED, 5,      9     },
    { NO_LED, NO_LED, 3,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 0,      NO_LED, NO_LED, NO_LED, 7,      6,      8      },
    { NO_LED, NO_LED, 1,      2,      NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, 14,     NO_LED, NO_LED, 15,     19     },
    { NO_LED, NO_LED, 13,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 10,     NO_LED, NO_LED, NO_LED, 17,     16,     18     },
    { NO_LED, NO_LED, 11,     12,     NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
    {91,40}, {77,56}, {63,56}, {77,24}, {63,8}, {21,8}, {21,40}, {35,40}, {7,40}, {7,8},
    {133,40}, {147,56}, {161,56}, {147,24}, {161,8}, {203,8}, {203,40}, {189,40}, {217,40}, {217,8}
}, {
    // LED Index to Flag
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif
