/*
This is the c configuration file for the keymap

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define EE_HANDS

// OLED
#ifdef OLED_DRIVER_ENABLE
#    undef SSD1306OLED
#    undef OLED_FONT_H
#    define OLED_FONT_H RHRUIZ_OLED_FONT_H
#    define OLED_SCROLL_TIMEOUT 8000
#    ifdef OLED_ROTATE
#        define OLED_SCROLL_TIMEOUT_RIGHT
#     endif
#endif

#undef USE_I2C
#define USE_SERIAL_PD2

#undef TAPPING_TERM
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define HOME_ROW_MODS

#define NO_ACTION_ONESHOT

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 27
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

// bootmagic

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

// bootloader

#define QMK_ESC_OUTPUT F4  // usually COL
#define QMK_ESC_INPUT D4   // usually ROW
#define QMK_LED D5
#define QMK_SPEAKER B0

// todo: remove on split common
#define NO_DEBUG_LEDS
