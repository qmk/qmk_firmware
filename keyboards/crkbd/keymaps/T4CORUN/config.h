/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
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

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_OLED_ENABLE



#if defined(RGBLIGHT_ENABLE)
//#   define RGBLIGHT_ANIMATIONS
//#   define RGBLIGHT_EFFECT_BREATHING
//#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#   define RGBLIGHT_LIMIT_VAL 120
#   define RGBLIGHT_HUE_STEP 10
#   define RGBLIGHT_SAT_STEP 17
#   define RGBLIGHT_VAL_STEP 17
#endif //RGBLIGHT_ENABLE

/*

#ifdef RGB_MATRIX_ENABLE
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true
#   define RGB_MATRIX_KEYPRESSES
//#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

    // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash. 
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 8
#   define RGB_MATRIX_SPD_STEP 10

    //First undefine all the RGB Animations
#   undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#   undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   undef ENABLE_RGB_MATRIX_BREATHING
#   undef ENABLE_RGB_MATRIX_BAND_SAT
#   undef ENABLE_RGB_MATRIX_BAND_VAL
#   undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   undef ENABLE_RGB_MATRIX_CYCLE_ALL
#   undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   undef ENABLE_RGB_MATRIX_DUAL_BEACON
#   undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   undef ENABLE_RGB_MATRIX_RAINDROPS
#   undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   undef ENABLE_RGB_MATRIX_HUE_BREATHING
#   undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#   undef ENABLE_RGB_MATRIX_HUE_WAVE
#   undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#   undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#   undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    //enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#   undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    //enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   undef ENABLE_RGB_MATRIX_SPLASH
#   undef ENABLE_RGB_MATRIX_MULTISPLASH
#   undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#   undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

    // RGB Matrix Animation modes. Explicitly enabled
    // For full list of effects, see:
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#endif

*/

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"


