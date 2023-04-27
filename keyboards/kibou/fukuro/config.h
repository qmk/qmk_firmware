/*
Copyright 2023 Kibou

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

#include "config_common.h"

#pragma once

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A9, A10, C13, A0, A6 }
#define MATRIX_COL_PINS { A8, B10, B2, B1, B0, A7, B9, B8, B7, B6, B5, B4, B3, A15, A1 }

#define LED_CAPS_LOCK_PIN A2

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

#define STM32_HSECLK 8000000

#define TAP_CODE_DELAY 50

#define FORCE_NKRO

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming*/
#define USB_POLLING_INTERVAL_MS 1

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
