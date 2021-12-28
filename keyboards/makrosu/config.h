/* Copyright 2021 Valdydesu_ 
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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAB69
#define PRODUCT_ID      0x8585
#define DEVICE_VER      0x0001
#define MANUFACTURER    valdydesu_
#define PRODUCT         makrosu

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { B6 }
#define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5}
#define UNUSED_PINS

#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { D1 }
#define TAP_CODE_DELAY 10 
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 5
/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



// EEPROM usage


#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
