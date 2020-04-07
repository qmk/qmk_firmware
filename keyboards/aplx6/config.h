/*
Copyright 2020 April Aplyard <alex.fragiou@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xE0E0
#define PRODUCT_ID      0x0030
#define DEVICE_VER      0x0001
#define MANUFACTURER    Aplyard
#define PRODUCT         Aplx6
#define DESCRIPTION     Aplx6 MediaPad

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* pin-out */
#define MATRIX_ROW_PINS { B5, F6 }
#define MATRIX_COL_PINS { B6, F5, F4 }
#define UNUSED_PINS


/* ws2812 RGB LED */
//#define RGB_DI_PIN X

//#define RGBLIGHT_ANIMATIONS
//#define RGBLED_NUM X    // Number of LEDs


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

#endif
