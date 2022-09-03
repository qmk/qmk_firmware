/*
 * Copyright 2022 Thomas.Haukland@gmail.com
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
#define VENDOR_ID 0xA8F8
#define PRODUCT_ID 0x1830
#define DEVICE_VER 0x0001
#define MANUFACTURER tompi
#define PRODUCT Zompi

#define SOFT_SERIAL_PIN GP0
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

//#define MASTER_RIGHT

#define MATRIX_ROWS 8
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS { GP9, GP10, GP4, GP5 }
#define MATRIX_COL_PINS { GP6, GP7, GP8, GP11, GP12 }

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN        GP3
#define I2C1_SDA_PIN        GP2
#define I2C_DRIVER I2CD2
#define OLED_BRIGHTNESS 128
//#define OLED_FONT_H "keyboards/mlego/m65/lib/glcdfont.c"
#endif

/* RGB settings. */
#define RGBLED_NUM 3
 #define RGBLED_SPLIT { 18, 18 }
#    define RGB_DI_PIN GP14
#    define DRIVER_LED_TOTAL 3

