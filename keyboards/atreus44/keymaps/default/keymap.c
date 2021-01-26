// This is the default layout shipped with the Keyboardio atreus

#include QMK_KEYBOARD_H

enum {
  QWERTY,
  FUN,
  UPPER
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT_stacked
  ( /* qwerty */
      // left hand...
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRAVE,
      KC_ESC,  KC_TAB,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL,
      // right hand...
               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
      KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
      KC_LALT, KC_SPC,  MO(FUN), KC_MINS, KC_QUOT, KC_ENT
  ),


  [FUN] = LAYOUT_stacked
  ( /* Fun layer */
      // left hand...
      KC_EXLM, KC_AT,   KC_UP,   KC_DLR,  KC_PERC,
      KC_LPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_RPRN,
      KC_LBRC, KC_RBRC, KC_HASH, KC_LCBR, KC_RCBR, KC_CIRC,
    MO(UPPER), KC_INS,  KC_LGUI, KC_LSFT, KC_DEL,  KC_LCTL,
      // right hand...
               KC_PGUP, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC,
               KC_PGDN, KC_KP_4, KC_KP_5, KC_KP_6, ___,
      KC_AMPR, KC_ASTR, KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS,
      KC_LALT, KC_SPC,  ___,     KC_PDOT, KC_KP_0, KC_PEQL
   ),

  [UPPER] = LAYOUT_stacked
  ( /* Upper layer */
      // left hand...
      KC_INS,  KC_HOME, ___,     KC_END,  KC_PGUP,
      KC_DEL,  ___,     ___,     ___,     KC_PGDN,
      ___,   KC__VOLUP, ___,     ___,     ___,     ___,
      ___, KC__VOLDOWN, ___,     ___,     ___,     ___,
      // right hand...
               KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
               KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
      ___,     ___,     KC_F1,   KC_F2,   KC_F3,   KC_F12,
      ___,     ___,     ___,     KC_PSCR, KC_SLCK, KC_MPLY
   ),

};
