#pragma once

#include "quantum.h"

#define XXXXXXX KC_NO

enum minorca_layers {
//  _QWERTY,
    _RUNE, // +++
//  _MOUSE, // +++
/*
    _EDITOR,
    _NUMBER,
    _SYMBOL,
    _SECRET, // -> _DEBUG?
    _F_KEYS
*/
};

#define MT_SLSH MT(MOD_RSFT, KC_SLSH)
#define MT_QUOT MT(MOD_LSFT, KC_QUOT)

#define LT_TAB LT(_EDITOR, KC_TAB)
#define LT_ENT LT(_NUMBER, KC_ENT)
//#define LT_SP1 LT(_NUMBER, KC_SPC)
#define LT_SP1 LT(_NUMBER, KC_BSPC)
#define LT_SP2 LT(_SYMBOL, KC_SPC)
#define LT_COMM LT(_MOUSE, KC_COMM)
#define LT_BSPC LT(_SECRET, KC_BSPC)
#define LT_DOT LT(_F_KEYS, KC_DOT)

enum custom_keycodes {
    MINORCA_FIRST = SAFE_RANGE,
    MT_LBRC,
    MT_RBRC,
    MT_LBRK,
    MT_RBRK,
    MT_LPRN,
    MT_RPRN,
    SECRET
};
