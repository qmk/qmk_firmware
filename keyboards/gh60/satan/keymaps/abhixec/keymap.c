#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 2
#define _CL 1
#define _EL 3


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift| Del|
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = LAYOUT_60_ansi_split_rshift(
  QK_GESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  LT(_EL, KC_BSPC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT, \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         KC_RSFT, KC_DEL, \
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RALT,KC_RGUI, MO(_FL),KC_RCTL),

/* Keymap _CL: (Colemak Layer) 
 */
[_CL] = LAYOUT_60_ansi_split_rshift(
  QK_GESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,   KC_LBRC, KC_RBRC,KC_BSLS, \
  LT(_EL, KC_BSPC), KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O,KC_QUOT,         KC_ENT, \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         KC_RSFT, KC_DEL, \
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RALT,KC_RGUI, MO(_FL),KC_RCTL),

[_EL] = LAYOUT_60_ansi_split_rshift(
  
  KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,  \
  _______,KC_LCTL,KC_WH_U,_______,_______,KC_MS_U,KC_PGUP,KC_HOME,KC_UP,KC_END,KC_DEL, QK_GESC, _______,_______, \
  _______,KC_LALT,KC_WH_D, KC_LSFT,_______,KC_MS_D,KC_PGDN,KC_LEFT,KC_DOWN,KC_RIGHT, KC_BSPC,_______,_______, \
_______,KC_UNDO,KC_CUT,KC_COPY,KC_PASTE, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,KC_MS_LEFT,KC_MS_RIGHT,_______,_______, _______, \
  _______,_______,_______,                _______,                        _______,_______,_______,_______),

 
  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * | KC_GRV|F1|F2|F3|F4|F5|F6|F7| F8 | F9  |10|F11|F12|        |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |BL-|BL+|BL   |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |       |   |HOME|   |       |
   * |-----------------------------------------------------------|
   * |        |   |  |   |   |   |V_DWN|V_UP|MUTE | END || |_CL  |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */

[_FL] = LAYOUT_60_ansi_split_rshift(
  
  KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,  \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR, BL_DEC, BL_INC,BL_TOGG, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,_______,_______, \
  _______,_______,_______,_______,_______,_______,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,KC_END,_______,_______, TG(_CL), \
  _______,_______,_______,                _______,                        _______,_______,_______,_______)
  
};

