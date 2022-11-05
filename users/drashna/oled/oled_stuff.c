/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 John Ezra - wpm graph
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

#include "drashna.h"
#ifdef UNICODE_COMMON_ENABLE
#    include "process_unicode_common.h"
#    include "keyrecords/unicode.h"
#endif
#ifdef AUDIO_CLICKY
#    include "process_clicky.h"
#endif
#if defined(AUTOCORRECTION_ENABLE)
#    include "keyrecords/autocorrection/autocorrection.h"
#endif
#include <string.h>

extern bool host_driver_disabled;

uint32_t        oled_timer                        = 0;
char            keylog_str[OLED_KEYLOGGER_LENGTH] = {0};
static uint16_t log_timer                         = 0;
#ifdef OLED_DISPLAY_VERBOSE
const char PROGMEM display_border[3] = {0x0, 0xFF, 0x0};
#endif

deferred_token kittoken;

// clang-format off
static const char PROGMEM code_to_name[256] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,  // 3x
    0xDB,0xDC,0xDD,0xDE,0XDF,0xFB,'P', 'S',  19, ' ',  17,  30,  16,  16,  31,  26,  // 4x
     27,  25,  24, 'N', '/', '*', '-', '+',  23, '1', '2', '3', '4', '5', '6', '7',  // 5x
    '8', '9', '0', '.','\\', 'A',   0, '=', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ',   0, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  24,  26,  24,  // Ex
     25,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,  24,  25,  27,  26, ' ', ' ', ' '   // Fx
};
// clang-format on

/**
 * @brief parses pressed keycodes and saves to buffer
 *
 * @param keycode Keycode pressed from switch matrix
 * @param record keyrecord_t data structure
 */
void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        if (((keycode & 0xFF) == KC_BSPC) && mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
            memset(keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
            return;
        }
        if (record->tap.count) {
            keycode &= 0xFF;
        } else if (keycode > 0xFF) {
            return;
        }
    }
    if (keycode > 0xFF) {
        return;
    }

    memmove(keylog_str, keylog_str + 1, OLED_KEYLOGGER_LENGTH - 1);

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[(OLED_KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

/**
 * @brief Keycode handler for oled display.
 *
 * This adds pressed keys to buffer, but also resets the oled timer
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord data struture
 * @return true
 * @return false
 */
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer_reset();
        add_keylog(keycode, record);
    }
    return true;
}

void oled_timer_reset(void) {
    oled_timer = timer_read32();
}
/**
 * @brief Renders keylogger buffer to oled
 *
 */
void render_keylogger_status(uint8_t col, uint8_t line) {
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(col, line);
#endif
    oled_write_P(PSTR(OLED_RENDER_KEYLOGGER), false);
    oled_write(keylog_str, false);
#ifdef OLED_DISPLAY_VERBOSE
    oled_advance_page(true);
#endif
}

/**
 * @brief Renders default layer state (aka layout) to oled
 *
 */
void render_default_layer_state(uint8_t col, uint8_t line) {
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(col, line);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK_DH), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_DVORAK), false);
            break;
    }
#ifdef OLED_DISPLAY_VERBOSE
    oled_advance_page(true);
#endif
}

/**
 * @brief Renders the active layers to the OLED
 *
 */
