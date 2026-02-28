/* Copyright 2021 3araht
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

#include "bandominedoni.h"

#if defined(SPLIT_HAND_MATRIX_GRID)
static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    gpio_set_pin_input_high(in_pin);
    gpio_set_pin_output(out_pin);
    gpio_write_pin_low(out_pin);
    // It's almost unnecessary, but wait until it's down to low, just in case.
    wait_us(1);
    uint8_t pin_state = gpio_read_pin(in_pin);
    // Set out_pin to a setting that is less susceptible to noise.
    gpio_set_pin_input_high(out_pin);
    matrix_io_delay();  // Wait for the pull-up to go HIGH.
    return pin_state;
}
#endif

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void) {
static enum { UNKNOWN, LEFT, RIGHT } hand_side = UNKNOWN;

    // only check once, as this is called often
    if (hand_side == UNKNOWN) {
#if defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        gpio_set_pin_input(SPLIT_HAND_PIN);
        hand_side = gpio_read_pin(SPLIT_HAND_PIN) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(SPLIT_HAND_MATRIX_GRID)
#    ifdef SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? RIGHT : LEFT;
        return (hand_side == LEFT);
#    else
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#    endif
#elif defined(EE_HANDS)
        hand_side = eeconfig_read_handedness() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(MASTER_RIGHT)
        hand_side = !is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#endif
        hand_side = is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
    } else {
        return (hand_side == LEFT);
    }
}
