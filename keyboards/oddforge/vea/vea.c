/*
Copyright 2021 MajorKoos <github.com/majorkoos>

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
#include "vea.h"
#include "i2c_master.h"


void keyboard_pre_init_kb(void) {
    led_init_ports();
    keyboard_pre_init_user();
}

void led_init_ports(void) {
    setPinOutput(NUMLOCK_LED_PIN);
    setPinOutput(CAPSLOCK_LED_PIN);
    setPinOutput(SCROLLLOCK_LED_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(NUMLOCK_LED_PIN, led_state.num_lock);
        writePin(CAPSLOCK_LED_PIN, led_state.caps_lock);
        writePin(SCROLLLOCK_LED_PIN, led_state.scroll_lock);
    }
    return res;
}
