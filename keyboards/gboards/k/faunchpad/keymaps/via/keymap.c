#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_faunch( 	KC_1,     KC_2,     KC_3,     KC_4,
  										  KC_5,     KC_6,     KC_7,     KC_8),
  [1] = LAYOUT_faunch( 	KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
