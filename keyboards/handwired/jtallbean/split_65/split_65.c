/* Copyright 2020 jtallbean
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

#include "split_65.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // Set our LED pins as output
    setPinOutput(B0);
    writePinLow(B0);

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        writePin(B0, led_state.caps_lock);
    }
    return res;
}
