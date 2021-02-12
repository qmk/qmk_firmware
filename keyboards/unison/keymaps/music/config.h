/* Copyright 2021 Takeshi Nishio
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

// time for long press
#define TAPPING_TERM 200

#ifdef AUDIO_ENABLE
    #define MUSIC_MAP
#endif

#ifdef RGB_DI_PIN
    // // settings for adding Underglow
    // #undef RGBLED_NUM
    // #define RGBLED_NUM 15 // Layer Indicator(2) + Rotary Encoder(5) + Under(8)

    // #undef RGBLIGHT_LED_MAP
    // #define RGBLIGHT_LED_MAP {1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} // Left to Right to Under Right to Under Left
#endif

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
#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
    #define MIDI_ADVANCED
#endif


#ifdef NKRO_ENABLE
    #define FORCE_NKRO
#endif

#ifdef SEQUENCER_ENABLE
    #define SEQUENCER_STEPS 32  // default: 16
    #define SEQUENCER_TRACKS 8
#endif
