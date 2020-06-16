#include QMK_KEYBOARD_H

// For readability
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Default layer
    * ,------.   ,-------------------------------------------------------------------------------------------------.
    * |  F1  |   | Esc   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   | Ins |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F2  |   | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \     | Del |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F3  |   | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter      |Home |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F4  |   | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    RShift   |  U  | End |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F5  |   | Ctrl |  Gui  |  Alt  |              Space                | RAlt |  FN  | RCtrl |  L  | D  |  R  |
    * `------'   `-------------------------------------------------------------------------------------------------'
    */
    [_BASE] = LAYOUT_ansi_1u(
        KC_F1, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,
        KC_F2, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_F3, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,      KC_HOME,
        KC_F4, KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_F5, KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,                 KC_RALT, MO(1),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

    /* Fn1 Layer 
    * ,------.   ,-------------------------------------------------------------------------------------------------.
    * |  F6  |   |  `~   |     |     |     |     |     |     |     |     |     |     |     |      |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F7  |   |        |     |     |     |     |     |     |     |     |     |     |     |     |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F8  |   |         |VolD |VolU |Mute |     |     |     |     |     |     |     |     |               |PgUp |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F9  |   |           |Prev |Play |Next |     |     |     |     |     |     |     |             |     |PgDn |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |  F10 |   |      |       |       |                                   |      |      |       |     |    |     |
    * `------'   `-------------------------------------------------------------------------------------------------'
    */
    [_FN1] = LAYOUT_ansi_1u(
        KC_F6,   KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_F7,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_F8,   KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,       KC_PGUP,
        KC_F9,   KC_TRNS,          KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN,
        KC_F10,  KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

    /* Fn2 Layer 
    * ,------.   ,-------------------------------------------------------------------------------------------------.
    * |      |   |       |     |     |     |     |     |     |     |     |     |     |     |      |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |        |     |     |     |     |     |     |     |     |     |     |     |     |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |         |     |     |     |     |     |     |     |     |     |     |     |               |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |           |     |     |     |     |     |     |     |     |     |     |             |     |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |      |       |       |                                   |      |      |       |     |    |     |
    * `------'   `-------------------------------------------------------------------------------------------------'
    */
    [_FN2] = LAYOUT_ansi_1u(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

    /* Fn3 Layer 
    * ,------.   ,-------------------------------------------------------------------------------------------------.
    * |      |   |       |     |     |     |     |     |     |     |     |     |     |     |      |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |        |     |     |     |     |     |     |     |     |     |     |     |     |          |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |         |     |     |     |     |     |     |     |     |     |     |     |               |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |           |     |     |     |     |     |     |     |     |     |     |             |     |     |
    * |------|   |-------------------------------------------------------------------------------------------------|
    * |      |   |      |       |       |                                   |      |      |       |     |    |     |
    * `------'   `-------------------------------------------------------------------------------------------------'
    */
    [_FN3] = LAYOUT_ansi_1u(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
};
