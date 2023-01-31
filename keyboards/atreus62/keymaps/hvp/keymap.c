
#include QMK_KEYBOARD_H
#include "hvp.c"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define LT3_ESC LT(3, KC_ESC)
#define LT4_TAB LT(4, KC_TAB)
#define LT1_ENT LT(1, KC_ENTER)
#define LT2_BSP LT(2, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( /* qwerty */
    KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC ,
    LT4_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC ,
    LT3_ESC,   KC_A,    KC_S,    KC_D,    LT(3,KC_F),    LT(4,KC_G),                        KC_H,    KC_J,    KC_K,    KC_L,    TD(TD1), TD(TD2) ,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD3), KC_SFTENT ,
    KC_LCTL,  KC_APP, _______, KC_LGUI,  KC_LALT,SFT_T(KC_SPC), LT2_BSP,   LT1_ENT,   SFT_T(KC_SPC),  KC_LSFT,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
  ),

  LAYOUT( /* Right */
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS ,
    KC_DEL,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC ,
    KC_DEL,  _______, _______, _______, _______, KC_LEFT_PAREN,                KC_RIGHT_PAREN,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, KC_LBRC,                     KC_RBRC, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_PIPE, 
    _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  LAYOUT(/* Left */
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS ,
    KC_TILDE,  KC_EXCLAIM,  KC_AT,  KC_HASH,  KC_DOLLAR, KC_PERCENT,      KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_BSPC,
    KC_DELETE, _______, _______, _______, _______, KC_LEFT_PAREN, KC_RIGHT_PAREN,            KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
    _______  , _______  , _______  , _______  , _______  , KC_LEFT_CURLY_BRACE  ,                     KC_RIGHT_CURLY_BRACE  ,KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TILD,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,  _______  ,  _______  , _______  , KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),


  LAYOUT(/* Esc */
    KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                     KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                     KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC_NO,  KC_NO, KC_NO, D_NAVI, KC_NO, KC_NO,                     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO ,
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO ,
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MSTP,  KC_MPLY,  KC_NO, KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),


  
  LAYOUT(/* Tab */
    _______,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______ ,
    _______,  _______, _______, _______, _______, _______,                     _______, KC_4, KC_5, KC_6, _______, _______ ,
    _______,  _______, _______, _______, _______, _______,                     KC_0, KC_1, KC_2, KC_3, _______, _______ ,
    KC_PSCR,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______ ,
    QK_BOOT,  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______
  ),
  /*
  [_TRNS] = LAYOUT(
    _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______ ,
    _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______ ,
    _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______ ,
    _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______ ,
    _______,  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______
  ),
  */
};
