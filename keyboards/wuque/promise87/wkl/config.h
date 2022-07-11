/* Copyright 2022 wuque
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
#define VENDOR_ID       0x906D
#define PRODUCT_ID      0x0006
#define DEVICE_VER      0x0001
#define MANUFACTURER    wuque
#define PRODUCT         promise87

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_ROW_PINS { B3, B7, B2, F0, D3, D0 }
#define MATRIX_COL_PINS { D6, D7, D1, D5, F7, D4, F5, F4, F1, C7, C6, B6, B5, B4, E6, B1, B0 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN F6
#define LED_PIN_ON_STATE 0
