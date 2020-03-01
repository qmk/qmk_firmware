/* Copyright 2019 Andy Lee <alee@alittlepeacemusic.com>
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
#include "verd.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    led_init_ports();
}

void led_init_ports(void) {
	setPinOutput(C7);
	writePinHigh(C7);
	setPinOutput(E6);
	writePinHigh(E6);
}

bool led_update_kb(led_t led_state) {
    writePin(C7, !led_state.caps_lock);
    writePin(E6, !led_state.num_lock);
    return true;
}
