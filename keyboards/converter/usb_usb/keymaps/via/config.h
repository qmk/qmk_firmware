/*
Copyright 2022 Jeff Shufelt <jshuf@puppyfish.com> @jshuf

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

// place overrides here

// enable compression of scan matrix in custom_matrix.cpp
#define COMPRESS_MATRIX

// size of compressed matrix
#ifdef MATRIX_ROWS
#undef MATRIX_ROWS
#endif // MATRIX_ROWS
#define MATRIX_ROWS 9
#ifdef MATRIX_COLS
#undef MATRIX_COLS
#endif // MATRIX_COLS
#define MATRIX_COLS 16

// We can only fit 3 9x16(x2 byte) matrices in the available space
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif // DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

// We have 1 2-bit layout option and 13 1-bit layout options
// in the VIA usb_usb.json, so we need 15 bits (2 bytes)
// of layout option storage.
#ifdef VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#undef VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#endif // VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
