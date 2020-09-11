/*
Copyright 2020 Jorge Briones <hola@keeblounge.com>

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

#include "config_common.h" // incluye archivo de configuracion comun

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B4C //KL
#define PRODUCT_ID      0x4334 // C4
#define DEVICE_VER      0x0001 //0001
#define MANUFACTURER    Keeblounge
#define PRODUCT         Concord45

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS {D3, C6, B2, B6}
#define MATRIX_COL_PINS {D2, D1, D0, D4, D7, E6, B4, B5, F6, F7, B1, F4, F5, B3}


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW //default

#define TAPPING_TERM 200 //default
