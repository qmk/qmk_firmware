/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

// Because Elite-C v3 has an issue :(
#define SPLIT_USB_DETECT

/* Select hand configuration */
// #define SPLIT_HAND_PIN
// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

/* Set tapping toggle */
#define TAPPING_TOGGLE 3
#define TAPPING_TERM 200

// Combo abilities
#define COMBO_COUNT 1

// apparantly I'm a fast typist
#define PERMISSIVE_HOLD

/* Fix Grave Escape key breaking app switching in MacOS */
#define GRAVE_ESC_GUI_OVERRIDE

// Disable space wasting music mode
#define NO_MUSIC_MODE

#undef RGBLED_NUM
// #define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 12
// #define RGBLIGHT_HUE_STEP 8
// #define RGBLIGHT_SAT_STEP 8
// #define RGBLIGHT_VAL_STEP 8
