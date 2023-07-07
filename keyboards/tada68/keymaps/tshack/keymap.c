#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Fn  |Win |Alt |        Space          |Alt|Fn |Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   *
   * Note: Shift + Esc = ~
   *       Win   + Esc = `
   */
[_BL] = LAYOUT_ansi(
  QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, KC_GRV,
  KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, KC_DEL ,
  KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,      KC_PGUP,
  KC_LSFT,          KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,  KC_UP,  KC_PGDN,
  MO(_FL), KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, MO(_FL), KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  Del  |    |
   * |----------------------------------------------------------------|
   * |     |BL |BL-|BL+|   |   |   |   |   |   |PSc|   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |<- |Dn |Up | ->|   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |        |MUT|V- |V+ |   |   |   |   |   |   |   |      |PUp|End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |Hme|PDn|End |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12, KC_DEL,   _______,
  _______, BL_TOGG, BL_DOWN, BL_UP  , _______, _______, _______, _______, _______, _______,  KC_PSCR, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,     _______,      KC_HOME,
  _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,  _______, _______,     KC_PGUP,      KC_END ,
  _______, _______, _______,                 _______,                     _______, _______,  _______, KC_HOME,     KC_PGDN,      KC_END ),
};
