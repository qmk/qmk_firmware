#pragma once

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif
#include "quantum.h"

#undef TAPPING_TERM
#define TAPPING_TERM 150

// Keys 

#define D_NAVI MT(MOD_LCTL | MOD_LSFT, KC_D)
