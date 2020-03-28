#pragma once

#include "quantum.h"

enum userspace_layers {
  _QWERTY,
  _LOWER, //symbols
  _RAISE, //numbers
  _ADJUST, //system
  _NUMPAD,
  _FN,
  _MOUSE
};

enum userspace_custom_keycodes {
  QWERTY = SAFE_RANGE,
  NEW_SAFE_RANGE,
  // custom keycodes for an Italian ANSI layout with accented vowels
  IT_CMLS, // IT_COMM and IT_LESS when combined with shift
  IT_DTMR, // IT_DOT and IT_MORE when combined with shift
  IT_SLQS, // IT_SLSH and IT_QST when combined with shift
  IT_APDQ, // IT_APO and IT_DQOT when combined with shift
  IT_SCCL, // IT_SMCL and IT_COLN when combined with shift
  PHONE, // my phone number
  DESK, // personal email
  SGCOM, // personal website
  VIVERE, // website
  SVIV // website email
};

// Defining Layer Keycodes
#define QWERTY DF(_QWERTY)
// For LOWER and RAISE I use TT instead of MO to be able to lock those layer tapping three times the key (TAPPING_TOGGLE 3 has been added in sigul.h)
#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define NUMPAD TG(_NUMPAD)
#define FN MO(_FN)
#define MOUSE TT(_MOUSE)
#define TABFN LT(_FN, KC_TAB)
#define ESCFN LT(_FN, KC_ESC)
#define FN_D LT(_FN, IT_D)
#define MS_B LT(_MOUSE, IT_B)

