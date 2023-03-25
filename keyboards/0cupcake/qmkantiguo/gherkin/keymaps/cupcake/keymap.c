#include QMK_KEYBOARD_H

/*
#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_C       LT(3, KC_C)
#define FN4_V       LT(4, KC_V)
#define FN5_B       LT(5, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(1,KC_QUOT),
    CTL_T(KC_Z),  ALT_T(KC_X),   KC_C,  KC_V,    LSFT_T(KC_SPC), LSFT_T(KC_BSPC),  KC_B,    KC_N,    KC_M,   LT(2,KC_DOT)
  ),
  
  [1] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                  KC_7,    KC_8,    KC_9,    KC_0,
    _______, _______, _______, _______, _______, _______,               _______, KC_MINS, KC_EQL, _______,
    KC_LCTL, KC_LALT, C(KC_Z), _______, LSFT_T(KC_ENT), LSFT_T(KC_DEL), _______, KC_SLSH, _______, KC_COMM
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_ESC, KC_F1,   KC_F2,  KC_F3,   KC_F4,  KC_F5,   KC_F6,  KC_LBRC, KC_RBRC,  KC_BSLS,
    KC_TAB, KC_F7,   KC_F8,  KC_F9,   KC_F10, KC_F11,  KC_F12, _______, _______,  KC_SCLN,
    KC_LCTL, KC_LALT, _______, _______, LSFT_T(KC_SPC), LSFT_T(KC_DEL),  _______, _______, MO(3), _______
  ),

  [3] = LAYOUT_ortho_3x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_GRV, _______ ,  _______, _______, _______, _______, _______, _______,KC_F11,KC_F12 ,
    RESET, _______, _______, _______, KC_DEL,KC_DEL, _______, _______, _______, _______
  ),
};

/*
  [3] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TAB,  _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
    _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
  ),

  [4] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_TAB,  _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
    _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),
  */