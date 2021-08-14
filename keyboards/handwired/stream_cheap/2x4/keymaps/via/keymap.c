#include QMK_KEYBOARD_H


enum layers {
  NORMAL_LAYER = 0,
  SECOND_LAYER = 1,
  THIRD_LAYER = 2,
  FOURTH_LAYER = 3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL_LAYER] = LAYOUT_ortho_2x4(
        KC_A,  KC_A, KC_A, TO(3),
        KC_A, KC_A, KC_A, TO(1)
    ),
    [SECOND_LAYER] = LAYOUT_ortho_2x4(
        KC_B,   KC_B, KC_B, TO(0),
        KC_B, KC_B, KC_B, TO(2)
    ),
    [THIRD_LAYER] = LAYOUT_ortho_2x4(
        KC_C,   KC_C, KC_C, TO(1),
        KC_C, KC_C, KC_C, TO(3)
    ),
    [FOURTH_LAYER] = LAYOUT_ortho_2x4(
        KC_D,   KC_D, KC_D, TO(2),
        KC_D, KC_D, KC_D, TO(0)
    )
};
