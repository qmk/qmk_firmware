#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "keymap_uk.h"



// Layer keys
#define NUM LT(_NUM, KC_ENT)
#define NAV LT(_NAV, KC_ESC)
// FUN is both together

// shortcuts
#define M_UNDO C(UK_Z)
#define M_CUT C(UK_X)
#define M_COPY C(UK_C)
#define M_PSTE C(UK_V)
#define M_SAVE C(UK_S)
#define TAB_L C(S(UK_LBRC))
#define TAB_R C(S(UK_RBRC))
#define WS_L A(S(KC_LEFT))  // select word left
#define WS_R A(S(KC_RIGHT)) // select word right
#define W_L A(KC_LEFT)      // move word left
#define W_R A(KC_RIGHT)     // move word right
#define LAU A(KC_SPC)    // Launcher for krunner 

// awkward symbols to type
#define GBPD LALT(UK_3) // UK pound sign
#define PMIN LALT(UK_PLUS) // plus/minus symbol
#define SHFT OSM(MOD_LSFT)
#define M_UNDO C(UK_Z)


