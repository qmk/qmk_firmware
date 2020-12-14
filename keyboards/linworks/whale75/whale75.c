/* Copyright 2020 Moritz Plattner
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
#include "whale75.h"

void matrix_init_kb(void) {
  matrix_init_user();
  led_init_ports();
}

/* Set lock LEDs as outputs */
void led_init_ports(void) {
    setPinOutput(A8);
    setPinOutput(A9);
    setPinOutput(A13);
}

/* Set lock LEDs to their states*/
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(A9, !led_state.num_lock);
        writePin(A13, !led_state.caps_lock);
        writePin(A8, !led_state.scroll_lock);
    }
    return true;
}