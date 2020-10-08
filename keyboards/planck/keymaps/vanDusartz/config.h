#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define TAPPING_TERM 180 // Number of miliseconds to register a tap vs hold
// #define RETRO_TAPPING    // tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
#define PERMISSIVE_HOLD  // makes tap and hold keys work better for fast typers who don't want tapping term set above 500

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif


/* The default speed for controlling the mouse with the keyboard is intentionally slow.
You can adjust these parameters by adding these settings to your keymap's config.h file.
All times are specified in milliseconds (ms). */
#define MOUSEKEY_DELAY             300 // When one of the mouse movement buttons is pressed this setting is used to define the delay between that button press and the mouse cursor moving. Some people find that small movements are impossible if this setting is too low, while settings that are too high feel sluggish.
#define MOUSEKEY_INTERVAL           50 // When a movement key is held down this specifies how long to wait between each movement report. Lower settings will translate into an effectively higher mouse speed.
#define MOUSEKEY_MAX_SPEED          10 // As a movement key is held down the speed of the mouse cursor will increase until it reaches MOUSEKEY_MAX_SPEED.
#define MOUSEKEY_TIME_TO_MAX        20 // How long you want to hold down a movement key for until MOUSEKEY_MAX_SPEED is reached. This controls how quickly your cursor will accelerate.
#define MOUSEKEY_WHEEL_MAX_SPEED     8 // The top speed for scrolling movements.
#define MOUSEKEY_WHEEL_TIME_TO_MAX  40 // How long you want to hold down a scroll key for until MOUSEKEY_WHEEL_MAX_SPEED is reached. This controls how quickly your scrolling will accelerate.


#define MUSIC_MASK (keycode != KC_NO)

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

#endif
