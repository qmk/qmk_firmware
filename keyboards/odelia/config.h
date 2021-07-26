/*
Copyright 2020 kb-elmo<mail@elmo.space>

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
#define VENDOR_ID    0x6BE3
#define PRODUCT_ID   0xA129
#define DEVICE_VER   0x0001
#define MANUFACTURER InterpolKeeb
#define PRODUCT      Odelia

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/* Keyboard Matrix Assignments */

#define MATRIX_ROW_PINS {B3, B7, B1, B2, B0, F4, F0, F1, D4, B6}
#define MATRIX_COL_PINS {B5, B4, D7, D6, E6, D0, D1, D2, D3, D5}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
