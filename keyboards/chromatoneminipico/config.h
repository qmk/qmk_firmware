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

/* ws2812 RGB LED */
#define RGB_DI_PIN GP12
#define RGBLED_NUM 116
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

#ifdef RGB_MATRIX_ENABLE

/* ws2812 RGB MATRIX */
#   define DRIVER_LED_TOTAL 116

 // reacts to keypresses
#   define RGB_MATRIX_KEYPRESSES

//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#   define RGB_MATRIX_STARTUP_SPD 127
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

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

// /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
// /* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

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

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

/* Audio */
#ifdef AUDIO_ENABLE
#   define AUDIO_PIN GP13
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
#endif  //  MIDI_ENABLE

/* 2021/01/22 added to shrink firmware size */
// NO_ACTION_TAPPING -1964 bytes, however, this disables Layer mods...
// #define NO_ACTION_TAPPING
// NO_ACTION_ONESHOT -388 bytes
#define NO_ACTION_ONESHOT

/* via layer setting */
/* default: 4 */
#define DYNAMIC_KEYMAP_LAYER_COUNT 12
