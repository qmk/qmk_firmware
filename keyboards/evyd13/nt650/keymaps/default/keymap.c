// Copyright 2022 Evelien Dekkers (@evyd13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability.
// The underscores don't mean anything - you can
// have a layer called STUFF or any other name.
// Layer names don't all need to be of the same
// length, and you can also skip them entirely
// and just use numbers.
enum layer_names {
    _BASE,
    _FUNC,
    _LOCK,
    _XTRA
};

#define LOCK_LED_PIN B0
#define GRV_TG TG(_LOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ansi_split_space(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FUNC),
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,                    KC_SPC,           KC_RALT, KC_RCTL,          KC_UP,
                                                                                                           KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNC] = LAYOUT_ansi_split_space(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, GRV_TG,  _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______, _______,
        _______, _______, _______,          _______,                   _______,          _______, KC_APP,           _______,
                                                                                                           _______, _______, _______
    ),
    [_LOCK] = LAYOUT_ansi_split_space(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______,                   _______,          _______, _______,          _______,
                                                                                                           _______, _______, _______
    ),
    [_XTRA] = LAYOUT_ansi_split_space(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______,                   _______,          _______, _______,          _______,
                                                                                                           _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    setPinOutput(LOCK_LED_PIN);
    switch (get_highest_layer(state)) {
        case _LOCK:
            writePin(LOCK_LED_PIN, 0);
            break;
        default: //  for any other layers, or the default layer
            writePin(LOCK_LED_PIN, 1);
            break;
    }
    return state;
}
