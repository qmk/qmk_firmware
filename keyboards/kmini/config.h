/* Copyright 2018 Evy Dekkers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6050
#define DEVICE_VER      0x0104
#define MANUFACTURER    Revo
#define PRODUCT         KMAC Kmini

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/*
 * Keyboard Matrix Assignments
 * The KMAC uses a demultiplexer for some of the cols.
 * See matrix.c for more details.
*/
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
//#define DIODE_DIRECTION

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3
// #define BACKLIGHT_PIN B7
// #define BACKLIGHT_BREATHING

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#endif
