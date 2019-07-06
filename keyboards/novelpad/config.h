/*
Copyright 2018 Cole Markham

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
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6070
#define DEVICE_VER      0x0001
#define MANUFACTURER    NovelKeys.xyz
#define PRODUCT         Novelpad
#define DESCRIPTION     5x4 Hotswap MX numpad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { C2, C4, C5, C6, C7 }
#define MATRIX_COL_PINS { D7, D6, D5, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)

#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PIN B7

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
#endif

#endif
