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
//#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef BACKLIGHT_PIN
#define MATRIX_ROW_PINS { B2, E6, B3, B7, D0 }
#define MATRIX_COL_PINS { D1, D2, D3, C6, D7, B4, B5, B6, F7, F6, F5, F4 }

//#define TAPPING_TERM 200
//#define TAPPING_TOGGLE 2

#endif
