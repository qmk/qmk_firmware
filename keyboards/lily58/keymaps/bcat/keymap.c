#include QMK_KEYBOARD_H

enum layer {
    LAYER_DEFAULT,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
};

#define LY_LWR MO(LAYER_LOWER)
#define LY_RSE MO(LAYER_RAISE)

#define KY_CESC LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_DEFAULT] = LAYOUT(
        KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KY_CESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LBRC,  KC_RBRC,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                      KC_LCTL,  KC_LALT,  LY_LWR,   KC_SPC,   KC_ENT,   LY_RSE,   KC_RGUI,  KC_APP
    ),

    [LAYER_LOWER] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F11,   KC_F12,   KC_INS,   KC_DEL,   _______,  _______,
        _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   _______,  _______,  KC_LBRC,  KC_RBRC,  KC_GRV,   KC_BSLS,  _______,  _______,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    [LAYER_RAISE] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        KC_PLUS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,
        _______,  _______,  _______,  _______,  _______,  _______,                      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_PGUP,
        _______,  _______,  KC_CAPS,  KC_PSCR,  KC_SLCK,  KC_PAUS,  _______,  _______,  KC_LCBR,  KC_RCBR,  KC_TILD,  KC_PIPE,  KC_END,   KC_PGDN,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    [LAYER_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,  _______,                      EEP_RST,  RESET,    _______,  _______,  _______,  _______,
        _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}