void render_layer_state(uint8_t col, uint8_t line) {
#ifdef OLED_DISPLAY_VERBOSE
    // clang-format off
    static const char PROGMEM tri_layer_image[][3][24] = {
        // base
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0x5D, 0x3E, 0x3E, 0x7C, 0x7C, 0xF8,
                0xF8, 0x7C, 0x7C, 0x3E, 0x3E, 0x5D,
                0x5D, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // raise
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0xC0,
                0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8,
                0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x55,
                0x55, 0x23, 0x23, 0x47, 0x47, 0x8F,
                0x8F, 0x47, 0x47, 0x23, 0x23, 0x55,
                0x55, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // lower
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0xD5,
                0xD5, 0xE2, 0xE2, 0xC4, 0xC4, 0x88,
                0x88, 0xC4, 0xC4, 0xE2, 0xE2, 0xD5,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x03, 0x07, 0x07, 0x0F,
                0x0F, 0x07, 0x07, 0x03, 0x03, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // adjust
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0xC0, 0x60, 0xA0, 0x50, 0xB0, 0x58,
                0xA8, 0x50, 0xB0, 0x60, 0xA0, 0x40,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0xD5, 0x6B, 0xB6, 0x6D, 0xD6, 0xAD,
                0xDA, 0x6D, 0xD6, 0x6B, 0xB6, 0x5D,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x02, 0x05, 0x06, 0x0D,
                0x0A, 0x05, 0x06, 0x03, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // blank
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
        },
        // better gamepad
        {
            {   0,  0,  0,192,224,224,112,240,240,240,240,144,144,240,240,240,240,112,224,224,192,  0,  0,  0 },
            { 128,248,255,255,255,254,252,230,195,195,230,255,255,254,247,227,246,253,254,255,255,255,248,128 },
            {   7, 15, 15, 15,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 15, 15, 15,  7 }

        },
        // mouse
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,192, 32, 32, 32,160, 32, 32, 32,192,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,240, 15,  0,  0,  0,  3,  0,  0,  0, 15,240,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  3,  6,  4,  4,  4,  4,  4,  4,  4,  6,  3,  0,  0,  0,  0,  0,  0 }
        }
    };

    // clang-format on
    uint8_t layer_is[4] = {0, 4, 4, 4};
    if (layer_state_is(_ADJUST)) {
        layer_is[0] = 3;
    } else if (layer_state_is(_RAISE)) {
        layer_is[0] = 1;
    } else if (layer_state_is(_LOWER)) {
        layer_is[0] = 2;
    }

    if (layer_state_is(_MOUSE)) {
        layer_is[1] = 6;
    }
    if (layer_state_is(_GAMEPAD)) {
        layer_is[2] = 5;
    }

    oled_set_cursor(col, line);
    oled_write_raw_P(tri_layer_image[layer_is[0]][0], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 4, line);
    oled_write_raw_P(tri_layer_image[layer_is[1]][0], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 8, line);
    oled_write_raw_P(tri_layer_image[layer_is[2]][0], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 13, line);
    oled_write_P(PSTR("Diablo2"), layer_state_is(_DIABLOII));
    oled_advance_page(true);

    oled_set_cursor(col, line + 1);
    oled_write_raw_P(tri_layer_image[layer_is[0]][1], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 4, line + 1);
    oled_write_raw_P(tri_layer_image[layer_is[1]][1], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 8, line + 1);
    oled_write_raw_P(tri_layer_image[layer_is[2]][1], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 13, line + 1);
    oled_write_P(PSTR("Diablo3"), layer_state_is(_DIABLO));
    oled_advance_page(true);

    oled_set_cursor(col, line + 2);
    oled_write_raw_P(tri_layer_image[layer_is[0]][2], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 4, line + 2);
    oled_write_raw_P(tri_layer_image[layer_is[1]][2], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 8, line + 2);
    oled_write_raw_P(tri_layer_image[layer_is[2]][2], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(col + 13, line + 2);
    oled_write_P(PSTR("Media"), layer_state_is(_MEDIA));
#else
    oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
    oled_write_P(PSTR(OLED_RENDER_LAYER_LOWER), layer_state_is(_LOWER));
    oled_write_P(PSTR(OLED_RENDER_LAYER_RAISE), layer_state_is(_RAISE));
#endif
    oled_advance_page(true);
}

/**
 * @brief Renders the current lock status to oled
 *
 * @param led_usb_state Current keyboard led state
 */
void render_keylock_status(led_t led_usb_state, uint8_t col, uint8_t line) {
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(col, line);
#endif
#ifdef CAPS_WORD_ENABLE
    led_usb_state.caps_lock |= is_caps_word_on();
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
#if !defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state.caps_lock);
#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state.scroll_lock);
#endif
}

