/*
 * Keyboard: Atreus
 * Keymap:   replicaJunction
 * Version:  2.1
 */

#include QMK_KEYBOARD_H
#include "replicaJunction.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[L_COLEMAK] = LAYOUT(
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  KC_A,    KC_R_LT, KC_S_LT, KC_T,    KC_G,                      KC_M,    KC_N,    KC_E_LT, KC_I_LT, KC_O,
  KX_Z_MT, KX_X_MT, KX_C_MT, KX_D_MT, KC_V,                      KC_K,    KX_H_MT, KX_COMT, KX_DOMT, KX_SLMT,
  TD_LAYR, KC_LGUI, KC_TAB,  KC_LSFT, KX_BKNM, KX_DCTL, KX_NALT, KX_SPAC, KC_RSFT, KC_MINS, KC_QUOT, KC_EQL
)
,

[L_NUM] = LAYOUT(
  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_SLSH,                   KC_COLN, KC_7,    KC_8,    KC_9,    KC_SLSH,
  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_PIPE,                   KC_HASH, KC_4,    KC_5,    KC_6,    KC_ASTR,
  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLS,                   KC_BSPC, KC_1,    KC_2,    KC_3,    KC_MINS,
  _______, KC_AMPR, KC_TILD, KC_GRV,  ooooooo, _______, KC_ENT,  MO_FUNC, KC_0,    KC_DOT,  KC_EQL,  KC_PLUS
)
,

[L_EXTEND] = LAYOUT(
  _______, _______, _______, KC_APP,  KX_CGR,                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,
  KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, _______,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
  _______, _______, _______, KX_SRCH, KX_PAST,                    _______, KX_STAB, KC_TAB,  _______, KC_INS,
  _______, _______, _______, _______, MO_FUNC,  KC_DEL,  KC_ENT,  _______, _______, _______, _______, KC_PSCR
)
,

[L_FUNC] = LAYOUT(
  _______, _______, M_LCLIK, M_RCLIK, M_MCLIK,                   KC_VOLU, KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, M_WHLUP,                   KC_MUTE, KC_F5,   KC_F6,   KC_F7,   KC_F8,
  M_LEFT,  M_DOWN,  M_UP,    M_RIGHT, M_WHLDN,                   KC_VOLD, KC_F1,   KC_F2,   KC_F3,   KC_F4,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
,

[L_LL_R] = LAYOUT(
  _______, _______, _______, _______, _______,                   KC_COLN, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
  _______, ooooooo, KC_AMPR, KC_PIPE, _______,                   KC_HASH, KC_P4,   KC_P5,   KC_P6,   KC_PAST,
  _______, _______, _______, _______, _______,                   KC_BSPC, KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  KC_EQL,  KC_PLUS
)
,

[L_LL_E] = LAYOUT(
  RJ_MAKE, RJ_EQ,   RJ_LEQ,  RJ_GEQ,  RJ_GEQR,                   _______, _______, _______, _______, _______,
  _______, _______, RJ_SELS, RJ_DUND, _______,                   _______, _______, ooooooo, _______, _______,
  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
,

[L_LL_I] = LAYOUT(
  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_SLSH,                   _______, KC_UNDS, KC_GRV,  _______, _______,
  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_PIPE,                   _______, KC_MINS, KC_QUOT, ooooooo,  _______,
  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLS,                   _______, KC_TILD, KC_DQT,  _______, _______,
  _______, KC_AMPR, KC_LABK, KC_RABK, _______, _______, _______, _______, _______, _______, _______, _______
)

};

// Uncomment any of these to add keyboard-specific code. Otherwise, they
// will use user defaults defined in the replicaJunction.h header file.

// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }

// void matrix_init_keymap(void) {};

// void matrix_scan_keymap(void) {};
