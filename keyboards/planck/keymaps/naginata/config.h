#pragma once

#undef PRODUCT
#define PRODUCT         Planck Naginata Style

// 薙刀式
// #define DEUCALYN
// #define NAGINATA_TATEGAKI
#define NAGINATA_YOKOGAKI
#define DSRLBY
// #define NAGINATA_EDIT_WIN // JP106
#define NAGINATA_EDIT_MAC // US101
#define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合
#define COMBO_COUNT 10
#define COMBO_TERM 40
// 薙刀式

// #define TAPPING_FORCE_HOLD
#define TAPPING_TERM 0
#define PERMISSIVE_HOLD
#define RETRO_TAPPING
#define TAPPING_TOGGLE 2

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

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
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

