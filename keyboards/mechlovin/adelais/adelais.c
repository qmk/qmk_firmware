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

#include "adelais.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(B2);
    writePinLow(B2);
    setPinOutput(C15);
    writePinLow(C15);
    setPinOutput(B9);
    writePinLow(B9);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B2, led_state.caps_lock);
        writePin(B9, led_state.scroll_lock);
        writePin(C15, led_state.num_lock);
    }

    return true;
}
