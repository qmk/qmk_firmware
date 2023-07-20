// Copyright 2021 Anton Kavalkou (@antosha417)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)
#endif

/*
 * MIDI options
 */

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
//#define MIDI_ADVANCED

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

#define TAPPING_TERM 200
#define COMBO_TERM 30

