// short version to replace #include "keymap_german_osx.h"
# pragma once

#define DE_AE    A(KC_A)    // Ä
#define DE_UE    A(KC_U)    // Ü
#define DE_OE    A(KC_O)    // Ö
#define DE_SS    A(KC_S)    // ß
#define DE_EURO  A(S(KC_2)) // €


// aliases for readability

// #define QWERTY   DF(_QWERTY) // todo: different letter layouts

#define XOY      TO(_LETTERS)
#define SYM      TO(_SYMBOLS)
#define NUM      TO(_NUMBERS)
#define NAV      TO(_NAV)
#define MECO     TO(_MEDIA_CODE)
#define GAME     TO(_GAME)
#define HYPA     OSL(_HYPER)
// #define CTL      TO(_KBD_CTRL) // todo: kbd ctrl layer

#define ALT_TAB  ALT_T(KC_TAB)
#define CMD_SPC  GUI_T(KC_SPACE)
#define SFT_ENT  SFT_T(KC_ENT)
#define CMD_BSP  GUI_T(KC_BSPC)
#define ALT_DEL  ALT_T(KC_DEL)
