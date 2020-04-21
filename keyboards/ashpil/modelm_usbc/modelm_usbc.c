/* Copyright 2019 ashpil
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
 * along with this program.  If not, see <http://www./gnu.org/licenses/>.
 */
#include "modelm_usbc.h"

void keyboard_pre_init_kb(void) {
  /* Setting status LEDs pins to output and +5V (off) */
  setPinOutput(D5);
  setPinOutput(D6);
  setPinOutput(D7);
  writePinHigh(D5);
  writePinHigh(D6);
  writePinHigh(D7);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(D5, !led_state.num_lock);
        writePin(D6, !led_state.caps_lock);
        writePin(D7, !led_state.scroll_lock);
    }
    return true;
}
