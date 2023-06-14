// Copyright 2022 Will Winder (@winder)
// SPDX-License-Identifier: GPL-2.0-or-later
//
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define FN_1 MO(_LOWER)
#define FN_2 MO(_RAISE)
#define TRMINAL LGUI(KC_ENT)
#define RESIZE  LGUI(KC_R)
#define BROWSER LSG(KC_ENT) // Left Shift + GUI, ENT.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
                 KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_UNDS,
                 KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_MUTE,                            KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
                 KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , TRMINAL, BROWSER, RESIZE , KC_UNDS, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                                     KC_LALT, KC_LGUI, FN_1   , KC_ENT , FN_2   , KC_SPC , KC_BSPC, KC_DEL
    ),
    [_LOWER] = LAYOUT(
                 _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
                 KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
                 KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
                 _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                                                     _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_BSPC,                                     KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_DEL,  _______,                            KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, XXXXXXX,
                 _______, KC_0,    KC_7,    KC_8,    KC_9,    KC_DOT,  _______, _______, _______, _______, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                                     _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return false;
}
#endif
