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
#define PRODUCT         affinity
#define DESCRIPTION     An 4x4 macropad with spectrum analyzer ic

/* key matrix */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7 }
#define DIODE_DIRECTION COL2ROW

/* msgeq7 */
#define MSGEQ7_OUT_PIN B5
#define MSGEQ7_RST_PIN B2
#define MSGEQ7_STROBE_PIN B6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* rgblight */
#define RGB_DI_PIN D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 16
#endif
