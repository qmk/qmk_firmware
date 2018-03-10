/*
Copyright 2017 Cole Markham

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6061
#define DEVICE_VER      0x0001
#define MANUFACTURER    WoodKeys.click
#define PRODUCT         Meira
#define DESCRIPTION     Low-profile Ortholinear Compact keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION CUSTOM_MATRIX

#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PWM_MAP {2, 4, 8, 16, 40, 55, 70, 128, 200, 255}

#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
#define RGBLED_NUM 15    // Number of LEDs

#endif
