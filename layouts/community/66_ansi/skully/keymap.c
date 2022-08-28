#include QMK_KEYBOARD_H

// Layer names
#define _BL 0
#define _FL 1
#define _CL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT_66_ansi(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,            KC_PGUP,
  KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_PGDN,
  KC_LCTL,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
  MO(_FL),           KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,         KC_UP,
  KC_LCTL,  KC_LALT,  KC_LGUI,  KC_SPC,                                           KC_RGUI,  KC_RALT,KC_RCTL,  KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT_66_ansi(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL,             BL_STEP,
  S(KC_TAB),  S(KC_Q),S(KC_W),S(KC_E),S(KC_R),S(KC_T),S(KC_Y),S(KC_U),S(KC_I),S(KC_O),S(KC_P),S(KC_LBRC),S(KC_RBRC),S(KC_BSLS),S(KC_PGDN),
  S(KC_LCTL),   S(KC_A),MO(_CL),S(KC_D),S(KC_F),S(KC_G),S(KC_H),S(KC_J),S(KC_K),S(KC_L),S(KC_SCLN),S(KC_QUOT),S(KC_ENT),
  MO(_FL),           S(KC_Z),S(KC_X),S(KC_C),S(KC_V),S(KC_B),S(KC_N),S(KC_M),S(KC_COMM),S(KC_DOT),S(KC_SLSH),KC_RSFT, KC_PGUP,
  KC_LCTL,  KC_LALT,  KC_LGUI,  S(KC_SPC),                                        KC_RGUI,  KC_RALT,KC_RCTL,  KC_HOME,KC_PGDN,KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = LAYOUT_66_ansi(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RGB_TOG,            RGB_VAI,
  CK_TOGG,    _______,_______,_______,QK_BOOT,  _______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_VAD,
  _______,      _______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  MO(_FL),           _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,         RGB_SAI,
  _______,  _______,  _______,  RGB_MOD,                                          _______,  _______,_______,  RGB_HUD,RGB_SAD,RGB_HUI),
};
