/*
Copyright 2020 April Aplyard <alex.fragiou@gmail.com>

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
#define VENDOR_ID       0xE0E0
#define PRODUCT_ID      0x0040
#define DEVICE_VER 		0x0002
#define MANUFACTURER    Aplyard
#define PRODUCT         Aplx6

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* 9Key PCB default pin-out */
#define MATRIX_ROW_PINS { B4, B5 }
#define MATRIX_COL_PINS { C6, D7, E6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

/* Encoder */
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 50
