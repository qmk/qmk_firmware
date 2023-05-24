/* Copyright 2021 Dino Fizzotti
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
#include "v1.h"

void keyboard_pre_init_kb(void) {
    // Immediately set the LED pin as an output and set it ON
    setPinOutput(A15);
    writePinHigh(A15);
    
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Blink the LED so we know everything is running OK
    // Finish with LED OFF
    writePinLow(A15);
    wait_ms(100);
    writePinHigh(A15);
    wait_ms(100);
    writePinLow(A15);
    
    keyboard_post_init_user();
}
