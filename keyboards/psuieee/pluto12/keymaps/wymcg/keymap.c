// Copyright 2021-22 Will McGLoughlin (wymcg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NAV,
    _PROD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_MUTE,    KC_MPRV,    KC_MPLY,    KC_MNXT,
    TO(_NAV),   G(KC_1),    G(KC_2),    G(KC_3),
    TO(_PROD),  G(KC_4),    G(KC_5),    G(KC_6)
  ),
  [_NAV] = LAYOUT(
    TO(_BASE),  KC_HOME,    KC_UP,      KC_END,
    A(KC_TAB),  KC_LEFT,    KC_DOWN,    KC_RIGHT,
    G(KC_TAB),  KC_PGDN,    KC_PGUP,    MO(_BASE)
  ),
  [_PROD] = LAYOUT(
    TO(_BASE),  KC_NO,      KC_NO,      KC_NO,
    C(KC_Z),    C(KC_X),    C(KC_C),    C(KC_V),
    C(KC_A),    C(KC_LEFT), C(KC_RIGHT),MO(_BASE)
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {
        case _BASE:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _NAV:
            if (clockwise) {
                tap_code16(C(G(KC_RIGHT)));
            } else {
                tap_code16(C(G(KC_LEFT)));
            }
            break;
        case _PROD:
            if (clockwise) {
                tap_code16(C(KC_Y));
            } else {
                tap_code16(C(KC_Z));
            }
            break;
    }
    return false;
}
