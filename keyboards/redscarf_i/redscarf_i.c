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

#include "redscarf_i.h"

void keyboard_pre_init_kb(void) {
  // initialize top row leds
  setPinOutput(F7);
  setPinOutput(F6);
  setPinOutput(F5);
  // and then turn them off
  writePinHigh(F7);
  writePinHigh(F6);
  writePinHigh(F5);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F7, !led_state.num_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case 1:
      writePinHigh(F6);
      writePinLow(F5);
      break;
    case 2:
      writePinLow(F6);
      writePinHigh(F5);
      break;
    default:
      writePinHigh(F6);
      writePinHigh(F5);
      break;
  }
  return state;
}
