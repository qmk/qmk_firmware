/* Copyright 2020-2021 PercyJW-2 <joris.wachsmuth@gmail.com>
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

// USB Device descriptor parameter
#define VENDOR_ID     0x4A57 // JW
#define PRODUCT_ID    0x0000 // first keeb
#define DEVICE_VER    0x0000 // first revision
#define MANUFACTURER  percyjw
#define PRODUCT       split65

// Audio
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

// Matrix Assignments
#define MATRIX_ROWS 10 //Rows are doubled-up
#define MATRIX_COLS 8

#define MATRIX_COL_PINS {A2, A1, A0, B8, B13, B14, B15, B9}
#define MATRIX_ROW_PINS {B5, B4, B3, B2, B1}

// COL2ROW, ROW2COL
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

// Split Keyboard specifics
#define SOFT_SERIAL_PIN A9
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 100

// Debounce to reduce unintended double-presses use 0 if not needed
#define DEBOUNCE 5

// Feature diable options
//#define NO_DEBUG
//#define NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define OLED_DISPLAY_128X64
