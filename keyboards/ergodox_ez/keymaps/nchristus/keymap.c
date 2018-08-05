// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0: Base layer */
  [BASE] = LAYOUT_ergodox(
    // left hand
    KC_ESC,   KC_1,     KC_2,    KC_3,    KC_4,     KC_5,     _______,
    KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,     KC_T,     _______,
    KC_LCTL,  KC_A,     KC_S,    KC_D,    KC_F,     KC_G,
    KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,     _______,
    KC_TAB,   KC_LGUI,  _______, KC_LALT, KC_LCTL,
                                                    _______,  _______,
                                                              _______,
                                          KC_LGUI,  KC_ENT,   _______,

    // right hand
    _______,  KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,
    KC_LBRC,  KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_BSLS,
              KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,
    KC_RBRC,  KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,
                        KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT,  _______,
    _______,  _______,
    _______,
    _______,  KC_BSPC,  KC_SPC
  )
};
