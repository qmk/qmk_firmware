/*
Copyright 2018 James Laird-Wah
Copyright 2025 QMK

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

/* key matrix size; rows are doubled for split */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* The two ATtiny key scanners hang off I2C1 (B6/B7). They implement clock
 * stretching, so a generous timeout is needed. */
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7

/* On-die flash EEPROM emulation for the GD32F303 (behaves as an STM32F103
 * high-density part). */
#define FEE_PAGE_SIZE 0x800
#define FEE_PAGE_COUNT 4
#define FEE_MCU_FLASH_SIZE_IGNORE_CHECK
#define FEE_MCU_FLASH_SIZE 512

/* RGB matrix: a coloured animation at a visible brightness on a fresh EEPROM.
 * (on/hue/sat are left at their defaults — true/0/255 — since setting them
 * explicitly duplicates the built-ins and the strict linter rejects that.) */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_DEFAULT_VAL 128
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
