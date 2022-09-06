/* Copyright 2021 datafx
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

#define brightnessMax 8

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4D47 // MG for Monstargear
#define PRODUCT_ID      0x5344 // SD for Soldered
#define DEVICE_VER      0x0001
#define MANUFACTURER    Monstargear
#define PRODUCT         XO87 Soldered

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define BACKLIGHT_PIN F0

#define MATRIX_ROW_PINS { E6,E7,E3,B0,B1,A2}
#define MATRIX_COL_PINS { C5,C3,C1,E1,D6,D2,B7,B3,F6,F7,F3,A5,A1,E2,C7,A6 }

#define KEYLED_ROWS 6
#define KEYLED_COLS 16
#define KEYLED_ROW_PINS { E5,B4,B5,F0,C6,D5 }
#define KEYLED_COL_PINS { C4,C2,C0,E0,D4,E4,B6,B2,F4,A0,F2,A4,F1,A7,D3,A3 }
#define LED_DRIVER_LED_COUNT 93

#define UNUSED_PINS
#define DIODE_DIRECTION ROW2COL
#define RGB_DI_PIN D7
#define DRIVER_LED_TOTAL 21
#define DRIVER_COUNT 2
#define RGBLED_NUM 21
#define RGBLIGHT_ANIMATIONS

#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_LEVELS 3
