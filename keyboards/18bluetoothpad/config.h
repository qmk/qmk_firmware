/*
Copyright 2020 latincompass
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "config_common.h"
#define VENDOR_ID       0x6C63 // "lc" = latincompass
#define PRODUCT_ID      0x3170 // "1p" = 18bluetoothpad
#define DEVICE_VER      0x0001
#define MANUFACTURER    latincompass
#define PRODUCT         18bluetoothpad
#define DESCRIPTION     18 RGB bluetoothpad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4


 #define MATRIX_ROW_PINS { B4, B5, B6, B7, C7 }

 #define MATRIX_COL_PINS { D4, D5, D6, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define AdafruitBleResetPin F4
#define AdafruitBleCSPin F6
#define AdafruitBleIRQPin F5


#define RGB_DI_PIN B0     // B0 LED out pin
//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
 #define RGBLED_NUM 22
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8

#define ENCODERS_PAD_A { F1 }
#define ENCODERS_PAD_B { F0 }
#define ENCODER_RESOLUTION 4
