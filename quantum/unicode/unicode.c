/* Copyright 2022
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

#include "unicode.h"

#include "eeprom.h"
#include "eeconfig.h"
#include "action.h"
#include "action_util.h"
#include "host.h"
#include "keycode.h"
#include "wait.h"
#include "send_string.h"
#include "utf8.h"

#if defined(AUDIO_ENABLE)
#    include "audio.h"
#endif

#if defined(UNICODE_ENABLE) + defined(UNICODEMAP_ENABLE) + defined(UCIS_ENABLE) > 1
#    error "Cannot enable more than one Unicode method (UNICODE, UNICODEMAP, UCIS) at the same time"
#endif

// Keycodes used for starting Unicode input on different platforms
#ifndef UNICODE_KEY_MAC
#    define UNICODE_KEY_MAC KC_LEFT_ALT
#endif
#ifndef UNICODE_KEY_LNX
#    define UNICODE_KEY_LNX LCTL(LSFT(KC_U))
#endif
#ifndef UNICODE_KEY_WINC
#    define UNICODE_KEY_WINC KC_RIGHT_ALT
#endif

// Comma-delimited, ordered list of input modes selected for use (e.g. in cycle)
// Example: #define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX
#ifndef UNICODE_SELECTED_MODES
#    define UNICODE_SELECTED_MODES -1
#endif

// Whether input mode changes in cycle should be written to EEPROM
#ifndef UNICODE_CYCLE_PERSIST
#    define UNICODE_CYCLE_PERSIST true
#endif

// Delay between starting Unicode input and sending a sequence, in ms
#ifndef UNICODE_TYPE_DELAY
#    define UNICODE_TYPE_DELAY 10
#endif

unicode_config_t unicode_config;
uint8_t          unicode_saved_mods;
led_t            unicode_saved_led_state;

#if UNICODE_SELECTED_MODES != -1
static uint8_t selected[]     = {UNICODE_SELECTED_MODES};
static int8_t  selected_count = ARRAY_SIZE(selected);
static int8_t  selected_index;
#endif

/** \brief unicode input mode set at user level
 *
 * Run user code on unicode input mode change
 */
__attribute__((weak)) void unicode_input_mode_set_user(uint8_t input_mode) {}

/** \brief unicode input mode set at keyboard level
 *
 *  Run keyboard code on unicode input mode change
 */
__attribute__((weak)) void unicode_input_mode_set_kb(uint8_t input_mode) {
    unicode_input_mode_set_user(input_mode);
}

#ifdef AUDIO_ENABLE
#    ifdef UNICODE_SONG_MAC
static float song_mac[][2] = UNICODE_SONG_MAC;
#    endif
#    ifdef UNICODE_SONG_LNX
static float song_lnx[][2] = UNICODE_SONG_LNX;
#    endif
#    ifdef UNICODE_SONG_WIN
static float song_win[][2] = UNICODE_SONG_WIN;
#    endif
#    ifdef UNICODE_SONG_BSD
static float song_bsd[][2] = UNICODE_SONG_BSD;
#    endif
#    ifdef UNICODE_SONG_WINC
static float song_winc[][2] = UNICODE_SONG_WINC;
#    endif
#    ifdef UNICODE_SONG_EMACS
static float song_emacs[][2] = UNICODE_SONG_EMACS;
#    endif

static void unicode_play_song(uint8_t mode) {
    switch (mode) {
#    ifdef UNICODE_SONG_MAC
        case UNICODE_MODE_MACOS:
            PLAY_SONG(song_mac);
            break;
#    endif
#    ifdef UNICODE_SONG_LNX
        case UNICODE_MODE_LINUX:
            PLAY_SONG(song_lnx);
            break;
#    endif
#    ifdef UNICODE_SONG_WIN
        case UNICODE_MODE_WINDOWS:
            PLAY_SONG(song_win);
            break;
#    endif
#    ifdef UNICODE_SONG_BSD
        case UNICODE_MODE_BSD:
            PLAY_SONG(song_bsd);
            break;
#    endif
#    ifdef UNICODE_SONG_WINC
        case UNICODE_MODE_WINCOMPOSE:
            PLAY_SONG(song_winc);
            break;
#    endif
#    ifdef UNICODE_SONG_EMACS
        case UNICODE_MODE_EMACS:
            PLAY_SONG(song_emacs);
            break;
#    endif
    }
}
#endif

