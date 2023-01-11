#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

// Tilde is shift-grave
#define KC_TLDE S(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Del |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Home|
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,  KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,  KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, KC_HOME,\
  MO(_FL), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,  KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,  KC_PGUP,\
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,   KC_PGDN,\
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                        MO(_FL), KC_ALGR, KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * | ` | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |Prt|Bks|PgU|Hom|End|Pau| Up|   |   |     |end |
   * |----------------------------------------------------------------|
   * |      |Lef|Dow|Rig|Scl|Del|PgD| ~ |Ins|Lef|Dow|Rig|        |Prt |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS, \
  KC_CAPS, _______, KC_UP,   _______, KC_BSPC, KC_PSCR, KC_PGUP, KC_HOME, KC_END,  KC_PAUS, KC_UP,   _______, _______, _______, KC_END, \
  _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  KC_SCRL, KC_PGDN, KC_TLDE, KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT,         _______, KC_PSCR,\
  _______,          _______, _______, BL_DOWN, BL_TOGG, BL_UP,   _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_BTN1, KC_MS_U, KC_BTN2,\
  _______, _______, _______,                   _______,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),
};
