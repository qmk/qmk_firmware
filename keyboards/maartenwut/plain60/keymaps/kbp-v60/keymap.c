#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum _layer {
  _MA,
  _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MA] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          \
  MO(_FN), KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,           \
  KC_LSFT, KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, LT(_FN, KC_UP),   \
  KC_LCTL, KC_LGUI, KC_LALT,                        KC_SPC,                          MO(_FN), KC_ALGR , LT(_FN, KC_APP),  KC_RCTRL),

[_FN] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL, \
  KC_CAPS, _______, KC_UP,   _______, KC_BSPC, KC_PSCR, KC_PGUP, KC_HOME, KC_END,  KC_HOME, KC_UP,   KC_END,  _______, KC_PGUP,\
  _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  KC_SLCK, KC_PGDN, KC_TILD, KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT,         KC_PGDN,\
  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_BTN1, KC_MS_U,\
  _______, _______, _______,                   _______,                            _______, _______, _______, KC_MS_L, KC_MS_D),
};
