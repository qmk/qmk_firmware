#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap _BL: (Base Layer) Default Layer
 * +-------------------------------------------------------------------------+
 * | ESC | 1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP |
 * +-------------------------------------------------------------------------+
 * | TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  |
 * +-------------------------------------------------------------------------+
 * | FN     |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |  RETURN |
 * +-------------------------------------------------------------------------+
 * | LSHIFT   |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / | SHIFT | FN |
 * +-------------------------------------------------------------------------+
 * |LALT|LMETA|RCTRL|   SPACE | FN | SPACE           | RALT| MENU| RWIN|RCTRL|
 * +-------------------------------------------------------------------------+
 */

  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, _______, KC_BSPC, \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    MO(_FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN1), \
    KC_LALT,  KC_LGUI, KC_LCTL, KC_SPC,  MO(_FN1), KC_SPC,  _______, KC_RALT, KC_APP,  _______, KC_RGUI, KC_RCTL
  ),

  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * | ~  | F1| F2| F3| F4| F5| F6| F7| F8| F9| F0|F11|F12|  DEL |
   * |-----------------------------------------------------------|
   * |     |   | UP|  | MSL|MSD|MSU|MSR|   |   |PRT|PGD|PGU|PAUS |
   * |-----------------------------------------------------------|
   * |       | LE| DN| RE|   |   | LE| DN| UP| RE|   |   |       |
   * |-----------------------------------------------------------|
   * |        |HOM|END|   |   |PRE|NXT|MUT|VOD|VOU|  /|Shift | FN|
   * |-----------------------------------------------------------|
   * |    |    |    |    |  PLAY | PLAY     |     |    |    |    |
   * `-----------------------------------------------------------'
   */

  [_FN1] = LAYOUT(
    KC_GRAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL, \
    _______,  _______, KC_UP,   _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, KC_PSCR, KC_PGUP, KC_PGDN, KC_PAUS, \
    _______,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, \
    _______,  KC_HOME, KC_END,  _______, _______, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, \
    _______,  _______, _______, KC_MPLY, _______,          KC_MPLY,         _______, _______, _______, _______, _______, _______
  )
};
