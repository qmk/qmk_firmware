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


#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
// TODO: share these strings with usbconfig.h
// Edit usbconfig.h to change these.
#define MANUFACTURER    Kprepublic
#define PRODUCT         jj4x4

/* matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { B5, B0, B3, B4 }
#define MATRIX_COL_PINS { A1, A0, A2, A3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_LEVELS 12
// #define BACKLIGHT_BREATHING  // works, but BL_TOGG might not work

#define TAPPING_TOGGLE 3

#define NO_UART 1

/* RGB underglow */
// The RGB_DI_PIN value seems to be shared between all PS2AVRGB boards.
// The same pin is used on the JJ40, at least.
#define RGBLED_NUM 5
#define RGB_DI_PIN E2 // NOTE: for PS2AVRGB boards, underglow commands are sent via I2C to 0xB0.
#define RGBLIGHT_ANIMATIONS
