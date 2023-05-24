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
#define PRODUCT_ID   0x9F9F
#define DEVICE_VER   0x0001
#define MANUFACTURER Axolstudio
#define PRODUCT      Yeti

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */

#define MATRIX_ROW_PINS { C7, C6, B6, B5, B4 }
#define MATRIX_COL_PINS { F6, F5, F4, F1, F0, F7, D7, D6, D4, B3, B7, D0, D1, D2, D3, D5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
