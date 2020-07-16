/*
Copyright 2020 Cloudboards

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

#include "config_common.h"


/* USB Device descriptor parameter */
#define VENDOR_ID 0x0000
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define PRODUCT Nimbus
#define DESCRIPTION A custom numpad



/* Matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS {C6, B6, B5, B4, D7}
#define MATRIX_COL_PINS {F1, F4, F5, F6}

/* Encoder stuff */
#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D4 }
#define ENCODER_BUTTON F7
#define ENCODER_RESOLUTION 2
#define DEBOUNCE 10

/* OLED Display */
#define OLED_DISPLAY_HEIGHT 32
#define OLED_DISPLAY_WIDTH  128
#define OLED_COM_PINS COM_PINS_SEQ

//Version 1 Old
// #define BACKLIGHT_PIN C7
// #define RGB_DI_PIN B7

//Version 2 New
#define RGB_DI_PIN C7
#define BACKLIGHT_PIN B7

#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 24
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

// Actually since it is RGB LEDs it should be this

#ifdef RGB_DI_PIN
  #define RGBLED_NUM 10
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
  // #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
  #define RGBLIGHT_SLEEP
#endif
