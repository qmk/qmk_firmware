/*
Copyright 2021 kb-elmo<mail@elmo.space>

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
#define VENDOR_ID    0xA68C
#define PRODUCT_ID   0x9879
#define DEVICE_VER   0x0001
#define MANUFACTURER kb-elmo
#define PRODUCT      Twelvekey

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D1, C4, D7 }
#define MATRIX_COL_PINS { C5, D0, B0, D6 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Backlight */
#define BACKLIGHT_PIN B1
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_ON_STATE 0

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
