/* Copyright 2020 sekigon-gonnoc
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

#include "grs_70ec.h"

void led_on(void) {
    setPinOutput(D2);
    writePinHigh(D2);
}

void led_off(void) { writePinLow(D2); }

void keyboard_post_init_kb(void) {
    led_on();

    keyboard_post_init_user();
}

void keyboard_pre_init_kb(void) {
    // Turn on extern circuit
    setPinOutput(F7);
    writePinHigh(F7);

    keyboard_pre_init_user();
}
