#pragma once


#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#define RGB_DI_PIN B3
#define RGBLED_NUM 13     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses (will slow down matrix scan by a lot)
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
// #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true// turn off effects when suspended
// #define RGB_MATRIX_SKIP_FRAMES 1 // number of frames to skip when displaying animations (0 is full effect) if not defined defaults to 1
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define EECONFIG_RGB_MATRIX (uint32_t *)15
#endif

#if defined(KEYBOARD_lets_split_rev2)
#define USE_SERIAL
#undef USE_I2C

#define EE_HANDS
#endif

#if !defined(KEYBOARD_planck_light)
#ifdef RGBLIGHT_ENABLE
#define NO_MUSIC_MODE
#endif // RGBLIGHT_ENABLE
#endif // KEYBOARD_planck_light


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

#define TAP_CODE_DELAY 10
