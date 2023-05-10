/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// default options applied when eeprom is cleared
#define DEFAULT_CAPS_LOCK_LIGHT_TAB      0            // 1 = enable, 0 = disable
#define DEFAULT_CAPS_LOCK_LIGHT_ALPHA    1            // 1 = enable, 0 = disable
#define DEFAULT_FN_LAYER_TRANSPARENT_OFF 0            // 1 = enable, 0 = disable
#define DEFAULT_FN_LAYER_SHOW_COLOR      1            // 1 = enable, 0 = disable
#define DEFAULT_RGB_ENABLE_MAC_BASE      1            // 1 = enable, 0 = disable
#define DEFAULT_RGB_ENABLE_WIN_BASE      1            // 1 = enable, 0 = disable
#define DEFAULT_HUE_WIN_BASE             80           // HSV green hue (Win Base layer)
#define RGB_MATRIX_DEFAULT_HUE           0            // HSV red hue  (Mac Base layer)
#define RGB_MATRIX_DEFAULT_SAT           255          // Both Win/Mac Base layers
#define RGB_MATRIX_DEFAULT_VAL           255          // Both Win/Mac Base layers
#define RGB_MATRIX_DEFAULT_SPD           127          // Both Win/Mac Base layers
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BREATHING  // Both Win/Mac Base layers

// Autocorrect is off at start up. If you want Autocorrect to be on at startup,
// remove or comment out the following line
#define AUTOCORRECT_OFF_AT_STARTUP

// Caps Lock RGB indicator color
#define CAPS_LOCK_INDICATOR_COLOR RGB_RED

// Dynamic Fn Layer RGB indicator options
#define FN1_LAYER_COLOR RGB_YELLOW

// Caps Word RGB indicator color
#define CAPS_WORD_INDICATOR_COLOR RGB_RED

// Caps Word is activated by double-tapping left Shift. Replace this with
// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD if you want to activate Caps Word
// by single-tapping both left and right Shift togeter.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Caps Word will light left Shift, left Control and left Option (or left Windows
// key) when acitvated. Remove this line if you want Caps Word to only light left
// Shift when enabled.
#define CAPS_WORD_LIGHT_LOWER_LEFT_CORNER