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

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT 15
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_DEFAULT_HUE 221
#endif

#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9

#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_DISPLAY_128X64
#define OLED_COM_PINS 0x12

#define OLED_IC OLED_IC_SH1106
#define OLED_COLUMN_OFFSET 2
