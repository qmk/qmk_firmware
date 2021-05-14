/*
Copyright 2021 stevendlander

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
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    stevendlander
#define PRODUCT         Unicomp Mini M

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 16

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
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F3, F2, F1, F0, E6, E7, B0, B1 }
#define MATRIX_COL_PINS { C7, C6, C5, C4, C3, C2, C1, C0, E1, E0, D7, B7, D5, D4, D3, D2 }
#define UNUSED_PINS

#define LED_PIN_ON_STATE 0
#define LED_NUM_LOCK_PIN B6
#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN B4

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed (5 is default) */
#define DEBOUNCE 5

/* The Mini M has no diodes */
#define MATRIX_HAS_GHOST
