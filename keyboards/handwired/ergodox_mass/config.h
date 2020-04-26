/* Copyright 2018 Andrew Mass
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

// USB device descriptor parameters
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0x1212
#define DEVICE_VER      0x0001
#define MANUFACTURER    mass
#define PRODUCT         ergodox_mass
#define DESCRIPTION     Custom ErgoDox Keyboard

// QMK definitions
#define MATRIX_ROWS 12 // Three GPX chips per side, two banks per chip
#define MATRIX_COLS 8  // 8 pins per GPX bank
#define UNUSED_PINS { E6, B7, D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7, F7 }
#define DEBOUNCE    10 // 10 ms debounce timer
