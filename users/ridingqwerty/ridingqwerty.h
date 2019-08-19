#pragma once

#include "quantum.h"
#include "version.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#    include "tapdances.h"
#endif
#if defined(UNICODEMAP_ENABLE)
#    include "unicode.h"
#endif

enum userspace_layers
{
    _QWERTY = 0,
#if defined(UNICODEMAP_ENABLE)
    _RUNE,
    _GREEK, //wip
#endif
    _EDITOR,
    _NUMBER,
    _SYMBOL,
    _F_KEYS,
    _DEBUG,  // version, make,reset?
    _SECRET, // roll secret into debug?
#if defined(MOUSEKEY_ENABLED)
    _MOUSE,
#endif
    _FINAL
};

#define LS(kc) MT(MOD_LSFT, KC_##kc)
#define LC(kc) MT(MOD_LCTL, KC_##kc)
#define LG(kc) MT(MOD_LGUI, KC_##kc)
#define LA(kc) MT(MOD_LALT, KC_##kc)
#define RS(kc) MT(MOD_RSFT, KC_##kc)
#define RC(kc) MT(MOD_RCTL, KC_##kc)
#define RG(kc) MT(MOD_RGUI, KC_##kc)
#define RA(kc) MT(MOD_RALT, KC_##kc)

// modtaps -- most can go
//#define LS_Z MT(MOD_LSFT, KC_Z)
//#define LS_RBRC MT(MOD_LSFT, KC_RBRC)
//#define LC_ESC MT(MOD_LCTL, KC_ESC)
//#define LG_TAB MT(MOD_LGUI, KC_TAB)
//#define LG_LBRC MT(MOD_LGUI, KC_LBRC)
//#define LA_LBRC MT(MOD_LALT, KC_LBRC)
//#define LA_RBRC MT(MOD_LALT, KC_RBRC)
//#define RS_MINS MT(MOD_RSFT, KC_MINS)
//#define RA_EQL MT(MOD_RALT, KC_EQL)
//#define RA_MINS MT(MOD_RALT, KC_MINS)
//RG_LMOT defined in process_records.h
//#define RG_EQL MT(MOD_RGUI, KC_EQL)
//#define RC_ENT MT(MOD_RCTL, KC_ENT)
//#define RS_SLSH MT(MOD_RSFT, KC_SLSH)
// layertaps
// first two letters denote shorthand for destination layer
// ED = EDTIOR, NM = NUMBER, SM = SYMBOL, SC = SECRET, FK = F_KEYS
#define ED(kc) LT(_EDITOR, KC_##kc)
#define NM(kc) LT(_NUMBER, KC_##kc)
#define SM(kc) LT(_SYMBOL, KC_##kc)
#define SC(kc) LT(_SECRET, KC_##kc)
#define FK(kc) LT(_F_KEYS, KC_##kc)

//#define ED_A LT(_EDITOR, KC_A)
//#define ED_ESC LT(_EDITOR, KC_ESC)
//#define NM_SCLN LT(_NUMBER, KC_SCLN)
//#define NM_BSPC LT(_NUMBER, KC_BSPC)
//#define NM_ENT LT(_NUMBER, KC_ENT)
//#define SM_SPC LT(_SYMBOL, KC_SPC)
//#define SC_TAB LT(_SECRET, KC_TAB)
//#define SC_BSPC LT(_SECRET, KC_BSPC)
//#define FK_DOT LT(_F_KEYS, KC_DOT)

// MINORCA BULLSHIT -- FIX THIS
#define MT_SLSH RS_SLSH
#define LT_SP1 NM_BSPC
#define LT_SP2 SM_SPC
#define LT_DOT FK_DOT
#define MS_COMM LT(_MOUSE, KC_COMM)
#define LT_COMM MS_COMM
#define LS_QUOT MT(MOD_LSFT, KC_QUOT)
#define MT_QUOT LS_QUOT
#define ED_TAB LT(_EDITOR, KC_TAB)    
#define LT_TAB ED_TAB
#define LT_ENT NM_ENT

void	matrix_init_keymap(void);
