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

#define WS2812_PIO_USE_PIO1
#define RGBLED_NUM 54
#define RGB_MATRIX_LED_COUNT RGBLED_NUM

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP25
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP24

/* #define EE_HANDS  */
/* #define MASTER_LEFT */
/* #define MASTER_RIGHT */

/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT    0
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
