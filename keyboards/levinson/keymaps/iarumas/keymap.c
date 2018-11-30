#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "neo2-keys-on-quertz-de-latin1.h"
#include "neo2-basic-layout.h"

enum my_keycodes{
  N2_LETS = 0,
  /* L02 */
  N2_SYMB,
  N2_CTRL,
  /*  L05 -> N2_GREEK */
  /*  L06 -> N2_MATH */
  N2_FUN,
  //
  QUERTZ
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
[N2_LETS] = LAYOUT_ortho_4x12( 
  KC_ESC,     KC_X,    KC_V,    KC_L,    KC_C,    KC_W,   KC_K,    KC_H,    KC_G,    KC_F,    KC_Q,    KC_ENTER,
  MO(N2_SYMB),    KC_U,    KC_I,    KC_A,    KC_E,    KC_O,   KC_S,    KC_N,    KC_R,    KC_T,    KC_D,    MO(N2_SYMB),
  KC_LSHIFT,  N_UE,    N_OE,    N_AE,    KC_P,    N_Z,    KC_B,    KC_M,    KC_COMM, KC_DOT,  KC_J,    KC_RSFT,
  KC_LCTRL,   KC_LGUI, KC_LALT, MO(N2_FUN), MO(N2_CTRL), KC_SPC, KC_SPC,  MO(N2_CTRL), MO(N2_FUN), KC_RALT, KC_LGUI, KC_RCTRL
),


[N2_SYMB] = LAYOUT_ortho_4x12( 
   _______,  N_DOTS,  N_USC,   N_LSQBR, N_RSQBR, N_CIRC,  N_EXKL,  N_LT,    N_GT,    N_EQ,    N_AMP,  _______,
   _______,  N_BSLS,  N_SLSH,  N_LCUBR, N_MINS, N_COLN,   N_QUES,  N_LPARN, N_RPARN, N_MINS,  N_AT,   _______,
   _______,  N_HASH,  N_DLR,   N_PIPE,  N_TILD,  N_GRAVE, N_PLUS,  N_PERC,  N_QUOT,  N_SING,  N_SEMI, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


[N2_CTRL] = LAYOUT_ortho_4x12( 
   _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,   KC_PGDN, KC_KP_SLASH,    KC_KP_7, KC_KP_8, KC_KP_9,  KC_KP_MINUS,     _______,
   _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_KP_ASTERISK, KC_KP_4, KC_KP_5, KC_KP_6,  KC_KP_PLUS,      _______,
   _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER, N_UNDO,  KC_KP_ENTER,    KC_KP_1, KC_KP_2, KC_KP_3,  KC_KP_DOT,       _______,
   _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______,  _______,         _______

),

[N2_FUN] = LAYOUT_ortho_4x12( 
   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_MAIL, KC_MSEL, KC_MY_COMPUTER, KC_CALCULATOR, N_PASTE, _______,
   _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_MPRV, KC_MPLY, KC_MNXT,        KC_MSTP,       N_COPY,  _______,
   _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_PSCR, KC_SLCK, KC_PAUS,        KC_NLCK,       N_CUT,   _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______,      _______, _______
),

[QUERTZ] = LAYOUT_ortho_4x12(
   _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
   _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    N_OE,    _______,
   _______, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  N_MINS,  _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};
