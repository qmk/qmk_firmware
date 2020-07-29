#include QMK_KEYBOARD_H


enum layers {
  NORMAL_LAYER = 0,
  SECOND_LAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER] = LAYOUT_2x5(KC_1, KC_2, KC_3, KC_4, KC_5,
							KC_6, KC_7, KC_8, KC_9, TO(1)),
	[SECOND_LAYER] = LAYOUT_2x5(KC_A, KC_B, KC_C, KC_D, KC_E,
							KC_F, KC_G, KC_H, KC_I,TO(0))
};


