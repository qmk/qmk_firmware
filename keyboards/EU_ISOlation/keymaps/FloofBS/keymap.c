#include "EU_ISO.h"

enum layers {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_EUISO_BIGSPACE(
                        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_F1,  KC_F2,  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, LT(_FN2, KC_QUOT),
        KC_F3,  KC_F4,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, LT(_FN1, KC_ENT),
                        KC_LCTL, KC_LALT,                          KC_SPC,                                  KC_LGUI, MO(_FN3)
    ),

    [_FN1] = LAYOUT_EUISO_BIGSPACE(
                          KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL,
        _______, _______, KC_ESC , KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    ),

    [_FN2] = LAYOUT_EUISO_BIGSPACE(
                          KC_GRV ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
        _______, _______, KC_ESC , KC_BSLS, KC_QUOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,    KC_4,    KC_5,    KC_6, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    ),

    [_FN3] = LAYOUT_EUISO_BIGSPACE(
                          _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______,   RESET, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                          _______, _______,                         _______,                                        _______,  _______
    )
};
