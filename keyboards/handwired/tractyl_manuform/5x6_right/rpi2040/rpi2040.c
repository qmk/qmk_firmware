/* Copyright 2020 Pascal Jaeger <pascal.jaeger@leimstift.de>
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

#include "quantum.h"

#ifdef RESET_PIN
void matrix_scan_sub_kb(void) {
    debug_enable = true;
    // for the double tap action of the reset pin
    static bool     last_state   = false;
    static uint8_t  tap_counter  = 0;
    static uint16_t reset_timer  = 0;
    static uint16_t debounce_timer = 0;
    bool            reset_pin_fe = readPin(RESET_PIN) < last_state && timer_elapsed(debounce_timer) > 50;

    // switch pin on
    setPinOutput(RESET_PIN);
    writePinHigh(RESET_PIN);

    if (reset_pin_fe) {
        if (tap_counter == 0) {
            reset_timer = timer_read();
        }
        debounce_timer = timer_read();
        tap_counter++; // count falling edges
    }

    if (timer_elapsed(reset_timer) > RESET_PIN_DOUBLE_TAP_RESET_TIMEOUT) {
        reset_timer = timer_read();
        tap_counter = 0;
    } else {
        if (tap_counter >= 2) {
            dprintf("Bootloader jumps\n");
            reset_keyboard();
        }
    }
    // update last state
    last_state = readPin(RESET_PIN);
}
#endif
