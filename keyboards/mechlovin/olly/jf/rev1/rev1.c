/* Copyright 2021 mechlovin
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
  gpio_set_pin_output(C0);
  gpio_set_pin_output(D0);
  gpio_set_pin_output(D1);
  gpio_set_pin_output(C1);
  gpio_set_pin_output(C6);
  gpio_set_pin_output(B0);
  gpio_set_pin_output(B1);
  gpio_set_pin_output(B2);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(D1, layer_state_cmp(state, 1));
    gpio_write_pin(D0, layer_state_cmp(state, 2));
    gpio_write_pin(C1, layer_state_cmp(state, 3));
    gpio_write_pin(C0, layer_state_cmp(state, 4));
    gpio_write_pin(C6, layer_state_cmp(state, 5));

    return state;
}
