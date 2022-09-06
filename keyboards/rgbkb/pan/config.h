/*Copyright 2020 RGBKB

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

#define VENDOR_ID       0x5247  // "RG" - RGBKB
#define PRODUCT_ID      0x8C9C  // Pan
#define DEVICE_VER      0x0002
#define MANUFACTURER    RGBKB
#define PRODUCT         Pan

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 13

#define ENCODER_RESOLUTION 4
#define RGBLED_NUM 64
#define RGBLIGHT_ANIMATIONS
#define DRIVER_LED_TOTAL RGBLED_NUM

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGBLIGHT_LIMIT_VAL 120
#define USB_MAX_POWER_CONSUMPTION 500

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
