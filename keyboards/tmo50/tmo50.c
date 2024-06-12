/* Copyright 2019 funderburker
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
#include "tmo50.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

  gpio_set_pin_output(B0);
  gpio_write_pin_low(B0);
  gpio_set_pin_output(B1);
  gpio_write_pin_high(B1);
  gpio_set_pin_output(B2);
  gpio_write_pin_high(B2);
  gpio_set_pin_output(B3);
  gpio_write_pin_high(B3);

	matrix_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state)
{
  state = layer_state_set_user(state);
  process_indicator_led_kb(state);

  return state;
}

__attribute__((weak))
bool process_indicator_led_user(layer_state_t state){
  return true;
}

bool process_indicator_led_kb(layer_state_t state)
{
  if(process_indicator_led_user(state))
  {
    // if on layer 0, turn on B0 LED, otherwise off.
    gpio_write_pin(B0, get_highest_layer(state) != 0);

    // if on layer 1, turn on B1 LED, otherwise off.
    gpio_write_pin(B1, get_highest_layer(state) != 1);

    // if on layer 2, turn on B2 LED, otherwise off.
    gpio_write_pin(B2, get_highest_layer(state) != 2);

    // if on layer 3, turn on B3 LED, otherwise off.
    gpio_write_pin(B3, get_highest_layer(state) != 3);
  }

  return true;
}
