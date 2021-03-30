/*
Copyright 2020 sh_xguitar
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
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x14BC
#define DEVICE_VER   0x0001
#define MANUFACTURER ASH
#define PRODUCT      XIIX

/* key matrix size */
#define MATRIX_ROWS 12
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
 */
#define MATRIX_ROW_PINS { C6, B6, B5, B4, D7, D0, D1, D2, D3, D5, D4, D6 }
#define MATRIX_COL_PINS { F1, F4, F5, F6, B0, B2, B1, B3, B7, C7 }
#define UNUSED_PINS

#define NUM_LOCK_LED_PIN E6
#define CAPS_LOCK_LED_PIN F0
#define SCROLL_LOCK_LED_PIN F7

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
