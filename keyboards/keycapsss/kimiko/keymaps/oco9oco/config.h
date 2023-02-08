/* Copyright 2019 MechMerlin
 * Copyright 2020 @ben_roe (keycapsss.com)
 * Copyright 2022 @oco9oco
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

// #undef RGBLIGHT_ANIMATIONS
// #undef RGBLIGHT_EFFECT_BREATHING
// #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
// #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #undef RGBLIGHT_EFFECT_SNAKE
// #undef RGBLIGHT_EFFECT_KNIGHT
// #undef RGBLIGHT_EFFECT_CHRISTMAS
// #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
// #undef RGBLIGHT_EFFECT_RGB_TEST
// #undef RGBLIGHT_EFFECT_ALTERNATING
// #undef RGBLIGHT_EFFECT_TWINKLE

// #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
// #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #undef ENABLE_RGB_MATRIX_BREATHING
// #undef ENABLE_RGB_MATRIX_BAND_SAT
// #undef ENABLE_RGB_MATRIX_BAND_VAL
// #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #undef ENABLE_RGB_MATRIX_CYCLE_ALL
// #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
// #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// #undef ENABLE_RGB_MATRIX_DUAL_BEACON
// #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #undef ENABLE_RGB_MATRIX_RAINDROPS
// #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #undef ENABLE_RGB_MATRIX_HUE_BREATHING
// #undef ENABLE_RGB_MATRIX_HUE_PENDULUM
// #undef ENABLE_RGB_MATRIX_HUE_WAVE
// #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// #undef ENABLE_RGB_MATRIX_PIXEL_RAIN

// #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #undef ENABLE_RGB_MATRIX_SPLASH
// #undef ENABLE_RGB_MATRIX_MULTISPLASH
// #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
// #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH


#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_HUE_STEP 8
#   define RGBLIGHT_SAT_STEP 8
#   define RGBLIGHT_VAL_STEP 8
#   define RGBLIGHT_SLEEP   /* the RGB lighting will be switched off when the host goes to sleep */
// #   define RGBLIGHT_SPLIT    
#   define RGBLIGHT_LAYERS
/*== all animations enable ==*/
//#   define RGBLIGHT_ANIMATIONS
/*== or choose animations to save space ==*/
#   define RGBLIGHT_EFFECT_BREATHING
//#   define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #   define RGBLIGHT_EFFECT_SNAKE
// #   define RGBLIGHT_EFFECT_KNIGHT
// #   define RGBLIGHT_EFFECT_CHRISTMAS
// #   define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #   define RGBLIGHT_EFFECT_RGB_TEST
// #   define RGBLIGHT_EFFECT_ALTERNATING
#endif
#ifdef RGB_MATRIX_ENABLE
// #   define RGB_MATRIX_KEYPRESSES
// #   ifdef RGB_MATRIX_KEYPRESSES
// #       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #   endif
#endif
// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
