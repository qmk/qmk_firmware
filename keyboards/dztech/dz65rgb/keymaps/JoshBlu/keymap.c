#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        KC_GRAVE,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        LT(1, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        SC_LSPO,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, KC_RGUI,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MPRV,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT, KC_VOLU,
        _______,        RGB_SPI, RGB_SPD, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          EE_CLR,  KC_VOLD,
        KC_LSFT,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_PGUP, KC_MNXT,
        _______,        _______, _______,                            _______,                   _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    )
};


#ifdef RGB_MATRIX_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t  layer = get_highest_layer(state);
    if ((layer > 0) && (layer < 10)) { //Only works for layers 1 - 9 where 0 would be the default layer
        rgb_matrix_set_color(layer, 0xFF, 0xFF, 0xFF);  //Set the coresponding backlight in the number row on to show layer number
    }
    return state;
}
#endif