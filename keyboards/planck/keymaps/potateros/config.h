#pragma once

#define MANUFACTURER    OLKB x potateros lol
#define PRODUCT         Wafflerinator 3000
// #define TAPPING_TERM 100
#define LEADER_TIMEOUT 400
#define DYNAMIC_MACRO_NO_NESTING

#ifdef AUDIO_ENABLE
   #define STARTUP_SONG SONG(STARTUP_SOUND)
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

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
// #define ENCODER_RESOLUTION 4
