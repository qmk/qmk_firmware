/* Copyright 2022 JannikB5825
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
#define MANUFACTURER    JannikB5825
#define PRODUCT         SHOC

#define SSD1306OLED
#define USE_SSD_I2C
#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 300000
#define OLED_BRIGHTNESS 255


/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3, B6, B2 }
#define MATRIX_COL_PINS { D3, D2, D4, C6, D7, E6, B4, B5 }
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
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
