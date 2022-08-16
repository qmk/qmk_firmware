/*
Copyright 2021 Evelien Dekkers

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

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {D0,C2,C5,C6}
#define MATRIX_COL_PINS {C4,C7,B7,B6,B5,B2,B1,B0,D6,D5,D4,D3,D2}
#define UNUSED_PINS

#define ENCODERS_PAD_A { B3 }
#define ENCODERS_PAD_B { B4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Backlight configuration
 */

#define QMK_ESC_OUTPUT C4 // usually COL
#define QMK_ESC_INPUT C6 // usually ROW
#define QMK_LED D1

#define LED_CAPS_LOCK_PIN D1
#define LED_PIN_ON_STATE 0
