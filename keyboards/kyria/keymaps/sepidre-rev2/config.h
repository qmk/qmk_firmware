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

docker container exec --workdir /qmk_firmware qmk qmk compile -kb kyria -km SepiDre
 */
#pragma once

//#define USE_MATRIX_I2C

//#define SSD1306OLED

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 300000
  #define OLED_FONT_END 127
#endif

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 150
#undef PRODUCT
#define PRODUCT Kyria Keyboard

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

#ifdef RGBLIGHT_ENABLE
  #undef RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD 3
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_HUE_STEP 1
  #define RGBLIGHT_SAT_STEP 1
  #define RGBLIGHT_VAL_STEP 1
  #define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
  #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
  #define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 6
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13} // Orients Kyria LEDs to a circle around both halves.
  //#define RBGLIGHT_LED_MAP {9,8,6,7,5,3,2,4,1,0,10,12,13,11,14,16,17,15,18,19} // Orients Kyria LEDs for a left half-right half columnar progression.
#endif
// Custom Font path
#define OLED_FONT_H "keyboards/kyria/keymaps/SepiDre/glcdfont.c"
#define OLED_DISABLE_TIMEOUT

// The Leader key allows to flexibly assign macros to key sequences.
#define NO_ACTION_MACRO
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 950
