/* Copyright 2020 Maarten Dekkers <maartenwut@gmail.com>
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
#include "gh80_3700.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

  matrix_init_user();
  led_init_ports();
}

void led_init_ports(void) {
  setPinOutput(E6);
  setPinOutput(B1);
  setPinOutput(D0);
  setPinOutput(D1);
  setPinOutput(F0);
  
  writePinHigh(E6);
  writePinHigh(B1);
  writePinHigh(D0);
  writePinHigh(D1);
  writePinHigh(F0);
}

bool led_update_kb(led_t led_state) {
  if(led_update_user(led_state)) {
    writePin(E6, !led_state.num_lock);
  }

  return true;
}