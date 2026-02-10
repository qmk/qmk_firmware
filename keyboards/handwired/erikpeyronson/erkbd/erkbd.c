// Copyright 2025 Erik Peyronson @erikpeyronson
// SPDX-License-Identifier: GPL-3.0-or-later
#include QMK_KEYBOARD_H

static void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    // clang-format on

    oled_write_P(qmk_logo, false);
}

static void render_layer(void) {
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln(get_u8_str(get_highest_layer(layer_state), ' '), false);
}

static void render_locks(void) {
    led_t led_config = host_keyboard_led_state();
    oled_write_P(PSTR("Caps "), led_config.caps_lock);
    oled_write_P(PSTR("Scrl "), led_config.scroll_lock);
    oled_write_P(PSTR("Num "), led_config.num_lock);
#ifdef CAPS_WORD_ENABLE
    oled_write_P(PSTR("Word "), is_caps_word_on());
#endif
    oled_advance_page(true);
}

static void render_mods(void) {
    uint8_t mod_state = get_mods();
    oled_write_P("Ctrl ", mod_state & MOD_MASK_CTRL);
    oled_write_P("Shift ", mod_state & MOD_MASK_SHIFT);
    oled_write_P("Alt ", mod_state & MOD_MASK_ALT);
    oled_write_P("Gui", mod_state & MOD_MASK_GUI);
    oled_advance_page(true);
}

static void render_delimeter(void) {
    oled_write_ln_P(PSTR("------------------"), false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_left()) {
        oled_render_logo();
    } else {
        render_delimeter();
        render_locks();
        render_delimeter();
        render_mods();
        render_delimeter();
        render_layer();
        render_delimeter();
    }

    return false;
}
