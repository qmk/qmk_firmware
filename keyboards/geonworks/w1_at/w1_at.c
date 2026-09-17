/* Copyright 2021 Yiancar-Designs
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

void led_init_ports(void) {
    // Set our LED pins as open drain outputs
    gpio_set_pin_output_open_drain(LED_CAPS_LOCK_PIN);
    gpio_set_pin_output_open_drain(LED_NUM_LOCK_PIN);
    gpio_set_pin_output_open_drain(LED_SCROLL_LOCK_PIN);
    gpio_set_pin_output_open_drain(LED_KANA_PIN);
    gpio_set_pin_output_open_drain(A14);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    gpio_write_pin(A14, !layer_state_cmp(state, 1));
    return layer_state_set_user(state);
}
