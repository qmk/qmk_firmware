/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2021 @dlford
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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// wiring of each half
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { B1, B3, B2, B6 }

#define DIODE_DIRECTION ROW2COL

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN D3
#define RGB_MATRIX_LED_COUNT 36
#define RGB_MATRIX_SPLIT { 18, 18 }
#define RGB_MATRIX_CENTER { 133, 54 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#undef LOCKING_RESYNC_ENABLE

/* Enables This makes it easier for fast typists to use dual-function keys */
#undef PERMISSIVE_HOLD
