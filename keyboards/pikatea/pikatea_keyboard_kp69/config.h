/*
Copyright 2022 Jack Kester

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
#define VENDOR_ID    0x5049
#define PRODUCT_ID   0x0019
#define DEVICE_VER   0x0001
#define MANUFACTURER Jack_Kester
#define PRODUCT      Pikatea Keyboard KP69

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

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
#define MATRIX_COL_PINS { F1,B0,C6,C7,B6,B5,D6,D4,D5,D3,D2,B7,B3,B1,B2 }
#define MATRIX_ROW_PINS { E6, F0, F6, F5, F4, NO_PIN }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoder setup */
#define ENCODERS 1

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { D7 }
#define ENCODER_RESOLUTION 4

//column then row
#define ENCODERS_CW_KEY  { { 1, 5 } }
#define ENCODERS_CCW_KEY { { 0, 5 } }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
