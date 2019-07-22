/*
Copyright 2019 Crokto

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
#define VENDOR_ID       0x6D6D
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    MetaMechs
#define PRODUCT         Daishi
#define DESCRIPTION     Compact Battlecruiser

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 18

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
#define MATRIX_ROW_PINS { D6, D7, E0, E1, C0, C1, C2 }
#define MATRIX_COL_PINS { E6, E7, E3, B0, B1, B2, A6, A5, A4, A3, A2, A1, A0, F7, F6, F5, F4, F3 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Set up rotary encoder */
#define ENCODERS_PAD_A { F1 }
#define ENCODERS_PAD_B { F0 }
#define ENCODER_RESOLUTION 2

/* Set delay for tap_code on rotary encoder */
#define TAP_CODE_DELAY 10