void unicode_input_mode_init(void) {
    unicode_config.raw = eeprom_read_byte(EECONFIG_UNICODEMODE);
#if UNICODE_SELECTED_MODES != -1
#    if UNICODE_CYCLE_PERSIST
    // Find input_mode in selected modes
    int8_t i;
    for (i = 0; i < selected_count; i++) {
        if (selected[i] == unicode_config.input_mode) {
            selected_index = i;
            break;
        }
    }
    if (i == selected_count) {
        // Not found: input_mode isn't selected, change to one that is
        unicode_config.input_mode = selected[selected_index = 0];
    }
#    else
    // Always change to the first selected input mode
    unicode_config.input_mode = selected[selected_index = 0];
#    endif
#endif
    unicode_input_mode_set_kb(unicode_config.input_mode);
    dprintf("Unicode input mode init to: %u\n", unicode_config.input_mode);
}

uint8_t get_unicode_input_mode(void) {
    return unicode_config.input_mode;
}

void set_unicode_input_mode(uint8_t mode) {
    unicode_config.input_mode = mode;
    persist_unicode_input_mode();
#ifdef AUDIO_ENABLE
    unicode_play_song(mode);
#endif
    unicode_input_mode_set_kb(mode);
    dprintf("Unicode input mode set to: %u\n", unicode_config.input_mode);
}

void cycle_unicode_input_mode(int8_t offset) {
#if UNICODE_SELECTED_MODES != -1
    selected_index = (selected_index + offset) % selected_count;
    if (selected_index < 0) {
        selected_index += selected_count;
    }
    unicode_config.input_mode = selected[selected_index];
#    if UNICODE_CYCLE_PERSIST
    persist_unicode_input_mode();
#    endif
#    ifdef AUDIO_ENABLE
    unicode_play_song(unicode_config.input_mode);
#    endif
    unicode_input_mode_set_kb(unicode_config.input_mode);
    dprintf("Unicode input mode cycle to: %u\n", unicode_config.input_mode);
#endif
}

void persist_unicode_input_mode(void) {
    eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config.input_mode);
}

