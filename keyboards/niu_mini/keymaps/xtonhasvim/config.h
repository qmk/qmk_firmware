#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

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

// help for fast typist+dual function keys?
#define PERMISSIVE_HOLD

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* speed up mousekeys a bit */
#define MOUSEKEY_DELAY             50
#define MOUSEKEY_INTERVAL          20
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       30
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

#endif
