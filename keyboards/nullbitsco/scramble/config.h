/*
Copyright 2020 Jay Greco

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
#define VENDOR_ID       0x6E61
#define PRODUCT_ID      0x6062

#define DEVICE_VER      0x0001
#define MANUFACTURER    nullbits
#define PRODUCT         SCRAMBLE

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

#define DIRECT_PINS {{D4,D5,B1}, {C3,C2,C1}}

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 10

/* Optional encoder pins */
#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D7 }
#define TAP_CODE_DELAY 10
