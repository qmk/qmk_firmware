#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_4x6(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   
        KC_BKSP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   
        KC_LCTL, KC_MENU, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC
    )
};
