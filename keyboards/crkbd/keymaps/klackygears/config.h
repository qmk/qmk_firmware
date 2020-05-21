/*
This is the c configuration file for the keymap

Copyright 2020 klackygears
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 5
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

#define SSD1306OLED

#define USE_SERIAL_PD2
#define PERMISSIVE_HOLD

#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TERM 150
#define IGNORE_MOD_TAP_INTERRUPT


#undef RGBLED_NUM

#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17


//#if defined(LED_ANIMATIONS)
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_RAINBOW_SPARKLE
//     #define RGBLIGHT_EFFECT_SNAKE
//     #undef  RGBLIGHT_EFFECT_SNAKE_LENGTH
//     #define RGBLIGHT_EFFECT_SNAKE_LENGTH 20
   #define RGBLIGHT_EFFECT_KNIGHT
   #undef  RGBLIGHT_EFFECT_KNIGHT_LENGTH
   #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 20
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
//     #define RGBLIGHT_EFFECT_BEAM
//     #define RGBLIGHT_EFFECT_HYPERBEAM
//#endif

#undef PRODUCT
#define PRODUCT klackygears Corne Keyboard

#define OLED_FONT_H "keyboards/crkbd/keymaps/klackygears/glcdfont.c"




