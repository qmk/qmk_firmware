#ifndef KOY_KEYS_ON_QUERTZ_DE_LATIN1_H
#define KOY_KEYS_ON_QUERTZ_DE_LATIN1_H


/*
This file defines the desierd KOY keys if you use a software (operating sysetm)
configured for a QUERTZ layout (de-latin1).
These chars can be created by using ALTGR on linux and a few of them on windows
with a German de-latin1 layout (depending on desktop environment and/or
application).
    ′¹²³¼½¬{[]}\¸
    @ł€¶ŧ←↓→øþ¨~
    æſðđŋħ̣ĸł˝^’
    |»«¢„“”µ·…–
Additionally, there are some common chars that we dit not yet define:
    §
*/


#include "koy_common.h"


// NQN key definitions in no particular order
#define N_LT KC_NONUS_BSLASH
#define N_HS KC_NONUS_HASH
#define N_DOTS RALT(KC_DOT) // …
#define N_USC LSFT(KC_SLASH) // _
#define N_LSQBR RALT(KC_8) // [
#define N_RSQBR RALT(KC_9) // ]
#define N_CIRC KC_GRAVE // ^
#define N_EXKL LSFT(KC_1) // !
#define N_GT LSFT(KC_NONUS_BSLASH) // >
#define N_EQ LSFT(KC_0) // =
#define N_AMP LSFT(KC_6) // &
#define N_BSLS RALT(KC_MINS) // \ backslash
#define N_SLSH LSFT(KC_7) // /
#define N_LCUBR RALT(KC_7) // {
#define N_RCUBR RALT(KC_0) // }
#define N_ASTR LSFT(KC_RBRC) // *
#define N_QUES LSFT(KC_MINS) // ?
#define N_LPARN LSFT(KC_8) // (
#define N_RPARN LSFT(KC_9) // )
#define N_MINS KC_SLASH // -
#define N_COLN LSFT(KC_DOT) // :
#define N_HASH KC_BSLASH // #
#define N_DLR LSFT(KC_4) // $
#define N_PIPE RALT(KC_NONUS_BSLASH) // |
#define N_TILD RALT(KC_RBRC) // ~
#define N_GRAVE LSFT(KC_EQUAL) // `
#define N_PLUS KC_RBRC // +
#define N_PERC LSFT(KC_5) // %
#define N_QUOT LSFT(KC_2) // "
#define N_SING LSFT(KC_BSLASH) // '
#define N_SEMI LSFT(KC_COMM) // ;
#define N_EURO RALT(KC_E) // €
#define N_AT RALT(KC_Q) // @
#define N_Z KC_Y
#define N_Y KC_Z
#define N_AE KC_QUOTE // ä
#define N_OE KC_SCOLON // ö
#define N_UE KC_LBRACKET // ü
#define N_MU RALT(KC_M) // µ
#define N_SS KC_MINS // ß
#define N_DEGRE LSFT(KC_GRAVE) // °
#define N_PASTE LCTL(KC_V) // CTRL+V
#define N_COPY LCTL(KC_C) // CTRL+C
#define N_CUT LCTL(KC_X) // CTRL+X
#define N_UNDO LCTL(N_Z) // CTRL+Z


#endif
