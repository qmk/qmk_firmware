/*
Copyright 2021 s8erdude

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
#define VENDOR_ID    0xB33F
#define PRODUCT_ID   0x58E4
#define DEVICE_VER   0x0001
#define MANUFACTURER s8erdude
#define PRODUCT      gorthage_truck

/* key matrix size */
#define MATRIX_ROWS 8
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
#define MATRIX_ROW_PINS { C6, B6, B5, B4, C7, B3, B7, D7}
#define MATRIX_COL_PINS { F0, F1, F4, F7, D6, E6, B0, B1, B2}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

// LEFT -> RIGHT
// D5, D3, D2
#define LED_NUM_LOCK_PIN D5
#define LED_CAPS_LOCK_PIN D3
#define LED_SCROLL_LOCK_PIN D2

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F6 }
