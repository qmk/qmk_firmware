/* Copyright 2020 Holten Campbell
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

void matrix_init_kb(void) {
  // set CapsLock LED to output and low
  gpio_set_pin_output(B0);
  gpio_write_pin_low(B0);
  // set NumLock LED to output and low
  gpio_set_pin_output(B1);
  gpio_write_pin_low(B1);
  // set ScrollLock LED to output and low
  gpio_set_pin_output(B2);
  gpio_write_pin_low(B2);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B1, led_state.num_lock);
        gpio_write_pin(B0, led_state.caps_lock);
        //gpio_write_pin(B2, led_state.scroll_lock);
    }
    return res;
}

//function for layer indicator LED
layer_state_t layer_state_set_kb(layer_state_t state)
{
    if (get_highest_layer(state) == 1) {
    gpio_write_pin_high(B2);
	} else {
		gpio_write_pin_low(B2);
    }
    return layer_state_set_user(state);
}