/**
 * @brief Renders the matrix scan rate to the host system
 *
 */
void render_matrix_scan_rate(uint8_t padding, uint8_t col, uint8_t line) {
#ifdef DEBUG_MATRIX_SCAN_RATE
    oled_set_cursor(col, line);
    oled_write_P(PSTR("MS:"), false);
    if (padding) {
        for (uint8_t n = padding; n > 0; n--) {
            oled_write_P(PSTR(" "), false);
        }
    }
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
#endif
}

/**
 * @brief Renders the modifier state
 *
 * @param modifiers Modifiers to check against (real, weak, onesheot, etc;)
 */
void render_mod_status(uint8_t modifiers, uint8_t col, uint8_t line) {
    static const char PROGMEM mod_status[5][3] = {{0xE8, 0xE9, 0}, {0xE4, 0xE5, 0}, {0xE6, 0xE7, 0}, {0xEA, 0xEB, 0}, {0xEC, 0xED, 0}};
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(col, line);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_LSHIFT)));
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_LGUI)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_LALT)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_LCTL)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_RCTL)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_RALT)));
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_RGUI)));
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_RSHIFT)));
#else
    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT));
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(" "), false);
    oled_write_P(mod_status[2], (modifiers & MOD_MASK_ALT));
    oled_write_P(mod_status[1], (modifiers & MOD_MASK_CTRL));
#endif
}

#ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#endif

void render_bootmagic_status(uint8_t col, uint8_t line) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    bool is_bootmagic_on;
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(col, line);
    //    oled_set_cursor(7, 3);
    is_bootmagic_on = !keymap_config.swap_lctl_lgui;
#else
    is_bootmagic_on = keymap_config.swap_lctl_lgui;
#endif

#ifdef OLED_DISPLAY_VERBOSE
    if (keymap_config.swap_lctl_lgui)
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NAME), false);
    oled_write_P(PSTR(" "), false);
#endif
    {
        oled_write_P(logo[1][0], is_bootmagic_on);
#ifdef OLED_DISPLAY_VERBOSE
    } else {
#endif
        oled_write_P(logo[0][0], !is_bootmagic_on);
    }
#ifndef OLED_DISPLAY_VERBOSE
    oled_write_P(logo[1][1], is_bootmagic_on);
    oled_write_P(logo[0][1], !is_bootmagic_on);
#endif
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
#if defined(AUTOCORRECTION_ENABLE) || defined(AUTOCORRECT_ENABLE)
    oled_write_P(PSTR("CRCT"), autocorrect_is_enabled());
    oled_write_P(PSTR(" "), false);
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), keymap_config.no_gui);
#endif
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(col, line + 1);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(logo[1][1], is_bootmagic_on);
    } else {
        oled_write_P(logo[0][1], !is_bootmagic_on);
    }
#endif
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_ONESHOT), is_oneshot_enabled());
#ifdef SWAP_HANDS_ENABLE
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_SWAP), swap_hands);
    oled_write_P(PSTR(" "), false);
#endif
}

#if defined(CUSTOM_POINTING_DEVICE)
extern bool tap_toggling;
#endif

