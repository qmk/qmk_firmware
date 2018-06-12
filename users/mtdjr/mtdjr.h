#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _SUPER 3
#define _ADJUST 16

enum user_layers {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  SUPER,
  ADJUST,
};

enum user_tapdance {
  TD_ENDLOCK,
  TD_ALTLOCK,
  TD_ESC,
};

enum user_solenoid {
  SOLENOID_TOG,
  SOLENOID_DWELL_MINUS,
  SOLENOID_DWELL_PLUS,
  SOLENOID_BUZZ_ON,
  SOLENOID_BUZZ_OFF,
};

#define KC_STOG SOLENOID_TOG
#define KC_SDM  SOLENOID_DWELL_MINUS
#define KC_SDP  SOLENOID_DWELL_PLUS
#define KC_SBON SOLENOID_BUZZ_ON
#define KC_SBOF SOLENOID_BUZZ_OFF

#define KC_     KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_xxxx KC_NO

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_SUPR SUPER
#define KC_RST  RESET

// TapDance Keycodes
#define KC_EXC  TD_ESC

// Macro Declarations
#define KC_ROOT M(0)
#define KC_PPLY M(1)
#define KC_PSEF M(2)
#define KC_XCPY M(3)
#define KC_XINS M(4)
#define KC_CAD  M(5)
#define UM_LOCK M(6)

// RGB and Backlighting
#define KC_RGB  RGB_TOG
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_BLT  BL_TOGG
#define KC_BLS  BL_STEP
#define KC_BLI  BL_INC
#define KC_BLD  BL_DEC


#endif
