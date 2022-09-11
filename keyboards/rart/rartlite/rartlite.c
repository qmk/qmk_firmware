/* Copyright 2021 Alabahuy
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
#include "rartlite.h"

void keyboard_pre_init_kb(void) {
  setPinOutput(B1);
  
  keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    writePin(B1, layer_state_cmp(state, 1));
    return layer_state_set_user(state);
}
