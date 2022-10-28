/*
Copyright 2022 Greg Mathews

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

#define PRODUCT Frame 48

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
#define MATRIX_ROW_PINS \
    { B6, B2, B3, B1 }
#define MATRIX_COL_PINS \
    { B5, B4, E6, D7, C6, D4, D0 }

/* Encoder pins */
#define ENCODERS_PAD_A \
    { D3 }
#define ENCODERS_PAD_B \
    { D2 }

#define ENCODERS_PAD_A_RIGHT \
    { D3 }
#define ENCODERS_PAD_B_RIGHT \
    { D2 }

#define ENCODER_DIRECTION_FLIP

/* Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN. */
#define USE_SERIAL
#define SOFT_SERIAL_PIN F4 // or D1, D2, D3, E6
#define SELECT_SOFT_SERIAL_SPEED 0
