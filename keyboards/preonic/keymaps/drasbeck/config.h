/*
Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) 2020 Max Drasbeck 
 *
 * You are free to:
 *
 *  Share — copy and redistribute the material in any medium or format
 *  Adapt — remix, transform, and build upon the material
 *   for any purpose, even commercially.
 *
 * The licensor cannot revoke these freedoms as long as you follow the license terms.
*/

#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) }//,
                                 //  SONG(COLEMAK_SOUND),
                                 //  SONG(DVORAK_SOUND)
                                //}
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
