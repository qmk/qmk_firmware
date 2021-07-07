#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   ,             KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
        LT(3, KC_TAB) , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T,                  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,
        LT(2, KC_CAPS), KC_A   , KC_S   , KC_D   , KC_F   , KC_G,                  KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT,
        LSFT_T(KC_GRV), KC_Z   , KC_X   , KC_C   , KC_V   , KC_B,                  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_BSPC),
        LCTL_T(KC_MINS), KC_LGUI, LALT_T(KC_EQL) , KC_SPC , LT(4, KC_ESC),         LT(1, KC_SPC) , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_PSCR, KC_F7  , KC_F8  , KC_F9  , KC_F12 , KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_PAUS, KC_F4  , KC_F5  , KC_F6  , KC_F11 , KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_INS , KC_F1  , KC_F2  , KC_F3  , KC_F10 , KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_7   , KC_8   , KC_9   , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_PMNS, KC_4   , KC_5   , KC_6   , KC_PLUS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_PAST, KC_1   , KC_2   , KC_3   , KC_PSLS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_0   , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_LCBR, S(KC_7), S(KC_8), S(KC_9), KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_LPRN, S(KC_4), S(KC_5), S(KC_6), KC_RPRN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_LBRC, S(KC_1), S(KC_2), S(KC_3), KC_RBRC, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               S(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [4] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
        KC_TRNS, A(KC_F4),C(KC_EQL), KC_END, C(KC_0), LCA(KC_DEL),                 KC_WBAK, C(KC_PGUP), C(KC_PGDN), KC_WFWD, C(KC_P), KC_TRNS, KC_TRNS, KC_MPLY,
        KC_TRNS, KC_HOME, C(KC_MINS), KC_DEL , KC_RGHT, KC_TRNS,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLU, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_SLEP, KC_TRNS, KC_SYSTEM_POWER, KC_TRNS, KC_LEFT,              KC_MNXT, KC_MPRV, KC_PGUP, KC_PGDN, KC_VOLD, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};
