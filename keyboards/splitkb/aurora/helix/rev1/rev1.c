/* Copyright 2023 splitkb.com <support@splitkb.com>
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

#include QMK_KEYBOARD_H

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: SPLIT_HAND_PIN is shared with the RGB pin so we don't want to keep reusing the pin for handedness checks.
bool is_keyboard_left(void) {
static enum { UNKNOWN, LEFT, RIGHT } hand_side = UNKNOWN;
    // only check once, as this is called often
    if (hand_side == UNKNOWN) {
        #if defined(SPLIT_HAND_PIN)
            // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
            gpio_set_pin_input(SPLIT_HAND_PIN);
            hand_side = gpio_read_pin(SPLIT_HAND_PIN) ? LEFT : RIGHT;
            return (hand_side == LEFT);
        #endif
        hand_side = is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
    } else {
        return (hand_side == LEFT);
    }
}

#ifdef SWAP_HANDS_ENABLE
// clang-format off
    __attribute__ ((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
        {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}},
        {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}},
        {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}},
        {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}},
        {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}},
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}},
        {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}},
        {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}}
    };
// clang-format on
#    ifdef ENCODER_MAP_ENABLE
        const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1,0};
#    endif
#endif
