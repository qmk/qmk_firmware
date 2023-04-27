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

#pragma once


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { C12, D2, B3, B4, C13 }
#define MATRIX_COL_PINS { C9, A8, A15, C10, C11, B5, B6, B7, A0, A1, A2, C3, C2, C1, A3, A4 }

/**/
#define LED_CAPS_LOCK_PIN C8

#define DEBOUNCE    1

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define STM32_HSECLK 8000000

#define TAP_CODE_DELAY 50

#define FORCE_NKRO

#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming*/
#define USB_POLLING_INTERVAL_MS 1

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
