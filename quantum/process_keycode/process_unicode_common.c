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
#include "utf8.h"

unicode_config_t unicode_config;
uint8_t          unicode_saved_mods;
bool             unicode_saved_caps_lock;
bool             unicode_saved_num_lock;

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

uint8_t get_unicode_input_mode(void) {
    return unicode_config.input_mode;
}

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

void persist_unicode_input_mode(void) {
    eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config.input_mode);
}

__attribute__((weak)) void unicode_input_start(void) {
    unicode_saved_caps_lock = host_keyboard_led_state().caps_lock;
    unicode_saved_num_lock  = host_keyboard_led_state().num_lock;

    // Note the order matters here!
    // Need to do this before we mess around with the mods, or else
    // UNICODE_KEY_LNX (which is usually Ctrl-Shift-U) might not work
    // correctly in the shifted case.
    if (unicode_config.input_mode == UC_LNX && unicode_saved_caps_lock) {
        tap_code(KC_CAPS_LOCK);
    }

    unicode_saved_mods = get_mods(); // Save current mods
    clear_mods();                    // Unregister mods to start from a clean state

    switch (unicode_config.input_mode) {
        case UC_MAC:
            register_code(UNICODE_KEY_MAC);
            break;
        case UC_LNX:
            tap_code16(UNICODE_KEY_LNX);
            break;
        case UC_WIN:
            // For increased reliability, use numpad keys for inputting digits
            if (!unicode_saved_num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            register_code(KC_LEFT_ALT);
            wait_ms(UNICODE_TYPE_DELAY);
            tap_code(KC_KP_PLUS);
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
            tap_code(KC_SPACE);
            if (unicode_saved_caps_lock) {
                tap_code(KC_CAPS_LOCK);
            }
            break;
        case UC_WIN:
            unregister_code(KC_LEFT_ALT);
            if (!unicode_saved_num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            break;
        case UC_WINC:
            tap_code(KC_ENTER);
            break;
    }

    set_mods(unicode_saved_mods); // Reregister previously set mods
}

__attribute__((weak)) void unicode_input_cancel(void) {
    switch (unicode_config.input_mode) {
        case UC_MAC:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UC_LNX:
            tap_code(KC_ESCAPE);
            if (unicode_saved_caps_lock) {
                tap_code(KC_CAPS_LOCK);
            }
            break;
        case UC_WINC:
            tap_code(KC_ESCAPE);
            break;
        case UC_WIN:
            unregister_code(KC_LEFT_ALT);
            if (!unicode_saved_num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            break;
    }

    set_mods(unicode_saved_mods); // Reregister previously set mods
}

// clang-format off

static void send_nibble_wrapper(uint8_t digit) {
    if (unicode_config.input_mode == UC_WIN) {
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
    bool onzerostart = true;
    for (int i = 7; i >= 0; i--) {
        if (i <= 3) {
            onzerostart = false;
        }
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        if (digit == 0) {
            if (!onzerostart) {
                send_nibble_wrapper(digit);
            }
        } else {
            send_nibble_wrapper(digit);
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
