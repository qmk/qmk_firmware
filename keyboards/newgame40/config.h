/*
Copyright 2018 Go Takigawa <gotakigawa@gmail.com>

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
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    GoTakigawa
#define PRODUCT         NEWGAME40

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* pin-out */
#define MATRIX_ROW_PINS { F7, B1, B3, B2 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN F6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 25    // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#ifndef IOS_DEVICE_ENABLE
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #define RGBLIGHT_LIMIT_VAL 130
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #define RGBLIGHT_LIMIT_VAL 45
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

