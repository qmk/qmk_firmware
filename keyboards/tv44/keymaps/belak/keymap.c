#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"

// Layer names. We stick to 3 letters if possible so MO(NAME) fits in 7
// characters and doesn't mess with the grid.
#define _QW 0
#define _L1 1
#define _L2 2
#define _L3 3

// Curly braces have their own keys. These are defined so they don't mess up the
// grid in layer 2.
#define L_CURBR LSFT(KC_LBRC)
#define R_CURBR LSFT(KC_RBRC)

#define BE_ESC  LSFT_T(KC_ESC)
#define L2_SLSH LT(_L2, KC_SLSH)
#define L3_QUOT LT(_L3, KC_QUOT)
#define L3_TAB  LT(_L3, KC_TAB)

// Fillers to make layering more clear
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = KEYMAP_ARROW_COMMAND( /* Qwerty */
    L3_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    MO(_L1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L3_QUOT,
    BE_ESC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   L2_SLSH,
    KC_LCTL, MO(_L2), KC_LALT, KC_LGUI,          KC_ENT,  KC_SPC,           KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_L1] = KEYMAP_ARROW_COMMAND( /* LAYER 1 */
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, KC_BSLS, KC_QUOT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_DOWN, KC_UP,   KC_LEFT, KC_RGHT, _______,
    _______, KC_ESC,  _______, KC_PSCR, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_RSFT,
    _______, KC_LGUI, _______, _______,          _______, _______,          _______, _______, _______, _______
  ),
  [_L2] = KEYMAP_ARROW_COMMAND( /* LAYER 2 */
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_ESC,  KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, L_CURBR, R_CURBR, KC_4,    KC_5,    KC_6,    KC_VOLU, KC_ENT,
    KC_LSFT, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_VOLD, _______,
    _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______
  ),
  [_L3] = KEYMAP_ARROW_COMMAND( /* LAYER 3 */
    _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
    KC_ESC,  _______, _______, _______, _______, _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    _______, KC_LGUI, _______, _______,          _______, _______,          _______, _______, _______, _______
  )
};

const uint16_t PROGMEM fn_actions[] = {};
