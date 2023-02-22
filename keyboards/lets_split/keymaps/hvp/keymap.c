#include QMK_KEYBOARD_H
#include "hvp.c"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _NAVI 5 
#define _ADJUST 6

enum custom_keycodes {
  QWERTY = SAFE_RANGE
};


#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define LT3_ESC LT(5, KC_ESC)
#define LT4_TAB LT(6, KC_TAB)
#define F_NAVI LT(5, KC_F)




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12(
   LT4_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, 
   LT3_ESC,  KC_A,    KC_S,    KC_D,    F_NAVI,    LT(6,KC_G),    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD1), TD(TD2),
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD3), SC_SENT , 
   KC_LCTL,  KC_APP, KC_LGUI, KC_LALT, LT(3,KC_SPC),   SFT_T(KC_SPC),  SC_SENT, LT(4,KC_SPC),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  
),

[_RAISE] = LAYOUT_ortho_4x12( /* Right */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
  KC_DEL, _______, _______, _______, _______, _______,                    _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______,                   _______, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_PIPE, 
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

[_LOWER] = LAYOUT_ortho_4x12( /* Left */
  KC_TILDE,  KC_EXCLAIM,  KC_AT,  KC_HASH,  KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_BSPC,
  KC_DEL, _______, _______, _______, _______, _______,                      _______, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
  _______, _______, _______, _______, _______, _______,                     _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TILD, 
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

[_NAVI] =  LAYOUT_ortho_4x12( /* Esc */
  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  _______, _______, _______, D_NAVI, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
  _______, _______, _______, _______, _______,KC_MUTE, KC_MPLY, KC_MSTP, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

[_ADJUST] =  LAYOUT_ortho_4x12( /* Tab */
  _______,  RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, KC_7, KC_8, KC_9, KC_0, _______,
  _______, RGB_M_P, RGB_HUD, RGB_HUI, _______, _______, _______, KC_4, KC_5, KC_6, _______, _______,
  KC_PSCR, _______, RGB_SAD, RGB_SAI, _______, _______, KC_0, KC_1, KC_2, KC_3, _______, _______,
  QK_BOOT, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______
)};
