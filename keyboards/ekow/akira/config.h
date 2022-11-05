/*
Copyright 2022 eugenepy

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
#define VENDOR_ID 0x4B59 // KY
#define PRODUCT_ID 0x414B // AK
#define DEVICE_VER 0x0000
#define MANUFACTURER Keeboyzlab
#define PRODUCT AKIRA

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

// M60-A PCB default pin-out
#define MATRIX_ROW_PINS \
    { B0, B1, B2, B10, B11 }
#define MATRIX_COL_PINS \
    { B12, B13, B14, B15, A8, A9, A10, A15, B3, B4, B5, B6, B7, B8, B9 }

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
/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 3
