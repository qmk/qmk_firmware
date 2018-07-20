#ifndef CONFIG_USER_H
#define CONFIG_USER_H


#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#define RGB_DI_PIN D3
#define RGBLED_NUM 16     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE


#if defined(KEYBOARD_lets_split_rev2)
#define USE_SERIAL
#undef USE_I2C

#define EE_HANDS
#endif

#if defined(KEYBOARD_planck_rev5)
#ifdef RGBLIGHT_ENABLE
#define NO_MUSIC_MODE
#endif // RGBLIGHT_ENABLE
#endif // KEYBOARD_planck_rev5


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
