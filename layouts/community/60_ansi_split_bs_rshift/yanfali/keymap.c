#include QMK_KEYBOARD_H

enum {
    BASE,
    FN,
    YFL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_60_ansi_split_bs_rshift(
    KC_ESC,         KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV, KC_BSPC,
    KC_TAB,         KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
    LCTL_T(KC_ESC), KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,
    KC_LSFT,        KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  MO(YFL),
    KC_LCTL,        KC_LALT, KC_LGUI,       KC_SPACE,             KC_RGUI, KC_RALT, MO(FN),  KC_RCTL),

[FN] = LAYOUT_60_ansi_split_bs_rshift(
    KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______,             _______,                               _______, _______, _______, _______),

[YFL] = LAYOUT_60_ansi_split_bs_rshift(
    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, EE_CLR,  QK_BOOT,
    KC_CAPS, KC_LEFT,  KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, _______,  _______,             _______,                               _______, _______, _______, _______),
};
