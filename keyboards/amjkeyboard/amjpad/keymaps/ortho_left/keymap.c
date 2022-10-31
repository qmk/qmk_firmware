#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * | T  | G  | B  |Spac|
   * |----|----|----|----|
   * | R  | F  | V  | Fn |
   * |----|----|----|----|
   * | E  | D  | C  | OS |
   * |----|----|----|----|
   * | W  | S  | X  | Alt|
   * |----|----|----|----|
   * | Q  | A  | Z  | Ctl|
   * |----|----|----|----|
   * | Esc| Tab|Shft| Fn2|
   * `-------------------'
   */

  [_BL] = LAYOUT_ortho_6x4(
    KC_T,   KC_G,   KC_B,      KC_SPACE,\
    KC_R,   KC_F,   KC_V,      MO(1),    \
    KC_E,   KC_D,   KC_C,      KC_LGUI, \
    KC_W,   KC_S,   KC_X,      KC_LALT, \
    KC_Q,   KC_A,   KC_Z,      KC_LCTL, \
    KC_TAB, KC_ESC, KC_LSFT,   MO(1)
  ),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * | 5  | F5 | F11|Spac|
   * |----|----|----|----|
   * | 4  | F4 | F10|    |
   * |----|----|----|----|
   * | 3  | F3 | F9 | OS |
   * |----|----|----|----|
   * | 2  | F2 | F8 | Alt|
   * |----|----|----|----|
   * | 1  | F1 | F7 | Ctl|
   * |----|----|----|----|
   * | `  | Del|Shft|    |
   * `-------------------'
   */
  [_FL] = LAYOUT_ortho_6x4(
    KC_5,  KC_F5,  KC_F11,  _______, \
    KC_4,  KC_F4,  KC_F10,  _______, \
    KC_3,  KC_F3,  KC_F9,   _______, \
    KC_2,  KC_F2,  KC_F8,   _______, \
    KC_1,  KC_F1,  KC_F7,   _______, \
    KC_GRV,KC_DEL, _______, _______
  ),
};
