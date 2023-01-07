#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"


#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(COLEMAK_SOUND), \
                                  SONG(QWERTY_SOUND), \
                                  SONG(AUDIO_ON_SOUND), \
                                  SONG(TERMINAL_SOUND), \
                                  SONG(NO_SOUND), \
                                  SONG(MUSIC_ON_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != MU_TOGG)


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

#endif

#ifndef TAPPING_TERM
#define TAPPING_TERM 200

#endif