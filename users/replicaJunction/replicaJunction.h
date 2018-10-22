#pragma once

#include "quantum.h"

///////////////////////////////////////////////////////////////////////////////
// Keymap definitions
///////////////////////////////////////////////////////////////////////////////

// Layer definitions
// #define L_COLEMAK 0
// #define L_QWERTY  1
// #define L_NUM     2
// #define L_EXTEND  3
// #define L_FUNC    4
// #define L_GAMING  5
// #define L_SYMBOL  6
// #define L_LL_R    7
// #define L_LL_S    8
// #define L_LL_E    9
// #define L_LL_I   10

// Keyboard aliases
#define _______ KC_TRNS
#define ooooooo KC_TRNS

#define MO_FUNC MO(L_FUNC)
#define TT_NUM  TT(L_NUM)
#define TG_GAME TG(L_GAMING)
#define OSL_SYM OSL(L_SYMBOL)

#define OSM_LSF OSM(MOD_LSFT)
#define OSM_RSF OSM(MOD_RSFT)

#define KX_CTSF LCTL(KC_LSFT)
#define KX_STAB LSFT(KC_TAB)
#define KX_CGR  LCTL(KC_GRV)
#define KX_PAST LCTL(LGUI(LALT(KC_V)))
#define KX_SRCH LCTL(LGUI(LALT(KC_S)))

#define KX_BKNM LT(L_NUM, KC_BSPC)
#define KX_DCTL CTL_T(KC_DEL)
#define KX_NALT ALT_T(KC_ENT)
#define KX_ECTL CTL_T(KC_ESC)
#define KX_SPAC LT(L_EXTEND, KC_SPC)

#define KX_Z_MT CTL_T(KC_Z)
#define KX_X_MT GUI_T(KC_X)
#define KX_C_MT MT(MOD_LCTL | MOD_LALT, KC_C)
#define KX_D_MT ALT_T(KC_D)

#define KX_SLMT CTL_T(KC_SLSH)
#define KX_DOMT GUI_T(KC_DOT)
#define KX_COMT MT(MOD_LCTL | MOD_LALT, KC_COMM)
#define KX_H_MT ALT_T(KC_H)

#ifdef L_LL_R
    #define KC_R_LT LT(L_LL_R, KC_R)
#else
    #define KC_R_LT KC_R
#endif

#ifdef L_LL_S
    #define KC_S_LT LT(L_LL_S, KC_S)
#else
    #define KC_S_LT KC_S
#endif

#ifdef L_LL_E
    #define KC_E_LT LT(L_LL_E, KC_E)
#else
    #define KC_E_LT KC_E
#endif

#ifdef L_LL_I
    #define KC_I_LT LT(L_LL_I, KC_I)
#else
    #define KC_I_LT KC_I
#endif

// "Macro" functions
enum userspace_custom_keycodes {
    RJ_MAKE = SAFE_RANGE,  // QMK make command
    RJ_QMKV,               // QMK version
    RJ_EQ,                 // ==
    RJ_NEQ,                // !=
    RJ_GEQ,                // >=
    RJ_LEQ,                // <=
    RJ_GEQR,               // => ("greater than or equal - right")
    RJ_DUND,               // $_
    RJ_SELS,               // select * (used for PowerShell)
    RJ_MUTE,               // Discord mute (GUI+Shift+M)
    RJ_DEAF,               // Discord deafen (GUI+Shift+D)
    RJ_DOVR                // Toggle Discord overlay (GUI+Shift+O)
};

// Mouse keys
#define M_UP KC_MS_UP
#define M_DOWN KC_MS_DOWN
#define M_LEFT KC_MS_LEFT
#define M_RIGHT KC_MS_RIGHT
#define M_LCLIK KC_MS_BTN1
#define M_RCLIK KC_MS_BTN2
#define M_MCLIK KC_MS_BTN3
#define M_WHLUP KC_WH_U
#define M_WHLDN KC_WH_D

// Used in macro definitions
#define TAP(code) register_code (code); unregister_code (code);

// Tap Dance
#ifdef TAP_DANCE_ENABLE
#define TD_LAYER_TOGGLE 0
extern void dance_layer(qk_tap_dance_state_t *state, void *user_data);
#define TD_LAYR TD(TD_LAYER_TOGGLE)
#endif // TAP_DANCE_ENABLE
