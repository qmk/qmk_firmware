/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define DEVICE_VER      0x0200
#define MANUFACTURER    DAVID
#define PRODUCT         DAVID_96

// #define RGBLED_NUM 15

#define MATRIX_ROWS 7
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { F1, F4, F5, F6, F7, D0, B7  }
#define MATRIX_COL_PINS { C7,C6,B4,F0,E6,B0,B1,B2,B3,D2,D3,D5,D4,D6,D7 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define BACKLIGHT_PIN B5
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

#define RGB_DI_PIN B6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 15
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
