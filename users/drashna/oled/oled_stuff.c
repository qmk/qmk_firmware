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

#include "drashna.h"
#ifdef CUSTOM_UNICODE_ENABLE
#    include "process_unicode_common.h"
#endif
#include <string.h>

extern bool host_driver_disabled;

#ifndef KEYLOGGER_LENGTH
// #    ifdef OLED_DISPLAY_128X64
#    define KEYLOGGER_LENGTH ((uint8_t)(OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH))
// #    else
// #        define KEYLOGGER_LENGTH (uint8_t *(OLED_DISPLAY_WIDTH / OLED_FONT_HEIGHT))
// #    endif
#endif

uint32_t        oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {0};
static uint16_t log_timer                        = 0;

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

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        if (((keycode & 0xFF) == KC_BSPC) && mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
            memset(keylog_str, ' ', sizeof(keylog_str) - 1);
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

    for (uint8_t i = 1; i < KEYLOGGER_LENGTH; i++) {
        keylog_str[i - 1] = keylog_str[i];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[(KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode, record);
#endif
    }
    return true;
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        // add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR(OLED_RENDER_KEYLOGGER), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
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
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_layer_state(void) {
    oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYER_LOWER), layer_state_is(_LOWER));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYER_RAISE), layer_state_is(_RAISE));
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GamePad"), layer_state_is(_GAMEPAD));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Diablo"), layer_state_is(_DIABLO));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Mouse"), layer_state_is(_MOUSE));
#endif
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
#if !defined(OLED_DISPLAY_128X64)
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state & (1 << USB_LED_CAPS_LOCK));
#if defined(OLED_DISPLAY_128X64)
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
#endif
}

void render_matrix_scan_rate(void) {
#ifdef DEBUG_MATRIX_SCAN_RATE
    oled_write_P(PSTR("MS:"), false);
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
#endif
}

void render_mod_status(uint8_t modifiers) {
    static const char PROGMEM mod_status[5][3] = {{0xE8, 0xE9, 0}, {0xE4, 0xE5, 0}, {0xE6, 0xE7, 0}, {0xEA, 0xEB, 0}, {0xEC, 0xED, 0}};
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
#if defined(OLED_DISPLAY_128X64)
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

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    bool is_bootmagic_on;
#ifdef OLED_DISPLAY_128X64
    is_bootmagic_on = !keymap_config.swap_lctl_lgui;
#else
    is_bootmagic_on = keymap_config.swap_lctl_lgui;
#endif

    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NAME), false);
#ifdef OLED_DISPLAY_128X64
    if (keymap_config.swap_lctl_lgui)
#else
    oled_write_P(PSTR(" "), false);
#endif
    {
        oled_write_P(logo[1][0], is_bootmagic_on);
#ifdef OLED_DISPLAY_128X64
    } else {
#endif
        oled_write_P(logo[0][0], !is_bootmagic_on);
    }
#ifndef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[1][1], is_bootmagic_on);
    oled_write_P(logo[0][1], !is_bootmagic_on);
#endif
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
#ifdef AUTOCORRECTION_ENABLE
    oled_write_P(PSTR("CRCT"), userspace_config.autocorrection);
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), keymap_config.no_gui);
#endif
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
    oled_write_P(PSTR("Magic"), false);
    oled_write_P(PSTR(" "), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(logo[1][1], is_bootmagic_on);
    } else {
        oled_write_P(logo[0][1], !is_bootmagic_on);
    }
#endif
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_ONESHOT), !is_oneshot_enabled());
#ifdef SWAP_HANDS_ENABLE
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_SWAP), swap_hands);
#endif
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

#if defined(POINTING_DEVICE_ENABLE)
extern bool tap_toggling;
#endif

