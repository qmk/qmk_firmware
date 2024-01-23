// Copyright 2024 jonylee@hfd (@jonylee1986)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// clang-format off
enum __layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN
};
#define KC_SIRI LGUI(KC_SPC)
#define KC_TASK LGUI(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_ansi( /* Base */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_DEL,       KC_MUTE,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,      KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,      KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                 KC_HOME,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                KC_UP,   KC_END,
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(WIN_FN),KC_RCTL,    KC_LEFT,  KC_DOWN, KC_RGHT),

    [WIN_FN] = LAYOUT_ansi( /* FN */
		EE_CLR,  KC_BRID, KC_BRIU, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MYCM, KC_WHOM, KC_TASK, KC_CALC, RGB_TOG,       _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       RGB_MOD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       RGB_HUI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               RGB_VAI,  _______,
		_______, GU_TOGG, _______,                   _______,                             _______, _______, _______,     RGB_SPD, RGB_VAD, RGB_SPI),

    [MAC_B] = LAYOUT_ansi( /* Base */
		KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL,C(KC_DOWN),KC_LPAD,KC_SIRI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,        KC_MUTE,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                 KC_HOME,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,               KC_UP,    KC_END,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MO(MAC_FN),KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN] = LAYOUT_ansi( /* FN */
		EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_TOG,       _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       RGB_MOD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       RGB_HUI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               RGB_VAI,  _______,
		_______, _______, _______,                   _______,                            _______, _______, _______,      RGB_SPD, RGB_VAD, RGB_SPI),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        default:
            break;
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [WIN_B]  = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_SAI, RGB_SAD)},
    [MAC_B]  = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [MAC_FN] = {ENCODER_CCW_CW(RGB_SAI, RGB_SAD)},
};
#endif
