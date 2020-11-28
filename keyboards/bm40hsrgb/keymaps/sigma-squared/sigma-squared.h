// qmk flash -kb bm40hsrgb -km sigma-squared

#pragma once

#include QMK_KEYBOARD_H

#define KC_NP KC_NO // key is not present
#define KC_NA KC_NO // present but not available for use
#define KC_NU KC_NO // available but not used

// non-KC_ keycodes
#define KC_RST RESET
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

//define layers
enum layers { BASE, MEDR, NAVR, NSSL, NSL, FUNL, GAME, SECGAME, CHAT, NAVR2, NSSL2, NSL2};

//define macro names
enum {
  M_EMAIL1 = SAFE_RANGE,
  M_EMAIL2,
  M_MATRIKEL,
  M_PHONE,
  M_ADDRESS,
};
