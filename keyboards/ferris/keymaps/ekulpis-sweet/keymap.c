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
      KC_ESC, UK_LBRC, UK_LCBR, UK_LPRN, TILDA,      UK_CIRC, UK_RPRN, UK_RCBR, UK_RBRC, UK_BSLS,
      UK_MINS, UK_ASTR, UK_EQL, UK_UNDS, UK_DLR,     MYHASH, CMD, SHFT, ALT, CTRL,
      UK_PLUS, PIPE, ATAT, UK_SLSH, UK_PERC,         KASHISH, KC_NUHS, UK_AMPR, UK_QUES, UK_EXLM,
                                KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT_split_3x5_2(
      KC_TAB, KC_NO, TAB_L, TAB_R, KC_VOLU,          KC_NO, KC_HOME, KC_UP, KC_END,  KC_DEL,
      CTRL, ALT, SHFT, CMD, KC_VOLD,                 SCRNSHOT, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
      KC_NO, KC_NO, KC_NO, KC_MNXT, KC_MPLY,         KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_ENT,
                          KC_TRNS, KC_TRNS,          LAU, KC_TRNS
  ),

  [_FUN] = LAYOUT_split_3x5_2(
      UK_7, UK_5, UK_3, UK_1, UK_9,                   UK_8, UK_0, UK_2, UK_4, UK_6,
      CTRL, ALT, SHFT, CMD, KC_F11,                  KC_F10, CMD, SHFT, ALT, CTRL,
      KC_F7, KC_F5, KC_F3, KC_F1, KC_F9,             KC_F8, KC_F12, KC_F2, KC_F4, KC_F6,
                     KC_TRNS,   KC_TRNS,             KC_SPC, KC_TRNS
  ),

};

enum combo_events {
   LDESK_COMBO, // F+S MacOS switch desktop to left  
   RDESK_COMBO, // P+T MacOS switch desktop to right
   MCTRL_COMBO, // G+M MacOS Mission Control   
   // Other combos...
   COMBO_LENGTH
 };


 
 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos


 // braces - vertical combos
 const uint16_t PROGMEM ldesk_combo[] = {UK_P, UK_T, COMBO_END};
 const uint16_t PROGMEM rdesk_combo[] = {UK_L, UK_N, COMBO_END};
 const uint16_t PROGMEM mctrl_combo[] = {UK_G, UK_M, COMBO_END};


 // system keys on combos

 combo_t key_combos[] = {
   [LDESK_COMBO] = COMBO(ldesk_combo, C(KC_LEFT)),
   [RDESK_COMBO] = COMBO(rdesk_combo, C(KC_RIGHT)),
   [MCTRL_COMBO] = COMBO(mctrl_combo, C(KC_UP)),

 };

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FUN);
}
