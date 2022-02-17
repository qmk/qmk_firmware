 /* Copyright 2021 duoshock 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */ 

#include "config_common.h"

#define VENDOR_ID       0x4D65
#define PRODUCT_ID      0x5543
#define DEVICE_VER      0x0001
#define MANUFACTURER    Merge
#define PRODUCT         UC-1

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

#define MATRIX_ROW_PINS { B1, B2 }
#define MATRIX_COL_PINS { B3, B4 }
#define UNUSED_PINS

#define RGB_DI_PIN B5
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F6 }
#define ENCODER_RESOLUTION 4
