#pragma once
#include "quantum.h"

#define BWORD LCTL(KC_BSPC)
#define LWORD LCTL(KC_LEFT)
#define RWORD LCTL(KC_RIGHT)
#define JUMPBACK LSFT(KC_TAB)
#define UNDO LCTL(KC_Z)
#define XPANDR LCTL(LSFT(KC_X))
#define NTAB LCTL(KC_T)
#define CTAB LCTL(KC_W)
#define XPANDR LCTL(LSFT(KC_X))
#define CMDBSP MT(MOD_LGUI, KC_BSPC)
#define ALTDEL MT(MOD_LALT, KC_DEL)

// Define all of
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  CSPEAK,
  SPEAK1,
  SPEAK2,
  SPEAK3,
  SPEAK4,
  PARADOWN,
  WREFRESH,
  PMERGE,
  REMCAPS,
};

