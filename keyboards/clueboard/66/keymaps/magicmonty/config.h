#pragma once

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
  #define MIDI_BASIC
*/

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
#define MIDI_TONE_KEYCODE_OCTAVES 2

/*
  Setting the modified Space Cadet Parens for German layout

  Default is
  #define LSPO_KEY KC_9
  #define RSPC_KEY KC_0
*/
#define LSPO_KEY KC_8
#define RSPC_KEY KC_9
#define PERMISSIVE_HOLD
