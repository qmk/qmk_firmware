#include QMK_KEYBOARD_H

#include "ortho.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY_MAC] = LAYOUT_ortho_4x12(
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS, \
      MOVE_MAC, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,  \
      KC_LCTL,  KC_LALT,  KC_LGUI,  RAISE,    P_ADJ,    KC_SPC,   LOWER,    KC_NO,    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC),

  [_MOVE_MAC]   = LAYOUT_ortho_4x12(
      KC_BACK,  IJ_STEP,  IJ_INTO,  IJ_OUT,   IJ_RUN,   IJ_STOP,  _______,  WD_BACK,  KC_HOME,  KC_END,   WD_FRWD,  KC_NEXT, \
      _______,  MM_LH,    MM_MAX,   MM_RH,    IJ_FIND,  IJ_IMPS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CM_RIGHT, CM_DOWN, \
      _______,  MM_UH,    MM_BH,    MAC_CPY,  MAC_PST,  IJ_IMPH,  _______,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______, \
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),
  
  [_RAISE]    = LAYOUT_ortho_4x12(
      KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE, \
      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DQUO, \
      _______,  KC_UNDO,  KC_CUT,   OS_COPY,  OS_PAST,  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_LT,    KC_GT,    KC_QUES,  _______, \
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

  [_LOWER]    = LAYOUT_ortho_4x12(
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS, \
      _______,  KC_4,     KC_5,     KC_6,     KC_PMNS,  KC_PSCR,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT, \
      _______,  KC_1,     KC_2,     KC_3,     KC_PPLS,  KC_NO,    KC_NO,    KC_WHOM,  KC_WBAK,  KC_WFWD,  KC_WSCH,  _______, \
      _______,  KC_0,     KC_DOT,   KC_ENT,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

  [_ADJUST]   = LAYOUT_ortho_4x12(
      _______,  NK_ON,    NK_OFF,   EEP_RST,  RESET,    KC_MSTP,  KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  KC_BTN2,  KC_INS,  \
      _______,  GE_SWAP,  GE_NORM,  DEBUG,    AG_SWAP,  AG_NORM,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN1,  _______, \
      _______,  KC_LYRC,  KC_FIRST, KC_CAPS,  KC_NO,    KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______, \
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______)
};
