/* Copyright 2017 Jack Humbert
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

#include "process_unicode_common.h"
#include "eeprom.h"
#include <ctype.h>
#include <string.h>

unicode_config_t unicode_config;
uint8_t          unicode_saved_mods;
bool             unicode_saved_caps_lock;

#if UNICODE_SELECTED_MODES != -1
static uint8_t selected[]     = {UNICODE_SELECTED_MODES};
static int8_t  selected_count = sizeof selected / sizeof *selected;
static int8_t  selected_index;
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
    dprintf("Unicode input mode init to: %u\n", unicode_config.input_mode);
}

uint8_t get_unicode_input_mode(void) { return unicode_config.input_mode; }

void set_unicode_input_mode(uint8_t mode) {
    unicode_config.input_mode = mode;
    persist_unicode_input_mode();
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
    dprintf("Unicode input mode cycle to: %u\n", unicode_config.input_mode);
#endif
}

void persist_unicode_input_mode(void) { eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config.input_mode); }

__attribute__((weak)) void unicode_input_start(void) {
    unicode_saved_caps_lock = host_keyboard_led_state().caps_lock;

    // Note the order matters here!
    // Need to do this before we mess around with the mods, or else
    // UNICODE_KEY_LNX (which is usually Ctrl-Shift-U) might not work
    // correctly in the shifted case.
    if (unicode_config.input_mode == UC_LNX && unicode_saved_caps_lock) {
        tap_code(KC_CAPS);
    }

    unicode_saved_mods = get_mods();  // Save current mods
    clear_mods();                     // Unregister mods to start from a clean state

    switch (unicode_config.input_mode) {
        case UC_MAC:
            register_code(UNICODE_KEY_MAC);
            break;
        case UC_LNX:
            tap_code16(UNICODE_KEY_LNX);
            break;
        case UC_WIN:
            register_code(KC_LALT);
            tap_code(KC_PPLS);
            break;
        case UC_WINC:
            tap_code(UNICODE_KEY_WINC);
            tap_code(KC_U);
            break;
    }

    wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak)) void unicode_input_finish(void) {
    switch (unicode_config.input_mode) {
        case UC_MAC:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UC_LNX:
            tap_code(KC_SPC);
            if (unicode_saved_caps_lock) {
                tap_code(KC_CAPS);
            }
            break;
        case UC_WIN:
            unregister_code(KC_LALT);
            break;
        case UC_WINC:
            tap_code(KC_ENTER);
            break;
    }

    set_mods(unicode_saved_mods);  // Reregister previously set mods
}

__attribute__((weak)) void unicode_input_cancel(void) {
    switch (unicode_config.input_mode) {
        case UC_MAC:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UC_LNX:
            tap_code(KC_ESC);
            if (unicode_saved_caps_lock) {
                tap_code(KC_CAPS);
            }
            break;
        case UC_WINC:
            tap_code(KC_ESC);
            break;
        case UC_WIN:
            unregister_code(KC_LALT);
            break;
    }

    set_mods(unicode_saved_mods);  // Reregister previously set mods
}

void register_hex(uint16_t hex) {
    for (int i = 3; i >= 0; i--) {
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        send_nibble(digit);
    }
}

void register_hex32(uint32_t hex) {
    bool onzerostart = true;
    for (int i = 7; i >= 0; i--) {
        if (i <= 3) {
            onzerostart = false;
        }
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        if (digit == 0) {
            if (!onzerostart) {
                send_nibble(digit);
            }
        } else {
            send_nibble(digit);
            onzerostart = false;
        }
    }
}

void register_unicode(uint32_t code_point) {
    if (code_point > 0x10FFFF || (code_point > 0xFFFF && unicode_config.input_mode == UC_WIN)) {
        // Code point out of range, do nothing
        return;
    }

    unicode_input_start();
    if (code_point > 0xFFFF && unicode_config.input_mode == UC_MAC) {
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

// clang-format off

void send_unicode_hex_string(const char *str) {
    if (!str) {
        return;
    }

    while (*str) {
        // Find the next code point (token) in the string
        for (; *str == ' '; str++);    // Skip leading spaces
        size_t n = strcspn(str, " ");  // Length of the current token
        char code_point[n+1];
        strncpy(code_point, str, n);   // Copy token into buffer
        code_point[n] = '\0';          // Make sure it's null-terminated

        // Normalize the code point: make all hex digits lowercase
        for (char *p = code_point; *p; p++) {
            *p = tolower((unsigned char)*p);
        }

        // Send the code point as a Unicode input string
        unicode_input_start();
        send_string(code_point);
        unicode_input_finish();

        str += n;  // Move to the first ' ' (or '\0') after the current token
    }
}

// clang-format on

// Borrowed from https://nullprogram.com/blog/2017/10/06/
static const char *decode_utf8(const char *str, int32_t *code_point) {
    const char *next;

    if (str[0] < 0x80) {  // U+0000-007F
        *code_point = str[0];
        next        = str + 1;
    } else if ((str[0] & 0xE0) == 0xC0) {  // U+0080-07FF
        *code_point = ((int32_t)(str[0] & 0x1F) << 6) | ((int32_t)(str[1] & 0x3F) << 0);
        next        = str + 2;
    } else if ((str[0] & 0xF0) == 0xE0) {  // U+0800-FFFF
        *code_point = ((int32_t)(str[0] & 0x0F) << 12) | ((int32_t)(str[1] & 0x3F) << 6) | ((int32_t)(str[2] & 0x3F) << 0);
        next        = str + 3;
    } else if ((str[0] & 0xF8) == 0xF0 && (str[0] <= 0xF4)) {  // U+10000-10FFFF
        *code_point = ((int32_t)(str[0] & 0x07) << 18) | ((int32_t)(str[1] & 0x3F) << 12) | ((int32_t)(str[2] & 0x3F) << 6) | ((int32_t)(str[3] & 0x3F) << 0);
        next        = str + 4;
    } else {
        *code_point = -1;
        next        = str + 1;
    }

    // part of a UTF-16 surrogate pair - invalid
    if (*code_point >= 0xD800 && *code_point <= 0xDFFF) {
        *code_point = -1;
    }

    return next;
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

// clang-format off

static void audio_helper(void) {
#ifdef AUDIO_ENABLE
    switch (get_unicode_input_mode()) {
#    ifdef UNICODE_SONG_MAC
        static float song_mac[][2] = UNICODE_SONG_MAC;
        case UC_MAC:
            PLAY_SONG(song_mac);
            break;
#    endif
#    ifdef UNICODE_SONG_LNX
        static float song_lnx[][2] = UNICODE_SONG_LNX;
        case UC_LNX:
            PLAY_SONG(song_lnx);
            break;
#    endif
#    ifdef UNICODE_SONG_WIN
        static float song_win[][2] = UNICODE_SONG_WIN;
        case UC_WIN:
            PLAY_SONG(song_win);
            break;
#    endif
#    ifdef UNICODE_SONG_BSD
        static float song_bsd[][2] = UNICODE_SONG_BSD;
        case UC_BSD:
            PLAY_SONG(song_bsd);
            break;
#    endif
#    ifdef UNICODE_SONG_WINC
        static float song_winc[][2] = UNICODE_SONG_WINC;
        case UC_WINC:
            PLAY_SONG(song_winc);
            break;
#    endif
    }
#endif
}

// clang-format on

bool process_unicode_common(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        switch (keycode) {
            case UNICODE_MODE_FORWARD:
                cycle_unicode_input_mode(shifted ? -1 : +1);
                audio_helper();
                break;
            case UNICODE_MODE_REVERSE:
                cycle_unicode_input_mode(shifted ? +1 : -1);
                audio_helper();
                break;

            case UNICODE_MODE_MAC ... UNICODE_MODE_WINC: {
                // Keycodes and input modes follow the same ordering
                uint8_t delta = keycode - UNICODE_MODE_MAC;
                set_unicode_input_mode(UC_MAC + delta);
                audio_helper();
                break;
            }
        }
    }

#if defined(UNICODE_ENABLE)
    return process_unicode(keycode, record);
#elif defined(UNICODEMAP_ENABLE)
    return process_unicodemap(keycode, record);
#elif defined(UCIS_ENABLE)
    return process_ucis(keycode, record);
#else
    return true;
#endif
}
