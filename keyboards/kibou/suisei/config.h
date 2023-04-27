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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x586A      //
#define PRODUCT_ID      0x0065      //
#define DEVICE_VER      0x0001      //
#define MANUFACTURER    Kibou      //
#define PRODUCT         suisei     //

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B11, B10, B0, A1, A0 }
#define MATRIX_COL_PINS { B2, A10, A9, A8, B15, B14, B13, A15, B3, B4, B5, B6, B7, B8, C13, B9 }

#define LED_CAPS_LOCK_PIN B1

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define STM32_HSECLK 8000000

#define TAP_CODE_DELAY 50

#define FORCE_NKRO

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Change USB Polling Rate to 1000hz and a larger keys per scan for elite gaming*/
#define USB_POLLING_INTERVAL_MS 1
