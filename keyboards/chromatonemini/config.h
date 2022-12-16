/*
Copyright 2021 3araht

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

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
// #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

//#define LED_NUM_LOCK_PIN B0
//#define LED_CAPS_LOCK_PIN B1
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

//#define BACKLIGHT_PIN B7
//#define BACKLIGHT_LEVELS 3
//#define BACKLIGHT_BREATHING

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
//#ifdef RGB_DI_PIN
//#    define RGBLED_NUM 16
//#    define RGBLIGHT_HUE_STEP 8
//#    define RGBLIGHT_SAT_STEP 8
//#    define RGBLIGHT_VAL_STEP 8
//#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
//#endif


#ifdef RGB_MATRIX_ENABLE

/* ws2812 RGB MATRIX */
#   define RGB_MATRIX_LED_COUNT 116

 // reacts to keypresses
#   define RGB_MATRIX_KEYPRESSES

//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#   define RGB_MATRIX_DEFAULT_SPD 127
#   define RGB_MATRIX_CENTER { 124, 32 }
// the above brighness setting has no effect on rgb_matrix_set_color().
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
//  Enable suspend mode.
#   define RGB_DISABLE_WHEN_USB_SUSPENDED

#   ifdef CONSOLE_ENABLE
#       define ENABLE_RGB_MATRIX_SOLID_COLOR
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   else
#       define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#       define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#       define ENABLE_RGB_MATRIX_BREATHING
#       define ENABLE_RGB_MATRIX_BAND_SAT
#       define ENABLE_RGB_MATRIX_BAND_VAL
#       define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#       define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#       define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#       define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#       define ENABLE_RGB_MATRIX_CYCLE_ALL
#       define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#       define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#       define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#       define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#       define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#       define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#       define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#       define ENABLE_RGB_MATRIX_DUAL_BEACON
#       define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#       define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#       define ENABLE_RGB_MATRIX_RAINDROPS
#       define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#       define ENABLE_RGB_MATRIX_HUE_BREATHING
#       define ENABLE_RGB_MATRIX_HUE_PENDULUM
#       define ENABLE_RGB_MATRIX_HUE_WAVE
#       define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#       define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#       define ENABLE_RGB_MATRIX_SPLASH
#       define ENABLE_RGB_MATRIX_MULTISPLASH
#       define ENABLE_RGB_MATRIX_SOLID_SPLASH
#       define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#   endif  // CONSOLE_ENABLE
#endif  // RGB_MATRIX_ENABLE

/* Audio */
#ifdef AUDIO_ENABLE
#   define AUDIO_PIN B6  // use PB6 = PIN10 as Audio output
// #define DAC_SAMPLE_MAX 32768U
#   define DAC_SAMPLE_MAX 65535U
// #define AUDIO_CLICKY
#   define NO_MUSIC_MODE
// #define STARTUP_SONG SONG(FANTASIE_IMPROMPTU)
// #define STARTUP_SONG SONG(NOCTURNE_OP_9_NO_1)
// #define STARTUP_SONG SONG(USSR_ANTHEM)
// #define STARTUP_SONG SONG(CAMPANELLA)
#endif  //  AUDIO_ENABLE

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
#   define MIDI_ADVANCED
// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#   define MIDI_INITIAL_VELOCITY 117
#endif  //  MIDI_ENABLE

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING

/* 2021/01/22 added to shrink firmware size */
// NO_ACTION_TAPPING -1964 bytes, however, this disables Layer mods...
// #define NO_ACTION_TAPPING
// NO_ACTION_ONESHOT -388 bytes
#define NO_ACTION_ONESHOT
