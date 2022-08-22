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

uint32_t                  oled_timer                            = 0;
char                      keylog_str[OLED_KEYLOGGER_LENGTH]     = {0};
static uint16_t           log_timer                             = 0;
static const char PROGMEM display_border[3]                     = {0x0, 0xFF, 0x0};

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
        oled_timer = timer_read32();
        add_keylog(keycode, record);
    }
    return true;
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        // add_keylog(0);
    }
}

/**
 * @brief Renders keylogger buffer to oled
 *
 */
void render_keylogger_status(void) {
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(1, 7);
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
void render_default_layer_state(void) {
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(5, 2);
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
void render_layer_state(void) {
#ifdef OLED_DISPLAY_VERBOSE
    static const char PROGMEM tri_layer_image[4][3][18] = {
        {
            {
                0x80, 0x80, 0x40, 0x40, 0x20, 0x20,
                0x10, 0x10, 0x08, 0x08, 0x10, 0x10,
                0x20, 0x20, 0x40, 0x40, 0x80, 0x80
            },
            {
                0x88, 0x88, 0x5D, 0x5D, 0x3E, 0x3E,
                0x7C, 0x7C, 0xF8, 0xF8, 0x7C, 0x7C,
                0x3E, 0x3E, 0x5D, 0x5D, 0x88, 0x88
            },
            {
                0x00, 0x00, 0x01, 0x01, 0x02, 0x02,
                0x04, 0x04, 0x08, 0x08, 0x04, 0x04,
                0x02, 0x02, 0x01, 0x01, 0x00, 0x00
            }
        },
        {
            {
                0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0,
                0xF0, 0xF0, 0xF8, 0xF8, 0xF0, 0xF0,
                0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80
            },
            {
                0x88, 0x88, 0x55, 0x55, 0x23, 0x23,
                0x47, 0x47, 0x8F, 0x8F, 0x47, 0x47,
                0x23, 0x23, 0x55, 0x55, 0x88, 0x88
            },
            {
                0x00, 0x00, 0x01, 0x01, 0x02, 0x02,
                0x04, 0x04, 0x08, 0x08, 0x04, 0x04,
                0x02, 0x02, 0x01, 0x01, 0x00, 0x00
            }
        },
        {
            {
                0x80, 0x80, 0x40, 0x40, 0x20, 0x20,
                0x10, 0x10, 0x08, 0x08, 0x10, 0x10,
                0x20, 0x20, 0x40, 0x40, 0x80, 0x80
            },
            {
                0x88, 0x88, 0xD5, 0xD5, 0xE2, 0xE2,
                0xC4, 0xC4, 0x88, 0x88, 0xC4, 0xC4,
                0xE2, 0xE2, 0xD5, 0xD5, 0x88, 0x88
            },
            {
                0x00, 0x00, 0x01, 0x01, 0x03, 0x03,
                0x07, 0x07, 0x0F, 0x0F, 0x07, 0x07,
                0x03, 0x03, 0x01, 0x01, 0x00, 0x00
            }
        },
        {
            {
                0x80, 0x80, 0x40, 0xC0, 0x60, 0xA0,
                0x50, 0xB0, 0x58, 0xA8, 0x50, 0xB0,
                0x60, 0xA0, 0x40, 0xC0, 0x80, 0x80
            },
            {
                0x88, 0x88, 0x5D, 0xD5, 0x6B, 0xB6,
                0x6D, 0xD6, 0xAD, 0xDA, 0x6D, 0xD6,
                0x6B, 0xB6, 0x5D, 0xD5, 0x88, 0x88
            },
            {
                0x00, 0x00, 0x01, 0x01, 0x03, 0x02,
                0x05, 0x06, 0x0D, 0x0A, 0x05, 0x06,
                0x03, 0x02, 0x01, 0x01, 0x00, 0x00
            }
        }
    };

    uint8_t layer_is = 0;
    if (layer_state_is(_ADJUST)) {
        layer_is = 3;
    } else if (layer_state_is(_RAISE)) {
        layer_is = 1;
    } else if (layer_state_is(_LOWER)) {
        layer_is = 2;
    }

    oled_set_cursor(1, 2);
    oled_write_raw_P(tri_layer_image[layer_is][0], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(5, 3);
    oled_write_P(PSTR("Diablo2"), layer_state_is(_DIABLOII));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Diablo3"), layer_state_is(_DIABLO));
    oled_advance_page(true);

    oled_set_cursor(1, 3);
    oled_write_raw_P(tri_layer_image[layer_is][1], sizeof(tri_layer_image[0][0]));
    oled_set_cursor(5, 4);
    oled_write_P(PSTR("GamePad"), layer_state_is(_GAMEPAD));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Mouse"), layer_state_is(_MOUSE));
    oled_advance_page(true);

    oled_set_cursor(1, 4);
    oled_write_raw_P(tri_layer_image[layer_is][2], sizeof(tri_layer_image[0][0]));

#else
    oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
    oled_write_P(PSTR(OLED_RENDER_LAYER_LOWER), layer_state_is(_LOWER));
    oled_write_P(PSTR(OLED_RENDER_LAYER_RAISE), layer_state_is(_RAISE));
    oled_advance_page(true);
#endif
}

/**
 * @brief Renders the current lock status to oled
 *
 * @param led_usb_state Current keyboard led state
 */
void render_keylock_status(uint8_t led_usb_state) {
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(1, 6);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
#if !defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state & (1 << USB_LED_CAPS_LOCK));
#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
#endif
}

/**
 * @brief Renders the matrix scan rate to the host system
 *
 */
void render_matrix_scan_rate(void) {
#ifdef DEBUG_MATRIX_SCAN_RATE
    oled_write_P(PSTR("MS:"), false);
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
#endif
}

/**
 * @brief Renders the modifier state
 *
 * @param modifiers Modifiers to check against (real, weak, onesheot, etc;)
 */
void render_mod_status(uint8_t modifiers) {
    static const char PROGMEM mod_status[5][3] = {{0xE8, 0xE9, 0}, {0xE4, 0xE5, 0}, {0xE6, 0xE7, 0}, {0xEA, 0xEB, 0}, {0xEC, 0xED, 0}};
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(1, 5);
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

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    bool is_bootmagic_on;
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(7, 4);
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
#ifdef AUTOCORRECTION_ENABLE
    oled_write_P(PSTR("CRCT"), userspace_config.autocorrection);
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), keymap_config.no_gui);
#endif
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(7, 5);
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
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(1, 6);
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
#        if !defined(OLED_DISPLAY_VERBOSE)
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
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(0, 2);
    render_default_layer_state();
#else
    render_default_layer_state();
#endif
}

// WPM-responsive animation stuff here
#define OLED_SLEEP_FRAMES 2
#define OLED_SLEEP_SPEED 10  // below this wpm value your animation will idle

#define OLED_WAKE_FRAMES 2                // uncomment if >1
#define OLED_WAKE_SPEED OLED_SLEEP_SPEED  // below this wpm value your animation will idle

#define OLED_KAKI_FRAMES 3
#define OLED_KAKI_SPEED 40  // above this wpm value typing animation to triggere

#define OLED_RTOGI_FRAMES 2
//#define OLED_LTOGI_FRAMES 2

//#define ANIM_FRAME_DURATION 500 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define OLED_ANIM_SIZE 32  // number of bytes in array, minimize for adequate firmware size, max is 1024
#define OLED_ANIM_ROWS 4
#define OLED_ANIM_MAX_FRAMES 3
#if (OLED_SLEEP_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_WAKE_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_KAKI_FRAMES > OLED_ANIM_MAX_FRAMES) || (OLED_RTOGI_FRAMES > OLED_ANIM_MAX_FRAMES)
#    error frame size too large
#endif

static uint8_t  animation_frame     = 0;
static uint8_t  animation_type      = 0;

void render_kitty(void) {
    // Images credit j-inc(/James Incandenza) and pixelbenny.
    // Credit to obosob for initial animation approach.
    // heavily modified by drashna because he's a glutton for punishment

    // clang-format off
    static const char PROGMEM animation[4][OLED_ANIM_MAX_FRAMES][OLED_ANIM_ROWS][OLED_ANIM_SIZE] = {
        // sleep frames
        {
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
                    0xa8, 0x48, 0xa8, 0x18, 0x08, 0x00, 0x00, 0x00,
                    0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03,
                    0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x80,
                    0x44, 0x84, 0x06, 0x05, 0x04, 0x80, 0x40, 0x20,
                    0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20,
                    0x18, 0x04, 0x04, 0x02, 0x7a, 0x86, 0x01, 0x80,
                    0x80, 0x01, 0x03, 0x05, 0x07, 0x01, 0x00, 0x00,
                    0x80, 0x83, 0x45, 0xfa, 0x3c, 0xe0, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08,
                    0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28,
                    0x28, 0x29, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39,
                    0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00
                }
            },
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x22, 0x22, 0x3a, 0x2a, 0x26, 0x22, 0x80, 0xc0,
                    0x80, 0x00, 0x24, 0x34, 0x2c, 0xe4, 0x60, 0x10,
                    0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38,
                    0x04, 0x02, 0x02, 0x01, 0x79, 0x87, 0x01, 0x80,
                    0x81, 0x83, 0x05, 0x05, 0x03, 0x01, 0x00, 0x00,
                    0x80, 0x43, 0x05, 0xfa, 0x3c, 0xe0, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08,
                    0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28,
                    0x28, 0x28, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39,
                    0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00
                }
            }
        },
        // wake frames
        {
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80,
                    0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x7f, 0x80, 0x40, 0x40, 0x5c, 0x00, 0x01,
                    0x41, 0x01, 0x00, 0x5c, 0x40, 0x40, 0x80, 0x7f,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x00,
                    0x80, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
                }
            },
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80,
                    0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x7f, 0x90, 0x12, 0x0a, 0x02, 0xf4, 0x09,
                    0x0d, 0xf1, 0x04, 0x02, 0x0a, 0x12, 0x90, 0x7f,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x01,
                    0x81, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08
                }
            }
        },
        // kaki frames
        {
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40,
                    0x80, 0x80, 0x80, 0x00, 0xfc, 0x84, 0x08, 0x08,
                    0x10, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x60,
                    0x80, 0x00, 0x00, 0x91, 0xa1, 0x80, 0x00, 0x00,
                    0x22, 0x84, 0x40, 0x50, 0x48, 0xc1, 0x3e, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x41, 0x82, 0xe2, 0x12, 0x0a, 0x06, 0x00,
                    0x80, 0x88, 0x4f, 0x02, 0x22, 0xe2, 0x9f, 0x40,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10,
                    0x14, 0x14, 0x1f, 0x1a, 0x0a, 0x0a, 0x04, 0x00
                }
            },
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x06, 0x1a, 0x22, 0xc2, 0x04, 0x04,
                    0x04, 0x07, 0x00, 0xc0, 0x20, 0x10, 0x80, 0x80,
                    0x01, 0x01, 0x02, 0xfc, 0xfe, 0x02, 0x3c, 0x20,
                    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d,
                    0x55, 0x50, 0x94, 0xf0, 0x10, 0x09, 0x08, 0x00,
                    0x80, 0x00, 0x06, 0x09, 0x1b, 0xee, 0x00, 0x00,
                    0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c,
                    0x14, 0x16, 0x15, 0x14, 0x14, 0x14, 0x14, 0x08
                }
            },
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x20, 0x40,
                    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01,
                    0x02, 0x04, 0x04, 0x03, 0x80, 0x40, 0x40, 0x20,
                    0x00, 0x01, 0x02, 0x8c, 0x70, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d,
                    0x55, 0x50, 0x94, 0xf0, 0x10, 0x0a, 0x0e, 0x1d,
                    0x95, 0x24, 0x24, 0x27, 0x13, 0xe1, 0x01, 0x01,
                    0x01, 0x01, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14,
                    0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18,
                    0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c,
                    0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x08
                }
            }
        },
        // rtogi frames
        {
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02,
                    0x01, 0x0f, 0x90, 0x10, 0x20, 0xf0, 0xf8, 0xf8
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08,
                    0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x08, 0x88, 0xc7, 0xc4, 0x62, 0x23, 0x11, 0x3f
                },
                {
                    0x80, 0x40, 0x20, 0x10, 0x88, 0xcc, 0x43, 0x80,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0,
                    0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c,
                    0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                },
                {
                    0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
                    0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04,
                    0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                }
            },
            {
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02,
                    0x01, 0x1f, 0xa0, 0x20, 0x40, 0x80, 0x00, 0xf0
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                    0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08,
                    0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x24,
                    0x24, 0x28, 0x6b, 0x40, 0xa0, 0x99, 0x86, 0xff
                },
                {
                    0x0f, 0x11, 0x22, 0x44, 0x48, 0x4c, 0x43, 0x80,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0,
                    0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c,
                    0x04, 0x06, 0x06, 0x06, 0x0e, 0x0e, 0x06, 0x01
                },
                {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04,
                    0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                }
            }
        }
    };
    // clang-format on

    for (uint8_t i = 0; i < 4; i++) {
        oled_set_cursor(1, i + 2);
        oled_write_raw_P(animation[animation_type][animation_frame][i], OLED_ANIM_SIZE);
    }
}

