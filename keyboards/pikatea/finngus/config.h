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


#define VENDOR_ID       0x5049
#define PRODUCT_ID      0x0014
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jack_Kester
#define PRODUCT         Pikatea FinnGus

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { B1, B3, B2 }
#define MATRIX_ROW_PIN_COUNT 3
/* It is arbitrary, but we use a grey code to limit transitions in the external chip.
Only one bit changes per row change, so there should be no timing related digital glitching */
#define MATRIX_ROW_MASKS { 4, 0, 2, 3, 1, 5, 7, 6 }
/*  Row num : bit mask : CD4051B pin grounded
 *  0 : 100 : 4
 *  1 : 000 : 0
 *  2 : 010 : 2
 *  3 : 011 : 3
 *  4 : 001 : 1
 *  5 : 101 : 5
 *  6 : 111 : 7
 *  7 : 110 : 6
 */

#define MATRIX_COL_PINS { D3, D2, D7, E6, F6, B6, F7, B4, B5 }

#define MATRIX_IO_DELAY 5

/* DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#define ENCODER_RESOLUTION 4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 10

