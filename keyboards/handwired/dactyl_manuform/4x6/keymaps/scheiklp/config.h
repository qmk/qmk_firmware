/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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


#define USE_I2C
//
// VBUS is used to power the LEDs without going "through" the MCU -> detecting handedness cannot rely on VBUS
// From the QMK documentation: Enabling this option changes the startup behavior to listen for an active USB communication to delegate which part is master and which is slave. With this option enabled and theres's USB communication, then that half assumes it is the master, otherwise it assumes it is the slave.
#define SPLIT_USB_DETECT

// WS2812 RGB LED strip input and number of LEDs
#undef RGB_DI_PIN
#undef RGBLED_NUM
#define RGB_DI_PIN F4
#define RGBLED_NUM 52
#define RGBLED_SPLIT {26, 26}
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE

// Amoeba royale PCBs (https://github.com/mtl/keyboard-pcbs/tree/master/amoeba-royale) use row to column layout (current can flow from row pin to column pin).
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5

#define AUTO_SHIFT_TIMEOUT 100
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC

// require two taps for a TT layer switch (default 5)
#define TAPPING_TOGGLE 2

// Mouse control
// constant mode (velocity)
#define MK_3_SPEED
// KC_ACL0 < KC_ACL1 < unmodified < KC_ACL2

// Cursor offset per movement (unmodified)
#define MK_C_OFFSET_UNMOD 16
// Time between cursor movements (unmodified)
#define MK_C_INTERVAL_UNMOD 10
/* #define MK_C_INTERVAL_UNMOD 16 */

// Cursor offset per movement (KC_ACL0)
#define MK_C_OFFSET_0 1
// Time between cursor movements (KC_ACL0)
#define MK_C_INTERVAL_0 32

// Cursor offset per movement (KC_ACL1)
#define MK_C_OFFSET_1 4
// Time between cursor movements (KC_ACL1)
#define MK_C_INTERVAL_1 16

// Cursor offset per movement (KC_ACL2)
#define MK_C_OFFSET_2 20
/* #define MK_C_OFFSET_2 32 */
// Time between cursor movements (KC_ACL2)
#define MK_C_INTERVAL_2 16
