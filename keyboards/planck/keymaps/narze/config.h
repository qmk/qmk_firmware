#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

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

#define TAPPING_TERM 200

#define COMBO_TERM 20
#define COMBO_COUNT 1

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define PREVENT_STUCK_MODIFIERS

#define SUPER_DUPER_SOUND S__NOTE(_B1)

#define MOUSEKEY_DELAY 100

#endif