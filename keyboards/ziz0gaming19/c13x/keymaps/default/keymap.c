#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LAYER2,
    _LAYER3,
    _FN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_10x4(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
        KC_Z, KC_X, KC_C, KC_V, KC_B, TO(1), KC_N, KC_M, KC_SLSH, KC_TAB,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),
    [_LAYER2] = LAYOUT_10x4(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(2), KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),
    [_LAYER3] = LAYOUT_10x4(
        KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, QK_RBT,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),
    [_FN] = LAYOUT_10x4(
        KC_ESC, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_PSCR, KC_NO, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_MPLY, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_SCLN, KC_QUOT, KC_ENT,
        KC_CAPS, KC_LBRC, KC_RBRC, KC_NUBS, KC_GRV, KC_NO, KC_COMM, KC_DOT, KC_SLSH, KC_TAB,
        KC_LCTL, KC_LALT, KC_SPC, KC_TRNS, KC_LGUI, KC_RSFT
    )
};
