/*
Copyright 2020 kb-elmo

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
#define VENDOR_ID    0x525C
#define PRODUCT_ID   0xC89F
#define DEVICE_VER   0x0001
#define MANUFACTURER Axolstudio
#define PRODUCT      Helpo

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

/* Keyboard Matrix Assignments */

#define MATRIX_ROW_PINS { A2, A3, A4, A5 }
#define MATRIX_COL_PINS { A1, B4, B3, B2, B1 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
