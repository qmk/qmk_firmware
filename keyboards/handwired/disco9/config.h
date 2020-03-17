/*
Copyright 2019 zk-phi

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
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    zk-phi
#define PRODUCT         disco9
#define DESCRIPTION     An ortho macropad with 9 keys and 21 backlights

/* key matrix */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { D4, C6, D7 }
#define MATRIX_COL_PINS { F4, F5, F6 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* rgblight */
#define RGB_DI_PIN D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 21
#endif
#ifdef RGB_MATRIX_ENABLE
#    define DRIVER_LED_TOTAL 21
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#endif
