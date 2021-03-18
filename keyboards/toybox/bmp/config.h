/*
Copyright 2020 sekigon-gonnoc

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

#ifndef __ASSEMBLER__

#define BMP_BOOTPIN_AS_RESET
/* key matrix size */
#define MATRIX_ROWS_DEFAULT 10
#define MATRIX_COLS_DEFAULT 8
#define THIS_DEVICE_ROWS 10
#define THIS_DEVICE_COLS 8
#define IS_LEFT_HAND  true
#define BMP_DEFAULT_MODE SINGLE

#define MATRIX_ROW_PINS { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 }
#define MATRIX_COL_PINS { 7, 7, 7, 7, 7, 7, 7, 7 }
#define MATRIX_LAYOUT \
    {1,  2,  3,  4,  5,  6,  7, 41, 42, 43, 44, 45, 46, 47, 48, 80, 0,  \
     9, 10, 11, 12, 13, 14, 15, 49, 50, 51, 52, 53, 54, 55, 56, 0, \
    17, 18, 19, 20, 21, 22, 57, 58, 59, 60, 61, 62, 63, 64, 0,  \
    25, 26, 27, 28, 29, 30, 65, 66, 67, 68, 69, 70, 71, 72, 0,  \
    33, 34, 35, 36, 73, 74, 75, 76, 77, 78, 79,  255}

#define KEYMAP_PRIOR_LOCALE 0
#define KEYMAP_ASCII 0
#define CONFIG_RESERVED { 0, 8, 0, 0, 0, 0, 0, 0 }

#include "microshell/util/mscmd.h"
#define USER_DEFINED_MSCMD                                      \
    {"tp_test", usrcmd_trackpad_test, "Test trackpad"}, {       \
        "tp_ram", usrcmd_trackpad_read_ram, "Read trackpad RAM" \
    }
MSCMD_USER_RESULT usrcmd_trackpad_test(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_trackpad_read_ram(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);

#define RGBLIGHT_SPLIT
#define G00 255 // Dummy for bin/qmk config generation
#define RGB_DI_PIN G00
#ifdef RGB_DI_PIN
  #define RGBLED_NUM_DEFAULT 128
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
  #define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_EFFECT_RGB_TEST
  #define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
  #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
  #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#endif
