/* Copyright 2024 will-hedges */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layers {
    _QWER,
    _COLE,
    _DVOR,
    _FN1,
};

#define FN1_CAPS LT(_FN1, KC_CAPS)

//custom keycode enums
enum custom_keycodes {
    BASE_QWER = QK_USER,
    BASE_COLE,
    BASE_DVOR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWER] = LAYOUT_84_iso(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_DEL,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,          KC_PGUP,
        FN1_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_COLE] = LAYOUT_84_iso(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_DEL,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC, KC_RBRC,          KC_PGUP,
        KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_DVOR] = LAYOUT_84_iso(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_DEL,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_LBRC, KC_RBRC, KC_BSPC, KC_HOME,
        KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,     KC_SLSH, KC_EQL,  			KC_PGUP,
        FN1_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,     KC_MINS, KC_NUHS, KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,     KC_Z,    KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT_84_iso(
        _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC, BASE_QWER,
        _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, QK_BOOT, _______, _______, _______, 		  BASE_COLE,
        _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BASE_DVOR,
        _______, KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, KC_APP,  _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),

/*
    [_BLANK] = LAYOUT_84_iso(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),
*/
};


//macros to allow the user to set whatever default layer they want, even after reboot
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE_QWER:
            if (record->event.pressed) {
            // when keycode BASE_QWER is pressed
                set_single_persistent_default_layer(_QWER);
            } else {
            // when keycode BASE_QWER is released
            }
            break;

        case BASE_COLE:
            if (record->event.pressed) {
            // when keycode BASE_COLE is pressed
                set_single_persistent_default_layer(_COLE);
            } else {
            // when keycode BASE_COLE is released
            }
            break;

        case BASE_DVOR:
            if (record->event.pressed) {
            // when keycode BASE_DVOR is pressed
                set_single_persistent_default_layer(_DVOR);
            } else {
            // when keycode BASE_DVOR is released
            }
            break;
    }
    return true;
};
