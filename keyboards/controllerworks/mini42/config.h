/*
 * Copyright 2022 Kevin Gee <info@controller.works>
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

#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define DIRECT_PINS {{GP2, GP3, GP4, GP5, GP6, GP7}, \
                     {GP8, GP9, GP10, GP11, GP12, GP13}, \
                     {GP14, GP15, GP16, GP17, GP18, GP19}, \
                     {GP20, GP21, GP22, NO_PIN, NO_PIN, NO_PIN}}
#define DIRECT_PINS_RIGHT {{GP7, GP6, GP5, GP4, GP3, GP2}, \
                           {GP13, GP12, GP11, GP10, GP9, GP8}, \
                           {GP19, GP18, GP17, GP16, GP15, GP14}, \
                           {GP22, GP21, GP20, NO_PIN, NO_PIN, NO_PIN}}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
/* #define DEBOUNCE 5 */

/* Serial settings */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP1
#define WS2812_PIO_USE_PIO1
#define RGB_DI_PIN GP0

#undef I2C_DRIVER
#define I2C_DRIVER I2CD1
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP25
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP24

/* #define EE_HANDS */
#define MASTER_LEFT
/* #define MASTER_RIGHT */

/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT    4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define OLED_FONT_H "keyboards/controllerworks/mini42/lib/glcdfont.c"