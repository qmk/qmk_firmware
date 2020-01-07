#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,-----------------------.
 * |   1   |   2   |   3   |
 * |-------+-------+-------|
 * |   4   | 5/ENT |   6   | Dbl Tap 5 for Enter
 * |-------+-------+-------|
 * |  7/0  |   8   | 9/FN  | 7/0 = Dbl Tap 7 for 0  -  9/FN = Hold 9 for FN
 * `-----------------------'
 */
[0] = LAYOUT( \
  KC_1,       BL_TOGG,      KC_3,       \
  KC_4,       KC_5,      KC_6,       \
  KC_7,       KC_8,      LT(1, KC_9) \
),

/* LAYER 1
 * ,-----------------------.
 * |  ESC  |   +   |   -   |
 * |-------+-------+-------|
 * |  BSPC |   *   |   /   |
 * |-------+-------+-------|
 * |  00   |   .   |       |
 * `-----------------------'
 */
[1] = LAYOUT( \
  KC_ESC,   KC_PLUS, KC_MINS, \
  KC_ENTER, KC_ASTR, KC_SLSH, \
  KC_0,     KC_DOT,  KC_TRNS  \
)

};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}