void render_user_status(uint8_t col, uint8_t line) {
#ifdef AUDIO_ENABLE
    bool is_audio_on = false, l_is_clicky_on = false;
#    ifdef SPLIT_KEYBOARD

    is_audio_on = user_state.audio_enable;
#        ifdef AUDIO_CLICKY
    l_is_clicky_on = user_state.audio_clicky_enable;
#        endif
#    else
    is_audio_on    = is_audio_on();
#        ifdef AUDIO_CLICKY
    l_is_clicky_on = is_clicky_on();
#        endif
#    endif
#endif
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(col, line);
#endif
    oled_write_P(PSTR(OLED_RENDER_USER_NAME), false);
#if !defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
#endif
#if defined(RGB_MATRIX_ENABLE)
    oled_write_P(PSTR(OLED_RENDER_USER_ANIM), userspace_config.rgb_matrix_idle_anim);
#    if !defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
#    endif
#elif defined(CUSTOM_POINTING_DEVICE)
    static const char PROGMEM mouse_lock[3] = {0xF2, 0xF3, 0};
    oled_write_P(mouse_lock, tap_toggling);
#endif
#ifdef AUDIO_ENABLE
    static const char PROGMEM audio_status[2][3] = {{0xE0, 0xE1, 0}, {0xE2, 0xE3, 0}};
    oled_write_P(audio_status[is_audio_on], false);

#    ifdef AUDIO_CLICKY
    static const char PROGMEM audio_clicky_status[2][3] = {{0xF4, 0xF5, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(audio_clicky_status[l_is_clicky_on && is_audio_on], false);
#        if !defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
#        endif
#    endif
#endif

    static const char PROGMEM rgb_layer_status[2][3] = {{0xEE, 0xEF, 0}, {0xF0, 0xF1, 0}};
    oled_write_P(rgb_layer_status[userspace_config.rgb_layer_change], false);
    static const char PROGMEM cat_mode[2][3] = {{0xF8, 0xF9, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(cat_mode[0], host_driver_disabled);
#if defined(UNICODE_COMMON_ENABLE)
    static const char PROGMEM uc_mod_status[5][3] = {{0xEC, 0xED, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0xEA, 0xEB, 0}};
    oled_write_P(uc_mod_status[get_unicode_input_mode()], false);
#endif
    if (userspace_config.nuke_switch) {
#if !defined(OLED_DISPLAY_VERBOSE)
        oled_write_P(PSTR(" "), false);
#endif
        static const char PROGMEM nukem_good[2] = {0xFA, 0};
        oled_write_P(nukem_good, false);
#if !defined(OLED_DISPLAY_VERBOSE)
        oled_advance_page(true);
#endif
    }
#if defined(OLED_DISPLAY_VERBOSE)
    oled_advance_page(true);
#endif
}

void render_rgb_hsv(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
    oled_write_P(PSTR("HSV: "), false);
#ifdef RGB_MATRIX_ENABLE
    oled_write(get_u8_str(rgb_matrix_get_hue(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u8_str(rgb_matrix_get_sat(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u8_str(rgb_matrix_get_val(), ' '), false);
#elif RGBLIGHT_ENABLE
    oled_write(get_u8_str(rgblight_get_hue(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u8_str(rgblight_get_sat(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u8_str(rgblight_get_val(), ' '), false);
#endif
}

void render_wpm(uint8_t padding, uint8_t col, uint8_t line) {
#ifdef WPM_ENABLE
    oled_set_cursor(col, line);
    oled_write_P(PSTR(OLED_RENDER_WPM_COUNTER), false);
    if (padding) {
        for (uint8_t n = padding; n > 0; n--) {
            oled_write_P(PSTR(" "), false);
        }
    }
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

//=============  USER CONFIG PARAMS  ===============
// wpm graph originally designed by john-ezra

// for 128x128:
// max_lines_graph          = 54;
// vertical_offset          = 64;
// for 128x64:
// max_lines_graph          = 64;
// vertical_offset          = 0;

void render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset) {
#ifdef WPM_ENABLE
    static uint16_t timer   = 0;
    static uint8_t  x       = OLED_DISPLAY_HEIGHT - 1;
    uint8_t         currwpm = get_current_wpm();
    float           max_wpm = OLED_WPM_GRAPH_MAX_WPM;

    if (timer_elapsed(timer) > OLED_WPM_GRAPH_REFRESH_INTERVAL) {                  // check if it's been long enough before refreshing graph
        x = (max_lines_graph - 1) - ((currwpm / max_wpm) * (max_lines_graph - 1)); // main calculation to plot graph line
        for (uint8_t i = 0; i <= OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS - 1; i++) {   // first draw actual value line
            oled_write_pixel(3, x + i + vertical_offset, true);
        }
#    ifdef OLED_WPM_GRAPH_VERTICAL_LINE
        static uint8_t vert_count = 0;
        if (vert_count == OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL) {
            vert_count = 0;
            while (x <= (max_lines_graph - 1)) {
                oled_write_pixel(3, x + vertical_offset, true);
                x++;
            }
        } else {
            for (uint8_t i = (max_lines_graph - 1); i > x; i--) {
                if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                    oled_write_pixel(3, i + vertical_offset, true);
                }
            }
            vert_count++;
        }
#    else
        for (int i = (max_lines_graph - 1); i > x; i--) {
            if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                oled_write_pixel(3, i + vertical_offset, true);
            }
        }
#    endif
#    include <math.h>
        uint8_t y_start  = ceil(vertical_offset / 8);
        uint8_t y_length = y_start + ceil(max_lines_graph / 8);
        oled_pan_section(false, y_start, y_length, 3, 125); // then move the entire graph one pixel to the right
        timer = timer_read();                               // refresh the timer for the next iteration
    }
#endif
}

#if defined(POINTING_DEVICE_ENABLE)
void render_pointing_dpi_status(uint16_t cpi, uint8_t padding, uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
    oled_write_P(PSTR("CPI:"), false);
    if (padding) {
        for (uint8_t n = padding - 1; n > 0; n--) {
            oled_write_P(PSTR(" "), false);
        }
    }

    oled_write(get_u16_str(cpi, ' '), false);
}
#endif

// WPM-responsive animation stuff here
#define OLED_SLEEP_FRAMES 2
#define OLED_SLEEP_SPEED 10 // below this wpm value your animation will idle

#define OLED_WAKE_FRAMES 2               // uncomment if >1
#define OLED_WAKE_SPEED OLED_SLEEP_SPEED // below this wpm value your animation will idle

#define OLED_KAKI_FRAMES 3
#define OLED_KAKI_SPEED 40 // above this wpm value typing animation to triggere

#define OLED_RTOGI_FRAMES 2
//#define OLED_LTOGI_FRAMES 2

//#define ANIM_FRAME_DURATION 500 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define OLED_ANIM_SIZE 36
#define OLED_ANIM_ROWS 4
#define OLED_ANIM_MAX_FRAMES 3
#if (OLED_SLEEP_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_WAKE_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_KAKI_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_RTOGI_FRAMES > OLED_ANIM_MAX_FRAMES)
#    error frame size too large
#endif

static uint8_t animation_frame = 0;
static uint8_t animation_type  = 0;

void render_kitty(uint8_t col, uint8_t line) {
    // Images credit j-inc(/James Incandenza) and pixelbenny.
    // Credit to obosob for initial animation approach.
    // heavily modified by drashna because he's a glutton for punishment

    // clang-format off
    static const char PROGMEM animation[4][OLED_ANIM_MAX_FRAMES][OLED_ANIM_ROWS][OLED_ANIM_SIZE] = {
        // sleep frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xa8, 0x48, 0xa8, 0x18, 0x08, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x80, 0x44, 0x84, 0x06, 0x05, 0x04, 0x80, 0x40, 0x20, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x18, 0x04, 0x04, 0x02, 0x7a, 0x86, 0x01, 0x80, 0x80, 0x01, 0x03, 0x05, 0x07, 0x01, 0x00, 0x00, 0x80, 0x83, 0x45, 0xfa, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x29, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x3a, 0x2a, 0x26, 0x22, 0x80, 0xc0, 0x80, 0x00, 0x24, 0x34, 0x2c, 0xe4, 0x60, 0x10, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0x04, 0x02, 0x02, 0x01, 0x79, 0x87, 0x01, 0x80, 0x81, 0x83, 0x05, 0x05, 0x03, 0x01, 0x00, 0x00, 0x80, 0x43, 0x05, 0xfa, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x28, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // wake frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x40, 0x40, 0x5c, 0x00, 0x01, 0x41, 0x01, 0x00, 0x5c, 0x40, 0x40, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x90, 0x12, 0x0a, 0x02, 0xf4, 0x09, 0x0d, 0xf1, 0x04, 0x02, 0x0a, 0x12, 0x90, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x01, 0x81, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // kaki frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0xfc, 0x84, 0x08, 0x08, 0x10, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x60, 0x80, 0x00, 0x00, 0x91, 0xa1, 0x80, 0x00, 0x00, 0x22, 0x84, 0x40, 0x50, 0x48, 0xc1, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x41, 0x82, 0xe2, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x88, 0x4f, 0x02, 0x22, 0xe2, 0x9f, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1a, 0x0a, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x06, 0x1a, 0x22, 0xc2, 0x04, 0x04, 0x04, 0x07, 0x00, 0xc0, 0x20, 0x10, 0x80, 0x80, 0x01, 0x01, 0x02, 0xfc, 0xfe, 0x02, 0x3c, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x09, 0x08, 0x00, 0x80, 0x00, 0x06, 0x09, 0x1b, 0xee, 0x00, 0x00, 0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x16, 0x15, 0x14, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01, 0x02, 0x04, 0x04, 0x03, 0x80, 0x40, 0x40, 0x20, 0x00, 0x01, 0x02, 0x8c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x0a, 0x0e, 0x1d, 0x95, 0x24, 0x24, 0x27, 0x13, 0xe1, 0x01, 0x01, 0x01, 0x01, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // rtogi frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x0f, 0x90, 0x10, 0x20, 0xf0, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0xc7, 0xc4, 0x62, 0x23, 0x11, 0x3f, 0x00, 0x00, 0x00, 0x00 },
                { 0x80, 0x40, 0x20, 0x10, 0x88, 0xcc, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1f, 0xa0, 0x20, 0x40, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x28, 0x6b, 0x40, 0xa0, 0x99, 0x86, 0xff, 0x00, 0x00, 0x00, 0x00 },
                { 0x0f, 0x11, 0x22, 0x44, 0x48, 0x4c, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c, 0x04, 0x06, 0x06, 0x06, 0x0e, 0x0e, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
            }
        }
    };
    // clang-format on

    for (uint8_t i = 0; i < 4; i++) {
        oled_set_cursor(col, line + i);
        oled_write_raw_P(animation[animation_type][animation_frame][i], OLED_ANIM_SIZE);
    }
}

void render_unicode_mode(uint8_t col, uint8_t line) {
#ifdef CUSTOM_UNICODE_ENABLE
    oled_set_cursor(col, line);
    oled_write_ln_P(PSTR("Unicode:"), false);
    switch (typing_mode) {
        case UCTM_WIDE:
            oled_write_P(PSTR("        Wide"), false);
            break;
        case UCTM_SCRIPT:
            oled_write_P(PSTR("      Script"), false);
            break;
        case UCTM_BLOCKS:
            oled_write_P(PSTR("      Blocks"), false);
            break;
        case UCTM_REGIONAL:
            oled_write_P(PSTR("    Regional"), false);
            break;
        case UCTM_AUSSIE:
            oled_write_P(PSTR("      Aussie"), false);
            break;
        case UCTM_ZALGO:
            oled_write_P(PSTR("       Zalgo"), false);
            break;
        case UCTM_NO_MODE:
            oled_write_P(PSTR("      Normal"), false);
            break;
        default:
            oled_write_P(PSTR("     Unknown"), false);
            break;
    }
#endif
}

uint32_t kitty_animation_phases(uint32_t triger_time, void *cb_arg) {
    static uint32_t anim_frame_duration = 500;
#ifdef CUSTOM_POINTING_DEVICE
    if (tap_toggling) {
        animation_frame     = (animation_frame + 1) % OLED_RTOGI_FRAMES;
        animation_type      = 3;
        anim_frame_duration = 300;
    } else
#endif
    {
#ifdef WPM_ENABLE
        if (get_current_wpm() <= OLED_SLEEP_SPEED) {
#endif
            animation_frame     = (animation_frame + 1) % OLED_SLEEP_FRAMES;
            animation_type      = 0;
            anim_frame_duration = 500;
#ifdef WPM_ENABLE
        } else if (get_current_wpm() > OLED_WAKE_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_WAKE_FRAMES;
            animation_type      = 1;
            anim_frame_duration = 800;
        } else if (get_current_wpm() >= OLED_KAKI_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_KAKI_FRAMES;
            animation_type      = 2;
            anim_frame_duration = 500;
        }
#endif
    }
    return anim_frame_duration;
}

void render_mouse_mode(uint8_t col, uint8_t line) {
#if (defined(KEYBOARD_bastardkb_charybdis) || defined(KEYBOARD_handwired_tractyl_manuform)) && defined(POINTING_DEVICE_ENABLE)
    // credit and thanks to jaspertandy on discord for these images
    static const char PROGMEM mouse_logo[3][2][16] = {// mouse icon
                                                      {{0, 0, 0, 252, 2, 2, 2, 58, 2, 2, 2, 252, 0, 0, 0, 0}, {0, 0, 63, 96, 64, 64, 64, 64, 64, 64, 64, 96, 63, 0, 0, 0}},
                                                      // crosshair icon
                                                      {{128, 240, 136, 228, 146, 138, 202, 127, 202, 138, 146, 228, 136, 240, 128, 0}, {0, 7, 8, 19, 36, 40, 41, 127, 41, 40, 36, 19, 8, 7, 0, 0}},
                                                      // dragscroll icon
                                                      {{0, 0, 112, 136, 156, 2, 15, 1, 15, 2, 140, 68, 56, 0, 0, 0}, {0, 0, 2, 6, 15, 28, 60, 124, 60, 28, 15, 6, 2, 0, 0, 0}}};

    uint8_t image_index = 0;
#    ifdef OLED_DISPLAY_TEST
    image_index = animation_frame;
#    else
    if (charybdis_get_pointer_sniping_enabled()) {
        image_index = 1;
    } else if (charybdis_get_pointer_dragscroll_enabled()) {
        image_index = 2;
    }
#    endif

    oled_set_cursor(col, line);
    oled_write_raw_P(mouse_logo[image_index][0], 16);
    oled_set_cursor(col, line + 1);
    oled_write_raw_P(mouse_logo[image_index][1], 16);
#endif
}

void render_status_right(void) {
#if defined(KEYBOARD_handwired_tractyl_manuform)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Manuform"), true);
#elif defined(KEYBOARD_bastardkb_charybdis)
    oled_set_cursor(6, 0);
    oled_write_P(PSTR("Charybdis"), true);
#elif defined(KEYBOARD_splitkb_kyria)
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("Kyria"), true);
#else
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("Right"), true);
#endif
#if defined(OLED_DISPLAY_VERBOSE)
    render_default_layer_state(1, 1);
#else
    render_default_layer_state(0, 0);
#endif

    /* Show Keyboard Layout  */
    render_layer_state(1, 2);
    render_mod_status(get_mods() | get_oneshot_mods(), 1, 5);
#if !defined(OLED_DISPLAY_VERBOSE) && defined(WPM_ENABLE) && !defined(STM32F303xC)
    render_wpm(2);
#endif
    render_keylock_status(host_keyboard_led_state(), 1, 6);
}

void render_status_left(void) {
#if defined(OLED_DISPLAY_VERBOSE)
    render_kitty(0, 1);

#    if defined(KEYBOARD_handwired_tractyl_manuform)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Tractyl"), true);
#    elif defined(KEYBOARD_bastardkb_charybdis)
    oled_set_cursor(6, 0);
    oled_write_P(PSTR("Charybdis"), true);
#    elif defined(KEYBOARD_splitkb_kyria)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("SplitKB"), true);
#    elif defined(KEYBOARD_handwired_fingerpunch_rockon)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Rock On"), true);
#    else
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("Left"), true);
#    endif

#    if defined(WPM_ENABLE)
    render_wpm(1, 7, 1);
#    elif defined(DEBUG_MATRIX_SCAN_RATE)
    render_matrix_scan_rate(1, 7, 1);
#    endif
#    if (defined(KEYBOARD_bastardkb_charybdis) || defined(KEYBOARD_handwired_tractyl_manuform)) && defined(POINTING_DEVICE_ENABLE)
    render_pointing_dpi_status(charybdis_get_pointer_sniping_enabled() ? charybdis_get_pointer_sniping_dpi() : charybdis_get_pointer_default_dpi(), 1, 7, 2);
    render_mouse_mode(17, 1);
#    elif defined(WPM_ENABLE) && defined(DEBUG_MATRIX_SCAN_RATE)
    render_matrix_scan_rate(1, 7, 2);
#    endif
    /* Show Keyboard Layout  */
    render_bootmagic_status(7, 3);
    render_user_status(1, 5);

    render_keylogger_status(1, 6);
#else
    render_default_layer_state(0, 0);
    /* Show Keyboard Layout  */
    render_bootmagic_status(7, 3);
    render_user_status(1, 5);

    render_keylogger_status(1, 6);
#endif
}

__attribute__((weak)) void oled_render_large_display(bool side) {
    if (!side) {
        render_unicode_mode(1, 14);
    }
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return rotation;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        memset(keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
    }

    kittoken = defer_exec(3000, kitty_animation_phases, NULL);

    oled_clear();
    oled_render();
    return oled_init_keymap(rotation);
}

__attribute__((weak)) bool oled_task_keymap(void) {
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
#ifndef OLED_DISPLAY_TEST
        if (timer_elapsed32(oled_timer) > 60000) {
            oled_off();
            return false;
        } else
#endif
        {
            oled_on();
        }
    }

    if (!oled_task_keymap()) {
        return false;
    }

#if defined(OLED_DISPLAY_VERBOSE)
    static const char PROGMEM header_image[] = {
        0, 192, 32, 16, 8, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 7, 15, 31, 63, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 127, 63, 31, 15, 7, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 32, 192, 0,
        //         0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0
    };
    oled_write_raw_P(header_image, sizeof(header_image));
#endif

#ifndef OLED_DISPLAY_TEST
    if (is_keyboard_left()) {
#endif
        render_status_left();
#if defined(OLED_DISPLAY_128X128)
        oled_render_large_display(true);
#endif
#ifndef OLED_DISPLAY_TEST
    } else {
        render_status_right();
#    if defined(OLED_DISPLAY_128X128)
        oled_render_large_display(false);
#    endif
    }
#endif

#if defined(OLED_DISPLAY_VERBOSE)
    uint8_t num_of_rows;
#    if defined(OLED_DISPLAY_128X128)
    num_of_rows = 15;
#    else
    num_of_rows = 7;
#    endif
    for (uint8_t i = 1; i < num_of_rows; i++) {
        oled_set_cursor(0, i);
        oled_write_raw_P(display_border, sizeof(display_border));
        oled_set_cursor(21, i);
        oled_write_raw_P(display_border, sizeof(display_border));
    }

    static const char PROGMEM footer_image[] = {0, 3, 4, 8, 16, 32, 64, 128, 128, 128, 128, 128, 128, 128, 192, 224, 240, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 240, 224, 192, 128, 128, 128, 128, 128, 128, 128, 64, 32, 16, 8, 4, 3, 0};
    oled_set_cursor(0, num_of_rows);
    oled_write_raw_P(footer_image, sizeof(footer_image));
#endif

    return false;
}
