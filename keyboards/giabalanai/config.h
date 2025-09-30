/*
Copyright 2023 3araht

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

// Right side has to be the master since 1, LED data is output from right side, and 2, Audio pin is prepared on right side as a reserve.
#define MASTER_RIGHT

// for "Generic" Promicro to be detected correctly as lefthand side (slave)
#define SPLIT_USB_DETECT

#define RGBLIGHT_LAYERS

#ifdef RGB_MATRIX_ENABLE
/* ws2812 RGB MATRIX */
//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

// the max brightness setting has no effect on rgb_matrix_set_color().
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
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Audio */
#ifdef AUDIO_ENABLE
#   define AUDIO_PIN B5  // use EX1 = PB5 = PIN9 as Audio output
// #define DAC_SAMPLE_MAX 32768U
#   define DAC_SAMPLE_MAX 65535U
// #define AUDIO_CLICKY
#   define NO_MUSIC_MODE
// #define STARTUP_SONG SONG(FANTASIE_IMPROMPTU)
// #define STARTUP_SONG SONG(NOCTURNE_OP_9_NO_1)
// #define STARTUP_SONG SONG(USSR_ANTHEM)
// #define STARTUP_SONG SONG(CAMPANELLA)
#endif

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

/* 2021/01/22 added to shrink firmware size */
// NO_ACTION_TAPPING -1964 bytes, however, this disables Layer mods...
// #define NO_ACTION_TAPPING
// NO_ACTION_ONESHOT -388 bytes
#define NO_ACTION_ONESHOT
