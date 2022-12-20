/* Copyright 2022 Tim (https://github.com/Timliuzhaolu)
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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B2, B1, B0, E6, B3, B7 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif


