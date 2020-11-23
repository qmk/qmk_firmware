/*
Copyright 2020 n2

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
#define VENDOR_ID 0x0335
#define PRODUCT_ID 0x0007 //7cols
#define DEVICE_VER 0x0001
#define MANUFACTURER n2
#define PRODUCT sekimen 7cols

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY

/*left side*/
#define MATRIX_ROW_PINS { B3, B5, B4, E6, C6  }
#define MATRIX_COL_PINS { B2, B6, B1, F7, F6, D7, D4  }

/*right side*/
#define MATRIX_ROW_PINS_RIGHT { B5, F5, F6, B1, F7  }
#define MATRIX_COL_PINS_RIGHT { F4, B3, B2, B6, C6, B4, E6  }

#define UNUSED_PINS
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

 #define RGB_DI_PIN D3
 #ifdef RGB_DI_PIN
   #define RGBLED_NUM 10
   #define RGBLIGHT_SPLIT
   #define RGBLED_SPLIT { 5, 5 }
   #define RGBLIGHT_HUE_STEP 8
   #define RGBLIGHT_SAT_STEP 8
   #define RGBLIGHT_VAL_STEP 8
   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
 #endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif

// Custom Font path
#define OLED_FONT_H "keyboards/sekimen/glcdfont.c"
