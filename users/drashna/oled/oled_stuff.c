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
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "lib/lib8tion/lib8tion.h"
#ifdef UNICODE_COMMON_ENABLE
#    include "process_unicode_common.h"
#    include "keyrecords/unicode.h"
#endif
#ifdef AUDIO_CLICKY
#    include "process_clicky.h"
#endif

#ifndef OLED_BRIGHTNESS_STEP
#    define OLED_BRIGHTNESS_STEP 32
#endif

bool is_oled_enabled = true, is_oled_locked = false, is_oled_force_off = false;

uint32_t oled_timer                                 = 0;
char     oled_keylog_str[OLED_KEYLOGGER_LENGTH + 1] = {0};

deferred_token kittoken;

extern uint8_t         oled_buffer[OLED_MATRIX_SIZE];
extern OLED_BLOCK_TYPE oled_dirty;

void oled_pan_section(bool left, uint16_t y_start, uint16_t y_end, uint16_t x_start, uint16_t x_end) {
    uint16_t i = 0;
    for (uint16_t y = y_start; y < y_end; y++) {
        if (left) {
            for (uint16_t x = x_start; x < x_end - 1; x++) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i + 1];
                oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
            }
        } else {
            for (uint16_t x = x_end - 1; x > 0; x--) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i - 1];
                oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
            }
        }
    }
}

/**
 * @brief parses pressed keycodes and saves to buffer
 *
 * @param keycode Keycode pressed from switch matrix
 * @param record keyrecord_t data structure
 */
void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = keycode_config(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
        } else {
            keycode = keycode_config(0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10));
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
    } else if (IS_QK_MODS(keycode)) {
        keycode = keycode_config(QK_MODS_GET_BASIC_KEYCODE(keycode));
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = keycode_config(0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10));
    } else if (IS_QK_BASIC(keycode)) {
        keycode = keycode_config(keycode);
    }

    if ((keycode == KC_BSPC) && mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        memset(oled_keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
        oled_keylog_str[OLED_KEYLOGGER_LENGTH] = 0x00;
        return;
    }

    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    memmove(oled_keylog_str, oled_keylog_str + 1, OLED_KEYLOGGER_LENGTH - 1);
    oled_keylog_str[(OLED_KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
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
        add_keylog(keycode, record);
        if (keycode == OLED_BRIGHTNESS_INC) {
            userspace_config.oled_brightness = qadd8(userspace_config.oled_brightness, OLED_BRIGHTNESS_STEP);
            oled_set_brightness(userspace_config.oled_brightness);
            eeconfig_update_user_config(&userspace_config.raw);
        } else if (keycode == OLED_BRIGHTNESS_DEC) {
            userspace_config.oled_brightness = qsub8(userspace_config.oled_brightness, OLED_BRIGHTNESS_STEP);
            oled_set_brightness(userspace_config.oled_brightness);
            eeconfig_update_user_config(&userspace_config.raw);
        } else if (keycode == OLED_LOCK) {
            is_oled_locked = !is_oled_locked;
            if (is_oled_locked) {
                oled_on();
            }
        }
    }
    return true;
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
    oled_write(oled_keylog_str, false);
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
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);

    static char          layer_state_buffer[11] = {0};
    static layer_state_t old_state              = 0;

    if (old_state != default_layer_state) {
        snprintf(layer_state_buffer, sizeof(layer_state_buffer), "%-10s", get_layer_name_string(default_layer_state, false));
        old_state = default_layer_state;
    }
    oled_write(layer_state_buffer, false);
    oled_advance_page(true);
#else
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
#endif
}

/**
 * @brief Renders the active layers to the OLED
 *
 */
void render_layer_state(uint8_t col, uint8_t line) {
#ifdef OLED_DISPLAY_VERBOSE
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
    bool is_caps = host_keyboard_led_state().caps_lock;
#ifdef CAPS_WORD_ENABLE
    is_caps |= is_caps_word_on();
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_LSFT)) || is_caps);
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_LGUI)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_LALT)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_LCTL)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_RCTL)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_RALT)));
    oled_write_P(mod_status[!keymap_config.swap_lctl_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_RGUI)));
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_RSFT)) || is_caps);
#else
    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT) || is_caps);
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
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[1][1], is_bootmagic_on);
    oled_write_P(logo[0][1], !is_bootmagic_on);
#endif
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
#if defined(AUTOCORRECT_ENABLE)
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
#elif defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
    static const char PROGMEM mouse_lock[3] = {0xF2, 0xF3, 0};
    oled_write_P(mouse_lock, get_auto_mouse_toggle());
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
    oled_write_P(cat_mode[0], get_keyboard_lock());
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
    if (is_rgblight_startup_running()) {
        oled_write_P(PSTR("Start Animation"), false);
    } else {
        oled_write(get_u8_str(rgblight_get_hue(), ' '), false);
        oled_write_P(PSTR(", "), false);
        oled_write(get_u8_str(rgblight_get_sat(), ' '), false);
        oled_write_P(PSTR(", "), false);
        oled_write(get_u8_str(rgblight_get_val(), ' '), false);
    }
