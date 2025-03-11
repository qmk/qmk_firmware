// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │               │ N │ M │ , │ . │ / │Sft│
      * ├───┼───┼───┼───┼───┼───┘               └───┼───┼───┼───┼───┼───┤
      * │Esc│lsu│rcl│Alt│Rai| ┌───┬───┐   ┌───┬───┐ │Low│AGr│Men│rcl│Cnf│
      * └───┴───┴───┴───┴───┘ │Spc│Del│   │Ent│Spc│ └───┴───┴───┴───┴───┘
      *                       │   │   │   │   │   │
      *                       └───┴───┘   └───┴───┘
      */
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_ESC,  KC_LGUI, KC_RCTL, KC_LALT, MO(2),                            MO(1),   KC_RALT, KC_APP,  KC_RCTL, MO(3),
                                            KC_SPC,  KC_DEL,         KC_ENT,  KC_SPC
    ),
    [1] = LAYOUT(
        _______, _______, KC_VOLU, KC_MUTE, KC_VOLD, _______,        _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,
        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,        KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,
        _______, _______, _______, KC_MSTP, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
                                            _______, _______,        _______, _______
    ),
    [2] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,  KC_F9,    KC_F10,  KC_F11,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,   KC_9,     KC_0,    _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
                                            _______, _______,        _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
                                            _______, _______,        _______, _______
    )
};
