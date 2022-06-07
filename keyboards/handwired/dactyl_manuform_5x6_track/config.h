/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#define PRODUCT_ID      0x3636
#define DEVICE_VER      0x0001
#define PRODUCT         Dactyl-Manuform (5x6)
/* USB Device descriptor parameter */
#define VENDOR_ID       0x444D
#define MANUFACTURER    ASmith

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { B7, D5, C7, F1, F0, B6 }
// Right
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4 }
//Left
//#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS { D3, B0, F4, F5, F6 }

#define DIODE_DIRECTION COL2ROW

#define OLED_DISPLAY_128X32 

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2


#define ROTATIONAL_TRANSFORM_ANGLE  -25
#define POINTING_DEVICE_INVERT_X
#define PMW3360_CPI 400

#define POINTING_DEVICE_RIGHT
#define PMW3389_CS_PIN F7

