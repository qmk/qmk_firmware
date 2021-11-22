/* Copyright 2021 Mike Tsao
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

// config.h

#pragma once

#include "config_common.h"

// USB Device descriptor parameters
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x8889
#define DEVICE_VER 0x0001
#define MANUFACTURER github.com/sowbug
#define PRODUCT ANSI TKL
#define DESCRIPTION A tenkeyless ANSI-layout keyboard

// key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

// key matrix pins
#define MATRIX_ROW_PINS \
    { C14, C15, A0, A1, A2, A3 }
#define MATRIX_COL_PINS \
    { A4, A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, A8, A9, A10, A15, B3 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B9
#define RGB_MATRIX_KEYPRESSES
#define RGBLED_NUM 87
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128

// Want backlighting and RGB Matrix patterns? See the note in the readme,
// apply the patches, and then uncomment the line below as well as the ones
// in rules.mk.
//
// #define BACKLIGHT_PIN rgb_matrix
