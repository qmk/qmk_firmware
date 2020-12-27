/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include "twenty_four_key.h"

/* LEDs on the top row (4 round buttons) 
 * First button Left - D4, backlight with the rest of the LEDs under the keys
 * 2nd - D0
 * 3rd - D1
 * 4th - D6
 *
*/

void keyboard_pre_init_kb(void) {
    led_init_ports();
    writePinLow(D0);
    writePinLow(D1);
    writePinLow(D6);
    keyboard_pre_init_user();
}

void led_init_ports(void) {
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D6);
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(D0, led_state.num_lock);
        writePin(D1, led_state.caps_lock);
        writePin(D6, led_state.scroll_lock);
    }
    return true;
}
