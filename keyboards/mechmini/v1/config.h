/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xCA40
#define DEVICE_VER      0x0001
// TODO: share these strings with usbconfig.h
// Edit usbconfig.h to change these.
#define MANUFACTURER    MECHKEYS
#define PRODUCT         Mechmini
#define DESCRIPTION     40% modular keyboard

/* matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { B0, B1, B2, B3 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4 }
#define DIODE_DIRECTION COL2ROW

#define NO_UART 1

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

/* RGB underglow */
// The RGB_DI_PIN value seems to be shared between all PS2AVRGB boards.
// The same pin is used on the JJ40, at least.
#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN E2
