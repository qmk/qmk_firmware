/* Copyright 2022 Momokai
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

/* USB Device descriptor parameter */
#define VENDOR_ID    0x69F9   // "69" + "Popular Racing Movie 9"  =  Momokai (?)
#define PRODUCT_ID   0x0006
#define DEVICE_VER   0x0001
#define MANUFACTURER Momokai
#define PRODUCT      Tap Trio

#define MATRIX_ROWS 1
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { E0 }
#define MATRIX_COL_PINS { E6, B2, B7, D1, D2, D3 }

#define DIODE_DIRECTION COL2ROW


//TODO: implement RGB Matrix
#define RGB_DI_PIN F0
#define RGBLED_NUM 5
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL


/*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
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


// #ifdef RGB_DI_PIN
// #define DRIVER_LED_TOTAL 5

// #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// // #    define RGBLIGHT_LIMIT_VAL 180 // Limit to vendor-recommended value
// #endif
// #ifdef RGB_MATRIX_ENABLE
// // #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180 // Limit to vendor-recommended value
//     // RGB Matrix Animation modes. Explicitly enabled
//     // For full list of effects, see:
//     // https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
//     #define ENABLE_RGB_MATRIX_SOLID_COLOR
//     #define ENABLE_RGB_MATRIX_ALPHAS_MODS
//     #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//     #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
//     #define ENABLE_RGB_MATRIX_BREATHING
//     // #define ENABLE_RGB_MATRIX_BAND_SAT
//     // #define ENABLE_RGB_MATRIX_BAND_VAL
//     // #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//     // #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//     // #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
//     // #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//     #define ENABLE_RGB_MATRIX_CYCLE_ALL
//     #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//     #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
//     // #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//     #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
//     // #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//     #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
//     #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
//     // #define ENABLE_RGB_MATRIX_DUAL_BEACON
//     #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
//     // #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//     #define ENABLE_RGB_MATRIX_RAINDROPS
//     #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
//     #define ENABLE_RGB_MATRIX_HUE_BREATHING
//     #define ENABLE_RGB_MATRIX_HUE_PENDULUM
//     #define ENABLE_RGB_MATRIX_HUE_WAVE
//     #define ENABLE_RGB_MATRIX_PIXEL_RAIN
//     #define ENABLE_RGB_MATRIX_PIXEL_FLOW
//     #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

//     // enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
//     // #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
//     // #define ENABLE_RGB_MATRIX_DIGITAL_RAIN

//     // enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
//     // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//     #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
//     #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//     #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//     // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
//     // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//     // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
//     // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
//     #define ENABLE_RGB_MATRIX_SPLASH
//     // #define ENABLE_RGB_MATRIX_MULTISPLASH
//     #define ENABLE_RGB_MATRIX_SOLID_SPLASH
//     // #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
// #endif
