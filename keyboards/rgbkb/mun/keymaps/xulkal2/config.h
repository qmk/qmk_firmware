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

// Xulkal custom stuff
#undef TAPPING_FORCE_HOLD

#undef TAPPING_TERM
#define TAPPING_TERM 175

#define SPACE_CADET_MODIFIER_CARRYOVER
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_LBRC
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_RBRC
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_MINS
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_EQL

// No need for the single versions when multi performance isn't a problem =D
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH

// 20m timeout (20m * 60s * 1000mil)
// #define RGB_DISABLE_TIMEOUT 1200000
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define OLED_SCROLL_TIMEOUT 20000
#define ONESHOT_TAP_TOGGLE 2

#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 8

#define ENCODER_RESOLUTION 2