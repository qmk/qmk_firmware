/*
Copyright 2019 MechMerlin <mechmerlin@gmail.com>

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
#define VENDOR_ID       0x444B // Duck ("DK")
#define PRODUCT_ID      0x4F52 // Orion ("OR")
#define DEVICE_VER      0x0002
#define MANUFACTURER    Duck
#define PRODUCT         Orion V3

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

#undef BACKLIGHT_PIN
#define BACKLIGHT_PINS { B1, B2, B3, E6 }
#define BACKLIGHT_LED_COUNT 4
#define BACKLIGHT_LEVELS 10

#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN D6
#define RGBLED_NUM 18

/* Set to top left most key */
#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 10

#define TAPPING_TERM 200
