#include QMK_KEYBOARD_H

// Tap Dance Declarations
enum tap_dances {
  ENT_5 = 0,
  ZERO_7,
};

// Macro Declarations
enum custom_keycodes {
  DBL_0 = SAFE_RANGE,
};

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
[0] = LAYOUT(
  KC_1,       KC_2,      KC_3,
  KC_4,       TD(ENT_5), KC_6,
  TD(ZERO_7), KC_8,      LT(1, KC_9)
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
[1] = LAYOUT(
  KC_ESC,   KC_PLUS, KC_MINS,
  KC_BSPC,  KC_ASTR, KC_SLSH,
  DBL_0,    KC_DOT,  KC_TRNS
)

};

qk_tap_dance_action_t tap_dance_actions[] = {
  [ENT_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_ENT),
  [ZERO_7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_0)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DBL_0:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        tap_code(KC_P0);
        tap_code(KC_P0);
      }
      break;

  }
  return true;
};


void matrix_init_user(void) {
}
