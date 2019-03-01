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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xE401
#define DEVICE_VER      0x0E41
#define MANUFACTURER    That-Canadian
#define PRODUCT         Lets Split Eh?
#define DESCRIPTION     An on-board component Lets Split w/ USB-C

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* serial.c configuration for split keyboard */
//#define SOFT_SERIAL_PIN D0

#endif
