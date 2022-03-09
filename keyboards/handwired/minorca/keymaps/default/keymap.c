#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_QUOT, MO(2),   MO(1),
    XXXXXXX, XXXXXXX, KC_LALT,                   KC_SPC,  KC_SPC,                    KC_DOT,  KC_SLSH, XXXXXXX
  ),
  [1] = LAYOUT( /* First */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_MPRV, KC_MPLY, KC_MNXT, KC_PGUP, KC_HOME, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_LGUI,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_PGDN, KC_END,  KC_L,    KC_SCLN, KC_UP,   _______, _______,
    XXXXXXX, XXXXXXX, KC_LALT,                   _______, _______,                   KC_DOWN, KC_RGHT, XXXXXXX
  ),
  [2] = LAYOUT( /* Second */
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TAB,  KC_MUTE, KC_VOLD, KC_VOLU, KC_TILD, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_ENT,
    KC_CAPS, KC_LSFT, KC_RSFT, KC_PAUS, KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_UP,   _______, _______,
    XXXXXXX, XXXXXXX, KC_LALT,                   _______, _______,                   KC_DOWN, KC_RGHT, XXXXXXX
  ),
};
