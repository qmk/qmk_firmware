// Copyright 2022-2023 Alin M Elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_ortho_5x4(
        KC_PSLS, KC_PAST, KC_MINS,   KC_EQL,
           KC_7,    KC_8,    KC_9,  KC_BSPC,
           KC_4,    KC_5,    KC_6,  KC_PPLS,
           KC_1,    KC_2,    KC_3,  KC_PENT,
       TT(_LWR),    KC_0,  KC_DOT,  TT(_RSE)
    ),
    [_LWR] = LAYOUT_ortho_5x4(
         KC_ESC, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, _______,  KC_DEL, _______
    ),
    [_RSE] = LAYOUT_ortho_5x4(
        _______, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, _______,  KC_DEL, _______
    ),
    [_ADJ] = LAYOUT_ortho_5x4(
        _______, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, QK_BOOT,  KC_DEL, _______
    )
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QW]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LWR] = {ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
    [_RSE] = {ENCODER_CCW_CW(KC_MFFD, KC_MRWD)},
    [_ADJ] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LWR, _RSE, _ADJ);
}
