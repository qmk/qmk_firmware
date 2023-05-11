#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL  0
#define _HLa 1
#define _HLb 2
#define _HL  3
#define _XL  4

enum hype_keycodes {
  FN_HLa = SAFE_RANGE,
  FN_HLb
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_HOME,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_PGUP,
  KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGDN,
  SC_LSPO,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   SC_RSPC,KC_UP,LT(_HLa, KC_END),
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                        KC_RALT,FN_HLa,FN_HLb, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _HL: Hype Fn Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|   |   |   |   |   |   |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
[_HLa] = LAYOUT_ansi(
   KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,          KC_DEL,KC_INS,
     KC_CAPS,_______,  KC_UP,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL,KC_PAUS,  KC_UP,_______,     _______,_______,
      _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,_______,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,            _______,_______,
           _______,_______,_______,_______,_______,_______,_______,_______, KC_END,KC_PGDN,KC_DOWN,       _______,KC_PGUP,_______,
    _______,  _______,  _______,                     _______,                     _______,_______,_______,KC_HOME,KC_PGDN, KC_END),

[_HLb] = LAYOUT_ansi(
   KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,          KC_DEL,KC_INS,
     KC_CAPS,_______,  KC_UP,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL,KC_PAUS,  KC_UP,_______,     _______,_______,
      _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,_______,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,            _______,_______,
           _______,_______,_______,_______,_______,_______,_______,_______, KC_END,KC_PGDN,KC_DOWN,       _______,KC_PGUP,_______,
    _______,  _______,  _______,                     _______,                     _______,_______,_______,KC_HOME,KC_PGDN, KC_END),

[_HL] = LAYOUT_ansi(
  BL_TOGG, BL_DOWN,BL_UP, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,LALT(KC_F4),MAGIC_UNSWAP_BACKSLASH_BACKSPACE,
     _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,MAGIC_SWAP_BACKSLASH_BACKSPACE,
      _______,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______,_______,_______,_______,_______,_______,_______,            _______,_______,
           _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,       _______,KC_MNXT,_______,
    KC_MPRV,  KC_MPLY,  KC_MNXT,                     KC_MPLY,                     _______,_______,_______,KC_MRWD,KC_MPRV,KC_MFFD),

[_XL] = LAYOUT_ansi(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,
     _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,_______,
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,            _______,_______,
           _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,       _______,_______,_______,
    _______,  _______,  _______,                     _______,                     _______,_______,_______,_______,_______,_______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN_HLa:
      if (record->event.pressed)
      {
        layer_on(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
    case FN_HLb:
      if (record->event.pressed)
      {
        layer_on(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
  }
  return true;
}
