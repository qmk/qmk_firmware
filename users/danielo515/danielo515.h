#pragma once

#include "quantum.h"


bool handle_macro(uint16_t kc);
bool is_macro (uint16_t kc);
bool process_incremental_macro (uint16_t);
void refresh_incremental_macros (uint16_t);
//**************** KEYCODES *********************//

enum custom_keycodes
{
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
  ALT_TAB,
  // Macros
  ARROW,
  F_ARROW,
  QWERTY,
  GREP,
  // Accented characters
  AC_A,
  AC_E,
  AC_I,
  AC_O,
  // Custom multi-os key-codes
  CUT,
  COPY,
  PASTE,
  SAVE,
  UNDO,
  CHG_LAYOUT,
  FIND,
  // OTHER OLD STUFF
  LOWER,
  RAISE,
  ADJUST,
  MAC_TGL,
  MACRO_START,  // START OF VSC DECLARATIONS
  T_TERM,
  FIX_ALL,
  BLK_CMNT,
  LN_CMNT,
  CMD_S_P,
  TRI_TICKS,
  MACRO_END,  // END OF VSC DECLARATIONS
  INC_MACROS_START,
  INC_MACROS_END,
};


enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _F,
  _D,
  _A,
  _S,
  _J,
  _K,
  _MACROS,
  _ADJUST,
  _SAFE_LAYER
};

// Function letters
#define FN_F LT(_F,KC_F)
#define FN_D LT(_D,KC_D)
#define FN_S LT(_S,KC_S)
#define FN_A LT(_A,KC_A)
#define FN_K LT(_K,KC_K)
#define FN_J LT(_J,KC_J)
#define KC_FN_D FN_D
#define KC_FN_S FN_S
#define KC_FN_F FN_F

#define KC_MACROS OSL(_MACROS)


#define KC_E_COLN LSFT(KC_DOT)
#define KC_E_EQL ES_EQL
#define KC_GUI OSM(MOD_RGUI)
#define KC_R_NUB S(KC_NUBS)
#define KC_E_LT KC_NUBS
#define KC_E_GT S(KC_NUBS)
#define KC_E_TILD ES_TILD
#define KC_E_MINS ES_MINS
#define KC_S_SPC SFT_T(KC_SPC)  // Tap for Space, hold for Shift
#define KC_E_OVRR ES_OVRR
#define KC_E_APOS ES_APOS
#define KC_E_IEXL ES_IEXL
// Short hand for complex key combinations
# define WIN_LEFT_HALF LALT(LGUI(KC_LEFT))
# define WIN_RIGHT_HALF LALT(LGUI(KC_RIGHT))
# define WIN_TO_LEFT LALT(LSFT( LGUI(KC_LEFT) ))
# define WIN_TO_RIGHT LALT(LSFT( LGUI(KC_RIGHT) ))

// Ready to use Tap dance definitions, just put them on your layout

#ifdef TAP_DANCE_ENABLE
    #include "tap_dance.h"
#endif