#endif
}

void render_rgb_mode(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
    __attribute__((unused)) static uint8_t mode;
    bool                                   need_update = false;
    static char                            buf[21]     = {0};

#ifdef RGB_MATRIX_ENABLE
    if (mode != rgb_matrix_get_mode()) {
        snprintf(buf, sizeof(buf), "%-20s", rgb_matrix_name(rgb_matrix_get_mode()));
        mode        = rgb_matrix_get_mode();
        need_update = true;
    }
#elif RGBLIGHT_ENABLE
    if (mode != rgblight_get_mode()) {
        snprintf(buf, sizeof(buf), "%-20s", rgblight_name(rgblight_get_mode()));
        mode        = rgblight_get_mode();
        need_update = true;
    }
#endif
    if (need_update) {
        for (uint8_t i = 1; i < sizeof(buf); ++i) {
            if (buf[i] == 0)
                break;
            else if (buf[i] == '_')
                buf[i] = ' ';
            else if (buf[i - 1] == ' ')
                buf[i] = toupper(buf[i]);
            else if (buf[i - 1] != ' ')
                buf[i] = tolower(buf[i]);
        }
    }

    oled_write(buf, false);
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
// #define OLED_LTOGI_FRAMES 2

// #define ANIM_FRAME_DURATION 500 // how long each frame lasts in ms
//  #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#if (OLED_SLEEP_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_WAKE_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_KAKI_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_RTOGI_FRAMES > OLED_ANIM_MAX_FRAMES)
#    error frame size too large
#endif

static uint8_t animation_frame = 0;
static uint8_t animation_type  = 0;

void render_kitty(uint8_t col, uint8_t line) {
    for (uint8_t i = 0; i < 4; i++) {
        oled_set_cursor(col, line + i);
        oled_write_raw_P(animation[animation_type][animation_frame][i], OLED_ANIM_SIZE);
    }
}

void render_unicode_mode(uint8_t col, uint8_t line) {
#if defined(CUSTOM_UNICODE_ENABLE) && defined(UNICODE_COMMON_ENABLE)
    oled_set_cursor(col, line);
    oled_write_P(PSTR("Unicode:"), false);
    oled_write_P(unicode_mode_str[unicode_typing_mode], false);
#endif
}

uint32_t kitty_animation_phases(uint32_t triger_time, void *cb_arg) {
    static uint32_t anim_frame_duration = 500;
#if defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
    if (get_auto_mouse_toggle()) {
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
#if defined(OLED_DISPLAY_VERBOSE)
    render_default_layer_state(1, 1);
#else
    render_default_layer_state(0, 0);
#endif

    /* Show Keyboard Layout  */
    render_layer_state(1, 2);
    render_mod_status(get_mods() | get_oneshot_mods(), 1, 5);
#if !defined(OLED_DISPLAY_VERBOSE) && defined(WPM_ENABLE) && !defined(STM32F303xC)
    render_wpm(2, 7, 1);
#endif
    render_keylock_status(host_keyboard_led_state(), 1, 6);
}

void render_status_left(void) {
#if defined(OLED_DISPLAY_VERBOSE)
    render_kitty(0, 1);

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
    if (side) {
        render_rgb_hsv(1, 7);
        render_rgb_mode(1, 8);

        render_wpm_graph(48, 72);
    } else {
        oled_advance_page(true);
        oled_advance_page(true);

        oled_set_cursor(0, 9);
        oled_write_raw_P(qmk_logo, 384); // is 3 rows of 128 pixels, so 384 bytes.

        render_unicode_mode(1, 14);
    }
}

__attribute__((weak)) void render_oled_title(bool side) {
    oled_write_P(side ? PSTR("     Left    ") : PSTR("    Right    "), true);
    // oled_write_P(PSTR(    "1234567890123"         "1234567890123"), true);
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return rotation;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        memset(oled_keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
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
#ifndef OLED_DISPLAY_TEST
    if (!is_oled_enabled) {
        oled_off();
        return false;
    } else
#endif
    {
        oled_on();
    }

    if (!oled_task_keymap()) {
        return false;
    }

#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_raw_P(header_image, sizeof(header_image));
    oled_set_cursor(4, 0);
    render_oled_title(is_keyboard_left());
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

    oled_set_cursor(0, num_of_rows);
    oled_write_raw_P(footer_image, sizeof(footer_image));
#endif

    return false;
}

void housekeeping_task_oled(void) {
    is_oled_enabled = false;
    if ((is_oled_locked || (last_input_activity_elapsed() < 60000)) && !is_oled_force_off) {
        is_oled_enabled = true;
    }
    if (oled_get_brightness() != userspace_config.oled_brightness) {
        oled_set_brightness(userspace_config.oled_brightness);
    }
}