uint32_t kitty_animation_phases(uint32_t triger_time, void *cb_arg) {
    uint32_t anim_frame_duration = 500;
    // can't change animation frame duration here, otherwise, it gets stuck.
    // weirdly, it seems to work fine if it's in keymap.c but not here.
    // Should move this block to the deferred execution?
#ifdef POINTING_DEVICE_ENABLE
    if (tap_toggling) {
        animation_frame = (animation_frame + 1) % OLED_RTOGI_FRAMES;
        animation_type = 3;
        anim_frame_duration = 300;
    } else
#endif
    {
        if (get_current_wpm() <= OLED_SLEEP_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_SLEEP_FRAMES;
            animation_type      = 0;
            anim_frame_duration = 500;
        } else if (get_current_wpm() > OLED_WAKE_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_WAKE_FRAMES;
            animation_type      = 1;
            anim_frame_duration = 800;
        } else if (get_current_wpm() >= OLED_KAKI_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_KAKI_FRAMES;
            animation_type      = 2;
            anim_frame_duration = 500;
        }
    }
    return anim_frame_duration;
}

void oled_driver_render_logo_left(void) {
#if defined(OLED_DISPLAY_VERBOSE)
    oled_set_cursor(0, 2);
    render_kitty();

#    if defined(KEYBOARD_handwired_tractyl_manuform)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Tractyl"), true);
#    elif defined(KEYBOARD_bastardkb_charybdis)
    oled_set_cursor(6, 0);
    oled_write_P(PSTR("Charybdis"), true);
#    else
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("Left"), true);
#    endif
    oled_set_cursor(7, 2);
