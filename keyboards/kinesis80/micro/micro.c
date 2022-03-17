/* Copyright 2019 DmNosachev
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

#include "micro.h"

void matrix_init_kb(void) {
	setPinOutput(NUM_LOCK_LED_PIN);
  setPinOutput(CAPS_LOCK_LED_PIN);
  setPinOutput(SCROLL_LOCK_LED_PIN);
  
  writePinHigh(NUM_LOCK_LED_PIN);
  writePinHigh(CAPS_LOCK_LED_PIN);
  writePinHigh(SCROLL_LOCK_LED_PIN);
  
	matrix_init_user();
}

bool led_update_kb(led_t led_state) {
bool res = led_update_user(led_state);
    if(res) {
        writePin(NUM_LOCK_LED_PIN, !led_state.num_lock);
        writePin(CAPS_LOCK_LED_PIN, !led_state.caps_lock);
        writePin(SCROLL_LOCK_LED_PIN, !led_state.scroll_lock);
    }
    return res;
}

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*
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
*/