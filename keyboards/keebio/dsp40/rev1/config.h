/* Copyright 2021 Danny Nguyen <danny@keeb.io>

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
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x144C
#define DEVICE_VER      0x0100
#define MANUFACTURER    Keebio
#define PRODUCT         DSP40 Rev. 1

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B9, A9, A8, B15 }
#define MATRIX_COL_PINS { B10, B2, A3, A4, B7, B6, A10, C13, C14, C15, F0, F1 }
#define ENCODERS_PAD_A { A1 }
#define ENCODERS_PAD_B { A2 }
#define TAP_CODE_DELAY 10
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN A6
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 1
// #define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 7

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 4
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== all animations enable ==*/
  #define RGBLIGHT_ANIMATIONS
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
