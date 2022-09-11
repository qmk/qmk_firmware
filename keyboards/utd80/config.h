/* Copyright 2021 UTDKeyboard & Dominic Gan
 * 
 * this program is free software: you can redistribute it and/or modify 
 * it under the terms of the gnu general public license as published by 
 * the free software foundation, either version 2 of the license, or 
 * (at your option) any later version. 
 * 
 * this program is distributed in the hope that it will be useful, 
 * but without any warranty; without even the implied warranty of 
 * merchantability or fitness for a particular purpose.  see the 
 * gnu general public license for more details. 
 * 
 * you should have received a copy of the gnu general public license 
 * along with this program.  if not, see <http://www.gnu.org/licenses/>. 
 */ 
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B4, D5, D0, B2, B3, B0 }
#define MATRIX_COL_PINS { B1, F0, F1, F4, F5, F6, F7, C7, C6, D3, E6, D7, D6, D4, D2, D1 }

#define BACKLIGHT_PIN B7
#define BACKLIGHT_BREATHING
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B6
#define LED_SCROLL_LOCK_PIN B5

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
