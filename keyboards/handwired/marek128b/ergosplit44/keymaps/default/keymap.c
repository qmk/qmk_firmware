// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _COLEMAK,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT(
            KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                   KC_Z,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
            KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                   KC_H,       KC_J,       KC_K,       KC_L,       KC_NO,      KC_ENT, 
            KC_LSFT,    KC_Y,       KC_X,       KC_C,       KC_V,       KC_B,                   KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_MINS,    KC_RSFT, 
                                    TG(_COLEMAK),KC_LCTL,    KC_SPC,     KC_LSFT,                KC_RSFT,    KC_SPC,     KC_NO,      KC_RALT
        ),
        [_COLEMAK] = LAYOUT(
            KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,                   KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_BSPC, 
            KC_CAPS,    KC_A,       KC_R,       KC_R,       KC_T,       KC_D,                   KC_H,       KC_N,       KC_E,       KC_I,       KC_O,       KC_ENT, 
            KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                   KC_K,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT, 
                                    KC_TRNS,    KC_LCTL,    KC_SPC,     KC_NO,                  KC_LALT,    KC_SPC,     KC_NO,      KC_RALT
        )
};

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, RGB_RED);
    }
	
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(1, RGB_RED);
    }

    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(2, RGB_RED);
    }
	
    switch (get_highest_layer(layer_state)) {
        case 1: 
            rgb_matrix_set_color(3, RGB_CYAN);
            break;
        case 2: 
            rgb_matrix_set_color(3, RGB_MAGENTA);
            break;
        case 3:
            rgb_matrix_set_color(3, RGB_YELLOW);
            break;
    } 
    return true;
}
