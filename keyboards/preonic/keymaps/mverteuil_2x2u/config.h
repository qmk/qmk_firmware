#ifdef AUDIO_ENABLE
#    if __has_include("copyright.h")
#        include "copyright.h"
#    endif

#    define AUDIO_CLICKY_DELAY_DURATION 0
#    define AUDIO_CLICKY_FREQ_DEFAULT 100.0f
#    define AUDIO_CLICKY_FREQ_MIN 61.0f
#    define AUDIO_CLICKY_FREQ_RANDOMNESS 0.2f
#    define DAC_SAMPLE_MAX 7000U
#    define STARTUP_SONG SONG(WORKMAN_SOUND)
#    define GOODBYE_SONG SONG(COIN_SOUND)
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
