/* Copyright 2021 3araht
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

#define MASTER_RIGHT
#ifndef MASTER_RIGHT
//  SPLIT_HAND_MATRIX_GRID was initially designed to use with left hand side diode D35 mounted and not pressing K7 on the right hand side during boot. However when a USB cable is reconnected immediately, it fails. Decided to use "MASTER_RIGHT" to make it more reliable.
#   define SPLIT_HAND_MATRIX_GRID B5, D0
#endif

#define SPLIT_USB_DETECT

#ifdef RGB_MATRIX_ENABLE
//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

// the max brightness setting has no effect on rgb_matrix_set_color().
// Use darker colors instead.
/*              RGB darker COLORS             */
#   define RGB_DARKWHITE 0x33, 0x33, 0x33
#   define RGB_DARKRED 0x33, 0x0, 0x0
#   define RGB_DARKCORAL 0x33, 0x18, 0xF
#   define RGB_DARKORANGE 0x33, 0x19, 0x0
#   define RGB_DARKGOLDENROD 0x2B, 0x21, 0x6
#   define RGB_DARKGOLD 0x33, 0x2B, 0x0
#   define RGB_DARKYELLOW 0x33, 0x33, 0x0
#   define RGB_DARKCHARTREUSE 0x19, 0x33, 0x0
#   define RGB_DARKGREEN 0x0, 0x33, 0x0
#   define RGB_DARKSPRINGGREEN 0x0, 0x33, 0x19
#   define RGB_DARKTURQUOISE 0xE, 0x16, 0x15
#   define RGB_DARKTEAL 0x0, 0x19, 0x19
#   define RGB_DARKCYAN 0x0, 0x33, 0x33
#   define RGB_DARKAZURE 0x1E, 0x31, 0x33
#   define RGB_DARKBLUE 0x0, 0x0, 0x33
#   define RGB_DARKPURPLE 0x18, 0x0, 0x33
#   define RGB_DARKMAGENTA 0x33, 0x0, 0x33
#   define RGB_DARKPINK 0x33, 0x19, 0x26

//  https://docs.qmk.fm/#/feature_rgb_matrix

#   ifdef CONSOLE_ENABLE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   else
// #define ENABLE_RGB_MATRIX_ALPHAS_MODS
#       define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#       define ENABLE_RGB_MATRIX_BREATHING
#       define ENABLE_RGB_MATRIX_BAND_SAT
#       define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#       define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#       define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#       define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#       define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#       define ENABLE_RGB_MATRIX_SPLASH
#       define ENABLE_RGB_MATRIX_SOLID_SPLASH
//  RAINDROPS don't match well with layer LED indicator (oc) using rgb_matrix_set_color().
// #define ENABLE_RGB_MATRIX_RAINDROPS
// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
//  Recommended not to use these.
#       ifndef VIA_ENABLE
#           define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#           define ENABLE_RGB_MATRIX_BAND_VAL
#           define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#           define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#           define ENABLE_RGB_MATRIX_CYCLE_ALL
#           define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#           define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#           define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#           define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#           define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#           define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#           define ENABLE_RGB_MATRIX_DUAL_BEACON
#           define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#           define ENABLE_RGB_MATRIX_HUE_BREATHING
#           define ENABLE_RGB_MATRIX_HUE_PENDULUM
#           define ENABLE_RGB_MATRIX_HUE_WAVE
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#           define ENABLE_RGB_MATRIX_MULTISPLASH
#           define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#       endif
#   endif  // CONSOLE_ENABLE
#endif  // RGB_MATRIX_ENABLE

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

/* 2021/01/22 added to shrink firmware size */
// NO_ACTION_TAPPING -1964 bytes, however, this disables Layer mods...
// #define NO_ACTION_TAPPING
// NO_ACTION_ONESHOT -388 bytes
#define NO_ACTION_ONESHOT

#ifdef MIDI_ENABLE
#   define MIDI_ADVANCED
// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#   define MIDI_INITIAL_VELOCITY 117
#endif  //  MIDI_ENABLE
