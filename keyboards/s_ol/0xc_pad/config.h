/* Copyright 2021 s-ol
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
#define VENDOR_ID 0x732D
#define PRODUCT_ID 0x0C70
#define DEVICE_VER 0x0001
#define MANUFACTURER s-ol
#define PRODUCT 0xC.pad

/* key matrix  */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS \
    { B7, B6, B5, B4 }
#define MATRIX_COL_PINS \
    { D4, D3, D2, D1 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* ws2812 RGB LED */
#define RGB_DI_PIN C7
#define DRIVER_LED_TOTAL 12
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_CENTER { 112, 63 }
#define RGB_MATRIX_KEYPRESSES
