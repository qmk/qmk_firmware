#include QMK_KEYBOARD_H
#include "hvp.c"

#define _QW 0
#define _L1 1
#define _L2 2
#define _L3 3
#define _L4 4

#define LT4_TAB LT(_L4, KC_TAB)
#define LT3_ESC LT(_L3, KC_ESC)

enum custom_keycodes {
  QW = SAFE_RANGE,
  L1,
  L2,
  L3,
  L4
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT_arrow( /* Qwerty */
    LT4_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT3_ESC, KC_A,    KC_S,    KC_D,    LT(3,KC_F),    LT(4,KC_G),    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD1), TD(TD2),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD3), SC_SENT,
    KC_LCTL, KC_LGUI, KC_LALT, LT(_L2,KC_ENT),  LT(_L1,KC_SPC), KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
  ),
  [_L1] = LAYOUT_arrow( /* LAYER 1 */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DELETE, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
    _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),
  [_L2] = LAYOUT_arrow( /* LAYER 2 */
    KC_TILDE,  KC_EXCLAIM,  KC_AT,  KC_HASH,  KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_BSPC,
    KC_DELETE, _______, _______, _______, _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
    _______, _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_PGUP,  _______,
    _______, _______, _______,      _______,      _______, _______, KC_HOME, KC_PGDN, KC_END
  ),
  [_L3] = LAYOUT_arrow( /* LAYER 3 */
    KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    _______, _______, _______, D_NAVI, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, KC_PSCR,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
    _______, _______,  KC_MUTE,     KC_MPLY,      KC_MSTP, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  [_L4] = LAYOUT_arrow( /* LAYER 4 */
    _______,  RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, KC_7, KC_8, KC_9, KC_0, _______,
    _______, RGB_M_P, RGB_HUD, RGB_HUI, _______, _______, _______, KC_4, KC_5, KC_6, _______, _______,
    KC_PSCR, _______, RGB_SAD, RGB_SAI, _______, _______, KC_0, KC_1, KC_2, KC_3, _______, _______,
    QK_BOOT, _______, RGB_VAD, RGB_VAI, _______,     _______,    _______, _______, _______
  )
};