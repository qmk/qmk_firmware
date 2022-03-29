/* Copyright 2020 Casey Webster <casey@e1337.dev>
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

#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  //#define RGBLIGHT_ANIMATIONS
  //#define RGBLIGHT_EFFECT_ALTERNATING
  #define RGBLIGHT_EFFECT_BREATHING
  //#define RGBLIGHT_EFFECT_CHRISTMAS
  //#define RGBLIGHT_EFFECT_KNIGHT
  //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
  //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  //#define RGBLIGHT_EFFECT_RGB_TEST
  //#define RGBLIGHT_EFFECT_SNAKE
  //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
  //#define RGBLIGHT_EFFECT_TWINKLE
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 128
  #define RGBLIGHT_EFFECT_BREATHE_MAX 128
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 16
  //#define RGBLIGHT_STARTUP_ANIMATION
#endif

#ifdef COMBO_ENABLE
  #define COMBO_COUNT 5
#endif

#define QMK_KEYS_PER_SCAN 4

#define EE_HANDS

//#define DEBUG_MATRIX_SCAN_RATE
//#define SPLIT_MODS_ENABLE
