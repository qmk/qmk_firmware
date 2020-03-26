#pragma once

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

// My custom configurations
// #define TAPPING_TOGGLE 3 // enable tapping toggle, used to lock level with a custom keycode defined by TT (in my case RAISE, LOWER and MOUSE)
// #define USB_MAX_POWER_CONSUMPTION 100 // required to be able to use the keyboard with iPad

// Settings for using the keybaord as a mouse
// #define MOUSEKEY_DELAY 30
// Delay between pressing a movement key and cursor movement
// #define MOUSEKEY_INTERVAL 16
// Time between cursor movements
// #define MOUSEKEY_MAX_SPEED  3
// Maximum cursor speed at which acceleration stops
// #define MOUSEKEY_TIME_TO_MAX 40
// Time until maximum cursor speed is reached
// #define MOUSEKEY_WHEEL_MAX_SPEED 0
// Maximum number of scroll steps per scroll action
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 0
// Time until maximum scroll speed is reached