__attribute__((weak)) void unicode_input_start(void) {
    unicode_saved_led_state = host_keyboard_led_state();

    // Note the order matters here!
    // Need to do this before we mess around with the mods, or else
    // UNICODE_KEY_LNX (which is usually Ctrl-Shift-U) might not work
    // correctly in the shifted case.
    if (unicode_config.input_mode == UNICODE_MODE_LINUX && unicode_saved_led_state.caps_lock) {
        tap_code(KC_CAPS_LOCK);
    }

    unicode_saved_mods = get_mods(); // Save current mods
    clear_mods();                    // Unregister mods to start from a clean state
    clear_weak_mods();

    switch (unicode_config.input_mode) {
        case UNICODE_MODE_MACOS:
            register_code(UNICODE_KEY_MAC);
            break;
        case UNICODE_MODE_LINUX:
            tap_code16(UNICODE_KEY_LNX);
            break;
        case UNICODE_MODE_WINDOWS:
            // For increased reliability, use numpad keys for inputting digits
            if (!unicode_saved_led_state.num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            register_code(KC_LEFT_ALT);
            wait_ms(UNICODE_TYPE_DELAY);
            tap_code(KC_KP_PLUS);
            break;
        case UNICODE_MODE_WINCOMPOSE:
            tap_code(UNICODE_KEY_WINC);
            tap_code(KC_U);
            break;
        case UNICODE_MODE_EMACS:
            // The usual way to type unicode in emacs is C-x-8 <RET> then the unicode number in hex
            tap_code16(LCTL(KC_X));
            tap_code16(KC_8);
            tap_code16(KC_ENTER);
            break;
    }

    wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak)) void unicode_input_finish(void) {
    switch (unicode_config.input_mode) {
        case UNICODE_MODE_MACOS:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UNICODE_MODE_LINUX:
            tap_code(KC_SPACE);
            if (unicode_saved_led_state.caps_lock) {
                tap_code(KC_CAPS_LOCK);
            }
            break;
        case UNICODE_MODE_WINDOWS:
            unregister_code(KC_LEFT_ALT);
            if (!unicode_saved_led_state.num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            break;
        case UNICODE_MODE_WINCOMPOSE:
            tap_code(KC_ENTER);
            break;
        case UNICODE_MODE_EMACS:
            tap_code16(KC_ENTER);
            break;
    }

    set_mods(unicode_saved_mods); // Reregister previously set mods
}

__attribute__((weak)) void unicode_input_cancel(void) {
    switch (unicode_config.input_mode) {
        case UNICODE_MODE_MACOS:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UNICODE_MODE_LINUX:
            tap_code(KC_ESCAPE);
            if (unicode_saved_led_state.caps_lock) {
                tap_code(KC_CAPS_LOCK);
            }
            break;
        case UNICODE_MODE_WINCOMPOSE:
            tap_code(KC_ESCAPE);
            break;
        case UNICODE_MODE_WINDOWS:
            unregister_code(KC_LEFT_ALT);
            if (!unicode_saved_led_state.num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            break;
        case UNICODE_MODE_EMACS:
            tap_code16(LCTL(KC_G)); // C-g cancels
            break;
    }

    set_mods(unicode_saved_mods); // Reregister previously set mods
}

// clang-format off

static void send_nibble_wrapper(uint8_t digit) {
    if (unicode_config.input_mode == UNICODE_MODE_WINDOWS) {
        uint8_t kc = digit < 10
                   ? KC_KP_1 + (10 + digit - 1) % 10
                   : KC_A + (digit - 10);
        tap_code(kc);
        return;
    }
    send_nibble(digit);
}

// clang-format on

void register_hex(uint16_t hex) {
    for (int i = 3; i >= 0; i--) {
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        send_nibble_wrapper(digit);
    }
}

void register_hex32(uint32_t hex) {
    bool first_digit        = true;
    bool needs_leading_zero = (unicode_config.input_mode == UNICODE_MODE_WINCOMPOSE);
    for (int i = 7; i >= 0; i--) {
        // Work out the digit we're going to transmit
        uint8_t digit = ((hex >> (i * 4)) & 0xF);

        // If we're still searching for the first digit, and found one
        // that needs a leading zero sent out, send the zero.
        if (first_digit && needs_leading_zero && digit > 9) {
            send_nibble_wrapper(0);
        }

        // Always send digits (including zero) if we're down to the last
        // two bytes of nibbles.
        bool must_send = i < 4;

        // If we've found a digit worth transmitting, do so.
        if (digit != 0 || !first_digit || must_send) {
            send_nibble_wrapper(digit);
            first_digit = false;
        }
    }
}

void register_unicode(uint32_t code_point) {
    if (code_point > 0x10FFFF || (code_point > 0xFFFF && unicode_config.input_mode == UNICODE_MODE_WINDOWS)) {
        // Code point out of range, do nothing
        return;
    }

    unicode_input_start();
    if (code_point > 0xFFFF && unicode_config.input_mode == UNICODE_MODE_MACOS) {
        // Convert code point to UTF-16 surrogate pair on macOS
        code_point -= 0x10000;
        uint32_t lo = code_point & 0x3FF, hi = (code_point & 0xFFC00) >> 10;
        register_hex32(hi + 0xD800);
        register_hex32(lo + 0xDC00);
    } else {
        register_hex32(code_point);
    }
    unicode_input_finish();
}

void send_unicode_string(const char *str) {
    if (!str) {
        return;
    }

    while (*str) {
        int32_t code_point = 0;
        str                = decode_utf8(str, &code_point);

        if (code_point >= 0) {
            register_unicode(code_point);
        }
    }
}
