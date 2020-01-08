
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "rgblight.h"
#include "tominabox1.h"
#include "mini.h"

#define xxx KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_space_base(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    TD(TD_Q_ESC),TD(TD_WTAB),     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,  TD(TD_QCOL), //Y+QUOTE = KC_BSPC
    TD(TD_CTRL_A),     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I, KC_O,
    LSFT_T(KC_Z),     KC_X,  KC_C,     KC_V,     KC_B,  KC_K, KC_M,  KC_COMM,  KC_DOT, TD(TD_QUES_ENT),
                       KC_LALT, KC_LGUI, LT(_RAISE, KC_SPC), MO(_LOWER)
  ),
  [_RAISE] = LAYOUT_split_space_base(
  KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0, //0 + 9 = KC_BSPC
  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_EQL,  KC_MINS,
  KC_DEL ,  KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,  KC_UNDS,  KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_DOT ,
                         KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS

),

[_LOWER] = LAYOUT_split_space_base(
  KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
      RESET,   RGBRST,  AG_NORM,  AG_SWAP,  DEBUG,  XXXXXXX,KC_PGDN,    KC_UP,  KC_PGUP,    XXXXXXX,
     RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  SPONGEBOB,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
     RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  AESTHETIC,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_BSLS,
     KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS
),
};
