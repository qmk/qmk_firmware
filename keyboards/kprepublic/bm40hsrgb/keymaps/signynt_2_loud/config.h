// qmk flash -kb bm40hsrgb -km signynt_2_loud

/* Copyright 2021 Vincenzo Mitchell Barroso
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

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_ANIMATIONS

//#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGBLIGHT_LIMIT_VAL 10

#ifdef RGB_MATRIX_ENABLE

#define TAPPING_TERM 200

//--------------------------------------------------------------------------------------------------------

//disable broken animations
#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    undef ENABLE_RGB_MATRIX_BREATHING
#    undef ENABLE_RGB_MATRIX_BAND_SAT
#    undef ENABLE_RGB_MATRIX_BAND_VAL
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    undef ENABLE_RGB_MATRIX_CYCLE_ALL
#    undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#    undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
//#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
//#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//#undef ENABLE_RGB_MATRIX_RAINDROPS
#    undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS  // DO NOT ENABLE
//#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
//#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
//#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
//#undef ENABLE_RGB_MATRIX_SPLASH
//#undef ENABLE_RGB_MATRIX_MULTISPLASH
//#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
//#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    undef RGB_MATRIX_STARTUP_MODE

#    define RGBLIGHT_HUE_STEP 20

#endif
