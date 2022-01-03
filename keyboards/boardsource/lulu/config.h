/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

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

#define VENDOR_ID       0x4273
#define PRODUCT_ID      0x7685
#define DEVICE_VER      0x0000
#define MANUFACTURER    Boardsource
#define PRODUCT         lulu

#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS {C6, D7, E6, B4, B5}

// wiring of each half
#define MATRIX_COL_PINS {F6, F7, B1, B3, B2, B6}
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define SPLIT_USB_DETECT
#define RGB_DI_PIN D3

#define ENCODERS_PAD_A { F0 }
#define ENCODERS_PAD_B { F1 }
#define ENCODERS_PAD_A_RIGHT { F0 }
#define ENCODERS_PAD_B_RIGHT { F1 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
#define DIODE_DIRECTION COL2ROW
#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGBLED_NUM 70  // Number of LEDs
    #define DRIVER_LED_TOTAL RGBLED_NUM
    #define RGB_MATRIX_SPLIT { 35, 35 }
    #define SPLIT_TRANSPORT_MIRROR
    #define RGBLIGHT_LIMIT_VAL 150
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_BAND_SAT
    #define ENABLE_RGB_MATRIX_BAND_VAL
#endif

