#include QMK_KEYBOARD_H
#include "haervig.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        KC_GESC,        DK_1,    CU_2,    DK_3,    CU_4,    DK_5,    CU_6,    CU_7,    CU_8,    CU_9,    CU_0,    CU_MINS, CU_EQL,  CU_BSPC, KC_HOME,
        KC_TAB,         DK_Q,    DK_W,    DK_E,    DK_R,    DK_T,    DK_Y,    DK_U,    DK_I,    DK_O,    DK_P,    CU_LBRC, CU_RBRC, CU_BSLS, KC_PGUP,
        CTL_T(KC_CAPS), DK_A,    DK_S,    DK_D,    DK_F,    DK_G,    DK_H,    DK_J,    DK_K,    DK_L,    CU_SCLN, CU_QUOT,          KC_ENT,  KC_PGDN,
        CU_LSFT,                 DK_Z,    DK_X,    DK_C,    DK_V,    DK_B,    DK_N,    DK_M,    CU_COMM, CU_DOT,  CU_SLSH, CU_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    )
};
