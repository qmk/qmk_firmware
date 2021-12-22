/*
Copyright 2021 Chris Broekema (broekema@gmail.com)

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

/* USB Device descriptor parameter */
#define VENDOR_ID    0xBEEF
#define PRODUCT_ID   0x6969
#define DEVICE_VER   0x0001
#define MANUFACTURER QMK

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { D1, D0, D4 }
#define MATRIX_COL_PINS { D7, E6, B4, B5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//#define JOYSTICK_AXES_COUNT 4
//#define JOYSTICK_BUTTON_COUNT 8
