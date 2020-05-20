#pragma once

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { F4, F5, D1, D0 }
#define MATRIX_COL_PINS { D4, C6, D7, D2, B4, B5, B6, B2, B3, B1, F7, F6 }
#define UNUSED_PINS



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

