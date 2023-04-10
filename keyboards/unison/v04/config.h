/*
Copyright 2021 Takeshi Nishio

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


/* key matrix pins */
/* NOTE: With Round-Robin matrix, set same pins for both. */
#define MATRIX_ROW_PINS { B3, E6, F1, F5, F7, B2, F0, F4, F6, C7 }
#define MATRIX_COL_PINS { B3, E6, F1, F5, F7, B2, F0, F4, F6, C7 }

#define DIODE_DIRECTION COL2ROW

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define AUDIO_PIN_ALT B6
  #define AUDIO_CLICKY
  #define MUSIC_MAP
#endif

/* RGB Lighting */
#define RGB_DI_PIN B7
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 7 // Layer Indicator(2) + Rotary Encoder(5)
  #define RGBLIGHT_LED_MAP {1, 2, 0, 3, 4, 5, 6} // align LEDs from Left to Right
  #define RGBLIGHT_HUE_STEP 4
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  // #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== Lighting Layers ==*/
  #define RGBLIGHT_LAYERS
  // #define RGBLIGHT_MAX_LAYERS 2
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_SNAKE
  // #define RGBLIGHT_EFFECT_KNIGHT
  // #define RGBLIGHT_EFFECT_CHRISTMAS
  // #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  // #define RGBLIGHT_EFFECT_RGB_TEST
  // #define RGBLIGHT_EFFECT_ALTERNATING
  #define RGBLIGHT_EFFECT_TWINKLE
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
