/*
Copyright 2022 Matt F

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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17


#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { GP2, GP29, GP28, GP19, GP12, GP11}
#define MATRIX_COL_PINS { GP27, GP26, GP25, GP24, GP23, GP22, GP20, GP21, GP14, GP15, GP16, GP17, GP18, GP13, GP0, GP1, GP3}
#define ENCODERS_PAD_A { GP10 }
#define ENCODERS_PAD_B { GP9 }


/* COL2ROW, ROW2COL*/
// (Defined in info.json) #define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN GP4
  #define RGBLED_NUM 18
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 10
  #define RGBLIGHT_VAL_STEP 10
  #define RGBLIGHT_LIMIT_VAL 225 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_TWINKLE


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */

