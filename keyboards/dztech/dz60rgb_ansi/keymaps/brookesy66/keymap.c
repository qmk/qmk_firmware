#include QMK_KEYBOARD_H

// layers
#define _BL 0 // base layer (default)
#define _ML 1 // modify/movement layer
#define _UL 2 // utility layer
#define SPC_ML LT(_ML, KC_SPC) // tap for space, hold for modify/movement layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Template
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//          _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//          _______, _______, _______, _______,                            _______,                            _______, _______, _______,

    [_BL] = LAYOUT_60_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CAPSWRD,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSPO,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC,
        KC_LCTL,        KC_LGUI, KC_LALT,                            SPC_ML,                             KC_RALT, KC_RGUI, MO(_UL), KC_RCTL
    ),
    [_ML] = LAYOUT_60_ansi(
        KC_GRV,         KC_MUTE, KC_VOLD, KC_VOLU, KC_END,  KC_F5,   _______, _______, _______, _______, KC_HOME, _______, _______, KC_DEL,
        _______,        _______, _______, _______, _______, _______, _______, KC_PGUP, KC_INS,  _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          _______,
        _______,        _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [_UL] = LAYOUT_60_ansi(
        KC_GRV,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,                 _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______,          _______,
        _______,        _______, _______,                            _______,                            _______, _______, _______, _______
    )
};
