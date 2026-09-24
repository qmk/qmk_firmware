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

void keyboard_pre_init_kb(void) {
  // Set our LED pins as output
  gpio_set_pin_output(C3);

  keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // Flash the led 1 sec on startup.
    gpio_write_pin_high(C3);
    wait_ms(1000);
    gpio_write_pin_low(C3);

    matrix_init_user();
}
