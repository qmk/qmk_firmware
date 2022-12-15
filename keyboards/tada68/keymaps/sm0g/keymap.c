#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _GM 2
#define _GF 3


// Tap dance declarations (These must go above the keymaps)
enum {
  TD_F1 = 0,
  TD_F2,
  TD_F3,
  TD_F4,
  TD_F5,
  TD_F6,
  TD_F7,
  TD_F8,
  TD_F9,
  TD_F10,
  TD_F11,
  TD_F12,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   \   |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bksp |Del |
   * |----------------------------------------------------------------|
   * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Caps|Win |Alt |        Space          |Alt|Ctrl| FN|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_ESC, TD(TD_F1), TD(TD_F2), TD(TD_F3), TD(TD_F4), TD(TD_F5), TD(TD_F6), TD(TD_F7), TD(TD_F8), TD(TD_F9), TD(TD_F10), TD(TD_F11), TD(TD_F12), KC_BSLS,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSPC,KC_DEL, \
  CTL_T(KC_ESC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  SC_LSPO,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   SC_RSPC,KC_UP,KC_PGDN, \
  KC_CAPS, KC_LGUI,KC_LALT,                KC_SPC,                        KC_RALT,KC_RCTL,MO(_FL), KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|       |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * | Caps |<- |Dn | ->|   |   |   |   |   |   |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |   |Prev|P/P|Next|
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, TG(_GM), KC_INS ,  \
  _______,_______, KC_UP,_______,_______, _______,_______,_______,_______,_______,_______,_______,_______, _______,KC_HOME, \
  KC_CAPS,KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,_______,_______,_______,_______,_______,_______,        _______,KC_END, \
  _______,_______,_______,BL_DOWN,BL_TOGG,BL_UP,  BL_BRTG,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______, _______, _______, \
  _______,_______,_______,                 _______,               _______,_______,_______,KC_MPRV,KC_MPLY, KC_MNXT),

[_GM] = LAYOUT_ansi(
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, _______,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSPC,KC_DEL, \
  KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN, \
  KC_CAPS, KC_LGUI,KC_LALT,                KC_SPC,                        KC_RALT,KC_RCTL,MO(_GF), KC_LEFT,KC_DOWN,KC_RGHT),
  
[_GF] = LAYOUT_ansi(
 _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, TG(_GM), KC_INS ,  \
  _______,_______, KC_UP,_______,_______, _______,_______,_______,_______,_______,_______,_______,_______, _______,KC_HOME, \
  KC_CAPS,KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,_______,_______,_______,_______,_______,_______,        _______,KC_END, \
  _______,_______,_______,BL_DOWN,BL_TOGG,BL_UP,  BL_BRTG,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______, _______, _______, \
  _______,_______,_______,                 _______,               _______,_______,_______,KC_MPRV,KC_MPLY, KC_MNXT),

};

// Tapdance definitions. Tap Dance F Keys.
tap_dance_action_t tap_dance_actions[] = {
  [TD_F1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1),
  [TD_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_F2),
  [TD_F3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),
  [TD_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_F4),
  [TD_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
  [TD_F6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_F6),
  [TD_F7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_F7),
  [TD_F8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_F8),
  [TD_F9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_F9),
  [TD_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_F10),
  [TD_F11] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_F11),
  [TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_F12),
};
