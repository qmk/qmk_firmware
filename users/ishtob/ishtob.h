#ifndef USERSPACE
#define USERSPACE
#include "quantum.h"

enum userspace_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
  DFU,
  P_CITRIX, //these macro exsists in macros_private.c, which is excluded from git
  P_MPASS,
  P_META,
  O_DAYRN,
  O_RTQ6H,
  O_3DRN,
  O_AUTODC,
  M_EMAIL,
  M_EMAIL2
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _PLOVER 5
#define _FNLAYER 6
#define _NUMLAY 7
#define _MOUSECURSOR 8
#define _ADJUST 16



#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define CTL_TTAB    CTL_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_FN(kc)   LT(_FNLAYER, kc)            // L-ayer T-ap Function Layer
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define LT_RAI(kc)  LT(_RAISE, kc)              // L-ayer T-ap to Raise
#define TG_NUMLAY   TG(_NUMLAY)                 //Toggle for layer _NUMLAY
/*
enum userspace_layers {
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _FNLAYER,
  _NUMLAY,
  _MOUSECURSOR,
  _ADJUST
};
*/



#endif // !USERSPACE