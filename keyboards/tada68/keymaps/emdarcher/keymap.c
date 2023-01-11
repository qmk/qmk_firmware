#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1
#define _CL 2
#define _ML 3

#define KC_X0   LT(_CL, KC_CAPS)

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
   * |Ctrl|Alt |Win |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  QK_GESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL,
  KC_X0,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN,
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                        KC_RALT,MO(_FL),KC_RCTL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer for FN key
   */
[_FL] = LAYOUT_ansi(
  KC_GRV,  KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS ,
  _______,_______,_______,_______,_______, _______,_______,_______,_______,_______,KC_PSCR,KC_SCRL,KC_PAUS, _______,KC_HOME,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MRWD,KC_MFFD,        _______, KC_END,
  _______,        _______,BL_BRTG,BL_DOWN,BL_TOGG,BL_UP,  KC_MPLY,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______, _______, _______,
  _______,_______,_______,                 _______,               _______,_______,_______,_______,_______, _______),

 /* Keymap _CL: Function Layer for Caps Lock key
  * uses VIM like control with hjkl for arrow keys
  */

[_CL] = LAYOUT_ansi(
  KC_GRV,  KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS ,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL,KC_PAUS, _______,KC_HOME,
  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,_______,_______,         _______, KC_END,
  _______,        _______,_______,_______,_______,_______,KC_MPLY,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______, _______, _______,
  _______,_______,_______,                 _______,               _______,_______,_______,_______,_______, _______),

 /* Keymap _ML: The Mouse control layer, activated by using both _FL and _CL layers
  * Activates mouse control. Keeps lower layer's control
  */
[_ML] = LAYOUT_ansi(
  KC_ESC ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_WH_R, KC_WH_L,KC_WH_U,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______, KC_WH_D,
  _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BTN1, KC_MS_U, KC_BTN2,
  _______,_______,_______,                 _______,               _______,_______,_______,KC_MS_L,KC_MS_D, KC_MS_R),

};


//layer state control
layer_state_t layer_state_set_user(layer_state_t state){
    //switch to _ML if both _FL and _CL are activated
    return update_tri_layer_state(state, _FL, _CL, _ML);
}
