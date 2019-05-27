/*
Copyright 2018 HnahKB

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


#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    QuangVuz
#define PRODUCT         Hpah
#define DESCRIPTION     Miss you Hnah

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* pin-out */
#define MATRIX_ROW_PINS { B3, B0, F7, F6, F5 }
#define MATRIX_COL_PINS { B2, B1, B7, D0 }
#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN E6
#define RGBLIGHT_TIMER
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10    // Number of LEDs

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 4
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


