#include QMK_KEYBOARD_H

enum layers{
  _BASE
};

enum combo_events {
	COMBO_ESC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_default(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    KC_A,  KC_S,  KC_D,  KC_F,   KC_G,   KC_H,  KC_J,   KC_K,  KC_L, KC_ENT,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM, KC_DOT,
    KC_1, KC_2, KC_3, KC_4, KC_SPACE, KC_4, KC_3, KC_2, QK_BOOT
  )
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_esc[] = {KC_E, KC_W, COMBO_END};

combo_t key_combos[] = {
	[COMBO_ESC] = COMBO(combo_esc,KC_ESC),
};
#endif