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

#include "bb.h"


void led_init_ports(void) {
  setPinOutput(C0);
  setPinOutput(D0);
  setPinOutput(D1);
  setPinOutput(C1);
  setPinOutput(C6);
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(D1, layer_state_cmp(state, 1));
    writePin(D0, layer_state_cmp(state, 2));
    writePin(C1, layer_state_cmp(state, 3));
    writePin(C0, layer_state_cmp(state, 4));
    writePin(C6, layer_state_cmp(state, 5));

    return state;
}
