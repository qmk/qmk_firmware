#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0, default layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ Esc │  F1 │  F2 │  F3 │  F4 │  F5 │  F6 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ ` ~ │  1  │  2  │  3  │  4  │  5  │  6  │
   * ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │    Tab    │  Q  │  W  │  E  │  R  │  T  │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤
   * │ Caps Lock │  A  │  S  │  D  │  F  │  G  │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤
   * │   Shift   │  Z  │  X  │  C  │  V  │  B  │
   * ├───────────┼─────┼─────┼─────┼─────┴─────┤
   * │   Ctrl    │  Fn │ Alt │Super│   Space   │
   * └───────────┴─────┴─────┴─────┴───────────┘
   */

  [0] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
         KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
         KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
         KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
         KC_LCTL,     MO(1),   KC_LALT, KC_LGUI,     KC_SPC
  ),

  /* Layer 1, function layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │RESET│
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │
   * ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │           │     │     │     │     │     │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤
   * │           │     │     │     │     │     │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤
   * │           │     │     │     │     │     │
   * ├───────────┼─────┼─────┼─────┼─────┴─────┤
   * │           │     │     │     │           │
   * └───────────┴─────┴─────┴─────┴───────────┘
   */

  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
