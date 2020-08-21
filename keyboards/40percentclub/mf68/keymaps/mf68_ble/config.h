/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/* Overrides for Feather 32u4 Bluefruit */

/* USB Device descriptor parameter */
#undef DESCRIPTION
#define DESCRIPTION     Magicforce 68 BLE

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef UNUSED_PINS
#define MATRIX_ROW_PINS { D1, D0, C6, D7, B5, B6, B7, D6 }
#define MATRIX_COL_PINS { C7, F7, F6, F5, F4, F1, F0, D2, D3 }
#define UNUSED_PINS {B5}
