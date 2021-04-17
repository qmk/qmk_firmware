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

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#define USB_SUSPEND_WAKEUP_DELAY 200

//#undef RGBLED_NUM
//#define RGBLIGHT_ANIMATIONS
//#define RGBLED_NUM 27
//#define RGBLIGHT_LIMIT_VAL 120
//#define RGBLIGHT_HUE_STEP 10
//#define RGBLIGHT_SAT_STEP 17
//#define RGBLIGHT_VAL_STEP 17

// Underglow
#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLED_NUM          10  // Number of LEDs
#    define RGBLED_SPLIT        { 5, 5 }
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP   6  // number of steps to cycle through the hue by
#    define RGBLIGHT_SAT_STEP   6  // number of steps to increment the saturation by
#    define RGBLIGHT_VAL_STEP   6  // number of steps to increment the brightness by
#    define RGBLIGHT_SLEEP         //  the RGB lighting will be switched off when the host goes to sleep
#endif

// QMK DFU
// #define QMK_ESC_OUTPUT F1  // COL pin if COL2ROW
// #define QMK_ESC_INPUT  D5  // ROW pin if COL2ROW

#define QMK_LED F0

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

#undef OLED_UPDATE_INTERVAL
#define OLED_UPDATE_INTERVAL 50

// Firmware optimizations

#undef  NO_DEBUG
#define NO_DEBUG
#undef  NO_PRINT
#define NO_PRINT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT 

// We only want ESC and Shift ESC 
#define GRAVE_ESC_ALT_OVERRIDE
#define GRAVE_ESC_CTRL_OVERRIDE
#define GRAVE_ESC_GUI_OVERRIDE