#pragma once

#ifdef AUDIO_ENABLE
#    if __GNUC__ > 7
#        if __has_include("drashna_song_list.h")
#            include "drashna_song_list.h"
#        endif  // if file exists
#    endif      // __GNUC__

#    define AUDIO_CLICKY
#    define STARTUP_SONG SONG(RICK_ROLL)
#    define GOODBYE_SONG SONG(SONIC_RING)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND), SONG(OVERWATCH_THEME) }

#    define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f

#    define UNICODE_SONG_OSX SONG(RICK_ROLL)
#    define UNICODE_SONG_LNX SONG(RICK_ROLL)
#    define UNICODE_SONG_WIN SONG(RICK_ROLL)
#    define UNICODE_SONG_BSD SONG(RICK_ROLL)
#    define UNICODE_SONG_WINC SONG(RICK_ROLL)
#endif  // !AUDIO_ENABLE

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    undef RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses (will slow down matrix scan by a lot)
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
// #   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
// #   define EECONFIG_RGB_MATRIX (uint32_t *)16

#    if defined(__AVR__) && !defined(__AVR_AT90USB1286__)
#        define DISABLE_RGB_MATRIX_ALPHAS_MODS
#        define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define DISABLE_RGB_MATRIX_BREATHING
#        define DISABLE_RGB_MATRIX_BAND_SAT
#        define DISABLE_RGB_MATRIX_BAND_VAL
#        define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        define DISABLE_RGB_MATRIX_CYCLE_ALL
#        define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #       define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define DISABLE_RGB_MATRIX_DUAL_BEACON
#        define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#        define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        define DISABLE_RGB_MATRIX_RAINDROPS
#        define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #       define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#        define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define DISABLE_RGB_MATRIX_SPLASH
#        define DISABLE_RGB_MATRIX_MULTISPLASH
#        define DISABLE_RGB_MATRIX_SOLID_SPLASH
#        define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    endif  // AVR
#endif      // RGB_MATRIX_ENABLE

#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 3000
#endif  // !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
#    define QMK_KEYS_PER_SCAN 4
#endif  // !QMK_KEYS_PER_SCAN

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING

#define FORCE_NKRO

#ifndef TAPPING_TOGGLE
#    define TAPPING_TOGGLE 1
#endif

#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif  // TAPPING_TERM
#if defined(KEYBOARD_ergodox_ez)
#    define TAPPING_TERM 185
#elif defined(KEYBOARD_crkbd)
#    define TAPPING_TERM 200
#else
#    define TAPPING_TERM 175
#endif

#define TAP_CODE_DELAY 5

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
