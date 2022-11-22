/* Copyright 2022 3araht
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

/* Handedness by Pin */
/* pull-up: left side,   pull-down: right side */
#define SPLIT_HAND_PIN GP28

/* test matrix scan speed */
// #define DEBUG_MATRIX_SCAN_RATE

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN GP0
// #define SERIAL_USART_TX_PIN GP0
#define SELECT_SOFT_SERIAL_SPEED 1
/*Sets the protocol speed when using serial communication*/
//Speeds:
//0: about 189kbps (Experimental only)
//1: about 137kbps (default)
//2: about 75kbps
//3: about 39kbps
//4: about 26kbps
//5: about 20kbps

// Right side has to be the master since 1, LED data is output from right side, and 2, Audio pin is prepared on right side as a reserve.
#define MASTER_RIGHT

// 2022/03/28 added. This might solve the "no left side communication via TRRS" issue.
// #define SPLIT_USB_DETECT
// SPLIT_USB_DETECT was not necessary since it is "Enabled by default on ChibiOS/ARM."
/* (RP2040) Speedup boot sequence by avoiding to use SPLIT_USB_DETECT */
#define USB_VBUS_PIN GP24

//#define BACKLIGHT_PIN B7
//#define BACKLIGHT_LEVELS 3
//#define BACKLIGHT_BREATHING

/* ws2812 RGB LED */
#define RGB_DI_PIN GP6
#define RGBLED_NUM 123
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

#ifdef RGB_MATRIX_ENABLE

/* ws2812 RGB MATRIX */
#   define DRIVER_LED_TOTAL 123
#   define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50

// the above brighness setting has no effect on rgb_matrix_set_color().
// Use darker colors instead.
/*              RGB darker COLORS             */
#   define RGB_DARKWHITE 0x66, 0x66, 0x66
#   define RGB_DARKRED 0x66, 0x0, 0x0
#   define RGB_DARKCORAL 0x66, 0x31, 0x1E
#   define RGB_DARKORANGE 0x66, 0x33, 0x0
#   define RGB_DARKGOLDENROD 0x56, 0x42, 0xD
#   define RGB_DARKGOLD 0x66, 0x56, 0x0
#   define RGB_DARKYELLOW 0x66, 0x66, 0x0
#   define RGB_DARKCHARTREUSE 0x33, 0x66, 0x0
#   define RGB_DARKGREEN 0x0, 0x66, 0x0
#   define RGB_DARKSPRINGGREEN 0x0, 0x66, 0x33
#   define RGB_DARKTURQUOISE 0x1C, 0x2C, 0x2A
#   define RGB_DARKTEAL 0x0, 0x33, 0x33
#   define RGB_DARKCYAN 0x0, 0x66, 0x66
#   define RGB_DARKAZURE 0x3D, 0x62, 0x66
#   define RGB_DARKBLUE 0x0, 0x0, 0x66
#   define RGB_DARKPURPLE 0x30, 0x0, 0x66
#   define RGB_DARKMAGENTA 0x66, 0x0, 0x66
#   define RGB_DARKPINK 0x66, 0x33, 0x4C

//  https://docs.qmk.fm/#/feature_rgb_matrix
//  Enable suspend mode.
// #    define RGB_DISABLE_WHEN_USB_SUSPENDED true

#   define ENABLE_RGB_MATRIX_SOLID_COLOR
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT  // white background ver. of _BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS  //White ver of above.
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif  // RGB_MATRIX_ENABLE

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
//#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
#ifdef MIDI_ENABLE
#    define MIDI_ADVANCED
// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#    define MIDI_INITIAL_VELOCITY 117
#endif  //  MIDI_ENABLE

/* via layer setting */
/* default: 4 */
#ifdef VIA_ENABLE
#   define DYNAMIC_KEYMAP_LAYER_COUNT 12
#endif  //  VIA_ENABLE

/*
 * Encoder options
 */
#ifdef ENCODER_ENABLE
#   define ENCODERS_PAD_A { }
#   define ENCODERS_PAD_B { }
#   define ENCODER_RESOLUTIONS { }
#   define ENCODERS_PAD_A_RIGHT { GP2 }
#   define ENCODERS_PAD_B_RIGHT { GP3 }
#   define ENCODER_RESOLUTIONS_RIGHT { 4 }
#   define TAP_CODE_DELAY 10
#endif  // ENCODER_ENABLE

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
