#include QMK_KEYBOARD_H

enum _layers {
  BS,
  FN
};

// shim wilba_tech
#ifndef EF_DEC
    #define EF_DEC RGB_RMOD
    #define EF_INC RGB_MOD
    #define H1_DEC RGB_HUD
    #define H1_INC RGB_HUI
    #define H2_DEC RGB_HUD
    #define H2_INC RGB_HUI
    #define S1_DEC RGB_SAD
    #define S1_INC RGB_SAI
    #define S2_DEC RGB_SAD
    #define S2_INC RGB_SAI
    #define BR_DEC RGB_VAD
    #define BR_INC RGB_VAI
    #define ES_DEC KC_TRNS
    #define ES_INC KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BS] = LAYOUT_65_ansi( /* Base */
    KC_GRV,          KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,\
    KC_TAB,          KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,\
    LCTL_T(KC_ESC),  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,\
    KC_LSFT,         KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END, \
    KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                          KC_RGUI, MO(FN),   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT),

[FN] = LAYOUT_65_ansi( /* FN */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,\
    KC_TRNS, EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  BR_DEC,  BR_INC,  ES_DEC,  ES_INC,  KC_TRNS,          KC_TRNS, KC_TRNS,\
    KC_VOLU, KC_VOLD, KC_MUTE,                KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
