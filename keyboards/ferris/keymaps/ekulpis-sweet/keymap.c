#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "keymap_uk.h"

enum layers {
  _CDH,
  _SYM,
  _NAV,
  _FUN,
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak Mod-DH layout
  [_CDH] = LAYOUT_split_3x5_2(
      UK_Q, UK_W, UK_F, UK_P, UK_B,                   UK_J, UK_L, UK_U,    UK_Y,   UK_QUOT,
      UK_A, UK_R, UK_S, UK_T, UK_G,                   UK_M, UK_N, UK_E,    UK_I,   UK_O,
      UK_Z, UK_X, UK_C, UK_D, UK_V,                   UK_K, UK_H, UK_COMM, UK_DOT, UK_SCLN,
                         NAV, SHFT,                   KC_SPC, SYM
  ),


  [_SYM] = LAYOUT_split_3x5_2(
      KC_ESC, UK_LBRC, UK_LCBR, UK_LPRN, UK_TILD,    UK_CIRC, UK_RPRN, UK_RCBR, UK_RBRC, UK_GRV,
      UK_MINS, UK_ASTR, UK_EQL, UK_UNDS, UK_DLR,     UK_HASH, CMD, ALT, CTRL, SHFT,
      UK_PLUS,  UK_BRKP, UK_AT, UK_SLSH, UK_PERC,    KC_NO, UK_BSLS, UK_AMPR, UK_QUES, UK_EXLM,
                                KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT_split_3x5_2(
      KC_TAB, KC_NO, TAB_L, TAB_R, KC_VOLU,          KC_NO, KC_HOME, KC_UP, KC_END,  KC_DEL,
      SHFT, CTRL, ALT, CMD, KC_VOLD,                 KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
      KC_NO, KC_NO, KC_NO, KC_MNXT, KC_MPLY,         KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_ENT,
                          KC_TRNS, KC_TRNS,          LAU, KC_TRNS
  ),

  [_FUN] = LAYOUT_split_3x5_2(
      UK_7, UK_5, UK_3, UK_1, UK_9,                   UK_8, UK_0, UK_2, UK_4, UK_6,
      SHFT, CTRL, ALT, CMD, KC_F11,                  KC_F10, CMD, ALT, CTRL, SHFT,
      KC_F7, KC_F5, KC_F3, KC_F1, KC_F9,             KC_F8, KC_F12, KC_F2, KC_F4, KC_F6,
                     KC_TRNS,   KC_TRNS,             KC_SPC, KC_TRNS
  ),

};

enum combo_events {
   // punctuation combos
   MINS_COMBO, // C+D   -
   USCR_COMBO, // H+,,  _
   SCLN_COMBO, // .+/   ;
   // braces
   LCBR_COMBO, // F+S   {
   LPRN_COMBO, // P+T    (
   LBRC_COMBO, // B+G    [
   RCBR_COMBO, // U+E    }
   RPRN_COMBO, // L+N    )
   RBRC_COMBO, // J+M    ]
   PIPE_COMBO, // C+X    |
   TILDE_COMBO, // ,+.   ~
   // Other combos...
   COMBO_LENGTH
 };


 
 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos
 const uint16_t PROGMEM mins_combo[] = {UK_C, UK_D, COMBO_END};
 const uint16_t PROGMEM uscr_combo[] = {UK_H, UK_COMM, COMBO_END};
 const uint16_t PROGMEM scln_combo[] = {UK_DOT, UK_SLSH, COMBO_END};
 const uint16_t PROGMEM pipe_combo[] = {UK_X, UK_C, COMBO_END};
 const uint16_t PROGMEM tilde_combo[] = {UK_DOT, UK_COMM, COMBO_END};


 // braces - vertical combos
 const uint16_t PROGMEM lcbr_combo[] = {UK_F, UK_S, COMBO_END};
 const uint16_t PROGMEM lprn_combo[] = {UK_P, UK_T, COMBO_END};
 const uint16_t PROGMEM lbrc_combo[] = {UK_B, UK_G, COMBO_END};
 const uint16_t PROGMEM rbrc_combo[] = {UK_J, UK_M, COMBO_END};
 const uint16_t PROGMEM rprn_combo[] = {UK_L, UK_N, COMBO_END};
 const uint16_t PROGMEM rcbr_combo[] = {UK_U, UK_E, COMBO_END};

 // system keys on combos

 combo_t key_combos[] = {
   [MINS_COMBO] = COMBO(mins_combo, UK_MINS),
   [USCR_COMBO] = COMBO(uscr_combo, LSFT(UK_MINS)),
   [SCLN_COMBO] = COMBO(scln_combo, UK_SCLN),
   [LCBR_COMBO] = COMBO(lcbr_combo, UK_LCBR),
   [LPRN_COMBO] = COMBO(lprn_combo, UK_LPRN),
   [LBRC_COMBO] = COMBO(lbrc_combo, UK_LBRC),
   [RCBR_COMBO] = COMBO(rcbr_combo, UK_RCBR),
   [RPRN_COMBO] = COMBO(rprn_combo, UK_RPRN),
   [RBRC_COMBO] = COMBO(rbrc_combo, UK_RBRC),
   [PIPE_COMBO] = COMBO(pipe_combo, UK_BRKP),
   [TILDE_COMBO] = COMBO(tilde_combo, UK_TILD),
 };

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FUN);
}
