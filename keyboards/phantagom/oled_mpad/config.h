/*
Copyright 2022 <dennis@kruyt.org>

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


#define TAPPING_TERM 400

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { GP23, GP22, GP21, GP20, GP19, GP18 }
#define MATRIX_COL_PINS { GP17, GP16, GP15 , GP14, GP11 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP4
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
/* #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U */

#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 0

#define I2C_DRIVER I2CD1
#define OLED_DISPLAY_128X64
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13
