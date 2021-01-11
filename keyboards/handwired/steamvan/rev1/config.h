/*
Copyright 2019 John M Daly <jmdaly@gmail.com>

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    John M Daly
#define PRODUCT         SteamVan rev1
#define DESCRIPTION     An open hardware forty percent PCB

/* Address for jumping to bootloader on STM32 chips. */
/* It is chip dependent, the correct number can be looked up here:
 * http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
 */
#define STM32_BOOTLOADER_ADDRESS 0x1FFFD800

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* ROWS: Top to bottom, COLS: Left to right
*/
#define MATRIX_ROW_PINS { A6, A5, A4, A3 }
#define MATRIX_COL_PINS { A9, A8, B15, B14, B13, A10, B9, B6, B5, B4, B3, A15 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Backlight configuration
 * Backlight LEDs on B8
 */
#define BACKLIGHT_LEVELS 24
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 16
#define RGB_DI_PIN A7
#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGB_MATRIX_KEYPRESSES
