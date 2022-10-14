#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ergodox(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    LGUI(KC_LCTL),
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_SPC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LGUI(KC_LALT),
        _______, _______, _______, _______, LOWER,
                                                       KC_LGUI, _______,
                                                                _______,
                                         KC_ENT, RGUI(KC_RCTL), _______,
        // right hand
        _______,       _______, _______, _______, _______, _______, _______,
        RGUI(KC_RCTL), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
                       KC_H,    KC_J,    KC_K,    KC_L,    KC_RSFT, KC_RGUI,
        RGUI(KC_RALT), KC_N,    KC_M,    KC_RCTL, KC_DOT,  KC_RALT, RGUI(KC_RSFT),
                                RAISE,   _______, _______, _______, _______,
             _______, KC_RGUI,
             _______,
             _______, KC_BSPC, KC_ENT
    ),

    [_LOWER] = LAYOUT_ergodox(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,
        _______, KC_LT,   KC_GT,   KC_LPRN, KC_RPRN, KC_GRV,
        KC_LALT, _______, _______, _______, KC_EQL,  KC_QUES, _______,
        _______, _______, _______, _______, _______,
                                                       _______, _______,
                                                                _______,
                                               KC_NO,  KC_NO,   _______,
        // right hand
        _______, _______, _______, _______, _______, _______, _______,
        KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,
                 KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_PIPE,
        KC_NO,   KC_UNDS, KC_PLUS, KC_COMM, _______, KC_SLSH, _______,
                          KC_RGUI, _______, _______, _______, _______,
             _______, KC_NO,
             _______,
             _______, KC_NO, KC_NO
    ),

    [_RAISE] = LAYOUT_ergodox(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
        KC_NO,   KC_COLN, KC_SCLN, KC_DQT,  KC_QUOT, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_LGUI,
                                                       _______, _______,
                                                                _______,
                                               KC_NO,  KC_NO,   _______,
        // right hand
        _______, _______, _______, _______, _______, _______, KC_NO,
        KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_NO,
        _______, ADJUST,  _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
             _______, KC_NO,
             _______,
             _______, KC_NO, KC_NO
    ),

    [_ADJUST] = LAYOUT_ergodox(
        // left hand
        _______,  _______,     _______,   _______, _______, _______, _______,
        _______,  _______,     _______,   _______, _______, _______,
        _______,  _______,     _______,   _______, _______, _______, _______,
        KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, QK_BOOT, _______,
        _______, _______, _______, _______, KC_LGUI,
                                                       _______, _______,
                                                                _______,
                                               KC_NO,  KC_NO,   _______,
        // right hand
        _______, _______, _______, _______, _______, _______,  _______,
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    _______,
                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,
        _______, _______, _______, _______, _______, KC_LNG1,  KC_LNG2,
                          _______, _______, _______, _______,  _______,
             _______, KC_NO,
             _______,
             _______, KC_NO, KC_NO
    )
};
