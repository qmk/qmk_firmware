#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BL = 0, // Base Layer
  _FL,      // Function Layer
  _LL      // Lights layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT_65_ansi_7u_wk_splitbs(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, LT(_FL, KC_UP), KC_DEL,
        MO(_LL), KC_LALT, KC_LGUI,                   KC_SPC,                                       KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT),

    [_FL] = LAYOUT_65_ansi_7u_wk_splitbs(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,  _______,
        _______, _______, _______, _______, RESET,   _______, _______, _______, _______, KC_SLCK, KC_PAUS, KC_UP,   _______, _______, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______,                   _______,                                     _______, _______, _______, _______),

    [_LL] = LAYOUT_65_ansi_7u_wk_splitbs(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG, RGB_VAD,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, RGB_SAD,
        _______, _______, _______,                   _______,                                     _______, RGB_RMOD, RGB_HUD, RGB_MOD),
};