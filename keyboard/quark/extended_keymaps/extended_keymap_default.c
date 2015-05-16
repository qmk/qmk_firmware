#include "extended_keymap_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC},
  {     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_NO, KC_ENT},
  {KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_RSFT},
  { KC_LCTL, KC_LALT, KC_LGUI, KC_NO, FUNC(2),    KC_SPC,  KC_NO, KC_NO,  FUNC(1),   KC_LEFT, KC_DOWN, KC_RGHT}
},
[1] = { 
  {KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL},
  {   KC_TAB,  KC_A, KC_S,S(KC_BSLS), S(KC_COMM),S(KC_DOT),S(KC_MINS),S(KC_GRV),S(KC_LBRC), S(KC_RBRC), KC_NO, KC_ENT},
  {KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SCLN,  S(KC_SCLN),    KC_HOME, KC_PGUP,   KC_RSFT},
  { KC_LCTL, KC_LALT, KC_LGUI, KC_NO, FUNC(2),    KC_SPC,  KC_NO, KC_NO,  FUNC(1),   KC_SCLN, KC_QUOT, KC_SLSH}
},
[2] = { 
  {KC_ESC, S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0), KC_BSPC},
  {     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_BSLS,  KC_SLSH,  KC_MINS,   KC_EQL,    KC_LBRC, KC_RBRC, KC_NO, KC_ENT},
  {KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    S(KC_7),    S(KC_EQL),    KC_COMM, KC_UP,   KC_RSFT},
  { KC_LCTL, KC_LALT, KC_LGUI, KC_NO, FUNC(2),    KC_SPC,  KC_NO, KC_NO,  FUNC(1),   KC_LEFT, KC_DOWN, KC_RGHT}
}
};


const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
    switch(id) {
      case 0:
        return MACRO_NONE;
      break;
    } 
    return MACRO_NONE;
};
