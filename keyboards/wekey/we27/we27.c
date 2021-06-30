/* Copyright 2021 @wekey
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

#include "we27.h"

#define __ NO_LED

led_config_t g_led_config = { {
    { 0,  1,  2,  3,  4  },
    { 9,  8,  7,  6,  5  },
    { 10, 11, 12, 13, 14 },
    { 18, 17, 16, 15, __ },
    { 19, 20, 21, 22, 23 },
    { 26, 25, __, 24, __ }
}, {
    {0,1},{56,1},{112,1},{168,1},{224,1},
    {0,16},{56,16},{112,16},{168,16},{224,16},
    {0,28},{56,28},{112,28},{168,28},{224,28},
    {0,40},{56,40},{112,40},{168,40},
    {0,52},{56,52},{112,52},{168,52},{224,52},
    {0,64},{56,64},{168,64}
}, {
    1, 1, 1, 1, 1,
    1, 1, 4, 4, 4,
    1, 4, 4, 4, 4,
    1, 4, 4, 4,
    1, 4, 4, 4, 4,
    1, 4,    4
} };

#define NUMBER_OF_ENCODERS 1
#define ENCODER_KEYMAP_CLOCKWISE { {5, 4} }
#define ENCODER_KEYMAP_COUNTERCLOCKWISE { {3, 4} }

const uint8_t encoder_km_clockwise[NUMBER_OF_ENCODERS][2] = ENCODER_KEYMAP_CLOCKWISE;
const uint8_t encoder_km_counterclockwise[NUMBER_OF_ENCODERS][2] = ENCODER_KEYMAP_COUNTERCLOCKWISE;

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    extern layer_state_t layer_state;
    if (index == 0) {
        keypos_t key;
        uint16_t keycode;
        if (clockwise) {
            key.row = encoder_km_clockwise[index][0];
            key.col = encoder_km_clockwise[index][1];
        } else {
            key.row = encoder_km_counterclockwise[index][0];
            key.col = encoder_km_counterclockwise[index][1];
        }
        keycode = keymap_key_to_keycode(get_highest_layer(layer_state), key);
        if (keycode != 0) {
            tap_code16(keycode);
        }
    }
    return true;
}
