#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_WBAK,   KC_WFWD,   LSG_T(KC_S),   G(KC_L),  MO(1) 
    ),

    [1] = LAYOUT(
        KC_BRIU,   KC_BRID,   KC_VOLU,   KC_VOLD,  _______
    )
};
