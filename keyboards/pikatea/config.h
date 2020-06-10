/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7069
#define PRODUCT_ID      0x706d
#define DEVICE_VER 		0x0001
#define MANUFACTURER    Pikatea Keyboards
#define PRODUCT         Pikatea Macropad
#define DESCRIPTION     Pikatea Macropad 5 Button 1 Knob GB1

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

/* 9Key PCB default pin-out */
#define MATRIX_COL_PINS { C6, D7, B5, B4, E6 }
#define MATRIX_ROW_PINS { F7 }
#define UNUSED_PINS

/* ws2812 RGB LED */

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D4 }
#define ENCODER_RESOLUTION 4

#endif
