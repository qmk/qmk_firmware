/*
Copyright 2020 Yncognito

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
#define VENDOR_ID       0x7979
#define PRODUCT_ID      0x6602
#define DEVICE_VER      0x0001
#define MANUFACTURER    Yncognito
#define PRODUCT         Batpad

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

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
#define MATRIX_ROW_PINS { F4, C7 }
#define MATRIX_COL_PINS { F1, F0, D5, D3 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B5
#define DRIVER_LED_TOTAL 8
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
// #define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
