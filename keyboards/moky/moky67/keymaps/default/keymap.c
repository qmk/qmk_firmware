// Copyright 2023 VertorWang (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,                   _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                   KC_SCRL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                    KC_DEL,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),                     KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT( /* Base */
        KC_GRV,  KC_MYCM, KC_WHOM, KC_MAIL, KC_CALC, KC_MSEL, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______,
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT,                   _______,
        _______, TO(0),   TO(2),   _______, _______, _______, _______, _______, _______, RM_TOGG, _______, _______,          _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          RM_VALU,
        _______, GU_TOGG, _______,                                     EE_CLR,                    _______, _______,          _______, RM_SPDD, RM_VALD, RM_SPDU),

    [2] = LAYOUT(  /* Base */
        KC_ESC,  KC_BRMD, KC_BRMU, KC_F3,   _______, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSPC,                   _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                   KC_SCRL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                    KC_DEL,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RALT, MO(3),                     KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [3] = LAYOUT(  /* FN */
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______,                   _______,
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT,                   _______,
        _______, TO(0),   TO(2),   _______, _______, _______, _______, _______, _______, RM_TOGG, _______, _______,          _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          RM_VALU,
        _______, _______, _______,                                     EE_CLR,                    _______, _______,          _______, RM_SPDD, RM_VALD, RM_SPDU),
};

// clang-format on

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [1] = { ENCODER_CCW_CW(RM_PREV,  RM_NEXT)},
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};

#endif
