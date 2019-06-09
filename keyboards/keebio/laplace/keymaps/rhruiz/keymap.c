#include QMK_KEYBOARD_H
#include "rhruiz.h"

#define KC_ KC_TRNS
#define KC__FN1 MO(_FN1)
#define KC__FN2 MO(_FN2)
#define KC__CFG MO(_CFG)

#define FN1 KC__FN1
#define FN2 KC__FN2
#define KC_RST RESET

#define KC_SPCFN1 SPCFN1
#define KC_SPCFN2 SPCFN2
#define KC_BKSFN2 BKSFN2
#define KC_CTRLESC CTRLESC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* template
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    */
  [_BL] = LAYOUT_kc(
    TAB,   Q,     W,     E,     R,     T,     Y,     U,     I,     O,     P,     LBRC,  RBRC,
    CTRLESC,  A,     S,     D,     F,     G,     H,     J,     K,     L,     SCLN,  ENT,
    LSFT,  Z,     X,     C,     V,     B,     N,     M,     COMM,  DOT,   SLSH,  RSFT,
    FN1,      LALT,  LGUI,   ,  SPCFN1,   BKSFN2,   RGUI,  RALT,  FN2,      RCTL
  ),

  [_VIM_EMACS] = LAYOUT_kc(
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,    ,   ,   ,
     ,   ,   ,   ,   ,   ,  LEFT,  DOWN,  UP,    RIGHT,   ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,    ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,
  ),

  [_MOUSE] = LAYOUT_kc(
     ,  BTN1,  MS_U,  BTN2,  ACL0,  ACL1,  ACL2,   ,   ,   ,   ,   ,   ,
     ,  MS_L,  MS_D,  MS_R,   ,   ,   ,   ,   ,   ,   ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,
  ),

  [_KEY_OVERRIDE] = LAYOUT_kc(
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,  QUOT,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,
     ,   ,   ,   ,   ,   ,   ,   ,   ,
  ),

  [_FN1] = LAYOUT_kc(
    GRV,   1,     2,     3,     4,     5,      6,     7,     8,     9,     0,     MINS,  EQL,
     ,   ,   ,   ,   ,   ,    ,   ,   ,   ,   ,  BSLS,
     ,   ,   ,   ,   ,   ,    ,   ,   ,   ,   ,   ,
     ,   ,   ,   ,   ,  _CFG,   ,   ,   ,
  ),

  [_FN2] = LAYOUT_kc(
    TILD,   EXLM,  AT,    HASH,  DLR,    PERC,  CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  UNDS,  PLUS,
     ,    ,   ,   ,   ,    ,   ,   ,   ,   ,   ,  PIPE,
     ,    ,   ,   ,   ,    ,   ,   ,   ,   ,   ,   ,
    _CFG,   ,   ,   ,  _CFG,   ,   ,   ,   ,
  ),

  [_CFG] = LAYOUT_kc(
     ,  F1,      F2,        F3,    F4,    F5,    F6,    F7,    F8,    F9,    F10,   F11,  F12,
     ,  _VOLUP,  _VOLDOWN,  MUTE,  EJCT,   ,  HOME,  PGDN,  PGUP,  END,    ,  RST,
     ,   ,     ,       ,   ,   ,   ,   ,   ,   ,   ,   ,
     ,   ,     ,       ,   ,   ,   ,   ,   ,
  )
};

void matrix_init_user(void) {
  setPinOutput(B0);
  writePinHigh(B0);

  setPinOutput(D5);
  writePinHigh(D5);
}

uint32_t layer_state_set_user(uint32_t state) {
  return rhruiz_layer_state_set_user(state);
}
