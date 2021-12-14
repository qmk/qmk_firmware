// replaces #include "keymap_german_osx.h"
# pragma once

#define DE_AE    A(KC_A)    // Ä
#define DE_UE    A(KC_U)    // Ü
#define DE_OE    A(KC_O)    // Ö
#define DE_SS    A(KC_S)    // ß
#define DE_EURO  A(S(KC_2)) // €


// aliases for readability

#define LETTERS  DF(_LETTERS)
// #define QWERTY   DF(_QWERTY) // TBD

#define SYM      TO(_SYMBOLS)
#define NUM      TO(_NUMBERS)
#define NAV      TO(_NAV)
#define MCO      TO(_MEDIA_CODE)
// #define CTL      TO(_KBD_CTRL) // TBD

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
