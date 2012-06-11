/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#ifndef LAYER_H
#define LAYER_H 1

#include <stdint.h>

extern uint8_t default_layer;
extern uint8_t current_layer;

/* return keycode for switch */
uint8_t layer_get_keycode(uint8_t row, uint8_t col);

/* process layer switching */
void layer_switching(uint8_t fn_bits);

#endif
