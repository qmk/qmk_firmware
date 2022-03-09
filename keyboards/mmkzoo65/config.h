/* Copyright 2021 TW59420 <https://github.com/TW59420>
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
#define VENDOR_ID       0x7BA1
#define PRODUCT_ID      0x6505
#define DEVICE_VER      0x0001
#define MANUFACTURER    MWStudio
#define PRODUCT         MMKZOO65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B2, B3, B7, E6, B0 }
#define MATRIX_COL_PINS { B1, F0, F1, F4, F5, F6, F7, D4, D6, D7, B4, B5, B6, C6, C7 }

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
#define FORCE_NKRO

/* 将USB 轮询速率更改为 1000hz 并为精英游戏每次扫描使用更大的密钥*/
#define USB_POLLING_INTERVAL_MS  2
#define QMK_KEYS_PER_SCAN  12
