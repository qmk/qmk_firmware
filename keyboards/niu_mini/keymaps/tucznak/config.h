#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#ifdef MANUFACTURER
#undef MANUFACTURER
#endif
#ifdef PRODUCT
#undef PRODUCT
#endif
#ifdef DESCRIPTION
#undef DESCRIPTION
#endif

#define MANUFACTURER    Potato Inc.
#define PRODUCT         Qt3.14
#define DESCRIPTION     Look, a keyboard!

/* turn off RGB when computer sleeps */
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif

/* send tap key if no layer key was used even after tap delay */
#define TAPPING_TERM 50
#define RETRO_TAPPING

//#define MUSIC_MASK (keycode != KC_NO)

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

#endif
