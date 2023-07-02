// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                          LT(1,KC_MUTE),
        KC_ENT,  KC_0,    KC_BSPC,
        KC_7,    KC_8,    KC_9,
        KC_4,    KC_5,    KC_6,
        KC_1,    KC_2,    KC_3
    ),
    [1] = LAYOUT(
                          _______,
        CK_TOGG, AU_TOGG, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

void render_oled_title(bool side) {
    oled_write_P(PSTR("   Macropad  "), true);
}

void render_rgb_mode(uint8_t col, uint8_t line);

void l_render_keylock_status(led_t led_usb_state, uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
#ifdef CAPS_WORD_ENABLE
    led_usb_state.caps_lock |= is_caps_word_on();
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state.caps_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state.scroll_lock);
}

bool oled_task_keymap(void) {
    oled_write_raw_P(header_image, sizeof(header_image));
    oled_set_cursor(0, 1);
    oled_write_raw_P(row_2_image, sizeof(row_2_image));
    oled_set_cursor(4, 0);
    render_oled_title(false);

    render_kitty(0, 2);
    render_matrix_scan_rate(1, 7, 2);

#ifdef AUDIO_ENABLE
    oled_set_cursor(7, 4);
    bool l_is_audio_on = is_audio_on();

    static const char PROGMEM audio_status[2][3] = {{0xE0, 0xE1, 0}, {0xE2, 0xE3, 0}};
    oled_write_P(audio_status[l_is_audio_on], false);

#    ifdef AUDIO_CLICKY
    bool                      l_is_clicky_on            = is_clicky_on();
    static const char PROGMEM audio_clicky_status[2][3] = {{0xF4, 0xF5, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(audio_clicky_status[l_is_clicky_on && l_is_audio_on], false);
#    endif
#endif

    static const char PROGMEM cat_mode[3] = {0xF8, 0xF9, 0};
    oled_write_P(cat_mode, get_keyboard_lock());

#ifdef RGB_MATIRX_ENABLE
    static const char PROGMEM rgb_layer_status[2][3] = {{0xEE, 0xEF, 0}, {0xF0, 0xF1, 0}};
    oled_write_P(rgb_layer_status[rgb_matrix_is_enabled()], false);
#endif

#ifdef HAPTIC_ENABLE
    static const char PROGMEM nukem_good[2] = {0xFA, 0};
    oled_write_P(haptic_get_enable() ? nukem_good : PSTR(" "), false);
#endif

    l_render_keylock_status(host_keyboard_led_state(), 7, 5);
    render_rgb_mode(1, 6);

    for (uint8_t i = 1; i < 7; i++) {
        oled_set_cursor(0, i);
        oled_write_raw_P(display_border, sizeof(display_border));
        oled_set_cursor(21, i);
        oled_write_raw_P(display_border, sizeof(display_border));
    }
    oled_set_cursor(0, 7);
    oled_write_raw_P(footer_image, sizeof(footer_image));

    return false;
}
