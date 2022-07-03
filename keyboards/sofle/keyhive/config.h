/* Copyright
 *   2021 solartempest
 *   2021 QMK
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
#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID    0xFC32
#define PRODUCT_ID   0x1287
#define DEVICE_VER   0x0002
#define MANUFACTURER Keyhive
#define PRODUCT      Sofle

// Key matrix size
// Rows are doubled-up. Added extra column for rotary encoder VIA mapping.
#define MATRIX_ROWS  10
#define MATRIX_COLS  7

// wiring of each half
#define MATRIX_ROW_PINS       { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS       { B6, B2, B3, B1, F7, F6, NO_PIN } // A virtual pin is needed for the encoder key matrix in via.
#define MATRIX_ROW_PINS_RIGHT { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS_RIGHT { F6, F7, B1, B3, B2, B6, NO_PIN } // A virtual pin is needed for the encoder key matrix in via.

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE        5

// Encoder support
#define ENCODERS_PAD_A            { F5 }
#define ENCODERS_PAD_B            { F4 }
#define ENCODERS_PAD_A_RIGHT      { F4 }
#define ENCODERS_PAD_B_RIGHT      { F5 }
#define ENCODER_RESOLUTIONS       { 4 }
#define ENCODER_RESOLUTIONS_RIGHT { 2 }  // Left encoder seems to have double-output issue but right does not.

#define TAP_CODE_DELAY  10

// Communication between sides
#define SOFT_SERIAL_PIN D2

// OLED settings
#define OLED_TIMEOUT    80000
#define OLED_BRIGHTNESS 90

#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSPORT_MIRROR

// Add RGB underglow
// by defining in the keyboard, incompatible keymaps will fail to compile.
#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN D3
#    define RGBLED_NUM 74
#    define RGBLED_SPLIT {37,37}
#    define RGBLIGHT_LIMIT_VAL 100 // LED Brightness, high power draw may exceed the USB limitations of 0.6A and cause a crash.
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
//#    define RGBLIGHT_LAYERS //Enable layer light indicators. Not required as updates are done in layer_state_set_user and led_update_user (+588).
#    define RGBLIGHT_SLEEP //Turn off LEDs when computer sleeping (+72)

//RGB LED Conversion macro from physical array to electric array (+146). This results in better looking animated effects.
//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
#    define LED_LAYOUT( \
  L00,  L01,  L02,  L03,  L04,  L05,          L08,  L09,  L010, L011, L012, L013, \
  L10,      L12,      L14,                              L19,      L111,     L113, \
  L20,  L21,  L22,  L23,  L24,  L25,          L28,  L29,  L210, L211, L212, L213, \
  L30,  L31,  L32,  L33,  L34,  L35,          L38,  L39,  L310, L311, L312, L313, \
  L40,      L42,      L44,                              L49,      L411,     L413, \
  L50,  L51,  L52,  L53,  L54,  L55,          L58,  L59,  L510, L511, L512, L513, \
          L62,  L63,  L64,  L65,  L66,      L67,  L68,  L69,  L610, L611,         \
      L71,                  L76,                  L77,                  L712     )\
  { \
    L14,L12,L10,L40,L42,L44,L71,L76,L66,L65,L55,L35,L25,L05,L04,L24,L34,L54,L64,L63,L53,L33,L23,L03,L02,L22,L32,L52,L62,L51,L31,L21,L01,L00,L20,L30,L50,L19,L111,L113,L413,L411,L49,L712,L77,L67,L68,L58,L38,L28,L08,L09,L29,L39,L59,L69,L610,L510,L310,L210,L010,L011,L211,L311,L511,L611,L512,L312,L212,L012,L013,L213,L313,L513, \
  }
//RGB LED logical order map
#    define RGBLIGHT_LED_MAP LED_LAYOUT( \
  5,  6,  17, 18, 29, 30,     43, 44, 55, 56, 67, 68, \
  4,    16,   28,                     45,   57,   69, \
  3,  7,  15, 19, 27, 31,     42, 46, 54, 58, 66, 70, \
  2,  8,  14, 20, 26, 32,     41, 47, 53, 59, 65, 71, \
  1,    13,   25,                     48,   60,   72, \
  0,  9,  12, 21, 24, 33,     40, 49, 52, 61, 64, 73, \
      11, 22, 23, 34, 35,   38, 39, 50, 51, 62,       \
      10,       36,              37,       63        )

#endif
