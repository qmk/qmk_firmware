#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_keycodes {
  _L0 = SAFE_RANGE,
  _L1,
  _L2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_L0] = KEYMAP( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_NO,   KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,   KC_NO,   KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL, KC_NO,   KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, \
  KC_ESC, KC_TAB, KC_LGUI,  KC_LSFT,  KC_NO,   KC_BSPC, KC_LALT, KC_SPC,  MO(_L2),  KC_MINS, KC_QUOT, KC_ENT   \
),

[_L2] = KEYMAP( \
  KC_EXLM,  KC_AT,   KC_UP,   KC_LCBR, KC_RCBR, KC_NO,   KC_NO,   KC_PGUP, KC_7,    KC_8,   KC_9, KC_ASTR, \
  KC_HASH,  KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,  KC_NO,   KC_NO,   KC_PGDN, KC_4,    KC_5,   KC_6, KC_PLUS, \
  KC_LBRC,  KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR, KC_LCTL, KC_NO,   KC_GRV,  KC_1,    KC_2,   KC_3, KC_BSLS, \
  TG(_L1),  KC_INS,  KC_LGUI, KC_LSFT, KC_NO,   KC_BSPC, KC_LALT, KC_SPC,  KC_TRNS, KC_DOT, KC_0, KC_EQL   \
),

[_L1] = KEYMAP( \
  KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO,   KC_NO,   KC_UP,   KC_F7,    KC_F8,   KC_F9,   KC_F10, \
  KC_DELT, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOWN, KC_NO,   KC_NO,   KC_DOWN, KC_F4,    KC_F5,   KC_F6,   KC_F11, \
  KC_TRNS, KC_VOLU, KC_TRNS, KC_TRNS, RESET,   KC_LCTL, KC_NO,   KC_TRNS, KC_F1,    KC_F2,   KC_F3,   KC_F12, \
  KC_TRNS, KC_VOLD, KC_LGUI, KC_LSFT, KC_NO,   KC_BSPC, KC_LALT, KC_SPC,  DF(_L0),  KC_PSCR, KC_SLCK, KC_PAUS \
),

};

