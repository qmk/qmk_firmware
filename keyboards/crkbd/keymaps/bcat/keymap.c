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
    /* Default layer: http://www.keyboard-layout-editor.com/#/gists/08d9827d916662a9414f48805aa895a5 */
    [LAYER_DEFAULT] = LAYOUT(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KY_CESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                                KC_LALT,  LY_LWR,   KC_SPC,   KC_ENT,   LY_RSE,   KC_RGUI
    ),

    /* Lower layer: http://www.keyboard-layout-editor.com/#/gists/c3fba5eaa2cd70fdfbdbc0f9e34d3bc0 */
    [LAYER_LOWER] = LAYOUT(
        KC_CAPS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,                      KC_PIPE,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_TILD,
        _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_APP,                       KC_BSLS,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_GRV,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Raise layer: http://www.keyboard-layout-editor.com/#/gists/08b44355d4ca85d294bad9e2821f91d7 */
    [LAYER_RAISE] = LAYOUT(
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_F11,   KC_DEL,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,                       KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F12,   KC_INS,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Adjust layer: http://www.keyboard-layout-editor.com/#/gists/77e7572e077b36a23eb2086017e16fee */
    [LAYER_ADJUST] = LAYOUT(
        _______,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,                      EEP_RST,  RESET,    _______,  _______,  _______,  _______,
        _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,                      RGB_RMOD, RGB_VAD,  RGB_VAI,  RGB_MOD,  RGB_SPI,  _______,
        _______,  _______,  _______,  KC_MUTE,  _______,  _______,                      RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_HUD,  RGB_SPD,  _______,
                                                _______,  _______,  _______,  RGB_TOG,  _______,  _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}
