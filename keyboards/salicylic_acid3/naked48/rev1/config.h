/*
Copyright 2021 Salicylic_Acid

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
#define MATRIX_ROWS 8
#define MATRIX_COLS 12

// wiring of each half
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, D7, E6, B4, B5 }
// When using Nafuda, comment out MATRIX_ROW_PINS_RIGHT and MATRIX_COL_PINS_RIGHT.
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6 }
#define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B1, B3, B2, B6, B4, B5, B2, B2 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#ifndef RGBLED_NUM
  #define RGBLED_NUM 48
#endif

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_DEFAULT_VAL 50

#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
