// Copyright 2020 Yushakobo
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef OLED_ENABLE
void render_status(void) {
    static const char os_logo[][2][3] PROGMEM = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
    if (!keymap_config.swap_lalt_lgui) {
        oled_write_P(os_logo[0][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[0][1], false);
    } else {
        oled_write_P(os_logo[1][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[1][1], false);
    }

    oled_write_P(PSTR(" Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR("\n"), false);

    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        // clang-format off
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        // clang-format on
    };
    oled_write_P(qmk_logo, false);
}

static void render_rgb_matrix_status(void) {
    oled_write_P(PSTR(" LED"), false);
    oled_write(get_u8_str(rgb_matrix_get_mode(), ' '), false);
    oled_write_char(':', false);
    oled_write(get_u8_str(rgb_matrix_get_hue() / RGB_MATRIX_HUE_STEP, ' '), false);
    oled_write_char(',', false);
    oled_write(get_u8_str(rgb_matrix_get_sat() / RGB_MATRIX_SAT_STEP, ' '), false);
    oled_write_char(',', false);
    oled_write(get_u8_str(rgb_matrix_get_val() / RGB_MATRIX_VAL_STEP, ' '), false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
        render_rgb_matrix_status();
    }
    return false;
}
#endif
