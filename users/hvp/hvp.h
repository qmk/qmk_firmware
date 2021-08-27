#pragma once
#include "quantum.h"
#undef TAPPING_TERM
#define TAPPING_TERM 150

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif

#ifdef TAPPING_TERM_PER_KEY
#    include "per_key.h"
#endif


#define D_NAVI MT(MOD_LCTL | MOD_LSFT, KC_D)

/* Home-row mods */
#define LG_A MT(MOD_LGUI, KC_A)
#define LA_S MT(MOD_LALT, KC_S)
#define LS_D MT(MOD_LSFT, KC_D)
#define LC_F MT(MOD_LCTL, KC_F)

#define RC_H MT(MOD_RCTL, KC_H)
#define RS_J MT(MOD_RSFT, KC_J)
#define RA_K MT(MOD_RALT, KC_K)
#define RG_L MT(MOD_RGUI, KC_L)