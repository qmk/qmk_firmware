#include QMK_KEYBOARD_H

enum layers {
  NORMAL_LAYER = 0,
   SECOND_LAYER
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER] = LAYOUT_ortho_2x3(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, TO(1)
    ),
    [SECOND_LAYER] = LAYOUT_ortho_2x3(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, TO(0)
    )
};

