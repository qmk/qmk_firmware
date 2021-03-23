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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B44 //KD
#define PRODUCT_ID      0x3738 //78
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kabe_Don
#define PRODUCT         78S

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS {D0,D2,F7,B1,B0,D6} 
#define MATRIX_COL_PINS {F5,F4,F6,C6,B6,B4,D3,D1,D4,F1,B3,D5,F0,C7,D7,B5,B2,E6}  

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5

#define RGB_DI_PIN B7  
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 20
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_ANIMATIONS 
#endif


