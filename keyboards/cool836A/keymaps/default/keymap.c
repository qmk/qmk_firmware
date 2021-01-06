#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_ESC,  LALT_T(KC_Q), KC_W,        KC_E, KC_R,        KC_T,  \
        KC_LCTL, KC_A,         KC_S,        KC_D, KC_F,        KC_G, \
        KC_LSFT, KC_Z,         GUI_T(KC_X), KC_C, LT(3, KC_V), LT(2, KC_B), \

        KC_Y,   KC_U,           KC_I, KC_O,    KC_P,     KC_BSPC, \
        KC_H,   KC_J,           KC_K, KC_L,    KC_MINS,  KC_ENTER, \
        KC_SPC, LT(1, KC_N), KC_M, KC_COMM, KC_DOT,   KC_SPC
    ),
    [1] = LAYOUT(
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,\
        KC_LCTL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,\
        KC_LSFT, _______, _______, _______, _______, _______,\

        KC_6,    KC_7,     KC_8,    KC_9,    KC_0,   KC_BSPC,\
        KC_PLUS, KC_MINS, KC_ASTR, KC_PSLS, KC_EQL,  KC_ENTER,\
        _______, _______, _______, _______, _______, KC_SPC
    ),
    [2] = LAYOUT(
        KC_TAB,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,\
        KC_LCTL, KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN,  KC_COLN,\
        KC_LSFT, KC_UNDS, KC_PIPE, KC_CIRC, KC_TILD, _______,\

        KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_BSPC,\
        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUES, KC_ENTER,\
        _______, _______, _______, _______,  _______,  KC_SPC
    ),
    [3] = LAYOUT(
        _______, _______, _______, KC_LPRN, KC_RPRN, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \

        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______
    )
};

