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

//tapdance
#define TAPPING_TERM 150

//backlight
#ifdef BACKLIGHT_ENABLE
    #define BACKLIGHT_PIN B7
	#define BACKLIGHT_LEVELS 3
    #define BACKLIGHT_ON_STATE 0
#endif	

#define USB_MAX_POWER_CONSUMPTION 100

#endif