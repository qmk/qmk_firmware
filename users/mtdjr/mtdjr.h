#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Layers
enum user_enum {
  // Layers
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  SUPER,
  ADJUST,
  // Solenoid
  SOLENOID_TOG,
  SOLENOID_DWELL_MINUS,
  SOLENOID_DWELL_PLUS,
  SOLENOID_BUZZ_ON,
  SOLENOID_BUZZ_OFF,
};

// Macro / Send String
enum user_macros {
  ROOT,
  PPLY,
  PSEF,
};

// TapDance
enum user_tapdance {
  TD_ENDLOCK,
  TD_ALTLOCK,
  TD_PRINT,
  TD_ESC,
};


// Layers
#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _SUPER  3
#define _ADJUST 16

// Macros
#define KC_ROOT M(ROOT)
#define KC_PPLY M(PPLY)
#define KC_PSEF M(PSEF)

// Tapdance
#define KC_EXC  TD(TD_ESC)
#define KC_ELCK TD(TD_ENDLOCK)
#define KC_ALCK TD(TD_ALTLOCK)
#define KC_MPNT TD(TD_PRINT)

// Custom Keycodes
#define KC_     KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_xxxx KC_NO
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_SUPR SUPER
#define KC_RST  RESET

// Key Combos
#define KC_XCPY LCTL(KC_INS)
#define KC_XINS LSFT(KC_INS)
#define KC_CAD  LCTL(LALT(KC_DEL))
#define KC_XCAD LCTL(LALT(KC_DEL))
#define KC_XLCK LGUI(KC_L)

// Solenoid
#define KC_STOG SOLENOID_TOG
#define KC_SDM  SOLENOID_DWELL_MINUS
#define KC_SDP  SOLENOID_DWELL_PLUS
#define KC_SBON SOLENOID_BUZZ_ON
#define KC_SBOF SOLENOID_BUZZ_OFF

// RGB and Backlighting
#define KC_RGB  RGB_TOG
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_MOD  RGB_MOD
#define KC_RMOD RGB_RMOD
#define KC_RPLN RGB_M_P
#define KC_RBTH RGB_M_B
#define KC_BLT  BL_TOGG
#define KC_BLS  BL_STEP
#define KC_BLI  BL_INC
#define KC_BLD  BL_DEC
#define KC_BLB  BL_BRTG
#define KC_BLON BL_ON
#define KB_BLOF BL_OFF


#endif