#    if defined(DEBUG_MATRIX_SCAN_RATE)
    render_matrix_scan_rate();
#    elif defined(WPM_ENABLE)
    render_wpm(1);
#    endif
    oled_set_cursor(7, 3);
#    if defined(KEYBOARD_handwired_tractyl_manuform)
    render_pointing_dpi_status(0);
#    elif defined(KEYBOARD_bastardkb_charybdis)
    render_pointing_dpi_status(1);
#    endif
    oled_set_cursor(0, 6);
#else
    render_default_layer_state();
#endif
}

void render_status_secondary(void) {
#    if defined(KEYBOARD_handwired_tractyl_manuform)
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Manuform"), true);
#    elif defined(KEYBOARD_bastardkb_charybdis)
    oled_set_cursor(6, 0);
    oled_write_P(PSTR("Charybdis"), true);
#    else
    oled_set_cursor(8, 0);
    oled_write_P(PSTR("Right"), true);
#    endif
    oled_driver_render_logo_right();
    /* Show Keyboard Layout  */
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
#if !defined(OLED_DISPLAY_VERBOSE) && defined(WPM_ENABLE) && !defined(CONVERT_TO_PROTON_C)
    render_wpm(2);
#endif
    render_keylock_status(host_keyboard_leds());
}

void render_status_main(void) {
    oled_driver_render_logo_left();

    /* Show Keyboard Layout  */
    render_bootmagic_status();
    render_user_status();

    // render_keylogger_status();
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        memset(keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
    }

    kittoken = defer_exec(3000, kitty_animation_phases, NULL);

    oled_clear();
    oled_render();
    return oled_init_keymap(rotation);
}

