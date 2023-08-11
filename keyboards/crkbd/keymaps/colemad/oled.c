// Copyright 2022 Álvaro Cortés (@ACortesDev)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_layer_symbol(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_layer_name(void) {
    bool lower = layer_state_is(_LOWER) & !layer_state_is(_ADJUST);
    bool raise = layer_state_is(_RAISE) & !layer_state_is(_ADJUST);
    bool adjust = layer_state_is(_ADJUST);

    if(lower){ 
        oled_write_P(PSTR("LOWER"), false);
    } else if(raise){ 
        oled_write_P(PSTR("RAISE"), false);
    } else if(adjust){ 
        oled_write_P(PSTR(" ADJ "), false);
    } else { 
        oled_write_P(PSTR("     "), false); 
    }
}

void render_mod_state(uint8_t modifiers) {
    static const char PROGMEM shift_line_1[] = {
        0x85, 0x86, 0x87, 0};
    static const char PROGMEM shift_line_2[] = {
        0xa5, 0xa6, 0xa7, 0};

    static const char PROGMEM ctrl_line_1[] = {
        0x88, 0x89, 0x8a, 0x8b, 0};
    static const char PROGMEM ctrl_line_2[] = {
        0xa8, 0xa9, 0xaa, 0xab, 0};

    static const char PROGMEM os_line_1[] = {
        0x8c, 0x8d, 0x8e, 0};
    static const char PROGMEM os_line_2[] = {
        0xac, 0xad, 0xae, 0};

    static const char PROGMEM alt_line_1[] = {
        0x8f, 0x90, 0x91, 0};
    static const char PROGMEM alt_line_2[] = {
        0xaf, 0xb0, 0xb1, 0};
    
    if (modifiers & MOD_MASK_GUI) {
        oled_write(" ", false);
        oled_write_ln_P(os_line_1, false);
        oled_write(" ", false);
        oled_write_ln_P(os_line_2, false);
    } else {
        oled_write_ln("", false);
        oled_write_ln("", false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write(" ", false);
        oled_write_ln_P(shift_line_1, false);
        oled_write(" ", false);
        oled_write_ln_P(shift_line_2, false);
    } else {
        oled_write_ln("", false);
        oled_write_ln("", false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write(" ", false);
        oled_write_ln_P(alt_line_1, false);
        oled_write(" ", false);
        oled_write_ln_P(alt_line_2, false);
    } else {
        oled_write_ln("", false);
        oled_write_ln("", false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_ln_P(ctrl_line_1, false);
        oled_write_ln_P(ctrl_line_2, false);
    } else {
        oled_write_ln("", false);
        oled_write_ln("", false);
    }
}

void render_status(void){
    render_layer_name();

    render_layer_symbol();
    
    oled_write_P(PSTR("\n\n\n"), false);
    
    render_mod_state(get_mods()|get_oneshot_mods());
}

bool oled_task_user(void) {
    render_status();
    return false;
}
