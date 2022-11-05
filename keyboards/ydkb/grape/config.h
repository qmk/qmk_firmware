/* Copyright 2022 somepin
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
#define VENDOR_ID       0x5945 // "YE"
#define PRODUCT_ID      0x6772 // "GR"
#define DEVICE_VER      0x0001
#define MANUFACTURER    YDKB
#define PRODUCT         Grape

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 18

#define MATRIX_COL_PINS { F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4, D5, D3, B3, B2, B1, B0 }

#define SN74X138_ADDRESS_PINS { D2, D1, D0 }

#define LED_NUM_LOCK_PIN F1
#define LED_CAPS_LOCK_PIN F0
#define LED_SCROLL_LOCK_PIN E6
#define LED_PIN_ON_STATE 0

#define BACKLIGHT_PIN B7
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN E6
#define RGBLED_NUM 4
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 3
