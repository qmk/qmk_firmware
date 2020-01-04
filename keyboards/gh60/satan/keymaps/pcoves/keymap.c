#include QMK_KEYBOARD_H

#include "pcoves.h"
#include "tapDance.h"

#define RUT RAINBOW_UNICORN_TOGGLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_60_ansi(
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC, \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS, \
    TD(CTRL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,  \
    KC_LSPO,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSPC, \
    KC_LCTL,  KC_LGUI, KC_LALT,                            LT(1, KC_SPC),                      KC_RALT, KC_RGUI, AUTRUCHE, KC_RCTL
  ),

  [1] = LAYOUT_60_ansi(
    RUT    , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL,  \
    _______, SECRET0, SECRET1, SECRET2, SECRET3, SECRET4, _______, _______, _______, _______, _______, _______, _______, RESET,   \
    _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,          EEP_RST, \
    _______,          _______, _______, _______, _______, EMOTE0,  EMOTE1,  EMOTE2,  EMOTE3,  KC_PDOT, _______,          _______, \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  )
};
