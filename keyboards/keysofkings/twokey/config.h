 /* Copyright 2020 Keys of Kings
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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xAE12
#define DEVICE_VER      0x0001
#define MANUFACTURER    Keys of Kings
#define PRODUCT         Twokey

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, B5 }
#define MATRIX_COL_PINS { B3, B2 }
#define UNUSED_PINS


#define ENCODERS_PAD_A { D7 }
#define ENCODERS_PAD_B { E6 }
#define ENCODER_RESOLUTION 1

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 5
#define RGBLIGHT_HUE_STEP 4
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 4
#define AUDIO_PIN B6
#define AUDIO_CLICKY
#endif

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(MAJOR_SOUND)
#endif
