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
#define VENDOR_ID 0x0001
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER Zilliq
#define PRODUCT 3Key
#define DESCRIPTION My custom 3Key

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 3

/* 9Key PCB default pin-out */
#define MATRIX_ROW_PINS \
  { D4 }
#define MATRIX_COL_PINS \
  { F4, F5, F6 }

#define C6_AUDIO

#define UNUSED_PINS

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(IMPERIAL_MARCH)
#endif

/* ws2812 RGB LED */
//#define RGB_DI_PIN F7

//#define RGBLED_NUM 1  // Number of LEDs

/* COL2ROW or ROW2COL */
//#define DIODE_DIRECTION COL2ROW

//#define TAPPING_TERM 200

#endif
