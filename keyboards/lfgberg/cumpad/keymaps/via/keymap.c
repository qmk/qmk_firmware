#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-------------------------------------------------,
   * | c  | c  |    | u  |    | u  |    | m  |    | m  |
   * |----|----|----|----|----|----|----|----|----|----|
   * | c  |    |    | u  |    | u  |    | m  | m  | m  |
   * |----|----|----|----|----|----|----|----|----|----|
   * | c  | c  |    | u  | u  | u  |    | m  |    | m  |
   * ,-------------------------------------------------,
   */

   [0] = LAYOUT(
     KC_C, KC_C,  KC_U,       KC_U,  KC_M,       KC_M,
     KC_C,        KC_U,       KC_U,  KC_M, KC_M, KC_M,
     KC_C, KC_C,  KC_U, KC_U, KC_U,  KC_M,       KC_M
   ),
   [1] = LAYOUT(
     KC_TRNS, KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
     KC_TRNS,           KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
     KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
   ),
   [2] = LAYOUT(
     KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
     KC_TRNS,            KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
     KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
   ),
   [3] = LAYOUT(
     KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
     KC_TRNS,            KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
     KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
   )
};
