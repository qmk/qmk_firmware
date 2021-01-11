#include QMK_KEYBOARD_H

enum layer {
    LAYER_DEFAULT,
    LAYER_FUNCTION,
    LAYER_ADJUST,
};

/* Switch to function layer when held. */
#define LY_FUNC MO(LAYER_FUNCTION)

/* Switch to adjust layer when held. */
#define LY_ADJST MO(LAYER_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default layer: http://www.keyboard-layout-editor.com/#/gists/327b41b5a933b3d44bf60ca9822e85dc */
    [LAYER_DEFAULT] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
        KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  LY_FUNC,
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,   KC_RALT,  LY_ADJST, KC_APP,   KC_RCTL
    ),

    /* Function layer: http://www.keyboard-layout-editor.com/#/gists/c7a55e75285d474b6301140eaf53f915 */
    [LAYER_FUNCTION] = LAYOUT_60_ansi_split_bs_rshift(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,
        KC_CAPS,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_UP,    _______,  _______,
        _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_LEFT,  KC_RGHT,  _______,
        _______,  _______,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDN,  KC_DOWN,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Adjust layer: http://www.keyboard-layout-editor.com/#/gists/6e1068e4f91bbacccaf5ac0acbeec79c */
    [LAYER_ADJUST] = LAYOUT_60_ansi_split_bs_rshift(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  EEP_RST,  RESET,    _______,  _______,  _______,  RGB_VAI,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUI,  RGB_SAI,  RGB_RMOD, RGB_MOD,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  BL_BRTG,  BL_DEC,   BL_INC,   RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};
