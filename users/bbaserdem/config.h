/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#   define NO_DEBUG
#endif

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#   define NO_PRINT
#endif

// Some of my own settings
# define HOUSEKEEPING_THROTTLE_INTERVAL_MS 250

// Split transport settings
#ifdef SPLIT_KEYBOARD
#   define SPLIT_TRANSPORT_MIRROR
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_MODS_ENABLE
#   define SPLIT_TRANSACTION_IDS_USER RPC_ID_CONFIG_SYNC, RPC_ID_RUNTIME_SYNC, RPC_ID_KEYMAP_SYNC
#   define SPLIT_LED_STATE_ENABLE
#   ifdef WPM_ENABLE
#       define SPLIT_WPM_ENABLE
#   endif // WPM_ENABLE
#   ifdef OLED_ENABLE
#       define SPLIT_OLED_ENABLE
#   endif // OLED_ENABLE
#endif // SPLIT_KEYBOARD

// Unicode entry mode
#ifdef UNICODEMAP_ENABLE
#   define UNICODE_SELECTED_MODES UC_LNX
    // Adapt the unicode entry mode to dvorak
#   ifdef UNICODE_KEY_LNX
#   undef UNICODE_KEY_LNX
#   endif
#   define UNICODE_KEY_LNX LCTL(LSFT(KC_F))
#endif // UNICODEMAP_ENABLE

// Mousekey mode
#ifdef MOUSEKEY_ENABLE
#   define MK_COMBINED
#endif // MOUSEKEY_ENABLE

// Tap-hold settings
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 20
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

// Backlight settings
#ifdef BACKLIGHT_ENABLE
#   define BACKLIGHT_BREATHING
#   define BREATHING_PERIOD 5
#endif // BACKLIGHT_ENABLE

// Audio definitions
#ifdef AUDIO_ENABLE
//#   define AUDIO_ENABLE_TONE_MULTIPLEXING
    // Make findable songs as defaults
#   ifdef HOROLOGY
#   define STARTUP_SONG    SONG(HOROLOGY)
#   endif
#   ifdef PEOPLE_VULTURES
#   define GOODBYE_SONG    SONG(PEOPLE_VULTURES)
#   endif
#   ifdef NONAGON_INFINITY
#   define MUSIC_ON_SONG   SONG(NONAGON_INFINITY)
#   endif
#   ifdef WAH_WAH
#   define MUSIC_OFF_SONG  SONG(WAH_WAH)
#   endif
    // Audio code expects these to be defined
#   ifdef BIG_FIG_WASP
#   define GAME_ON_SONG    SONG(BIG_FIG_WASP)
#   else
#   define GAME_ON_SONG    SONG(USSR_ANTHEM)
#   endif
#   ifdef POLYGONDWANALAND
#   define GAME_OFF_SONG   SONG(POLYGONDWANALAND)
#   else
#   define GAME_OFF_SONG   SONG(NOCTURNE_OP_9_NO_1)
#   endif
#endif // AUDIO_ENABLE

// OLED definitions
#ifdef OLED_ENABLE
    // Timeout does not work for split secondary board; i implemented it myself
#   define OLED_TIMEOUT 30000
    // Fade out the screen when timing out
#   define OLED_FADE_OUT
#   define OLED_FADE_OUT_INTERVAL 15
#endif // OLED_ENABLE

// For perkey leds
#ifdef RGB_MATRIX_ENABLE
// This is not working
//#   define RGB_DISABLE_TIMEOUT 1800000
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true
    // Start using this mode
#   define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_BEACON
#   define RGB_MATRIX_STARTUP_HUE 100
#   define RGB_MATRIX_STARTUP_SAT 255
#   define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    // Some config options
#   define RGB_MATRIX_KEYRELEASES
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS      // Enable framebuffer effects
#endif // RGB_MATRIX_ENABLE
