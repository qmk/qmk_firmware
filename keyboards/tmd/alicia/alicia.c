/* Copyright 2019 themillerdave
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
#include "alicia.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*

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

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}


*/

/* Indicator lights in the bottom left.  Scroll (Top), Num (Middle), Caps (Bottom)
*   NOTE: if you want to use the MOSI, C6, or B7 debug header pins - you cannot use the LED indicators and must comment / remove this method override
*/ 

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        if (led_state.num_lock) {
            writePinLow(C6);
        } else {
            writePinHigh(C6);
        }
        if (led_state.caps_lock) {
            writePinLow(B2);
        } else {
            writePinHigh(B2);
        }
        if (led_state.scroll_lock) {
            writePinLow(B7);
        } else {
            writePinHigh(B7);
        }
    }
    return true;
}