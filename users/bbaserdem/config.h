/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

/* CONFIG
 * Common hardware configuration accross my boards
 */
// Space saving
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif
// Unicode entry mode
#ifdef UNICODEMAP_ENABLE
    #define UNICODE_SELECTED_MODES UC_LNX
    // Adapt the unicode entry mode to dvorak
    #ifdef UNICODE_KEY_LNX
    #undef UNICODE_KEY_LNX
    #endif
    #define UNICODE_KEY_LNX LCTL(LSFT(KC_F))
#endif

// Mousekey mode
#ifdef MOUSEKEY_ENABLE
    #define MK_COMBINED
#endif

// Tap-hold settings
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 20
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

// Encoder settings
#ifdef ENCODER_ENABLE
    #define ENCODER_RESOLUTION 2
#endif

// Backlight settings
#ifdef BACKLIGHT_ENABLE
    // Turn on breathing only if audio is not enabled, due to hardware stuff
    #ifndef AUDIO_ENABLE
        #define BACKLIGHT_BREATHING
        #define BREATHING_PERIOD 5
    #endif
#endif

// Enable RGB LED sleep mode
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    #define RGB_DISABLE_WHEN_USB_SUSPENDED true
#endif

// Audio definitions
#ifdef AUDIO_ENABLE
    // Make findable songs as defaults
    #ifdef HOROLOGY
    #define STARTUP_SONG    SONG(HOROLOGY)
    #endif
    #ifdef PEOPLE_VULTURES
    #define GOODBYE_SONG    SONG(PEOPLE_VULTURES)
    #endif
    #ifdef NONAGON_INFINITY
    #define MUSIC_ON_SONG   SONG(NONAGON_INFINITY)
    #endif
    #ifdef WAH_WAH
    #define MUSIC_OFF_SONG  SONG(WAH_WAH)
    #endif
    // Audio code expects these to be defined
    #ifdef BIG_FIG_WASP
    #define GAME_ON_SONG    SONG(BIG_FIG_WASP)
    #else
    #define GAME_ON_SONG    SONG(USSR_ANTHEM)
    #endif
    #ifdef POLYGONDWANALAND
    #define GAME_OFF_SONG   SONG(POLYGONDWANALAND)
    #else
    #define GAME_OFF_SONG   SONG(NOCTURNE_OP_9_NO_1)
    #endif
#endif

// For underglow light
#ifdef RGBLIGHT_ENABLE
    // Enable animations
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_TWINKLE
    // Enable layer switching code
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_MAX_LAYERS 10
    #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
    // If these are not defined; just default to entire board for layer 
    #define RGBLIGHT_LEFT_BEG 0
    #define RGBLIGHT_LEFT_NUM RGBLED_NUM
    #define RGBLIGHT_RIGHT_BEG 0
    #define RGBLIGHT_RIGHT_NUM RGBLED_NUM
#endif

// For perkey leds
#ifdef RGB_MATRIX_ENABLE
    // Start using this mode
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_BEACON
    #define RGB_MATRIX_STARTUP_HUE 100
    #define RGB_MATRIX_STARTUP_SAT 255
    #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    // Some config options
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_KEYRELEASES
    // Disable some animation modes
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define DISABLE_RGB_MATRIX_BAND_RAINDROPS
    #define DISABLE_RGB_MATRIX_BAND_JELLYBEAN_RAINDROPS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#endif
