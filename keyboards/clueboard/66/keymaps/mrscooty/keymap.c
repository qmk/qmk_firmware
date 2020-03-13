#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  KC_GESC,	KC_1,	KC_2,	KC_3,   KC_4,   KC_5,   KC_6,   KC_7,	KC_8,	KC_9,		KC_0,		KC_MINS,	KC_EQL,		KC_GRV,		KC_BSPC,	KC_HOME,
  KC_TAB,	KC_Q,	KC_W,	KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,		KC_P,		KC_LBRC,	KC_RBRC,	KC_BSLS,				KC_END,
  MO(_FL), 	KC_A,	KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   	KC_SCLN,	KC_QUOT,  	KC_NUHS,  	KC_ENT,
  KC_LSFT, 	KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,	KC_DOT, 	KC_SLSH,  	KC_RO,   	KC_RSFT,          		KC_UP,
  KC_LCTL, 	KC_LGUI,KC_LALT,KC_MHEN,        KC_SPC, KC_SPC,                 			KC_HENK,	KC_RALT, 	MO(_FL),  	KC_RCTL, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  KC_GRV,	 KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______, KC_DEL,           KC_PGUP,
  _______, RGB_TOG, KC_MPRV, KC_MPLY, KC_MNXT,_______,_______,KC_HOME,KC_UP,  KC_END,   _______,  _______,  _______,  KC_PSCR,                	 KC_PGDN,
  _______, RGB_VAI, KC_MUTE, KC_VOLD, KC_VOLU,_______,_______,KC_LEFT,KC_DOWN,KC_RIGHT, _______,  _______,  _______,  _______,
  _______, RGB_VAD, _______, _______, _______,_______,_______,_______,_______,_______,  _______,  _______,  _______,  _______,          RGB_SAI,
  _______, _______, _______, _______,         RGB_MOD, RGB_MOD,                          _______,  _______,  _______,  _______, RGB_HUD, RGB_SAD, RGB_HUI)
};

  /* Keymap _CL: Control layer
   
[_CL] = LAYOUT(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI,
  _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_HUI),
};*/
