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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    delayedbrain
#define PRODUCT         d48tr
#define DESCRIPTION     A light weight keyboard with trackball

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { D2, D3, F6, F7 }
#define MATRIX_COL_PINS { B1, B3, B2, B6, B5, B4, E6, D7, C6, D4, F5, F4 }

/*Trackball's I2C address ("0X4A" is default)*/
#define TRACBALL_ADDR 0X4A

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

#endif
