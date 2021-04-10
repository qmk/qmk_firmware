#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)

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


/* Ignore Mod Tap Interrupt
https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold

For Instance:
SFT_T(KC_A) Down
KC_X Down
SFT_T(KC_A) Up
KC_X Up
Normally, this would send a capital X (SHIFT+x), or, Mod + key. With Ignore Mod Tap Interrupt enabled,
holding both keys are required for the TAPPING_TERM to register the hold action.
A quick tap will output ax in this case, while a hold on both will still output capital X (SHIFT+x).
*/
#define IGNORE_MOD_TAP_INTERRUPT
