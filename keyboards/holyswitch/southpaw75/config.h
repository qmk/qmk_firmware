/*
Copyright 2020 drewguy

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x484F // "HO" short for Holy Switch
#define PRODUCT_ID      0x5350 // "SP" short for Southpaw
#define DEVICE_VER      0x0001
#define MANUFACTURER    drewguy
#define PRODUCT         southpaw default

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 9

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

//                         0   1   2   3   4   5   6   7   8
#define MATRIX_ROW_PINS { B2, F0, C6, D4, D3, F1, D2, B5, D5 }
#define MATRIX_COL_PINS { B6, F7, F6, F5, F4, D0, D1, D7, B4 }

#define DIODE_DIRECTION COL2ROW
