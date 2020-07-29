/*Copyright 2019 coseyfannitutti

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6869
#define DEVICE_VER      0x0002
#define MANUFACTURER    RGBKB
#define PRODUCT         Pan
#define DESCRIPTION     "Ortho or Staggered DIY kit with RGB"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 13

//#ifdef ATmega32A
//  #define MATRIX_ROW_PINS { D7, D1, D5, D6, C2 }
//  #define MATRIX_COL_PINS { C3, C4, C5, C6, C7, A7, A6, A5, A4, A3, A2, A1, A0 }
//  #define ENCODERS_PAD_A { B0, D0 }
//  #define ENCODERS_PAD_B { B1, B2}
//  #define RGB_DI_PIN B3
//  #pragma message "atmega" // for debug
//#endif

//#ifdef ProtonC
//  #define MATRIX_ROW_PINS { A15, B10, A14, A13, A7 }
//  #define MATRIX_COL_PINS { A8, A6, B0, B1, B2, B4, B5, A1, A2, B3, B9, A10, A9 }
//  #define ENCODERS_PAD_A { B14, B11 }
//  #define ENCODERS_PAD_B { B15, B12 }
//  #define RGB_DI_PIN A3
//  #pragma message "stm32" // for
//#endif

#define UNUSED_PINS
#define ENCODER_RESOLUTION 4
#define RGBLED_NUM 64
#define RGBLIGHT_ANIMATIONS
#define DRIVER_LED_TOTAL RGBLED_NUM

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define USB_MAX_POWER_CONSUMPTION 510
#define RGBLIGHT_LIMIT_VAL 120

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

