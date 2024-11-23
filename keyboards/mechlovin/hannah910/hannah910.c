/* Copyright 2019 Mechlovin
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
  gpio_set_pin_output(B2);
  gpio_set_pin_output(D0);
  gpio_set_pin_output(D1);
  gpio_set_pin_output(D2);

}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B2, led_state.caps_lock);
    }
    return res;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
  // if on layer 1, turn on D2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        gpio_write_pin_high(D2);
    } else {
        gpio_write_pin_low(D2);
    }
  // if on layer 2, turn on D1 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        gpio_write_pin_high(D1);
    } else {
        gpio_write_pin_low(D1);
    }

  // if on layer 3, turn on D0 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        gpio_write_pin_high(D0);
    } else {
        gpio_write_pin_low(D0);
    }

    return state;
}
