/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x3257
#define DEVICE_VER      0x0300
#define MANUFACTURER    Keebio
#define PRODUCT         Quefrency Rev. 3

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

#define DIODE_DIRECTION COL2ROW
// wiring of each half
#define MATRIX_ROW_PINS { B1, B2, C7, B4, D7 }
#define MATRIX_COL_PINS { F4, F1, F0, B7, B3, D2, D3, D5, D4 }
#define MATRIX_ROW_PINS_RIGHT { B3, B2, B6, B4, D7 }
#define MATRIX_COL_PINS_RIGHT { F1, F0, F4, F5, F6, D5, C7, D3, B7 }
#define SPLIT_HAND_PIN F7
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F6 }
#define ENCODERS_PAD_A_RIGHT { D6 }
#define ENCODERS_PAD_B_RIGHT { D4 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define BACKLIGHT_PIN B5
#define CAPS_LOCK_LED_PIN B6

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN E6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16    // Number of LEDs
#define RGBLED_SPLIT { 8, 8 }
#define RGBLIGHT_LED_MAP { 1, 2, 3, 12, 13, 14, 15, 0, 7, 6, 5, 4, 11, 10, 9, 8 }

// Set 65% column (option 3) and Macro (option 4) on by default
#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00DE
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
