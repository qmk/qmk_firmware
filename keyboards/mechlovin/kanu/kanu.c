/* Copyright 2020 Team Mechlovin'
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
  setPinOutput(B2);
  setPinOutput(D0);
  setPinOutput(D1);
  setPinOutput(D2);

}
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B2, led_state.caps_lock);
    }

    return true;
}

__attribute__((weak))
layer_state_t layer_state_set_user(layer_state_t state) {
  // if on layer 1, turn on D2 LED, otherwise off.
  writePin(D2, get_highest_layer(state) == 1);
  // if on layer 2, turn on D1 LED, otherwise off.
  writePin(D1, get_highest_layer(state) == 2);
  // if on layer 3, turn on D0 LED, otherwise off.
  writePin(D0, get_highest_layer(state) == 3);
  return state;
}
