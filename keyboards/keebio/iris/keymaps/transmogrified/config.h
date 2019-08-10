/*
Copyright 2017 Adam Roberts <adam+gh@bikuman.com>

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

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
//#define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define NO_USB_STARTUP_CHECK //keep both sides on when pc is sleeping.
#define TAPPING_TERM 200

// Remove features i don't use
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
 
// Override the rev2 config.h BACKLIGHT_LEVELS setting
#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 125
