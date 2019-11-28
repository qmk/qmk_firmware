#pragma once

#include "quantum.h"
#include "process_records.h"

enum userspace_layers
{
    _QWERTY = 0,
    _EDITOR,
    _NUMBER,
    _SYMBOL,
    _F_KEYS,
    _DEBUG,
    _SECRET,
    _FINAL
};

// modtaps
#define LS_Z MT(MOD_LSFT, KC_Z)
#define LC_ESC MT(MOD_LCTL, KC_ESC)
#define LG_TAB MT(MOD_LGUI, KC_TAB)
#define LA_LBRC MT(MOD_LALT, KC_LBRC)
#define LS_RBRC MT(MOD_LSFT, KC_RBRC)
#define RS_MINS MT(MOD_RSFT, KC_MINS)
#define RA_EQL MT(MOD_RALT, KC_EQL)
//RG_LMOT defined in process_records.h
#define RC_ENT MT(MOD_RCTL, KC_ENT)
#define RS_SLSH MT(MOD_RSFT, KC_SLSH)
// layertaps
#define ED_A LT(_EDITOR, KC_A)
#define ED_ESC LT(_EDITOR, KC_ESC)
#define NM_SCLN LT(_NUMBER, KC_SCLN)
#define NM_BSPC LT(_NUMBER, KC_BSPC)
#define SM_SPC LT(_SYMBOL, KC_SPC)
#define SC_TAB LT(_SECRET, KC_TAB)
#define FK_DOT LT(_F_KEYS, KC_DOT)

