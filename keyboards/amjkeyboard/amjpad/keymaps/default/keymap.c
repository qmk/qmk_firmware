#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Esc |TAB |BS  | =  |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   0     |./FN|    |
   * `-------------------'
   */

  [_BL] = LAYOUT_numpad_6x4(
    KC_ESC,  KC_TAB,  KC_BSPC, KC_PEQL,
    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,   KC_P2,   KC_P3,
      KC_P0, LT(_FL,KC_PDOT),  KC_PENT
  ),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * |Esc |TAB |BS  | =  |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----|RST |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   0     |./FN|    |
   * `-------------------'
   */
  [_FL] = LAYOUT_numpad_6x4(
    KC_ESC,  KC_TAB,  KC_BSPC, KC_PEQL,
    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,
    KC_P4,   KC_P5,   KC_P6,   QK_BOOT,
    KC_P1,   KC_P2,   KC_P3,
      KC_P0, LT(_FL,KC_PDOT),  KC_PENT
  ),
};
