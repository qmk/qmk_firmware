#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    //#define STARTUP_SONG SONG(PREONIC_SOUND)
    #define STARTUP_SONG SONG(NO_SOUND)

#endif

#define TAPPING_TERM 200

#define MUSIC_MASK (keycode != KC_NO)

#define COPY      LCTL(KC_C)
#define PASTE     LCTL(KC_V)
#define T_PREV    LCTL(KC_PGUP)
#define T_NEXT    LCTL(KC_PGDN)
#define N_TAB     LCTL(KC_T)
#define W_QUIT    LALT(KC_F4)

#define ALL       LCTL(KC_A)

#define E_BACK     S(A(KC_LEFT))
#define E_FORWARD  S(A(KC_RIGHT))

#define SWITCH    LALT(KC_ESC)
#define TERMINAL  RGUI(KC_T)

#define OSUP      LCTL(LALT(KC_UP))
#define OSDOWN    LCTL(LALT(KC_DOWN))

#define PUSH_2_TALK LCTL(KC_F23)

#define MOUSEKEY_INTERVAL           20
#define MOUSEKEY_DELAY              100
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          7
#define MOUSEKEY_WHEEL_MAX_SPEED    5
#define MOUSEKEY_WHEEL_TIME_TO_MAX  60
#define MOUSEKEY_WHEEL_DELAY        100

#define UNICODE_SELECTED_MODES UC_LNX

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
