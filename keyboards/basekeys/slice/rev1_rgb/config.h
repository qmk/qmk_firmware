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
#define VENDOR_ID       0x424B   // BK
#define PRODUCT_ID      0x9876
#define DEVICE_VER      0x0004
#define MANUFACTURER    2Moons
#define PRODUCT         Slice RGB
#define DESCRIPTION     A custom keyboard

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 18

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, B5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define DIODE_DIRECTION COL2ROW

#define RGB_KEYBOARD

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
//#define EE_HANDS
#define MASTER_LEFT
//#define MASTER_RIGHT

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* RGB LED */
#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 69    // Number of LEDs. backlight x69
#define RGBLED_SPLIT { 34, 35 }
#define RGBLIGHT_LIMIT_VAL 120 /* The maximum brightness level */
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_ANIMATIONS
#endif

#define OLED_FONT_H "keyboards/basekeys/slice/slice_font.c"
