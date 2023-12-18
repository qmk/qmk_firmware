#pragma once
#define TAPPING_TERM 200





/* Leader Key
   ========================================================================== */

// Activates the leader key
// #define LEADER_PER_KEY_TIMING
// resets the timeout after each key is tapped
// #define LEADER_TIMEOUT 240






/* Autoshifting
   ========================================================================== */

// This controls how long you have to hold a key before you get the shifted state.
#define AUTO_SHIFT_TIMEOUT 150

// Do not Auto Shift special keys -_, =+, [{, ]}, ;:, '", ,<, .>, and /?
// #define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
#define NO_AUTO_SHIFT_NUMERIC

// Do not Auto Shift alpha characters, which include A through Z.
// #define NO_AUTO_SHIFT_ALPHA

// Lower the Auto Shift timeout variable (down)
// AS_DOWN

// Raise the Auto Shift timeout variable (up)
// AS_UP

// Report your current Auto Shift timeout value
// AS_RPT

// Turns on the Auto Shift Function
// AS_ON

// Turns off the Auto Shift Function
// AS_OFF

// Toggles the state of the Auto Shift feature
// AS_TOGG


#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(COIN_SOUND)
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

