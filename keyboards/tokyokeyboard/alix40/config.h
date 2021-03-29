/*
Copyright 2021 quadcube <james@quadcube.xyz>
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
#define VENDOR_ID       0x5143 // QC
#define PRODUCT_ID      0x4134 // A4
#define DEVICE_VER      0x0001
#define MANUFACTURER    quadcube
#define PRODUCT         alix40

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 31
#define BACKLIGHT_BREATHING
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* key matrix pins */
#define MATRIX_ROW_PINS { D7, C6, C7, B5 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0, D0, D1, D2, D3, D5, D6 }
#define UNUSED_PINS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN B0
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#endif

/* For Production */
#define QMK_ESC_OUTPUT F7 // usually COL
#define QMK_ESC_INPUT D7 // usually ROW

/* Bluetooth */
#define AdafruitBleResetPin D4
#define AdafruitBleCSPin    B4
#define AdafruitBleIRQPin   E6
#define BATTERY_LEVEL_PIN   B6
