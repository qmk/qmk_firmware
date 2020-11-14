#pragma once
#include "quantum.h"

enum custom_keycodes
{
    EPRM = SAFE_RANGE, 
    RGB_SLD,
    ALT_TAB,
    QWERTY,
    SYM,
    NAV,
    ADJUST,
// Macros
    ARROW,
    IARROW,
    CLN_EQ,
    F_ARROW,
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
    MAC_TGL,
    INC_MACROS_START,
    INC_MACROS_END,
};

//**************** KEYCODES *********************//
enum layers {
    _QWERTY,
    _SYMB,
    _NAV,
    _ADJUST,
    _F,
    _D,
    _S,
    _A,
    _J,
    _K,
    // iris specific - TBD
    _LOWER,
    _RAISE,
    _MACROS,
    _SAFE_LAYER
};

//===== Function letters
# define FN_F LT(_F,KC_F)
# define FN_D LT(_D,KC_D)
# define FN_S LT(_S,KC_S)
# define FN_A LT(_A,KC_A)
# define FN_K LT(_K,KC_K)
# define FN_J LT(_J,KC_J)
# define KC_FN_D FN_D
# define KC_FN_S FN_S
# define KC_FN_F FN_F

# define KC_MACROS OSL(_MACROS)


# define KC_E_COLN LSFT(KC_DOT)
# define KC_E_EQL ES_EQL
# define KC_GUI OSM(MOD_RGUI)
# define KC_R_NUB S(KC_NUBS)
# define KC_E_LT KC_NUBS
# define KC_E_GT S(KC_NUBS)
# define KC_E_TILD ES_TILD
# define KC_E_MINS ES_MINS
# define KC_E_OVRR ES_OVRR
# define KC_E_APOS ES_APOS
# define KC_E_IEXL ES_IEXL
//==========  Short hand for complex key combinations
# define WIN_LEFT_HALF LALT(LGUI(KC_LEFT))
# define WIN_RIGHT_HALF LALT(LGUI(KC_RIGHT))
# define WIN_TO_LEFT LALT(LSFT( LGUI(KC_LEFT) ))
# define WIN_TO_RIGHT LALT(LSFT( LGUI(KC_RIGHT) ))
# define ALL_WIN LCTL(KC_DOWN)
# define EXPOSE LGUI(KC_DOWN)
// ========== Modifiers!!
# define SHIFT OSM(MOD_LSFT)
//=============== tap for key hold for mod
# define HYPR_H HYPR_T(KC_H)
# define CTL_K RCTL_T(KC_K)
# define ALT_J ALT_T(KC_J)
# define SFT_MINS LSFT_T(KC_MINS) // tap - hold shift
# define CMD_QUOT GUI_T(KC_QUOTE) // tap ' hold cmd
//=============== Movement modified
# define CTL_LEFT LCTL(KC_LEFT)
# define CTL_RIGHT LCTL(KC_RIGHT)

# define SFT_LEFT LSFT(KC_LEFT)
# define SFT_RIGHT LSFT(KC_RIGHT)
