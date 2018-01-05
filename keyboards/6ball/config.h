/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    That-Canadian
#define PRODUCT         6-Ball
#define DESCRIPTION     6-Ball Macropuck

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

/* pin-out */
#define MATRIX_ROW_PINS { F5 }
#define MATRIX_COL_PINS { F4, D4, B5, B6, B2, F6 }
#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN F7
#define RGBLIGHT_TIMER
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 6    // Number of LEDs
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

#endif
