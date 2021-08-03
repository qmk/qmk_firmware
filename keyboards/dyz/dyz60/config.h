/*
Copyright 2021 dayatz

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
#define VENDOR_ID       0xD772
#define PRODUCT_ID      0x000A
#define DEVICE_VER      0x0001
#define MANUFACTURER    dyz
#define PRODUCT         dyz60
#define DESCRIPTION     60% with flexcut and multiple mounts support

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { B0, E6, F0, F5, F4 }
#define MATRIX_COL_PINS { F6, F7, B3, B2, B1, D2, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B7
#define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 19
// #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLED_NUM 16

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define LED_CAPS_LOCK_PIN F1

#define TAP_CODE_DELAY 10 // Need this delay for some keys like VOLD/VOLU to work
#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D1 }

// python3 util/vial_generate_keyboard_uid.py
#define VIAL_KEYBOARD_UID {0xBF, 0x0D, 0x8D, 0xDF, 0xDB, 0x11, 0x0C, 0xA5}
// encoder per layers
#define VIAL_ENCODER_DEFAULT { KC_VOLD, KC_VOLU, KC_LEFT, KC_RIGHT, KC_TRNS, KC_TRNS }
#define VIAL_ENCODER_KEYCODE_DELAY 10

#define DYNAMIC_KEYMAP_LAYER_COUNT 3
