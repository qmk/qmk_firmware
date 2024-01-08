/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 15000
#define OLED_FONT_H "keyboards/splitkb/kyria/keymaps/semd/glcdfont.c"

#ifdef RGBLIGHT_ENABLE
  // #define RGBLIGHT_EFFECT_ALTERNATING
  #define RGBLIGHT_MODE_STATIC_GRADIENT
  // #define RGBLIGHT_MODE_STATIC_LIGHT
  #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_CHRISTMAS
  // #define RGBLIGHT_EFFECT_KNIGHT
  // #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  // #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_RGB_TEST
  // #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_TWINKLE

  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLED_NUM 20
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 200
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LAYERS
#endif

#ifdef ENCODER_ENABLE
#    define ENCODER_DIRECTION_FLIP
#    define ENCODER_RESOLUTION 2
#endif

#define EE_HANDS

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250

#define TAPPING_TOGGLE 2

#define CAPS_WORD_INVERT_ON_SHIFT
