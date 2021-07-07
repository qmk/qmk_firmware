/* Copyright 2021 Samuel Lu
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

#include "xt65e.h"

void keyboard_pre_init_kb (void) {
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:
            writePinHigh(B0);
            writePinLow(B1);
            writePinLow(B2);
            break;
        case 2:
            writePinLow(B0);
            writePinHigh(B1);
            writePinLow(B2);
            break;
		case 3:
            writePinLow(B0);
            writePinLow(B1);
            writePinHigh(B2);
            break;
        default:
            writePinHigh(B0);
            writePinHigh(B1);
            writePinHigh(B2);
            break;
    }
	return state;
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    writePin(E6, led_state.caps_lock);
  }
  return res;
}

// __attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
  // writePin(B0, layer_state_cmp(state, 1));
  // writePin(B1, layer_state_cmp(state, 2));
  // writePin(B2, layer_state_cmp(state, 3));
  // return state;
// }