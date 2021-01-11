#pragma once

#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#    define RGB_DI_PIN B3
#    define RGBLED_NUM 13  // Number of LEDs
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP 12
#    define RGBLIGHT_SAT_STEP 12
#    define RGBLIGHT_VAL_STEP 12
#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#    ifdef RGB_MATRIX_ENABLE
#        define RGBLIGHT_DISABLE_KEYCODES
#    endif
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses (will slow down matrix scan by a lot)
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
#endif

#if defined(KEYBOARD_lets_split_rev2)
#    define USE_SERIAL
#    undef USE_I2C
#    define EE_HANDS
#endif

#if !defined(KEYBOARD_planck_light)
#    ifdef RGBLIGHT_ENABLE
#        define NO_MUSIC_MODE
#    endif  // RGBLIGHT_ENABLE
#endif      // KEYBOARD_planck_light

#if defined(KEYBOARD_planck)
#    undef PRODUCT
#    if defined(KEYBOARD_planck_light)
#        define PRODUCT Drashna Hacked RGB Beacon(Planck Light)
#    elif defined(KEYBOARD_planck_rev6)
#        define PRODUCT Drashna Hacked Planck Rev6
#    elif defined(KEYBOARD_planck_ez)
#        define PRODUCT Drashna Hacked Planck EZ
#    endif
#endif

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

// #define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2
