#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_KP_7, KC_KP_8, KC_KP_9,
               KC_KP_4, LT(1, KC_KP_5), KC_KP_6,
               KC_KP_1, KC_KP_2, KC_KP_3),

  [1] = LAYOUT(RESET, RGB_TOG, RGB_MODE_FORWARD,
               RGB_HUI, RGB_HUD, RGB_SAI,
               RGB_SAD, RGB_VAI, RGB_VAD),

};