bool oled_task_user(void) {
    update_log();

    if (is_keyboard_master()) {
#ifndef OLED_DISPLAY_TEST
        if (timer_elapsed32(oled_timer) > 30000) {
            oled_off();
            return false;
        } else
#endif
        {
            oled_on();
        }
    }
#if defined(OLED_DISPLAY_VERBOSE)
     static const char PROGMEM header_image[] = {
         0,192, 32, 16,  8,  4,  2,  1,  1,  1,  1,  1,  1,  1,  1,  3,  7, 15, 31, 63,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127, 63, 31, 15,  7,  3,  1,  1,  1,  1,  1,  1,  1,  1,  2,  4,  8, 16, 32,192,  0,
         0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0
     };
     static const char PROGMEM footer_image[] = {
         0,  3,  4,  8, 16, 32, 64,128,128,128,128,128,128,128,192,224,240,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,240,224,192,128,128,128,128,128,128,128, 64, 32, 16,  8,  4,  3,  0
     };
    oled_write_raw_P(header_image, sizeof(header_image));
    oled_set_cursor(0, 1);
#endif

#ifndef OLED_DISPLAY_TEST
    if (is_keyboard_left()) {
#endif
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
#ifndef OLED_DISPLAY_TEST
    } else {
        render_status_secondary();
    }
#endif

#if defined(OLED_DISPLAY_128X128)
    if (is_keyboard_left()) {
        render_keylogger_status();
    }
#endif

#if defined(OLED_DISPLAY_VERBOSE)
    uint8_t num_of_rows;
#    if defined(OLED_DISPLAY_128X128)
    num_of_rows = 15;
#    else
    num_of_rows = 7;
#    endif
    for (uint8_t i= 1; i < num_of_rows; i++) {
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
