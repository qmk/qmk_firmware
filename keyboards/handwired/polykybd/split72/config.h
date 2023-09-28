/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX, UNICODE_MODE_MACOS, UNICODE_MODE_WINCOMPOSE
#define TAP_CODE_DELAY 4

/* key matrix size */
#define MATRIX_ROWS_PER_SIDE 5
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define DIODE_DIRECTION ROW2COL
#define LAYOUT_TO_INDEX(row, col) ((row)*MATRIX_COLS+(col))

#define RGBLED_NUM       72
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#define RGB_MATRIX_SPLIT { 36, 36 }
//#define SPLIT_TRANSPORT_MIRROR


#define NUM_SHIFT_REGISTERS 5

// Split keyboard
// https://docs.qmk.fm/#/feature_split_keyboard?id=split-keyboard
#define SERIAL_USART_TX_PIN GP5
//#define MASTER_LEFT
//#define SERIAL_PIO_USE_PIO1
//#define SPLIT_USB_DETECT
//#define SPLIT_USB_TIMEOUT 5000
//#define SPLIT_USB_TIMEOUT_POLL 10
//#define SPLIT_WATCHDOG_ENABLE
#define EE_HANDS
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
//#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_POLY_DATA

//somehow connected to the matrix light
//#define SPLIT_MAX_CONNECTION_ERRORS 0

