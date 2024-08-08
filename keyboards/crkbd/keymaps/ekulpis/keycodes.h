#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "keymap_uk.h"



// Thumbs
#define MED LT(_MEDIA, KC_ESC)
#define NAV LT(_NAV, KC_SPC)
#define SHFT OSM(MOD_LSFT)

#define SYM LT(_SYM, KC_ENT)
#define NUM LT(_NUM, KC_BSPC)
#define FUN LT(_FUN, KC_DEL)

#define MOUS LT(_MOUS, KC_TAB)

#define LAU LGUI(UK_D)    // launcher (cmd+spc)
#define CLBRC S(KC_LBRC)
#define CRBRC S(KC_RBRC)
#define AMPR S(UK_7)
#define ASTR S(UK_8)
#define HASH S(UK_4)
#define EXCL S(UK_1)
#define DQUOT S(UK_2)
#define ATSYM S(KC_QUOT)
#define PIPE S(KC_NUBS)
#define DOLLA S(UK_4)
#define PERC S(UK_5)
#define CARROT S(UK_6)
#define PLUS S(KC_EQL)
#define COLLON S(KC_SCLN)
#define LPAR S(UK_9)
#define RPAR S(UK_0)
#define UNDRS S(KC_MINS)
#define GBPD S(UK_3)

 