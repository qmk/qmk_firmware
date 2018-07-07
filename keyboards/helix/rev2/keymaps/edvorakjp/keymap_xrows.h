#ifndef KEYMAP_XROWS_H
#define KEYMAP_XROWS_H

#include "edvorakjp.h"

enum custom_keycodes {
  KC_LOCK = NEW_SAFE_RANGE,
};

#define KC_ KC_TRNS

#define KC_TMB1 LGUI_T(KC_TAB)
#define KC_TMB2 LSFT_T(KC_SPC)
#define KC_TMB3 LOWER // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_TMB4 LCTL_T(KC_ESC)
#define KC_TMB5 RSFT_T(KC_DEL)
#define KC_TMB6 RAISE // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped
#define KC_TMB7 RCTL_T(KC_BSPC)
#define KC_TMB8 RALT_T(KC_ENT)
#define KC_TMB9 LGUI(KC_TAB)

#define KC_RST  RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_EDJP EDVORAK
#define KC_QWER QWERTY

#endif
