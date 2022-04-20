/* Copyright 2021 NachoxMacho
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6964
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0002
#define MANUFACTURER    Idobao
#define PRODUCT         Montex

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, D6, D7, B4, B5, C6 }
#define MATRIX_COL_PINS { D5, D3, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN B1
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

// Uncomment out to use the underbody LEDs, hidden by the aluminum case. Useful for the acrylic bottom
// #define MONTEX_USE_UNDERBODY

// LED MAP
//
//       4       3       2       1       0
//   LED05,  LED04,  LED03,  LED02,  LED01
// +----------------------------------------
// |
// |     5       6       7       8       9
// | LED10,  LED09,  LED08,  LED07,  LED06
// +---------------------------------------+
//                                      10 |
//                                   LED11 |
//      14     13       12      11	       |
//   LED15,  LED14,  LED13,  LED12         |
// +---------------------------------------+
// |
// |    15      16      17      18
// | LED19,  LED18,  LED17,  LED16
// +---------------------------------------+
//                                      19 |
//                                   LED24 |
// +---------------------------------------+
// |    23      22      21      20
// | LED23,  LED22,  LED21,  LED20
// |
// |    24      25              26
// | LED27,  LED26,          LED25
// +---------------------------------------+
//                                         |
// UNDERBODY LIGHTING                      |
//                                         |
//      29      30                         |
//   LED29,  LED28                         |
// +--------------                         |
// |                                       |
// |    28      27                         |
// | LED30,  LED31                         |
// |---------------------------------------+

#ifdef MONTEX_USE_UNDERBODY
#define RGBLED_NUM 31
#define RGBLIGHT_LED_MAP {4,3,2,1,0,9,8,7,6,5,14,13,12,11,10,18,17,16,15,23,22,21,20,19,26,25,24,29,30,28,27}
#else
#define RGBLED_NUM 27
#define RGBLIGHT_LED_MAP {4,3,2,1,0,9,8,7,6,5,14,13,12,11,10,18,17,16,15,23,22,21,20,19,26,25,24}
#endif


#endif
