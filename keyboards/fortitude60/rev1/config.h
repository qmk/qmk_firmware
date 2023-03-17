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


// wiring of each half
#define MATRIX_ROW_PINS { D1, D0, D3, B7, B6 }
#define MATRIX_COL_PINS { F7, F6, F5, B3, B2, B1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//#define EE_HANDS

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 500

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#ifdef RGBLIGHT_ENABLE
  #define RGB_DI_PIN B5
  #define RGBLED_NUM 18    // Number of LEDs */
#endif
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
