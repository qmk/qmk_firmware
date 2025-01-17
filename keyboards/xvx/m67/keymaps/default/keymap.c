// Copyright 2024 jonylee@hfd
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT( /* FN */
		EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RM_HUEU, KC_GRV,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_INS,  KC_PSCR, KC_PAUS, RM_NEXT, RM_SATU,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RM_SATD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RM_VALU, _______,
		_______, GU_TOGG, _______,                   _______,                                     _______, _______, RM_SPDD, RM_VALD, RM_SPDU),

    [2] = LAYOUT( /* Base */
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, MO(3),   KC_LEFT, KC_DOWN, KC_RGHT),

    [3] = LAYOUT( /* FN */
		EE_CLR,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RM_HUEU, KC_GRV,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_INS,  KC_PSCR, KC_PAUS, RM_NEXT, RM_SATU,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RM_SATD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RM_VALU, _______,
		_______, _______, _______,                   _______,                                     _______, _______, RM_SPDD, RM_VALD, RM_SPDU),
};
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        set_single_persistent_default_layer(active ? 2 : 0);
        if (active) {
            keymap_config.no_gui = 0;
            eeconfig_update_keymap(keymap_config.raw);
        }
    }
    return true;
}