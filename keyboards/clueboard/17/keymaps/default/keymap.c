#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * .-------------------.
   * |NL F|   /|   *|   -|
   * |-------------------|
   * |   7|   8|   9|    |
   * |--------------|    |
   * |   4|   5|   6|   +|
   * |-------------------|
   * |   1|   2|   3|    |
   * |--------------|    |
   * |        0|   .| Ent|
   * '-------------------'
   */
  [_BL] = LAYOUT_numpad_5x4(
    LT(_FL, KC_NUM),  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,            KC_P8,   KC_P9,
    KC_P4,            KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,            KC_P2,   KC_P3,
    KC_P0,                     KC_PDOT, KC_PENT
  ),

  /* Keymap _FL: Function Layer
   * .-------------------.
   * |NL F|    |    | Fn0|
   * |-------------------|
   * |    | Fn4|    |    |
   * |--------------|    |
   * | Fn3|BL_S| Fn2| Fn6|
   * |-------------------|
   * |    | Fn5|    |    |
   * |--------------|    |
   * |      Fn1|    | Fn7|
   * '-------------------'
   */
  [_FL] = LAYOUT_numpad_5x4(
    LT(_FL, KC_NUM),  _______, _______, UG_TOGG,
    _______,          UG_SATU, _______,
    UG_HUED,          BL_STEP, UG_HUEU, UG_VALU,
    _______,          UG_SATD, _______,
    UG_NEXT,                   _______, UG_VALD
  )
};
