/*
Copyright 2021 James Sa <james.sa.2013@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0805

#define MANUFACTURER    JSA
#define PRODUCT         Angel
/* USB Version in Binary-coded decimal: 0xJJMN where
 * JJ is the major number, M is minor, N is sub minor. */
#define DEVICE_VER      0x0100  // Version 1.00: hand-wire


/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/*
 * Keyboard Matrix Assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 */
#define MATRIX_ROW_PINS { B6, B2, B5, B4 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, D4, C6, D7, E6, B3, B1, F7, F6, F5 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

// https://docs.qmk.fm/using-qmk/software-features/tap_hold
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
#define MATRIX_HAS_GHOST
