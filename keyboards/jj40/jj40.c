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

#include "jj40.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "quantum.h"

__attribute__ ((weak))
void matrix_scan_user(void) {
    /* Nothing to do here... yet */
}

void matrix_init_kb(void) {

  // Call the keymap level matrix init.
  matrix_init_user();

  // Set our LED pins as output
  DDRB |= (1<<6);
}

void matrix_init_user(void) {
}