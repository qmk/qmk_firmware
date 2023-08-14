/*
This is the c configuration file for the keymap

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* key matrix size     */
/* Rows are doubled-up */
#undef MATRIX_ROWS
#undef MATRIX_COLS
#define MATRIX_ROWS 10
#define MATRIX_COLS 5

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F7, B1, B3, B2, B6 }

#define USB_MAX_POWER_CONSUMPTION 50

/* Select hand configuration */

/* #define MASTER_LEFT */
// #define MASTER_RIGHT
#define EE_HANDS

/* ws2812 RGB LED */
#undef RGBLED_NUM
#define WS2812_DI_PIN D3

#define RGBLED_NUM 50
#endif
