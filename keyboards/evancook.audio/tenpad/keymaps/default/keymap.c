#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,---------------------------------------.
 * |   Q   |   W   |   E   |   R   |   T   |
 * |-------+-------+-------|-------|-------|
 * |   A   |   S   |   D   |   F   |   G   |
 * ,---------------------------------------.
 * 
 * 
 */
[0] = LAYOUT( \
  KC_Q,       KC_W,      KC_E,      KC_R,      KC_T,         \
  KC_A,       KC_S,      KC_D,      KC_F,      KC_G         \
)
};
