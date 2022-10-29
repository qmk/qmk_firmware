/*
Copyright 2021 Mechlovin' Studio

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
#define MATRIX_ROW_PINS { A6, A1, A0, C15, C14, C13 }
#define MATRIX_COL_PINS { A4, A3, A2, A5, B9, B8, B7, B6, B5, B4, B3, A15, A10, A9, A8, B15, B14, B13, B12, B11, B10 }

#define LED_NUM_LOCK_PIN B1
#define LED_CAPS_LOCK_PIN A14
#define LED_SCROLL_LOCK_PIN B2
#define LED_PIN_ON_STATE 0 

#define ENCODERS_PAD_A { A7 }
#define ENCODERS_PAD_B { B0 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 10
#define FEE_PAGE_COUNT 4