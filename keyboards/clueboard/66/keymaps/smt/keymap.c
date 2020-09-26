#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _FL 3
#define _CL 4

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper (Super+Ctrl+Shift+Alt)
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWERTY: Base Layer (Default Layer)
   * ,-----------------------------------------------------------.  ,---.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|  |PgU|
   * |-----------------------------------------------------------|  |---|
   * |HpTab|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   BS|  |PgD|
   * |-----------------------------------------------------------|  `---'
   * |CtlEsc|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|   | Ent|
   * |--------------------------------------------------------------.
   * |Shift|  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift| Fn| Up|
   * |------------------------------------------------------------------.
   * |Ctrl|Gui|Alt |    | Space| Space|    |Alt |Gui |Ctrl|Left|Down|Rgt|
   * `------------------------------------------------------------------'
   */
[_QWERTY] = LAYOUT(
  KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS, KC_GRV,           KC_PGUP,
  HPR_TAB, KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,                   KC_PGDN,
  CTL_ESC, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  XXXXXXX,  KC_ENT,
  KC_LSFT, XXXXXXX, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  SFT_ENT,  MO(_FL),          KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,          KC_SPC,KC_SPC,                        XXXXXXX,  KC_RALT,  KC_RGUI,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _COLEMAK: Base Layer
   * ,-----------------------------------------------------------.  ,---.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|  |PgU|
   * |-----------------------------------------------------------|  |---|
   * |HpTab|  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|   BS|  |PgD|
   * |-----------------------------------------------------------|  `---'
   * |CtlEsc|  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|   | Ent|
   * |--------------------------------------------------------------.
   * |Shift|  |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift| Fn| Up|
   * |------------------------------------------------------------------.
   * |Ctrl|Gui|Alt |    | Space| Space|    |Alt |Gui |Ctrl|Left|Down|Rgt|
   * `------------------------------------------------------------------'
   */
[_COLEMAK] = LAYOUT(
  KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS, KC_GRV,           KC_PGUP,
  HPR_TAB, KC_Q,    KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSPC,                   KC_PGDN,
  CTL_ESC, KC_A,    KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,    KC_O,     KC_QUOT,  XXXXXXX,  KC_ENT,
  KC_LSFT, XXXXXXX, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  SFT_ENT,  MO(_FL),          KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,          KC_SPC,KC_SPC,                        XXXXXXX,  KC_RALT,  KC_RGUI,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _DVORAK: Base Layer
   * ,-----------------------------------------------------------.  ,---.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|  \|  `|  |PgU|
   * |-----------------------------------------------------------|  |---|
   * |HpTab|  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|   BS|  |PgD|
   * |-----------------------------------------------------------|  `---'
   * |CtlEsc|  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|   | Ent|
   * |--------------------------------------------------------------.
   * |Shift|  |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|Shift| Fn| Up|
   * |------------------------------------------------------------------.
   * |Ctrl|Gui|Alt |    | Space| Space|    |Alt |Gui |Ctrl|Left|Down|Rgt|
   * `------------------------------------------------------------------'
   */
[_DVORAK] = LAYOUT(
  KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_GRV,           KC_PGUP,
  HPR_TAB, KC_QUOT, KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,    KC_L,     KC_SLSH,  KC_EQL,   KC_BSPC,                   KC_PGDN,
  CTL_ESC, KC_A,    KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,    KC_S,     KC_MINS,  XXXXXXX,  KC_ENT,
  KC_LSFT, XXXXXXX, KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,    KC_V,     KC_Z,     SFT_ENT,  MO(_FL),          KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,          KC_SPC,KC_SPC,                        XXXXXXX,  KC_RALT,  KC_RGUI,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______, _______,          BL_STEP,
  _______, _______, _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK, KC_PAUS,  _______,  _______,  KC_DEL,                    _______,
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  MO(_FL),          KC_PGUP,
  _______, _______, _______, _______,        _______,_______,                        _______,  _______,  _______,  _______, KC_HOME, KC_PGDN, KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = LAYOUT(
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, RGB_TOG,          RGB_VAI,
  _______, _______, _______,_______,RESET,  _______,_______,QWERTY, COLEMAK,DVORAK,  _______,  _______,  _______,  _______,                   RGB_VAD,
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,
  MO(_FL), _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  MO(_FL),          RGB_SAI,
  _______, _______, _______,_______,         RGB_MOD,RGB_MOD,                        _______,  _______,  _______,  _______, RGB_HUD, RGB_SAD, RGB_HUI),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
  }
  return true;
}
