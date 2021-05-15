/*
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
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER    alysaght
#define PRODUCT         ortho36

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { D1, B4, B5, B2 }
#define MATRIX_COL_PINS { B3, B1, F7, F6, F5, D0, D4, C6, D7, E6 }
#define UNUSED_PINS { D2, B0, F4, B6, B7, D5, C7, F1, F0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#define RGBLED_NUM 11
#define RGBLIGHT_ANIMATIONS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
