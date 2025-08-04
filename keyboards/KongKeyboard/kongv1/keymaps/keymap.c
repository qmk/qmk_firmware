#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ortho_5x5(
KC_1, KC_2, KC_3, KC_4, KC_5,
KC_6, KC_7, KC_8, KC_9, KC_0,
KC_Q, KC_W, KC_E, KC_R, KC_T,
KC_A, KC_S, KC_D, KC_F, KC_G,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  
)
};

