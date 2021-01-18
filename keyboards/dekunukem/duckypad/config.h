/*

QMK Firmware for dekuNukem/duckyPad

Copyright (C) 2020 Max Bridgland <@M4cs>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0B91
#define DEVICE_VER      0x0001
#define MANUFACTURER dekuNukem
#define PRODUCT duckyPad

#define MATRIX_ROWS 1
#define MATRIX_COLS 17

#define DIRECT_PINS {{ B13, B14, B15, A8, A15, B3, B4, B5, B6, B7, C13, C14, C15, F0, F1, A1, A2 }}

#define RGB_DI_PIN A10
#define RGBLED_NUM 15
#define DRIVER_LED_TOTAL 15

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_STARTUP_HUE 221

#define I2C1_SCL_BANK GPIOB
#define I2C1_SCL 8
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 9

#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE STD_DUTY_CYCLE

#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_DISPLAY_128X64
#define OLED_COM_PINS 0x12

#define OLED_IC OLED_IC_SH1106
#define OLED_COLUMN_OFFSET 2
