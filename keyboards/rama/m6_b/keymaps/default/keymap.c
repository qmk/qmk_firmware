#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        TO(1), KC_A, KC_B, KC_C, KC_D, KC_E),

    LAYOUT(
        TO(2), KC_F, KC_G, KC_H, KC_I, KC_J),

    LAYOUT(
        TO(3), KC_K, KC_L, KC_M, KC_N, KC_O),

    LAYOUT(
        TO(4), KC_P, KC_Q, KC_R, KC_S, KC_T),

    LAYOUT(
        TO(5), KC_U, KC_V, KC_W, KC_X, KC_Y),

    LAYOUT(
        TO(0), KC_Z, KC_1, KC_2, KC_3, KC_4)};

