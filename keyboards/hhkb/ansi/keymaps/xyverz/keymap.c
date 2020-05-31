/*
Xyverz's HHKB layout

Rev 0.1, initial commit.

This is my initial keymap for the HHKB with Hasu's alternate controller.
The default layer is Dvorak, with Qwerty and Colemak being optional.
Will probably add to it later, but for now I'm going to enjoy this as it is.
*/

#include QMK_KEYBOARD_H

enum layer_names {
    _QW,
    _DV,
    _CM,
    _FL,
};

enum planck_keycodes { DVORAK = SAFE_RANGE, QWERTY, COLEMAK };

#define FN_TAB  LT(_FL, KC_TAB) 

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*
   *  _QW: Qwerty Layer
   * ,-----------------------------------------------------------.
   * |ESC | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \ |Del|
   * |-----------------------------------------------------------|
   * |Fn/Tb|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|BkSpc|
   * |-----------------------------------------------------------|
   * |Control|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return|
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift |Fn|
   * |-----------------------------------------------------------|
   * |        |Alt |Gui |      Space        |Gui |Alt |          |
   * `-----------------------------------------------------------'
   */
  /* Layer 0: Qwerty */
  [_QW] = LAYOUT(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL ,
    FN_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT ,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(_FL),
             KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT
  ),

  /*
   *  _DV: Dvorak Layer
   * ,-----------------------------------------------------------.
   * |ESC | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]| \ |Del|
   * |-----------------------------------------------------------|
   * |Fn/Tb|  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|BkSpc|
   * |-----------------------------------------------------------|
   * |Control|  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -| Return|
   * |-----------------------------------------------------------|
   * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z| Shift |Fn|
   * |-----------------------------------------------------------|
   * |        |Alt |Gui |      Space        |Gui |Alt |          |
   * `-----------------------------------------------------------'
   */
  /* Layer 1: Dvorak */
  [_DV] = LAYOUT(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL ,
    FN_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSPC,
    KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          KC_ENT,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             KC_RSFT, MO(_FL),
             KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT
  ),

  /*
   *  _CM: Colemak Layer
   * ,-----------------------------------------------------------.
   * |ESC | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \ |Del|
   * |-----------------------------------------------------------|
   * |Fn/Tb|  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|BkSpc|
   * |-----------------------------------------------------------|
   * |Control|  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '| Return|
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /| Shift |Fn|
   * |-----------------------------------------------------------|
   * |        |Alt |Gui |      Space        |Gui |Alt |          |
   * `-----------------------------------------------------------'
   */
  /* Layer 2: Colemak */
  [_CM] = LAYOUT(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL ,
    FN_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(_FL),
             KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT
  ),

  /*
   *  _FL: Function Layer
   * ,-----------------------------------------------------------.
   * |Grv |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |RST|
   * |-----------------------------------------------------------|
   * |     |   |_QW|_DV|_CM|   |   |PgU| Up|PgD|PSc|SLk|Pau|     |
   * |-----------------------------------------------------------|
   * |       |   |MPr|MPl|MNx|   |Hom| Lt| Dn| Rt|   |   |       |
   * |-----------------------------------------------------------|
   * |CAPS    |   |Mut|VlD|VlU|   |End|   |   |   |   |       |  |
   * |-----------------------------------------------------------|
   * |        |    |    |        Ins        |    |    |          |
   * `-----------------------------------------------------------'
   */
  /* Layer 3: Functions */
  [_FL] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, RESET  ,
    _______, _______, QWERTY,  DVORAK,  COLEMAK, _______, _______, KC_PGUP, KC_UP,   KC_PGDN, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    KC_CAPS, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_END,  _______, _______, _______, _______,          _______, _______,
             _______, _______,                   _______,                                     _______, _______
  ),

};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DVORAK:
                set_single_persistent_default_layer(_DV);
                return false;
            case QWERTY:
                set_single_persistent_default_layer(_QW);
                return false;
            case COLEMAK:
                set_single_persistent_default_layer(_CM);
                return false;
        }
    }
    return true;
}