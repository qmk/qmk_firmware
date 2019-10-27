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
    /* Default layer: http://www.keyboard-layout-editor.com/#/gists/e0eb3af65961e9fd612dcff3ddd88e4f */
    [LAYER_DEFAULT] = LAYOUT(
        KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KY_CESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LBRC,  KC_RBRC,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                      KC_LCTL,  KC_LALT,  LY_LWR,   KC_SPC,   KC_ENT,   LY_RSE,   KC_RGUI,  KC_APP
    ),

    /* Lower layer: http://www.keyboard-layout-editor.com/#/gists/19ad0d3b5d745fbb2818db09740f5a11 */
    [LAYER_LOWER] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
        _______,  _______,  _______,  KC_PIPE,  KC_TILD,  KC_DEL,                       _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  _______,
        _______,  _______,  _______,  KC_BSLS,  KC_GRV,   KC_INS,   _______,  _______,  _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  _______,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Raise layer: http://www.keyboard-layout-editor.com/#/gists/912be7955f781cdaf692cc4d4c0b5823 */
    [LAYER_RAISE] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_PGUP,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  KC_F11,   KC_F12,   _______,  _______,  KC_END,   KC_PGDN,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Adjust layer: http://www.keyboard-layout-editor.com/#/gists/8f6a3f08350a9bbe1d414b22bca4e6c7 */
    [LAYER_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        KC_CAPS,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,                      EEP_RST,  RESET,    KC_PSCR,  KC_SLCK,  KC_PAUS,  _______,
        _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}
