/*
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
#define VENDOR_ID       0x4342 // CB
#define PRODUCT_ID      0x8785
#define DEVICE_VER      0x0001
#define MANUFACTURER    CherryB.Studio
#define PRODUCT         CB87RGB

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 *                        0   1   2   3   4   5   6   7   8   9
*/
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B7, D0, D1, D2, D3, F6 }
#define MATRIX_COL_PINS { D5, D4, D6, D7, B4, B5, F5, C6, C7, F7 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RGB_DI_PIN E6
#define DRIVER_LED_TOTAL 92
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_KEYPRESSES


