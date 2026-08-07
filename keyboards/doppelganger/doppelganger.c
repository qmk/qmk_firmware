/* Copyright 2019 Yiancar-Designs
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

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(B0);

    keyboard_pre_init_user();
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(B0, !(state & (1UL << 1)));
    return state;
}

// Override core logic as we reuse SPLIT_HAND_PIN within matrix pins
bool is_keyboard_left(void) {
    gpio_set_pin_input(SPLIT_HAND_PIN);
    return gpio_read_pin(SPLIT_HAND_PIN);
}
