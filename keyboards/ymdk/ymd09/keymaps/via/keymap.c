#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_KP_7, KC_KP_8, KC_KP_9,
               KC_KP_4, LT(1, KC_KP_5), KC_KP_6,
               KC_KP_1, KC_KP_2, KC_KP_3),

  [1] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI, QK_BOOT, RGB_SAI,
               RGB_HUD, RGB_VAD, RGB_SAD),

  [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),

  [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),
};
