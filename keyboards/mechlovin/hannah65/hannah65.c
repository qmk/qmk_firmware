/* Copyright 2020 Team Mechlovin
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

#include "hannah65.h"

void matrix_init_kb(void) {
    matrix_init_user();
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(B9);
    writePinLow(B9);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B9, led_state.caps_lock);
    }

    return true;
}