void render_user_status(void) {
#ifdef AUDIO_ENABLE
    bool is_audio_on = false, is_clicky_on = false;
#    ifdef SPLIT_KEYBOARD

    is_audio_on  = user_state.audio_enable;
    is_clicky_on = user_state.audio_clicky_enable;
#    else
    is_audio_on  = is_audio_on();
    is_clicky_on = is_clicky_on();
#    endif
#endif
    oled_write_P(PSTR(OLED_RENDER_USER_NAME), false);
#if !defined(OLED_DISPLAY_128X64)
    oled_write_P(PSTR(" "), false);
#endif
#if defined(RGB_MATRIX_ENABLE)
    oled_write_P(PSTR(OLED_RENDER_USER_ANIM), userspace_config.rgb_matrix_idle_anim);
#    if !defined(OLED_DISPLAY_128X64)
    oled_write_P(PSTR(" "), false);
#    endif
#elif defined(POINTING_DEVICE_ENABLE)
    static const char PROGMEM mouse_lock[3] = {0xF2, 0xF3, 0};
    oled_write_P(mouse_lock, tap_toggling);
#endif
#ifdef AUDIO_ENABLE
    static const char PROGMEM audio_status[2][3] = {{0xE0, 0xE1, 0}, {0xE2, 0xE3, 0}};
    oled_write_P(audio_status[is_audio_on], false);

#    ifdef AUDIO_CLICKY
    static const char PROGMEM audio_clicky_status[2][3] = {{0xF4, 0xF5, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(audio_clicky_status[is_clicky_on && is_audio_on], false);
#        if !defined(OLED_DISPLAY_128X64)
    oled_write_P(PSTR(" "), false);
#        endif
#    endif
#endif

    static const char PROGMEM rgb_layer_status[2][3] = {{0xEE, 0xEF, 0}, {0xF0, 0xF1, 0}};
    oled_write_P(rgb_layer_status[userspace_config.rgb_layer_change], false);
    static const char PROGMEM cat_mode[2][3] = {{0xF8, 0xF9, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(cat_mode[0], host_driver_disabled);
#if defined(CUSTOM_UNICODE_ENABLE)
    static const char PROGMEM uc_mod_status[5][3] = {{0xEA, 0xEB, 0}, {0xEC, 0xED, 0}};
    oled_write_P(uc_mod_status[get_unicode_input_mode() == UC_MAC], false);
#endif
    if (userspace_config.nuke_switch) {
#if !defined(OLED_DISPLAY_128X64)
        oled_write_P(PSTR(" "), false);
#endif
        static const char PROGMEM nukem_good[2] = {0xFA, 0};
        oled_write_P(nukem_good, false);
#if !defined(OLED_DISPLAY_128X64)
        oled_advance_page(true);
#endif
    }
#if defined(OLED_DISPLAY_128X64)
    oled_advance_page(true);
#endif
}

void oled_driver_render_logo(void) {
    // clang-format off
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on
    oled_write_P(qmk_logo, false);
}

void render_wpm(uint8_t padding) {
#ifdef WPM_ENABLE

    oled_write_P(PSTR(OLED_RENDER_WPM_COUNTER), false);
    if (padding) {
        for (uint8_t n = padding; n > 0; n--) {
            oled_write_P(PSTR(" "), false);
        }
    }
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

#if defined(KEYBOARD_handwired_tractyl_manuform) || defined(KEYBOARD_bastardkb_charybdis)
extern kb_config_data_t kb_config;
void                    render_pointing_dpi_status(uint8_t padding) {
    oled_write_P(PSTR("CPI:"), false);
    if (padding) {
        for (uint8_t n = padding - 1; n > 0; n--) {
            oled_write_P(PSTR(" "), false);
        }
    }

    oled_write(get_u16_str(kb_config.device_cpi, ' '), false);
}
#endif

__attribute__((weak)) void oled_driver_render_logo_right(void) {
#if defined(OLED_DISPLAY_128X64)
    oled_driver_render_logo();
    render_default_layer_state();
    oled_set_cursor(0, 4);
#else
    render_default_layer_state();
#endif
}

__attribute__((weak)) void oled_driver_render_logo_left(void) {
#if defined(OLED_DISPLAY_128X64)
    oled_driver_render_logo();
#    ifdef DEBUG_MATRIX_SCAN_RATE
    render_matrix_scan_rate();
#    elif defined(WPM_ENABLE)
    render_wpm(0);
#    endif
    oled_write_P(PSTR("  "), false);
#    if defined(KEYBOARD_handwired_tractyl_manuform) || defined(KEYBOARD_bastardkb_charybdis)
    render_pointing_dpi_status(1);
#    endif
    oled_set_cursor(0, 4);
#else
    render_default_layer_state();
#endif
}

void render_status_secondary(void) {
    oled_driver_render_logo_right();
    /* Show Keyboard Layout  */
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
#if !defined(OLED_DISPLAY_128X64) && defined(WPM_ENABLE) && !defined(CONVERT_TO_PROTON_C)
    render_wpm(2);
#endif
    // render_keylock_status(host_keyboard_leds());
}

void render_status_main(void) {
    oled_driver_render_logo_left();

    /* Show Keyboard Layout  */
    // render_keylock_status(host_keyboard_leds());
    render_bootmagic_status();
    render_user_status();

    // render_keylogger_status();
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    memset(keylog_str, ' ', sizeof(keylog_str) - 1);

    return oled_init_keymap(rotation);
}

bool oled_task_user(void) {
    update_log();

    if (is_keyboard_master()) {
        if (timer_elapsed32(oled_timer) > 30000) {
            oled_off();
            return false;
        } else {
            oled_on();
        }
    }
    if (is_keyboard_left()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
    if (is_keyboard_master()) {
        render_keylogger_status();
    } else {
        render_keylock_status(host_keyboard_leds());
    }
    return false;
}
