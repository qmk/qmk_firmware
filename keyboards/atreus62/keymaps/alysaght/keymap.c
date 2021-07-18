// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// qmk compile -kb atreus62
// qmk flash -kb atreus62


#include QMK_KEYBOARD_H
#include "alysaght.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Qwerty
[_QWERTY] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________ALPHA_LN__________________,                       _________________ALPHA_RN__________________, XXXXXXX,
  XXXXXXX, _________________QWERTY_L1_________________,                       _________________QWERTY_R1_________________, XXXXXXX,
  XXXXXXX, _________________QWERTY_L2_________________,                       _________________QWERTY_R2_________________, XXXXXXX,
  XXXXXXX, _________________QWERTY_L3_________________,                       _________________QWERTY_R3_________________, XXXXXXX,
  XXXXXXX, _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________, XXXXXXX
),

// Workman
[_WORKMAN] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________ALPHA_LN__________________,                       _________________ALPHA_RN__________________, XXXXXXX,
  XXXXXXX, _________________WORKMAN_L1________________,                       _________________WORKMAN_R1________________, XXXXXXX,
  XXXXXXX, _________________WORKMAN_L2________________,                       _________________WORKMAN_R2________________, XXXXXXX,
  XXXXXXX, _________________WORKMAN_L3________________,                       _________________WORKMAN_R3________________, XXXXXXX,
  XXXXXXX, _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________, XXXXXXX
),

// Colemak DH
[_COLEMAK] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________ALPHA_LN__________________,                       _________________ALPHA_RN__________________, XXXXXXX,
  XXXXXXX, _________________COLEMAK_L1________________,                       _________________COLEMAK_R1________________, XXXXXXX,
  XXXXXXX, _________________COLEMAK_L2________________,                       _________________COLEMAK_R2________________, XXXXXXX,
  XXXXXXX, _________________COLEMAK_L3________________,                       _________________COLEMAK_R3________________, XXXXXXX,
  XXXXXXX, _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________, XXXXXXX
),

// Final Fantasy XIV
[_FFXIV] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________FFXIV_L0__________________,                       _________________FFXIV_R0__________________, XXXXXXX,
  XXXXXXX, _________________FFXIV_L1__________________,                       _________________FFXIV_R1__________________, XXXXXXX,
  XXXXXXX, _________________FFXIV_L2__________________,                       _________________FFXIV_R2__________________, XXXXXXX,
  XXXXXXX, _________________FFXIV_L3__________________,                       _________________FFXIV_R3__________________, XXXXXXX,
  XXXXXXX, _________________FFXIV_LT__________________,   XXXXXXX, XXXXXXX,   _________________FFXIV_RT__________________, XXXXXXX
),

// Number and Symbol layer
[_NSL] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________NSL_L1____________________,                       _________________NSL_R1____________________, XXXXXXX,
  XXXXXXX, _________________NSL_L2____________________,                       _________________NSL_R2____________________, XXXXXXX,
  XXXXXXX, _________________NSL_L3____________________,                       _________________NSL_R3____________________, XXXXXXX,
  XXXXXXX, _________________NSL_LT____________________,   XXXXXXX, XXXXXXX,   _________________NSL_RT____________________, XXXXXXX
),

// SHIFTED Number and Symbol layer
[_NSSL] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________NSSL_L1___________________,                       _________________NSSL_R1___________________, XXXXXXX,
  XXXXXXX, _________________NSSL_L2___________________,                       _________________NSSL_R2___________________, XXXXXXX,
  XXXXXXX, _________________NSSL_L3___________________,                       _________________NSSL_R3___________________, XXXXXXX,
  XXXXXXX, _________________NSSL_LT___________________,   XXXXXXX, XXXXXXX,   _________________NSSL_RT___________________, XXXXXXX
),

// FUNCTION layer
[_FUNL] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________FUNC_L1___________________,                       _________________FUNC_R1___________________, XXXXXXX,
  XXXXXXX, _________________FUNC_L2___________________,                       _________________FUNC_R2___________________, XXXXXXX,
  XXXXXXX, _________________FUNC_L3___________________,                       _________________FUNC_R3___________________, XXXXXXX,
  XXXXXXX, _________________FUNC_LT___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_RT___________________, XXXXXXX
),

// Navigation layer
[_NAVR] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________NAV_L1____________________,                       _________________NAV_R1____________________, XXXXXXX,
  XXXXXXX, _________________NAV_L2____________________,                       _________________NAV_R2____________________, XXXXXXX,
  XXXXXXX, _________________NAV_L3____________________,                       _________________NAV_R3____________________, XXXXXXX,
  XXXXXXX, _________________NAV_LT____________________,   XXXXXXX, XXXXXXX,   _________________NAV_RT____________________, XXXXXXX
),

// MOUSE layer
[_MOUSE] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________MOUSE_L1__________________,                       _________________MOUSE_R1__________________, XXXXXXX,
  XXXXXXX, _________________MOUSE_L2__________________,                       _________________MOUSE_R2__________________, XXXXXXX,
  XXXXXXX, _________________MOUSE_L3__________________,                       _________________MOUSE_R3__________________, XXXXXXX,
  XXXXXXX, _________________MOUSE_LT__________________,   XXXXXXX, XXXXXXX,   _________________MOUSE_RT__________________, XXXXXXX
),

// MEDIA layer
[_MEDIA] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________MEDIA_L1__________________,                       _________________MEDIA_R1__________________, XXXXXXX,
  XXXXXXX, _________________MEDIA_L2__________________,                       _________________MEDIA_R2__________________, XXXXXXX,
  XXXXXXX, _________________MEDIA_L3__________________,                       _________________MEDIA_R3__________________, XXXXXXX,
  XXXXXXX, _________________MEDIA_LT__________________,   XXXXXXX, XXXXXXX,   _________________MEDIA_RT__________________, XXXXXXX
),

// Adjust (_MOUSE + _MEDIA)
[_ADJUST] = LAYOUT_custom_wrapper(
  XXXXXXX, _________________BLANK_5___________________,                       _________________BLANK_5___________________, XXXXXXX,
  XXXXXXX, _________________DRAGO_L1__________________,                       _________________DRAGO_R1__________________, XXXXXXX,
  XXXXXXX, _________________DRAGO_L2__________________,                       FFXIV,   QWERTY,  WORKMAN, COLEMAK, XXXXXXX, XXXXXXX,
  XXXXXXX, _________________DRAGO_L3__________________,                       _________________DRAGO_R3__________________, XXXXXXX,
  XXXXXXX, _________________DRAGO_LT__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_RT__________________, XXXXXXX
)


};
