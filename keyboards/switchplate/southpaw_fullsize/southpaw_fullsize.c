/* Copyright 2020 Ryota Goto
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

#include "southpaw_fullsize.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

#define INDICATOR_NUM D3
#define INDICATOR_CAPS D4
#define INDICATOR_SCR D5


void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // D3 Numlock, D4 Capslock, D5 Scrlock
    setPinOutput(INDICATOR_NUM);
    setPinOutput(INDICATOR_CAPS);
    setPinOutput(INDICATOR_SCR);
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    writePin(INDICATOR_NUM, !led_state.num_lock);
    writePin(INDICATOR_CAPS, !led_state.caps_lock);
    writePin(INDICATOR_SCR, !led_state.scroll_lock);
    return true;
}

