// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"

extern uint8_t logged_row;
extern uint8_t logged_col;
extern uint32_t oled_timer;
static char logged_char = ' ';
static uint16_t logged_keycode = 0;

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void handle_oled_keypress(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
    if (keycode < 60) {
        logged_char = code_to_name[keycode];
    }

    logged_keycode = keycode;
}

void oled_render_keylog(void) {
    oled_write(get_u8_str(logged_row, '0'), false);
    oled_write_P(PSTR(":"), false);
    oled_write(get_u8_str(logged_col, '0'), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u16_str(logged_keycode, ' '), false);
    oled_write_P(PSTR(" : "), false);
    oled_write((const char *)&logged_char, false);
}

void render_master_oled(void) {
    if (timer_elapsed32(oled_timer) > CUSTOM_OLED_TIMEOUT) {
        oled_off();
        return;
    }

    oled_on();
    oled_render_layer_state();
    oled_render_keylog();
}
