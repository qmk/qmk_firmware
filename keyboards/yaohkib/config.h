/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 jabbato

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
//#define VENDOR_ID       0x44d6
//#define PRODUCT_ID      0x0001
//#define DEVICE_VER      0x0001
//#define MANUFACTURER    jabbato
//#define PRODUCT         YAOHKIB

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }

// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1}

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define USE_SERIAL

//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
