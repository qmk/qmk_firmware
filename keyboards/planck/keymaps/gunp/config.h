#pragma once

/* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TAP_TOGGLE 7
/* Time (in ms) before the one shot key is released */
#define ONESHOT_TIMEOUT 5000

/* Sets the amount of memory that Dynamic Macros can use.
   This is a limited resource, dependent on the controller. */
#define DYNAMIC_MACRO_SIZE 4096
/* Defining this falls back to using the user `keymap.c` file
   to trigger the macro behaviour. */
#define DYNAMIC_MACRO_USER_CALL

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    /* #define UNICODE_SONG_LNX  UNICODE_LINUX */
    /* #define UNICODE_SONG_WIN  UNICODE_WINDOWS */
    /* #define UNICODE_SONG_MAC  TERMINAL_SOUND */
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
#define ENCODER_RESOLUTION 4

