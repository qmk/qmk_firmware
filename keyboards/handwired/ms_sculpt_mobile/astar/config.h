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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Microsoftplus

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 18

#define PRODUCT         sculpt mobile astar
                        /*0   1   2   3    4   5  6   7   8 */
#define MATRIX_ROW_PINS {D7, C6, D4, D0, D1, D3, D2, E2}
/*                        A  B   C   D   E   F   G   H   I   J  K   L   M   N   O   P   Q  R  */
#define MATRIX_COL_PINS {B4, B5, E6, B7, B6, D6,  C7, F7, F6, F4,F5, F1,F0, D5, B0, B1, B2, B3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST


