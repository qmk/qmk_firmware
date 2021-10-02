/*
Copyright 2021 Kyle McCreery
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
#define VENDOR_ID       0x6653
#define PRODUCT_ID      0x6565
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mokey
#define PRODUCT         ginkgo 65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
                       /*  1  2   3   4   5   6   7   8   9   10  11  12  13  14  15  16 */
#define MATRIX_ROW_PINS { F6, B2, F4, E6, B3 }
#define MATRIX_COL_PINS { C7, F7, B7, F5, B0, F1, D0, D1, D2, D3, D5, D4, D6, D7, B4, B1 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
