// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// qmk compile -kb keebio/nyquist/rev3
// qmk flash -kb keebio/nyquist/rev3

#include QMK_KEYBOARD_H
#include "alysaght.h"

#define LAYOUT_nyquist_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Qwerty
[_QWERTY] = LAYOUT_nyquist_wrapper(
  _________________QWERTY_L1_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R1_________________,
  _________________QWERTY_L2_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R2_________________,
  _________________QWERTY_L3_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R3_________________,
  _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________
),

// Workman
[_WORKMAN] = LAYOUT_nyquist_wrapper(
  _________________WORKMAN_L1________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R1________________,
  _________________WORKMAN_L2________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R2________________,
  _________________WORKMAN_L3________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R3________________,
  _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________
),

// Colemak DH
[_COLEMAK] = LAYOUT_nyquist_wrapper(
  _________________COLEMAK_L1________________,   XXXXXXX, XXXXXXX,   _________________COLEMAK_R1________________,
  _________________COLEMAK_L2________________,   XXXXXXX, XXXXXXX,   _________________COLEMAK_R2________________,
  _________________COLEMAK_L3________________,   XXXXXXX, XXXXXXX,   _________________COLEMAK_R3________________,
  _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________
),

// Number and Symbol layer
[_NSL] = LAYOUT_nyquist_wrapper(
  _________________NSL_L1____________________,   XXXXXXX, XXXXXXX,   _________________NSL_R1____________________,
  _________________NSL_L2____________________,   XXXXXXX, XXXXXXX,   _________________NSL_R2____________________,
  _________________NSL_L3____________________,   XXXXXXX, XXXXXXX,   _________________NSL_R3____________________,
  _________________NSL_LT____________________,   XXXXXXX, XXXXXXX,   _________________NSL_RT____________________
),

// SHIFTED Number and Symbol layer
[_NSSL] = LAYOUT_nyquist_wrapper(
  _________________NSSL_L1___________________,   XXXXXXX, XXXXXXX,   _________________NSSL_R1___________________,
  _________________NSSL_L2___________________,   XXXXXXX, XXXXXXX,   _________________NSSL_R2___________________,
  _________________NSSL_L3___________________,   XXXXXXX, XXXXXXX,   _________________NSSL_R3___________________,
  _________________NSSL_LT___________________,   XXXXXXX, XXXXXXX,   _________________NSSL_RT___________________
),

// FUNCTION layer
[_FUNL] = LAYOUT_nyquist_wrapper(
  _________________FUNC_L1___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R1___________________,
  _________________FUNC_L2___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R2___________________,
  _________________FUNC_L3___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R3___________________,
  _________________FUNC_LT___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_RT___________________
),

// Navigation layer
[_NAVR] = LAYOUT_nyquist_wrapper(
  _________________NAV_L1____________________,   XXXXXXX, XXXXXXX,   _________________NAV_R1____________________,
  _________________NAV_L2____________________,   XXXXXXX, XXXXXXX,   _________________NAV_R2____________________,
  _________________NAV_L3____________________,   XXXXXXX, XXXXXXX,   _________________NAV_R3____________________,
  _________________NAV_LT____________________,   XXXXXXX, XXXXXXX,   _________________NAV_RT____________________
),

// MOUSE layer
[_MOUSE] = LAYOUT_nyquist_wrapper(
  _________________MOUSE_L1__________________,   XXXXXXX, XXXXXXX,   _________________MOUSE_R1__________________,
  _________________MOUSE_L2__________________,   XXXXXXX, XXXXXXX,   _________________MOUSE_R2__________________,
  _________________MOUSE_L3__________________,   XXXXXXX, XXXXXXX,   _________________MOUSE_R3__________________,
  _________________MOUSE_LT__________________,   XXXXXXX, XXXXXXX,   _________________MOUSE_RT__________________
),

// MEDIA layer
[_MEDIA] = LAYOUT_nyquist_wrapper(
  _________________MEDIA_L1__________________,   XXXXXXX, XXXXXXX,   _________________MEDIA_R1__________________,
  _________________MEDIA_L2__________________,   XXXXXXX, XXXXXXX,   _________________MEDIA_R2__________________,
  _________________MEDIA_L3__________________,   XXXXXXX, XXXXXXX,   _________________MEDIA_R3__________________,
  _________________MEDIA_LT__________________,   XXXXXXX, XXXXXXX,   _________________MEDIA_RT__________________
),

// Adjust (_MOUSE + _MEDIA)
[_ADJUST] = LAYOUT_nyquist_wrapper(
  _________________DRAGO_L1__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R1__________________,
  _________________DRAGO_L2__________________,   XXXXXXX, XXXXXXX,   XXXXXXX, QWERTY,  WORKMAN, COLEMAK, XXXXXXX,
  _________________DRAGO_L3__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R3__________________,
  _________________DRAGO_LT__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_RT__________________
)


};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
