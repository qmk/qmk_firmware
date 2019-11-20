/* Copyright 2019 HELIAR MK
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

#include <print.h>
#include "wm1.h"


void keyboard_pre_init_kb(void)
{
    setPinOutput(D7);
    print("init LED output Pin D7");
    setPinOutput(D6);
    print("init LED output Pin D6");
    setPinOutput(D4);
    print("init LED output Pin D4");
}

bool led_update_kb(led_t led_state) {
    if (led_state.num_lock) {
        writePinLow(D7);
    } else {
        writePinHigh(D7);
    }
    if (led_state.caps_lock) {
        writePinLow(D6);
    } else {
        writePinHigh(D6);
    }
    if (led_state.scroll_lock) {
        writePinLow(D4);
    } else {
        writePinHigh(D4);
    }
    return led_update_user(led_state);
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}
