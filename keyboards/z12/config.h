/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>

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

#pragma once

#include "config_common.h"

#define ENCODERS_PAD_A { B5, B6 }
#define ENCODERS_PAD_B { B4, B2 }

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/*Keyboard Matrix Assignments */

#define DIRECT_PINS { \
    { NO_PIN, E6, C6, NO_PIN }, \
    { D2, D7, D4, D3 }, \
    { F7, B1, B3, NO_PIN }, \
    { F6, F5, F4, NO_PIN } \
}

#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
