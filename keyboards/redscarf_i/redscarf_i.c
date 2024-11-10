/* Copyright 2019 Ben Weakley
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
  // initialize top row leds
  gpio_set_pin_output(F6);
  gpio_set_pin_output(F5);
  // and then turn them off
  gpio_write_pin_high(F6);
  gpio_write_pin_high(F5);

  keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case 1:
      gpio_write_pin_high(F6);
      gpio_write_pin_low(F5);
      break;
    case 2:
      gpio_write_pin_low(F6);
      gpio_write_pin_high(F5);
      break;
    default:
      gpio_write_pin_high(F6);
      gpio_write_pin_high(F5);
      break;
  }
  return state;
}
