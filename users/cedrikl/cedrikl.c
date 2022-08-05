/* Copyright 2021 Cedrik Lussier @cedrikl
.* Directly inspired from the work of jonavin https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/ansi/keymaps/jonavin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include QMK_KEYBOARD_H
#include "cedrikl.h"

// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (host_keyboard_led_state().num_lock != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}


// INITIAL STARTUP

void keyboard_post_init_user(void) {
    #ifdef STARTUP_NUMLOCK_ON
        activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOC_ON
}
