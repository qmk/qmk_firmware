/* Copyright 2020 Takeshi Nishio
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

// double tap to toggle
#define TAPPING_TOGGLE 2

// time for long press
#define TAPPING_TERM 200

#ifdef AUDIO_ENABLE
// Music-Modeは使用しないので、mapいらない
// music map for music-mode
// #   define MUSIC_MAP
  #undef AUDIO_CLICKY
#endif

// #ifdef RGB_DI_PIN
//     #undef RGBLED_NUM
//     #define RGBLED_NUM 12 // Left(4) + Under(8)

//     #undef RGBLIGHT_LED_MAP // Left --> Under, no need to re-map leds
// #endif

#define RGBLIGHT_MAX_LAYERS 10


#ifdef MIDI_ENABLE
/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

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
#   define MIDI_ADVANCED
#endif
