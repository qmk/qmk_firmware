// Copyright 2022 TDC

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.

// T his program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 20

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS {B3,B0,A7,A6,A5,A4}
#define MATRIX_COL_PINS {A9,A8,B15,B14,B13,B12,B11,B10,B2,B1,A3,A2,A1,A0,B9,B8,B7,B4,B6,B5}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN A15
#ifdef RGB_DI_PIN
#define RGBLED_NUM 104
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 6
#define RGBLIGHT_VAL_STEP 6
#define RGBLIGHT_DEFAULT_HUE 4
#define RGBLIGHT_LIMIT_VAL 15 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
//    #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//     #define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
