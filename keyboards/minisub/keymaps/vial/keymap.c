#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Qwerty */
    KC_GESC,       KC_Q,    KC_W,    KC_E,  KC_R, KC_T,    KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,        KC_A,    KC_S,    KC_D,  KC_F, KC_G,    KC_H,   KC_J,  KC_K,    KC_L,    KC_QUOT, LT(2, KC_ENT),
    KC_LSFT,       KC_Z,    KC_X,    KC_C,  KC_V, KC_B,    KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
    KC_LCTL,       KC_LGUI, KC_LALT,              LT(1, KC_SPC),                   KC_LEFT, KC_DOWN, KC_RIGHT
  ),
  [1] = LAYOUT( /* LAYER 2 */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS, KC_MINS, KC_EQL,  KC_BSLS, KC_TRNS, KC_TRNS, KC_UP,   KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SLSH, KC_PGUP, KC_BSLS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_HOME, KC_PGDN, KC_END
  ),
  [2] = LAYOUT( /* LAYER 1 */
    KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MPLY,
    KC_TRNS, KC_UNDS, KC_PLUS, KC_PIPE, KC_TRNS, KC_TRNS, KC_VOLU, KC_MPRV, KC_VOLD, KC_MNXT, KC_COLN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_QUES, KC_VOLU, KC_PIPE,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_MPRV, KC_VOLD, KC_MNXT
  ),
  [3] = LAYOUT( /* LAYER 3 */
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS
  )
};
