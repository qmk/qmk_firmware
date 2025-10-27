/*
 *  Copyright (C) 2021  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

// I2C {
#define F_SCL 100000UL // Run I2C bus at 100 kHz
#define I2C_START_RETRY_COUNT 20
#define I2C_TIMEOUT 100 // milliseconds
// } I2C

// EEPROM {
#define EEPROM_SIZE 1024
// TODO: Refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x76EC
#define EEPROM_MAGIC_ADDR 64
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x02
#define EEPROM_VERSION_ADDR (EEPROM_MAGIC_ADDR + 2)
// } EEPROM

// Dynamic keymap {
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define DYNAMIC_KEYMAP_MACRO_COUNT 0
// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR (EEPROM_VERSION_ADDR + 1)
// Dynamic macro starts after dynamic keymaps, it is disabled
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 0
// } Dynamic keymap

// System76 EC {
#define SYSTEM76_EC_EEPROM_ADDR (DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE)
#define SYSTEM76_EC_EEPROM_SIZE (EEPROM_SIZE - SYSTEM76_EC_EEPROM_ADDR)
// } System76 EC
