/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Use custom magic number so that when switching branches, EEPROM always gets reset
#define EECONFIG_MAGIC_NUMBER (uint16_t)0x1339

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

#if defined(SPLIT_KEYBOARD)
#    define SPLIT_MODS_ENABLE
// #    define SPLIT_TRANSPORT_MIRROR
#    define SERIAL_USE_MULTI_TRANSACTION
// #    define SPLIT_NUM_TRANSACTIONS_KB 2
#endif

#ifdef AUDIO_ENABLE

#    define AUDIO_CLICKY
#    define STARTUP_SONG SONG(RICK_ROLL)
#    define GOODBYE_SONG SONG(SONIC_RING)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND), SONG(OVERWATCH_THEME) }

#    define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f

#    define UNICODE_SONG_MAC SONG(RICK_ROLL)
#    define UNICODE_SONG_LNX SONG(RICK_ROLL)
#    define UNICODE_SONG_WIN SONG(RICK_ROLL)
#    define UNICODE_SONG_BSD SONG(RICK_ROLL)
#    define UNICODE_SONG_WINC SONG(RICK_ROLL)
#endif  // !AUDIO_ENABLE

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    if defined(__AVR__) && !defined(__AVR_AT90USB1286__)
#        undef RGBLIGHT_ANIMATIONS
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#    else
#        define RGBLIGHT_ANIMATIONS
#    endif
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses (will slow down matrix scan by a lot)
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
// #   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
// #   define EECONFIG_RGB_MATRIX (uint32_t *)16

#    if defined(__AVR__) && !defined(__AVR_AT90USB1286__) && !defined(KEYBOARD_launchpad)
#        define DISABLE_RGB_MATRIX_ALPHAS_MODS
#        define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
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
// #        define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
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

#ifdef OLED_DRIVER_ENABLE
#    ifdef SPLIT_KEYBOARD
#        define OLED_UPDATE_INTERVAL 60
#    else
#        define OLED_UPDATE_INTERVAL 15
#    endif
#    define OLED_DISABLE_TIMEOUT
#    define OLED_FONT_H "drashna_font.h"
#    define OLED_FONT_END 255
// #    define OLED_FONT_5X5
// #    define OLED_FONT_AZTECH
// #    define OLED_FONT_BMPLAIN
// #    define OLED_FONT_SUPER_DIGG
// #    define OLED_LOGO_GMK_BAD
// #    define OLED_LOGO_HUE_MANITEE
// #    define OLED_LOGO_CORNE
// #    define OLED_LOGO_GOTHAM
#    define OLED_LOGO_SCIFI
#endif

#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 3000
#endif  // !ONESHOT_TIMEOUT

#ifdef QMK_KEYS_PER_SCAN
#    undef QMK_KEYS_PER_SCAN
#    define QMK_KEYS_PER_SCAN 2
#endif  // !QMK_KEYS_PER_SCAN

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING
#define TAPPING_TERM_PER_KEY

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

#ifdef CONVERT_TO_PROTON_C
// pins that are available but not present on Pro Micro
#    define A3 PAL_LINE(GPIOA, 3)
#    define A4 PAL_LINE(GPIOA, 4)
#    define A5 PAL_LINE(GPIOA, 5)
#    define A6 PAL_LINE(GPIOA, 6)
#    define A7 PAL_LINE(GPIOA, 7)
#    define A8 PAL_LINE(GPIOA, 8)
#    define A13 PAL_LINE(GPIOA, 13)
#    define A14 PAL_LINE(GPIOA, 14)
#    define A15 PAL_LINE(GPIOA, 15)
#    define B10 PAL_LINE(GPIOB, 10)
#    define B11 PAL_LINE(GPIOB, 11)
#    define B12 PAL_LINE(GPIOB, 12)
#    define C13 PAL_LINE(GPIOC, 13)
#    define C14 PAL_LINE(GPIOC, 14)
#    define C15 PAL_LINE(GPIOC, 15)
#endif
