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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x606A
#define DEVICE_VER      0x0002
#define MANUFACTURER    XeaL
#define PRODUCT         XeaLous Brown Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 13
#define DEBOUNCE 10
#define USB_POLLING_INTERVAL_MS 1
/* layer optimization */
#define LAYER_STATE_8BIT
#define MAX_LAYER 2

//debug scanrate
//#define DEBUG_MATRIX_SCAN_RATE
//debug scans taking longer than one ms
//#define BENCHMARK_MATRIX
#define MATRIX_IO_DELAY 15
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
#define MATRIX_ROW_PINS { D3, D2, D1, D0, D4 }
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5, B6, B2, B3, B1, F7, F6, F5, F4 }
#define UNUSED_PINS { }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
