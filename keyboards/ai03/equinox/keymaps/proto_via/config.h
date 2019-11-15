/*
Copyright 2019 Ryota Goto

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

// Fix for prototype missing COL0, COL1, using backlight and RGB underglow I/O pins
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { C4, B7, C6, C7, B6, B5, B4, B3, B2, B1, B0, D6 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 32
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 34

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 35
// Dynamic macro starts after dynamic keymaps (35+(4*4*12*2)) = (35+384)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 419
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 605
#define DYNAMIC_KEYMAP_MACRO_COUNT 16