/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com> <4sStylZ@protonmail.ch>

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
#include "quantum.h"

/*
 * Hardware function pre initialisation.
 * See https://docs.qmk.fm/#/custom_quantum_functions?id=example-keyboard_pre_init_user-implementation
 */
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(C3);
}

void matrix_init_kb(void) {

    // Flash the led 1 sec on startup.
    writePinHigh(C3);
    wait_ms(1000);
    writePinLow(C3);
}
